#pragma once

#include <memory>

#include <RayTracingDemo\Collider.h>

class SceneObject
{
public:
	SceneObject() {}
	virtual ~SceneObject() {}

public:
	Transform transform;
	Material mat;
	Mesh *mesh;
	Physics::Collider *collider;
};