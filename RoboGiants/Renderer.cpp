#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer() : objects()
{
}


Renderer::~Renderer()
{
}

void Renderer::Add(IDrawable drawable)
{
	objects.push_back(drawable);
}

Renderer& operator<<(Renderer& renderer, IDrawable drawable)
{	
	renderer.Add(drawable);
	return renderer;
}

void Renderer::Draw()
{	
	for (auto item : objects)
	{		
		item->Draw();
	}
}