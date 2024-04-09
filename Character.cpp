#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
    };
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
    
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        // normalized so that it doesn't move fast along diagonals
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
}