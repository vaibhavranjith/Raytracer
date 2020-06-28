#pragma once
#include<math.h>
#include"vector.h"
#include"sample.h"
class Point {
public:
	float x, y, z;
	Point(float X,float Y,float Z) {
		x = X; y = Y; z = Z;
	}
	Point(Vector& a) {
		x = a.x; y = a.y; z = a.z;
	}
	Point() {
		x = 0; y = 0; z = 0;
	}
	static Point add(Point& a, Point& b) {
		Point res(a.x + b.x, a.y + b.y, a.z + b.z);
		return res;
	}

	static Point add(Vector& a, Point& b) {
		Point res(a.x + b.x, a.y + b.y, a.z + b.z);
		return res;
	}

	static Point add(Point&  a, Vector& b) {
		Point res(a.x + b.x, a.y + b.y, a.z + b.z);
		return res;
	}
	static Point sub(Vector& a, Point& b) {
		Point res(a.x - b.x, a.y - b.y, a.z -b.z);
		return res;
	}

	static Point sub(Point& a, Vector& b) {
		Point res(a.x - b.x, a.y - b.y, a.z - b.z);
		return res;
	}
	static Point sub(Point& a, Point& b) {
		Point res(a.x - b.x, a.y - b.y, a.z - b.z);
		return res;
	}
	static float dotproduct(Point& a, Point& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	static float dotproduct(Vector& a, Point& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	static float dotproduct(Point& a, Vector& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	static Vector normalize(Point a) {
		float mag = (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
		Vector res(a.x / mag, a.y / mag, a.z / mag);
		return res;
	}
};
class Ray {
public:
	Point pos;
	Vector dir;
	float t_min, t_max;
	Ray(Vector& eyepos) {
		pos.x = eyepos.x; pos.y = eyepos.y; pos.z = eyepos.z;
		dir = eyepos;
		t_min = 0;
		t_max = 1000;
	}
	Ray() {
		t_min = 0; t_max = 0;
	}
};

class Camera {
public:
	Vector pos;
	Camera(Vector& eyepos) {
		pos = eyepos;
	}
	void generateRay(Sample& sample, Ray* ray) {
		Vector eye = ray->dir;
		Vector screenpoint(sample.x, sample.y, sample.z);
		ray->dir = Vector::sub(screenpoint, eye);
		ray->pos = pos;
	}
};