﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY Keyboard::Get()
#define DELTA Timer::Get()->GetElapsedTime()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <ctime>    // time

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef XMVECTOR Vector4;
typedef XMFLOAT4X4 Float4x4;

//Framework Header
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"

#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"

#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"

#include "Framework/Math/Vector3.h"
#include "Framework/Math/Transform.h"

#include "Framework/Environment/Environment.h"

//Obejct Header
#include "Objects/Basic/Cube.h"

//Scene
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;