#version 330 core

in vec3 vertexColor;
out vec4 color;

void main()
{
    if(gl_FrontFacing)
    {
        color = vec4(vertexColor, 1.0);
    }
    else
    {
        color = vec4(0.2, 0.2, 0.2, 1.0);
    }

}
