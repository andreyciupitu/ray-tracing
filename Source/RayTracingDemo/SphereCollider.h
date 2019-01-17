#pragma once

#include "Collider.h"
#include <Core\Engine.h>

namespace Physics
{
	class SphereCollider : public Collider
	{
	public:
		SphereCollider(SceneObject *obj) : Collider(obj), center(glm::vec3(0)), radius(0) {}
		virtual ~SphereCollider() {}

		// Inherited via Collider
		virtual bool IntersectRay(const Ray &r, HitInfo *hit) override;

	public:
		glm::vec3 center;
		float radius;
	};
}