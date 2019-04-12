#include "raylib.h"
#include <iostream>
#include "pipeManager.h"
#include <string>
#include "MainGame.h"
char last[KILOBYTE];

int main()
{
	InitWindow(800,650,"raylib");
	SetTargetFPS(120);
	InitializeGame();
	//is server?
	while (!WindowShouldClose())
	{
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		DrawText("SERVER", 75, 325, 64, BLACK);
		DrawText("CLIENT", 475, 325, 64, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			if (GetMousePosition().x > 325) {
				isServer = false;
			} else {
				isServer = true;
			}
			break;
		}
		DrawCircle(GetMousePosition().x, GetMousePosition().y, 10, RED);
		EndDrawing();
	}
	if (isServer) {
		instantiateServer();
	}
	else {
		instantiateClient();
	}
	while (!WindowShouldClose())
	{
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		DrawFPS(700, 15);
		if (isServer) {
			DrawText("server", 0,0,100,BLACK);
		}
		else {
			DrawText("client", 0, 0, 100, BLACK);
		}
		if (isServer) {
			//char * buffer = new char[64];
			memcpy(getBuffer(), (char *)(void *)&GetUnitPosition(0), sizeof(GetUnitPosition(0)));
			//std::strcpy(getBuffer(), "Lmao");
			//snprintf(buffer, sizeof buffer, "%f", (float)GetMousePosition().x);
			writeNetwork();

		}
		else {
			readNetwork();
			Vector3 temp = *(Vector3 *)(void *)getBuffer();
			SetUnitPosition(temp,0);
			//if (getBuffer()[0] != 0x2D) {
				//DrawText(getBuffer(), 400, 325, 64, BLACK);
			//printf("%.*s\n", 8, getBuffer());
			//std::strcpy(last, getBuffer());
			/*}
			else {
				DrawText(last, 400, 325, 64, BLACK);
			}*/
		}
		Update(0);
		Draw(0);
		DrawCircle(GetMousePosition().x, GetMousePosition().y, 10, RED);
		EndDrawing();
	}
	if (isServer) {
		disconnect();
	}
	CloseWindow();
	return 0;
}