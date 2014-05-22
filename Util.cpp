#include "Util.h"

char* Util::utilReadFromFile(char* filename) {
  unsigned int bufferSize = 1048576;
  char* buffer = (char*)malloc(bufferSize);
  FILE* file = fopen(filename, "r");
  if(file == NULL)
  {
    fprintf(stderr, "Could not open file, %s \n" , filename);
  }
  unsigned int index = 0;
  while(true)
  {
    char c = (char)fgetc(file);
    if(ferror(file) != 0)
    {
      fprintf(stderr, "Could not read from file %s\n", filename);
    }
    if(index == bufferSize - 1)
    {
      bufferSize *= 2;
      buffer = (char*)realloc((void*)buffer, bufferSize);
    }
    if(feof(file))
    {
      break;
    }
    buffer[index] = c;
    index++;
  }
  buffer[index] = NULL;
  fclose(file);
  return buffer;
}

void Util::printMat(glm::mat4  mat){
  int i,j;
  for (j=0; j<4; j++){
    for (i=0; i<4; i++){
    printf("%f ",mat[i][j]);
  }
  printf("\n");
 }
}