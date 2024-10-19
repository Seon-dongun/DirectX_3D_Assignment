#include "Framework.h"
#include "SlideGameScene.h"

SlideGameScene::SlideGameScene()
{
    cubes.push_back(new Cube({ 1,1,1 },L"Textures/Landscape/Box1.png"));
    cubes.back()->SetLocalPosition({ 0,0,0 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box3.png"));
    cubes.back()->SetLocalPosition({ 1,0,0 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box2.png"));
    cubes.back()->SetLocalPosition({ 2,0,0 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box4.png"));
    cubes.back()->SetLocalPosition({ 0,0,-1 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box5.png"));
    cubes.back()->SetLocalPosition({ 1,0,-1 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box6.png"));
    cubes.back()->SetLocalPosition({ 2,0,-1 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box7.png"));
    cubes.back()->SetLocalPosition({ 0,0,-2 });
    cubes.push_back(new Cube({ 1,1,1 }, L"Textures/Landscape/Box8.png"));
    cubes.back()->SetLocalPosition({ 1,0,-2 });

    cubes.push_back(new Cube());
    cubes.back()->SetLocalPosition({ 2,0,-2 });

    for (int i = 0; i < 9; i++)
        loc[i]=i;


    CubeShuffle();
}

SlideGameScene::~SlideGameScene()
{    

}

void SlideGameScene::Update()
{
    if (loc[8] == 8)
        GameClear();

    if (KEY->Down('W'))
    {
        if (cubes[8]->GetLocalPosition().GetZ() + speed < 1)
        {
            cubes[8]->Translate(Vector3(0, 0, speed));
            for (int i = 0; i < 8; i++)
            {
                if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                {
                    cubes[i]->Translate(Vector3(0, 0, -speed));
                    int tmp = loc[8];
                    loc[8] = loc[i];
                    loc[i] = tmp;
                }
            }
        }
    }
    if (KEY->Down('S'))
    {
        if (cubes[8]->GetLocalPosition().GetZ() - speed > -3)
        {
            cubes[8]->Translate(Vector3(0, 0, -speed));
            for (int i=0;i<8;i++)
            {
                if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                {
                    cubes[i]->Translate(Vector3(0, 0, speed));
                    int tmp = loc[8];
                    loc[8] = loc[i];
                    loc[i] = tmp;
                }
            }
        
        }
    }
    if (KEY->Down('A'))
    {
        if (cubes[8]->GetLocalPosition().GetX() - speed > -1) {
            cubes[8]->Translate(Vector3(-speed, 0, 0));
            for (int i = 0; i < 8; i++)
            {
                if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                {
                    cubes[i]->Translate(Vector3(speed, 0, 0));
                    int tmp = loc[8];
                    loc[8] = loc[i];
                    loc[i] = tmp;
                }
            }
        }
    }
    if (KEY->Down('D'))
    {
        if (cubes[8]->GetLocalPosition().GetX() + speed < 3) {
            cubes[8]->Translate(Vector3(speed, 0, 0));
            for (int i = 0; i < 8; i++)
            {
                if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                {
                    cubes[i]->Translate(Vector3(-speed, 0, 0));
                    int tmp = loc[8];
                    loc[8] = loc[i];
                    loc[i] = tmp;
                }
            }
        }
    }


    for (Cube* cube : cubes)
        cube->UpdateWorld();
}

void SlideGameScene::PreRender()
{
}

void SlideGameScene::Render()
{
    for (Cube* cube : cubes)
        cube->Render();
}

void SlideGameScene::PostRender()
{
}

void SlideGameScene::GUIRender()
{
}

void SlideGameScene::CubeShuffle()
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 30; i++) {
        int randDir = rand() % 4;

        switch (randDir)
        {
        case 1:
            if (cubes[8]->GetLocalPosition().GetZ() + speed < 1)
            {
                cubes[8]->Translate(Vector3(0, 0, speed));
                for (int i = 0; i < 8; i++)
                {
                    if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                    {
                        cubes[i]->Translate(Vector3(0, 0, -speed));
                        int tmp = loc[8];
                        loc[8] = loc[i];
                        loc[i] = tmp;
                    }
                }
            }
            break;
        case 2:
            if (cubes[8]->GetLocalPosition().GetZ() - speed > -3)
            {
                cubes[8]->Translate(Vector3(0, 0, -speed));
                for (int i = 0; i < 8; i++)
                {
                    if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                    {
                        cubes[i]->Translate(Vector3(0, 0, speed));
                        int tmp = loc[8];
                        loc[8] = loc[i];
                        loc[i] = tmp;
                    }
                }

            }// 4 5 , 8 2
            break;
        case 3:
            if (cubes[8]->GetLocalPosition().GetX() - speed > -1) {
                cubes[8]->Translate(Vector3(-speed, 0, 0));
                for (int i = 0; i < 8; i++)
                {
                    if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                    {
                        cubes[i]->Translate(Vector3(speed, 0, 0));
                        int tmp = loc[8];
                        loc[8] = loc[i];
                        loc[i] = tmp;
                    }
                }
            }
            break;
        case 4:
            if (KEY->Down('D'))
            {
                if (cubes[8]->GetLocalPosition().GetX() + speed < 3) {
                    cubes[8]->Translate(Vector3(speed, 0, 0));
                    for (int i = 0; i < 8; i++)
                    {
                        if (cubes[8]->GetLocalPosition().GetX() == cubes[i]->GetLocalPosition().GetX() && cubes[8]->GetLocalPosition().GetY() == cubes[i]->GetLocalPosition().GetY() && cubes[8]->GetLocalPosition().GetZ() == cubes[i]->GetLocalPosition().GetZ())
                        {
                            cubes[i]->Translate(Vector3(-speed, 0, 0));
                            int tmp = loc[8];
                            loc[8] = loc[i];
                            loc[i] = tmp;
                        }
                    }
                }
            }
            break;
        }
    }


}

void SlideGameScene::GameClear()
{
    for (int i = 0; i < 9; i++) {
        if (loc[i] != i)
            return;
    }

    KillTimer(hWnd, 0);
    MessageBox(hWnd, L"GameClear", L"GameClear", MB_OK);
    DestroyWindow(hWnd);
}
