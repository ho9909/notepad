#pragma once

#include <Windows.h>
#include"resource.h"


extern HDC hdc;

extern int len;//���� ���ڿ�
extern int s_len;//�� ���ڿ�
extern int bs_len;//�� ������ �� ���ڿ�

extern int line;//���� ���ڿ��� ��
extern int s_line;//�� ������ ������
extern int insert_flag;//�μ�Ʈ ������
extern int tab_num;//���Ҷ� �ʿ��� ����
extern int i,j,k;

extern SIZE size;//������ ũ�⸦ �����ִ� ����
extern TCHAR str[100][1000];//���ڿ��� ���� �� ����
extern int Arr_len[100][1000];//���� �ϳ��ϳ��� ���̰� �� �迭
extern int beforesize; //���� ũ�⸦ ������ִ� ����



//KEYDOWN
//01)����Ű
void Left(HWND hwnd);
void Right(HWND hwnd);
void Up(HWND hwnd);
void Down(HWND hwnd);
//02)��ư ����
void Home(HWND hwnd);
void End(HWND hwnd);
void Insert();
void Delete(HWND hwnd);

void Enter(HWND hwnd);

//WM_CHAR
void Back(HWND hwnd);
void Tab(HWND hwnd);
void Tchar(HWND hwnd, WPARAM wParam);

//WM_COMMAND
void KHS_new(HWND hwnd);
void KHS_new_m(HWND hwnd);
void KHS_save(HWND hwnd, int flag);
void KHS_open(HWND hwnd);
void KHS_open_m(HWND hwnd);
