#include <vector>
#include "raylib.h"
#include "Vec2.h"
#include "Boid.h"

const int BOID_COUNT = 100;

std::vector<Boid> boids;

void initBoids() {
    for (int i = 0; i < BOID_COUNT; i++) {
        Vec2 position((float)GetRandomValue(0, 800), (float)GetRandomValue(0, 600));
        Vec2 velocity((float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100));
        boids.push_back(Boid(position, velocity));
    }
}

void wrapBoid(Boid& boid) {
    if (boid.position.x < 0) {
        boid.position.x = 800;
    } else if (boid.position.x >= 800) {
        boid.position.x = 0;
    }
    if (boid.position.y < 0) {
        boid.position.y = 600;
    } else if (boid.position.y >= 600) {
        boid.position.y = 0;
    }
}

int main() {
    InitWindow(800, 600, "Boids Sim");
    SetTargetFPS(60);

    initBoids();

    while (!WindowShouldClose()) {
        // Update boids
        float dt = GetFrameTime();

        for (int i = 0; i < BOID_COUNT; i++) {
            boids[i].position += boids[i].velocity * dt;
            wrapBoid(boids[i]);
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < BOID_COUNT; i++) {
            float angle = atan2f(boids[i].velocity.y, boids[i].velocity.x) * RAD2DEG;
            DrawPoly((Vector2){boids[i].position.x, boids[i].position.y}, 3, 6, angle, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}