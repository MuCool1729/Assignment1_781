#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "Engine.h"
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

int main() {

	std::ifstream input_file("B:/IITD/Sem8/COL781/Assignment 1/input/input.json");

	json j_if = json::parse(input_file);

	int width = (int)j_if["width"];
	int height = (int)j_if["height"];

	Color ambient_light = Color((double)j_if["ambient_light"][0], (double)j_if["ambient_light"][1],
		(double)j_if["ambient_light"][2], (double)j_if["ambient_light"][3]);

	camera_position = Vec((double)j_if["camera"]["position"][0], (double)j_if["camera"]["position"][1],
		(double)j_if["camera"]["position"][2]);

	camera_lookat = Vec((double)j_if["camera"]["look_at"][0], (double)j_if["camera"]["look_at"][1],
		(double)j_if["camera"]["look_at"][2]);
	
	/*int width = 800, height = 600;

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

	stbi_write_png("rendered10.png", width, height, 3, img, width * 3);*/



	return 0;
}