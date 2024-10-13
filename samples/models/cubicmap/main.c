/*******************************************************************************************
*
*   raylib [models] example - Cubicmap loading and drawing
*
*   Example originally created with raylib 1.8, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <raylib.h>


PSP_MODULE_INFO("cubicmap", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define ATTR_PSP_WIDTH 480
#define ATTR_PSP_HEIGHT 272

SceCtrlData pad;


int flag=1;

void updateController()
{
    sceCtrlReadBufferPositive(&pad, 1);

    if (pad.Buttons != 0)
    {
        if (pad.Buttons & PSP_CTRL_SQUARE)
        {
            TraceLog(LOG_INFO,"Square pressed \n");
        }
        
        if (pad.Buttons & PSP_CTRL_TRIANGLE)
        {
            TraceLog(LOG_INFO,"Triangle pressed \n");
        } 
        
        if (pad.Buttons & PSP_CTRL_CIRCLE)
        {
            TraceLog(LOG_INFO,"Cicle pressed \n");
        } 
        
        if (pad.Buttons & PSP_CTRL_CROSS)
        {
            TraceLog(LOG_INFO,"Cross pressed \n");
            flag=0;
        } 

        if (pad.Buttons & PSP_CTRL_UP)
        {
            TraceLog(LOG_INFO,"Up pressed \n");
        } 
        
        if (pad.Buttons & PSP_CTRL_DOWN)
        {
            TraceLog(LOG_INFO,"Down pressed \n");
        } 
        
        if (pad.Buttons & PSP_CTRL_LEFT)
        {
            TraceLog(LOG_INFO,"Left pressed \n");
        } 
        
        if (pad.Buttons & PSP_CTRL_RIGHT)
        {
            TraceLog(LOG_INFO,"Right pressed \n");
        }      

        if (pad.Buttons & PSP_CTRL_START)
        {
            TraceLog(LOG_INFO,"Start pressed \n");
        }
        
        if (pad.Buttons & PSP_CTRL_SELECT)
        {
            TraceLog(LOG_INFO,"Select pressed \n");
        }
        
        if (pad.Buttons & PSP_CTRL_LTRIGGER)
        {
            TraceLog(LOG_INFO,"L-trigger pressed \n");
        }
        
        if (pad.Buttons & PSP_CTRL_RTRIGGER)
        {
            TraceLog(LOG_INFO,"R-trigger pressed \n");
        }      
    }

}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = ATTR_PSP_WIDTH;
    const int screenHeight = ATTR_PSP_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - cubesmap loading and drawing");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 16.0f, 14.0f, 16.0f };     // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    Image image = LoadImage("host0:/models/cubicmap/cubicmap.png");      // Load cubicmap image (RAM)
    Texture2D cubicmap = LoadTextureFromImage(image);       // Convert image to texture to display (VRAM)

    Mesh mesh = GenMeshCubicmap(image, (Vector3){ 1.0f, 1.0f, 1.0f });
    Model model = LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("host0:/models/cubicmap/cubicmap_atlas.png");    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

    Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };          // Set model position

    UnloadImage(image);     // Unload cubesmap image from RAM, already uploaded to VRAM

    //bool pause = false;     // Pause camera orbital rotation (and zoom)

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (flag)        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        updateController();

        UpdateCamera(&camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(model, mapPosition, 1.0f, WHITE);

            EndMode3D();

            DrawTextureEx(cubicmap, (Vector2){ screenWidth - cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
            DrawRectangleLines(screenWidth - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GREEN);

            DrawText("cubicmap image used to", screenWidth - cubicmap.width*4-10, 90, 10, GRAY);
            DrawText("generate map 3d model", screenWidth - cubicmap.width*4-10 , 104, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(cubicmap);    // Unload cubicmap texture
    UnloadTexture(texture);     // Unload map texture
    UnloadModel(model);         // Unload map model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
