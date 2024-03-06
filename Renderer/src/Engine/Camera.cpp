#include "trpch.h"
#include "Camera.h"
#include "../WindowCreation/D3DApplication.h"

void glitc::Camera::Initialize()
{
	this->positionVector = { 0.0f, 0.0f, -2.0f, 0.0f };
	this->eyePosition = this->positionVector;

	this->world = XMMatrixIdentity();
	this->view = XMMatrixLookAtLH(this->eyePosition, this->lookatPos, this->upDirection);
	this->projection = XMMatrixPerspectiveFovLH(this->fovRadians, this->aspectRatio, this->nearZ, this->farZ);
}

void glitc::Camera::SetCameraPosition(XMVECTOR& position)
{
	this->eyePosition = position;
	this->positionVector = this->eyePosition;
}

const XMMATRIX& glitc::Camera::GetWorldMatrix() const
{
	return this->world;
}

const XMMATRIX& glitc::Camera::GetViewMatrix() const
{
	return this->view;
}

const XMMATRIX& glitc::Camera::GetProjectionMatrix() const
{
	return this->projection;
}

void glitc::Camera::SetProjectionMatrix(XMMATRIX projectionMatrix)
{
	this->projection = projectionMatrix;
}

const DirectX::XMVECTOR& glitc::Camera::GetForwardVector() const
{
	return this->vectorForward;
}

const DirectX::XMVECTOR& glitc::Camera::GetBackwardsVector() const
{
	return this->vectorBackward;
}

const DirectX::XMVECTOR& glitc::Camera::GetUpwardVector() const
{
	return this->vectorUpward;
}

const DirectX::XMVECTOR& glitc::Camera::GetDownwardsVector() const
{
	return this->vectorDownward;
}

const DirectX::XMVECTOR& glitc::Camera::GetLeftVector() const
{
	return this->vectorLeft;
}

const DirectX::XMVECTOR& glitc::Camera::GetRightVector() const
{
	return this->vectorRight;
}

float glitc::Camera::GetNearZ() const
{
	return this->nearZ;
}

float glitc::Camera::GetFarZ() const
{
	return this->farZ;
}

void glitc::Camera::AdjustPosition(XMVECTOR position)
{
	this->positionVector += position;
	this->UpdateViewMatrix();
}

void glitc::Camera::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->positionVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void glitc::Camera::AdjustRotation(const XMVECTOR& rotation)
{
	this->rotationVector += rotation;
	XMStoreFloat3(&this->rot, this->rotationVector);
	this->UpdateViewMatrix();
}

void glitc::Camera::ResetCamera()
{
	this->positionVector = { 0.0f, 0.0f, -2.0f, 0.0f };
	this->eyePosition = this->positionVector;
	this->rot = { 0.0f, 0.0f, 0.0f };

	//this->world = XMMatrixIdentity();
	//this->view = XMMatrixLookAtLH(this->eyePosition, this->lookatPos, this->upDirection);
	//this->projection = XMMatrixPerspectiveFovLH(this->fovRadians, this->aspectRatio, this->nearZ, this->farZ);
	this->UpdateViewMatrix();
}

void glitc::Camera::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotationVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void glitc::Camera::UpdateViewMatrix()
{
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR cameraTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, rotationMatrix);
	cameraTarget += this->positionVector;
	XMVECTOR upDirection = XMVector3TransformCoord(this->DEFAULT_UPWARD_VECTOR, rotationMatrix);
	this->view = XMMatrixLookAtLH(this->positionVector, cameraTarget, upDirection);

	XMMATRIX vectorrotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vectorForward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vectorrotationMatrix);
	this->vectorBackward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vectorrotationMatrix);
	this->vectorLeft = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vectorrotationMatrix);
	this->vectorRight = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vectorrotationMatrix);
}
