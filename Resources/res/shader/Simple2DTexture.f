#version 120

uniform sampler2D texture;
varying vec2 textureCoord;

void main()
{
	gl_FragColor = texture2D(texture, vec2(0.0,0.0));
	//gl_FragColor = vec4(textureCoord,0.0,1.0);
}