#pragma once
class Texture;
class Rect;
class Sprite;

enum color {
    Red,
    Green,
    Yellow,
    Blue
};
class Render {
public:
    virtual ~Render() = default;

    virtual void BeginFrame() = 0;
    virtual void Clear() = 0;
    virtual void EndFrame() = 0;

    virtual void DrawTexture(Texture* texture, const Rect& src, const Rect& dst) = 0;
    virtual void DrawSprite(const Sprite* sprite, int x, int y, float scale, bool IsRight) = 0;

    virtual void DrawRect(int pos_x, int pos_y, int size_x, int size_y, color rectcolor) = 0;
    virtual void DrawLine(int start_x, int start_y, int end_x, int end_y, color linecolor) = 0;

    virtual void* GetRenderer() = 0;
};