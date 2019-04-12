#include "MainGame.h"
#include <iostream>
#include <vector>
#include <raylib.h>
Model bird;
Camera camera;
float CAMERA_SPEED = 25;
Vector3 CursorPosition;

struct Unit {
	Vector3 position;
	float rotation;
	Model model;
	Vector3 destination;
	float speed;
};
Unit unitArray[1024];
float clamp(float n, float min, float max) {
	return fminf(fmaxf(n, min), max);
}
Vector3 operator += ( Vector3 lhs, Vector3 rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}
Vector3 operator -= (Vector3 lhs, Vector3 rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}
Vector3 operator - (Vector3 lhs, Vector3 rhs) {
	return { lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z };
}
Vector3 operator + (Vector3 lhs, Vector3 rhs) {
	return { lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z };
}
Vector3 operator / (Vector3 lhs, float rhs) {
	return { lhs.x / rhs,
		lhs.y / rhs,
		lhs.z / rhs };
}
Vector3 operator * (Vector3 lhs, float rhs) {
	return { lhs.x * rhs,
		lhs.y * rhs,
		lhs.z * rhs };
}
float length(Vector3 lhs) {
	return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z);
}
Vector3 normalize(Vector3 lhs) {
	if (lhs.x == 0, lhs.y == 0, lhs.z == 0) {
		return lhs;
	}
	return lhs / length(lhs);
}
Vector3 MoveTowards(Vector3 start, Vector3 goal, float distance){
	Vector3 direction = goal - start;
	float dirlen = length(direction);
	if (dirlen < distance) {
		return goal;
	}
	direction = direction / dirlen;
	return start + direction * distance;


}
void Update(float dt)
{
	bool onEdge = false;
	if (GetMousePosition().x > GetScreenWidth()-5) {
		camera.position.x -= GetFrameTime()*CAMERA_SPEED;
		camera.target.x -= GetFrameTime()*CAMERA_SPEED;
	}
	if (GetMousePosition().x > GetScreenWidth()) {
		onEdge = true;
	}
	if (GetMousePosition().y > GetScreenHeight()-5) {
		camera.position.z -= GetFrameTime()*CAMERA_SPEED;
		camera.target.z -= GetFrameTime()*CAMERA_SPEED;
	}
	if (GetMousePosition().y > GetScreenHeight()) {
		onEdge = true;
	}
	if (GetMousePosition().x < 5) {
		camera.position.x += GetFrameTime()*CAMERA_SPEED;
		camera.target.x += GetFrameTime()*CAMERA_SPEED;
	}
	if (GetMousePosition().x < 0) {
		onEdge = true;
	}
	if (GetMousePosition().y < 5) {
		camera.position.z += GetFrameTime()*CAMERA_SPEED;
		camera.target.z += GetFrameTime()*CAMERA_SPEED;
	}
	if (GetMousePosition().y < 0) {
		onEdge = true;
	}
	if (onEdge) SetMousePosition({ clamp(GetMouseX(), 1, GetScreenWidth() - 1), clamp(GetMouseY(), 1, GetScreenHeight() - 1) });
	CursorPosition = GetCollisionRayGround(GetMouseRay(GetMousePosition(), camera), 0).position;
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
		unitArray[0].destination = CursorPosition;
	}
	if (length(unitArray[0].position - unitArray[0].destination) > 0.0001f)
		unitArray[0].position = MoveTowards(unitArray[0].position, unitArray[0].destination, GetFrameTime()*unitArray[0].speed);
	//printf("x:%f\ny:%f\nz:%f\n", normalize(unitArray[0].position - unitArray[0].destination).x, normalize(unitArray[0].position - unitArray[0].destination).y, normalize(unitArray[0].position - unitArray[0].destination).z);
	//if(isPanning)SetMousePosition({ clamp(GetMouseX(), 5, GetScreenWidth()), clamp(GetMouseY(), 0, GetScreenWidth()) });
	
}

void Draw(float dt)
{
	BeginMode3D(camera);
	DrawCircle3D(CursorPosition, 1, { 1,0,0 },90,GREEN);
	DrawModel(unitArray[0].model, unitArray[0].position, 1, BLACK);
	DrawGrid(10, 1);
	EndMode3D();
}

void InitializeGame() {
	DisableCursor();
	camera = Camera();
	camera.target = { 0,0,0 };
	camera.position = { 0,10,-1 };
	camera.fovy = 90;
	camera.up = { 0,0,10 };
	bird = LoadModel("resources/models/bird.obj");
	unitArray[0] = { Vector3(),0,bird,Vector3(),20 };
}

void SetUnitPosition(Vector3 vec, int unitIndex)
{
	unitArray[unitIndex].position = vec;
}

Vector3 GetUnitPosition(int unitIndex)
{
	return unitArray[unitIndex].position;
}
