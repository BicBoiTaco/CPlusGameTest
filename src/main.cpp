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
#include <time.h>  

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir


bool playerIsDead;
bool canMove = true;
bool canMoveUp = true;
bool canMoveDown = true;
bool canMoveLeft = true;
bool canMoveRight = true;

const int outOfBoundsUp = 0;
const int outOfBoundsDown = 750;
const int outOfBoundsLeft = 0;
const int outOfBoundsRight = 750;



const int moveSpeed = 3;

int eStartPosX = 850;

// Player start pos
int pStartPosX = 30;
int pStartPosY = 400;


int recX = pStartPosX;
int& refX = recX;
int recY = pStartPosY;
int& refY = recY;

int RandomHieght() {
	int objHeight;
	objHeight = rand() % 700 + 50;
	return objHeight;
}

void ResetPlayer() {
	playerIsDead = false;
	recX = pStartPosX;
	recY = pStartPosY;
	canMove = true;
	
}






int EnemyMovementSpeed(int enemyType) {
	int enemySpeed = 1;
	if (enemyType == 1){
		enemySpeed = rand() % 2 + 1;
	}
	return enemySpeed;
}







void MovementInput() {
	if (IsKeyDown(KEY_RIGHT) && canMoveRight) {
		recX += moveSpeed;
	}
	if (IsKeyDown(KEY_LEFT) && canMoveLeft) {
		recX -= moveSpeed;
	}
	if (IsKeyDown(KEY_UP) && canMoveUp) {
		recY -= moveSpeed;
	}
	if (IsKeyDown(KEY_DOWN) && canMoveDown) {
		recY += moveSpeed;
	}
}


int main ()
{

	srand(time(0));


	Rectangle obstacle{ 800, RandomHieght(), 20, 20};

	SetTargetFPS(60);
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 800, "Box Game");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");


	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{


		//std::cout << GetFPS() << "\n";
		std::cout << obstacle.y << "\n";

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// Dont allow player out of bounds
		if (refX > outOfBoundsRight) {
			refX = outOfBoundsRight;
			canMoveRight = false;
		}
		else {
			canMoveRight = true;
		}
		if (refY > outOfBoundsDown) {
			refY = outOfBoundsDown;
			canMoveDown = false;
		}
		else {
			canMoveDown = true;
		}
		if (refX < outOfBoundsLeft) {
			refX = outOfBoundsLeft;
			canMoveLeft = false;
		}
		else {
			canMoveLeft = true;
		}
		if (refY < outOfBoundsUp) {
			refY = outOfBoundsUp;
			canMoveUp = false;
		}
		else {
			canMoveUp = true;
		}

		Rectangle player = { refX, refY, 50, 50 };

		DrawRectangle(obstacle.x -= EnemyMovementSpeed(1), obstacle.y, obstacle.width, obstacle.height, RED);

		DrawRectangle(refX, refY, player.width, player.height, WHITE);

		// I NEED TO MAKE THIS PROCEEDURAL SO THAT MANY SPAWN OFF SCREEN AND SLIDE TOWARDS PLAYER, THEN DELETE WHEN OFFSCREEN AGAIN
		

		if (CheckCollisionRecs(player, obstacle)) {
			bool playerIsDead = true;
		}
		if (playerIsDead == true) {
			DrawText("Game Over!", 250, 400, 50, RED);
			canMove = false;
		}

		if (IsKeyPressed(KEY_R)) {
			ResetPlayer();
			std::cout << "\n" << "I Work!!!" << "\n";
			obstacle.y = RandomHieght();
			obstacle.x = eStartPosX;

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
