#pragma once

class Material {
public:

	double Ka, Kd, Ks, Krg, Ktg, refractive_index;
	int specular_exponent;

	Material():Ka(0),Kd(0),Ks(0),refractive_index(-1),specular_exponent(0),Krg(0),Ktg(0) {}

	Material(double Ka, double Kd, double Ks, double refractive_index,int specular_exponent, double Krg, double Ktg)
		:Ka(Ka),Kd(Kd),Ks(Ks),refractive_index(refractive_index), specular_exponent(specular_exponent), Krg(Krg), Ktg(Ktg)
	{}

};