#version 410 core

in vec2 vertexPosition;
in vec4 vertexColour;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColour;
out vec2 fragmentUV;

uniform mat4 P;

void main()
{
    //gl_Position = vec4(vertexPosition, 0.0, 1.0);
    gl_Position = (P * vec4(vertexPosition, 0.0, 1.0));
    //gl_Position.z = 0.0;
    //gl_Position.w = 1.0;

    fragmentColour = vertexColour;
    fragmentPosition = vertexPosition;
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}