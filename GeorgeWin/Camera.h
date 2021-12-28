#pragma once
#include <DirectXMath.h>
using namespace DirectX;
const float YAW = 90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.5f;
const float SENSITIVTY = 0.05f;
class Camera
{
public:
	Camera(XMVECTORF32 pos, XMVECTORF32 front);
private:
	XMMATRIX	lookAt;
	XMVECTORF32 Position;
	XMVECTORF32 Front;
	XMVECTORF32 Right;
	XMVECTORF32 WorldUp;
	XMVECTORF32 Target;
	float Yaw;
	float Pitch;
	float MoveMentSpeed;
	float MouseSensitivity;
};