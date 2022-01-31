#include <iostream>
#include "Box.h"

int main() {

	Ray ray(Vec(0, 1, 0), Vec(1, 0, 0));

	Box bx(Vec(3, 0, 0), 3, 3, 3, Vec(1, 0, 0), Vec(0, 1, 0));

	std::cout << bx.findIntersection(ray) << "\n";

	return 0;
}