#version 420

uniform vec3 colourin;

out vec4 f_colour;
in vec4 v_normal;

void main()
{
	vec3 light = vec3(1.0,-1.0,-1.0);
	vec3 normal = vec3(v_normal.x, v_normal.y, v_normal.z);
	float amount = dot(light,normal);
	if(amount < 0.0)
		amount = 0.0;
	amount = amount + 0.5;
   f_colour = vec4(amount * 0.5, amount * 0.396, amount * 0.09,1.0);
}