#include"LightingObject3d.hlsli"


struct Material
{
	float32_t4 color;
	float32_t4x4 uv;
	float32_t shininess;
};
struct DirectionalLight {
	float32_t4 color;
	float32_t3 direction;
	float intensity;
};

struct PointLight
{
	float32_t4 color;
	float32_t3 position;
	float intensity;
	float radious;
	float decay;
};

struct NowLightTotal
{
	int32_t count;
};

ConstantBuffer<Material>gMaterial :register(b0);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t1);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

Texture2D<float32_t4>gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {

	float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;

	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

	float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

	float32_t3 pTotalSpecular = 0;
	float32_t3 pTotalDffuse = 0;

	//atten 0.5,0.6,0.0
	float32_t atten = 0;
	for (int32_t i = 0; i < gNowLightTotal.count; i++)
	{
		//点光源

		float32_t distance = length(gPointLight[i].position - input.worldPosition);
		float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);


		float32_t3 pLightDirection = normalize(input.worldPosition - gPointLight[i].position);
		float32_t3 pRefrectLight = reflect(pLightDirection, normalize(input.normal));
		float32_t3 pHalfVector = normalize(-pLightDirection + toEye);


		float pNdotL = dot(normalize(input.normal), -normalize(pLightDirection));
		float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
		float pNdotH = dot(normalize(input.normal), pHalfVector);
		float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

		//拡散
		float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		pTotalDffuse = pTotalDffuse + pDiffuse;
		//鏡面
		float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);
		pTotalSpecular = pTotalSpecular + pSpecular;

	}


	output.color.rgb =  pTotalDffuse + pTotalSpecular+ atten;
	//output.color.rgb -= atten;
	output.color.a = gMaterial.color.a * textureColor.a;

	return output;
}