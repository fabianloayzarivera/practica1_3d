#pragma once
#include "common.h"
#include <vector>
#include "vertex.h"

class Shader;
class Buffer 
{
private:
	uint32_t vertexBuffer;
	uint32_t indexBuffer;
public:
	Buffer(std::vector<Vertex> v, std::vector<uint32_t> i);
	~Buffer();
	void draw(const Shader& shader) const;
};