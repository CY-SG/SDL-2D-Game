#pragma once
#include"Window.h"
#include<string>
class SDL_Window;
class SDLWindow :public Window {
public:
	SDLWindow(int w, int h, const std::string& name);
	bool ShouldClose() const override;
	void PollEvents() override;
	~SDLWindow();
	SDL_Window* GetSDLWindow();
private:
	SDL_Window* window = nullptr;
	bool shouldClose = false;
};