#pragma once
#include"vector.h"
#include"sample.h"

class Sampler {
	public:
	int w, h;
	Vector ul, ur, lr, ll;
	int rcount, ccount;
	Sampler(int width,int height,Vector& UL,Vector& UR,Vector& LR,Vector& LL) {
		w = width;
		h = height;
		ul = UL; ur = UR; lr = LR; ll = LL;
		rcount = 0; ccount = -1;
	}
	bool getSample(Sample* sample) {
		double colres = abs(ur.x - ul.x) / w; 
		double rowres = abs(ul.y - ll.y) / h;
		double zres = abs(ur.z - ul.z) / h;
		if (rcount == h - 1 && ccount == w - 1)
			return false;	
		ccount++;
		sample->r = rcount; sample->c = ccount;
		if (rcount < h) { 
			if (ccount < w) {
				sample->x =(float)( ul.x + ccount*colres+colres/2);
			}
			else {
				sample->y =(float)(ul.y-rcount*rowres-rowres/2);
				ccount = 0;
				rcount++; 
			}
			sample->y = (float)(ul.y - rcount * rowres-rowres/2);
			sample->z = (float)(ul.z + ccount * zres + zres / 2); 
		}
		else {
			return false;
		}
		return true;
	}
};