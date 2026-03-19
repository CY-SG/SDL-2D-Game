#define SDL_MAIN_HANDLED
#include"Engine.h"
#include <iostream>

int main(int argc, char* argv[]){
	Engine* engine = new Engine();
	engine->Run();
}
