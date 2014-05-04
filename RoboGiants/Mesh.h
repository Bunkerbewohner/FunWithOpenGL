#pragma once
#include "Drawable.h"
#include <vector>
#include "vertex.h"
#include <gl/GL.h>

using Vertices = std::vector<Vertex>;

class Mesh : public Drawable
{
	Vertices vertices;
	bool built;
	GLuint buffer;

	GLuint BuildBuffer();
	void UpdateBuffer();

public:
	Mesh();
	~Mesh();

	void Draw();	
};

