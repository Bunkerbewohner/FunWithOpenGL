#pragma once

#include <vector>
#include <memory>
#include "Drawable.h"

using IDrawable = std::shared_ptr<Drawable>;

class Renderer
{
private:
	std::vector<IDrawable> objects;

public:
	Renderer();
	~Renderer();

	void Add(IDrawable drawable);
	//Renderer* operator<<(IDrawable drawable);

	void Draw();
};

Renderer& operator<<(Renderer& renderer, IDrawable drawable);
