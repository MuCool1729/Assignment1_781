#include <iostream>
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include "Engine.h"

int main() {

	Vec centre(45, 0, 0);
	double radius = 42;	
	Color scolor(1, 0, 0, 1.0);
	Material smaterial(0.5, 0.4, 0, -1, 4, 0, 0);

	Sphere* sphere = new Sphere(centre, radius, scolor, smaterial);

	Vec centre2(100, 200, 100);
	double radius2 = 42;
	Color scolor2(0, 1, 0, 1.0);
	Material smaterial2(0.6, 0.8, 0, -1, 8, 0, 0);

	Sphere* sphere2 = new Sphere(centre2, radius2, scolor2, smaterial2);

	models.push_back(sphere);
	models.push_back(sphere2);

	Light l1(Vec(0, 2, 0), Color(1, 1, 1, 1));

	lights.push_back(l1);

	camera_position = Vec(-400, 200, 0);
	camera_lookat = Vec(0, 200, 0);

	int width = 800, height = 600;

	std::vector<std::vector<Color>> image = getImageMat(width, height, Color(1, 1, 1, 0.3));

	uint8_t* img = new uint8_t[width * height * 3];

	int ind = 0;

	for (int i = height-1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			img[ind++] = static_cast<int>(image[j][i].red * 255.99);
			img[ind++] = static_cast<int>(image[j][i].green * 255.99);
			img[ind++] = static_cast<int>(image[j][i].blue * 255.99);
		}
	}

	stbi_write_png("rendered10.png", width, height, 3, img, width * 3);

	return 0;
}