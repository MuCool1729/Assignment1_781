#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <GLFW/glfw3.h>

#include "Engine.h"

int main() {

	int width, height;
	Color ambient_color;
	get_data("B:/IITD/Sem8/COL781/Assignment 1/input/input.json", width, height, ambient_color);
	
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

	glfwInit();


	return 0;
}