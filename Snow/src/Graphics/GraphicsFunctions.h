#pragma once
#include "GraphicsTypes.h"

bool LoadObj(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs);

bool LoadMesh(const char* path, Mesh &mesh);
void SetupMesh(Mesh &mesh);
Mesh* CreateMesh(const char* path, const char* name);
Mesh* GetMesh(const char* meshName, std::vector<Mesh>&meshList);
void DestroyMesh(const char* meshName, std::vector<Mesh>&meshList);

bool LoadTex();
Tex* CreateTex();
Tex* GetTex(const char* texName);
void DestroyTex(const char* texName);

void DrawMesh();
void DrawTexturedMesh();
void DrawPoint();
void DrawVector();
void DrawAABB();
void DrawCircle();
void DrawText();
