#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include<vector>
#include<FreeImage.h>
#define MAINPROGRAM
#include"variables.h"
#include"readfile.h"
#include"vector.h"
#include"sampler.h"
#include"film.h"
#include"geometry.h"
#include"camera.h"
#include"raytracer.h"
using namespace std;

int main(int argc, char* argv[])
{	
	if (argc < 2) {
		cerr << "Usage: program_name filename\n";
		exit(-1);
	}
	FreeImage_Initialise();
	readFile(argv[1]);
	Raytracer renderman;
	Camera cam(eyepos);
	Sample point;
	Sampler Pointmachine(w,h, UL, UR, LR, LL);
	bool validpoint = true;
	Color calculatedcolor;
	Film picture(w, h);

	while (validpoint) {
		Ray light(eyepos);
		validpoint = Pointmachine.getSample(&point); //generates sample
		cam.generateRay(point,&light);//shooting light
		renderman.trace(light, 0, &calculatedcolor);
		picture.commit(point, calculatedcolor);//recording color
	}
	picture.saveScreenshot("doom.png");
	FreeImage_DeInitialise();
	return 1;
}