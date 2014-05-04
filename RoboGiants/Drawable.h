#pragma once

#include <iostream>

class Drawable
{
public:	
	virtual ~Drawable();
	virtual void Draw() = 0;
};

class Placeholder : public Drawable
{
public:
	Placeholder() {}
	~Placeholder() {}

	void Draw() {
		std::cout << "Draw placeholder\n";
	}
};