#version 150

in vec3 position;
in vec3 texCoord;
in vec3 normal;

void main()
{
    gl_Position = vec4(position, 1.0);
}