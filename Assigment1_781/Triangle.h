#pragma once

#include "math.h"
#include "Object.h"
#include "Vec.h"
#include "Color.h"

class Triangle : public Object
{

public:
	Vec A, B, C, normal;

	Triangle() :A(1, 0, 0), B(0, 1, 0), C(0, 0, 1) {
		Vec f = C - B;
		Vec s = A - B;
		normal = f.cross(s).normalize();
	}

	Triangle(Vec A1, Vec B1, Vec C1, Color col) : A(A1), B(B1), C(C1)
	{
		this->color = color;
		this->material = Material();
		Vec f = C - B;
		Vec s = A - B;
		normal = f.cross(s).normalize();
	}

	Triangle(Vec A1, Vec B1, Vec C1) : A(A1), B(B1), C(C1)
	{
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material();
		Vec f = C - B;
		Vec s = A - B;
		normal = f.cross(s).normalize();
	}

	Triangle(Vec A1, Vec B1, Vec C1, Color col, Material material) : A(A1), B(B1), C(C1)
	{
		this->color = color;
		this->material = material;
		Vec f = C - B;
		Vec s = A - B;
		normal = f.cross(s).normalize();
	}

	bool isInside(Vec point) {
		double area1 = ((point - B).cross(C - B)).magnitude();
		double area2 = ((point - C).cross(A - C)).magnitude();
		double area3 = ((point - A).cross(B - A)).magnitude();
		double total = ((A - B).cross(C - B)).magnitude();

		return (abs(total - area1 - area2 - area3) <= 0.001);
	}

	Vec getNormalAt(Vec intersection_point) override {
		if (isInside(intersection_point)) {
			return normal;
		}
		return Vec(0, 0, 0);
	}

	Color getColor() override {
		return color;
	}

	double findIntersection(Ray ray) override
	{
		Vec ray_direction = ray.direction;
		Vec ray_origin = ray.origin;
		double a = ray_direction.dot(normal);
		if (a == 0)
		{
			return -1;
		}
		else
		{
			Vec origin(0, 0, 0);
			double dist = (B - origin).dot(normal);

			Vec unormal = normal;

			if (((A * normal * -1).Sum() + dist) == 0) {
				unormal *= -1;
			}

			double t = -(unormal.dot(ray_origin) + dist) / unormal.dot(ray_direction);

			Vec point = ray_origin + ray_direction * t;

			if (isInside(point) && t > 0) {
				return (point - ray_origin).magnitude();
			}
			return -1;
		}
	}
};

