﻿#pragma once

#pragma region Required libraries

#include <random>
#include "Box.h"
#include "Color.h"
#include "Light.h"
#include "Material.h"
#include "Object.h"
#include "Quadric.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vec.h"
#include <string>
#include <fstream>
#include <json.hpp>

#pragma endregion

using json = nlohmann::json;

// Using global variables to store camera position and the point where camera is pointing to
Vec camera_position, camera_lookat;
// World origin and up vector
Vec origin(0, 0, 0);
Vec world_up(0, 1, 0);
// List of objects and light sources in the scene
std::vector<Object*> models;
std::vector<Light> lights;
// accuracy for avoiding same object intersection in recursive tracing
const double accuracy = 0.0001;
// Max depth upto which recursive ray tracing should be done
int MAX_DEPTH = 3;

/// <summary>
/// Reads input from JSON file
/// </summary>
/// <param name="filename"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="ambient_light"></param>
/// <param name="num_samples"></param>
void get_data(std::string filename, int& width, int& height, Color& ambient_light, int& num_samples) {
	std::ifstream input_file(filename);

	if (!input_file) {
		std::cerr << "Error in opening file at " << filename << "\n";
		return;
	}

	json j_if = json::parse(input_file);

	width = (int)j_if["width"];
	height = (int)j_if["height"];
	MAX_DEPTH = (int)j_if["max_depth"];
	num_samples = (int)j_if["num_samples"];

	camera_position = Vec((double)j_if["camera"]["position"][0], (double)j_if["camera"]["position"][1],
		(double)j_if["camera"]["position"][2]);

	camera_lookat = Vec((double)j_if["camera"]["look_at"][0], (double)j_if["camera"]["look_at"][1],
		(double)j_if["camera"]["look_at"][2]);

	for (auto& i : j_if["lights"].items()) {
		Vec position((double)i.value()["position"][0], (double)i.value()["position"][1], (double)i.value()["position"][2]);
		Color light_color((double)i.value()["color"][0], (double)i.value()["color"][1],
			(double)i.value()["color"][2], (double)i.value()["color"][3]);

		Light light(position, light_color);
		lights.push_back(light);
	}

	ambient_light = Color((double)j_if["ambient_light"][0], (double)j_if["ambient_light"][1],
		(double)j_if["ambient_light"][2], (double)j_if["ambient_light"][3]);

	for (auto& i : j_if["scene"].items()) {
		for (auto& j : i.value().items()) {
			if (j.key() == "Triangle") {
				Vec A((double)j.value()["A"][0], (double)j.value()["A"][1], (double)j.value()["A"][2]);
				Vec B((double)j.value()["B"][0], (double)j.value()["B"][1], (double)j.value()["B"][2]);
				Vec C((double)j.value()["C"][0], (double)j.value()["C"][1], (double)j.value()["C"][2]);

				Color color((double)j.value()["color"][0], (double)j.value()["color"][1],
					(double)j.value()["color"][2], (double)j.value()["color"][3]);

				Material material((double)j.value()["material"]["Ka"], (double)j.value()["material"]["Kd"],
					(double)j.value()["material"]["Ks"], (double)j.value()["material"]["refractive_index"],
					(int)j.value()["material"]["specular_exponent"], (double)j.value()["material"]["Krg"],
					(double)j.value()["material"]["Ktg"]);

				Triangle* t = new Triangle(A, B, C, color, material);
				models.push_back(t);
			}
			if (j.key() == "Sphere") {

				Vec centre((double)j.value()["centre"][0], (double)j.value()["centre"][1], (double)j.value()["centre"][2]);
				double radius = (double)j.value()["radius"];

				Color color((double)j.value()["color"][0], (double)j.value()["color"][1],
					(double)j.value()["color"][2], (double)j.value()["color"][3]);

				Material material((double)j.value()["material"]["Ka"], (double)j.value()["material"]["Kd"],
					(double)j.value()["material"]["Ks"], (double)j.value()["material"]["refractive_index"],
					(int)j.value()["material"]["specular_exponent"], (double)j.value()["material"]["Krg"],
					(double)j.value()["material"]["Ktg"]);

				Sphere* s = new Sphere(centre, radius, color, material);
				models.push_back(s);
			}
			if (j.key() == "Quadric") {

				double A = j.value()["A"];
				double B = j.value()["B"];
				double C = j.value()["C"];
				double D = j.value()["D"];
				double E = j.value()["E"];
				double F = j.value()["F"];
				double G = j.value()["G"];
				double H = j.value()["H"];
				double I = j.value()["I"];
				double J = j.value()["J"];

				Color color((double)j.value()["color"][0], (double)j.value()["color"][1],
					(double)j.value()["color"][2], (double)j.value()["color"][3]);

				Material material((double)j.value()["material"]["Ka"], (double)j.value()["material"]["Kd"],
					(double)j.value()["material"]["Ks"], (double)j.value()["material"]["refractive_index"],
					(int)j.value()["material"]["specular_exponent"], (double)j.value()["material"]["Krg"],
					(double)j.value()["material"]["Ktg"]);

				Quadric* q = new Quadric(A, B, C, D, E, F, G, H, I, J, color, material);
				models.push_back(q);
			}
			if (j.key() == "Box") {

				Vec centre((double)j.value()["centre"][0], (double)j.value()["centre"][1], (double)j.value()["centre"][2]);
				double l = (double)j.value()["l"];
				double b = (double)j.value()["b"];
				double h = (double)j.value()["h"];
				Vec vx((double)j.value()["vx"][0], (double)j.value()["vx"][1], (double)j.value()["vx"][2]);
				Vec vy((double)j.value()["vy"][0], (double)j.value()["vy"][1], (double)j.value()["vy"][2]);

				Color color((double)j.value()["color"][0], (double)j.value()["color"][1],
					(double)j.value()["color"][2], (double)j.value()["color"][3]);

				Material material((double)j.value()["material"]["Ka"], (double)j.value()["material"]["Kd"],
					(double)j.value()["material"]["Ks"], (double)j.value()["material"]["refractive_index"],
					(int)j.value()["material"]["specular_exponent"], (double)j.value()["material"]["Krg"],
					(double)j.value()["material"]["Ktg"]);

				Box* bx = new Box(centre, l, b, h, vx, vy, color, material);
				models.push_back(bx);
			}
		}
	}
}

