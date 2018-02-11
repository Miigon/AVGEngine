#version 120

attribute vec4 vPosition;
attribute vec2 vTextureCoord;

varying vec2 textureCoord;

void main()
{
	gl_Position=vPosition;
	textureCoord = vTextureCoord;
}