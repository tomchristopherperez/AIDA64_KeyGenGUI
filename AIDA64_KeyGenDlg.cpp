﻿
// AIDA64_KeyGenDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AIDA64_KeyGen.h"
#include "AIDA64_KeyGenDlg.h"
#include "afxdialogex.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cctype>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAIDA64KeyGenDlg 对话框



CAIDA64KeyGenDlg::CAIDA64KeyGenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AIDA64_KEYGEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAIDA64KeyGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAIDA64KeyGenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAIDA64KeyGenDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAIDA64KeyGenDlg 消息处理程序

BOOL CAIDA64KeyGenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAIDA64KeyGenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAIDA64KeyGenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAIDA64KeyGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

WORD data[] = {
	0x001F, 0x001C, 0x001F, 0x001E, 0x001F, 0x001E, 0x001F, 0x001F,
	0x001E, 0x001F, 0x001E, 0x001F, 0x001F, 0x001D, 0x001F, 0x001E,
	0x001F, 0x001E, 0x001F, 0x001F, 0x001E, 0x001F, 0x001E, 0x001F
};

char arry[] = {
	0x44, 0x59, 0x31, 0x34, 0x55, 0x46, 0x33, 0x52,
	0x48, 0x57, 0x43, 0x58, 0x4C, 0x51, 0x42, 0x36,
	0x49, 0x4B, 0x4A, 0x54, 0x39, 0x4E, 0x35, 0x41,
	0x47, 0x53, 0x32, 0x50, 0x4D, 0x38, 0x56, 0x5A,
	0x37, 0x45
};

//前24位取校验值
int calc1(char* str) {
	//只取前24个
	DWORD len = 24;
	int v1 = 0;
	if (len > 0) {
		int i = 0;
		do {
			v1 ^= str[i] << 8;
			int v4 = 8;
			do {
				if ((v1 & 0x8000) == 0)
					v1 *= 2;
				else
					v1 = 2 * v1 ^ 0x8201;
				--v4;
			} while (v4);
			v1 = v1 & 0xffff;
			++i;
			--len;
		} while (len);
	}
	return v1;
}

//通过校验值取特征码
char* calc2(int b, char* buff) {
	WORD v4 = b % 0x484 / 0x22;
	WORD v5 = b % 0x484 % 0x22;
	WORD index = b / 0x484;
	char* rRet = 0;
	if (b <= 0x9987) {
		if (index <= 0x21 && v4 <= 0x21u && v5 <= 0x21u) {
			buff[0] = arry[index];
			buff[1] = arry[v4];
			buff[2] = arry[v5];
			rRet = buff;
		}
		else return NULL;
	}
	else return NULL;
	return rRet;
}

//黑名单检测
bool check_blacklist(char* key) {
	HANDLE hFile = CreateFileA("black_list.txt", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("打开黑名单错误!\n");
		return true;
	}
	char buff[26] = { 0 };
	DWORD dwsize = 0;
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	int i = 0;
	while (1) {
		i++;
		ReadFile(hFile, buff, 25, &dwsize, 0);
		if (dwsize != 0) {
			if (!strcmp(buff, key)) {
				printf("在黑名单第%d行！\n", i);
				CloseHandle(hFile);
				return false;
			}
		}
		else {
			CloseHandle(hFile);
			return true;
		}
		SetFilePointer(hFile, 2, 0, FILE_CURRENT);

	}
}

//某几位Key取校验值
int check_num(char* num) {
	int len = strlen(num);
	int re = 0;
	for (int i = 0; i < len; i++) {
		for (int k = 0; k < 0x22; k++) {
			if (num[i] == arry[k]) { //判断Key在特征字符串的位置
				//计算幂  pow(base,指数)
				double n = pow(34.0, (double)(len - i - 1));
				int ret = 0;
				ret = trunc(n);//取整
				ret *= k;
				re += ret;
				break;
			}
		}
	}
	return re;
}

bool __fastcall IsLeapYear(unsigned __int16 a1) {
	return !(a1 & 3) && (a1 % 0x64u || !(a1 % 0x190u));
}

