#include "PlaneCollider.h"

#include <Core\Engine.h>
#include <RayTracingDemo\Physics.h>

bool Physics::PlaneCollider::IntersectRay(const Ray &r, HitInfo *hit)
{
	float t;

	// Check for intersection point
	float denom = glm::dot(normal, r.direction);
	if (denom > 1e-6) 
	{
		glm::vec3 diff = center - r.origin;
		t = glm::dot(diff, normal) / denom;

		// Compute hit info
		hit->hitNormal = normal;
		hit->hitPoint = r.origin + t * r.direction;
		return (t >= 0);
	}

	return false;
}
