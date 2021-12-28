struct vsout
{
    float4 color : Color;
    float4 pos : SV_Position;

};

vsout main(float3 pos : Position,float2 color:Color)
{
    vsout vso;
    vso.color = float4(color,1.0f,1.0f);
    vso.pos = float4(pos.x, pos.y-0.7f, pos.z, 1.0f);
    return vso;
}