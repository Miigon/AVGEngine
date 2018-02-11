#version 120

uniform sampler2D texture;
varying vec2 textureCoord;

void main()
{
	gl_FragColor = texture2D(texture, textureCoord);
	if (gl_FragColor.a == 0.0f)
		discard;
}