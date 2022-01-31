#pragma once

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

#pragma endregion

Vec camera_position, camera_lookat;

Vec origin(0, 0, 0);
Vec world_up(0, 1, 0);
std::vector<Object> models;
std::vector<Light> lights;
const double accuracy = 0.0001;
const int MAX_DEPTH = 4;

Ray getReflected(Ray incident, Vec normal, Vec intersection_point) {

	Vec reflected_dir = incident.direction - normal * 2 * (incident.direction.dot(normal.normalize()));

	return Ray(intersection_point, reflected_dir.normalize());
}

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

double get_random_double() {
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::mt19937 generator;
	return dist(generator);
}

Color traceRay(Ray r, double ambient_light, double refractive_index, int depth) {

	// Closest

	std::vector<double> intersection_distance;
	int closest_index = -1;

	for (int i = 0; i < models.size(); i++)
	{
		intersection_distance.push_back(models[i].findIntersection(r));
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

	if (closest_index == -1) {
		return Color(0, 0, 0, 1);
	}

	// Normal

	Vec intersection_point = r.origin + r.direction.normalize() * intersection_distance[closest_index];
	Vec normal = models[closest_index].getNormalAt(intersection_point);

	if (normal == Vec(0, 0, 0)) {
		return Color(0, 0, 0, 1);
	}

	// Lights

	std::vector<Light> interfering_lights;

	for (int i = 0; i < lights.size(); i++)
	{
		Ray shadow_ray(intersection_point, lights[i].pos - intersection_point);

		double shadow_ray_length = (lights[i].pos - intersection_point).magnitude();

		bool is_shadowed = false;

		for (int j = 0; j < models.size(); j++)
		{
			double dist = models[j].findIntersection(shadow_ray);
			if (dist < shadow_ray_length) {
				is_shadowed = true;
			}
		}

		if (!is_shadowed) {
			interfering_lights.push_back(lights[i]);
		}
	}

	// Reflections and Refractions

	// Phong model

}

std::vector<std::vector<Color>> getImageMat(int width, int height, double ambient_light, int num_samples = 16) {

	Vec cam_pos(camera_position);
	Vec look_at(camera_lookat);

	Vec a = (cam_pos - look_at).normalize();
	Vec camera_direction = (a * -1).normalize();
	Vec camera_right = world_up.cross(a).normalize();
	Vec camera_up = a.cross(camera_right).normalize();

	Vec lower_left_corner = cam_pos - camera_right * 0.5 * width - camera_up * 0.5 * height - a;

	std::vector<std::vector<Color>> ret(width, std::vector<Color>(height));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Color color(0, 0, 0, 1);
			for (int k = 0; k < num_samples; ++k)
			{
				double u = (i + get_random_double()) / (width);
				double v = (j + get_random_double()) / (height);
				// ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
				//origin = lookfrom;
				//horizontal = viewport_width * u(camera right);
				//vertical = viewport_height * v;

				Ray r(cam_pos, lower_left_corner + camera_right * u * width + camera_up * v * height - cam_pos);

				Color ret_color = traceRay(r, ambient_light, 1, 3);
				color += ret_color;
			}

			color = color * (1 / num_samples);
			ret[i][j] = color;
		}
	}

	return ret;

}
