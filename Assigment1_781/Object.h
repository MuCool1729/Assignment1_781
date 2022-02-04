#pragma once

#include "Ray.h"
#include "Vec.h"
#include "Color.h"
#include "Material.h"

// Parent class of all objects(like box)
class Object {
public:

	Color color;
	Material material;

	Object(Color color):color(color) {}

	Object() {
		color.red = 0.0;
		color.blue = 0.0;
		color.green = 0.0;
		color.alpha = 1.0;
	}

	virtual Color getColor() = 0;

	virtual Vec getNormalAt(Vec intersection_position) = 0;

	virtual double findIntersection(Ray ray) = 0;
};


