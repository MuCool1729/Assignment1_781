#pragma once

#include "Vec.h"
#include "Color.h"

// Light at given position with color
class Light {
public:
	Vec pos;
	Color color;

	Light():pos(0,0,0),color(1,1,1,1){}

	Light(Vec pos, Color color):pos(pos),color(color){}

	Light(Vec pos):pos(pos),color(1,1,1,1){}

};