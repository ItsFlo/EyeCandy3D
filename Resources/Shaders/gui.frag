#include "Common.glsl"

uniform float time;

uniform bool material_has_texture;
uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform vec4 material_emissive;
uniform float material_shininess;

uniform sampler2D texture_diffuse1;
uniform vec4 uColor;

in vec2 texCoords;
in vec3 normal;

out vec4 fragColor;

void main(void)
{
	fragColor = vec4(1.0,1.0,1.0,1.0);
	
	if(material_has_texture)
	{
		fragColor = texture(texture_diffuse1, texCoords);
	}
	else
	{
		fragColor = material_diffuse;
	}
	
	fragColor = fragColor + (1.0 - fragColor.a) * material_diffuse;
	fragColor = fragColor + material_ambient;

	fragColor = uColor;
}