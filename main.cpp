#include "Experiment.h"
#include <GL/glew.h>
#include <GL/glut.h>

int main(int argc, char** argv) {
	
	Experiment::getInstance().initGLUT(argc,argv);

	return 0;
} 