/// <summary>
/// Returns reflected ray
/// </summary>
/// <param name="incident"></param>
/// <param name="normal"></param>
/// <param name="intersection_point"></param>
/// <returns></returns>
Ray getReflected(Ray incident, Vec normal, Vec intersection_point) {

	Vec reflected_dir = incident.direction - normal * 2 * (incident.direction.dot(normal.normalize()));

	return Ray(intersection_point, reflected_dir.normalize());
}

/// <summary>
/// Returns refracted ray
/// </summary>
/// <param name="incident"></param>
/// <param name="normal"></param>
/// <param name="intersection_point"></param>
/// <param name="incident_ri"></param>
/// <param name="transmit_ri"></param>
/// <returns></returns>
Ray getRefracted(Ray incident, Vec normal, Vec intersection_point, double incident_ri, double transmit_ri) {

	double cos_theta_i = normal.normalize().dot(incident.direction.normalize());

	bool isInside = cos_theta_i > 0;

	double abs_cos_theta_i = abs(cos_theta_i);
	double abs_sin_theta_i = sqrt(1 - (abs_cos_theta_i * abs_cos_theta_i));

	double ref_ind_ratio = incident_ri / transmit_ri;

	double sin_theta_t = (ref_ind_ratio * abs_sin_theta_i);
	double cos_theta_t = sqrt(1 - (sin_theta_t * sin_theta_t));

	Vec real_normal = isInside ? (normal * -1) : (normal);

	Vec refracted_dir =
		(((incident.direction + real_normal * abs_cos_theta_i)) * ref_ind_ratio -
			(real_normal * cos_theta_t)).normalize();

	return Ray(intersection_point, refracted_dir);
}

/// <summary>
/// Generates random double between [0,1]
/// </summary>
/// <returns></returns>
double get_random_double() {
	std::random_device rd;
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::mt19937 generator(rd());
	return dist(generator);
}

/// <summary>
/// Returns value of color at given point using phong illumination model
/// </summary>
/// <param name="intersection_point"></param>
/// <param name="viewing_direction"></param>
/// <param name="normal"></param>
/// <param name="interfering_lights"></param>
/// <param name="ambient_light"></param>
/// <param name="reflected_color"></param>
/// <param name="refracted_color"></param>
/// <param name="model_material"></param>
/// <returns></returns>
Color phongModel(Vec intersection_point, Vec viewing_direction, Vec normal, std::vector<Light> interfering_lights,
	Color ambient_light, Color reflected_color, Color refracted_color, Material model_material) {

	// Flip the normal if not in same direction
	if (viewing_direction.dot(normal) < 0) {
		normal = normal * -1;
	}

	normal = normal.normalize();

	Color ret(0, 0, 0, 1);

	for (int i = 0; i < interfering_lights.size(); i++)
	{
		Color light_color = interfering_lights[i].color;
		Vec incident_ray = interfering_lights[i].pos - intersection_point;

		// If any light is falling directly or not
		double cos_theta = incident_ray.normalize().dot(normal);
		if (cos_theta < 0) {
			continue;
		}

		Vec reflected_ray = normal * 2 * cos_theta - incident_ray.normalize();

		ret += light_color * model_material.Kd * cos_theta;

		// Check for specular
		double cos_alpha = reflected_ray.normalize().dot(viewing_direction.normalize());
		if (cos_alpha > 0) {
			ret += light_color * model_material.Ks * pow(cos_alpha, model_material.specular_exponent);
		}
	}

	ret += ambient_light * model_material.Ka;

	ret += reflected_color * model_material.Krg;

	ret += refracted_color * model_material.Ktg;

	ret.clip();

	return ret;
}

