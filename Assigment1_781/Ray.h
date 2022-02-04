#pragma once

#include "vec.h"

// Ray with origin and direction
class Ray {
public:

	Vec origin, direction;

	Ray() :origin(0, 0, 0), direction(0, 0, 0) {}

	Ray(Vec origin, Vec direction) :origin(origin), direction(direction.normalize()) {}

	Ray(const Ray& r) :origin(r.origin), direction(r.direction) {}

};