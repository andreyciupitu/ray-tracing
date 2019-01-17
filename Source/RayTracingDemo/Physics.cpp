#include "Physics.h"

namespace Physics
{
	HitInfo Raycast(const Ray &r, std::vector<SceneObject*> &sceneObjects)
	{
		HitInfo nearestHit;
		nearestHit.collider = nullptr;
		float tnear = INFINITY;

		// Test all objects in the scene
		for (auto obj : sceneObjects)
		{
			HitInfo hit;

			// If we hit something
			// test the distance
			if (obj->collider->IntersectRay(r, &hit))
			{
				float t = (hit.hitPoint.x - r.origin.x) / r.direction.x;
				if (t < tnear)
				{
					tnear = t;
					nearestHit = hit;
					nearestHit.collider = obj->collider;
				}
			}
		}

		return nearestHit;
	}
}