
#include "math.h"
#include "Object.h"
#include "Vec.h"
#include "Color.h"

class Triangle : public Object
{

public:
	Vec A, B, C, normal;
	Color color;
	Triangle(Vec A1, Vec B1, Vec C1, Color col) : A(A1), B(B1), C(C1), color(col)
	{
		Vec f = C - B;
		Vec s = A - B;
		normal = f.cross(s).normalize();
	}
	Triangle(Vec A1, Vec B1, Vec C1) : A(A1), B(B1), C(C1), color()
	{
		Vec f = C - B;
		Vec s = A - B;
		normal = f.cross(s).normalize();
	}
	double findIntersection(Ray ray)
	{
		Vec ray_direction = ray.direction;
		Vec ray_origin = ray.origin;
		double a = ray_direction.dot(normal);
		if (a ==0)
		{
			return -1;
		}
		else
		{
			Vec origin(0, 0, 0);
			double dist = (B - origin).dot(normal);
			//dist = abs(dist);
			double t = -(normal.dot(ray_origin) + dist) / normal.dot(ray_direction);

			Vec point = ray_origin + ray_direction * t;
			double area1 = ((point - B).cross(C - B)).magnitude();
			double area2 = ((point - C).cross(A - C)).magnitude();
			double area3 = ((point - A).cross(B - A)).magnitude();
			double total = ((A - B).cross(C - B)).magnitude();
			if (abs(total - area1 - area2 - area3) <= 0.001) {
				return (point - ray_origin).magnitude();
			}
			
			t = -(normal.dot(ray_origin*-1) + dist) / normal.dot(ray_direction*-1);
			point = ray_origin + ray_direction * t;
			area1 = ((point - B).cross(C - B)).magnitude();
			area2 = ((point - C).cross(A - C)).magnitude();
			area3 = ((point - A).cross(B - A)).magnitude();
			total = ((A - B).cross(C - B)).magnitude();

			if (abs(total - area1 - area2 - area3) <= 0.001) {
				return (point - ray_origin).magnitude();
			}
			return -1;
		}
	}
};

