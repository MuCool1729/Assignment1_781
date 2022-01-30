#include <iostream>
#include "vec.h"
#include "Triangle.h"


int main() {

	Vec a(0, 0, 1), b(0, 1, 0),c(1, 0, 0);
	Vec orig(0, 0, 0), direction(1, 1, 1);
	Triangle tr(a, b, c);
	Ray ray(orig, direction);
	std::cout << tr.findIntersection(ray) << std::endl;

	std::cout << tr.getColor() << "\n";

	return 0;
}