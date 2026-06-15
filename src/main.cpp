/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/
*/

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "main.h"
#include "resource_dir.h"
#include <cstdlib>
#include <ctime>

int main()
{
	GameState gameState = MENU;

	std::srand(static_cast<unsigned int>(time(nullptr)));
	int chances = 0;
	int score = 0;
	const int screenHeight = 600;
	const int screenWidth = 1200;
	InitWindow(screenWidth, screenHeight, "Hit The Target");
	SetTargetFPS(60);

	float playerSpeed = 300.0f;
	float tankX = 145.0f;
	float tankY = 450.0f;
	float xMax = (screenWidth / 3.0f) - 120.0f;
	float xMin = 0.0f;
	Projectile bullet;
	const float barrelLength = 120.0f;
	const float bulletSpeed = 950.0f;
	const float gravity = 900.0f;
	const float groundY = 500.0f;
	player player1;
	float angleRad = -15.0f * DEG2RAD;

	Target target;
	target.x = GetRandomValue(500, 1150);
	target.y = GetRandomValue(25, 475);
	target.radius = 35.0f;

	auto resetGame = [&]() {
		chances = 0;
		score = 0;
		tankX = 145.0f;
		bullet = {};
		angleRad = -15.0f * DEG2RAD;
		target.x = GetRandomValue(500, 1150);
		target.y = GetRandomValue(25, 475);
	};

	while (!WindowShouldClose())
	{
		float dtime = GetFrameTime();
		bool isPlaying = gameState == OUT_OF_Five || gameState == ARCADE_MODE;

		if (isPlaying)
		{
			float dx = 0.0f;
			if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) dx += 1.0f;
			if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) dx -= 1.0f;

			tankX += dx * playerSpeed * dtime;
			if (tankX < xMin) tankX = xMin;
			if (tankX > xMax) tankX = xMax;

			Vector2 barrelPos = {tankX + 65, tankY - 10};
			Vector2 mouse = GetMousePosition();
			angleRad = atan2f(mouse.y - barrelPos.y, mouse.x - barrelPos.x);

			Vector2 muzzle = {
				barrelPos.x + cosf(angleRad) * barrelLength,
				barrelPos.y + sinf(angleRad) * barrelLength
			};

			if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) && !bullet.alive)
			{
				bullet.alive = true;
				bullet.pos = muzzle;
				bullet.vel = {cosf(angleRad) * bulletSpeed, sinf(angleRad) * bulletSpeed};
				if (gameState == OUT_OF_Five) chances++;
			}

			if (bullet.alive)
			{
				bullet.vel.y += gravity * dtime;
				bullet.pos.x += bullet.vel.x * dtime;
				bullet.pos.y += bullet.vel.y * dtime;

				bool shotFinished = false;
				bool targetHit = false;
				Vector2 targetCenter = {(float)target.x, (float)target.y};
				float radiusSquared = target.radius * target.radius;

				if (Dist2(bullet.pos, targetCenter) <= radiusSquared)
				{
					bullet.alive = false;
					score++;
					shotFinished = true;
					targetHit = true;
					target.x = GetRandomValue(500, 1150);
					target.y = GetRandomValue(25, 475);
				}
				else if (bullet.pos.y >= groundY)
				{
					bullet.alive = false;
					bullet.pos.y = groundY;
					shotFinished = true;
				}

				if (shotFinished)
				{
					if (gameState == ARCADE_MODE && !targetHit)
					{
						gameState = RESULTS;
					}
					else if (gameState == OUT_OF_Five && chances >= 5)
					{
						gameState = RESULTS;
					}
				}
			}
		}

		BeginDrawing();
		drawLandScape();

		if (gameState == MENU)
		{
			DrawText("Welcome To Hit The Target!", 410, 150, 32, BLACK);
			if (GuiButton((Rectangle){475, 250, 250, 80}, "Arcade Mode"))
			{
				resetGame();
				gameState = ARCADE_MODE;
			}
			if (GuiButton((Rectangle){475, 360, 250, 80}, "Best Of 5"))
			{
				resetGame();
				gameState = OUT_OF_Five;
			}
		}
		else if (gameState == RESULTS)
		{
			string resultText = "Final Score: " + to_string(score);
			DrawText(resultText.c_str(), 490, 220, 32, BLACK);
			if (GuiButton((Rectangle){475, 300, 250, 80}, "Back To Menu"))
			{
				gameState = MENU;
			}
		}
		else
		{
			Vector2 barrelPos = {tankX + 65, tankY - 10};
			float angle = angleRad * RAD2DEG;
			string scoreText = "Score: " + to_string(score);
			DrawText(scoreText.c_str(), 1020, 10, 24, BLACK);

			if (gameState == OUT_OF_Five)
			{
				string chancesText = "Shots: " + to_string(chances) + " / 5";
				DrawText(chancesText.c_str(), 1020, 40, 24, BLACK);
			}

			target.drawtarget();
			if (bullet.alive) DrawCircleV(bullet.pos, 5.0f, BLACK);
			player1.drawTank((int)tankX, (int)tankY);
			player1.drawTankBarrel(barrelPos, angle);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
