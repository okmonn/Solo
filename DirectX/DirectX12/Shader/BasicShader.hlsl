Texture2D<float4> tex : register(t0);
SamplerState      smp : register(s0);

//���[���h�r���[�v���W�F�N�V����
cbuffer wvp : register(b0)
{
	//���[���h�s��
	float4x4 world;
	//�r���[�s��
	float4x4 view;
    //�v���W�F�N�V�����s��
    float4x4 projection;
}

//�摜�f�[�^
cbuffer image : register(b1)
{
    //�E�B���h�E�T�C�Y
    float2 window;
}

//�o��
struct Out
{
	//�V�X�e�����W
	float4 svpos  : SV_POSITION;
	//���W
	float4 pos    : POSITION;
	//uv�l
	float2 uv     : TEXCOORD;
};

//����
struct Input
{
	//���W
	float4 pos : POSITION;
	//uv
	float2 uv  : TEXCOORD;
};

// ���_�V�F�[�_
Out VS(Input input)
{
    //�e�N�X�`���T�C�Y�̎擾
    float2 size = float2(0.0f, 0.0f);
    tex.GetDimensions(size.x, size.y);

    input.pos.xy = float2(-1, 1) + (input.pos.xy / float2((window.x / 2), -(window.y / 2)));
    input.uv = input.uv / size;

    input.pos = mul(world, input.pos);
    input.pos = mul(view, input.pos);
    input.pos = mul(projection, input.pos);

	Out o;
	o.svpos = input.pos;
	o.pos   = input.pos;
	o.uv    = input.uv;

	return o;
}

// �s�N�Z���V�F�[�_
float4 PS(Out o) : SV_TARGET
{
    float4 ps = tex.Sample(smp, o.uv);
    if (ps.a <= 0.0f)
    {
        discard;
    }
        
    return ps;
}