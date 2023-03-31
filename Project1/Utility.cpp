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