int EncodeDate(int a1, int a2, int a3) {
	unsigned __int16 v4; // bx
	unsigned __int16 v5; // di
	WORD* v6; // esi
	int v7; // eax
	signed int v8; // ecx
	char v10; // [esp+11h] [ebp-3h]
	unsigned __int16 v11; // [esp+12h] [ebp-2h]
	double a4 = 0;

	v4 = a3;
	v5 = a2;
	v11 = a1;
	v10 = 0;
	v6 = (WORD*)(24 * (IsLeapYear(a1) & 0x7F) + (char*)data);
	if (v11 >= 1 && v11 <= 0x270F &&
		v5 >= 1 && v5 <= 0xC &&
		v4 >= 1 && v4 <= *(v6 + 2 * v5 - 2)) {
		v7 = v5 - 1;
		if (v7 > 0) {
			v8 = 1;
			do {
				v4 += *(v6 + 2 * v8++ - 2);
				--v7;
			} while (v7);
		}
		a4 = (long double)(v4 + (v11 - 1) / 400 + (v11 - 1) / 4 + 365 * (v11 - 1) - (v11 - 1) / 100 - 0xA955A);
		v10 = 1;
	}
	return a4;
}

//注册流程
bool Reg(char* key) {
	int a = calc1(key);
	bool res = false;
	char check1[4] = { 0 };
	calc2((a % 0x9987) & 0xffff, check1);
	if (check1[1] == key[24]) { //条件1
		//黑名单检测
		if (check_blacklist(key)) { //条件2

			char buff1[3] = { 0 };
			buff1[0] = key[22];
			buff1[1] = key[23];
			int v23 = check_num(buff1);

			char buff2[3] = { 0 };
			buff2[0] = key[0];
			buff2[1] = key[1];
			int v24 = check_num(buff2);
			WORD v56 = (0xff & v23) ^ v24 ^ 0xBF;    //n1  必须等于2

			char buff3[3] = { 0 };
			buff3[0] = key[2];
			buff3[1] = key[3];
			int v88 = check_num(buff3);
			WORD a4 = (0xff & v23) ^ v88 ^ 0xED;  //0x64<= a4 <= 0x3DE


			char buff4[3] = { 0 };
			buff4[0] = key[4];
			buff4[1] = key[5];
			int v89 = check_num(buff4);
			WORD v53 = (0xff & v23) ^ v89 ^ 0x77;     //n2    v53<=0x64

			char buff5[3] = { 0 };
			buff5[0] = key[6];
			buff5[1] = key[7];
			int v90 = check_num(buff5);
			WORD v54 = (0xff & v23) ^ v90 ^ 0xDF;     //n3    v54<=0x64

			char buff6[5] = { 0 };
			buff6[0] = key[8];
			buff6[1] = key[9];
			buff6[2] = key[10];
			buff6[3] = key[11];
			int v91 = check_num(buff6);
			int a5 = v23 ^ v91 ^ 0x4755;   // 1<= a5 < 0x31E

			char buff7[5] = { 0 };
			buff7[0] = key[12];
			buff7[1] = key[13];
			buff7[2] = key[14];
			buff7[3] = key[15];
			int v92 = check_num(buff7);
			WORD v25 = v23 ^ v92 ^ 0x7CC1;              //n4    v25>>9 >0    v25>>5 <0xC

			char buff8[5] = { 0 };
			buff8[0] = key[16];
			buff8[1] = key[17];
			buff8[2] = key[18];
			int v93 = check_num(buff8);
			WORD  a7 = (v23 & 0xff) ^ v93 ^ 0x3FD;  //a7<0xec4

			char buff9[5] = { 0 };
			buff9[0] = key[19];
			buff9[1] = key[20];
			buff9[2] = key[21];
			int v94 = check_num(buff9);
			WORD a8 = (0xff & v23) ^ v94 ^ 0x935;         //1<=a8 <= 0xE4C

			if (a4 != 0x3E7 &&               //条件3
				v53 <= 0x64u &&            //条件4
				v54 <= 0x64u &&             //条件5
				a5 != 0xFFFF &&              //条件6
				a7 <= 0xE4C &&             //条件7
				a8 <= 0xE4C &&            //条件8
				(a7 != 0xE4C || a8 != 0x726)) { //条件9
				double a6 = 0;
				int v26 = v25 >> 9;
				v26 = ((v25 >> 9) & 0x1F) + 0x7D3; //最大就7F2
				int v27 = (v25 >> 5) & 0xF; //最大F
				int v28 = v25 & 0x1F;          //最大1F
				if (0xffff & v26 >= 0x7D4              //条件10
					&& v26 <= 0x833  //条件11
					&& v27 >= 1  //条件12
					&& v27 <= 0xC
					&& v28 >= 1    //条件13
					&& v28 <= 0x1F) {
					a6 = EncodeDate(v26, v27, v28);
				}
				//条件14
				bool v29 = v56 == 2 && a4 >= 0x64 && a4 < 0x3DE && a5 && a5 < 0x31E && a6 != 0.0 && a8;
				if (v29) res = true;
			}
		}
	}
	return res;
}

