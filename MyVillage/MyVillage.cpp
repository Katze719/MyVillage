#include "cameraMode/cameraMode.h"




int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1600;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "MyVillage");

	Player player = { 0 };
	player.position = (Vector2){ 400, 280 };
	player.speed = 0;
	player.canJump = false;

	//Level 1
	EnvItem envItems[] = {
		//{{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
		{{ 0, 400, 1000, 200 }, 1, GRAY },
		{{ 300, 200, 400, 10 }, 1, GRAY },
		{{ 150, 300, 200, 15 }, 1, DARKGREEN },
		{{ 650, 300, 100, 10 }, 1, GRAY },
		{{600, 0, 0, 0}, 1, GREEN}
	};

	int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

	// Texturen
	Image bgImage = LoadImage("C:/Users/pauld/Desktop/hmm/aGHHoPbab7gxeG2SqHx6dpKVdxs8ta.png");
	Texture2D bgTexture = LoadTextureFromImage(bgImage);
	UnloadImage(bgImage);

	Camera2D camera = { 0 };
	camera.target = player.position;
	camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	// Store pointers to the multiple update camera functions
	void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
		UpdateCameraCenter,
		UpdateCameraCenterInsideMap,
		UpdateCameraCenterSmoothFollow,
		UpdateCameraEvenOutOnLanding,
		UpdateCameraPlayerBoundsPush
	};

	int cameraOption = 0;
	int cameraUpdatersLength = sizeof(cameraUpdaters) / sizeof(cameraUpdaters[0]);

	const char* cameraDescriptions[] = {
		"Follow player center",
		"Follow player center, but clamp to map edges",
		"Follow player center; smoothed",
		"Follow player center horizontally; updateplayer center vertically after landing",
		"Player push camera on getting too close to screen edge"
	};

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update vars here
		//----------------------------------------------------------------------------------
		float deltaTime = GetFrameTime();

		UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

		camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

		if (camera.zoom > 3.0f) camera.zoom = 3.0f;
		else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

		if (IsKeyPressed(KEY_R))
		{
			camera.zoom = 1.0f;
			player.position = (Vector2){ 400, 280 };
		}

		if (IsKeyPressed(KEY_C)) cameraOption = (cameraOption + 1) % cameraUpdatersLength;

		// Call update camera function by its pointer
		cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(LIGHTGRAY);

		DrawTexture(bgTexture, screenWidth / 100 - bgTexture.width / 100, screenHeight / 100 - bgTexture.height / 100, WHITE);

		BeginMode2D(camera);

		for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

		Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40, 40 };
		DrawRectangleRec(playerRect, RED);

		EndMode2D();

		DrawText("Controls:", 20, 20, 10, BLACK);
		DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
		DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
		DrawText("- Mouse Wheel to Zoom in-out, R to reset the Game", 40, 80, 10, DARKGRAY);
		DrawText("- C to change camera mode", 40, 100, 10, DARKGRAY);
		DrawText("Current camera mode:", 20, 120, 10, BLACK);
		DrawText(cameraDescriptions[cameraOption], 40, 140, 10, DARKGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}