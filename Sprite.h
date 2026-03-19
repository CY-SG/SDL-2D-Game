#pragma once
#include<memory>
#include"Rect.h"
class Texture;
class Rect;
class Sprite {
public:
	Sprite(std::shared_ptr<Texture>texture, const Rect& rect):
		texture(texture),rect(rect){}
	Texture* GetTexture() const { return texture.get(); }
	const Rect& GetRect() const { return rect; }
private:
	std::shared_ptr<Texture> texture;
	Rect rect;
};