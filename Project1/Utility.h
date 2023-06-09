#pragma once
#include"Console.h"
#include"Struct.h"
#include <thread>
#include <future>

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
void SaveFileBi(string filename,PlayerBoard player);
void ReadBiandPrint(string filename);
void DeleteBox(int x, int y, board** table, int index1, int index2,char bg[][54]);
void DrawStatusBoard(PlayerBoard player);
void ReadBackground(string filename, char bg[][54]);
void PrintBackground(char bg[][54], int x, int y);
void DeleteBoard(board** table, int size);
void DeleteLinkList(int x, int y, node* phead, int index1, int index2);