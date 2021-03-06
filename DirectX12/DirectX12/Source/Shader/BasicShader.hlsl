Texture2D<float4> tex : register(t0);
SamplerState      smp : register(s0);

//ワールドビュープロジェクション
cbuffer wvp : register(b0)
{
	//ワールド行列
	float4x4 world;
	//ビュー行列
	float4x4 view;
    //プロジェクション行列
    float4x4 projection;
     //ウィンドウサイズ
    float2 window;
}

//出力
struct Out
{
	//システム座標
	float4 svpos  : SV_POSITION;
	//座標
	float4 pos    : POSITION;
	//uv値
	float2 uv     : TEXCOORD;
    //α
    float alpha   : ALPHA;
};

//入力
struct Input
{
	//座標
	float4 pos  : POSITION;
	//uv
	float2 uv   : TEXCOORD;
    //色
    float alpha : ALPHA;
};

// 頂点シェーダ
Out VS(Input input)
{
    //テクスチャサイズの取得
    float2 size = float2(0.0f, 0.0f);
    tex.GetDimensions(size.x, size.y);

    input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((window.x / 2.0f), -(window.y / 2.0f)));
    input.uv = input.uv / size;
    input.alpha = (input.alpha > 1.0f) ? 1.0f : input.alpha;

    //input.pos = mul(world, input.pos);
    //input.pos = mul(view, input.pos);
    //input.pos = mul(projection, input.pos);

	Out o;
	o.svpos = input.pos;
	o.pos   = input.pos;
	o.uv    = input.uv;
    o.alpha = input.alpha;

	return o;
}

// ピクセルシェーダ
float4 PS(Out o) : SV_TARGET
{
    float4 ps = tex.Sample(smp, o.uv);
    ps.a *= o.alpha;
    if (ps.a <= 0.0f)
    {
        discard;
    }
    
    return ps;
}
