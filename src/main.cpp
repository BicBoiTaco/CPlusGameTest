/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib-cpp.hpp"
#include <iostream>


#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

bool canMove = true;

const int moveSpeed = 3;

// Player start pos
int pStartPosX = 30;
int pStartPosY = 400;


int recX = pStartPosX;
int& refX = recX;
int recY = pStartPosY;
int& refY = recY;

Rectangle obstacle{ 400, 400, 20, 20 };


void ResetGame() {

	recX = pStartPosX;
	recY = pStartPosY;
	canMove = true;
}


void MovementInput() {
	if (IsKeyDown(KEY_RIGHT)) {
		refX += moveSpeed;
	}
	if (IsKeyDown(KEY_LEFT)) {
		refX -= moveSpeed;
	}
	if (IsKeyDown(KEY_UP)) {
		refY -= moveSpeed;
	}
	if (IsKeyDown(KEY_DOWN)) {
		refY += moveSpeed;
	}
}


int main ()
{


	SetTargetFPS(60);
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Box Game");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{


		std::cout << GetFPS() << "\n";
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font


		Rectangle player = { refX, refY, 50, 50 };

		
		DrawRectangle(refX, refY, player.width, player.height, WHITE);
		DrawRectangle(obstacle.x, obstacle.y, obstacle.width, obstacle.height, RED);

		if (CheckCollisionRecs(player, obstacle)) {
			DrawText("Game Over!", 500, 350, 50, RED);
			canMove = false;
		}
		else {
			canMove = true;
		}

		if (IsKeyPressed(KEY_R)) {
			ResetGame();
			std::cout << "\n" << "I Work!!!" << "\n";
		}

		if (canMove) {
			MovementInput();
		}
		


		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}



	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
