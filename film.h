#pragma once
#include"sample.h"
#include"FreeImage.h"
#include<string>
#include<iostream>
#include<math.h>
using namespace std;

double adj(float C) {
	if (abs(C) < 0.0031308) {
		return 12.92 * C;
	}
	return 1.055 * pow(C, 0.41666) - 0.055;
}
class Color {
	public:
		float r, g, b;
		Color(float R, float G, float B) {
			r = R; g = G; b = B;
			if (R > 1)r = 1; if (G > 1)g = 1; if (B > 1)b = 1;
			if (R < 0)r = 0; if (G < 0)g = 0; if (B < 0)b = 0;
		}
		Color() {
			r = 0; g = 0; b = 0;
		}
		static Color addcolors(Color& x, Color& y) {
			Color res(x.r + y.r, x.g + y.g, x.b + y.b);
			return res;	
		}
		static Color subcolor(Color& x, Color& y) {
			Color res(x.r - y.r, x.g - y.g, x.b - y.b);
			return res;
		}
		static Color scalarproduct(Color& x, Color& y) {
			Color res(x.r * y.r, x.g * y.g, x.b * y.b);
			return res;
		}

		static Color scale(float x, Color& y) {
			Color res(x * y.r, x * y.g, x * y.b);
			return res;
		}
		static void xyztorgb(BYTE* R, BYTE* G, BYTE* B,Color x) {
			//if (x.r > 1)x.r = 1; if (x.g > 1)x.g = 1; if (x.b > 1)x.b = 1;
			//if (x.r < 0)x.r = 0; if (x.g < 0)x.g = 0; if (x.b < 0)x.b = 0;
			*B = 255 * adj(x.r);
			*G = 255 * adj(x.g);
			*R = 255 * adj(x.b);	
		}
		/* USE this if non-linear relation with xyz is required.sRGB space
		*R = (BYTE)255*(3.2404542 * x.r - 1.5371385 * x.g - 0.4985314 * x.b);
			*G = (BYTE)255*(-0.9692660 * x.r + 1.8760108 * x.g + 0.0415560 * x.b);
			*B =(BYTE)255*( 0.0556434 * x.r - 0.2040259 * x.g + 1.0572252 * x.b);
		function adj(C) {
			if (Abs(C) < 0.0031308) {
				return 12.92 * C;
			}
			return 1.055 * Math.pow(C, 0.41666) - 0.055;
		}*/
};

class Film {
	public:
		BYTE* pixels;
		int w, h;
		Film(int W,int H) {
			pixels = new BYTE[3 * (W * H)];
			w = W; h = H;
		}
		void commit(Sample& sample,Color& color){
			BYTE r, g, b;
			Color::xyztorgb(&r, &g, &b, color);
			this->pixels[(sample.r) * 3 *(this-> w)+ (sample.c) * 3] = r;
			this->pixels[(sample.r) * 3 * (this->w) + (sample.c) * 3 + 1] = g;
			this->pixels[(sample.r) * 3 * (this->w) + (sample.c) * 3 + 2] = b;
		}
		void saveScreenshot(string fname) {
			FIBITMAP* img = FreeImage_ConvertFromRawBits(this->pixels, this->w,this->h, this->w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
			cout << "Saving screenshot: " << fname << "\n";
			FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
		}
};
