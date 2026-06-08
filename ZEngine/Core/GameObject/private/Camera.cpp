#include "../public/Camera.h"
#include <Windows.h>

glm::vec3 Camera::GetPosition() const
{
	return Position;
}

void Camera::SetPosition(float x, float y, float z)
{
	Position = { x,y,z };
}

void Camera::SetPosition(const glm::vec3& v)
{
	Position = v;
}

float Camera::GetNearZ() const
{
	return NearZ;
}

float Camera::GetFarZ() const
{
	return FarZ;
}

float Camera::GetAspect() const
{
	return AspectRatio;
}

float Camera::GetFovY() const
{
	return FovY;
}

float Camera::GetFovX() const
{
	float halfWidth = 0.5f * GetNearWindowWidth();;
	return 2.0f * glm::atan(halfWidth / NearZ);
}

float Camera::GetNearWindowWidth() const
{
	return AspectRatio * GetNearWindowHeight();
}

float Camera::GetNearWindowHeight() const
{
	return this->NearWindowHeight;
}

float Camera::GetFarWindowWidth() const
{
	return GetFarWindowHeight() * AspectRatio;
}

float Camera::GetFarWindowHeight() const
{
	return this->FarWindowHeight;
}

void Camera::SetLens(float InFOV, float InWidth, float InHeight, float InzNear, float InzFar)
{
	FovY = InFOV;
	AspectRatio = InWidth / InHeight;
	NearZ = InzNear;
	FarZ = InzFar;
	Width = InWidth;
	Height = InHeight;

	NearWindowHeight = 2.0f * NearZ * glm::tan(0.5f * FovY);
	FarWindowHeight = 2.0f * FarZ * glm::tan(0.5f * FovY);

	Proj = glm::perspectiveFovLH(FovY, Width, Height, NearZ, FarZ);


}

void Camera::LookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp)
{

}

void Camera::LookAt(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
{
}

glm::mat4x4 Camera::GetView() const
{
	return View;
}

glm::mat4x4 Camera::GetProj() const
{
	return Proj;
}

glm::mat4x4 Camera::GetView4x4f() const
{
	return View;
}

glm::mat4x4 Camera::GetProj4x4f() const
{
	return Proj;
}

void Camera::Strafe(float d)
{
	glm::vec3 scale = glm::vec3{ d };

	Position = scale * Right + Position;

	ViewDirty = true;

}

void Camera::Walk(float d)
{
	glm::vec3 scale = glm::vec3{ d };

	Position = scale * Look + Position;

	ViewDirty = true;

}

void Camera::Pitch(float angle)
{
	glm::mat3x3 R = glm::mat3x3{glm::angleAxis(angle, Right)};

	Up =  Up * R;
	Look = Look *R;
	ViewDirty = true;

}

void Camera::RotateY(float angle)
{
	glm::mat3x3 R = glm::mat3x3{ glm::angleAxis(angle, glm::vec3{0.f, 1.f,0.f}) };
	Right = Right  * R;
	Look = Look * R;
	Up = Up * R;

	ViewDirty = true;

}

void Camera::Update(const float& DeltaTime)
{
	if (GetAsyncKeyState('W') & 0x8000)
		Walk(10.0f * DeltaTime);
	if (GetAsyncKeyState('S') & 0x8000)
		Walk(-10.0f * DeltaTime);
	if (GetAsyncKeyState('A') & 0x8000)
		Strafe(-10.0f * DeltaTime);
	if (GetAsyncKeyState('D') & 0x8000)
		Strafe(10.0f * DeltaTime);
	UpdateViewMatrix();
	UpdateFrustum();
}

void Camera::UpdateViewMatrix()
{

	if (ViewDirty) {
		glm::vec3 R = Right;
		glm::vec3 U = Up;
		glm::vec3 L = Look;
		glm::vec3 P = Position;

		L = glm::normalize(L);
		U = glm::normalize(glm::cross(L, R));
		R = glm::cross(U, L);

		float x = -glm::dot(P, R);
		float y = -glm::dot(P, U);
		float z = -glm::dot(P, L);

		Right = R;
		Up = U;
		Look = L;
		

		View[0][0] = Right.x;
		View[0][1] = Right.y;
		View[0][2] = Right.z;
		View[0][3] = x;

		View[1][0] = Up.x;
		View[1][1] = Up.y;
		View[1][2] = Up.z;
		View[1][3] = y;

		View[2][0] = Look.x;
		View[2][1] = Look.y;
		View[2][2] = Look.z;
		View[2][3] = z;

		View[3][0] = 0.0f;
		View[3][1] = 0.0f;
		View[3][2] = 0.0f;
		View[3][3] = 1.0f;

		ViewDirty = false;
	}
}

void Camera::UpdateFrustum()
{

	//DirectX::BoundingFrustum::CreateFromMatrix(this->mFrustum, GetProj(), false);
}
