#pragma once
#include<math.h>
#include<iostream>
class Vector
{
	public:
	float x, y, z;
	Vector(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	Vector() {
		x = 0;
		y = 0;
		z = 0;
	}
	static Vector sum(Vector& a, Vector& b) {
		Vector res(a.x + b.x, a.y + b.y, a.z + b.z);
		return res;
	}
	static Vector sub(Vector& a, Vector& b) {
		Vector res(a.x - b.x, a.y - b.y, a.z - b.z);
		return res;
	}
	static float dotproduct(Vector& a, Vector& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	static Vector normalize(Vector& a) {
		float mag = (float)sqrt((double)a.x * a.x + (double)a.y * a.y + (double)a.z * a.z);
		Vector res(a.x / mag, a.y / mag, a.z / mag);
		return res;
	}
	static void printVector(Vector& that) {
		std::cout << '\n' << that.x << ' ' << that.y << ' ' << that.z << '\n';
	}

};


