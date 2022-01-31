#include <iostream>
#include "Engine.h"

int main() {

	Ray r = getRefracted(Ray(Vec(1, 1, 0), Vec(-1, -1, 0)), Vec(0, -1, 0), Vec(0, 0, 0), 1, sqrt(2));

	std::cout << r.origin << "\ndirection: " << r.direction << "\n";

	return 0;
}