#pragma once
#include <malloc.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include <vector>
class Object
{
	protected: 
		Shader* vertex;
		Shader* fragment;
		uint shaderProgram;
		uint vao;
		uint* buffers;
		uint positionLoc;
		uint normalLoc;
		uint objectMatrixLoc;
		uint perspectiveMatrixLoc;
		uint colourLoc;
		glm::mat4 objectMatrix;
		glm::mat4 perspectiveMatrix;
		glm::vec3 colour;
		uint numVertices;
		std::vector<unsigned int> indices;
		std::vector<float> vertices;
		std::vector<float> normals;
		uint drawType;
	public:
		void translate(float,float,float);
		Object();
		virtual ~Object();
		virtual void compileShaders();
		virtual void draw();
		void setVertexShader(Shader*);
		void setFragmentShader(Shader*);
		void initSettings();
		virtual void bufferData();
		std::vector<float> getVertices();
		std::vector<unsigned int> getIndices();
		std::vector<float> getNormals();
};