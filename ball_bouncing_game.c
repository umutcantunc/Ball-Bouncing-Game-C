
#include "raylib.h"

typedef struct {
    Vector2 konum;
    Vector2 hiz;
    float yaricap;
    Color renk;
} TopVerisi;

int main() {
    const int ekranGenislik = 600;
    const int ekranYukseklik = 400;

    InitWindow(ekranGenislik, ekranYukseklik, "Ball Bouncing Game");
    SetTargetFPS(60);

    // Fizik Ayarlari
    const float yercekimi = 0.5f;
    const float ziplamaGucu = 12.0f; 

    int skor = 0;
    bool oyunBitti = false;

    // Top baslangic
    TopVerisi top;
    top.konum = (Vector2){ ekranGenislik / 2.0f, ekranYukseklik / 2.0f };
    top.hiz = (Vector2){ 2.0f, 0.0f }; // baslangicta ufak bir hiz
    top.yaricap = 40.0f;
    top.renk = MAROON;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            top.konum = (Vector2){ ekranGenislik / 2.0f, ekranYukseklik / 2.0f };
            top.hiz = (Vector2){ 0.0f, 0.0f };
            skor = 0;
            oyunBitti = false;
        }
        
        if (!oyunBitti) {

            top.konum.x += top.hiz.x;
            top.konum.y += top.hiz.y;
            top.hiz.y += yercekimi;


            //  Yer�ekimi ve Hareket
            

            if (top.konum.x > 560 || top.konum.x < 40) {
                top.hiz.x = -top.hiz.x;
            }


            // Duvarlardan Sektirme (Sa� ve Sol)
            




            //  Tiklama kontrolu
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointCircle(GetMousePosition(), top.konum, top.yaricap)) {

                // 1. Yukari firlat
                top.hiz.y = -ziplamaGucu;
                // 2. Yana Firlat 
                
                top.hiz.x = (top.konum.x - GetMouseX()) * 0.2f;

                skor++;
            }

            // Yere dusme kontrol
            if (top.konum.y > ekranYukseklik + top.yaricap) {
                oyunBitti = true;
            }
        }

        // Cizim
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!oyunBitti) {
                // Topu ciz
                DrawCircleV(top.konum, top.yaricap, top.renk);

                // Gorsel ipucu: Topun merkezini goster (Kucuk nokta)
                DrawCircleV(top.konum, 3, WHITE);

                DrawText(TextFormat("Score: %d", skor), 10, 10, 30, LIGHTGRAY);
            }
            else {
                DrawText("GAME OVER!", 180, 150, 40, RED);
                DrawText(TextFormat("Score: %d", skor), 220, 200, 20, DARKGRAY);
                DrawText("'R' with play again", 200, 250, 20, GRAY);
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
