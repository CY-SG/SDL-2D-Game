#pragma once
class Texture {
public:
	virtual ~Texture() = default;
	int GetWidth()const { return width; }
	int GetHeight()const { return height; }
protected:
	int width;
	int height;
};