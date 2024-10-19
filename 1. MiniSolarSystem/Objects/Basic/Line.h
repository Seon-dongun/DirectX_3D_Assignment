#pragma once
class Line : public Transform
{
public:
	Line(WCHAR ch);
	Line(WCHAR ch, float pos);
	~Line();

	void Render();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	MatrixBuffer* worldBuffer;

	vector<VertexColor> vertices;
};