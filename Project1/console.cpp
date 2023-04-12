#include"Console.h"

using namespace std;
#define MAXLB 100

// Create the box for the menu
// Tutorial: https://www.youtube.com/watch?v=oDh046cT_Q0
void MenuBox(int x, int y, int width, int height, int TextColor, string Text) {
    // draw the background inside box
    for (int iy = y + 1; iy <= y + height - 1; iy++) {
        for (int ix = x + 1; ix <= x + width - 1; ix++) {
            GoTo(ix, iy);
            cout << " ";
        }
    }
    // draw 2 line from x,y/y + height to x + width,y/y + height
    for (int ix = x; ix <= x + width; ix++) {
        GoTo(ix, y);
        cout << char(196);
        GoTo(ix, y + height);
        cout << char(196);
    }
    // draw 2 line from x/x + width,y to x/x + width, y + height 
    for (int iy = y; iy <= y + height; iy++) {
        GoTo(x, iy);
        cout << char(179);
        GoTo(x + width, iy);
        cout << char(179);
    }
    // draw 4 corner for the box
    GoTo(x, y);
    cout << char(218);
    GoTo(x + width, y);
    cout << char(191);
    GoTo(x, y + height);
    cout << char(192);
    GoTo(x + width, y + height);
    cout << char(217);
    // Get 
    int temp = GotoCentral(width, Text);
    GoTo(x + temp + 1, y + height / 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TextColor);
    cout << Text;
}       
//Tutorial:https://cplusplus.com/forum/beginner/241912/
//Print Menu 
void MainMenu(PlayerBoard& player,int& mode,int& size) {
    int y = 15;
    int x = 45;
    Account acc[100];

    // Print the first box of menu
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    MenuBox(x, y + (0 * 2), 30, 2, 11, "Play");
    // Print the second box of menu
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    MenuBox(x, y + (1 * 2), 30, 2, 11, "LEADERBOARD");
    // Print the third box of menu
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    MenuBox(x, y + (2 * 2), 30, 2, 11, "EXIT");
    // Fix the line which is covered by the box under 
    for (int i = 1; i < 3; i++) {
        GoTo(x, y + (i * 2));
        cout << char(195);
        GoTo(x + 30, y + (i * 2));
        cout << char(180);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    ReadAndDraw("pikachu1.txt", 12, 76, 18);
    ReadAndDraw("titlepokemon.txt", 13, 25, 0);
    ReadAndDraw("pikachu.txt", 14, 1, 16);
    int xp = x, yp = y;
    int xcu = xp, ycu = yp;
    bool loop = true;
    int kt = 0;
    // Move to choose the features
    while (loop) {
        string nd;
        switch (ycu)
        {

        case 15: nd = "PLAY"; break;
        case 17: nd = "LEADERBOARD"; break;
        case 19: nd = "EXIT"; break;
        default:
            break;
        }
        Highlight(xcu + 1, ycu, 28, 2, 16, 11, nd);// Blackened the box before
        xcu = xp;
        ycu = yp;

        switch (yp)
        {
        case 15: nd = "PLAY"; break;
        case 17: nd = "LEADERBOARD"; break;
        case 19: nd = "EXIT"; break;
        default:
            break;
        }
        Highlight(xp + 1, yp, 28, 2, 15, 11, nd);// Hightlight the chosen box
        int ch = _getch();
        // 224: arrow buttons
        if (ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
                //72:up, 80:down, 77:right, 75:left
            case 72:
                if (yp > y)
                    yp -= 2;
                break;
            case 80:
                if (yp < (y + 4))
                    yp += 2;
                else yp = 15;
                break;
            default: break;
            }
        }
        // Enter to choose the feature 
        if (ch == 13) {
            switch (yp) {
            case 15:
                SetColor(0, 0);
                system("cls");
                kt = 1;
                loop = false;
                break;
            case 17:
                kt = 2;
                SetColor(0, 0);
                system("cls");
                loop = false;
                break;
            case 19:
                SetColor(0, 0);
                exit(0);
                break;
            }
        }
        else
        {
            if (char(ch) == '0')
                loop = false;
        }
        switch (kt) {
        case 1:
            TutorialMenu();
            NameScreen(acc,player);
            DifficultScreen(mode, size);
            break;
        case 2:
            LeaderBoard(player,mode,size);
            break;
        default:
            break;
        }
    }

}
// Print LeaderBoard menu
void LeaderBoard(PlayerBoard& player, int& mode, int& size) {
    /*SaveFileBi("player.bin",player);*/
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    ReadAndDraw("PlayerTitle.txt", 4, 30, 1);
    int x = 1;
    int y = 8;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    GoTo(1, 6);
    cout << "Top";
    GoTo(6, 6);
    cout << "Player";
    GoTo(56, 6);
    cout << "Achivements";
    GoTo(91, 6);
    cout << "Date";
    GoTo(111, 6);
    cout << "Score";
    ReadBiandPrint("player.bin");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    GoTo(48, 28);
    cout << "Press any key to continue!";
    _getch();
    system("cls");
    MainMenu(player, mode, size);
}
// Print Tutorial screen 
void TutorialMenu() {
    PlaySound(TEXT("effect.wav"), NULL, SND_FILENAME | SND_ASYNC);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    ReadAndDraw("Tutorial.txt", 4, 37, 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    MenuBox(70, 9, 17, 5, 15, "(0,0)");
    MenuBox(87, 9, 17, 5, 15, "(0,1)");
    MenuBox(70, 14, 17, 5, 15, "(1,0)");
    MenuBox(87, 14, 17, 5, 15, "(1,1)");
    GoTo(79, 8);
    cout << "0";
    GoTo(97, 8);
    cout << "1";
    GoTo(67, 11);
    cout << "0";
    GoTo(67, 16);
    cout << "1";
    GoTo(67, 8);
    cout << "x/y";
    GoTo(70, 14);
    cout << char(195);
    GoTo(104, 14);
    cout << char(180);
    GoTo(87, 14);
    cout << char(197);
    GoTo(0, 8);
    cout << "PRESS Arrow keys to move";
    GoTo(0, 9);
    cout << "Press Enter to choose";
    GoTo(0, 10);
    cout << "Find two letters that are the same";
    GoTo(0, 11);
    cout <<"and have atleast one of theese valid paths : ";
    GoTo(0, 12);
    cout << "   I path, L path, Z path, U path";
    GoTo(0, 13);
    cout << "Win condition:";
    GoTo(0, 14);
    cout << "   all the letters have been removed";
    GoTo(0, 15);
    cout << "Note:";
    GoTo(0, 16);
    cout << "   if there is a barrier in the middle of these valid path";
    GoTo(0, 17);
    cout << "   THE MATCH CAN'T BE DONE!!!";
    GoTo(0, 18);
    cout << "Still don't get it??";
    GoTo(0, 19);
    cout << "Don't worry, just play and you will get used to it soon.";
    GoTo(0, 20);
    cout << "Good luck and have fun !!!!";
    GoTo(48, 23);
    cout << "Press any key to continue!";
    _getch();
}
//Print difficult screen
void DifficultScreen(int& mode, int& size) {
    system("cls");
    int x = 45;
    int y = 14;
    GoTo(45, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Choose the difficulty and size";
    MenuBox(x, y + (0 * 2), 30, 2, 15, "NORMAL 4x4");
    MenuBox(x, y + (1 * 2), 30, 2, 15, "NORMAL 6x6");
    MenuBox(x, y + (2 * 2), 30, 2, 15, "HARD   4x4");
    MenuBox(x, y + (3 * 2), 30, 2, 15, "HARD   6x6");
    for (int i = 1; i < 4; i++) {
        GoTo(x, y + (i * 2));
        cout << char(195);
        GoTo(x + 30, y + (i * 2));
        cout << char(180);
    }

    int xp = x, yp = y;
    int xcu = xp, ycu = yp;
    bool loop = true;
    int kt = 1;
    // Move to choose the features
    while (loop) {
        string nd;
        switch (ycu)
        {

        case 14: nd = "NORMAL 4x4"; break;
        case 16: nd = "NORMAL 6x6"; break;
        case 18: nd = "HARD   4x4"; break;
        case 20: nd = "HARD   6x6"; break;
        default:
            break;
        }
        Highlight(xcu, ycu, 30, 2, 16, 15, nd);// Blackened the box before
        xcu = xp;
        ycu = yp;

        switch (yp)
        {
        case 14: nd = "NORMAL 4x4"; break;
        case 16: nd = "NORMAL 6x6"; break;
        case 18: nd = "HARD   4x4"; break;
        case 20: nd = "HARD   6x6"; break;
        default:
            break;
        }
        Highlight(xp, yp, 30, 2, 8, 15, nd);// Hightlight the chosen box

        int ch = _getch();
        // 224: arrow buttons
        if (ch == 224)
        {
            ch = _getch();
            PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            switch (ch)
            {
                //72:up, 80:down, 77:right, 75:left
            case 72:
                if (yp > y)
                    yp -= 2;
                break;
            case 80:
                if (yp < (y + 6))
                    yp += 2;
                break;
            default: break;
            }
        }
        // Enter to choose the feature 
        if (ch == 13) {
                
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            system("cls");
            switch (yp) {
            case 14:
                mode = 1;
                size = 4;
                loop = false;
                break;
            case 16:
                mode = 1;
                size = 6;
                loop = false;
                break;
            case 18: 
                mode = 2;
                size = 4;
                loop = false;
                break;
            case 20:
                mode = 2;
                size = 6;
                loop = false;
                break;
            }
        }
        else
        {
            if (char(ch) == '0')
                loop = false;
        }
    }
}
// Print the name screen 
void Login(PlayerBoard  &player, int num,Account *acc) {

    int loop = true;
    while (loop) {
        SetColor(0, 0);
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        GoTo(50, 14);
        cout << "Your ig name: ";
        fgets(player.name, sizeof(player.name), stdin);
        GoTo(50, 15);
        cout << "Your Password: ";
        fgets(player.pass, sizeof(player.pass), stdin);
        for (int i = 0; i < num; i++) {
            if (strcmp(player.name, acc[i].name) == 1 && strcmp(player.pass, acc[i].pass) == 1) {
                GoTo(45, 18);
                cout << "LOGIN SUCCESFULL!!";
                loop = false;
                system("pause");
            }
            else {
                GoTo(45, 18);
                cout << "LOGIN FAILED!!";
                system("pause");
            }
        }
    }
    GoTo(50, 12);
    cout << "Date (dd/mm/yyyy): ";
    fgets(player.date, sizeof(player.date), stdin);
}
// Print the name screen 
void NameScreen(Account acc[MAXLB], PlayerBoard& player)
{
    ifstream fin;
    fin.open("player.bin", ios::binary | ios::in);
    fin.seekg(0, ios::end);
    int num = fin.tellg() / sizeof(Account);
    fin.seekg(0, ios::beg);
    for (int i = 0; i < num; i++) {
        fin.read((char*)&acc[i], sizeof(Account));
    }

    int x = 45;
    int y = 15;
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    MenuBox(x, y, 30, 2, 11, "LOGIN");
    MenuBox(x, y + 2, 30, 2, 11, "SIGN IN");
    for (int i = 1; i < 2; i++) {
        GoTo(x, y + (i * 2));
        cout << char(195);
        GoTo(x + 30, y + (i * 2));
        cout << char(180);
    }
    int xp = x, yp = y;
    int xcu = xp, ycu = yp;
    bool loop = true;
    int kt = 1;
    while (loop) {
        string nd;
        switch (ycu)
        {

        case 15: nd = "LOGIN"; break;
        case 17: nd = "SIGN IN"; break;
        default:
            break;
        }
        Highlight(xcu + 1, ycu, 28, 2, 16, 11, nd);// Blackened the box before
        xcu = xp;
        ycu = yp;

        switch (yp)
        {
        case 15: nd = "LOGIN"; break;
        case 17: nd = "SIGN IN"; break;
        default:
            break;
        }
        Highlight(xp + 1, yp, 28, 2, 15, 11, nd);// Hightlight the chosen box
        int ch = _getch();
        // 224: arrow buttons
        if (ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
                //72:up, 80:down, 77:right, 75:left
            case 72:
                if (yp > y)
                    yp -= 2;
                break;
            case 80:
                if (yp < (y + 2))
                    yp += 2;
                else yp = 15;
                break;
            default: break;
            }
        }
        // Enter to choose the feature 
        if (ch == 13) {
            switch (yp) {
            case 15:
                SetColor(0, 0);
                system("cls");
                kt = 1;
                loop = false;
                break;
            case 17:
                kt = 2;
                SetColor(0, 0);
                system("cls");
                loop = false;
                break;
            default:
                break;
            }
        }
        else
        {
            if (char(ch) == '0')
                loop = false;
        }       
    }
    switch (kt) {
    case 1:
        Login(player, num, acc);
        break;
    case 2:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        GoTo(50, 14);
        cout << "Your ig name: ";
        fgets(player.name, sizeof(player.name), stdin);
        GoTo(50, 15);
        cout << "Your Password: ";
        fgets(player.pass, sizeof(player.pass), stdin);
        GoTo(50, 16);
        cout << "Date: ";
        fgets(player.date, sizeof(player.date), stdin);
        break;
    default:
        break;
    }
}
// Print the end game screen
void GameOver(bool result)
{   
    if (result == true) {
        // Print the winning screen
        ReadAndDraw("StageCompleted.txt", 5, 30, 12);
        PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Beep(500, 200);
        Beep(678, 400);
        Beep(1268, 200);
        Beep(1105, 1000);
        Beep(1397, 200);
        Beep(1397, 200);
        Beep(1397, 200);
        Beep(1576, 1000);
        GoTo(45, 20);
        cout << "Press any key to continue!!!";
        _getch();
    }
    else {
        //print the losing screen
        ReadAndDraw("GameOver.txt", 6, 45, 12);
        PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Beep(1568, 200);
        Beep(1568, 200);
        Beep(1568, 200);
        Beep(1245, 1000);
        Beep(1397, 200);
        Beep(1397, 200);
        Beep(1397, 200);
        Beep(1175, 1000);
        GoTo(35, 20);
        cout << "Maybe you will get luck next time to win this CHILD's game :>>>>";
        _getch();
    }
}