#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
	float FovY = 0.0f;
	float AspectRatio = 1.0f;
	float NearZ = 0.1f;
	float FarZ = 1000.0f;
	float NearWindowHeight = 0.0f;
	float FarWindowHeight = 0.0f;
	float Width = 0.0f;
	float Height = 0.0f;


	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Up = { 0.0f, 1.0f, 0.0f };
	glm::vec3 Right = { 1.0f, 0.0f, 0.0f };
	glm::vec3 Look = { 0.0f, 0.0f, 1.0f };

	glm::mat4x4 View = glm::mat4{1.f};
	glm::mat4x4 Proj = glm::mat4{1.f};

public:

	bool ViewDirty = true;

	glm::vec3 GetPosition()const;

	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& v);

	float GetNearZ()const;
	float GetFarZ()const;
	float GetAspect()const;
	float GetFovY() const;
	float GetFovX() const;

	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;

	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;

	void SetLens(float InFOV, float InWidth, float InHeight, float InzNear, float InzFar);

	void LookAt(glm::vec3 pos,
		glm::vec3 target,
		glm::vec3 worldUp);

	void LookAt(const glm::vec3& pos,
		const glm::vec3& target,
		const glm::vec3& up);

	glm::mat4x4 GetView()const;
	glm::mat4x4 GetProj()const;

	glm::mat4x4 GetView4x4f()const;
	glm::mat4x4 GetProj4x4f()const;

	/// <summary>
	/// Position +=  d * Right
	/// </summary>
	/// <param name="d"></param>
	void Strafe(float d);

	/// <summary>
	/// Position +=  d * Look
	/// </summary>
	/// <param name="d"></param>
	void Walk(float d);

	void Pitch(float angle);
	void RotateY(float angle);

	/// <summary>
	/// todo: replace this with input system, and handle input in player controller
	/// </summary>
	/// <param name="DeltaTime"></param>
	void Update(const float& DeltaTime);

	void UpdateViewMatrix();
	void UpdateFrustum();
};