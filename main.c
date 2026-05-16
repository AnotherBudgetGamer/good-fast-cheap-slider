#include <raylib.h>
#include "abg_ui.h"

#define SCREEN_W 900
#define SCREEN_H 600

#define SLIDER_TOTAL 100
#define SLIDER_COUNT 3

typedef struct {
    Vector2 pos;
    Vector2 size;
    float v;
    const char *label;
    Color color;
    bool hovered;
} Slider;

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Good, Fast, Cheap Slider");
    SetTargetFPS(60);

    Slider sliders[SLIDER_COUNT] = {
        {
            .pos = {100, 220},
            .size = {180, 260},
            .v = 33,
            .label = "GOOD",
            .color = RED,
            .hovered = false
        },
        {
            .pos = {360, 220},
            .size = {180, 260},
            .v = 33,
            .label = "GOOD",
            .color = GREEN,
            .hovered = false
        },
        {
            .pos = {620, 220},
            .size = {180, 260},
            .v = 34,
            .label = "GOOD",
            .color = BLUE,
            .hovered = false
        }

    };
    
    int draggedSlider = -1;

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < SLIDER_COUNT; i++) {
            ABG_Rect slider = ABG_RectFromSize(
                sliders[i].pos.x,
                sliders[i].pos.y,
                sliders[i].size.x,
                sliders[i].size.y
            );

            sliders[i].hovered = ABG_RectContainsPoint(slider, mousePos.x, mousePos.y);
        }

        BeginDrawing();
            ClearBackground(BROWN);

            for (int i = 0; i < SLIDER_COUNT; i++) {
                ABG_Rect rect = ABG_RectFromSize(
                    sliders[i].pos.x,
                    sliders[i].pos.y,
                    sliders[i].size.x,
                    sliders[i].size.y
                );

                ABG_DrawRect(rect, sliders[i].color);

                DrawText(
                    TextFormat("%s: %.0f%%", sliders[i].label, sliders[i].v),
                    (int)sliders[i].pos.x + 30,
                    (int)sliders[i].pos.y + 150,
                    24,
                    WHITE
                );

                if (sliders[i].hovered) {
                    ABG_DrawRectLines(rect, WHITE);
                } else {
                    ABG_DrawRectLines(rect, BLACK);
                }
            }

        EndDrawing();

        }
    CloseWindow();
    
    return 0;
}