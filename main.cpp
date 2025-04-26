#include <windows.h>//windows �������
#include<stdio.h>
#include"resource.h"
#include "Function.h"

//TRUE�� ����� �׸��� FALSE�� ���� �׸���

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("2017E7010_�����̸޸���");


//���ι�(WinMain) �Լ�ȣ����(WINAPI-stdcall�� ó����)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //	WINAPI : ������ ���α׷��̶�� �ǹ�
	LPSTR lpszCmdLine, int nCmdShow)							 //	hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{																 //	szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
	HWND	hwnd;												 //	iCmdShow : �����찡 ȭ�鿡 ��µ� ����
	MSG		msg;
	WNDCLASS WndClass;											 //	WndClass ��� ����ü ����									 
	WndClass.style = CS_SAVEBITS;					 //	��½�Ÿ�� -> ������ ������� WM_PAINT�޼��� �߻� ����
	WndClass.lpfnWndProc = (WNDPROC)WndProc;								 //	���ν��� �Լ���
	WndClass.cbClsExtra = 0;									 //	O/S ��� ���� �޸� (Class)
	WndClass.cbWndExtra = 0;									 //	O/s ��� ���� �޸� (Window)
	WndClass.hInstance = hInstance;								 //	���� ���α׷� ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 //	������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM);				 //	Ŀ�� ����-> I�� �����س���
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	����   
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);								 //	�޴� �̸�
	WndClass.lpszClassName = lpszClass;							 //	Ŭ���� �̸�
	RegisterClass(&WndClass);									 //	�ռ� ������ ������ Ŭ������ �ּ�

	hwnd = CreateWindow(lpszClass,								 //	�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ �ؿ��� ���ڵ�
		lpszClass,												 //	������ Ŭ����, Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,		 //	������ ��Ÿ��
		CW_USEDEFAULT,											 //	������ ��ġ, x��ǥ
		CW_USEDEFAULT,											 //	������ ��ġ, y��ǥ
		600,											 //	������ ��   
		400,											 //	������ ����   
		NULL,												 //	�θ� ������ �ڵ�	 
		NULL,													 //	�޴� �ڵ�
		hInstance,    											 //	���� ���α׷� ID
		NULL     												 //	������ ������ ����
		);
	ShowWindow(hwnd, nCmdShow);									 //	�������� ȭ�� ���
	UpdateWindow(hwnd);											 //	O/S �� WM_PAINT �޽��� ����

	while (GetMessage(&msg, NULL, 0, 0))						 //	WinProc()���� PostQuitMessage() ȣ�� ������ ó��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //	WinMain -> WinProc  
	}
	return (int)msg.wParam;
}


HDC hdc;

int len;//���� ���ڿ�
int s_len;//�� ���ڿ�
int bs_len;//�� ������ �� ���ڿ�

int line;//���� ���ڿ��� ��
int s_line;//�� ������ ������
int insert_flag=0;//�μ�Ʈ ������
int tab_num;//���Ҷ� �ʿ��� ����
int i=0,j=0,k=0;

//int yPos;//��ũ�� �� �� �ʿ�
//int xPos;


SIZE size;//������ ũ�⸦ �����ִ� ����
TCHAR str[100][1000];//���ڿ��� ���� �� ����
int Arr_len[100][1000];//���� �ϳ��ϳ��� ���̰� �� �迭
int beforesize=0; //���� ũ�⸦ ������ִ� ����



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;//������ ũ��,������� ������ ����ִ� ����ü


	//static TCHAR str[100][1000];//���ڿ��� ���� �� ����		-> static�� ���� ��������ó�� �� �� �ִ�



	switch (iMsg) {

	case WM_SETFOCUS://���α׷��� ��Ŀ�� �Ǿ��� ��
		CreateCaret(hwnd, NULL, 1, 14);//ĳ���� ����� �ش�.
		ShowCaret(hwnd);//ĳ���� �����ش�.  
		break;

	case WM_KILLFOCUS://���α׷��� �ƿ� ��Ŀ�� �Ǿ��� ��
		HideCaret(hwnd);//ĳ���� �����ش�.
		DestroyCaret();//ĳ���� �����ش�.
		break;

	case WM_CREATE://���α׷��� ó�� ����ɽ� �ѹ��� �߻��Ǵ� �ʱ�ȭ �޽���
		len = 0;
		s_len = 0;
		line = 0;
		s_line = 0;
		break;

	case WM_KEYDOWN:
		switch (wParam) {

		case VK_LEFT://���� Ŀ�� �̵�Ű
			Left( hwnd);
			break;

		case VK_RIGHT://���� Ŀ�� �̵�Ű
			Right( hwnd);
			break;

		case VK_UP://���� Ŀ�� �̵�Ű
			Up( hwnd);
			break;

		case VK_DOWN://�Ʒ��� Ŀ�� �̵�Ű
			Down( hwnd);
			break;

		case VK_HOME://HomeŰ
			Home(hwnd);
			break;

		case VK_END://EndŰ
			End( hwnd);
			break;

		case VK_INSERT://Insert Ű
			Insert();
			break;

		case VK_DELETE://Delete Ű
			Delete( hwnd);
			break;  

		case VK_TAB://TabŰ
			Tab( hwnd);
			break;

		}//Ű�ٿ�
		break;

	case WM_CHAR: //Ű���� �Է½� �߻��ȴ�. ����wParam���� �޾ƿ´�.
		switch (wParam) {

		case VK_RETURN://Enter
			Enter(hwnd);
			break;
		case VK_BACK: //Backspace		
			Back( hwnd);
			break;

		default://���ڸ� ������ ������ش�
			if((TCHAR)wParam !=  VK_TAB)//���� �ƴ� ��
			{
				Tchar( hwnd,  wParam);
			}
		}//����ġ ��

		//�Է��� ���� �� ����  ĳ���� ��ġ�� �ٲ�����Ѵ�.
		hdc=GetDC(hwnd);//�ٲ� �������� ������ �����´�.
		GetTextExtentPoint(hdc,str[line],len,&size); //GetTextExtentPoint�� ���ڿ��� ���� ���̸� ������ش�.

		if(len==1)
		{
			Arr_len[line][len-1] = size.cx;
			beforesize=size.cx;
		}
		else if(len==0)//ȨŰ ���� �� �Է�
		{
			Arr_len[line][len]=size.cx;
			beforesize=size.cx;
		}
		else
		{
			Arr_len[line][len-1]= size.cx - beforesize;
			beforesize=size.cx;
		}


		SetCaretPos(5+size.cx,20*line);//ĳ���� ��ġ�� �ٲ��ִ�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ����.
		InvalidateRect(hwnd, NULL, TRUE);

		break;//�� ��

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (i = 0; i < s_line + 1; i++)
			TextOut(hdc, 5, i*20, str[i], lstrlen(str[i]));
		//���ٿ� 20 ��ŭ ���߿� ȭ��ǥ�� ����� line ��
		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);//0�̸� ���α׷� ����
		return 0;



	case WM_COMMAND://���α׷� ������ ����ڰ� �޴� �׸��� �����ϸ� WM_COMMAND �޼��� �߻�


		switch(wParam) {

		case ID_KHS_NEW://���� ���� �����
			KHS_new_m( hwnd);
			break;

		case ID_KHS_OPEN: //���� ����
			KHS_open_m( hwnd);
			break;

		case ID_KHS_SAVE://���� ����
			KHS_save( hwnd, 0);

			break;

		case ID_KHS_QUIT://���α׷� ����
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}

		break;

	}//����ġ ��

	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //	CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}