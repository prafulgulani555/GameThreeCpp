#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollsionRec()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningtime += deltaTime;
    if (runningtime >= updateTime)
    {
        frame++;
        runningtime = 0.f;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + velocity
        // normalized so that it doesn't move fast along diagonals
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // character drawing
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}