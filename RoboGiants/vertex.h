#pragma once

#include <array>
#include <stdint.h>

struct VertexComponent
{
	
};

struct Position : VertexComponent
{
	union
	{
		float values[4];
		struct {
			float x, y, z, w;
		};
	};	

	Position(float x, float y, float z, float w = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

struct Tangent : Position {};
struct Normal : Position {};

struct TexCoord : VertexComponent
{
	union
	{
		float values[2];
		struct {
			float x, y;
		};
	};

	TexCoord(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Color : VertexComponent
{
	union
	{
		uint32_t color;
		struct {
			uint8_t r, g, b, a;
		};
	};

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 1)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

struct Vertex
{
	Position	position;
	Color		color;
	TexCoord	texcoord;
	Normal		normal;
	Tangent		tangent;
};