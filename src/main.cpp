#include <vector>
#include "raylib.h"
#include "Vec2.h"
#include "Boid.h"
#include "SimParams.h"
#include "Ui.h"

constexpr int SIM_WIDTH = 1280;
constexpr int SIM_HEIGHT = 720;
constexpr int WINDOW_WIDTH = SIM_WIDTH + UI_PANEL_WIDTH;
constexpr int WINDOW_HEIGHT = SIM_HEIGHT;
const int BOID_COUNT = 500;

SimParams params;
std::vector<Boid> boids;

void initBoids() {
    for (int i = 0; i < BOID_COUNT; i++) {
        Vec2 position(
            (float)GetRandomValue(0, SIM_WIDTH - 1),
            (float)GetRandomValue(0, SIM_HEIGHT - 1));
        Vec2 velocity((float)GetRandomValue(-500, 500), (float)GetRandomValue(-500, 500));
        Vec2 acceleration(0, 0);
        boids.push_back(Boid(position, velocity, acceleration));
    }
}

void clampBoidSpeed(Boid& boid) {
    const float speed = boid.velocity.length();
    if (speed < 1e-6f) {
        return;
    }
    if (speed > params.maxSpeed) {
        boid.velocity = boid.velocity / speed * params.maxSpeed;
    } else if (speed < params.minSpeed) {
        boid.velocity = boid.velocity / speed * params.minSpeed;
    }
}

void applyEdgeTurn(Boid& boid) {
    if (boid.position.x < params.edgeMargin) {
        boid.velocity.x += params.turnFactor;
    } else if (boid.position.x > SIM_WIDTH - params.edgeMargin) {
        boid.velocity.x -= params.turnFactor;
    }

    if (boid.position.y < params.edgeMargin) {
        boid.velocity.y += params.turnFactor;
    } else if (boid.position.y > SIM_HEIGHT - params.edgeMargin) {
        boid.velocity.y -= params.turnFactor;
    }
}

std::vector<Boid> getNeighbours(Boid& boid) {
    std::vector<Boid> neighbours;
    for (int i = 0; i < BOID_COUNT; i++) {
        if (&boids[i] == &boid) continue;

        Vec2 dist = boids[i].position - boid.position;
        if (dist.lengthSquared() < params.perceptionRadius * params.perceptionRadius) {
            neighbours.push_back(boids[i]);
        }
    }
    return neighbours;
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Boids Sim");
    SetTargetFPS(60);

    initBoids();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Calculate forces
        for (int i = 0; i < BOID_COUNT; i++) {
            boids[i].acceleration = Vec2(0, 0);
            std::vector<Boid> neighbours = getNeighbours(boids[i]);

            // Separation
            Vec2 separation = Vec2(0, 0);
            for (int j = 0; j < neighbours.size(); j++) {
                Vec2 dist = boids[i].position - neighbours[j].position;
                if (dist.lengthSquared() < params.separationRadius * params.separationRadius) {
                    separation += dist;
                }
            }
            boids[i].acceleration += separation * params.avoidFactor;

            // Alignment and Cohesion
            Vec2 averageVelocity = Vec2(0, 0);
            Vec2 averagePosition = Vec2(0, 0);

            for (int j = 0; j < neighbours.size(); j++) {
                averageVelocity += neighbours[j].velocity;
                averagePosition += neighbours[j].position;
            }

            if (neighbours.size() > 0) {
                averageVelocity = averageVelocity / neighbours.size();
                Vec2 desired = averageVelocity.normalized() * params.maxSpeed;
                boids[i].acceleration += (desired - boids[i].velocity) * params.alignmentFactor;

                averagePosition = averagePosition / neighbours.size();
                boids[i].acceleration += (averagePosition - boids[i].position) * params.cohesionFactor;
            }
        }

        // Update boids
        for (int i = 0; i < BOID_COUNT; i++) {
            boids[i].velocity += boids[i].acceleration * dt;
            applyEdgeTurn(boids[i]);
            clampBoidSpeed(boids[i]);
            boids[i].position += boids[i].velocity * dt;
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < BOID_COUNT; i++) {
            float angle = atan2f(boids[i].velocity.y, boids[i].velocity.x) * RAD2DEG;
            DrawPoly((Vector2){boids[i].position.x, boids[i].position.y}, 3, 6, angle, BLUE);
        }

        DrawFPS(10, 10);
        DrawTuningPanel(params, SIM_WIDTH, WINDOW_HEIGHT);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
