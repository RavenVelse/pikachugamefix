#include"Console.h"
#include"Normal.h"
#include"Struct.h"
#include"Utility.h"
#include"Difficult.h"
#pragma comment (lib, "winmm.lib")

using namespace std;

int main() 
{
    int mode = 0;
    int size = 0;
    SetUpWindow(200, 30);
    PlayerBoard player;
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);
    while (true)
    {
        MainMenu(player, mode, size);
        if (mode == 1)
        {
            Normal(player, size);
        }
        else if (mode == 2)
        {
            Difficult(player, size);
        }
        GameOver(player);
    }

}