#pragma once

#include <RayTracingDemo\Physics.h>
#include <Component/SimpleScene.h>

class SceneObject;

class DemoScene : public SimpleScene
{
public:
	DemoScene();
	~DemoScene();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	// Ray tracing algorithm, returns the color that should
	// be assigned to the current pixel
	glm::vec3 TraceRay(Physics::Ray r, int depth);

	// Uses ray tracing to render the scene
	void Render();

	// Computes the phong shading at the given point
	glm::vec3 ComputePhongShading(const Physics::HitInfo &hit, const Material &mat, const glm::vec3 &lightDir);

private:
	// Ray tracing parameters
	float rayOffset;
	int maxDepth;

	// Scene stuff
	glm::vec3 backgroundColor;
	glm::vec3 directionalLight;
	std::vector<SceneObject*> sceneObjects;

	unsigned char *result;
};
