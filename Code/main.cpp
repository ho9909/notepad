#include <windows.h>//windows 헤더파일
#include<stdio.h>
#include"resource.h"
#include "Function.h"

//TRUE는 지우고 그리기 FALSE는 위에 그리기

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("2017E7010_메모장");


//메인문(WinMain) 함수호출자(WINAPI-stdcall로 처리됨)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //	WINAPI : 윈도우 프로그램이라는 의미
	LPSTR lpszCmdLine, int nCmdShow)							 //	hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{																 //	szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
	HWND	hwnd;												 //	iCmdShow : 윈도우가 화면에 출력될 형태
	MSG		msg;
	WNDCLASS WndClass;											 //	WndClass 라는 구조체 정의									 
	WndClass.style = CS_SAVEBITS;					 //	출력스타일 -> 가려진 윈도우는 WM_PAINT메세지 발생 안함
	WndClass.lpfnWndProc = (WNDPROC)WndProc;								 //	프로시저 함수명
	WndClass.cbClsExtra = 0;									 //	O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra = 0;									 //	O/s 사용 여분 메모리 (Window)
	WndClass.hInstance = hInstance;								 //	응용 프로그램 ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 //	아이콘 유형
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM);				 //	커서 유형-> I로 설정해놓음
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	배경색   
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);								 //	메뉴 이름
	WndClass.lpszClassName = lpszClass;							 //	클래스 이름
	RegisterClass(&WndClass);									 //	앞서 정의한 윈도우 클래스의 주소

	hwnd = CreateWindow(lpszClass,								 //	윈도우가 생성되면 핸들(hwnd)이 반환 밑에는 인자들
		lpszClass,												 //	윈도우 클래스, 타이틀 이름
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,		 //	윈도우 스타일
		CW_USEDEFAULT,											 //	윈도우 위치, x좌표
		CW_USEDEFAULT,											 //	윈도우 위치, y좌표
		600,											 //	윈도우 폭   
		400,											 //	윈도우 높이   
		NULL,												 //	부모 윈도우 핸들	 
		NULL,													 //	메뉴 핸들
		hInstance,    											 //	응용 프로그램 ID
		NULL     												 //	생성된 윈도우 정보
		);
	ShowWindow(hwnd, nCmdShow);									 //	윈도우의 화면 출력
	UpdateWindow(hwnd);											 //	O/S 에 WM_PAINT 메시지 전송

	while (GetMessage(&msg, NULL, 0, 0))						 //	WinProc()에서 PostQuitMessage() 호출 때까지 처리
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //	WinMain -> WinProc  
	}
	return (int)msg.wParam;
}


HDC hdc;

int len;//현재 문자열
int s_len;//총 문자열
int bs_len;//전 라인의 총 문자열

int line;//현재 문자열의 행
int s_line;//총 라인의 사이즈
int insert_flag=0;//인서트 프레그
int tab_num;//탭할때 필요한 숫자
int i=0,j=0,k=0;

//int yPos;//스크롤 할 때 필요
//int xPos;


SIZE size;//문자의 크기를 정해주는 변수
TCHAR str[100][1000];//문자열을 저장 할 공간
int Arr_len[100][1000];//문자 하나하나의 길이가 들어갈 배열
int beforesize=0; //전의 크기를 기억해주는 변수



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;//글자의 크기,색깔등의 정보가 들어있는 구조체


	//static TCHAR str[100][1000];//문자열을 저장 할 공간		-> static을 쓰면 전역변수처럼 쓸 수 있다



	switch (iMsg) {

	case WM_SETFOCUS://프로그램이 포커싱 되었을 때
		CreateCaret(hwnd, NULL, 1, 14);//캐럿을 만들어 준다.
		ShowCaret(hwnd);//캐럿을 보여준다.  
		break;

	case WM_KILLFOCUS://프로그램이 아웃 포커싱 되었을 때
		HideCaret(hwnd);//캐럿을 숨겨준다.
		DestroyCaret();//캐럿을 지워준다.
		break;

	case WM_CREATE://프로그램이 처음 실행될시 한번만 발생되는 초기화 메시지
		len = 0;
		s_len = 0;
		line = 0;
		s_line = 0;
		break;

	case WM_KEYDOWN:
		switch (wParam) {

		case VK_LEFT://좌측 커서 이동키
			Left( hwnd);
			break;

		case VK_RIGHT://우측 커서 이동키
			Right( hwnd);
			break;

		case VK_UP://위쪽 커서 이동키
			Up( hwnd);
			break;

		case VK_DOWN://아래쪽 커서 이동키
			Down( hwnd);
			break;

		case VK_HOME://Home키
			Home(hwnd);
			break;

		case VK_END://End키
			End( hwnd);
			break;

		case VK_INSERT://Insert 키
			Insert();
			break;

		case VK_DELETE://Delete 키
			Delete( hwnd);
			break;  

		case VK_TAB://Tab키
			Tab( hwnd);
			break;

		}//키다운
		break;

	case WM_CHAR: //키보드 입력시 발생된다. 값은wParam에서 받아온다.
		switch (wParam) {

		case VK_RETURN://Enter
			Enter(hwnd);
			break;
		case VK_BACK: //Backspace		
			Back( hwnd);
			break;

		default://문자를 받으면 출력해준다
			if((TCHAR)wParam !=  VK_TAB)//탭이 아닐 시
			{
				Tchar( hwnd,  wParam);
			}
		}//스위치 끝

		//입력이 끝날 때 마다  캐럿의 위치를 바꿔줘야한다.
		hdc=GetDC(hwnd);//바뀐 윈도우의 정보를 가져온다.
		GetTextExtentPoint(hdc,str[line],len,&size); //GetTextExtentPoint는 문자열의 폭과 높이를 계산해준다.

		if(len==1)
		{
			Arr_len[line][len-1] = size.cx;
			beforesize=size.cx;
		}
		else if(len==0)//홈키 누른 후 입력
		{
			Arr_len[line][len]=size.cx;
			beforesize=size.cx;
		}
		else
		{
			Arr_len[line][len-1]= size.cx - beforesize;
			beforesize=size.cx;
		}


		SetCaretPos(5+size.cx,20*line);//캐럿의 위치를 바꿔주는                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               역할.
		InvalidateRect(hwnd, NULL, TRUE);

		break;//차 끝

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (i = 0; i < s_line + 1; i++)
			TextOut(hdc, 5, i*20, str[i], lstrlen(str[i]));
		//한줄에 20 만큼 나중에 화살표가 생기면 line 자
		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);//0이면 프로그램 종료
		return 0;



	case WM_COMMAND://프로그램 실행중 사용자가 메뉴 항목을 선택하면 WM_COMMAND 메세지 발생


		switch(wParam) {

		case ID_KHS_NEW://파일 새로 만들기
			KHS_new_m( hwnd);
			break;

		case ID_KHS_OPEN: //파일 열기
			KHS_open_m( hwnd);
			break;

		case ID_KHS_SAVE://파일 저장
			KHS_save( hwnd, 0);

			break;

		case ID_KHS_QUIT://프로그램 종료
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}

		break;

	}//스위치 끝

	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //	CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}
