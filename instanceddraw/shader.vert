#version 330 core

in vec3 position;
in vec3 isz;
out vec3 vertexColor;

uniform mat4 m;
uniform mat4 p;
uniform mat4 v;

void main()
{
    if(gl_VertexID < 12)
    {
        vertexColor = vec3(1.0, 0.0, 0.0);
    }
    else if(gl_VertexID >= 12 && gl_VertexID < 24)
    {
        vertexColor = vec3(0.0, 1.0, 0.0);
    }
    else
    {
        vertexColor = vec3(0.0, 0.0, 1.0);
    }

    gl_Position = p * v * m * vec4(position.x + isz.x,position.y + isz.y,position.z + isz.z,   1.0);
}
