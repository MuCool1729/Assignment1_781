#pragma once

#include "Vec.h"
#include "Object.h"
#include "Color.h"

// Sphere object with radius and centre
class Sphere : public Object
{
public:

	Vec centre;
	double radius;

	// Constructors

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

	/// <summary>
	/// Check whether the point is on surface or not
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	bool isOnSurface(Vec point) {
		double distance = ((centre - point) * (centre - point)).Sum();
		distance = sqrt(distance);
		return (abs(distance - radius) <= 0.001);
	}

	/// <summary>
	/// Returns color of the sphere
	/// </summary>
	/// <returns></returns>
	Color getColor() override{
		return color;
	}

	/// <summary>
	/// Returns normal at the given point
	/// </summary>
	/// <param name="intersection_point"></param>
	/// <returns></returns>
	Vec getNormalAt(Vec intersection_point) override {
		Vec ret(0, 0, 0);
		if (isOnSurface(intersection_point)) {
			ret = intersection_point - centre;
			ret.normalize();
		}
		return ret;
	}

	/// <summary>
	/// Returns distance of sphere from ray origin(if not intersecting return -1)
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
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