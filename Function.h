#pragma once

#include <Windows.h>
#include"resource.h"


extern HDC hdc;

extern int len;//현재 문자열
extern int s_len;//총 문자열
extern int bs_len;//전 라인의 총 문자열

extern int line;//현재 문자열의 행
extern int s_line;//총 라인의 사이즈
extern int insert_flag;//인서트 프레그
extern int tab_num;//탭할때 필요한 숫자
extern int i,j,k;

extern SIZE size;//문자의 크기를 정해주는 변수
extern TCHAR str[100][1000];//문자열을 저장 할 공간
extern int Arr_len[100][1000];//문자 하나하나의 길이가 들어갈 배열
extern int beforesize; //전의 크기를 기억해주는 변수



//KEYDOWN
//01)방향키
void Left(HWND hwnd);
void Right(HWND hwnd);
void Up(HWND hwnd);
void Down(HWND hwnd);
//02)버튼 모음
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
