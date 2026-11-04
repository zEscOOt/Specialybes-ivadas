#include "raylib.h"
#include "raymath.h"

void Vector2ScreenWrap(Vector2* v1, int w, int h);

struct Meteor {
	Vector2 position;
	Vector2 velocity;
	unsigned int radius;
};

struct Meteor createMeteor(){
	struct Meteor m;
    m.position = (struct Vector2){0.0f, 0.0f}; // Initialize position
    m.velocity = (struct Vector2){0.0f, 0.0f}; // Initialize velocity
    m.radius = 0; // Initialize radius
    return m;
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
	const Vector2 Vec2MaxVelocity = {30.f, 30.f};
	const Vector2 Vec2MinVelocity = {-30.f, -30.f}; 
	const float playerAcceleration = 0.2f;
	const float playerTurnSpeed = 4.0f; // In degrees
	const float playerRadius = 30.0f;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    Vector2 playerPosition = { (float)screenWidth/2, (float)screenHeight/2 };
	Vector2 playerPointOffset[3] = {{0.0f, -playerRadius}, {-playerRadius/2, playerRadius}, {playerRadius/2, playerRadius}};
	Vector2 playerPointPos[3];
	Vector2 playerVelocity = {0.0f, 0.0f};
	float playerRotation = 0.0f * PI; // 0 is North

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
		if(IsKeyDown(KEY_RIGHT)) playerRotation += playerTurnSpeed * DEG2RAD;
		if(IsKeyDown(KEY_LEFT)) playerRotation -= playerTurnSpeed * DEG2RAD;
        if(IsKeyDown(KEY_UP)) playerVelocity = Vector2Add(playerVelocity, Vector2Rotate((Vector2){0.0f, -playerAcceleration}, playerRotation));

		playerVelocity = Vector2Clamp(playerVelocity, Vec2MinVelocity, Vec2MaxVelocity);
		// Apply velocity
		playerPosition = Vector2Add(playerPosition, playerVelocity);	
		Vector2ScreenWrap(&playerPosition, screenWidth, screenHeight);

		
		for(int i = 0; i < 3; i++){
			playerPointPos[i] = Vector2Add(Vector2Rotate(playerPointOffset[i], playerRotation), playerPosition);
		} 

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("Vel X: %.02f", playerVelocity.x), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Vel Y: %.02f", playerVelocity.y), 10, 40, 20, DARKGRAY);

			DrawCircle(playerPointPos[0].x, playerPointPos[0].y, 3.0f, RED);
            DrawTriangleLinesEx(playerPointPos[0], playerPointPos[1], playerPointPos[2], 2.0f, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void Vector2ScreenWrap(Vector2* v1, int w, int h){
	if(v1->x >= w) v1->x = 0;
	if(v1->y >= h) v1->y = 0;

	if(v1->x < 0) v1->x = w;
	if(v1->y < 0) v1->y = h;

}
