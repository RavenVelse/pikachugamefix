#include"Utility.h"
#include"Struct.h"
#pragma comment (lib, "winmm.lib")
using namespace std;
bool stoptime = 1;
// Set position on screen
void GoTo(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}
char inToA(int k) {
    switch (k)
    {
    case 0:return '0';
    case 1:return '1';
    case 2:return '2';
    case 3:return '3';
    case 4:return '4';
    case 5:return '5';
    case 6:return '6';
    case 7:return '7';
    case 8:return '8';
    case 9:return '9';
    default:
        break;
    }
}

void insertarray(char* h, Hour* j) {
    int bait = 0;
    bait = j->second;
    h[7] = inToA(bait % 10);
    h[6] = inToA(bait /= 10);

    bait = j->minute;
    h[4] = inToA(bait % 10);
    h[3] = inToA(bait /= 10);

    bait = j->hour;
    h[1] = inToA(bait % 10);
    h[0] = inToA(bait /= 10);

}

bool changetime(Hour* h) {
    if (h->second > 0) --h->second;
    else if (h->minute > 0) {
        h->second = 59;
        --h->minute;
    }
    else if (h->hour > 0)
    {
        --h->hour;
        h->minute = 59;
        h->second = 59;
    }
    else return 0;
    return 1;
}

//dung de in ra mot chuoi thay the ham cout
void WriteBlockChar(char* Arraych, int row, int col, int x, int y, int color)
{
    CHAR_INFO* charater = new CHAR_INFO[row * col];
    for (int i = 0; i < row * col; i++) {
        charater[i].Attributes = color;
        charater[i].Char.UnicodeChar = Arraych[i];
    }
    COORD sizebuff = { col,row };
    COORD pos = { 0,0 };
    SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), charater, sizebuff, pos, &earea);
    delete[] charater;
}

void printClock() {
    Hour h = { 0,0,5 };
    char a[8] = { '0','0',':','0','0',':','0','0' };
    while (stoptime)
    {
        if (!changetime(&h)) stoptime = 0;
        insertarray(a, &h);
        WriteBlockChar(a, 1, 8, 70, 3, 0x004);
        Sleep(970);
    }
    return;
}
void close(DWORD evt) {
    if (evt == CTRL_CLOSE_EVENT) stoptime = 0;
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
    GoTo(x + temp1, y + height / 2);
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
// Read player file
void ReadFile(string filename, PlayerBoard PB[MAXLB], int& NumPlayer) {
    NumPlayer = 1;
    int i = 0;
    ifstream fin;
    fin.open(filename);
    while (!fin.eof()) {
        getline(fin, PB[i].num, '.');
        getline(fin, PB[i].name, '.');
        getline(fin, PB[i].date, '.');
        getline(fin, PB[i].score);
        i++;
        NumPlayer++;
    }
    fin.close();
}
// Save player file after 
void SaveFile(string filename, PlayerBoard PB[MAXLB], int NumPlayer) {
    ofstream fout;
    fout.open(filename);
    for (int i = 0; i < NumPlayer; i++) {
        fout << PB[i].num << "." << PB[i].name << "." << PB[i].date << "." << PB[i].score << endl;
    }
    fout.close();
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
