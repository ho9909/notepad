#include "Function.h"


//KEYDOWN
//01)����Ű
void Left(HWND hwnd)
{
	if(len==0)//�Ǿ�
	{
		if(s_line!=0)// �ƿ� �Ǿ��� �ƴ� ��
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
	if(len==lstrlen(str[line]))//�ǵ�
			{
				if(line!=s_line)//�ƿ� �� �ڰ� �ƴ� ��
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
			if(line!=0)//�� ���� �ƴ� ��
			{
				bs_len = lstrlen(str[line-1]);//�� ��
				if(bs_len<len)//�� ���� �� ª�� ��
				{
					line--;
					len = bs_len;//�� ���� �� �ڷ�
					s_len =   lstrlen(str[line]);
				}
				else//�� ���� ���ų� �� �� �� 
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

		if(line!=s_line)//�� �Ʒ��� �ƴ� ��
			{
				bs_len = lstrlen(str[line+1]);//�Ʒ� ��
				if(bs_len<len)//�Ʒ� ���� �� ª�� ��
				{
					line++;
					len = bs_len;//�� ���� �� �ڷ�
					s_len =   lstrlen(str[line]);
				}
				else//�Ʒ� ���� ���ų� �� �� �� 
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
//02)��ư ����
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
			if(len ==s_len)//�ǵ�
			{
				if(line!=s_line)//�� ������ �� �ǵڰ� �ƴ� ��
				{

					bs_len = lstrlen(str[line+1]);//������ �ܾ��
					for(i=s_len; i<s_len+bs_len; i++ )//�� �� �ڸ��� ���� ���� ������ ������ŭ �����ؼ� �ٿ��ְ�
					{
						str[line][i] = str[line+1][k];
						Arr_len[line][i] = Arr_len[line+1][k];
						k++;

					}
					for(i=0;i<bs_len;i++)//�����ִ� �ڸ��� �����ְ�
					{
						str[line+1][i]=NULL;
						Arr_len[line+1][i]=NULL;
					}

					for(i=1; i<s_line-line; i++)//��ĭ�� �̷��ִ� ����
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
				//�ڿ��ִ°� ��ĭ �� ��������
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

tab_num = len%8;//8�� ���� ������ ��
			if(len==s_len)//�� ���ϋ�
			{
				if(tab_num ==0 )//8�� ������ �������� ���� 8��ŭ �̵�
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
			else//�ڿ� �۾��� ������
			{
				if(tab_num ==0 )//8�� ������ �������� ���� 8��ŭ �̵�
				{
					for(i=0;i<s_len-len;i++)//s_len-len����ŭ
					{
						str[line][s_len+7-i] = str[line][s_len-1-i];//�ǵڿ������� 8ĭ�� �� �ű��	
					}
					for(i=0;i<8;i++)//s_len-len����ŭ
					{
						str[line][len+i] = ' ';//�� ���� �ڸ� �����̽��ٷ� ä���ش�.
					}
					s_len = s_len+8;
					len=len+8;

				}
				else
				{
					for(i=0;i<s_len-len;i++)//s_len-len����ŭ
					{
						str[line][s_len+7-tab_num-i] = str[line][s_len-1-i];//�ǵڿ������� 8ĭ�� �� �ű��	
					}
					for(i=0;i<8-tab_num;i++)//s_len-len����ŭ
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

			if(len == lstrlen(str[line]))//�� �ڿ��� ����
			{

				if(line==s_line)//�� �� �ε� �� �� ���϶�
				{
					line++;
					s_line++;
					len = 0;
					s_len = 0;
					InvalidateRect(hwnd, NULL, TRUE);
				}
				else//�� �� �ε� �߰� ���϶�
				{
					int k ;
					for(i=0; i<s_line-line; i++)//��ĭ�� �̷��ִ� ����
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
			else//���� �߰����� ���͸� ���� ��
			{
				if(line==s_line)//�߰��ε� �� �� ���϶�
				{
					for(i=0; i<s_len-len; i++)//�� ĭ ������ �Ű��ְ�
					{
						str[line+1][i] = str[line][i+len];
						Arr_len[line+1][i] = Arr_len[line][i+len];
					}
					for(i=len; i<s_len; i++)//���� �ִ� �ڸ� �����ְ�
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
				else//�߰��ε� �߰� ���϶�
				{
					int k ;
					for(i=0; i<s_line-line; i++)//��ĭ�� �̷��ִ� ����
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
					for(i=0; i<s_len-len;i++)//���� ���� ĳ�� �ڿ������� �����ٷ� �Ű��ش�.
					{
						str[line+1][i] = str[line][len+i];
						Arr_len[line+1][i] = Arr_len[line][len+i];
					}
					for(i=len;i<s_len;i++)//�����ִ� ������ �����
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


			if(len==0)//���� �� ��
			{				
				int k=0;

				if(line!=0)//�� ù���� �� ���� �ƴҶ�
				{
					bs_len = lstrlen(str[line-1]);//������ �ܾ��
					for(i=bs_len; i<bs_len+ s_len; i++ )//�� �� �ڸ��� ���� ���� ������ ������ŭ �����ؼ� �ٿ��ְ�
					{
						str[line-1][i] = str[line][len+k];
						Arr_len[line-1][i] = Arr_len[line][len+k];
						k++;

					}
					for(i=0;i<s_len;i++)//�����ִ� �ڸ��� �����ְ�
					{
						str[line][i]=NULL;
						Arr_len[line][i]=NULL;
					}
					//�ڿ� �ִ°� ��ĭ�� ����ش�



					for(i=0; i<s_line-line; i++)//��ĭ�� �̷��ִ� ����
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
			else//�߰��̳� ��
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
					//������ġ�� NULL�̸� �� �� ġ�� ��� NULL�� �ƴϸ� ��ĭ �� �̷�� ��� 
					if(str[line][len]==NULL)
					{
						str[line][len] = (TCHAR)wParam;
						len++;
						s_len++;
						InvalidateRect(hwnd, NULL, FALSE);
				
					}
					else
					{
						//i�� ����line�� len�� ��ŭ���� ���� len������ �ڷ� �о��ش�.
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
				else//�μ�Ʈ�� ���� ���
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


	//�����
	WORD wc = 0xFEFF; //����� ���� Ī��....�����ڵ带 ���Ұ�?
	DWORD dwBytes = 0;


	OPENFILENAME OFN2;

	memset(&OFN2,0,sizeof(OPENFILENAME));
	OFN2.lStructSize = sizeof(OPENFILENAME);
	OFN2.hwndOwner = hwnd;
	OFN2.lpstrFilter = TEXT("��� ����(*.*)\0*.*\0�ؽ�Ʈ ����\0*.txt;*.doc\0");
	OFN2.lpstrFile = lpstrFile; //lpstrFile
	OFN2.Flags = OFN_NOCHANGEDIR;
	OFN2.nMaxFile = MAX_PATH;



	if(GetSaveFileName(&OFN2) != 0) //���̾�α� ����
	{


		fp = CreateFile(OFN2.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		// �����ڵ����� �˸��� BOM
		WriteFile(fp, &wc, 2, &dwBytes, NULL);

		// �����ڵ� �ؽ�Ʈ ���̸�ŭ ����Ѵ�
		for(i=0;i<=s_line;i++)
		{
			WriteFile(fp, str[i], lstrlen(str[i]) * sizeof(TCHAR), &readn, NULL);
			WriteFile(fp, "\r", 2, &readn, NULL);//�� ������
			WriteFile(fp, "\n", 2, &readn, NULL);//����
		}
		CloseHandle(fp); // ���� �ʿ������ �ڵ��� �ݴ´�
		MessageBox(hwnd, TEXT("�ؽ�Ʈ ���Ϸ� �����Ͽ����ϴ�."), TEXT("WriteFile"), MB_OK);

		if(flag==1)
		{
			KHS_new(hwnd);
		}


	}
	else
	{
		MessageBox(hwnd, TEXT("�ؽ�Ʈ ������ �������� ���߽��ϴ�."), 0, MB_OK);

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
	OFN.lpstrFilter = TEXT("��� ����(*.*)\0*.*\0�ؽ�Ʈ ����\0*.txt;*.doc\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = MAX_PATH;
	OFN.Flags = OFN_NOCHANGEDIR;//���ų� ������ ������ ���� ���丮�� ���۵��丮�� ���� �ʰ��ϴ� ��
	//OFN.lpstrInitialDir =TEXT( "c:\\");
	//���̾�α׸� �ҷ����� �κ�


	//���̾�α׸� �����ִ� �κ� -> �ؽ�Ʈ���� ���� �� ���ڵ��κ��� ANSI�� �ƴ϶� �����ڵ�
	if(GetOpenFileName(&OFN)!=0) 
	{

		wsprintf(op_str, TEXT("%s ������ �����߽��ϴ�."),OFN.lpstrFile);
		fp = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  


		if (fp != INVALID_HANDLE_VALUE) // ������ ���� ���� Ȯ�� �����ϸ� INVALID_HANDLE_VALUE�� ��ȭ�Ѵ�.
		{

			ReadFile(fp, buf, 1024, &readn, NULL); // buf�� �ϴ� ��� ����
			j=0;
			k=0;
			//if(buf[0]==65279)//�����ڵ��̸�
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


			MessageBox(hwnd,op_str,TEXT("���� ���� ����"),MB_OK);
			CloseHandle(fp); // ���� �ʿ������ �ڵ��� �ݴ´�

		}
		else
		{
			MessageBox(hwnd, TEXT("�ؽ�Ʈ ������ �о���� ���߽��ϴ�."), 0, MB_OK);
		}

	}

}
void KHS_new_m(HWND hwnd)
{
	if(s_len!=0  || s_line!=0)//���� ������ ������� ������
			{
				//�����Ұ����� �޼��� �ڽ��� ���
				char retn = MessageBox(hwnd,TEXT("������ �Ͻðڽ��ϱ�?"),TEXT("����"),MB_YESNOCANCEL);
				if(retn==IDYES)//��
				{
					KHS_save(hwnd, 0);
					KHS_new(hwnd);
				}//�� ��
				else if(retn==IDNO)//�ƴϿ�
				{
					KHS_new(hwnd);
				}//�ƴϿ� ��
			}

}
void KHS_open_m(HWND hwnd)
{

	if(s_len!=0 || s_line!=0)//���� ������ ������� ������
			{
				char retn = MessageBox(hwnd,TEXT("������ �Ͻðڽ��ϱ�?"),TEXT("����"),MB_YESNOCANCEL);
				if(retn==IDYES)//��
				{
					KHS_save(hwnd, 1);
					KHS_open(hwnd);
				}//�� ��
				else if(retn==IDNO)//�ƴϿ�
				{
					KHS_new( hwnd);//����� ���� ����
					KHS_open(hwnd);

				}//�ƴϿ� ��
			}
			else
			{
				KHS_open(hwnd);
			}

}