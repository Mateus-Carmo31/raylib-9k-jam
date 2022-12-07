#include "camerarig.hpp"
#include <algorithm>

void CameraRig::Update(float delta)
{
    if (trauma > 0)
    {
        trauma = std::max(trauma - decay * delta, 0.0f);
        cam.offset.x = defOffset.x + maxShake.x * trauma * trauma * GetRandomValue(-1, 1);
        cam.offset.y = defOffset.y + maxShake.y * trauma * trauma * GetRandomValue(-1, 1);
    }
}


void CameraRig::ApplyTrauma(float amount)
{
    TraceLog(LOG_INFO, "Applied %.2f units to camera trauma.", amount);
    trauma = std::min(trauma + amount, 1.0f);
}
