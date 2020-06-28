#pragma once
#include"vector.h"
#include"lights.h"
#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

#ifdef MAINPROGRAM 
Vector eyepos(0.0, 0.0, 0.0);
Vector UL(-1, 1, -1);
Vector UR(1, 1, -1);
Vector LL(-1, -1, -1);
Vector LR(1, -1, -1);
int w = 500, h = 500; // width and height 
#else 
EXTERN Vector eyepos;
EXTERN int w, h;
EXTERN Vector UL;
EXTERN Vector UR;
EXTERN Vector LL;
EXTERN Vector LR;
#endif 


EXTERN int numdlight;
EXTERN DLight dlights[10];