#pragma once

#include "Vec.h"
#include "Object.h"

class Quadric : public Object
{
public:
	double A, B, C, D, E, F, G, H, I, J;

	Quadric() :A(0), B(0), C(0), D(0), E(0), F(0), G(0), H(0), I(0), J(0) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material();
	}

	Quadric(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j) :
		A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j) {
		this->color = Color(1.0, 1.0, 1.0, 1.0);
		this->material = Material();
	}

	Quadric(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, Color color) :
		A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j) {
		this->color = color;
		this->material = Material();
	}

	Quadric(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, Color color, Material material) :
		A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j) {
		this->color = color;
		this->material = material;
	}

	// Q(x,y,z) = Ax2 + By2 + Cz2 + Dxy+ Exz + Fyz + Gx + Hy + Iz + J 

	Vec getNormalAt(Vec intersection_point) override
	{
		double xn, yn, zn, xi, yi, zi;
		xi = intersection_point.x;
		yi = intersection_point.y;
		zi = intersection_point.z;
		xn = (2 * A * xi) + (D * yi) + (E * zi) + G;
		yn = (2 * B * yi) + (D * xi) + (F * zi) + H;
		zn = (2 * C * zi) + (E * xi) + (F * yi) + I;
		return Vec(xn, yn, zn).normalize();
	}

	Color getColor() override {
		return color;
	}

	double findIntersection(Ray ray) override
	{
		double a, b, c, xo, yo, zo, xd, yd, zd;

		Vec ray_origin = ray.origin;
		Vec ray_direction = ray.direction.normalize();

		xo = ray_origin.x;
		yo = ray_origin.y;
		zo = ray_origin.z;
		xd = ray_direction.x;
		yd = ray_direction.y;
		zd = ray_direction.z;

		a = (A * pow(xd, 2)) + (B * pow(yd, 2)) + (C * pow(zd, 2)) +
			(D * xd * yd) + (E * xd * zd) + (F * yd * zd);
		b = 2 * ((A * xo * xd) + (B * yo * yd) + (C * zo * zd))
			+ (D * ((xo * yd) + (yo * xd))) + (E * ((xo * zd) + (zo * xd))) + (F * ((yo * zd) + (yd * zo)))
			+ (G * xd) + (H * yd) + (I * zd);
		c = (A * pow(xo, 2)) + (B * pow(yo, 2)) + (C * pow(zo, 2))
			+ (D * xo * yo) + (E * xo * zo) + (F * yo * zo)
			+ (G * xo) + (H * yo) + (I * zo) + J;

		if (a != 0)
		{
			double discriminant = (b * b) - (4 * a * c);
			if (discriminant < 0)
			{
				return -1;
			}
			else
			{
				double first_root = (double)(-b + sqrt(discriminant)) / (2 * a);
				double second_root = (double)(-b - sqrt(discriminant)) / (2 * a);

				if (first_root >= 0 && second_root >= 0) {
					return (first_root > second_root ? second_root : first_root);
				}
				else if (first_root >= 0)
					return first_root;
				else if (second_root >= 0)
					return second_root;

				return -1;
			}
		}
		else if (a == 0)
		{
			if (b != 0)
				return (-c / b);
			else
				return -1;
		}
	}

};