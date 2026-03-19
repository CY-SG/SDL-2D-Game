#include"SDL2/SDL.h"
#include<iostream>
#include<string>

#include "Engine.h"
#include"EngineTime.h"
#include"Render.h"
#include"Window.h"
#include"Time.h"
#include"Input.h"
#include"ResourceManager.h"
#include"Sprite.h"
#include"Entity.h"

#include"SDLPlatform.h"
#include"SDLRender.h"
#include"SDLInput.h"
#include"SDLTime.h"
#include"SDLWindow.h"
#include"SDLTexture.h"
#include"SDLResourceManager.h"

#include"AnimationClip.h"
#include"AnimationClipManager.h"
#include"AnimationFrame.h"
#include"AnimationPlay.h"
#include"AnimationController.h"
#include"AnimationState.h"
#include"AnimationComponent.h"

#include"TransformComponent.h"

#include"Camera2D.h"
#include"CameraSystem.h"

#include"PhysicsSystem.h"
#include"Collider2DComponent.h"
#include"RigidBody2DComponent.h"

#include"PlayerControllerComponent.h"

#include"InitEntity.h"
#include"PrefabManager.h"

#include"World.h"
Engine::Engine()
{

}

Engine::~Engine()
{
}

void Engine::Run()
{
	SDLPlatform::Init();
	SDLWindow* window = new SDLWindow(800, 600, "Engine");
	std::unique_ptr<SDLRender> renderer = std::make_unique<SDLRender>(window);
	EngineTime::Init(new SDLTime());

    //摄像机设置
    std::unique_ptr<Camera2D> mainCamera = std::make_unique<Camera2D>(800, 600);

    std::unique_ptr<SDLResourceManager> resourceManager = std::make_unique<SDLResourceManager>(renderer.get());
    std::unique_ptr<AnimationClipManager> animationClipManager = std::make_unique<AnimationClipManager>();
    World* world = World::Instance();
    world->Initial(std::move(renderer),std::move(mainCamera),std::move(resourceManager), std::move(animationClipManager));
    while (!window->ShouldClose()) {
        window->PollEvents();

        EngineTime::Tick();


        world->Update();

        // Scene / System 更新

    }

    delete window;
}
