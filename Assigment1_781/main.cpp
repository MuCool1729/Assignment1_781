#include <iostream>
#include "vec.h"
#include "Triangle.h"
#include "Sphere.h"

int main() {

	Vec centre(2, 0, 0);
	Ray ray(Vec(0, 1, 0), Vec(-1, 0, 0));

	Sphere s(centre, 1.0);

	std::cout << s.findIntersection(ray) << "\n";

	return 0;
}