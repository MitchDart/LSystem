#include "Line.h"

Line::Line() : Object()
{
	drawType = GL_TRIANGLES;
	vertex = new Shader("vertex.glsl",GL_VERTEX_SHADER);
	fragment = new Shader("fragment.glsl",GL_FRAGMENT_SHADER);
	objectMatrix = glm::translate(objectMatrix,glm::vec3(0.0f, 0.0f, -2.0f));
}

void Line::addSegment(float sx, float sy, float sz, float ex, float ey, float ez)
{
	glm::vec3 v(ex - sx, ey - sy, ez - sz);
	glm::vec3 a = glm::cross(glm::normalize(v),glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 rotate;
	for(int i = 0; i < 9; i++){
		rotate = glm::rotate(rotate, 40.0f, v);
		glm::vec4 answer = rotate * glm::vec4(a,1.0f);
		vertices.push_back((radius*answer.x) + sx);
		vertices.push_back((radius*answer.y) + sy);
		vertices.push_back((radius*answer.z) + sz);
		vertices.push_back((radius*answer.x) + ex);
		vertices.push_back((radius*answer.y) + ey);
		vertices.push_back((radius*answer.z) + ez);
		normals.push_back(answer.x);
		normals.push_back(answer.y);
		normals.push_back(answer.z);
		normals.push_back(answer.x);
		normals.push_back(answer.y);
		normals.push_back(answer.z);
	}
	for(int i = 0; i < 8; i++) {
		indices.push_back(numElements);
		indices.push_back(numElements + 1);
		indices.push_back(numElements + 2);

		indices.push_back(numElements + 2);
		indices.push_back(numElements + 1);
		indices.push_back(numElements + 3);
		numElements = numElements + 2;
	}
	indices.push_back(numElements);
	indices.push_back(numElements + 1);
	indices.push_back(numElements - (8*2));

	indices.push_back(numElements - (8*2));
	indices.push_back(numElements + 1);
	indices.push_back(numElements - (8*2) + 1);
	numElements = numElements + 2;
	if(sy < 1.0f)
	radius = (1.0f - (ey+1.0f)/2.0f)*0.01f;
	else 
	radius = 0.0f;
}

void Line::draw()
{
	Object::draw();
	objectMatrix = glm::rotate(objectMatrix,0.1f,glm::vec3(0.0f,1.0f,0.0f));
}