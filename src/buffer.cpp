
#include "buffer.h"
#include "shader.h"
Buffer::Buffer(std::vector<Vertex> vertex, std::vector<uint32_t> indexes) 
{
	//VERTEX	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);

	//INDEXES
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexes.size(), indexes.data(), GL_STATIC_DRAW);


}

void Buffer::draw(const Shader& shader) const 
{
	
	shader.setupAttribs();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Buffer::~Buffer() 
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}