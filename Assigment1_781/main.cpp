#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <GLFW/glfw3.h>

#include "Engine.h"

int main(int argc, char** argv) {

	// Take input from arguments
	/*if (argc < 2) {
		std::cerr << "Please provide an input file location.";
		std::cerr << "\n Use: .\\a.exe <input_file_path>" << std::endl;
		return -1;
	}

	std::string input_file_name = std::string(argv[1]);*/

	// Get data
	int width, height, num_samples;
	Color ambient_color;
	get_data("../input/input_standard.json", width, height, ambient_color, num_samples);
	
	std::vector<std::vector<Color>> image = getImageMat(width, height, ambient_color, num_samples);

	// Put the data in 1D array to be displayed using OpenGL
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

	// Initialize GLFW and create a window
	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, "Assignment 1", NULL, NULL);

	if (!window) {
		return -1;
	}

	// Make window as current context
	glfwMakeContextCurrent(window);

	// Render the image we got
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data_);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	uint8_t* img = new uint8_t[width * height * 3];

	int ind = 0;

	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			img[ind++] = static_cast<int>(image[j][i].red * 255.99);
			img[ind++] = static_cast<int>(image[j][i].green * 255.99);
			img[ind++] = static_cast<int>(image[j][i].blue * 255.99);
		}
	}

	stbi_write_png("rendered_033.png", width, height, 3, img, width * 3);

	glfwTerminate();

	return 0;
}