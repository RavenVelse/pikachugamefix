#include"Console.h"
#include"Normal.h"
#include"Struct.h"
#include"Utility.h"
#pragma comment (lib, "winmm.lib")
using namespace std;

int main() {
    SetUpWindow(200, 30);

    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);

    MainMenu();
    int size = 4;
    board** table = new board * [size];
    DisplayBoard(table, size);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    PlayerInput(table, size, 2, 0, x1, y1, x2, y2);
    system("cls");
    GoTo(20, 50);
    cout << x1 << " " << y1 << "&" << " " << x2 << " " << y2;
}