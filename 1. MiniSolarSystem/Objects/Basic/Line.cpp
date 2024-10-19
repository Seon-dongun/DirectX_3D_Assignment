#include "Framework.h"

Line::Line(WCHAR ch)
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	if (ch == 'x')
	{
		vertices.emplace_back(WIN_WIDTH,0,0,0,0,0);
		vertices.emplace_back(-WIN_WIDTH, 0, 0, 0, 0, 0);
	}
	else if (ch == 'y')
	{
		vertices.emplace_back(0, WIN_HEIGHT, 0, 0, 0, 0);
		vertices.emplace_back(0, -WIN_HEIGHT, 0, 0, 0, 0);
	}
	else if (ch == 'z')
	{
		vertices.emplace_back(0, 0, 1500, 0, 0, 0);
		vertices.emplace_back(0, 0, -1500, 0, 0, 0);
	}

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexColor), vertices.size());

	worldBuffer = new MatrixBuffer();
}

Line::Line(WCHAR ch, float pos)
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	if (ch == 'x')
	{
		vertices.emplace_back(WIN_WIDTH, 0, pos, 0, 0, 0);
		vertices.emplace_back(-WIN_WIDTH, 0, pos, 0, 0, 0);
	}
	else if (ch == 'y')
	{
		vertices.emplace_back(0, WIN_HEIGHT, pos, 0, 0, 0);
		vertices.emplace_back(0, -WIN_HEIGHT, pos, 0, 0, 0);
	}
	else if (ch == 'z')
	{
		vertices.emplace_back(pos, 0, 1500, 0, 0, 0);
		vertices.emplace_back(pos, 0, -1500, 0, 0, 0);
	}

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexColor), vertices.size());

	worldBuffer = new MatrixBuffer();
}

Line::~Line()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete worldBuffer;
}

void Line::Render()
{
	worldBuffer->SetVS(0);

	vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
}
