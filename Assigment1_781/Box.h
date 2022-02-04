#pragma once
#include "Object.h"
#include "Triangle.h"
#include <vector>

// Box object
class Box : public Object
{
public:

	// Length, Breadth and Height of the box
	double l, b, h;
	/// centre of the box and local x,y,z axis of the box(in box co-ordinate system where centre is origin)
	Vec centre, vx, vy, vz;
	// We are discribing box as collection of 12 triangles
	std::vector<Triangle> face_triangles;

	// Constructors

	Box() :centre(0, 0, 0), l(1), b(1), h(1), vx(1, 0, 0), vy(0, 1, 0) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material();
		vz = Vec(0, 0, 1);
		addFaces();
	}

	Box(Vec centre, double l, double b, double h, Vec vx, Vec vy) : centre(centre), l(l), b(b), h(h), vx(vx.normalize()), vy(vy.normalize()) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material();
		vz = vx.cross(vy).normalize();
		addFaces();
	}

	Box(Vec centre, double l, double b, double h, Vec vx, Vec vy, Color color) : centre(centre), l(l), b(b), h(h), vx(vx.normalize()), vy(vy.normalize()) {
		this->color = color;
		this->material = Material();
		vz = vx.cross(vy).normalize();
		addFaces();
	}

	Box(Vec centre, double l, double b, double h, Vec vx, Vec vy, Color color, Material material) : centre(centre), l(l), b(b), h(h), vx(vx.normalize()), vy(vy.normalize()) {
		this->color = color;
		this->material = material;
		vz = vx.cross(vy).normalize();
		addFaces();
	}

	/// <summary>
	///	It adds 12 triangles(2 for each face) for the given box
	/// </summary>
	void addFaces() {

		Vec c = centre * 2;

		Vec ubl = (c + vz * b + vy * h - vx * l) * 0.5;
		Vec ubr = (c + vz * b + vy * h + vx * l) * 0.5;
		Vec utl = (c - vz * b + vy * h - vx * l) * 0.5;
		Vec utr = (c - vz * b + vy * h + vx * l) * 0.5;
		Vec lbl = (c + vz * b - vy * h - vx * l) * 0.5;
		Vec lbr = (c + vz * b - vy * h + vx * l) * 0.5;
		Vec ltl = (c - vz * b - vy * h - vx * l) * 0.5;
		Vec ltr = (c - vz * b - vy * h + vx * l) * 0.5;

		// Top face triangles
		face_triangles.push_back(Triangle(utr, utl, ubr));
		face_triangles.push_back(Triangle(utl, ubr, ubl));

		// Bottom face triangles
		face_triangles.push_back(Triangle(ltr, ltl, lbr));
		face_triangles.push_back(Triangle(ltl, lbr, lbl));
	
		// Right face traingles
		face_triangles.push_back(Triangle(utr, ltr, ubr));
		face_triangles.push_back(Triangle(lbr, ltr, ubr));

		// Left face triangles
		face_triangles.push_back(Triangle(lbl, utl, ubl));
		face_triangles.push_back(Triangle(lbl, utl, ltl));

		// Front face trinagles
		face_triangles.push_back(Triangle(ubr, ubl, lbr));
		face_triangles.push_back(Triangle(ubl, lbl, lbr));

		// Back face triangles
		face_triangles.push_back(Triangle(utr, utl, ltr));
		face_triangles.push_back(Triangle(utl, ltl, ltr));
	}

	/// <summary>
	/// Returns color of the box
	/// </summary>
	/// <returns></returns>
	Color getColor() override {
		return color;
	}

	/// <summary>
	/// Returns normal at intersection point
	/// </summary>
	/// <param name="intersection_point"></param>
	/// <returns></returns>
	Vec getNormalAt(Vec intersection_point) override
	{
		for (Triangle t : face_triangles) {
			if (t.isInside(intersection_point)) {
				return t.normal;
			}
		}
		return Vec(0, 0, 0);
	}

	/// <summary>
	/// Finds intersection distance for given ray
	/// </summary>
	/// <param name="ray">input ray</param>
	/// <returns>distance from ray origin</returns>
	double findIntersection(Ray ray) override {
		double min_dist = -1;

		for (int i = 0; i < face_triangles.size(); ++i)
		{
			double dist = face_triangles[i].findIntersection(ray);
			if (dist > 0) {
				if (min_dist == -1) {
					min_dist = dist;
				}
				else {
					min_dist = (min_dist > dist ? dist : min_dist);
				}
			}
		}
		return min_dist;
	}

};