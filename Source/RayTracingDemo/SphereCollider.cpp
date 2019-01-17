#include "SphereCollider.h"

#include <Core\Engine.h>
#include <RayTracingDemo\Physics.h>

bool Physics::SphereCollider::IntersectRay(const Ray &r, HitInfo *hit)
{
	float t0, t1;

	// Compute equation coefs
	glm::vec3 L = r.origin - center;
	float a = glm::dot(r.direction, r.direction);
	float b = 2 * glm::dot(r.direction, L);
	float c = glm::dot(L, L) - radius * radius;

	// Solve the equation
	float discr = b * b - 4 * a * c;
	if (discr < 0) 
		return false;
	else if (discr == 0) 
	{
		t0 = t1 = -0.5 * b / a;
	}
	else 
	{
		t0 = -0.5 * (b + sqrt(discr)) / a;
		t1 = -0.5 * (b - sqrt(discr)) / a;
	}

	// Choose positive solution
	if (t0 < 0 && t1 < 0)
	{
		return false;
	}
	else if (t0 < 0)
	{
		t0 = t1;
	}

	// Compute hit details
	hit->hitPoint = r.origin + t0 * r.direction;
	hit->hitNormal = glm::normalize(hit->hitPoint - center);

	return true;
}
