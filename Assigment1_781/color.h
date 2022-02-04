#pragma once

#include <iostream>

// Color class for color which will be assigned to objects
// We thought of using alpha in initial design but we are not using alpha, it is just there
class Color {

public:
	double red, green, blue, alpha;

	// Constructors

	Color(double red, double green, double blue, double alpha) :red(red), green(green), blue(blue), alpha(alpha) {}

	Color() :red(0.0), green(0.0), blue(0.0), alpha(1.0) {}

	Color(const Color& v) :red(v.red), green(v.green), blue(v.blue), alpha(v.alpha) {}

	// Operator overloading for better code readability 

	Color operator +(Color const& obj) {
		Color res;
		res.red = red + obj.red;
		res.green = green + obj.green;
		res.blue = blue + obj.blue;
		res.alpha = alpha;
		return res;
	}
	Color& operator +=(Color const& obj) {
		this->red += obj.red;
		this->green += obj.green;
		this->blue += obj.blue;
		return *this;
	}
	Color operator *(Color const& obj) {
		Color res;
		res.red = red * obj.red;
		res.green = green * obj.green;
		res.blue = blue * obj.blue;
		res.alpha = alpha;
		return res;
	}
	Color& operator *=(Color const& obj) {
		this->red *= obj.red;
		this->green *= obj.green;
		this->blue *= obj.blue;
		return *this;
	}
	Color operator *(double const& obj) {
		Color res;
		res.red = red * obj;
		res.green = green * obj;
		res.blue = blue * obj;
		res.alpha = alpha;
		return res;
	}
	Color& operator *=(double const& obj) {
		this->red *= obj;
		this->green *= obj;
		this->blue *= obj;
		return *this;
	}

	/// <summary>
	/// In case any color value goes more than 1 or less than 0, we are clipping it to stay between 0 and 1
	/// </summary>
	void clip() {
		if (red > 1)  red = 1;
		if (green > 1)  green = 1;
		if (blue > 1)  blue = 1;
		if (red < 0)  red = 0;
		if (green < 0)  green = 0;
		if (blue < 0)  blue = 0;
	}

	/// <summary>
	/// Output operator overloaded
	/// </summary>
	/// <param name="os"></param>
	/// <param name="c"></param>
	/// <returns></returns>
	friend std::ostream& operator << (std::ostream& os, const Color& c) {
		os << "rgba: " << c.red << " " << c.blue << " " << c.green << " " << c.alpha;
		return os;
	}
};

