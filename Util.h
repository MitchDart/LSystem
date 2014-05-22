#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Util 
{
public:
	static char* utilReadFromFile(char*);
	static void printMat(glm::mat4);
};
