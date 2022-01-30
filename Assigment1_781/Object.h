#pragma once

#include "Ray.h"
#include "Vec.h"
#include "Color.h"

class Object {
public:
	Color color;
	Object() {}

	Color getColor() { return Color(0.0, 0.0, 0.0, 0); }

	Vec getNormalAt(Vec intersection_position) {
		return Vec(0, 0, 0);
	}

	double findIntersection(Ray ray) {
		return 0;
	}

};


