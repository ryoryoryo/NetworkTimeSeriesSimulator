// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
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