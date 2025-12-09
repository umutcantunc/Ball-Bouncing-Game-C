
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

    // Fizik Ayarlarý
    const float yercekimi = 0.5f;
    const float ziplamaGucu = 12.0f; // Biraz daha güçlü zýplasýn

    int skor = 0;
    bool oyunBitti = false;

    // Top Baþlangýç
    TopVerisi top;
    top.konum = (Vector2){ ekranGenislik / 2.0f, ekranYukseklik / 2.0f };
    top.hiz = (Vector2){ 2.0f, 0.0f }; // Hafif bir baþlangýç hýzý
    top.yaricap = 40.0f;
    top.renk = MAROON;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            top.konum = (Vector2){ ekranGenislik / 2.0f, ekranYukseklik / 2.0f };
            top.hiz = (Vector2){ 0.0f, 0.0f };
            skor = 0;
            oyunBitti = false;
        }
        // --- 1. GÜNCELLEME ---
        if (!oyunBitti) {

            top.konum.x += top.hiz.x;
            top.konum.y += top.hiz.y;
            top.hiz.y += yercekimi;


            // A) Yerçekimi ve Hareket
            // Kodunuzu buraya yazýn (Hýzý güncelle, Konumu güncelle):

            if (top.konum.x > 560 || top.konum.x < 40) {
                top.hiz.x = -top.hiz.x;
            }


            // B) Duvarlardan Sektirme (Sað ve Sol)
            // Kodunuzu buraya yazýn:




            // C) Týklama Kontrolü (Vektörel Fýrlatma)
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointCircle(GetMousePosition(), top.konum, top.yaricap)) {

                // 1. Yukarý Fýrlat
                top.hiz.y = -ziplamaGucu;
                // 2. Yana Fýrlat (YENÝ GÖREV)
                // Topun merkezi ile fare arasýndaki farký hýza dönüþtürün.
                // Kodunuzu buraya yazýn:
                top.hiz.x = (top.konum.x - GetMouseX()) * 0.2f;

                skor++;
            }

            // D) Yere Düþme Kontrolü
            if (top.konum.y > ekranYukseklik + top.yaricap) {
                oyunBitti = true;
            }
        }

        // --- 2. ÇÝZÝM ---
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!oyunBitti) {
                // Topu Çiz
                DrawCircleV(top.konum, top.yaricap, top.renk);

                // Görsel Ýpucu: Topun merkezini göster (Küçük nokta)
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
