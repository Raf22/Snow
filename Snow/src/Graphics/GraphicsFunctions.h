#pragma once
#include "GraphicsTypes.h"
#include "Camera.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"


bool LoadObj(const char* path, std::vector<glm::vec4>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs); //loads obj file and writes data into vectors, returns false if anything goes wrong

bool LoadMesh(const char* path, Mesh &mesh); //loads mesh
void SetupMesh(Mesh *mesh, Shader &shader); //generates the mesh's vao and vbo and inputs mesh data into them for rendering
Mesh* CreateMesh(const char* path, const char* name); //creates and returns a new mesh with specified name
Mesh* GetMesh(const char* meshName, std::vector<Mesh>&meshList); //finds a mesh in a specificed mesh list
void DestroyMesh(const char* meshName, std::vector<Mesh>&meshList); //destroys a mesh in a specified mesh list

bool LoadTex(const char* path, Tex& tex);
Tex* CreateTex(const char* path, const char* name);
Tex* GetTex(const char* texName, std::vector<Tex>&texList);
void DestroyTex(const char* texName, std::vector<Tex>&texList);

Model* CreateModel(Mesh *mesh, Tex *tex, const char* name);
Model* GetModel(const char* modelName, std::vector<Model>&modelList);
void DestroyModel(const char* modelName, std::vector<Model>&modelList);

void DrawMesh(const Mesh mesh, const Camera camera, Shader shader);			//render function for mesh
void DrawTexturedMesh();	//render function for mesh and texture
void DrawModel();			//render function for model
void DrawPoint();			//render function for point
void DrawAABB();			//render function for AABB
void DrawCircle();			//render function for circle
void DrawText();			//render function for text
