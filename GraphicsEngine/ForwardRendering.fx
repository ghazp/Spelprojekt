Texture2D tex2D;

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
	float3 Normal : NORMAL;
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;		// SV_Position is a (S)ystem (V)ariable that denotes transformed position
	float2 UVCoord : UVCOORD;
	float4 EyeCoord : EYE_COORD;
	float3 Normal : NORMAL;
};

//Variables that updated often
cbuffer cbEveryFrame
{
	//Transformation matrices
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix modelMatrix;

	float modelAlpha;
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
	//FillMode = Solid;
	CullMode = NONE;
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
float3 calcLight(float3 eyeCoord, float3 normal)
{
	//Variables
	/*float3 n = normalize(mul(normal, mul(modelMatrix,viewMatrix)));
	float3 s = normalize(lightPos - eyeCoord);
	float3 r = -1 * s + 2 * dot(s,n) * n;
	float3 v = -eyeCoord;

	//Ambient light
	float3 ambient = la * ka;

	//Diffuse light
	float3 diffuse = max(dot(s,n), 0) * ld * kd;

	//Specular light
	float3 specular = ls * ks * pow(max(dot(r,v), 0), f);
	
	return (ambient + diffuse + specular);*/

	return float3(1.0f, 1.0f, 1.0f);
}

PSSceneIn VSScene(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix worldViewProjection = mul(viewMatrix, projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = input.Normal;
	output.EyeCoord = mul( float4(input.Pos,1.0), mul(modelMatrix,viewMatrix) );

	return output;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	float4 color = tex2D.Sample(linearSampler, input.UVCoord);
	color.w *= modelAlpha;

	float3 li = calcLight(input.EyeCoord, input.Normal);

	return color;
}

technique10 RenderModelForward
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );

	    SetDepthStencilState( EnableDepth, 0 );
	    SetRasterizerState( rs );
    }  
}