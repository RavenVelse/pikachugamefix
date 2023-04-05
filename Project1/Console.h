#pragma once
#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<string>
#include<fstream>
#include<string>
#include "Struct.h"
#include"Utility.h"
#include <time.h>
#include<mmsystem.h>

using namespace std;
#define MAXLB 100
void MenuBox(int x, int y, int width, int height, int TextColor, string Text);
void DrawBox(int x, int y, char c);
void TutorialMenu(string name, string date);
void LeaderBoard();
void MainMenu(PlayerBoard& player, int& mode,int& size);
void DifficultScreen(int& mode, int& size);
void NameScreen(PlayerBoard& player);