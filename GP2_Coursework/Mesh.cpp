#include "Mesh.h"

void Mesh::init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	initModel(model);
}

void Mesh::initModel(const IndexedModel& model)
{
	drawCount = model.indices.size();

	// Generating a vertex array and storing it in VAO
	glGenVertexArrays(1, &vertexArrayObject);
	// Binding the VAO
	glBindVertexArray(vertexArrayObject);

	// Generating buffers based on array of buffers
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	// Telling OpenGL what type of data the buffer is and passing it (position)
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);
	// Moving the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Telling OpenGL what type of data the buffer is and passing it (texture coords)
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// Unbinding the VAO
	glBindVertexArray(0);
}

Mesh::Mesh()
{
	drawCount = NULL;
}

void Mesh::loadModel(const std::string& filename)
{
	// Loading the model by file name
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initModel(model);
	// Creating sphere collider for the model
	Sphere meshSphere();
}

Mesh::~Mesh()
{
	// Deleting vertex array
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::draw()
{
	// Binding the vertex array
	glBindVertexArray(vertexArrayObject);
	// Drawing elements
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::updateSphereData(glm::vec3 pos, float radius)
{
	// Updating collider's position and radius
	meshSphere.SetPos(pos);
	meshSphere.SetRadius(radius);
}

