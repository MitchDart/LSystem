#pragma once
#include <malloc.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "LSystem.h"
#include "Object.h"


class Experiment
{
private:
	const GLuint VERTEX_SIZE = 5;
	const GLuint VERTICES_PER_TRIANGLE = 3;
	const GLuint DIMENSIONS = 2;
	const GLuint COLOUR_COMPONENT_COUNT = 3;
	const GLuint ARRAY_SIZE = VERTICES_PER_TRIANGLE * (DIMENSIONS + COLOUR_COMPONENT_COUNT);


	 glm::mat4 world;
	 glm::mat4 view;
	 glm::mat4 projection;

	Object** objectStack;
	int numObjects;
	bool started;
public:
	Experiment();
	Experiment(int*, char**);
	Experiment(Experiment const&);
	void operator=(Experiment const&);
	~Experiment(void);
	//CALL BACKS
	static void display(void);
	static void idle(void);
	static void keyboard(int,int,int);
	static void keyboardup(int,int,int);
	static void asci(unsigned char,int,int);
	static void asciup(unsigned char,int,int);
	static void mouseMove(int,int);

	static void initGLUT(int,char**);
	void initMatricies(void);
	glm::vec3 v4tov3(glm::vec4 v);
	void setup();
	void addToObjectStack(Object*);
	static Experiment& getInstance() {
		static Experiment instance;
		return instance;
	}
};

