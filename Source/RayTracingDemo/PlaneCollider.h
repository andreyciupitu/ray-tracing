#pragma once

#include "Collider.h"
#include <Core\Engine.h>

namespace Physics
{
	class PlaneCollider : public Collider
	{
	public:
		PlaneCollider(SceneObject *obj) : Collider(obj) {}
		virtual ~PlaneCollider() {}

		// Inherited via Collider
		virtual bool IntersectRay(const Ray &r, HitInfo *hit) override;

	public:
		glm::vec3 normal;
		glm::vec3 center;
	};
}