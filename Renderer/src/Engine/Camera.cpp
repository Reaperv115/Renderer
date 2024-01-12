#include "trpch.h"
#include "Camera.h"

void glitc::Camera::Initialize()
{
	positionVector = { 0.0f, 0.0f, -2.0f, 0.0f };
	eyePosition = positionVector;

	world = XMMatrixIdentity();
	view = XMMatrixLookAtLH(eyePosition, lookatPos, upDirection);
	projection = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

void glitc::Camera::SetCameraPosition(XMVECTOR& position)
{
	eyePosition = position;
	positionVector = eyePosition;
}

const XMMATRIX& glitc::Camera::GetWorldMatrix() const
{
	return world;
}

const XMMATRIX& glitc::Camera::GetViewMatrix() const
{
	return view;
}

const XMMATRIX& glitc::Camera::GetProjectionMatrix() const
{
	return projection;
}

const DirectX::XMVECTOR& glitc::Camera::GetForwardVector() const
{
	return vectorForward;
}

const DirectX::XMVECTOR& glitc::Camera::GetBackwardsVector() const
{
	return vectorBackward;
}

const DirectX::XMVECTOR& glitc::Camera::GetUpwardVector() const
{
	return vectorUpward;
}

const DirectX::XMVECTOR& glitc::Camera::GetDownwardsVector() const
{
	return vectorDownward;
}

const DirectX::XMVECTOR& glitc::Camera::GetLeftVector() const
{
	return vectorLeft;
}

const DirectX::XMVECTOR& glitc::Camera::GetRightVector() const
{
	return vectorRight;
}

void glitc::Camera::AdjustPosition(XMVECTOR position)
{
	positionVector += position;
	UpdateViewMatrix();
}

void glitc::Camera::UpdateViewMatrix()
{
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	XMVECTOR cameraTarget = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rotationMatrix);
	cameraTarget += positionVector;
	XMVECTOR upDirection = XMVector3TransformCoord(DEFAULT_UPWARD_VECTOR, rotationMatrix);
	view = XMMatrixLookAtLH(positionVector, cameraTarget, upDirection);
}
