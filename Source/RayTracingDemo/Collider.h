#pragma once

class SceneObject;

namespace Physics
{
	struct Ray;
	struct HitInfo;

	class Collider
	{
	public:
		Collider(SceneObject *obj) : sceneObject(obj) {}
		virtual ~Collider() {}

		// Computes the intersection of the collider with the ray.
		// Returns the hit details in the hit info, and returns false
		// if the ray doesn't intersect the collider.
		virtual bool IntersectRay(const Ray &r, HitInfo *hit) = 0;

	public:
		SceneObject *sceneObject;
	};
}