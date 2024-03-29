#pragma once
#include "../Utilities/Matrices.h"
using namespace DirectX;

namespace glitc
{
	class D3DApplication;
	class Camera
	{
	public:
		void Initialize();
		void SetCameraPosition(XMVECTOR& position);
		XMMATRIX& GetWorldMatrix();
		const XMMATRIX& GetWorldMatrix() const;
		const XMMATRIX& GetViewMatrix() const;
		const XMMATRIX& GetProjectionMatrix() const;

		void SetProjectionMatrix(XMMATRIX projectionMatrix);

		const XMVECTOR& GetForwardVector() const;
		const XMVECTOR& GetBackwardsVector() const;
		const XMVECTOR& GetUpwardVector() const;
		const XMVECTOR& GetDownwardsVector() const;
		const XMVECTOR& GetLeftVector() const;
		const XMVECTOR& GetRightVector() const;

		float GetNearZ() const;
		float GetFarZ() const;

		void AdjustPosition(float x, float y, float z);
		void AdjustPosition(XMVECTOR position);
		void AdjustRotation(const XMVECTOR& rotation);
		void AdjustRotation(float x, float y, float z);

		void ResetCamera();
	private:
		XMVECTOR positionVector, rotationVector;
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 rot = {0.0f, 0.0f, 0.0f };
		float roll, pitch, yaw = 0.0f;

		float fovDegrees = 90.0f;
		float fovRadians = XMConvertToRadians(fovDegrees);
		float aspectRatio = 800.0f / 600.0f;
		float nearZ = 0.1f;
		float farZ = 1000.0f;

		XMMATRIX world, view, projection;

		DirectX::XMVECTOR eyePosition = { 0.0f, 0.0f, -2.0f, 0.0f },
					      lookatPos	  =	{ 0.0f, 0.0f,  0.0f, 0.0f },
			              upDirection = { 0.0f, 1.0f,  0.0f, 0.0f };
	private:
		void UpdateViewMatrix();
		const XMVECTOR DEFAULT_FORWARD_VECTOR    =   { 0.0f, 0.0f, 1.0f, 0.0f  };
		const XMVECTOR DEFAULT_BACKWARD_VECTOR   =   { 0.0f, 0.0f, -1.0f, 0.0f };

		const XMVECTOR DEFAULT_UPWARD_VECTOR     =   { 0.0f, 1.0f, 0.0f, 0.0f  };
		const XMVECTOR DEFAULT_DOWNWARD_VECTOR   =   { 0.0f, -1.0f, 0.0f, 0.0f };

		const XMVECTOR DEFAULT_LEFT_VECTOR       =   { -1.0f, 0.0f, 0.0f, 0.0f };
		const XMVECTOR DEFAULT_RIGHT_VECTOR      =   { 1.0f, 0.0f, 0.0f, 0.0f  };

		XMVECTOR vectorForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		XMVECTOR vectorBackward = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
		XMVECTOR vectorUpward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMVECTOR vectorDownward =  XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
		XMVECTOR vectorLeft = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR vectorRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0);
	};
}

