Texture2D positionTexture;
Texture2D normalTexture;
Texture2D diffuseTexture;

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR; // coming up after the break!
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VSSceneIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;		// SV_Position is a (S)ystem (V)ariable that denotes transformed position
	float2 UVCoord : UVCOORD;
};

//Variables that updated often
cbuffer cbEveryFrame
{
	//Transformation matrices
	//matrix viewMatrix;
	//matrix projectionMatrix;
	//matrix modelMatrix;

	int nrOfPointLights;
	int nrOfDirectionalLights;
	int nrOfSpotLights;
	float3 lightPosition[100];
	float3 lightDirection[100];
	float3 la[150];
	float3 ld[150];
	float3 ls[150];
	float lightRadius[100];
	float2 lightAngle[50];

	float3 cameraPos;
};

// State Structures
DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

RasterizerState rs
{
	FillMode = Solid;
	CullMode = BACK;
};

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};

BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};



//-----------------------------------------------------------------------------------------
// Calculate the light intensity for a given point
//-----------------------------------------------------------------------------------------
float3 calcAmbientLight()
{
	float3 la = float3(0.1f, 0.1f, 0.1f);
	float3 ka = float3(1.0f, 1.0f, 1.0f);

	//Ambient light
	float3 ambient = la * ka;

	return ambient;
}

float3 calcDiffuseLight(float3 lightDir, float3 normal, float3 color)
{
	//Variables
	float3 n = normal;
	float3 s = normalize(lightDir);

	//Diffuse light
	float3 diffuse = saturate(dot(s,n)) * color;

	return diffuse;
}

float3 calcSpecularLight(float3 lightDir, float3 normal, float3 color)
{
	float3 ks = float3(1.0f, 1.0f, 1.0f);
	float f = 30.0f;

	lightDir = -normalize(lightDir);
	float3 reflection = reflect(lightDir, normal);

	//Specular light
	float3 specular = color * pow(saturate(dot(normal,(-lightDir + cameraPos))), f);

	return specular;
}

PSSceneIn VSScene(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	// transform the point into view space
	output.Pos = float4(input.Pos,1.0);
	output.UVCoord = input.UVCoord;

	return output;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	float4 position = positionTexture.Sample(linearSampler, input.UVCoord);
	float4 normal = normalTexture.Sample(linearSampler, input.UVCoord);
	float4 diffuse = diffuseTexture.Sample(linearSampler, input.UVCoord);

	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float3 ambientLight = float3(0.0f, 0.0f, 0.0f);
	float3 diffuseLight = float3(0.0f, 0.0f, 0.0f);
	float3 specularLight = float3(0.0f, 0.0f, 0.0f);

	int i;
	float3 distVector;
	float distance;
	float cutoff = 0.005f;
	float attenuation;
	int nrOfPointAndDirectionalLights = nrOfPointLights + nrOfDirectionalLights;

	for(i = 0; i < nrOfPointLights; i++)
	{
		distVector = (lightPosition[i] - position.xyz);
		distance = length(distVector);
		attenuation = 1 / ((distance / lightRadius[i] + 1) * (distance / lightRadius[i] + 1));

		ambientLight = ambientLight + la[i];
		diffuseLight = diffuseLight + calcDiffuseLight(distVector, normal.xyz, ld[i]) * attenuation;
		specularLight = specularLight + calcSpecularLight(distVector, normal.xyz, ls[i]) * attenuation;
	}

	for(i = 0; i < nrOfDirectionalLights; i++)
	{
		ambientLight = ambientLight + la[nrOfPointLights + i];
		diffuseLight = diffuseLight + calcDiffuseLight(lightDirection[i], normal.xyz, ld[nrOfPointLights + i]);
		specularLight = specularLight + calcSpecularLight(lightDirection[i], normal.xyz, ls[nrOfPointLights + i]);
	}

	for(i = 0; i < nrOfSpotLights; i++)
	{
		distVector = (lightPosition[nrOfPointLights + i] - position.xyz);
		distance = length(distVector);
		attenuation = 1 / ((distance / lightRadius[nrOfPointLights + i] + 1) * (distance / lightRadius[nrOfPointLights + i] + 1));

		float3 pos = float3(50.0f, 1.0f, 50.0f);
		float3 s = normalize((lightPosition[nrOfPointLights + i] - position.xyz));

		float angle = max(acos(dot(s, normalize(lightDirection[nrOfDirectionalLights + i]))), 0.0f);
		float spotfactor = max((cos(angle) - cos(lightAngle[i].x / 2)) / (cos(lightAngle[i].y / 2) - cos(lightAngle[i].x / 2)), 0.0f);

		ambientLight = ambientLight + la[nrOfPointAndDirectionalLights + i];
		diffuseLight = diffuseLight + calcDiffuseLight(s, normal.xyz, ld[nrOfPointAndDirectionalLights + i]) * spotfactor * attenuation;
		specularLight = specularLight + calcSpecularLight(s, normal.xyz, ls[nrOfPointAndDirectionalLights + i]) * spotfactor * attenuation;
	}

	return float4(ambientLight, 0.0f) + float4(diffuseLight, 1.0f) * diffuse + float4(specularLight, 0.0f);
}

technique10 RenderModelDeferred
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );

	    SetDepthStencilState( DisableDepth, 0 );
	    SetRasterizerState( rs );
    }  
}