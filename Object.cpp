#include "Object.h"

Object::Object()
{
	printf("Creating object\n");
	vertex = 0;
	fragment = 0;
	vao = 0;
	objectMatrix = glm::mat4();
	GLint m_viewport[4];

	glGetIntegerv( GL_VIEWPORT, m_viewport );
	perspectiveMatrix = glm::perspective(60.0f, (m_viewport[2] / m_viewport[3]) * 1.0f, 0.1f, 100.f);
	drawType = GL_TRIANGLES;
	colour = glm::vec3(1.0f,1.0f,1.0f);
}

void Object::initSettings()
{
	glEnable(GL_DEPTH_TEST);
}

void Object::compileShaders()
{
	printf("Compiling shader program\n");
	shaderProgram = glCreateProgram();
	if(vertex != 0)
		glAttachShader(shaderProgram,vertex->getHandle());
	if(fragment != 0)
		glAttachShader(shaderProgram,fragment->getHandle());
	glLinkProgram(shaderProgram);

	GLint status;
  	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  	if(status == GL_FALSE)
  	{
		GLint len;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &len);
		char* log = new char[len];
		glGetProgramInfoLog(shaderProgram, len, &len, log);
		printf("%s",log);
	    delete [] log;
	    exit(0);
  	}

	positionLoc = glGetAttribLocation(shaderProgram, "position");
	normalLoc = glGetAttribLocation(shaderProgram, "normal");
	objectMatrixLoc = glGetUniformLocation(shaderProgram, "objectMatrix");
	perspectiveMatrixLoc = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
	colourLoc = glGetUniformLocation(shaderProgram, "colourin");
	printf("Colour Location: %d\n",colourLoc);
}

void Object::bufferData() 
{
	printf("Generating Buffers\n");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	buffers = new unsigned int[3]; // max 3 buffers
	glGenBuffers(3, buffers);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc,3,GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc,3,GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glUseProgram(shaderProgram);
	
	glUniformMatrix4fv(perspectiveMatrixLoc,1,GL_FALSE,glm::value_ptr(perspectiveMatrix));
	glUniform3fv(colourLoc,1,glm::value_ptr(colour));

	glBindVertexArray(0);
}

void Object::draw()
{

	initSettings();
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glUniformMatrix4fv(objectMatrixLoc,1,GL_FALSE,glm::value_ptr(objectMatrix));
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawElements(drawType,indices.size(),GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}

void Object::setVertexShader(Shader* s)
{
	vertex = s;
}
void Object::setFragmentShader(Shader* s)
{
	fragment = s;
}

void Object::translate(float x ,float y ,float z)
{
	objectMatrix = glm::translate(glm::mat4(objectMatrix),glm::vec3(x, y, z));
}

std::vector<float> Object::getVertices() {
	 return vertices;
}

std::vector<unsigned int> Object::getIndices() {
	 return indices;
}

std::vector<float> Object::getNormals() {
	 return normals;
}

Object::~Object() {

}