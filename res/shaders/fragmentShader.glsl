#version 150

in vec3 vs_out_color;

out vec4 fs_out_color;

void main()
{
    fs_out_color = vec4(vs_out_color, 1.0);
}