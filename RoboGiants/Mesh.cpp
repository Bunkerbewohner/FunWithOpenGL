#include "stdafx.h"
#include "Mesh.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "opengl4.h"
#include "lib/glcorearb.h"

Mesh::Mesh() : vertices(), built(false), buffer(0)
{
}


Mesh::~Mesh()
{
}

GLuint Mesh::BuildBuffer()
{
	GL::GenBuffer(1, &buffer);
	GL::BindBuffer(GL_ARRAY_BUFFER, buffer);
	return 0;
}

void Mesh::UpdateBuffer()
{
	if (buffer > 0) GL::InvalidateBuffer(buffer);	
	buffer = BuildBuffer();
	built = true;
}

void Mesh::Draw()
{
	if (!built) UpdateBuffer();
}