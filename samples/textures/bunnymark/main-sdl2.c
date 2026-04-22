/*******************************************************************************************
*
*   raylib [textures] example - Bunnymark
*
*   Example originally created with raylib 1.6, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <raylib.h>

PSP_MODULE_INFO("bunnymark", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define ATTR_PSP_WIDTH 480
#define ATTR_PSP_HEIGHT 272
#define MAX_BUNNIES    50000
#define MAX_BATCH_ELEMENTS  8192

typedef struct Bunny {
  Vector2 position;
  Vector2 speed;
  Color color;
} Bunny;

int main(void)
{
  const int screenWidth = ATTR_PSP_WIDTH;
  const int screenHeight = ATTR_PSP_HEIGHT;

  InitWindow(screenWidth, screenHeight, "raylib [textures] example - bunnymark");

  int x = screenWidth/2;
  int y = screenHeight/2;

  Rectangle boxB = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f, 6, 6 };

  Texture2D texBunny = LoadTexture("./wabbit_alpha.png");

  Bunny *bunnies = (Bunny *)malloc(MAX_BUNNIES*sizeof(Bunny));

  int bunniesCount = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
  {
    if (IsKeyDown(KEY_UP)) y -= 6;
    if (IsKeyDown(KEY_DOWN)) y += 6;
    if (IsKeyDown(KEY_LEFT)) x -= 6;
    if (IsKeyDown(KEY_RIGHT)) x += 6;

    boxB.x = x - boxB.width/2;
    boxB.y = y - boxB.height/2;

    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      for (int i = 0; i < 100; i++)
      {
        if (bunniesCount < MAX_BUNNIES)
        {
          bunnies[bunniesCount].position.x = boxB.x;
          bunnies[bunniesCount].position.y = boxB.y;
          bunnies[bunniesCount].speed.x = (float)GetRandomValue(-250, 250)/60.0f;
          bunnies[bunniesCount].speed.y = (float)GetRandomValue(-250, 250)/60.0f;
          bunnies[bunniesCount].color = (Color){ GetRandomValue(50, 240),
                             GetRandomValue(80, 240),
                             GetRandomValue(100, 240), 255 };
          bunniesCount++;
        }
      }
    }

    for (int i = 0; i < bunniesCount; i++)
    {
      bunnies[i].position.x += bunnies[i].speed.x;
      bunnies[i].position.y += bunnies[i].speed.y;

      if (((bunnies[i].position.x + texBunny.width/2) > GetScreenWidth()) ||
        ((bunnies[i].position.x + texBunny.width/2) < 0)) bunnies[i].speed.x *= -1;
      if (((bunnies[i].position.y + texBunny.height/2) > GetScreenHeight()) ||
        ((bunnies[i].position.y + texBunny.height/2 - 40) < 0)) bunnies[i].speed.y *= -1;
    }

    BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawRectangleRec(boxB, BLUE);

      for (int i = 0; i < bunniesCount; i++)
      {
        DrawTexture(texBunny, (int)bunnies[i].position.x, (int)bunnies[i].position.y, bunnies[i].color);
      }

      DrawRectangle(0, 0, screenWidth, 40, BLACK);
      DrawText(TextFormat("bunnies: %i", bunniesCount), 120, 15, 10, GREEN);
      DrawText(TextFormat("batched draw calls: %i", 1 + bunniesCount/MAX_BATCH_ELEMENTS), 200, 15, 10, MAROON);

      DrawFPS(10, 10);

    EndDrawing();
  }

  free(bunnies);

  UnloadTexture(texBunny);

  CloseWindow();

  return 0;
}
