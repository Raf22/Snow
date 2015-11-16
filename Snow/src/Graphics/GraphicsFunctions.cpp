#include "GraphicsFunctions.h"


bool LoadObj(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs) {
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE* file;
	fopen_s(&file, path, "r");
	if (file == nullptr) {
		return false;
	}
	while (1) {
		char lineHeader[256];
		int checkEOF = fscanf_s(file, "%s", lineHeader);
		if (checkEOF == EOF) {
			break;
		}
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < normalIndices.size(); ++i) {
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			out_normals.push_back(normal);
		}
		for (unsigned int i = 0; i < uvIndices.size(); ++i) {
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			out_uvs.push_back(uv);
		}
	}

	fclose(file);
	return true;
}

bool LoadMesh(const char* path, Mesh &mesh) {
	return LoadObj(path, mesh.vertices, mesh.normals, mesh.uvs);
}

void SetupMesh(Mesh &mesh) {
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
	
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices), &mesh.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh.vertices), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mesh.normals), (void*)0);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(mesh.uvs), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh* CreateMesh(const char* path, const char* _name) {
	Mesh* mesh = new Mesh;

	mesh->name = _name;
	LoadMesh(path, *mesh);
	SetupMesh(*mesh);

	return mesh;
}

Mesh* GetMesh(const char* name, std::vector<Mesh>&meshList) {
	for (std::vector<Mesh>::iterator meshIter = meshList.begin(); meshIter != meshList.end(); ++meshIter) {
		if (meshIter->name == name) {
			return &*meshIter;
		} 
	}
	return nullptr;
}

void DestroyMesh(const char* name, std::vector<Mesh>&meshList) {
	for (std::vector<Mesh>::iterator meshIter = meshList.begin(); meshIter != meshList.end(); ++meshIter) {
		if (meshIter->name == name) {
			meshList.erase(meshIter);
			delete &meshIter;
		}
	}
}