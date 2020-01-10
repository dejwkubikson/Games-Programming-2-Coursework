#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Mesh.h"

struct Camera
{
public:
	Camera()
	{
	}

	// Initializing the camera.
	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);

		Mesh* collider = new Mesh();
		collider->updateSphereData(pos, 2);
	}

	// Returns the view projection of the camera.
	inline glm::mat4 GetViewProjection() const
	{
		// View Matrix
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	// Moving the camera forward / backward (when negative amount is set)
	void MoveForward(float amt)
	{
		// Adding amount to current pos vector
		pos += forward * amt;
		
		// Y axis is blocked so that the camera doesn't fly
		pos = glm::vec3(pos.x, 0.0f, pos.z);

		// Updating the sphere collider's position to be same as camera's
		collider.updateSphereData(pos, 3);
	}

	// Moving the camera right / left (when negative amount is set)
	void MoveRight(float amt)
	{
		// Adding amount to current pos vector
		pos += glm::cross(up, forward) * amt;

		// Y axis is blocked so that the camera doesn't fly
		pos = glm::vec3(pos.x, 0.0f, pos.z);

		// Updating the sphere collider's position to be same as camera's
		collider.updateSphereData(pos, 3);
	}

	// Rotates the camera on Y axis (up and down)
	void RotateY(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	// Rotates the camera on X axis (left and right)
	void RotateX(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

	// Returns current camera position
	glm::vec3 getPos()
	{
		return this->pos;
	}

	// Mesh class' sphere is used to check collisions.
	Mesh collider;

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};
