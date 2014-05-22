#include "Shader.h"

Shader::Shader(char* filename,int type) {
	printf("Creating shader: %s\n", filename);
	const char* shaderFile = Util::utilReadFromFile(filename);
	handle = glCreateShader(type);
	glShaderSource(handle,1,&shaderFile,NULL);
	delete [] shaderFile;
	glCompileShader(handle);
	GLint status;
  	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
  	if(status == GL_FALSE)
  	{
		GLint len;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &len);
		char* log = new char[len];
		glGetShaderInfoLog(handle, len, &len, log);
		printf("%s",log);
	    delete [] log;
	    exit(0);
  	}
  	printf("Shader compiled\n");
}

int Shader::getHandle() {
	return handle;
}