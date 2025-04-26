#include "Function.h"


//KEYDOWN
//01)방향키
void Left(HWND hwnd)
{
	if(len==0)//맨앞
	{
		if(s_line!=0)// 아예 맨앞이 아닐 때
		{
			line--;
			len = lstrlen(str[line]);
			s_len = len;
			InvalidateRect(hwnd, NULL, TRUE);
		}

	}
	else{
		len--;
	}

	hdc=GetDC(hwnd);
	GetTextExtentPoint(hdc,str[line],len,&size);
	SetCaretPos(5+size.cx,20*line);
	InvalidateRect(hwnd, NULL, TRUE);

}
void Right(HWND hwnd)
{
	if(len==lstrlen(str[line]))//맨뒤
			{
				if(line!=s_line)//아예 맨 뒤가 아닐 떄
				{
					line++;
					len = 0;
					s_len =  lstrlen(str[line]);
					InvalidateRect(hwnd, NULL, TRUE);
				}

			}
			else{
				len++;
			}

			hdc=GetDC(hwnd);
			GetTextExtentPoint(hdc,str[line],len,&size);
			SetCaretPos(5+size.cx,20*line);
			InvalidateRect(hwnd, NULL, TRUE);


}
void Up(HWND hwnd)
{
			if(line!=0)//맨 위가 아닐 때
			{
				bs_len = lstrlen(str[line-1]);//윗 줄
				if(bs_len<len)//윗 줄이 더 짧을 때
				{
					line--;
					len = bs_len;//그 줄의 맨 뒤로
					s_len =   lstrlen(str[line]);
				}
				else//윗 줄이 같거나 더 길 떄 
				{
					line--;
					s_len =   lstrlen(str[line]);
				}
			}

			hdc=GetDC(hwnd);
			GetTextExtentPoint(hdc,str[line],len,&size);
			SetCaretPos(5+size.cx,20*line);
			InvalidateRect(hwnd, NULL, TRUE);
}
void Down(HWND hwnd)
{

		if(line!=s_line)//맨 아래가 아닐 때
			{
				bs_len = lstrlen(str[line+1]);//아랫 줄
				if(bs_len<len)//아래 줄이 더 짧을 때
				{
					line++;
					len = bs_len;//그 줄의 맨 뒤로
					s_len =   lstrlen(str[line]);
				}
				else//아래 줄이 같거나 더 길 떄 
				{
					line++;
					s_len =   lstrlen(str[line]);
				}
			}
			hdc=GetDC(hwnd);
			GetTextExtentPoint(hdc,str[line],len,&size);
			SetCaretPos(5+size.cx,20*line);
			InvalidateRect(hwnd, NULL, TRUE);
}
//02)버튼 모음
void Home(HWND hwnd)
{
			len = 0;
			SetCaretPos(5,20*line);
			InvalidateRect(hwnd, NULL, TRUE);
}
void End(HWND hwnd)
{
	len = lstrlen(str[line]);
			hdc=GetDC(hwnd);
			GetTextExtentPoint(hdc,str[line],len,&size);
			SetCaretPos(5+size.cx,20*line);
			InvalidateRect(hwnd, NULL, TRUE);
}
void Insert()
{
	if(insert_flag==0)
			{
				insert_flag = 1;
			}
			else
			{
				insert_flag = 0;
			}
}
void Delete(HWND hwnd)
{
	 k=0;
			if(len ==s_len)//맨뒤
			{
				if(line!=s_line)//맨 마지막 줄 맨뒤가 아닐 때
				{

					bs_len = lstrlen(str[line+1]);//밑줄의 단어수
					for(i=s_len; i<s_len+bs_len; i++ )//이 전 자리서 부터 현재 라인의 갯수만큼 복사해서 붙여주고
					{
						str[line][i] = str[line+1][k];
						Arr_len[line][i] = Arr_len[line+1][k];
						k++;

					}
					for(i=0;i<bs_len;i++)//원래있던 자리를 지워주고
					{
						str[line+1][i]=NULL;
						Arr_len[line+1][i]=NULL;
					}

					for(i=1; i<s_line-line; i++)//한칸씩 미뤄주는 역할
					{
						k =  lstrlen(str[(line)+i+1]);
						for(j=0; j< k; j++)
						{
							str[line+i][j] = str[(line)+i+1][j];
							Arr_len[line+i][j]  = Arr_len[(line)+i+1][j];
						}
						for(j=0; j< k; j++)
						{
							str[(line)+i+1][j]=NULL;
							Arr_len[(line)+i+1][j]=NULL;
						}
					}

					s_line--;
					s_len= lstrlen(str[line]);


				}
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else
			{
				//뒤에있는게 한칸 씩 지워지기
				for(i=len; i<s_len; i++)
				{
					str[line][i] = str[line][i+1];
				}
				s_len--;
				InvalidateRect(hwnd, NULL, TRUE);

			}
		
		}

void Tab(HWND hwnd)
{

tab_num = len%8;//8로 나눈 나머지 값
			if(len==s_len)//끝 줄일떄
			{
				if(tab_num ==0 )//8로 나누어 떨어지면 원래 8만큼 이동
				{
					for(i=0;i<8;i++)
					{
						str[line][len+i] = ' ';
					}
					len = len+ 8;
					s_len = s_len+8;
				}
				else
				{
					for(i=0;i<8-tab_num;i++)
					{
						str[line][len+i] = ' ';
					}

					len = len+ 8-tab_num;
					s_len = s_len+8-tab_num;
				}


			}
			else//뒤에 글씨가 있을때
			{
				if(tab_num ==0 )//8로 나누어 떨어지면 원래 8만큼 이동
				{
					for(i=0;i<s_len-len;i++)//s_len-len번만큼
					{
						str[line][s_len+7-i] = str[line][s_len-1-i];//맨뒤에서부터 8칸씩 띄어서 옮긴다	
					}
					for(i=0;i<8;i++)//s_len-len번만큼
					{
						str[line][len+i] = ' ';//그 원래 자리 스페이스바로 채워준다.
					}
					s_len = s_len+8;
					len=len+8;

				}
				else
				{
					for(i=0;i<s_len-len;i++)//s_len-len번만큼
					{
						str[line][s_len+7-tab_num-i] = str[line][s_len-1-i];//맨뒤에서부터 8칸씩 띄어서 옮긴다	
					}
					for(i=0;i<8-tab_num;i++)//s_len-len번만큼
					{
						str[line][len+i] =' ';
					}
					len=len+8-tab_num;
					s_len =  s_len+8-tab_num;

				}
			}

			hdc=GetDC(hwnd);
			GetTextExtentPoint(hdc,str[line],len,&size);
			SetCaretPos(5+size.cx,20*line);
			InvalidateRect(hwnd, NULL, FALSE);
			}


//WM_CHAR
void Enter(HWND hwnd)
{

			if(len == lstrlen(str[line]))//맨 뒤에서 엔터
			{

				if(line==s_line)//맨 끝 인데 맨 끝 줄일때
				{
					line++;
					s_line++;
					len = 0;
					s_len = 0;
					InvalidateRect(hwnd, NULL, TRUE);
				}
				else//맨 끝 인데 중간 줄일때
				{
					int k ;
					for(i=0; i<s_line-line; i++)//한칸씩 미뤄주는 역할
					{
						k =  lstrlen(str[(s_line)-i]);
						for(j=0; j< k; j++)
						{
							str[(s_line+1)-i][j] = str[(s_line)-i][j];
							Arr_len[(s_line+1)-i][j] = Arr_len[(s_line)-i][j];
						}
						for(j=0; j< k; j++)
						{
							str[(s_line)-i][j]=NULL;
							Arr_len[(s_line)-i][j]=NULL;
						}
					}
					line++;
					s_line++;
					len = 0;
					s_len = 0;
					InvalidateRect(hwnd, NULL, FALSE);
				}
			}
			else//문장 중간에서 엔터를 쳤을 때
			{
				if(line==s_line)//중간인데 맨 끝 줄일때
				{
					for(i=0; i<s_len-len; i++)//한 칸 밑으로 옮겨주고
					{
						str[line+1][i] = str[line][i+len];
						Arr_len[line+1][i] = Arr_len[line][i+len];
					}
					for(i=len; i<s_len; i++)//원래 있던 자리 지워주고
					{
						str[line][i]=NULL;
						Arr_len[line][i]=NULL;
					}
					line++;
					s_line++;
					len=0;
					s_len =  lstrlen(str[line]);
					InvalidateRect(hwnd, NULL, TRUE);
				}
				else//중간인데 중간 줄일때
				{
					int k ;
					for(i=0; i<s_line-line; i++)//한칸씩 미뤄주는 역할
					{
						k =  lstrlen(str[(s_line)-i]);
						for(j=0; j< k; j++)
						{
							str[(s_line+1)-i][j] = str[(s_line)-i][j];
							Arr_len[(s_line+1)-i][j] = Arr_len[(s_line)-i][j];
						}
						for(j=0; j< k; j++)
						{
							str[(s_line)-i][j]=NULL;
							Arr_len[(s_line)-i][j]=NULL;
						}
					}
					for(i=0; i<s_len-len;i++)//현재 줄의 캐럿 뒤에문장을 다음줄로 옮겨준다.
					{
						str[line+1][i] = str[line][len+i];
						Arr_len[line+1][i] = Arr_len[line][len+i];
					}
					for(i=len;i<s_len;i++)//원래있던 문장을 지운다
					{
						str[line][i] = NULL;
						Arr_len[line][i] = NULL;
					}
					line++;
					s_line++;
					len = 0;
					s_len = lstrlen(str[line]);
					InvalidateRect(hwnd, NULL, FALSE);
				}
			}



}
void Back(HWND hwnd)
{


			if(len==0)//줄의 맨 앞
			{				
				int k=0;

				if(line!=0)//맨 첫줄의 맨 앞이 아닐때
				{
					bs_len = lstrlen(str[line-1]);//윗줄의 단어수
					for(i=bs_len; i<bs_len+ s_len; i++ )//이 전 자리서 부터 현재 라인의 갯수만큼 복사해서 붙여주고
					{
						str[line-1][i] = str[line][len+k];
						Arr_len[line-1][i] = Arr_len[line][len+k];
						k++;

					}
					for(i=0;i<s_len;i++)//원래있던 자리를 지워주고
					{
						str[line][i]=NULL;
						Arr_len[line][i]=NULL;
					}
					//뒤에 있는걸 한칸식 당겨준다



					for(i=0; i<s_line-line; i++)//한칸씩 미뤄주는 역할
					{
						k =  lstrlen(str[(line)+i+1]);
						for(j=0; j< k; j++)
						{
							str[line+i][j] = str[(line)+i+1][j];
							Arr_len[line+i][j]  = Arr_len[(line)+i+1][j];
						}
						for(j=0; j< k; j++)
						{
							str[(line)+i+1][j]=NULL;
							Arr_len[(line)+i+1][j]=NULL;
						}
					}

					line--;
					s_line--;
					len=bs_len;
					s_len= lstrlen(str[line]);
				}


			}
			else//중간이나 끝
			{

				for(i=len; i<s_len;i++)
				{
					str[line][i-1] = str[line][i];
				}
				str[line][s_len-1] = NULL;
				len--;
				s_len--;
				InvalidateRect(hwnd, NULL, FALSE);

			}




}
void Tchar(HWND hwnd, WPARAM wParam)
{

if(insert_flag==0)
				{
					//현재위치가 NULL이면 그 위 치에 출력 NULL이 아니면 한칸 씩 미루고 출력 
					if(str[line][len]==NULL)
					{
						str[line][len] = (TCHAR)wParam;
						len++;
						s_len++;
						InvalidateRect(hwnd, NULL, FALSE);
				
					}
					else
					{
						//i는 현재line의 len수 만큼부터 현재 len까지의 뒤로 밀어준다.
						for(i= lstrlen(str[line]) ; i>len; i--)
						{
							str[line][i] = str[line][i-1];
							Arr_len[line][i] = Arr_len[line][i-1];
						}

						str[line][len] = (TCHAR)wParam;
						len++;
						s_len++;
						InvalidateRect(hwnd, NULL, FALSE);
						
					}
					
				}
				else//인서트가 눌린 경우
				{

					str[line][len] = (TCHAR)wParam;
					len++;
					s_len++;
					InvalidateRect(hwnd, NULL, FALSE);


				}
}

//WM_COMMAND
void KHS_new(HWND hwnd)
{
	memset(str,0,sizeof(str)); 
	memset(Arr_len,0,sizeof(Arr_len));
	line=0;
	s_line=0;
	len=0;
	s_len=0;
	SetCaretPos(5,0);
	InvalidateRect(hwnd, NULL, TRUE);
}
void KHS_save(HWND hwnd, int flag)
{

	TCHAR op_str[300] = {0,};
	TCHAR lpstrFile[MAX_PATH] = L"";


	HANDLE fp; 
	DWORD readn;  


	//저장용
	WORD wc = 0xFEFF; //헤더를 쓰는 칭구....유니코드를 뜻할걸?
	DWORD dwBytes = 0;


	OPENFILENAME OFN2;

	memset(&OFN2,0,sizeof(OPENFILENAME));
	OFN2.lStructSize = sizeof(OPENFILENAME);
	OFN2.hwndOwner = hwnd;
	OFN2.lpstrFilter = TEXT("모든 파일(*.*)\0*.*\0텍스트 파일\0*.txt;*.doc\0");
	OFN2.lpstrFile = lpstrFile; //lpstrFile
	OFN2.Flags = OFN_NOCHANGEDIR;
	OFN2.nMaxFile = MAX_PATH;



	if(GetSaveFileName(&OFN2) != 0) //다이얼로그 열기
	{


		fp = CreateFile(OFN2.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		// 유니코드임을 알리는 BOM
		WriteFile(fp, &wc, 2, &dwBytes, NULL);

		// 유니코드 텍스트 길이만큼 기록한다
		for(i=0;i<=s_line;i++)
		{
			WriteFile(fp, str[i], lstrlen(str[i]) * sizeof(TCHAR), &readn, NULL);
			WriteFile(fp, "\r", 2, &readn, NULL);//맨 앞으로
			WriteFile(fp, "\n", 2, &readn, NULL);//개행
		}
		CloseHandle(fp); // 이제 필요없어진 핸들은 닫는다
		MessageBox(hwnd, TEXT("텍스트 파일로 저장하였습니다."), TEXT("WriteFile"), MB_OK);

		if(flag==1)
		{
			KHS_new(hwnd);
		}


	}
	else
	{
		MessageBox(hwnd, TEXT("텍스트 파일을 저장하지 못했습니다."), 0, MB_OK);

	}
}
void KHS_open(HWND hwnd)
{
	TCHAR op_str[300] = {0,};
	TCHAR lpstrFile[MAX_PATH] = L"";
	TCHAR buf[1024];

	HANDLE fp; 
	DWORD readn;  


	memset(buf,0,sizeof(buf));

	OPENFILENAME OFN;
	memset(&OFN,0,sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hwnd;
	OFN.lpstrFilter = TEXT("모든 파일(*.*)\0*.*\0텍스트 파일\0*.txt;*.doc\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = MAX_PATH;
	OFN.Flags = OFN_NOCHANGEDIR;//열거나 저장한 파일이 속한 디렉토리를 시작디렉토리로 하지 않게하는 것
	//OFN.lpstrInitialDir =TEXT( "c:\\");
	//다이얼로그를 불러오는 부분


	//다이얼로그를 열어주는 부분 -> 텍스트파일 저장 시 인코딩부분이 ANSI가 아니라 유니코드
	if(GetOpenFileName(&OFN)!=0) 
	{

		wsprintf(op_str, TEXT("%s 파일을 선택했습니다."),OFN.lpstrFile);
		fp = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  


		if (fp != INVALID_HANDLE_VALUE) // 파일의 존재 여부 확인 실패하면 INVALID_HANDLE_VALUE를 반화한다.
		{

			ReadFile(fp, buf, 1024, &readn, NULL); // buf에 일단 모두 저장
			j=0;
			k=0;
			//if(buf[0]==65279)//유니코드이면
			//{
				for(i=1;i<lstrlen(buf);i++)
				{
					if(buf[i]==13)
					{
						i++;
						k++;
						j=0;
						line++;
						s_line++;
						len = 0;
						s_len=0;
					}
					else{
						str[k][j] = buf[i];
						j++;
						len++;
						s_len++;
					}
				//}
			}

			hdc=GetDC(hwnd);
			GetTextExtentPoint(hdc,str[line],len,&size);
			SetCaretPos(5+size.cx,20*line);
			InvalidateRect(hwnd, NULL, TRUE);


			MessageBox(hwnd,op_str,TEXT("파일 열기 성공"),MB_OK);
			CloseHandle(fp); // 이제 필요없어진 핸들은 닫는다

		}
		else
		{
			MessageBox(hwnd, TEXT("텍스트 파일을 읽어오지 못했습니다."), 0, MB_OK);
		}

	}

}
void KHS_new_m(HWND hwnd)
{
	if(s_len!=0  || s_line!=0)//만약 내용이 비어있지 않으면
			{
				//저장할것인지 메세지 박스로 물어봄
				char retn = MessageBox(hwnd,TEXT("저장을 하시겠습니까?"),TEXT("질문"),MB_YESNOCANCEL);
				if(retn==IDYES)//예
				{
					KHS_save(hwnd, 0);
					KHS_new(hwnd);
				}//예 끝
				else if(retn==IDNO)//아니요
				{
					KHS_new(hwnd);
				}//아니오 끝
			}

}
void KHS_open_m(HWND hwnd)
{

	if(s_len!=0 || s_line!=0)//만약 내용이 비어있지 않으면
			{
				char retn = MessageBox(hwnd,TEXT("저장을 하시겠습니까?"),TEXT("질문"),MB_YESNOCANCEL);
				if(retn==IDYES)//예
				{
					KHS_save(hwnd, 1);
					KHS_open(hwnd);
				}//예 끝
				else if(retn==IDNO)//아니요
				{
					KHS_new( hwnd);//지우고 파일 열기
					KHS_open(hwnd);

				}//아니오 끝
			}
			else
			{
				KHS_open(hwnd);
			}

}