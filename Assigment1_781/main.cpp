#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <GLFW/glfw3.h>

#include "Engine.h"

int main() {

	int width, height;
	Color ambient_color;
	get_data("../input/input.json", width, height, ambient_color);
	
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
	
	std::vector<std::vector<Color>> image = getImageMat(width, height, ambient_color, 4);

	unsigned char* data_ = new unsigned char[width * height * 3];

	int id = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data_[id++] = image[j][i].red * 255.59;
			data_[id++] = image[j][i].green * 255.59;
			data_[id++] = image[j][i].blue * 255.59;
		}
	}

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, "Assignment 1", NULL, NULL);

	if (!window) {
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data_);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}