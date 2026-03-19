#pragma once
#include"Render.h"
#include"Rect.h"
class SDLWindow;
class SDL_Renderer;
class SDL_Rect;
class SDLRender :public Render {
public:
    SDLRender(SDLWindow* window);
    ~SDLRender();
    void BeginFrame() override;
    void Clear() override;
    void EndFrame() override;
    void DrawTexture(Texture* texture, const Rect& src, const Rect& dst) override;
    void DrawSprite(const Sprite* sprite, int x, int y, float scale, bool IsRight) override;
    void DrawRect(int pos_x, int pos_y, int size_x, int size_y, color rectcolor) override;
    void DrawLine(int start_x, int start_y, int end_x, int end_y, color linecolor) override;
    void* GetRenderer()override;
private:
    SDL_Rect ToSDLRect(const Rect& rect);
    SDL_Renderer* renderer;
};