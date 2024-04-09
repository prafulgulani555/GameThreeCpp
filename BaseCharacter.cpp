#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollsionRec()
{
    return Rectangle{screenPos.x, screenPos.y, width * scale, height * scale};
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

    // character drawing
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}