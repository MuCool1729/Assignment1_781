#pragma once
#include "Object.h"
#include "Triangle.h"
#include <vector>

class Box : public Object
{
public:

	double l, b, h;
	Vec centre, vx, vy, vz;
	std::vector<Triangle> face_triangles;

	Box() :centre(0, 0, 0), l(1), b(1), h(1), vx(1, 0, 0), vy(0, 1, 0) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		vz = Vec(0, 0, 1);
		addFaces();
	}

	Box(Vec centre, double l, double b, double h, Vec vx, Vec vy) : centre(centre), l(l), b(b), h(h), vx(vx.normalize()), vy(vy.normalize()) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		vz = vx.cross(vy).normalize();
		addFaces();
	}

	Box(Vec centre, double l, double b, double h, Vec vx, Vec vy, Color color) : centre(centre), l(l), b(b), h(h), vx(vx.normalize()), vy(vy.normalize()) {
		this->color = color;
		vz = vx.cross(vy).normalize();
		addFaces();
	}

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

	Color getColor() override {
		return color;
	}

	Vec getNormalAt(Vec intersection_point) override
	{
		for (Triangle t : face_triangles) {
			if (t.isInside(intersection_point)) {
				return t.normal;
			}
		}
		return Vec(0, 0, 0);
	}

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