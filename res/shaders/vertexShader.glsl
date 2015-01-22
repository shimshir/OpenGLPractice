#version 150

in vec2 position;
in vec3 vs_in_color;

out vec3 vs_out_color;

void main()
{
    vs_out_color = vs_in_color;
    gl_Position = vec4(position, 0.0, 1.0);
}