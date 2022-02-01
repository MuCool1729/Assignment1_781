#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include "Engine.h"

int main() {

	Vec centre(5, 0, 0);
	double radius = 3;	
	Color scolor(0.2, 0.8, 0.5, 1.0);
	Material smaterial(0.5, 0.2, 0.3, -1, 3, 0.2, 0.2);

	Sphere* sphere = new Sphere(centre, radius, scolor, smaterial);

	models.push_back(sphere);

	Light l1(Vec(0, 2, 0), Color(1, 1, 1, 1));

	lights.push_back(l1);

	camera_position = Vec(-15, 0, 0);
	camera_lookat = Vec(1, 0, 0);

	std::vector<std::vector<Color>> image = getImageMat(10, 10, Color(1, 1, 1, 0.3));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << "<" << i + 1 << ", " << j + 1 << "> " << image[i][j] << "\n";
		}
	}

	return 0;
}