#version 130

attribute vec4 vertex;
uniform mat4 pvmMatrix;
uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform vec4 clipPlane0; // defined in view-space


void main(void)
{
   gl_Position = pvmMatrix * vertex;
   vec4 vsPos = vMatrix * mMatrix * vertex; // position of vertex in viewspace
   gl_ClipDistance[0] = dot(clipPlane0,vsPos);
}