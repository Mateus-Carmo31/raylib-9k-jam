#ifndef CAMERARIG_H_
#define CAMERARIG_H_

#include "raylib.h"

struct CameraRig
{
    CameraRig(Camera2D cam, float decay) : cam(cam), decay(decay), defOffset(cam.offset) {}

    Camera2D cam;

    float trauma {0};
    float decay;
    Vector2 maxShake {40, 25};

    void ApplyTrauma(float amount);
    void Update(float delta);
private:
    Vector2 defOffset;
};

#endif // CAMERARIG_H_
