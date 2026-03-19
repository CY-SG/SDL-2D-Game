#include "AnimationClipManager.h"
#include"Texture.h"
#include"Rect.h"
std::shared_ptr<AnimationClip> AnimationClipManager::LoadAnimationClip(const std::string& name, std::shared_ptr<Texture> texture, int n, int i, int j, float duration,bool loop)
{
    if (animationClipMap.count(name))return animationClipMap[name];
    int texture_width = texture->GetWidth();
    int texture_height = texture->GetHeight();
    int width = texture_width / i;
    int height = texture_height / j;
    std::shared_ptr<AnimationClip>animationClip = std::make_shared<AnimationClip>();
        for (int inum = 0; inum < n; inum++) {
            int it = inum / i;
            int jt = inum % i;
            Rect rect(jt * width, it * height, width, height);
            Sprite sprite(texture, rect);
            animationClip.get()->AddFrame(sprite, duration, loop);
        }
    animationClipMap[name] = animationClip;
    return animationClip;
}

std::shared_ptr<AnimationClip> AnimationClipManager::GetAnimationClip(const std::string& name)
{
    return animationClipMap[name];
}

std::shared_ptr<AnimationClip> AnimationClipManager::LoadAnimationClip(const std::string& name, std::vector<std::shared_ptr<Texture>> texture, float duration, bool loop)
{
    if (animationClipMap.count(name))return animationClipMap[name];
    std::shared_ptr<AnimationClip>animationClip = std::make_shared<AnimationClip>();
    for (auto& p : texture) {
        int texture_width = p->GetWidth();
        int texture_height = p->GetHeight();
        Rect rect(0, 0, texture_width, texture_height);
        Sprite sprite(p, rect);
        animationClip.get()->AddFrame(sprite, duration, loop);
    }
    animationClipMap[name] = animationClip;
    return animationClip;
}
