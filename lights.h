#pragma once
#include"camera.h"
#include"vector.h"
#include"film.h"
#include"geometry.h"
class Light {
public:
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) = 0;
		
};
class DLight :public Light {
public:
	Color intensity;
	Point pos;
	DLight(Point p, Color x) {
		pos = p;
		intensity = x;
	}
	DLight() {
		pos = *(new Point(0,0,0));
		intensity = *(new Color(0, 0, 0));
	}
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
		Point temp = Point::sub(pos, local.pos);
		Vector resdir(temp.x, temp.y, temp.z);
		lray->dir = Vector::normalize(resdir);
		lray->pos = local.pos;
		//*lcolor = intensity;
	}
};
