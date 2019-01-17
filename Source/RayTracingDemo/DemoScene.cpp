#include "DemoScene.h"

#include <vector>
#include <iostream>

#include <RayTracingDemo\SceneObject.h>
#include <RayTracingDemo\Physics.h>
#include <RayTracingDemo\SphereCollider.h>
#include <RayTracingDemo\PlaneCollider.h>
#include <Core/Engine.h>

DemoScene::DemoScene()
{
	backgroundColor = glm::vec3(0.972f, 0.949f, 0.549f);
	directionalLight = glm::normalize(glm::vec3(-1.0f, -2.0f, 0.0f));

	rayOffset = 0.01f;
	maxDepth = 5;
}

DemoScene::~DemoScene()
{
	for (auto obj : sceneObjects)
	{
		delete obj->collider;
		delete obj;
	}
}

void DemoScene::Init()
{
	// Camera -----------------------------------------------------------------------
	{
		auto camera = GetSceneCamera();
		camera->SetPositionAndRotation(glm::vec3(15, 2, -20), glm::quat(glm::vec3(-10 * TO_RADIANS, 90 * TO_RADIANS, 0)));
		camera->SetPerspective(60, window->props.aspectRatio, 0.01f, 200);
		camera->Update();
	}

	// Cube mesh -----------------------------------------------------------------
	{
		Mesh* mesh = new Mesh("cube");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		mesh->UseMaterials(false);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Sphere mesh ---------------------------------------------------------------
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		mesh->UseMaterials(false);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Quad mesh -----------------------------------------------------------------
	{
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(-0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec2(0.0f, 1.0f)),
			VertexFormat(glm::vec3(0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec2(1.0f, 1.0f)),
			VertexFormat(glm::vec3(0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec2(1.0f, 0.0f)),
			VertexFormat(glm::vec3(-0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec2(0.0f, 0.0f))
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		meshes["quad"] = new Mesh("quad");
		meshes["quad"]->InitFromData(vertices, indices);
		meshes["quad"]->UseMaterials(false);
	}

	// Floor ---------------------------------------------------------------------
	{
		SceneObject *plane = new SceneObject();
		plane->mesh = meshes["sphere"];

		// Create collider
		Physics::PlaneCollider *collider = new Physics::PlaneCollider(plane);
		collider->center = glm::vec3(0.0f, -4.0f, 0.0f);
		collider->normal = glm::vec3(0.0f, -1.0f, 0.0f);
		plane->collider = collider;

		// Create material
		plane->mat.baseColor = glm::vec4(0.176f, 0.607f, 0.745f, 1.0f);
		plane->mat.ambient = glm::vec4(0.25f);
		plane->mat.diffuse = glm::vec4(0.5f);
		plane->mat.specular = glm::vec4(0.75f);
		plane->mat.reflection = 0.0f;
		plane->mat.transparency = 0.0f;
		plane->mat.shininess = 16;
		
		sceneObjects.push_back(plane);
	}

	// Ballz ---------------------------------------------------------------------
	{
		SceneObject *sphere = new SceneObject();
		sphere->mesh = meshes["sphere"];

		// Create collider
		Physics::SphereCollider *collider = new Physics::SphereCollider(sphere);
		collider->center = glm::vec3(0.0, 0.0, -20.0);
		collider->radius = 4.0f;
		sphere->collider = collider;

		// Create material
		sphere->mat.baseColor = glm::vec4(0.466f, 0.819f, 0.180f, 1.0f);
		sphere->mat.ambient = glm::vec4(0.25f);
		sphere->mat.diffuse = glm::vec4(0.5f);
		sphere->mat.specular = glm::vec4(0.7f);
		sphere->mat.reflection = 1.0f;
		sphere->mat.transparency = 0.5f;
		sphere->mat.refractionIndex = 1.1f;
		sphere->mat.shininess = 32;
		sphere->mat.fresnelAdjust = 0.2f;

		sceneObjects.push_back(sphere);
	} 
	{
		SceneObject *sphere = new SceneObject();
		sphere->mesh = meshes["sphere"];

		// Create collider
		Physics::SphereCollider *collider = new Physics::SphereCollider(sphere);
		collider->center = glm::vec3(5.0, -1.0, -15.0);
		collider->radius = 2.0f;
		sphere->collider = collider;

		// Create material
		sphere->mat.baseColor = glm::vec4(0.898f, 0.062f, 0.2f, 1.0f);
		sphere->mat.ambient = glm::vec4(0.25f);
		sphere->mat.diffuse = glm::vec4(0.5f);
		sphere->mat.specular = glm::vec4(0.25f);
		sphere->mat.reflection = 0.6f;
		sphere->mat.transparency = 0.5f;
		sphere->mat.refractionIndex = 1.1f;
		sphere->mat.shininess = 8;
		sphere->mat.fresnelAdjust = 0.1;

		sceneObjects.push_back(sphere);
	}
	{
		SceneObject *sphere = new SceneObject();
		sphere->mesh = meshes["sphere"];

		// Create collider
		Physics::SphereCollider *collider = new Physics::SphereCollider(sphere);
		collider->center = glm::vec3(5.0f, 1.0f, -25.0f);
		collider->radius = 3.0f;
		sphere->collider = collider;

		// Create material
		sphere->mat.baseColor = glm::vec4(0.635f, 0.188f, 0.811f, 1.0f);
		sphere->mat.ambient = glm::vec4(0.25f);
		sphere->mat.diffuse = glm::vec4(0.5f);
		sphere->mat.specular = glm::vec4(0.5f);
		sphere->mat.reflection = 1.0f;
		sphere->mat.transparency = 0.0f;
		sphere->mat.refractionIndex = 1.1f;
		sphere->mat.shininess = 32;
		sphere->mat.fresnelAdjust = 0.1f;

		sceneObjects.push_back(sphere);
	}
	{
		SceneObject *sphere = new SceneObject();
		sphere->mesh = meshes["sphere"];

		// Create collider
		Physics::SphereCollider *collider = new Physics::SphereCollider(sphere);
		collider->center = glm::vec3(-5.5f, 0.0f, -15.0f);
		collider->radius = 3.0f;
		sphere->collider = collider;

		// Create material
		sphere->mat.baseColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
		sphere->mat.ambient = glm::vec4(0.25f);
		sphere->mat.diffuse = glm::vec4(0.5f);
		sphere->mat.specular = glm::vec4(0.5f);
		sphere->mat.reflection = 1.0f;
		sphere->mat.transparency = 0.0f;
		sphere->mat.refractionIndex = 1.1f;
		sphere->mat.shininess = 16;
		sphere->mat.fresnelAdjust = 0.1f;

		sceneObjects.push_back(sphere);
	}

	Render();
}

void DemoScene::FrameStart()
{
	ClearScreen();
}

void DemoScene::Update(float deltaTimeSeconds)
{
}

void DemoScene::FrameEnd()
{
}

glm::vec3 DemoScene::TraceRay(Physics::Ray r, int depth)
{
	Physics::HitInfo hit = Physics::Raycast(r, sceneObjects);

	// Black if no intersection
	if (!hit.collider)
		return backgroundColor;

	// Init resulting color
	glm::vec3 surfaceColor =  glm::vec3(0.0f); 	
	
	// If the normal and the ray have the same orientation 
	// then we hit the inside of a surface
	bool inside = false;
	if (glm::dot(hit.hitNormal, r.direction) > 0)
	{
		hit.hitNormal = -hit.hitNormal;
		inside = true;
	}

	// Upward bias to be used for the new rays
	// To make sure we don't collide with the same surface again
	SceneObject *hitObject = hit.collider->sceneObject;
	Material mat = hitObject->mat;

	// If it's a diffuse object, no need to raytrace any further
	Physics::Ray lightRay(hit.hitPoint + hit.hitNormal * rayOffset, -directionalLight);
	Physics::HitInfo obscure = Physics::Raycast(lightRay, sceneObjects);

	int transmission = 0;

	if (!obscure.collider)
	{
		transmission = 1;
		surfaceColor += ComputePhongShading(hit, mat, directionalLight);
	}
	else
	{
		surfaceColor += glm::vec3(mat.ambient * mat.baseColor);
	}

	// Ray trace reflections and refractions
	if ((mat.transparency > 0 || mat.reflection > 0) && depth < maxDepth) 
	{
		// Compute the Fresnel effect for the reflection
		float facingRatio = glm::dot(r.direction, hit.hitNormal);
		float fresnelBias = mat.fresnelAdjust;
		float fresnelScale = 1 - mat.fresnelAdjust;
		float fresneleffect = std::max(0.0f, std::min(1.0f, fresnelBias + fresnelScale * pow(1 + facingRatio, 3)));
		
		// Find the reflection color
		glm::vec3 reflectionColor(0.0f);
		if (mat.reflection)
		{
			// Compute the reflected ray
			Physics::Ray reflectedRay;
			reflectedRay.direction = glm::reflect(r.direction, hit.hitNormal);
			glm::normalize(reflectedRay.direction);
			reflectedRay.origin = hit.hitPoint + hit.hitNormal * rayOffset;

			// Trace the reflected ray
			reflectionColor = TraceRay(reflectedRay, depth + 1);
		}

		// if the sphere is also transparent compute refraction ray (transmission)
		glm::vec3 refractionColor(0.0f);
		if (mat.transparency) 
		{
			// Determine the ratio of the refraction indices
			float eta = (inside) ? mat.refractionIndex : 1 / mat.refractionIndex;  
			
			// Compute refracted ray
			Physics::Ray refractedRay;
			refractedRay.direction = glm::refract(r.direction, hit.hitNormal, eta);
			glm::normalize(refractedRay.direction);
			refractedRay.origin = hit.hitPoint - hit.hitNormal * rayOffset;

			// Trace the refracted ray
			refractionColor = TraceRay(refractedRay, depth + 1);
		}

		// Apply the Fresnel effect to mix the colors
		surfaceColor += reflectionColor * fresneleffect * mat.reflection + refractionColor *
						(1 - fresneleffect) * mat.transparency;
	}

	return surfaceColor;
}

void DemoScene::Render()
{
	auto camera = GetSceneCamera();
	glm::ivec2 resolution = window->GetResolution();
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, resolution.x, resolution.y);
	glm::vec3 *image = new glm::vec3[resolution.x * resolution.y];
	glm::vec3 *pixel = image;
	
	// Trace rays
	for (unsigned y = 0; y < resolution.y; y++) 
	{
		for (unsigned x = 0; x < resolution.x; x++, ++pixel)
		{
			// Convert back to world space
			glm::vec3 screenCoords = glm::vec3(x + 0.5f, resolution.y - y + 0.5f, 1.0f);
			glm::vec3 pixelPos = glm::unProject(screenCoords, camera->GetViewMatrix(),
					camera->GetProjectionMatrix(), viewport);

			// Compute the primary rays
			Physics::Ray primaryRay;
			primaryRay.origin = camera->transform->GetWorldPosition();
			primaryRay.direction = glm::normalize(pixelPos - primaryRay.origin);

			// Start ray tracing
			*pixel = TraceRay(primaryRay, 0);
		}
	}

	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << resolution.x << " " << resolution.y << "\n255\n";
	for (unsigned i = 0; i < resolution.x * resolution.y; ++i) 
	{
		ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) <<
			(unsigned char)(std::min(float(1), image[i].y) * 255) <<
			(unsigned char)(std::min(float(1), image[i].z) * 255);
	}
	ofs.close();

	delete[] image;
}

glm::vec3 DemoScene::ComputePhongShading(const Physics::HitInfo &hit, const Material &mat, const glm::vec3 &lightDir)
{
	glm::vec3 ambient = mat.ambient;
	glm::vec3 diffuse(0.0f);
	glm::vec3 specular(0.0f);

	// Compute required vectors
	glm::vec3 L = glm::normalize(-lightDir);
	glm::vec3 V = glm::normalize(GetSceneCamera()->transform->GetWorldPosition() - hit.hitPoint);
	glm::vec3 H = glm::normalize(L + V);

	// If light hits this point compute diffuse and specular components
	bool lightHit = glm::dot(hit.hitNormal, L) > 0;
	if (lightHit)
	{
		diffuse = mat.diffuse * std::max(0.0f, glm::dot(hit.hitNormal, L));
		specular = mat.specular * pow(std::max(glm::dot(hit.hitNormal, H), 0.0f), mat.shininess);
	}

	return (ambient + diffuse + specular) * glm::vec3(mat.baseColor);
}