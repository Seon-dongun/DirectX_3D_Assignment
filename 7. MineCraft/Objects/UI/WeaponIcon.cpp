#include "Framework.h"
#include "WeaponIcon.h"

WeaponIcon::WeaponIcon(WeaponData data) : data(data)
{
	material->SetDiffuseMap(ToWString(data.uiImage));
}

WeaponIcon::~WeaponIcon()
{
}

void WeaponIcon::PostRender()
{
	Quad::Render();
}
