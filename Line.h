#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Object.h"

class Line : public Object
{
private:
	float startx,starty,endx,endy;
	float radius = 0.01f;
	int numElements = 0;
public:
	Line();
	void addSegment(float,float,float,float,float,float);
	//void compileShaders();
	//void bufferData();
	void draw();
};
