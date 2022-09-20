#include "client.hpp"

/* ***********
 * Game Client
 * ***********
 */

void DrawMenu(std::vector<Menu::Button> b) {
    DrawText("TODO: render the game properly, check menu states and other cringe bullshit", 10, 10, 20, GREEN);
    for (int x = 0; x < b.size(); x++) {
        DrawRectangle(b[x].x, b[x].y, b[x].w, b[x].h, b[x].c);
    }
}
void DrawGame() {
    return;
}

void DrawEnd() {
    return;
}

// FIXME: if you reuse this for something more serious,
// try getting these values from a file instead of this atrocity
// I'm commiting. also categorize them by menu type jesus christ
// what is this thing
std::vector<Menu::Button> PrepareMenuButtons(int scr_w, int scr_h) {
    std::vector<Menu::Button> r;
    // start game
    Menu::Button b1(scr_w/2, (scr_h/2)-35, 200, 150, GREEN);

    // quit game
    Menu::Button b2(b1.x + b1.w + 10, (b1.y), 200, 150, RED); 
    
    r.push_back(b1);
    r.push_back(b2);
    return r;
}

// quick comment: next time I'm doing GUIs in raylib
// (i.e. abyssnet) I better start by doing that GUI creator
// thing I've been cooking for a while

int main() {
    WindowInfo w;
    // get raylib to run
    InitWindow(w.width, w.height, w.title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    SetTargetFPS(60);
    std::vector<Menu::Button> menu_b = PrepareMenuButtons(w.width, w.height);
    while (!WindowShouldClose()) {
        // TODO: CheckKeypresses()
        BeginDrawing();
        ClearBackground(BLACK);
        switch(w.state) {
            case WIN_MENU:
                DrawMenu(menu_b);
                break;
            case WIN_GAME:
                DrawGame();
                break;
            case WIN_END:
                DrawEnd();
                break;
        }
        EndDrawing();
    }
    CloseWindow(); // FIXME: send this to destructor if we're doing that sort of thing
    return 0;
}
