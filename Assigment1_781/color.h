#pragma once

class Color {

public:
	double red, green, blue, alpha;

	Color(double x, double y, double z,double u) :red(x), green(y), blue(z),alpha(u) {}

	Color() :red(1.0), green(0.0), blue(0.0),alpha(1.0) {}

	Color(const Color& v) :red(v.red), green(v.green), blue(v.blue) ,alpha(v.alpha) {}

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

	Color colorAverage(Color color) {
		return Color((red + color.red) / 2, (green + color.green) / 2, (blue + color.blue) / 2, alpha);
	}

	void clip() {
		if (red > 1)  red = 1; 
		if (green > 1)  green = 1; 
		if (blue > 1)  blue = 1; 
		if (red < 0)  red = 0; 
		if (green < 0)  green = 0; 
		if (blue < 0)  blue = 0; 
	}
};

