#pragma once

#include "math.h"
#include <iostream>
#include <ostream>
#include <ostream>

class Vec {
public:
	double x, y, z;

	Vec(double x, double y, double z):x(x),y(y),z(z){}

	Vec():x(0.0),y(0.0),z(0.0){}

	Vec(const Vec &v):x(v.x),y(v.y),z(v.z){}

	double magnitude() {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vec normalize() {
		double magnitude = sqrt((x * x) + (y * y) + (z * z));
		return Vec(x / magnitude, y / magnitude, z / magnitude);
	}

	Vec negative() {
		return Vec(-x, -y, -z);
	}
	
	Vec operator +(Vec const& obj) {
		Vec res;
		res.x = x + obj.x;
		res.y = y + obj.y;
		res.z = z + obj.z;
		return res;
	}
	Vec& operator +=(Vec const& obj) {
		this->x += obj.x;
		this->y += obj.y;
		this->z += obj.z;
		return *this;
	}
	Vec& operator -=(Vec const& obj) {
		this->x -= obj.x;
		this->y -= obj.y;
		this->z -= obj.z;
		return *this;
	}

	Vec& operator *=(Vec const& obj) {
		this->x *= obj.x;
		this->y *= obj.y;
		this->z *= obj.z;
		return *this;
	}
	Vec& operator -=(double const& d) {
		this->x -= d;
		this->y -= d;
		this->z -= d;
		return *this;
	}
	Vec& operator *=(double const& d) {
		this->x *= d;
		this->y *= d;
		this->z *= d;
		return *this;
	}
	Vec& operator +=(double const& d) {
		this->x += d;
		this->y += d;
		this->z += d;
		return *this;
	}

	Vec operator -(Vec const& obj) {
		Vec res;
		res.x = x - obj.x;
		res.y = y - obj.y;
		res.z = z - obj.z;
		return res;
	}
	Vec operator *(double const& obj) {
		Vec res;
		res.x = x * obj;
		res.y = y * obj;
		res.z = z * obj;
		return res;
	}

	Vec cross(Vec const& obj) {
		Vec res;
		res.x = y * obj.z - z * obj.y;
		res.y = -(x * obj.z - z * obj.x);
		res.z = x * obj.y - y * obj.x;
		return res;
	}
	double dot(Vec const& obj) {
		double ans = 0;
		ans += (x * obj.x);
		ans += (y * obj.y);
		ans += (z * obj.z);
		return ans;
	}
	
	friend std::ostream& operator << (std::ostream & os, const Vec & v){
		os << v.x << " " << v.y << " " << v.z << "\n";
		return os;
	}
};

