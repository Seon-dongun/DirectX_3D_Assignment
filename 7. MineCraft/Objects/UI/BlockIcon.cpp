#include "Framework.h"

BlockIcon::BlockIcon(wstring image,int id) : Button(image), id(id)
{
}

BlockIcon::~BlockIcon()
{
}

void BlockIcon::PostRender()
{
	Quad::Render();
}
