cbuffer ConstantBuffer : register(b0)
{
    matrix world;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
    float3 Color : COLOR;
};

VS_OUT main(float2 pos : POSITION, float3 color : COLOR)
{
    VS_OUT output;
    float4 local_pos = float4(pos.x, pos.y, 0.0f, 1.0f);
    output.Pos = mul(local_pos, world);
    output.Color = color;
    return output;
}



