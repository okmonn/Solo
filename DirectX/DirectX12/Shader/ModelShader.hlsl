Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

//���[���h�r���[�v���W�F�N�V����
cbuffer wvp : register(b0)
{
	//���[���h�s��
    float4x4 world;
	//�r���[�s��
    float4x4 view;
    //�v���W�F�N�V�����s��
    float4x4 projection;
     //�E�B���h�E�T�C�Y
    float2 window;
}

//�}�e���A��
cbuffer mat : register(b1)
{
    //��{�F
    float3 diffuse;
    //�e�N�X�`���Ή��t���O
    bool texFlag;
}

//�o��
struct Out
{
    //�V�X�e�����W
    float4 svpos : SV_POSITION;
    //���W
    float4 pos : POSITION;
    //�@��
    float3 normal : NORMAL;
    //uv
    float2 uv : TEXCOORD;
};

//����
struct VSInput
{
    //���W
    float4 pos : POSITION;
    //�@��
    float4 normal : NORMAL;
    //uv
    float2 uv : TEXCOORD;
};

//���_�V�F�[�_
Out VS(VSInput input)
{
    input.pos = mul(world, input.pos);
    input.pos = mul(view, input.pos);
    input.pos = mul(projection, input.pos);

    Out o;
    o.svpos  = input.pos;
    o.pos    = input.pos;
    o.uv     = input.uv;
    o.normal = mul(world, input.normal);

    return o;
}

//�s�N�Z���V�F�[�_
float4 PS(Out o) : SV_TARGET
{
    //�����x�N�g��
    float3 light = normalize(float3(-1.0f, 1.0f, -1.0f));

    //����
    float bright = dot(o.normal, light);

    //�F
    float3 color = (texFlag == true ? tex.Sample(smp, o.uv).rgb : diffuse);

    return float4(color * bright, 1);
}