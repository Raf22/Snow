#include "GraphicsFunctions.h"


bool LoadObj(const char* path, std::vector<glm::vec4>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs) {
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
				out_vertices.push_back(glm::vec4(vertex, 1.0));
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

void SetupMesh(Mesh *mesh, Shader &shader) {
	glGenVertexArrays(1, &mesh->vao);

	glBindVertexArray(mesh->vao);

	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(glm::vec4), &mesh->vertices[0], GL_STATIC_DRAW);
	shader.inAttrib("vPosition", nullptr);

	glGenBuffers(1, &mesh->nbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->nbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(glm::vec3), &mesh->normals[0], GL_STATIC_DRAW);
	//shader.inAttrib("vNormal", nullptr);

	glGenBuffers(1, &mesh->tbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->tbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->uvs.size() * sizeof(glm::vec2), &mesh->uvs[0], GL_STATIC_DRAW);
	//shader.inAttrib("vTexCoord", nullptr);


}

Mesh* CreateMesh(const char* path, const char* _name) {
	Mesh* mesh = new Mesh;

	mesh->name = _name;
	LoadMesh(path, *mesh);

	return mesh;
}

Mesh* GetMesh(const char* name, std::vector<Mesh>&meshList) {
	Mesh *mesh = nullptr;
	for (std::vector<Mesh>::iterator meshIter = meshList.begin(); meshIter != meshList.end(); ++meshIter) {
		if (meshIter->name == name) {
			mesh = &*meshIter;
		} 
	}
	return mesh;
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
	//calculate mesh LocalTransformMatrix
	glm::mat4 qX = glm::rotate(mesh.rotX, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 qY = glm::rotate(mesh.rotY, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 qZ = glm::rotate(mesh.rotZ, glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 meshTransform = glm::translate(glm::mat4(1.0), mesh.position) * (qZ*qY*qX) * glm::scale(mesh.scale);

	shader.uniformMatrix4("model", meshTransform);
	shader.uniformMatrix4("view", camera.GetViewMatrix());
	shader.uniformMatrix4("projection", glm::perspective(camera.fov, camera.asp, camera.near, camera.far));
		
	glBindVertexArray(mesh.vao);
	shader.bind();
	glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
	glBindVertexArray(0);
}

void DrawTexturedMesh(const Mesh mesh, const Tex tex, const Camera camera, Shader shader) {
	glBindTexture(GL_TEXTURE_2D, tex.texID);
	DrawMesh(mesh, camera, shader);
}

void DrawModel(const Model model, const Camera camera, const Shader shader) {
	DrawTexturedMesh(model.mesh, model.tex, camera, shader);
}