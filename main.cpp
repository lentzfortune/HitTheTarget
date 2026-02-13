/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "main.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>

int main ()
{
	std::srand(static_cast<unsigned int>(time(nullptr)));
	int chances = 5;
	int Score = 0;
	const int screenHeight = 600;
	const int screenWidth = 1200;
	InitWindow(screenWidth,screenHeight,"Hit The Target");
	SetTargetFPS(60);

	float dtime = 0.0f;
	float playerSpeed = 300.0f;
	Vector2 GetSplinePointBezierQuad(Vector2 p1, Vector2 c2, Vector2 p3, float t);
	float tankX = 145.0f;
	float tankY = 450.0f;
	float xMax = (screenWidth/3.0f) - 120.0f;
	float xMin = 0.0f;
	Projectile bullet;
	const float barrelLength = 120.0f;
	const float bulletSpeed = 600.0f; 
	const float gravity = 900.f;
	const float groundY = 500.0f;
	player player1;

	Target target;
    target.x = RandRangeInt(425, 1175);
    target.y = RandRangeInt(25, 475);
    target.radius = 35.f;

	


	
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		
		

		dtime = GetFrameTime();
		float dx = 0.0f;
		
		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {dx += 1.0f;}
		if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)){dx -= 1.0f;}

		tankX += dx * playerSpeed * dtime;

		if (tankX < xMin){
			tankX = xMin;
		}
		if (tankX > xMax){
			tankX = xMax;
		}
		
		
		
		

    
// Barrel origin (hinge point)
	Vector2 barrelPos = {tankX + 65, tankY - 10};

// Get mouse position
	Vector2 mouse = GetMousePosition();

// Compute angle to mouse
	float angleRad = atan2f(mouse.y - barrelPos.y, mouse.x - barrelPos.x);
	float angle = angleRad * RAD2DEG;
// Draw tank and barrel
	Vector2 muzzle = {barrelPos.x + cosf(angleRad) * barrelLength, barrelPos.y + sinf(angleRad) * barrelLength};
	if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) && !bullet.alive) {
    bullet.alive = true;
    bullet.pos = muzzle;
    bullet.vel = { cosf(angleRad) * bulletSpeed, sinf(angleRad) * bulletSpeed };
}
	if (bullet.alive) {
    // gravity (positive Y is down)daad
    bullet.vel.y += gravity * dtime;
    bullet.pos.x += bullet.vel.x * dtime;
    bullet.pos.y += bullet.vel.y * dtime;

    // ground collision
    if (bullet.pos.y >= groundY) {
        bullet.alive = false;
        bullet.pos.y = groundY; 
		
	}else{
		Vector2 tgtCenter = {(float)target1.x, (float)target1.y};
		float r2 = target1.radius * target1.radius;
		if (Dist2(bullet.pos,tgtCenter) <=r2){
			bullet.alive = false;

			target1.x = RandRangeInt(425,1175);
			target1.y = changeTargetPositionY(25,475);
			target1.radius = 35.f;
		}
	}
}
	
	

	if (bullet.alive) {
    DrawCircleV(bullet.pos, 5.0f, BLACK);}
	BeginDrawing();
	drawLandScape();
	target.drawtarget();

	if(bullet.alive){
    DrawCircleV(bullet.pos, 5.0f, BLACK);}
	//player1.drawTank(440, 120);
	player1.drawTank((int)tankX, (int)tankY);
	player1.drawTankBarrel(barrelPos, angle);
		

		
	EndDrawing();
	
	}


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}