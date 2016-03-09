#version 130

uniform bool lightOn;
uniform bool hasTexture;
uniform vec3 LightPosition_worldspace;
uniform vec4 LightColor;
uniform float LightAmbient, LightDiffuse, LightSpecular;
uniform float Kc, Kl, Kq;
uniform int MaterialShininess;
uniform sampler2D textureSampler;


varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;
varying vec4 vertexcolor;
varying vec2 UV;


void main()
{
	// Material properties
	vec4 MaterialAmbientColor, MaterialDiffuseColor, MaterialSpecularColor;

	if(lightOn)
	{
		if(hasTexture)
		{
			MaterialAmbientColor  = vec4(texture2D(textureSampler, UV).rgb*LightAmbient, vertexcolor.a) ;
			MaterialDiffuseColor  = vec4(texture2D(textureSampler, UV).rgb*LightDiffuse, vertexcolor.a);
		}
		else
		{
			MaterialAmbientColor  = vec4(vertexcolor.rgb * LightAmbient, vertexcolor.a);
			MaterialDiffuseColor  = vec4(vertexcolor.rgb * LightDiffuse, vertexcolor.a);
		}
		MaterialSpecularColor = vec4(LightSpecular, LightSpecular, LightSpecular, 1.0);

		// Distance to the light
		float distance = length(LightPosition_worldspace - Position_worldspace);

		// Normal of the computed fragment, in camera space
		vec3 n = normalize(Normal_cameraspace);

		// Direction of the light (from the fragment to the light)
		vec3 l = normalize(LightDirection_cameraspace);

		// Cosine of the angle between the normal and the light direction,
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta = clamp(dot(n,l), 0, 1);

		// Eye vector (towards the camera)
		vec3 E = normalize(EyeDirection_cameraspace);

		// Direction in which the triangle reflects the light
		vec3 R = reflect(-l,n);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		float cosAlpha = clamp( dot( E,R ), 0.0001, 1);

		float attenuation_factor = 1.0/(Kc + Kl*distance + Kq*distance*distance);

		gl_FragColor =
			MaterialAmbientColor * LightColor +
			(MaterialDiffuseColor  * LightDiffuse * cosTheta  +	MaterialSpecularColor  * LightSpecular * pow(cosAlpha, MaterialShininess))
				 * LightColor * attenuation_factor;
	}
	else
	{
		if(hasTexture)
		{
			gl_FragColor  = vec4(texture2D(textureSampler, UV).rgb, vertexcolor.a) ;
		}
		else
		{
			gl_FragColor  = vertexcolor;
		}
	}
}















