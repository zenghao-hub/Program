#pragma once
#include<windows.h>
#include <shldisp.h>
using namespace std;


//����ƶ���ָ��λ��
void MouseMove(int x, int y)
{
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//��ȡ��Ļ�ֱ��ʿ��
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//��ȡ��Ļ�ֱ��ʸ߶�
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));
}

//����������
void MouseLeftDown()
{
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
}

//�������ſ�
void MouseLeftUp()
{
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));

}

//����Ҽ�����
void MouseRightDown()
{
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
}

//����Ҽ��ſ�
void MouseRightUp()
{
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &Input, sizeof(INPUT));
}

/*
��ʾ����
*/
void ShowDesktop()
{
	CoInitialize(0);
	IShellDispatch4 *pdisp = NULL;
	CoCreateInstance(CLSID_Shell, NULL, CLSCTX_ALL, __uuidof(IShellDispatch4), (void **)&pdisp);
	if (pdisp)
	{
		pdisp->ToggleDesktop();
		pdisp->Release();
	}
}