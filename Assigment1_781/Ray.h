#pragma once

#include "vec.h"

class Ray {
public:
	
	Vec origin, direction;

	Ray(Vec origin, Vec direction):origin(origin),direction(direction){}

	Ray(const Ray& r):origin(r.origin),direction(r.direction){}

};