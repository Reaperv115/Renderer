#pragma once
#include "../Utilities/Matrices.h"
using namespace DirectX;

namespace glitc
{
	class Camera
	{
	public:
		void Initialize();
		void SetCameraPosition(XMVECTOR& position);
		const XMMATRIX& GetWorldMatrix() const;
		const XMMATRIX& GetViewMatrix() const;
		const XMMATRIX& GetProjectionMatrix() const;

		const XMVECTOR& GetForwardVector() const;
		const XMVECTOR& GetBackwardsVector() const;
		const XMVECTOR& GetUpwardVector() const;
		const XMVECTOR& GetDownwardsVector() const;
		const XMVECTOR& GetLeftVector() const;
		const XMVECTOR& GetRightVector() const;

		void AdjustPosition(XMVECTOR position);
	private:
		XMVECTOR positionVector;
		XMFLOAT3 pos, rot = {0.0f, 0.0f, 0.0f};

		float fovDegrees = 90.0f;
		float fovRadians = XMConvertToRadians(fovDegrees);
		float aspectRatio = 800.0f / 600.0f;
		float nearZ = 0.1f;
		float farZ = 1000.0f;

		XMMATRIX world, view, projection;

		DirectX::XMVECTOR eyePosition = { 0.0f, 0.0f, -2.0f, 0.0f },
					      lookatPos = { 0.0f, 0.0f, 0.0f, 0.0f },
			              upDirection = { 0.0f, 1.0f, 0.0f, 0.0f };
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

