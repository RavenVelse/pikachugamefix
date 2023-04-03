#pragma once
#include"Console.h"
#include"Struct.h"

#define MAXLB 100
using namespace std;
void GoTo(SHORT posX, SHORT posY);
void DisableCtrButton(bool Close, bool Min, bool Max);
void SetScreenBufferSize(SHORT width, SHORT height);
void SetWindowSize(SHORT width, SHORT height);
void HideCursor(bool visible);
void HideScrollBar();
void SetUpWindow(int width, int height);
int GotoCentral(int width, string Text);
void SetColor(int backgound_color, int text_color);
void Highlight(int x, int y, int width, int height, int BackColor, int TextColor, string Text);
void ReadAndDraw(string filename, int line, int x, int y);
void ReadFile(string filename, PlayerBoard PB[MAXLB], int& NumPlayer);
void SaveFile(string filename, PlayerBoard PB[MAXLB], int NumPlayer);
void DeleteBox(int x, int y, board** table, int index1, int index2);
void DrawStatusBoard();
