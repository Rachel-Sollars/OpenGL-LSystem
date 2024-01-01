#version 330 core

//out vec3 color;
out vec4 color;
in vec3 vertNorm;
in vec2 vertUV;

uniform sampler2D texSampler;

uniform LightBlock {
	vec3 lightDir;
	vec3 lightColour;
};

uniform vec3 objColour;

void main(){
	vec3 norm = normalize(vertNorm);
	vec3 lightNorm = normalize(lightDir);

	//if object colour, use texture else object colour
	vec3 baseColour = objColour.x < 0.0f ? texture(texSampler, vertUV).xyz : objColour;

	float diffuseFactor = max(dot(norm, lightNorm), 0.0f);
	vec3 diffuse = diffuseFactor * lightColour;

	color = vec4(diffuse * baseColour, 1.0f);
}