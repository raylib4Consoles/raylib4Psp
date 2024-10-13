/*******************************************************************************************
*
*   raylib [shapes] example - raylib logo animation
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
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

PSP_MODULE_INFO("logoanim", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define ATTR_PSP_WIDTH 480
#define ATTR_PSP_HEIGHT 272

SceCtrlData pad;

bool flag=true;
bool l1flag=false;
bool r1flag=false;
int xflag;

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
            xflag=1;
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
            flag=0;
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

bool initApp()
{
    return true;
}
void finishApp()
{
    
    
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

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - raylib logo animation");
    //TRACELOG(LOG_INFO, "PLATFORM: calling dreamcast gl init");
    //glKosInit();
    int logoPositionX = screenWidth/2 - 128;
    int logoPositionY = screenHeight/2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;             // Useful for fading

    
  
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

   
    // Main game loop
    while (flag)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        updateController();


        if (state == 0)                 // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
            framesCounter++;

            if (framesCounter/12)       // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        else if (state == 4)            // State 4: Reset and Replay
        {
            if (xflag)
            {
                framesCounter = 0;
                lettersCount = 0;

                topSideRecWidth = 16;
                leftSideRecHeight = 16;

                bottomSideRecWidth = 16;
                rightSideRecHeight = 16;

                alpha = 1.0f;
                state = 0;          // Return to State 0
                xflag = 0;
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
   
            if (state == 0)
            {
                if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
            }
            else if (state == 1)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
            }
            else if (state == 2)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

                DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
            }
            else if (state == 3)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

                DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

                DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));
                DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));
            }
            else if (state == 4)
            {
                DrawText("powered by raylib4Psp [X] REPLAY", screenWidth/2-200, screenHeight/2-38, 20, GRAY);
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    finishApp();
    return 0;
}
