#include "LSystem.h"

LSystem::LSystem(char* s)
{
	string = new char[strlen(s)];
	strcpy(string, s);
	printf("Initializing LSystem using %s\n",string);
	for(int j = 0; j < numRecursions; j++)
	{
		for(int i = 0; i < strlen(string); i++)
		{
			for(int k = 0; k < strlen(conditions); k++)
			{
				if(string[i] == conditions[k]) {
					applyRule(i,k);
					i = i + strlen(rules[k]) - 1;
				}
			}
		}
	}
	generateLines();
}
 
void LSystem::applyRule(int s,int r)
{
	char* newString = new char[strlen(string) + strlen(rules[r])];
	for(int i = 0; i < s; i++)
	{
		newString[i] = string[i];
	}
	for(int i = 0; i < strlen(rules[r]); i++)
	{
		newString[s+i] = rules[r][i];
	}
	for(int i = 0; i < strlen(string) - s -1; i++)
	{
		newString[s+strlen(rules[r])+i] = string[s+i+1];
	}
	newString[strlen(string)+strlen(rules[r]) -1] = '\0';
	delete [] string;
	string = newString;
}

void LSystem::generateLines()
{
	float d = 0.1f;
	float r = 22.0f;
	int currentLine = 0;
	float currentX = 0.0f;
	float currentY = -1.0f;
	float currentZ = 0.0f;
	float currentRot = 0.0f;
	float currentOr = 0.0f;
	stack<float> stackX;
	stack<float> stackY;
	stack<float> stackZ;
	stack<float> stackRot;
	stack<float> stackOr;
	lines = new Line();
	for(int i = 0; i < strlen(string); i++)
	{
		switch(string[i])
		{
			case 'F' :
				lines->addSegment(currentX,currentY, currentZ, currentX + (d * sin(currentRot*PI/180)), currentY + (d * cos(currentRot*PI/180)), currentZ + (d * sin(currentOr*PI/180)));
				currentX = currentX + (d * sin(currentRot*PI/180));
				currentY = currentY + (d * cos(currentRot*PI/180));
				currentZ = currentZ + (d * sin(currentOr*PI/180));
				break;
			case '[' :
				stackX.push(currentX);
				stackY.push(currentY);
				stackZ.push(currentZ);
				stackOr.push(currentOr);
				stackRot.push(currentRot);
				break;
			case ']' :
				currentX = stackX.top();
				currentY = stackY.top();
				currentZ = stackZ.top();
				currentRot = stackRot.top();
				currentOr = stackOr.top();
				stackX.pop();
				stackY.pop();
				stackZ.pop();
				stackRot.pop();
				stackOr.pop();
				break;
			case '+' :
				currentRot = currentRot + r;
				break;
			case '-' :
				currentRot = currentRot - r;
				break;
			case '*' :
				currentOr = currentOr + r;
				break;
			case '&' :
				currentOr = currentOr - r;
				break;
		}
	}
	lines->compileShaders();
	lines->bufferData();
	Experiment::getInstance().addToObjectStack(lines);
}
