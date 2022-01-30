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
	}

	Sphere(Vec centre, double radius, Color color) :centre(centre), radius(radius) {
		this->color = color;
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

	}
};