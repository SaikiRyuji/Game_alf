#pragma once
#pragma warning (disable  : 4201)
#pragma warning (disable  : 4127)
#define BUILD_LEVEL_DEBUG		0		//デバッグビルド
#define BUILD_LEVEL_PREVIEW		1		//プレビュービルド
#define BUILD_LEVEL_MASTER		2		//マスタービルド。

#define BUILD_LEVEL		BUILD_LEVEL_PREVIEW

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include<d3d11_1.h>
#include <map>
#include <functional>
#include <algorithm>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//DirectXTKのインクルードファイル。
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include"policy\NonCopyable.h"
#include "physics/Physics.h"
#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include"Engine.h"
#include"graphics\GraphicsEngine.h"
#include"GameObject\GameObjectManager.h"


#include "graphics/Skeleton.h"


#include"graphics\Shader.h"
#include"graphics\GPUBuffer\Vertexbuffer.h"
#include"graphics\GPUBuffer\StructuredBuffer.h"
#include"graphics\GPUView\ShaderResourceView.h"
#include"graphics\GPUView\UnorderedAccessView.h"
#include"graphics\GPUBuffer\Constantbuffer.h"
#include "graphics/SkinModel.h"
#include"timer\GameTime.h"
#include"graphics\Primitive.h"

#include"graphics\GPUBuffer\Indexbuffer.h"

#include"graphics\2D\Sprite.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "Camera/Camera.h"

#include"util\Util.h"
#include"debug\Log.h"

const float FRAME_BUFFER_W = 1280.0f;				//フレームバッファの幅。
const float FRAME_BUFFER_H = 720.0f;				//フレームバッファの高さ。

static const int MAX_BONE = 512;	//!<ボーンの最大数。
