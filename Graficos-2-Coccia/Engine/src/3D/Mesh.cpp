#include "Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Engine;

unsigned int _modelUniform;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures, bool usesSpecularMaps) : Entity()
{
	canDraw = true;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	_usesSpecularMaps = usesSpecularMaps;
	//_shader = shader;
	_renderer = _renderer->_staticRenderer;
	_boundingBox = CalculateBoundingBox();
	verticesBoundingBox = CalculateVerticesBoundingBox(_boundingBox);
	SetUpMesh();
}

Mesh::~Mesh()
{

}

void Mesh::SetUpMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);

	//_modelUniform = glGetUniformLocation(_renderer->GetShader(), "model");
	//glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);	
}

void Mesh::Draw()
{
	_boundingBox = CalculateBoundingBox();
	verticesBoundingBox = CalculateVerticesBoundingBox(_boundingBox);

	if (canDraw)
	{
		// -------------------------------------

	//_modelUniform = glGetUniformLocation(_renderer->GetShader(), "model");
	//_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
	//glUniform1i(glGetUniformLocation(_renderer->GetShader(), "model"), 0);

		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;


		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			string number;
			string name = textures[i].type;
			string matStructName = "material.";

			if (name == "diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "specular")
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if (name == "normal")
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if (name == "height")
				number = std::to_string(heightNr++); // transfer unsigned int to string

			_renderer->SetMesh((matStructName + name + number).c_str(), i, _usesSpecularMaps);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		//_renderer->UpdateModelUniform(_generalMatrix.model, _renderer->GetShader());
		//_renderer->UpdateProgram(_generalMatrix.model);
		// draw mesh
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}
	
}
BoundingBox Mesh::CalculateBoundingBox()
{
	BoundingBox bbox;

	if (vertices.empty()) {
		bbox.min = { 0.0f, 0.0f, 0.0f };
		bbox.max = { 0.0f, 0.0f, 0.0f };
		return bbox;
	}

	bbox.min = vertices[0].Position;
	bbox.max = vertices[0].Position;

	for (const auto& vertex : vertices) {
		bbox.min.x = std::min(bbox.min.x, vertex.Position.x);
		bbox.min.y = std::min(bbox.min.y, vertex.Position.y);
		bbox.min.z = std::min(bbox.min.z, vertex.Position.z);
		bbox.max.x = std::max(bbox.max.x, vertex.Position.x);
		bbox.max.y = std::max(bbox.max.y, vertex.Position.y);
		bbox.max.z = std::max(bbox.max.z, vertex.Position.z);

	}

	return bbox;
}
array<vec3, 8> Mesh::CalculateVerticesBoundingBox(BoundingBox bbox)
{

	std::array<glm::vec3, 8> boundingBoxVertices = { {
		{bbox.min.x, bbox.min.y, bbox.min.z}, // Vértice 0
		{bbox.max.x, bbox.min.y, bbox.min.z}, // Vértice 1
		{bbox.max.x, bbox.max.y, bbox.min.z}, // Vértice 2
		{bbox.min.x, bbox.max.y, bbox.min.z}, // Vértice 3
		{bbox.min.x, bbox.min.y, bbox.max.z}, // Vértice 4
		{bbox.max.x, bbox.min.y, bbox.max.z}, // Vértice 5
		{bbox.max.x, bbox.max.y, bbox.max.z}, // Vértice 6
		{bbox.min.x, bbox.max.y, bbox.max.z}  // Vértice 7
	} };


	return boundingBoxVertices;
}
// --------------------------------
// Virtual Functions:

void Mesh::SetColor(ENTITY_COLOR color) { }
void Mesh::SetColor(float r, float g, float b) { }
void Mesh::TriggerCollision(Entity* other) { }