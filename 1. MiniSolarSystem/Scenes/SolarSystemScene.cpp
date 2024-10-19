#include "Framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
    cubes.push_back(new Cube({ 3,3,3 },{1,0,0}));
    cubes.push_back(new Cube({ 1,1,1 },{0,0,1}));
    cubes.push_back(new Cube({0.4,0.4,0.4},{0.2,0.2,0.2}));
    cubes[1]->SetLocalPosition({ 7,0,0 });
    cubes[2]->SetLocalPosition({1.5,0,0});
    cubes[1]->SetParent(cubes[0]);
    cubes[2]->SetParent(cubes[1]);

    lines.push_back(new Line('x'));
    lines.push_back(new Line('y'));
    lines.push_back(new Line('z'));


    for (int i = 0; i < 100; i++) {
        xz.push_back(new Line('x', 1 + i * 1));
        xz.push_back(new Line('x', -1 + (i*-1)));

        xz.push_back(new Line('z', 1 + i * 1));
        xz.push_back(new Line('z', -1 + (i * -1)));
    }

    XMVECTOR eye = XMVectorSet(3, 15, -15, 0);//Cam Pos
    XMVECTOR focus = XMVectorSet(0, 0, 0, 0);//Cam Look at Pos
    XMVECTOR up = XMVectorSet(0, 1, 0, 0);//Cam Up Vector

    Matrix view = XMMatrixLookAtLH(eye, focus, up);

    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        (float)WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

    viewBuffer = new MatrixBuffer();
    projectionBuffer = new MatrixBuffer();

    viewBuffer->Set(view);
    viewBuffer->SetVS(1);

    projectionBuffer->Set(projection);
    projectionBuffer->SetVS(2);
}

SolarSystemScene::~SolarSystemScene()
{    
    delete viewBuffer;
    delete projectionBuffer;
}

void SolarSystemScene::Update()
{
    if (KEY->Press('W'))
        cubes[0]->Translate(Vector3(0,0,1)*DELTA);
    if (KEY->Press('S'))
        cubes[0]->Translate(Vector3(0, 0, -1) * DELTA);
    if (KEY->Press('A'))
        cubes[0]->Translate(Vector3(-1, 0, 0) * DELTA);
    if (KEY->Press('D'))
        cubes[0]->Translate(Vector3(1, 0, 0) * DELTA);
    if (KEY->Press('Q'))
        cubes[0]->Translate(Vector3(0, 1, 0) * DELTA);
    if (KEY->Press('E'))
        cubes[0]->Translate(Vector3(0, -1, 0) * DELTA);

    if (KEY->Press('T'))
        cubes[0]->Rotate(Vector3(0, 0, 1) * DELTA);
    if (KEY->Press('G'))
        cubes[0]->Rotate(Vector3(0, 0, -1) * DELTA);
    if (KEY->Press('Y'))
        cubes[0]->Rotate(Vector3(-1, 0, 0) * DELTA);
    if (KEY->Press('H'))
        cubes[0]->Rotate(Vector3(1, 0, 0) * DELTA);
    if (KEY->Press('U'))
        cubes[0]->Rotate(Vector3(0, 1, 0) * DELTA);
    if (KEY->Press('J'))
        cubes[0]->Rotate(Vector3(0, -1, 0) * DELTA);

    for (Cube* cube : cubes)
        cube->UpdateWorld();

}

void SolarSystemScene::PreRender()
{
}


void SolarSystemScene::Render()
{
    for (Cube* cube : cubes)
        cube->Render();

    for (Line* line : lines)
        line->Render();

    for (Line* line : xz)
        line->Render();
}

void SolarSystemScene::PostRender()
{
}

void SolarSystemScene::GUIRender()
{
}
