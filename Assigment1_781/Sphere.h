#pragma once

#include "Vec.h"
#include "Object.h"
#include "Color.h"

class Sphere : public Object
{
public:

	Vec centre;
	double radius;

	Sphere() :centre(0.0, 0.0, 0.0), radius(1.0) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material();
	}

	Sphere(Vec centre, double radius, Color color) :centre(centre), radius(radius) {
		this->color = color;
		this->material = Material();
	}

	Sphere(Vec centre, double radius) :centre(centre), radius(radius) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material(); 
	}

	Sphere(Vec centre, double radius, Color color, Material material) :centre(centre), radius(radius) {
		this->color = color;
		this->material = material;
	}

	bool isOnSurface(Vec point) {
		double distance = ((centre - point) * (centre - point)).Sum();
		distance = sqrt(distance);
		return (abs(distance - radius) <= 0.001);
	}

	Color getColor() override{
		return color;
	}

	Vec getNormalAt(Vec intersection_point) override {
		Vec ret(0, 0, 0);
		if (isOnSurface(intersection_point)) {
			ret = intersection_point - centre;
			ret.normalize();
		}
		return ret;
	}

	double findIntersection(Ray ray) override {
		Vec ray_origin = ray.origin;
		Vec ray_direction = ray.direction.normalize();

		double a = 1.0;
		double b = 2 * (ray_direction.x * (ray_origin.x - centre.x) +
			ray_direction.y * (ray_origin.y - centre.y) +
			ray_direction.z * (ray_origin.z - centre.z));
		double c = pow(ray_origin.x - centre.x, 2) + pow(ray_origin.y - centre.y, 2) +
			pow(ray_origin.z - centre.z, 2) - pow(radius, 2);

		double discriminant = pow(b, 2) - 4 * a * c;

		if (discriminant < 0) {
			return -1;
		}
		else {
			double first_root = (-b + sqrt(discriminant)) / (2 * a);
			double second_root = (-b - sqrt(discriminant)) / (2 * a);


			if (second_root >= 0) {
				return second_root;
			}
			if (first_root >= 0) {
				return first_root;
			}
			return -1;
		}
	}
};