#ifndef SPRITE_H_
#define SPRITE_H_

#include "raylib.h"

class Sprite
{
public:
    Sprite(Texture2D _tex, bool centered) : tex(_tex)
    {
        width = _tex.width;
        height = _tex.height;

        if(centered)
            origin = { width / 2, height / 2 };

        sourceRect = {0, 0, width, height};
        tint = WHITE;
    }

    Sprite(Texture2D _tex, bool centered, float _width, float _height) : tex(_tex)
    {
        width = _width;
        height = _height;

        if(centered)
            origin = { width / 2, height / 2 };

        sourceRect = {0, 0, width, height};
        tint = WHITE;
    }

    void Draw()
    {
        DrawTexturePro(tex,
                       sourceRect,
                       {pos.x, pos.y, width, height},
                       origin,
                       rotation, tint);
    }

    Vector2 pos {0};
    float width, height;
    Vector2 origin {0};
    float rotation {0};
    Rectangle sourceRect;
    Color tint;

private:
    Texture2D tex;
};

#endif // SPRITE_H_