char newkey[26];

CString UnReg() {
	CString regcode = L"";
	srand(time(0));
	int time = 0, v0, v1, v2, v3, v4, v5, v6, v7, v8;
start:
	while (1) {
		time++;
		char buff[3] = { 0 };
		buff[0] = newkey[22] = arry[rand() % 0x21];
		buff[1] = newkey[23] = arry[rand() % 0x21];
		v0 = check_num(buff);
		char buff1[3] = { 0 };
		buff1[0] = newkey[0] = arry[rand() % 0x21];
		buff1[1] = newkey[1] = arry[rand() % 0x21];
		v1 = check_num(buff1);
		if (((v0 & 0xff) ^ v1 ^ 0xBF) == 2) break;
	}
	time = 0;
	while (1) {
		time++;
		char buff2[3] = { 0 };
		buff2[0] = newkey[2] = arry[rand() % 0x21];
		buff2[1] = newkey[3] = arry[rand() % 0x21];
		v2 = check_num(buff2);
		if ((v2 ^ (v0 & 0xff) ^ 0xED) >= 0x64 && (v2 ^ (v0 & 0xff) ^ 0xED) <= 0x3DE) break;
	}
	time = 0;
	while (1) {
		time++;
		char buff3[3] = { 0 };
		buff3[0] = newkey[4] = arry[rand() % 0x21];
		buff3[1] = newkey[5] = arry[rand() % 0x21];
		v3 = check_num(buff3);
		if (((v0 & 0xff) ^ v3 ^ 0x77) <= 0x64) break;
	}
	time = 0;
	while (1) {
		time++;
		char buff4[3] = { 0 };
		buff4[0] = newkey[6] = arry[rand() % 0x21];
		buff4[1] = newkey[7] = arry[rand() % 0x21];
		v4 = check_num(buff4);
		if (((v0 & 0xff) ^ v4 ^ 0xDF) <= 0x64) break;
	}
	time = 0;
	while (1) {
		time++;
		char buff5[5] = { 0 };
		buff5[0] = newkey[8] = arry[rand() % 0x21];
		buff5[1] = newkey[9] = arry[rand() % 0x21];
		buff5[2] = newkey[10] = arry[rand() % 0x21];
		buff5[3] = newkey[11] = arry[rand() % 0x21];
		v5 = check_num(buff5);
		if (((v0 & 0xffff) ^ v5 ^ 0x4755) >= 1 && ((v0 & 0xffff) ^ v5 ^ 0x4755) <= 0x31E) break;
	}
	time = 0;
	while (1) {
		time++;
		char buff6[5] = { 0 };
		buff6[0] = newkey[12] = arry[rand() % 0x21];
		buff6[1] = newkey[13] = arry[rand() % 0x21];
		buff6[2] = newkey[14] = arry[rand() % 0x21];
		buff6[3] = newkey[15] = arry[rand() % 0x21];
		v6 = check_num(buff6);
		if (((((v0 & 0xffff) ^ v6 ^ 0x7CC1) >> 9) <= 0xF) && ((((v0 & 0xffff) ^ v6 ^ 0x7CC1) >> 9) > 8) && ((((v0 & 0xffff) ^ v6 ^ 0x7CC1) >> 5) & 0xf) < 0xc) break;
	}
	time = 0;
	while (1) {
		time++;
		char buff7[4] = { 0 };
		buff7[0] = newkey[16] = arry[rand() % 0x21];
		buff7[1] = newkey[17] = arry[rand() % 0x21];
		buff7[2] = newkey[18] = arry[rand() % 0x21];
		v7 = check_num(buff7);
		if (((v0 & 0xff) ^ v7 ^ 0x3FD) == 0) break;
		//随机不出来就重新开始
		if (time > 100000) {
			time = 0;
			goto start;
		}
	}
	time = 0;
	while (1) {
		time++;
		char buff8[4] = { 0 };
		buff8[0] = newkey[19] = arry[rand() % 0x21];
		buff8[1] = newkey[20] = arry[rand() % 0x21];
		buff8[2] = newkey[21] = arry[rand() % 0x21];
		v8 = check_num(buff8);
		if (((v0 & 0xff) ^ v8 ^ 0x935) < 0xE4C && (v0 ^ v8 ^ 0x935) >= 1) break;
	}

	int a = calc1(newkey);
	char check2[4] = { 0 };
	calc2((a % 0x9987) & 0xffff, check2);
	newkey[24] = check2[1];//赋值最后一位
	//黑名单检测
	if (!check_blacklist(newkey)) {
		time = 0;
		goto start;
	}
	//日期检测
	int year = ((((v0 & 0xffff) ^ v6 ^ 0x7CC1) >> 9) & 0x1F) + 0x7D3;
	int month = (((v0 & 0xffff) ^ v6 ^ 0x7CC1) >> 5) & 0xF;
	int day = ((v0 & 0xffff) ^ v6 ^ 0x7CC1) & 0x1F;
	double data = EncodeDate(year, month, day);

	if (data + ((v0 & 0xff) ^ v8 ^ 0x935) < 43409) { // 43423-14     <  data+a8
		//printf("时间校验未通过，重新开始！\n");
		time = 0;
		goto start;
	}
	regcode.Format(L"%C%C%C%C%C-%C%C%C%C%C-%C%C%C%C%C-%C%C%C%C%C-%C%C%C%C%C\n",
		newkey[0], newkey[1], newkey[2], newkey[3], newkey[4],
		newkey[5], newkey[6], newkey[7], newkey[8], newkey[9],
		newkey[10], newkey[11], newkey[12], newkey[13], newkey[14],
		newkey[15], newkey[16], newkey[17], newkey[18], newkey[19],
		newkey[20], newkey[21], newkey[22], newkey[23], newkey[24]
	);
	//复验
	if (Reg(newkey)) return regcode;
	else return L"";
}

void CAIDA64KeyGenDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString result = UnReg();
	if (result.Trim().IsEmpty()) {
		AfxMessageBox(L"Failed to calculate the code,please try again!");
	}
	else {
		GetDlgItem(IDC_FUCKER)->SetWindowText(result);
		if (OpenClipboard())
		{
			HGLOBAL clipbuffer;
			char* buffer;
			EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, result.GetLength() + 1);
			buffer = (char*)GlobalLock(clipbuffer);
			int num = WideCharToMultiByte(CP_OEMCP, NULL, result, -1, NULL, 0, NULL, FALSE);
			char* pchar = new char[num];
			WideCharToMultiByte(CP_OEMCP, NULL, result, -1, pchar, num, NULL, FALSE);
			strcpy(buffer, pchar);
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_TEXT, clipbuffer);
			CloseClipboard();
		}
		AfxMessageBox(L"Register Code has been successfully generated and it's been copied to the clipboard!");
	}
}
