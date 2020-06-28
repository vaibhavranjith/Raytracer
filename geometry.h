#pragma once
#include"camera.h"
#include"vector.h"
#include<math.h>
#include"variables.h"
class Normal {
public:
	float x, y, z;
	Normal(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
		double mag = sqrt(x * x + y * y + z * z);
		if (mag != 0) {
			x = (float)(X / mag); y = (float)(Y / mag); z = (float)(Z / mag);
		}
	}
	Normal() {
		x = 0; y = 0; z = 0;
	}
	static Normal sum(Normal& a, Normal& b) {
		Normal res(a.x + b.x, a.y + b.y, a.z + b.z);
		return res;
	}
	static Normal sub(Normal& a, Normal& b) {
		Normal res(a.x - b.x, a.y - b.y, a.z - b.z);
		return res;
	}
};
class LocalGeo {
public:
	Point pos;
	Normal normal;
	LocalGeo(Point& p, Normal& n) {
		pos = p;
		normal = n;

	}
	LocalGeo() {
		pos = *(new Point(0, 0, 0));
		normal = *(new Normal(0, 0, 0));
	}
};
class BRDF {
public:
	Color kd, ks, ka, kr;
	BRDF(Color d, Color s, Color a, Color r) {
		kd = d; ks = s; ka = a; kr = r;
	}
	BRDF() {
	}
};
/*
class Material {
public:
	BRDF constantBRDF;
	void getBRDF(LocalGeo& local, BRDF* brdf) {
		*brdf = constantBRDF;
	}
};*/
class Sphere {
public:
	Point center;
	float radius;
	BRDF mat;
	Sphere() {
		radius = 0;
	}
	Sphere(Point& c, float r,BRDF& b) {
		center = c;
		radius = r;
		mat = b;
	}
	bool intersect(Ray& ray, float* thit, LocalGeo* local) {
		Vector p1 = Vector::normalize(ray.dir);
		float a = Vector::dotproduct(p1,  p1);
		float b = 2 * Point::dotproduct(p1, Point::sub(ray.pos, center));
		Point temp = Point::sub(ray.pos, center);
		float c = Point::dotproduct(temp, temp) - radius * radius;
		//cout << (b * b - 4 * a * c) << '\n';
		if ((b * b - 4 * a * c )< 0)
			return false;
	
		else if (b * b - 4 * a * c == 0) 
			*thit = -b / (2 * a);
		else {
			float det = sqrt(b * b - 4 * a * c);
			float root1 = (-b + det) / (2 * a);
			float root2 = (-b - det) / (2 * a);
			if (root1 < 0)
				*thit = root2;
			else if (root2 < 0)
				*thit = root1;

			if (root1 < root2)
				*thit = root1;
			else
				*thit = root2;
		}
		Point pt(ray.dir.x * (*thit), ray.dir.y * (*thit), ray.dir.z * (*thit));
		Point p = Point::add(ray.pos, pt);
		Normal n(p.x - center.x, p.y - center.y, p.z - center.z);
		local->pos = p;
		local->normal = n;
		return true;
	}
};
