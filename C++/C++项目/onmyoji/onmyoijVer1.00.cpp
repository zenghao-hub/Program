#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
#include<memory>
#include<iterator>
#include<stack>
#include<map>
#include<set>
#include <cassert>
#include <fstream>

#include <opencv2/opencv.hpp>
#include"MouseOperation.h"

using namespace cv;
#define SQDIFF 0
#define SADIFF 1


// ��ȡ���ʱ��
int rand_number()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	return sys.wMilliseconds;
}


/*
�������λ�ã�debug������Ļ��С
����ʦӦ�ó���ͼƬ�����120��1050�����ݵ�������������С������
*/
void testMousePos()
{
	for (int i = 0; i < 200; i++)
	{
		POINT pt = { 0,0 };
		GetCursorPos(&pt);
		Sleep(1000);// ��ʱһ��
		cout << pt.x << ' ' << pt.y << endl;// �����������
	}
}


/*
ģ��ƥ��
i_match j_match��ƥ�������
begin_i begin_j�Ǳ�����������㣬������С��ͼ���������·�����˿��Լ�Сx������Χ��begin_i = 1000��begin_j = 0��

*/
float templateMatch(const Mat & src, const Mat & temp, int & i_match, int & j_match, int Match_methold,int begin_i,int begin_j, int end_i, int end_j)
{
	int src_cols = src.cols;
	int src_rows = src.rows;
	int temp_cols = temp.cols;
	int temp_rows = temp.rows;
	// i�����j����
	int i_end = src_rows - temp.rows + 1;
	int j_end = src.cols - temp.cols + 1;
	//cout << i_end << ' ' << j_end << endl;
	float match_degree = FLT_MAX;

	for (int i = begin_i; i < i_end&&i<end_i; i = i + 1)
	{
		for (int j = begin_j; j < j_end&&j<end_j; j = j + 1)
		{
			float match_ij = 0.0;

			for (int m = 0; m < temp_rows; m++)
			{
				for (int n = 0; n < temp_cols; n++)
				{
					uchar val_s = src.at<uchar>(i + m, j + n);
					uchar val_t = temp.at<uchar>(m, n);
					if (Match_methold == SQDIFF)
					{
						match_ij += float((val_t - val_s) * (val_t - val_s));
					}
					else if (Match_methold == SADIFF)
					{
						match_ij += float(abs(val_t - val_s));
					}
				}
			}

			//cout << "�鿴ƥ��ֵ"<<match_ij << endl;
			if (match_ij < match_degree)
			{
				match_degree = match_ij;
				i_match = i;
				j_match = j;
			}
		}
	}


	return match_degree;

}

