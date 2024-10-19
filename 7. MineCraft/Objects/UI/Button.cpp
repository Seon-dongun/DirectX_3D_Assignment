#include "Framework.h"

Button::Button()
{
}

Button::Button(wstring textureFile) : Quad(textureFile)
{
}

void Button::Update()
{
    if (!IsActive()) return;

    if (IsContainPos(mousePos))
    {
        if (KEY->Down(VK_LBUTTON))
            isDownCheck = true;

        if (KEY->Press(VK_LBUTTON))
            state = DOWN;
        else
            state = OVER;

        if (isDownCheck && KEY->Up(VK_LBUTTON))
        {
            if (event)
                event();

            if (paramEvent)
                paramEvent(object);

            isDownCheck = false;
        }
    }
    else
    {
        state = NONE;

        if (KEY->Up(VK_LBUTTON))
            isDownCheck = false;
    }
    
    switch (state)
    {
    case Button::NONE:
        material->GetBuffer()->diffuse = NONE_COLOR;
        break;
    case Button::DOWN:
        material->GetBuffer()->diffuse = DOWN_COLOR;
        break;
    case Button::OVER:
        material->GetBuffer()->diffuse = OVER_COLOR;
        break;
    }

    UpdateWorld();
}