#pragma once

#include <Core/Engine.h>
#include <RayTracingDemo\SceneObject.h>

namespace Physics
{
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;

		Ray() {}
		Ray(glm::vec3 origin, glm::vec3 d) : origin(origin), direction(d) {}
	};

	struct HitInfo
	{
		glm::vec3 hitPoint;
		glm::vec3 hitNormal;
		Collider *collider;

		HitInfo() {}
		HitInfo(glm::vec3 point, glm::vec3 norm) : hitPoint(point), hitNormal(norm) {}
	};

	// Cast the ray and returns the first hit, if any.
	HitInfo Raycast(const Ray &r, std::vector<SceneObject*> &sceneObjects);
}