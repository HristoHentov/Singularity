#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) 
		* clamp(dot(-vec3(0.2,0.2,0.8), normal0), 0.0, 1.0) * 3;
}