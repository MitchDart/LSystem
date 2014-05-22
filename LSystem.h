#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Line.h"
#include <cstring>
#include <stack>
#include <cmath>
#include "Experiment.h"

#define PI 3.14159265

using namespace std;

class LSystem 
{
private:
	char* string;
	Line* lines;
	int numLines = 0;
	const char* conditions = "F";
	const char rules[1][100] = {"FF-[-F+F&+F]+[+F*-F-F]&[F-FF]*[F+F+F]"};
	const int numRecursions = 3;
public:
	LSystem(char*);
	void applyRule(int,int);
	void generateLines();
};
