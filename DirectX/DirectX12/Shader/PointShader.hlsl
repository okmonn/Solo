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

//�o��
struct Out
{
	//�V�X�e�����W
    float4 svpos : SV_POSITION;
	//���W
    float4 pos : POSITION;
    //�F
    float4 color : COLOR;
};

//����
struct Input
{
	//���W
    float4 pos : POSITION;
    //�F
    float4 color : COLOR;
};

// ���_�V�F�[�_
Out VS(Input input)
{
    input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((window.x / 2.0f), -(window.y / 2.0f)));

    //input.pos = mul(world, input.pos);
    //input.pos = mul(view, input.pos);
    //input.pos = mul(projection, input.pos);

    Out o;
    o.svpos = input.pos;
    o.pos   = input.pos;
    o.color = input.color;

    return o;
}

// �s�N�Z���V�F�[�_
float4 PS(Out o) : SV_TARGET
{
    if(o.color.a <= 0.0f)
    {
        discard;
    }

    return o.color;
}
