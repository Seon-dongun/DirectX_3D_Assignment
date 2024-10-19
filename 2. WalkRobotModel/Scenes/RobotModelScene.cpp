#include "Framework.h"
#include "RobotModelScene.h"

RobotModelScene::RobotModelScene()
{

    cubes.push_back(new Cube({ 0.3,0.3,0.3 }));
    cubes.push_back(new Cube({0.6,0.9,0.5}));
    cubes.push_back(new Cube({ 0.2,0.4,0.2 }));
    cubes.push_back(new Cube({ 0.2,0.4,0.2 }));
    cubes.push_back(new Cube({ 0.2,0.4,0.2 }));
    cubes.push_back(new Cube({ 0.2,0.4,0.2 }));

    cubes[1]->SetLocalPosition({0, -0.6, 0});
    cubes[2]->SetLocalPosition({ -0.43, 0.22, 0 });
    cubes[3]->SetLocalPosition({ 0.43, 0.22, 0 });
    cubes[4]->SetLocalPosition({ -0.2, -0.7, 0 });
    cubes[5]->SetLocalPosition({ 0.2, -0.7, 0 });
    
    cubes[2]->SetPivot(Vector3(-0.43, 0.22, 0));
    cubes[3]->SetPivot(Vector3(0.43, 0.22, 0));
    cubes[4]->SetPivot(Vector3(-0.2, 0.3, 0));
    cubes[5]->SetPivot(Vector3(0.2, 0.3, 0));

    cubes[1]->SetParent(cubes[0]);
    cubes[2]->SetParent(cubes[1]);
    cubes[3]->SetParent(cubes[1]);
    cubes[4]->SetParent(cubes[1]);
    cubes[5]->SetParent(cubes[1]);

    XMVECTOR eye = XMVectorSet(3, 3, -3, 0);//Cam Pos
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

RobotModelScene::~RobotModelScene()
{    
    delete viewBuffer;
    delete projectionBuffer;
}

void RobotModelScene::Update()
{
    if (KEY->Press('W'))
    {
        cubes[0]->Translate(Vector3(0, 0, 1) * DELTA);
        cubes[2]->Rotate(Vector3(1, 0, 0) * DELTA);
        cubes[3]->Rotate(Vector3(-1, 0, 0) * DELTA);
        cubes[4]->Rotate(Vector3(1, 0, 0) * DELTA);
        cubes[5]->Rotate(Vector3(-1, 0, 0) * DELTA);

    }
    if (KEY->Press('S')) 
    {
        cubes[0]->Translate(Vector3(0, 0, -1) * DELTA);
        cubes[2]->Rotate(Vector3(-1, 0, 0) * DELTA);
        cubes[3]->Rotate(Vector3(1, 0, 0) * DELTA);
        cubes[4]->Rotate(Vector3(-1, 0, 0) * DELTA);
        cubes[5]->Rotate(Vector3(1, 0, 0) * DELTA);
    }
    if (KEY->Press('A'))
    {
        cubes[0]->Translate(Vector3(-1, 0, 0) * DELTA);
        cubes[2]->Rotate(Vector3(1, 0, 0) * DELTA);
        cubes[3]->Rotate(Vector3(-1, 0, 0) * DELTA);
        cubes[4]->Rotate(Vector3(1, 0, 0) * DELTA);
        cubes[5]->Rotate(Vector3(-1, 0, 0) * DELTA);
    }
    if (KEY->Press('D'))
    {
        cubes[0]->Translate(Vector3(1, 0, 0) * DELTA);
        cubes[2]->Rotate(Vector3(-1, 0, 0) * DELTA);
        cubes[3]->Rotate(Vector3(1, 0, 0) * DELTA);
        cubes[4]->Rotate(Vector3(-1, 0, 0) * DELTA);
        cubes[5]->Rotate(Vector3(1, 0, 0) * DELTA);
    }
    if (KEY->Press('Q'))
        cubes[0]->Translate(Vector3(0, 1, 0) * DELTA);
    if (KEY->Press('E'))
        cubes[0]->Translate(Vector3(0, -1, 0) * DELTA);
    
    if (KEY->Press('T'))
        cubes[0]->Rotate(Vector3(0, 0, 1) * DELTA);
    if (KEY->Press('G'))
        cubes[0]->Rotate(Vector3(0, 0, -1) * DELTA);
    if (KEY->Press('F'))
        cubes[0]->Rotate(Vector3(-1, 0, 0) * DELTA);
    if (KEY->Press('H'))
        cubes[0]->Rotate(Vector3(1, 0, 0) * DELTA);
    if (KEY->Press('R'))
        cubes[0]->Rotate(Vector3(0, 1, 0) * DELTA);
    if (KEY->Press('Y'))
        cubes[0]->Rotate(Vector3(0, -1, 0) * DELTA);

    for (Cube* cube : cubes)
        cube->UpdateWorld();
}

void RobotModelScene::PreRender()
{
}

void RobotModelScene::Render()
{
    for (Cube* cube : cubes)
        cube->Render();
}

void RobotModelScene::PostRender()
{
}

void RobotModelScene::GUIRender()
{
}
