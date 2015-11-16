#pragma once
#include "GraphicsTypes.h"

bool LoadObj(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs);

bool LoadMesh(const char* path, Mesh &mesh);
void SetupMesh(Mesh &mesh);
Mesh* CreateMesh(const char* path, const char* name);
Mesh* GetMesh(const char* meshName, std::vector<Mesh>&meshList);
void DestroyMesh(const char* meshName, std::vector<Mesh>&meshList);

bool LoadTex(const char* path, Tex& tex);
Tex* CreateTex(const char* path, const char* name);
Tex* GetTex(const char* texName, std::vector<Tex>&texList);
void DestroyTex(const char* texName, std::vector<Tex>&texList);

Model* CreateModel(Mesh *mesh, Tex *tex, const char* name);
Model* GetModel(const char* modelName, std::vector<Model>&modelList);
void DestroyModel(const char* modelName, std::vector<Model>&modelList);

void DrawMesh();
void DrawTexturedMesh();
void DrawModel();
void DrawPoint();
void DrawVector();
void DrawAABB();
void DrawCircle();
void DrawText();
