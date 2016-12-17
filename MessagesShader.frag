#version 120

varying vec2 var_vertexUV; //texture to screen
uniform sampler2D myTextureSampler;
bool white;

void main(){
	
	vec4 color = texture2D( myTextureSampler, var_vertexUV );
	
	bvec3 bools = greaterThan (color.rgb, vec3(0.5,0.5,0.5));
	if (bools.x && bools.y && bools.z) //if color.rgb == vec3(1.0,1.0,1.0)
	discard;

	gl_FragColor = color;

	// if (white)
	// {
	// 	gl_FragColor.rgb = texture2D( myTextureSampler, var_vertexUV ).rgb;
	// 	gl_FragColor.a = 0;
	// }


}