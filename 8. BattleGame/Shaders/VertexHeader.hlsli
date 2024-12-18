//VertexHeader.hlsli

//VertexLayouts
struct Vertex
{
	float4 pos : POSITION;	
};

struct VertexUV
{
	float4 pos : POSITION;
	float2 uv : UV;	
};

struct VertexColor
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct VertexUVNormal
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

struct VertexUVNormalTangent
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};

struct VertexUVNormalTangentBlend
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float4 indices : BLENDINDICES;
	float4 weights : BLENDWEIGHTS;
};

////////////////////////////////////////////////////
//Vertex Constant Buffer
cbuffer WorldBuffer : register(b0)
{
	matrix world;
}

cbuffer ViewBuffer : register(b1)
{
	matrix view;
	matrix invView;
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix projection;
}

struct Frame
{
	int clip;
	int curFrame;
	float time;
	float scale;
};

struct Motion
{
	float takeTime;
	float tweenTime;
	float runningTime;
	float padding;
	
	Frame cur, next;
};

cbuffer FrameBuffer : register(b3)
{
	Motion motion;
}

Texture2DArray transformMap : register(t0);

matrix SkinWorld(float4 indices, float4 weights)
{
	matrix transform = 0;
	matrix cur, next;
	
	matrix curAnim, nextAnim;
	
	float4 c0, c1, c2, c3;
	float4 n0, n1, n2, n3;
	
	[unroll(4)]
	for (int i = 0; i < 4; i++)
	{
		int clip = motion.cur.clip;
		int curFrame = motion.cur.curFrame;
		
		c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame, clip, 0));
		c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame, clip, 0));
		c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame, clip, 0));
		c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame, clip, 0));
		
		cur = matrix(c0, c1, c2, c3);
		
		n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame + 1, clip, 0));
		n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame + 1, clip, 0));
		n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame + 1, clip, 0));
		n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame + 1, clip, 0));
		
		next = matrix(n0, n1, n2, n3);
		
		curAnim = lerp(cur, next, motion.cur.time);
		
		clip = motion.next.clip;
		curFrame = motion.next.curFrame;
		
		[flatten]
		if (clip > -1)
		{		
			c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame, clip, 0));
			c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame, clip, 0));
			c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame, clip, 0));
			c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame, clip, 0));
		
			cur = matrix(c0, c1, c2, c3);
		
			n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame + 1, clip, 0));
			n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame + 1, clip, 0));
			n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame + 1, clip, 0));
			n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame + 1, clip, 0));
		
			next = matrix(n0, n1, n2, n3);
		
			nextAnim = lerp(cur, next, motion.next.time);
			
			curAnim = lerp(curAnim, nextAnim, motion.tweenTime);
		}
		
		transform += mul(weights[i], curAnim);
	}
	
	return transform;
}