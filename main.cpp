#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
// #include "BaseCharacter.h"

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tilesets/worldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};


    Prop props[2] {
        Prop {Vector2{300.f, 400.f}, LoadTexture("nature_tilesets/Rock.png")},
        Prop {Vector2{400.f, 200.f}, LoadTexture("nature_tilesets/Log.png")}
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // map drawing
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the props 
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        // check prop player collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollsionRec()))
            {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}