/*
���� ����ͼƬ��������ǰĿ¼
str��ʾ�����Ŀ¼
*/
int Screen(string str)
{
	//��ȡ��ǰ������ĻDC
	HDC hDC = GetDC(GetDesktopWindow());
	//CDC *pDC = CDC::FromHandle(hDC);

	//�����ɫģʽ
	int BitPerPixel = GetDeviceCaps(hDC, BITSPIXEL);
	int Width = GetDeviceCaps(hDC, HORZRES);
	int Height = GetDeviceCaps(hDC, VERTRES);

	//cout << "��ǰ��Ļɫ��ģʽΪ" << BitPerPixel << "λɫ��" << endl
	//	<< "��Ļ��ȣ�" << Width << endl
	//	<< "��Ļ�߶ȣ�" << Height << endl << endl;

	HDC memDC;//�ڴ�DC
	memDC = CreateCompatibleDC(hDC);

	HBITMAP memBitmap;
	HGDIOBJ oldmemBitmap;//��������Ļ���ݵ�bitmap
	memBitmap = CreateCompatibleBitmap(hDC, Width, Height);

	oldmemBitmap = SelectObject(memDC, memBitmap);//��memBitmapѡ���ڴ�DC
	BitBlt(memDC, 0, 0, Width, Height, hDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC

														   //���´��뱣��memDC�е�λͼ���ļ�
														   //BITMAP bmp;
														   //GetBitmap(&bmp);//���λͼ��Ϣ

	BITMAP bm;
	GetObject(memBitmap, sizeof(BITMAP), (LPBYTE)&bm);

	FILE *fp = fopen(str.c_str(), "w+b");

	BITMAPINFOHEADER bih = { 0 };//λͼ��Ϣͷ
	bih.biBitCount = bm.bmBitsPixel;//ÿ�������ֽڴ�С
	bih.biCompression = BI_RGB;
	bih.biHeight = bm.bmHeight;//�߶�
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bm.bmWidthBytes * bm.bmHeight;//ͼ�����ݴ�С
	bih.biWidth = bm.bmWidth;//���

	BITMAPFILEHEADER bfh = { 0 };//λͼ�ļ�ͷ
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
	bfh.bfSize = bfh.bfOffBits + bm.bmWidthBytes * bm.bmHeight;//�ļ��ܵĴ�С
	bfh.bfType = (WORD)0x4d42;

	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ

	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ

	byte * p = new byte[bm.bmWidthBytes * bm.bmHeight];//�����ڴ汣��λͼ����

	GetDIBits(memDC, (HBITMAP)memBitmap, 0, Height, p,
		(LPBITMAPINFO)&bih, DIB_RGB_COLORS);//��ȡλͼ����

	fwrite(p, 1, bm.bmWidthBytes * bm.bmHeight, fp);//д��λͼ����

	delete[] p;
	fclose(fp);
	SelectObject(memDC, oldmemBitmap);

	// cout << "��Ļͼ���Ѵ洢���ļ���" << endl;
	return 0;
}

// ��ȡʤ��ͼ
int Screen2(string str)
{
	//��ȡ��ǰ������ĻDC
	HDC hDC = GetDC(GetDesktopWindow());
	//CDC *pDC = CDC::FromHandle(hDC);

	//�����ɫģʽ
	int BitPerPixel = GetDeviceCaps(hDC, BITSPIXEL);
	int Width = GetDeviceCaps(hDC, HORZRES);
	int Height = GetDeviceCaps(hDC, VERTRES);

	//cout << "��ǰ��Ļɫ��ģʽΪ" << BitPerPixel << "λɫ��" << endl
	//	<< "��Ļ��ȣ�" << Width << endl
	//	<< "��Ļ�߶ȣ�" << Height << endl << endl;

	HDC memDC;//�ڴ�DC
	memDC = CreateCompatibleDC(hDC);

	HBITMAP memBitmap;
	HGDIOBJ oldmemBitmap;//��������Ļ���ݵ�bitmap
	memBitmap = CreateCompatibleBitmap(hDC, 450, 400); // 450 400 

	oldmemBitmap = SelectObject(memDC, memBitmap);//��memBitmapѡ���ڴ�DC
	BitBlt(memDC, 0, 0, 450, 400, hDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC 
	// BitBlt(memDC, 760, 420, 450, 400, hDC, 0, 420, SRCCOPY);
														   //���´��뱣��memDC�е�λͼ���ļ�
														   //BITMAP bmp;
														   //GetBitmap(&bmp);//���λͼ��Ϣ

	BITMAP bm;
	GetObject(memBitmap, sizeof(BITMAP), (LPBYTE)&bm);

	FILE *fp = fopen(str.c_str(), "w+b");

	BITMAPINFOHEADER bih = { 0 };//λͼ��Ϣͷ
	bih.biBitCount = bm.bmBitsPixel;//ÿ�������ֽڴ�С
	bih.biCompression = BI_RGB;
	bih.biHeight = bm.bmHeight;//�߶�
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bm.bmWidthBytes * bm.bmHeight;//ͼ�����ݴ�С
	bih.biWidth = bm.bmWidth;//���

	BITMAPFILEHEADER bfh = { 0 };//λͼ�ļ�ͷ
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
	bfh.bfSize = bfh.bfOffBits + bm.bmWidthBytes * bm.bmHeight;//�ļ��ܵĴ�С
	bfh.bfType = (WORD)0x4d42;

	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ

	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ

	byte * p = new byte[bm.bmWidthBytes * bm.bmHeight];//�����ڴ汣��λͼ����

	GetDIBits(memDC, (HBITMAP)memBitmap, 0, Height, p,
		(LPBITMAPINFO)&bih, DIB_RGB_COLORS);//��ȡλͼ����

	fwrite(p, 1, bm.bmWidthBytes * bm.bmHeight, fp);//д��λͼ����

	delete[] p;
	fclose(fp);
	SelectObject(memDC, oldmemBitmap);

	// cout << "��Ļͼ���Ѵ洢���ļ���" << endl;
	return 0;
}


// ����Сͼ�꣬����onmyoji
void step1()
{
	// ������ʦ���򣨷�����С����ǰ�棩
	ShowDesktop();
	MouseMove(120, 1050);
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
}

// ������ս�������ʮ��ս
void step2()
{
	int x = 1230, y = 650;
	x = x + rand_number() % 20;
	y = y + rand_number() % 20;
	MouseMove(x, y);// �ƶ�����ս��λ��
	Sleep(3000 + rand_number());// �ȴ����ʱ��
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
}

// ������ʼ����ʮս����ʼ
void step3()
{
	int x = 1430, y = 700;
	x = x + rand_number() % 30;
	y = y + rand_number() % 30;
	MouseMove(x, y);// �ƶ�����ս��λ��
	Sleep(2000 + rand_number());// �ȴ����ʱ��

	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
}


/*
�ò��Գ����Ѿ�����һ���ϵĲ��ԡ���������
version20191011.1
*/
int test1011()
{
	/*
	MouseRightDown();
	MouseRightUp();*/

	//testMousePos();

	step1();
	while (1)
	{
		step2();
		Sleep(3000 + rand_number());
		step3();
		Sleep(rand_number());// �ȴ����ʱ��
		MouseMove(1000, 500);
		// ս�������У���Ҫ2min���ң��������ݵ���ǿ�����Լ���ʱ��
		Sleep(60000 + rand_number()); // ��Ҫ�ȴ�120s�����


		MouseLeftDown();//����������
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftUp();

		Sleep(rand_number());
		MouseLeftDown();//����������
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftUp();

		Sleep(rand_number());
		MouseLeftDown();//����������
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftUp();

		Sleep(3000 + rand_number());
	}
	//testMousePos();
	return 0;

	// ��Ϸ���
}

/*
ͼ��ƥ���ȡλ�ã�ƥ��ֵ��������ʼ
int i_match, j_match;// ģ��ƥ���������
float match_degree;//ģ��ƥ��ֵ�����ֵ3.7xpow(10,6)
1000, 0 �ǵ�����int begin_i,int begin_j
*/
void GetPosition(string desktopScreen, string minOnmyoji, int &i_match, int &j_match, float &match_degree,int begin_i,int begin_j, int end_i, int end_j)
{
	Mat src = imread(desktopScreen, CV_LOAD_IMAGE_GRAYSCALE);
	Mat temp = imread(minOnmyoji, CV_LOAD_IMAGE_GRAYSCALE);
	match_degree = templateMatch(src, temp, i_match, j_match, SQDIFF, begin_i, begin_j, end_i, end_j);
	//cout << i_match << endl << j_match << endl << match_degree << endl;
}
/*
����ʦ����������
Ҫ�󣺴�����ʦ����½����ʦ���򿪵���ʮ��ս���棬Ȼ����С���������Ǳ���ģ�
1. �������Ҫ��Ĳ���
2. �������沢��ȡ����ͼƬ������Ϊ./JpgData/����.jpg
3. ģ��ƥ��������»�ͼ���λ��
4. ���ݼ��������� ������ʦ
5. ������ʦ���ͼ��ͼ��ƥ�䣬���������ʦ���ڵ�λ�ã�����ʦ���ڴ�С�ǹ̶��ġ�
��Ҫ�궨��λ��(311,556)����������ڴ����·�560���ұ�310λ�ô�������ս���ڡ�������ߡ����·� -90���ұ�530
6. �ƶ�����սλ�ã�������ս
7. �ȴ�3s�󣬵������ʼ��������ʼ���ڡ�������ߡ����ұ�728���·�-35
8. �ƶ�������λ�ã��ұ�515���·�-360
9. һֱ�������λ�ã�ֱ��ս����������ˣ�ս��������������Ŀǰ������ʱ������,�ƶ���������ߣ�ս������
10. ѭ��6-9��

1480 800
*/

// ��ʮ����
void battleForHun10()
{
	// 2
	ShowDesktop();
	Sleep(1000);
	string desktopScreen = "./JpgData/����.jpg";
	string minOnmyoji = "./JpgData/��С��ͼ��.jpg";// ��Ҫ���н�ͼ����
	Screen(desktopScreen);

	// 3 ������int begin_i=1000,int begin_j=0
	int i_match, j_match;// ģ��ƥ���������
	float match_degree = 0.0;//ģ��ƥ��ֵ�����ֵ3.7xpow(10,6)
	GetPosition(desktopScreen, minOnmyoji, i_match, j_match, match_degree, 1000, 0, 3000, 3000);

	// 4
	MouseMove(j_match + 72, i_match + 15);
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
	Sleep(1000 + rand_number());// �ȴ����ʱ��

	// 5 �������λ��747 701
	string fullScreen = "./JpgData/����ʦ���ڽ���.jpg";
	string hun10 = "./JpgData/��ʮ��ս����.jpg";
	Screen(fullScreen);
	int i_match2, j_match2;// ģ��ƥ���������
	float match_degree2 = 0.0;//ģ��ƥ��ֵ�����ֵ3.7xpow(10,6)
	GetPosition(fullScreen, hun10, i_match2, j_match2, match_degree2, 559, 20, 905, 1000);
	while (1)
	{
		// 6 
		MouseMove(j_match2 + 530 + rand_number() % 30, i_match2 - 90 + rand_number() % 30); // �����ң����£�
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftDown();//����������
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftUp();
		Sleep(1000 + rand_number());// �ȴ����ʱ��

									// 7
		Sleep(3000);
		MouseMove(j_match2 + 718 + rand_number() % 20, i_match2 - 45 + rand_number() % 20); // �����ң����£�
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftDown();//����������
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftUp();
		Sleep(rand_number());// �ȴ����ʱ��

		// 8
		int time = 25;
		int rand = rand_number() % 10;
		MouseMove(j_match2 + 510 + rand, i_match2 - 365 + rand); // �����ң����£�
		while (time--)
		{
			MouseLeftDown();//����������
			Sleep(2000 + rand_number());// �ȴ����ʱ��
			MouseLeftUp();
		}

		// 9
		MouseMove(j_match2 + rand, i_match2 + rand); // �����ң����£�
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftDown();//����������
		Sleep(rand_number());// �ȴ����ʱ��
		MouseLeftUp();
		Sleep(rand_number());// �ȴ����ʱ��
	}
}

/* 
���ͻ�Ʊ궨
x1 = 663,x2 = 961,x3 = 1300
y1 = 356,y2 = 486,y3 = 600
*/

void MouseLeft()
{
	Sleep(rand_number());
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
	Sleep(rand_number());// �ȴ����ʱ��
}
void battleForJiejie(int i,int j)
{
	int x[3] = { 663, 961, 1300 };
	int y[3] = { 356,  486, 600 };
	int battleX[3] = { 731,1038,1347 };
	int battleY[3] = { 521,643,758 };

	// 2
	ShowDesktop();
	Sleep(1000);
	string desktopScreen = "./JpgData/����.jpg";
	string minOnmyoji = "./JpgData/��С��ͼ��.jpg";// ��Ҫ���н�ͼ����
	Screen(desktopScreen);

	// 3 ������int begin_i=1000,int begin_j=0
	int i_match, j_match;// ģ��ƥ���������
	float match_degree = 0.0;//ģ��ƥ��ֵ�����ֵ3.7xpow(10,6)
	GetPosition(desktopScreen, minOnmyoji, i_match, j_match, match_degree, 1000, 0, 3000, 3000);

	// 4
	MouseMove(j_match + 72, i_match + 15);
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
	Sleep(1000 + rand_number());// �ȴ����ʱ��

	// 5
	
	while((i+j)!=5&&j<3)
	{
		//int row = i / 3, col = i % 3;
		MouseMove(x[i]+ rand_number()%10, y[j]+ rand_number() % 10);
		MouseLeft();
		Sleep(rand_number());

		MouseMove(battleX[i] + rand_number() % 10, battleY[j] + rand_number() % 10);
		MouseLeft();

		
		MouseMove(1431 + rand_number() % 10, 720 + rand_number() % 10);
		Sleep(5000);
		MouseLeft();

		Sleep(45000);
		string battleEnd = "./JpgData/ս������.jpg";
		string battleEndDemo = "./JpgData/ս������ͼ��.jpg";// ��Ҫ���н�ͼ����
		string battleEnd2 = "./JpgData/ս������2.jpg";
		Screen(battleEnd);
		Mat src = imread(battleEnd, CV_LOAD_IMAGE_GRAYSCALE);
		Rect m_select = Rect(760, 420, 450, 400);
		Mat m_src = src(m_select);
		imwrite(battleEnd2, m_src);
		
		Sleep(1000);
		float thresholdMatch = 1000000.0;
		int i_match2, j_match2;// ģ��ƥ���������
		float match_degree2 = 0.0;//ģ��ƥ��ֵ�����ֵ3.7xpow(10,6)
		while (match_degree2 < thresholdMatch)
		{
			
			GetPosition(battleEnd2, battleEndDemo, i_match2, j_match2, match_degree2, 0, 0, 3000, 3000);
			Sleep(1000 + rand_number());
			cout << match_degree2;
		}
		MouseLeft();
		Sleep(2000 + rand_number());
		i++;
		if (i == 3)
		{
			j++;
			i = 0;
		}

	}
	
}


/*
������ӡ
�궨��������ӡ�� 622 511
�궨��ˢ�¡� 858 780 Rect(753, 738, 185, 80);// sad = 192509
�궨�����롱1372 426 ������ʽ(1317,396,110,70) // sad = 135310
�궨����ʼ��1431 720
�궨����ӡ�733 789
�궨��ʤ����960��682 Rect(820, 550, 280, 230);// sad = 822425
*/
bool isHaveRefresh()
{
	string battleRefresh = "./JpgData/������ӡˢ��.jpg";
	string battleRefreshTemplate = "./JpgData/ˢ��.jpg";// ��Ҫ���н�ͼ����
	string battleRefresh2 = "./JpgData/������ӡˢ��2.jpg";
	int i_match3, j_match3;// ģ��ƥ���������
	float match_degree3 = pow(10, 7);//ģ��ƥ��ֵ��SAD��Сֵ6*pow(10,6)
	float thresholdMatch3 = 2 * pow(10, 6);
	Screen(battleRefresh);
	Mat src = imread(battleRefresh);
	Rect m_select = Rect(753, 738, 185, 80);
	Mat m_src = src(m_select);
	imwrite(battleRefresh2, m_src);
	GetPosition(battleRefresh2, battleRefreshTemplate, i_match3, j_match3, match_degree3, 0, 0, 3000, 3000);
	return match_degree3 > thresholdMatch3 ? false : true;
}

bool isHaveJoin()
{
	string battleJoin = "./JpgData/������ӡ����.jpg";
	string battleJoinTemplate = "./JpgData/����.jpg";// ��Ҫ���н�ͼ����
	string battleJoin2 = "./JpgData/������ӡ����2.jpg";
	int i_match2, j_match2;// ģ��ƥ���������
	float match_degree2 = pow(10, 7);//ģ��ƥ��ֵ��SAD��Сֵ6*pow(10,6)
	float thresholdMatch = 6*pow(10, 6);
	Screen(battleJoin);
	Mat src = imread(battleJoin);
	Rect m_select = Rect(1310, 385, 110, 70);
	Mat m_src = src(m_select);
	imwrite(battleJoin2, m_src);
	GetPosition(battleJoin2, battleJoinTemplate, i_match2, j_match2, match_degree2, 0, 0, 3000, 3000);
	return match_degree2 > thresholdMatch ? false : true;
}

bool isHaveSuccess()
{
	string battleJoin = "./JpgData/ս������.jpg";
	string battleJoinTemplate = "./JpgData/ս������ͼ��.jpg";// ��Ҫ���н�ͼ����
	string battleJoin2 = "./JpgData/ս������2.jpg";
	int i_match2, j_match2;// ģ��ƥ���������
	float match_degree2 = pow(10, 7);//ģ��ƥ��ֵ��SAD��Сֵ6*pow(10,6)
	float thresholdMatch = pow(10, 6);
	Screen(battleJoin);
	Mat src = imread(battleJoin);
	Rect m_select = Rect(840, 580, 260, 200);
	Mat m_src = src(m_select);
	imwrite(battleJoin2, m_src);
	GetPosition(battleJoin2, battleJoinTemplate, i_match2, j_match2, match_degree2, 0, 0, 3000, 3000);
	//cout << match_degree2 << endl;
	return match_degree2 > thresholdMatch ? false : true;
}
void battleMonstor()
{
	ShowDesktop();
	Sleep(1000);
	string desktopScreen = "./JpgData/����.jpg";
	string minOnmyoji = "./JpgData/��С��ͼ��.jpg";// ��Ҫ���н�ͼ����
	Screen(desktopScreen);

	// 3 ������int begin_i=1000,int begin_j=0
	int i_match, j_match;// ģ��ƥ���������
	float match_degree = 0.0;//ģ��ƥ��ֵ�����ֵ3.7xpow(10,6)
	GetPosition(desktopScreen, minOnmyoji, i_match, j_match, match_degree, 1000, 0, 3000, 3000);

	// 4
	MouseMove(j_match + 72, i_match + 15);
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftDown();//����������
	Sleep(rand_number());// �ȴ����ʱ��
	MouseLeftUp();
	Sleep(1000 + rand_number());// �ȴ����ʱ��

	// ������Ϸ��
	// �ж��Ƿ���ˢ��
	int cnt = 0;
	while (1)
	{

		bool isBeginBattle = false;
		int isHaveRefreshCnt = 0, isHaveJoinCnt = 0, isHaveSuccessCnt = 0;
		while (isHaveRefresh())
		{
			//isHaveRefreshCnt++;
			//if (isHaveRefreshCnt > 50)
			//	break;
			// ���ˢ��
			Sleep(100);
			MouseMove(848 + rand_number() % 10, 770 + rand_number() % 10);
			Sleep(100);// �ȴ����ʱ��
			MouseLeftDown();//����������
			Sleep(100 + rand_number() % 20);// �ȴ����ʱ��
			MouseLeftUp();
			//Sleep(50);// ��Ҫ���Ժ�
			// �ж��Ƿ��м���
			while (isHaveJoin())
			{
				//isHaveJoinCnt++;
				//if (isHaveJoinCnt > 50)
				//	break;
				// �������
				MouseMove(1360 + rand_number() % 10, 416 + rand_number() % 10);
				Sleep(200);// �ȴ����ʱ��
				MouseLeftDown();//����������
				Sleep(100);// �ȴ����ʱ��
				MouseLeftUp();
				Sleep(200);// �ȴ����ʱ��
				MouseLeftDown();//����������
				Sleep(100);// �ȴ����ʱ��
				MouseLeftUp();
				//Sleep(100);
			}
			Sleep(300);
		}
		Sleep(7000 + rand_number());// �ȴ����ʱ��

		// �����ʼ
		MouseMove(1421 + rand_number() % 20, 710 + rand_number() % 20);
		MouseLeft();

		Sleep(30000 + rand_number());
		while (!isHaveSuccess())
		{
			//isHaveSuccessCnt++;
			//if (isHaveSuccessCnt > 10)
			//	break;
			Sleep(2000);
		}

		// ս������ ��������733 789
		MouseLeft();
		Sleep(2000);
		MouseMove(723 + rand_number() % 20, 779 + rand_number() % 20);
		MouseLeft();
		Sleep(2000);

		// û�п���ˢ�£����ܻ�����һ����
		while (!isHaveRefresh())
		{
			//isHaveRefreshCnt++;
			//if (isHaveRefreshCnt > 100)
			//	break;
			MouseMove(723 + rand_number() % 20, 779 + rand_number() % 20);
			MouseLeft();
			Sleep(2000);
		}
		cout << "�Ѿ�ս��" << cnt << "��" << endl;
		cnt++;
	}
	

}

int main()
{
	cout << "��ʼ" << endl;
	int battleWay = 1;
	switch (battleWay)
	{
	case 1: // ���ʮ
		battleForHun10();
		break;
	case 2: // ����ͻ��
		battleForJiejie(0,0);// (1,0)��ʾ��һ�У��ڶ���
		break;
	case 3:// ������ӡ
		battleMonstor();
		break;
	default:
		int test = battleWay;
		//isHaveSuccess();
		//testMousePos();

		/*
		string battleJoin = "./JpgData/������ӡ����.jpg";
		string battleJoinTemplate = "./JpgData/����.jpg";// ��Ҫ���н�ͼ����
		string battleJoin2 = "./JpgData/������ӡ����2.jpg";
		int i_match2, j_match2;// ģ��ƥ���������
		float match_degree2 = pow(10, 7);//ģ��ƥ��ֵ��SAD��Сֵ6*pow(10,6)
		float thresholdMatch = 6 * pow(10, 6);
		// Screen(battleJoin);
		Mat src = imread(battleJoin);
		Rect m_select = Rect(1310, 385, 110, 70);
		Mat m_src = src(m_select);
		imwrite(battleJoin2, m_src);
		GetPosition(battleJoin2, battleJoinTemplate, i_match2, j_match2, match_degree2, 0, 0, 3000, 3000);
		cout << match_degree2 << endl;
		*/

		
	}
	//system("pause");
	return 0;
}
