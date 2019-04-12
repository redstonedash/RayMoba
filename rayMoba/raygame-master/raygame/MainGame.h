#pragma once
void Update(float dt);
void Draw(float dt);
void InitializeGame();
struct Vector3;
void SetUnitPosition(Vector3 vec, int unitIndex);
Vector3 GetUnitPosition(int unitIndex);
struct Unit;