#include "GraphicsFunctions.h"


bool LoadObj(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs) {
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::ifstream file(path);
	if(!file) {
		return false;
	}
	char lineBuffer[256];
	while (file.getline(lineBuffer, 256)) {
		switch(lineBuffer[0]) {
		case 'v':
			switch(lineBuffer[1]) {
			case 'n':{
				glm::vec3 normal;
				sscanf_s(lineBuffer, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
				break;
			case 't':{
				glm::vec2 uv;
				sscanf_s(lineBuffer, "vt %f %f", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
				break;
			case ' ':{
				glm::vec3 vertex;
				sscanf_s(lineBuffer, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
				break;
			}
			break;
		case 'f':
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = sscanf_s(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
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
			break;
		}
	}
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mesh.normals), (void*)0);
	//
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(mesh.uvs), (void*)0);

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

void DrawMesh(const Mesh mesh, const Camera camera, Shader shader) {

	shader.bind();
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
	shader.unbind();
	glBindVertexArray(0);
}