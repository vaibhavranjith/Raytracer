#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <FreeImage.h>
using namespace std;
#include "readfile.h"
#include"variables.h"
bool readvals(stringstream &s, int numvals, float* values)
{
	
	for (int i = 0; i < numvals; i++) {
		s >> values[i];
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

void readFile(const char* filename) {
	string str, cmd;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {
		bool validinput;
		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && str[0] != '#') {
				//parsing ut blank lines and comments
				stringstream s(str);
				float values[12];
				s >> cmd;
				if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						w = (int)values[0];
						h = (int)values[1];
					}
				}

				if (cmd == "eyepos") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						eyepos.x = values[0];
						eyepos.y = values[1];
						eyepos.z = values[2];
					}
				}

				if (cmd == "corners") {
					validinput = readvals(s, 12, values);
					if (validinput) {
						UL.x = values[0]; UL.y = values[1]; UL.z = values[2];
						UR.x = values[3]; UR.y = values[4]; UR.z = values[5];
						LR.x = values[6]; LR.y = values[7]; LR.z = values[8];
						LL.x = values[9]; LL.y = values[10]; LL.z = values[11];
					}
				}

				if (cmd == "directional") {
					validinput = readvals(s, 6, values);
					if (validinput) {
						Point p(values[0], values[1], values[2]);
						Color c(values[3], values[4], values[5]);
						dlights[numdlight].pos = p;
						dlights[numdlight].intensity = c;
						numdlight++;
					}
				}
			
			}
			getline(in, str);
		}
	}
	else {
		cout << "Not able to open file";
	}
}
