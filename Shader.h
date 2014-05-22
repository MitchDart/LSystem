#pragma once
#include <malloc.h>
#include <stdlib.h>
#include "Util.h"
#include <GL/glew.h>

class Shader
{
	private:
		int type;
		int handle;
	public:
		Shader(char*, int type);
		int getHandle();
};