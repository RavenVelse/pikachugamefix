#include"Utility.h"
#pragma comment (lib, "winmm.lib")
using namespace std;
// Set position on screen
void GoTo(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}
// Disable CLOSE, MINIMIZE,MAXIMIZE button
void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    // CHoose 1 to delete CLOSE button
    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    // Choose 1 to delete MINIMIZE button
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    // CHoose 1 to delete MAXIMIZE button
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}
// Set Window buffer size
void SetScreenBufferSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}
// Set Window screen size
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
// Hide cursor on the window screen
void HideCursor(bool visible) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
// Hide scrollbar on the window
void HideScrollBar() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);

    COORD new_screen_buffer_size;

    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;

    SetConsoleScreenBufferSize(console, new_screen_buffer_size);
}
// Set up window with all prototype above
// Tutorial: https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console
void SetUpWindow(int width, int height) {
    // Set up screen buffer size
    SetScreenBufferSize(width, height);
    // Set up console window title 
    SetConsoleTitle(L"PoKeMon with me");
    // Set up window size 
    SetWindowSize(width, height);
    // Hide Cursor
    HideCursor(0);
    // Disable CLOSE,MINIMIZE, MAXIMIZE button
    DisableCtrButton(1, 1, 1);
    // Hide scroll bar on the screen
    HideScrollBar();
}
// Set central position for text 
int GotoCentral(int width, string Text) {
    width = (width - Text.length()) / 2;
    return width;
}
// Choose the color for background and text
void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
// Color the background and text 
void Highlight(int x, int y, int width, int height, int BackColor, int TextColor, string Text) {
    SetColor(BackColor, TextColor);
    for (int iy = y + 1; iy <= y + height - 1; iy++) {
        for (int ix = x + 1; ix <= x + width - 1; ix++) {
            GoTo(ix, iy);
            cout << " ";
        }
    }
    int temp1 = GotoCentral(width, Text);
    GoTo(x + temp1 + 1, y + height / 2);
    cout << Text;
}
//Read and then draw on the console screen
void ReadAndDraw(string filename, int line, int x, int y)
{
    ifstream fin;
    string* dong = new string[line];
    fin.open(filename);
    for (int i = 0; i < line; i++)
    {
        getline(fin, dong[i]);
    }
    fin.close();
    for (int i = 0; i < line; i++)
    {
        GoTo(x, y);
        cout << dong[i] << endl;
        y++;
    }
}
void SaveFileBi(string filename) {
    PlayerBoard PB;
    ofstream fout;
    fout.open(filename, ios::binary | ios :: app);
    if (!fout.good()) {
        return;
    }
    fout.write((char*) & PB, sizeof(PlayerBoard));
    fout.close();
}
void ReadBiandPrint(string filename) {
    PlayerBoard;
    int x = 1;
    int y = 8;
    ifstream fin;
    fin.open(filename, ios::binary | ios::in);
    fin.seekg(0, ios::end);
    int num = fin.tellg() / sizeof(PlayerBoard);
    fin.seekg(0, ios::beg);
    PlayerBoard* player = new PlayerBoard[num];
    for (int i = 0; i < num; i++) {
        fin.read((char*)&player[i], sizeof(PlayerBoard));
    }
    for (int i = 0; i < num; i++) {
        if(i == 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        }if (i == 1) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }if (i == 2) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        }
        GoTo(x, y);
        cout << player[i].num;
        GoTo(x + 5, y);
        cout << player[i].name;
        GoTo(x + 90, y);
        cout << player[i].date;
        GoTo(x + 110, y);
        cout << player[i].score;
        y += 2;
    }
    fin.close();
    delete[] player;
}
void DrawBox(int x, int y, char c)
{
    int w = 7;
    int h = 3;
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            GoTo(x, y);
        }
        else
        {
            GoTo(x, y + +1 + h);
        }
        for (int j = 0; j < w; j++)
        {
            cout << "-"; // ve ngang
        }
    }
    y++;
    x--;
    for (int i = 0; i < 3; i++)
    {
        GoTo(x, y + i);
        if (i == 1)
        {
            cout << '|' << "   " << c << "   " << '|';
        }
        else
        {
            cout << '|' << "       " << '|'; // ve canh doc
        }
    }
    cout << endl;
}

void DeleteBox(int x, int y, board** table, int index1, int index2)
{
    table[index1][index2].c = ' ';
    table[index1][index2].empty = true;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int ytemp = y, xtemp = x;
    for (int i = 0; i < 2; i++)
    {
        GoTo(x, ytemp);
        for (int j = 0; j < 8; j++)
        {
            cout << " ";
        }
        ytemp += 4;
    }
    for (int i = 1; i < 4; i++)
    {
        GoTo(x , y + i);
        cout << "         ";
    }
}

void DrawStatusBoard(PlayerBoard player)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    GoTo(84, 1);
    cout << "STATUS BOARD";
    GoTo(71, 2);
    cout << "- Player name: " << player.name;
    GoTo(71, 3);
    cout << "- Points: " << "    ";// xoa cho trung` neu nhu diem < 0
    GoTo(81, 3);
    cout << player.score;
    GoTo(71, 4);// dia chi thoi gian
    cout << "- Time left: ";
    GoTo(71, 5);
    cout << "- Char match: ";
    GoTo(71, 6);
    cout << "- Matching style: ";
    GoTo(71, 7);
    cout << "- Help: ";
    GoTo(80, 13);
    cout << "RULES AND KEYS CONTROL";
    GoTo(71, 14);
    cout << "- Each match will give you 100 points";
    GoTo(71, 15);
    cout << "- Using help will cost you 200 points";
    GoTo(71, 16);
    cout << "- For each minutes that you have left";
    GoTo(71, 17);
    cout << "will give you minutes * 100 points";
    GoTo(71, 18);
    cout << "- Press arrow keys to move, enter to ";
    GoTo(71, 19);
    cout << "choose and H to receive help";
    for (int i = 0; i <= 40; i++)
    {
        GoTo(70 + i, 0);
        cout << "-";
        GoTo(70 + i, 12);
        cout << "-";
        GoTo(70 + i, 20);
        cout << "-";
    }
    for (int i = 1; i < 20; i++)
    {
        GoTo(70, i);
        cout << "|";
        GoTo(110, i);
        cout << "|";
    }
}

void Timer(bool result,int min,int sec )
{
    
    while (result)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        if (min == 0 && sec == 0)
        {
            result = false;
        }
        GoTo(85, 4);
        if (min < 10)
        {
            cout << " " << min;
        }
        else
        {
            cout << min;
        }
        cout << ":";
        if (sec < 10)
        {
            cout << " " << sec;
        }
        else
        {
            cout << sec;
        }
        if (sec == 0)
        {
            min--;
            sec = 60;
        }
        Sleep(1000);
        sec--;
    }
}