#include"Utility.h"
#pragma warning(disable : 4996)
#pragma comment (lib, "winmm.lib")
using namespace std;
// Set position on screen
// minutes and second variables
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
void SaveFileBi(string filename,PlayerBoard player) {
    ofstream fout;
    fout.open(filename, ios::binary | ios :: app);
    if (!fout.good()) {
        return;
    }
    fout.write((char*) & player, sizeof(PlayerBoard));
    fout.close();
}
void ReadBi(string filename, PlayerBoard* player, int& num_acc) {
    ifstream fin;
    fin.open(filename, ios::binary | ios::in);
    fin.seekg(0, ios::end);
    num_acc = fin.tellg() / sizeof(PlayerBoard);
    fin.seekg(0, ios::beg);
    PlayerBoard* player = new PlayerBoard[num_acc];
    for (int i = 0; i < num_acc; i++) {
        fin.read((char*)&player[i], sizeof(PlayerBoard));
    }
    fin.close();
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
    // Sắp xếp lại dữ liệu người chơi theo điểm với selection sort
    for (int i = 0; i < num; i++) {
        int maxID = i;
        for (int j = i + 1; j < num; j++) {
            if (player[j].score >= player[maxID].score) {
                maxID = j;
            }
            swap(player[i].name, player[maxID].name);
            swap(player[i].date, player[maxID].date);
            swap(player[i].pass, player[maxID].pass);
            swap(player[i].score, player[maxID].score);
            swap(player[i].achive1, player[maxID].achive1);
            swap(player[i].achive2, player[maxID].achive2);
            swap(player[i].achive3, player[maxID].achive3);
        }
    }
        for (int i = 0; i < num && i < 10; i++) {
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
        GoTo(x + 55, y);
        if ((player[i].achive1 == 1 && player[i].achive2 == 0 && player[i].achive3 == 0) || (player[i].achive1 == 0 && player[i].achive2 == 1 && player[i].achive3 == 0) || (player[i].achive1 == 0 && player[i].achive2 == 0 && player[i].achive3 == 1)) {
            cout << 1;
        }
        else if ((player[i].achive1 == 1 && player[i].achive2 == 1 && player[i].achive3 == 0) || (player[i].achive1 == 0 && player[i].achive2 == 1 && player[i].achive3 == 1) || (player[i].achive1 == 1 && player[i].achive2 == 0 && player[i].achive3 == 1)) {
            cout << 2;
        }
        else if (player[i].achive1 == 1 && player[i].achive2 == 1 && player[i].achive3 == 1) {
            cout << 3;
        }
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

void DeleteBox(int x, int y, board** table, int index1, int index2,char bg[][54])
{ 
    table[index1][index2].c = ' ';
    table[index1][index2].empty = true;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
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
        GoTo(x, y + i);
        cout << "         ";
    }
}
void ReadBackground(string filename, char bg[][54]) {
    ifstream fin;
    fin.open(filename, ios :: in);
    if (!fin.is_open()) {
        system("exit");
    }
    else {
        fin.ignore();
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 54; j++) {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }

}
void PrintBackground(char bg[][54], int x,int y) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            GoTo(x + j, y + i);
            cout << bg[y +i][x +j];
        }
    }
}
void DrawStatusBoard(PlayerBoard player)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    GoTo(84, 1);
    cout << "STATUS BOARD";
    GoTo(71, 2);
    cout << "- Date: " << player.date;
    GoTo(71, 3);
    cout << "- Player name: " << player.name;
    GoTo(71, 4);
    cout << "- Points: " << "    ";// xoa cho trung` neu nhu diem < 0
    GoTo(81, 4);
    cout << player.score;
    GoTo(71, 5);// dia chi thoi gian
    cout << "- Time left: ";
    GoTo(71, 6);
    cout << "- Char match: ";
    GoTo(71, 7);
    cout << "- Matching style: ";
    GoTo(71, 8);
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
bool CheckLeapYear(char x) {
    if ((x % 4 == 0 && x % 100 != 0) || x % 400 == 0) {
        return true;
    }
    return false;
}
bool CheckDay(char* d,char *m, char *y) {

    string day(d);
    int d1 = stoi(day);
    string month(m);
    int m1 = stoi(month);
    string year(y);
    int y1 = stoi(year);
    if (CheckLeapYear(y1)) {
        switch (m1) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (d1 < 32 && d1> 0) {
                return true;
            }
            else return false;
            break;
        case 4: case 6: case 9 : case 11:
            if (d1 < 31 && d1 >0) {
                return true;
            }
            else return false;
            break;
        case 2:
            if (d1 < 30 && d1 > 0) {
                return true;
            }
            else return false;
        default:
            return false;
        }
    }
    else if (!CheckLeapYear(y1)) {
        switch (m1) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (d1 < 32 && d1> 0) {
                return true;
            }
            else return false;
            break;
        case 4: case 6: case 9: case 11:
            if (d1 < 31 && d1 >0) {
                return true;
            }
            else return false;
            break;
        case 2:
            if (d1 < 29 && d1 > 0) {
                return true;
            }
            else return false;
        default:
            return false;
        }
    }
    return false;
}

