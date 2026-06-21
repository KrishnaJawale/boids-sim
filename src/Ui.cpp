#include "Ui.h"

constexpr int ROW_HEIGHT = 36;
constexpr int PANEL_PADDING = 12;

struct SliderDef {
    const char* label;
    float SimParams::*field;
    float min;
    float max;
};

constexpr SliderDef SLIDERS[] = {
    {"Max speed", &SimParams::maxSpeed, 10.0f, 300.0f},
    {"Min speed", &SimParams::minSpeed, 0.0f, 200.0f},
    {"Perception", &SimParams::perceptionRadius, 20.0f, 250.0f},
    {"Separation", &SimParams::separationRadius, 5.0f, 100.0f},
    {"Avoid", &SimParams::avoidFactor, 0.0f, 10.0f},
    {"Alignment", &SimParams::alignmentFactor, 0.0f, 5.0f},
    {"Cohesion", &SimParams::cohesionFactor, 0.0f, 5.0f},
    {"Edge margin", &SimParams::edgeMargin, 0.0f, 200.0f},
    {"Turn factor", &SimParams::turnFactor, 0.0f, 5.0f},
};

float clamp01(float t) {
    if (t < 0.0f) return 0.0f;
    if (t > 1.0f) return 1.0f;
    return t;
}

void drawSlider(int x, int y, int width, const char* label, float& value, float min, float max) {
    DrawText(label, x, y, 14, RAYWHITE);
    DrawText(TextFormat("%.1f", value), x + width - 48, y, 12, LIGHTGRAY);

    const Rectangle bounds = {(float)x, (float)(y + 18), (float)width, 16.0f};
    DrawRectangleRec(bounds, (Color){40, 40, 40, 255});

    const float fillWidth = bounds.width * clamp01((value - min) / (max - min));
    DrawRectangle((int)bounds.x, (int)bounds.y, (int)fillWidth, (int)bounds.height, (Color){80, 140, 220, 255});
    DrawRectangleLinesEx(bounds, 1.0f, (Color){120, 120, 120, 255});

    if (CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const float t = clamp01((GetMousePosition().x - bounds.x) / bounds.width);
        value = min + t * (max - min);
    }
}

void validateParams(SimParams& params) {
    if (params.minSpeed < 0.0f) params.minSpeed = 0.0f;
    if (params.maxSpeed < 1.0f) params.maxSpeed = 1.0f;
    if (params.minSpeed >= params.maxSpeed) params.minSpeed = params.maxSpeed - 1.0f;

    if (params.separationRadius < 1.0f) params.separationRadius = 1.0f;
    if (params.perceptionRadius < params.separationRadius) {
        params.perceptionRadius = params.separationRadius;
    }
}

void DrawTuningPanel(SimParams& params, int simWidth, int windowHeight) {
    DrawRectangle(simWidth, 0, UI_PANEL_WIDTH, windowHeight, (Color){24, 24, 24, 240});

    const int x = simWidth + PANEL_PADDING;
    const int sliderWidth = UI_PANEL_WIDTH - PANEL_PADDING * 2;
    int y = PANEL_PADDING;

    DrawText("Tuning", x, y, 20, RAYWHITE);
    y += 32;

    for (const SliderDef& slider : SLIDERS) {
        drawSlider(x, y, sliderWidth, slider.label, params.*(slider.field), slider.min, slider.max);
        y += ROW_HEIGHT;
    }

    validateParams(params);
}
