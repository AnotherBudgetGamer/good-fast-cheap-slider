#include <raylib.h>
#include "abg_core.h"
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

void Slider_SetVProportion(Slider sliders[], int draggedSlider, float newDraggedValue) {
    float oldOtherTotal = 0.0f;
    int zeroOtherCount = 0;

    for (int i = 0; i < SLIDER_COUNT; i++) {
        if (i != draggedSlider) {
            oldOtherTotal += sliders[i].v;

            if (sliders[i].v <= ABG_EPSILON) {
                zeroOtherCount++;
            }
        }
    }

    float newOtherTotal = (float)SLIDER_TOTAL - newDraggedValue;
    float otherDelta = newOtherTotal - oldOtherTotal;

    sliders[draggedSlider].v = newDraggedValue;

    /*
        Edge case 1:
        If all other sliders were 0, there is no ratio to preserve.
        Split the remaining value evenly.
    */
    if (oldOtherTotal <= ABG_EPSILON) {
        float splitValue = newOtherTotal / (float)(SLIDER_COUNT - 1);

        for (int i = 0; i < SLIDER_COUNT; i++) {
            if (i != draggedSlider) {
                sliders[i].v = splitValue;
            }
        }

        return;
    }

    /*
        Edge case 2:
        If the dragged slider moved down, the other sliders gained value.

        If any non-dragged sliders are currently 0, give the newly freed value
        to those zero sliders instead of letting the non-zero slider absorb
        everything proportionally.
    */
    if (otherDelta > ABG_EPSILON && zeroOtherCount > 0) {
        float valueForEachZero = otherDelta / (float)zeroOtherCount;

        for (int i = 0; i < SLIDER_COUNT; i++) {
            if (i != draggedSlider && sliders[i].v <= ABG_EPSILON) {
                sliders[i].v = valueForEachZero;
            }
        }

        return;
    }

    /*
        Normal proportional behavior.
        This handles:
        - no zero sliders
        - dragged slider moving up, meaning the others must shrink
    */
    for (int i = 0; i < SLIDER_COUNT; i++) {
        if (i != draggedSlider) {
            float oldRatio = sliders[i].v / oldOtherTotal;
            sliders[i].v = newOtherTotal * oldRatio;
        }
    }
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Good, Fast, Cheap Slider");
    SetTargetFPS(60);

    Slider sliders[SLIDER_COUNT] = {
        {
            .pos = {100, 100},
            .size = {180, 400},
            .v = 33,
            .label = "GOOD",
            .color = RED,
            .hovered = false
        },
        {
            .pos = {360, 100},
            .size = {180, 400},
            .v = 33,
            .label = "CHEAP",
            .color = GREEN,
            .hovered = false
        },
        {
            .pos = {620, 100},
            .size = {180, 400},
            .v = 34,
            .label = "FAST",
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

        // hover + click for selected slider
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < SLIDER_COUNT; i ++) {
                if (sliders[i].hovered) {
                    draggedSlider = i;
                    break;
                }
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            draggedSlider = -1;
        }

        // selected slider drag
        if (draggedSlider != -1 && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Slider *s = &sliders[draggedSlider];

            float sliderTop = s->pos.y;
            float sliderBottom = s->pos.y + s->size.y;

            float newValue = ABG_RemapFloatClamped(
                mousePos.y,
                sliderBottom,
                sliderTop,
                0.0f,
                (float)SLIDER_TOTAL
            );

            Slider_SetVProportion(sliders, draggedSlider, newValue);
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

                ABG_DrawRect(rect, DARKGRAY);

                float fillPercent = sliders[i].v / (float)SLIDER_TOTAL;
                float fillHeight = sliders[i].size.y * fillPercent;
                float fill_y = sliders[i].pos.y + sliders[i].size.y - fillHeight;

                ABG_Rect fillRect = ABG_RectFromSize(
                    sliders[i].pos.x,
                    fill_y,
                    sliders[i].size.x,
                    fillHeight
                );

                ABG_DrawRect(fillRect, sliders[i].color);

                DrawText(
                    TextFormat("%s: %.0f%%", sliders[i].label, sliders[i].v),
                    (int)sliders[i].pos.x + 30,
                    (int)sliders[i].pos.y + 150,
                    24,
                    WHITE
                );

                if (sliders[i].hovered || draggedSlider == i) {
                    ABG_DrawRectLines(rect, WHITE);
                } else {
                    ABG_DrawRectLines(rect, BLACK);
                }

                DrawText(
                    "This is to demonstrate proportional distribution",
                    20, 20, 20, BLACK
                );

                DrawText(
                    "Click/Drag slider to change values",
                    20, 50, 20, BLACK
                );
            }

        EndDrawing();

    }

    CloseWindow();
    
    return 0;
}