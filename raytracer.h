#pragma once
#include"film.h"
#include"camera.h"
#include"geometry.h"
#include<math.h>
#include<algorithm>
#include"variables.h"
#include"lights.h"
using namespace std;

class Raytracer {
public:
	void trace(Ray& ray,int depth,Color* color){
		LocalGeo local;
		float thit;
		Color ka(0.0, 0.0, 0.0), kr(0, 0, 0), ks(1.0, 1.0, 1.0), kd(1.0, 0.0, 1.0);
		BRDF mat(kd, ks, ka, kr);
		Sphere s(*(new Point(0, 0, -20)),3,mat);
		if (s.intersect(ray, &thit, &local)) {
			//Color res(0, 0, 1); 
			//*color = res;
			Color res(0, 0, 0);
			res = Color::addcolors(res, s.mat.ka);
			//cout << res.r << " " << res.g << " " << res.b << "\n";
			for (int i = 0; i < numdlight; i++) {
				Ray lray(eyepos);
				dlights[i].generateLightRay(local,&lray,&res);
				Vector eyedir = Point::normalize(Point::sub(eyepos,local.pos));
				Vector halfvec = Vector::normalize(Vector::sum(eyedir, lray.dir));
				Vector normal(local.normal.x, local.normal.y, local.normal.z);
				float ndotl = Vector::dotproduct(normal, lray.dir);
				ndotl = (ndotl > 0) ? ndotl : 0;
				Color lambert = Color::scalarproduct(s.mat.kd, dlights[i].intensity);
				lambert = Color::scale(ndotl,lambert);
				float ndoth = Vector::dotproduct(normal, halfvec);
				ndoth = (ndoth > 0) ? ndoth : 0.0;
				Color phong = Color::scalarproduct(s.mat.ks, dlights[i].intensity);
				phong = Color::scale(pow(ndoth, 50), phong);
				res = Color::addcolors(res, lambert);
				res = Color::addcolors(res, phong);
				//cout << res.r << " " << res.g << " " << res.b << "\n";
				//cout << phong.r << " " << phong.g << " " << phong.b << "\n";
				//cout << ndoth << " " << ndotl << "\n";
			}
			*color=res;
		}
		else {
			Color res(0, 0, 0);
			//cout << res.r << " " << res.g << " " << res.b << "\n";
			*color = res;
		}

	}
};
