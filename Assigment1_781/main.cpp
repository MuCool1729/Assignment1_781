#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include "Engine.h"

int main() {

	Vec centre(5, 0, 0);
	double radius = 2;	
	Color scolor(0.2, 0.8, 0.5, 1.0);
	Material smaterial(0.5, 0.2, 0.3, -1, 3, 0.2, 0.2);

	Sphere* sphere = new Sphere(centre, radius, scolor, smaterial);

	models.push_back(sphere);

	Light l1(Vec(0, 2, 0), Color(1, 1, 1, 1));

	lights.push_back(l1);

	camera_position = Vec(0, 0, 0);
	camera_lookat = Vec(1, 0, 0);

	std::vector<std::vector<Color>> image = getImageMat(200, 150, Color(1, 1, 1, 0.3));

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			double r, b, g;

			r = image[i][j].red;
			b = image[i][j].blue;
			g = image[i][j].green;

			if (r + b + g > 0) {
				std::cout << "<" << i + 1 << ", " << j + 1 << "> " << image[i][j] << "\n";
			}
		}
	}

	return 0;
}