#pragma once
#include <raylib.h>

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 400.0f

struct Player {
	Vector2 position;
	float speed;
	bool canJump;
};

struct EnvItem {
	Rectangle rect;
	int blocking;
	Color color;
};

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);