/// <summary>
/// Traces the given ray
/// </summary>
/// <param name="r"></param>
/// <param name="ambient_light"></param>
/// <param name="refractive_index">Refractive index of the model where ray is travelling</param>
/// <param name="depth">Ray tracing tree depth</param>
/// <returns></returns>
Color traceRay(Ray r, Color ambient_light, double refractive_index, int depth) {

	// Finding closest object

	std::vector<double> intersection_distance;
	int closest_index = -1;

	for (int i = 0; i < models.size(); i++)
	{
		intersection_distance.push_back(models[i]->findIntersection(r));

		if (intersection_distance[i] > accuracy)
		{
			if (closest_index == -1)
			{
				closest_index = i;
			}
			else if (intersection_distance[closest_index] > intersection_distance[i])
			{
				closest_index = i;
			}
		}
	}

	// If not found return black
	if (closest_index == -1) {
		return Color(0, 0, 0, 1);
	}

	// Normal at intersection point

	Vec intersection_point = r.origin + r.direction.normalize() * intersection_distance[closest_index];
	Vec normal = models[closest_index]->getNormalAt(intersection_point);

	// Some glitch may be
	if (normal == Vec(0, 0, 0)) {
		return Color(0, 0, 0, 1);
	}

	// Checking the interfering lights at the intersection point

	std::vector<Light> interfering_lights;

	for (int i = 0; i < lights.size(); i++)
	{
		Ray shadow_ray(intersection_point, lights[i].pos - intersection_point);

		double shadow_ray_length = (lights[i].pos - intersection_point).magnitude();

		bool is_shadowed = false;

		for (int j = 0; j < models.size(); j++)
		{
			double dist = models[j]->findIntersection(shadow_ray);
			if (dist < shadow_ray_length && dist > accuracy) {
				is_shadowed = true;
			}
		}

		if (!is_shadowed) {
			interfering_lights.push_back(lights[i]);
		}
	}
	
	// Checking Reflections and Refractions

	Color reflected_color(0, 0, 0, 1), refracted_color(0, 0, 0, 1);

	if (depth < MAX_DEPTH) {

		Ray reflected_ray = getReflected(r, normal, intersection_point);

		reflected_color = traceRay(reflected_ray, ambient_light, refractive_index, depth + 1);

		double model_ri = models[closest_index]->material.refractive_index;

		if (model_ri > 0) {
			Ray refracted_ray;
			if (refractive_index == model_ri) {
				refracted_ray = getRefracted(r, normal, intersection_point, model_ri, 1);
				refracted_color = traceRay(refracted_ray, ambient_light, 1, depth + 1);
			}
			else {
				refracted_ray = getRefracted(r, normal, intersection_point, refractive_index, model_ri);
				refracted_color = traceRay(refracted_ray, ambient_light, model_ri, depth + 1);
			}
		}
	}

	// Phong model call

	Color final_color = phongModel(intersection_point, r.direction * -1, normal, interfering_lights, ambient_light,
		reflected_color, refracted_color, models[closest_index]->material);


	final_color = final_color * models[closest_index]->color;

	final_color.clip();


	return final_color;
}

/// <summary>
/// To calculate matrix of color values for the window
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="ambient_light"></param>
/// <param name="num_samples"></param>
/// <returns>Matrix of colors for window</returns>
std::vector<std::vector<Color>> getImageMat(int width, int height, Color ambient_light, int num_samples = 16) {

	Vec cam_pos(camera_position);
	Vec look_at(camera_lookat);

	Vec a = (cam_pos - look_at);
	Vec camera_direction = (a * -1).normalize();
	Vec camera_right = world_up.cross(a).normalize();
	Vec camera_up = a.cross(camera_right).normalize();

	// Finding lower left corner of the camera in world co-ordinate system
	Vec lower_left_corner = cam_pos - camera_right * 0.5 * width - camera_up * 0.5 * height - a;

	std::vector<std::vector<Color>> ret(width, std::vector<Color>(height));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			// Calculate num_samples samples for given pixel and average it out to get color at that pixel
			// Super sampling for Anti-aliasing
			Color color(0, 0, 0, 1);
			for (int k = 0; k < num_samples; ++k)
			{
				double u = (i + get_random_double()) / (width - 1);
				double v = (j + get_random_double()) / (height - 1);

				Ray r(cam_pos, lower_left_corner + camera_right * u * width + camera_up * v * height - cam_pos);

				Color ret_color = traceRay(r, ambient_light, 1, 0);
				color += ret_color;

			}

			color = color * (1 / (double)num_samples);
			ret[i][j] = color;
		}
		// Priting the progress
		if (i % 20 == 0) {
			std::cout << "Completed " << i << std::endl;
		}
	}

	return ret;

}
