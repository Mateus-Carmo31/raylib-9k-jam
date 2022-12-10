#ifndef UI_H_
#define UI_H_

#include "tween.hpp"

class MainMenu
{
    char option = 0;
    float fade = 0.0;
    bool creditsOpen = false;
    const char* options[2] = { "START", "CREDITS" };
    Tween transitionTween;

public:
    void Update(float delta);
    void Draw();
};

#endif // UI_H_
