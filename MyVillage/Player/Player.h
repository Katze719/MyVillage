#pragma once
#include <raylib.h>

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

typedef struct Player {
	Vector2 position;
	float speed;
	bool canJump;
} Player;

typedef struct EnvItem {
	Rectangle rect;
	int blocking;
	Color color;
} EnvItem;

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);
