#version 420

uniform mat4 objectMatrix;
uniform mat4 perspectiveMatrix;

in vec3 position;
in vec3 normal;

out vec4 v_normal;
out vec3 v_world;

void main()
{
  v_normal = perspectiveMatrix * objectMatrix * vec4(normal, 1.0);
  gl_Position = perspectiveMatrix * objectMatrix * vec4(position, 1.0);
}