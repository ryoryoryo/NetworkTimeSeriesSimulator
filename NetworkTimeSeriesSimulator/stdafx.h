// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <set>
#include <sstream>

using namespace std;

string readText(string path);
map<int, string> readCsv(string path);
string intToString(int number);
int stringToInt(string s);
int chatToInt(char c);
int GetRandom(int min, int max);