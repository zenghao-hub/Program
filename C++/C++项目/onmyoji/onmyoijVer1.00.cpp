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


// 获取随机时间
int rand_number()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	return sys.wMilliseconds;
}


/*
测试鼠标位置，debug电脑屏幕大小
阴阳师应用程序图片大概在120，1050（根据电脑情况与桌面大小而定）
*/
void testMousePos()
{
	for (int i = 0; i < 200; i++)
	{
		POINT pt = { 0,0 };
		GetCursorPos(&pt);
		Sleep(1000);// 延时一秒
		cout << pt.x << ' ' << pt.y << endl;// 输出鼠标的坐标
	}
}


/*
模板匹配
i_match j_match是匹配的坐标
begin_i begin_j是遍历搜索的起点，由于最小化图标在桌面下方，因此可以减小x遍历范围（begin_i = 1000，begin_j = 0）

*/
float templateMatch(const Mat & src, const Mat & temp, int & i_match, int & j_match, int Match_methold,int begin_i,int begin_j, int end_i, int end_j)
{
	int src_cols = src.cols;
	int src_rows = src.rows;
	int temp_cols = temp.cols;
	int temp_rows = temp.rows;
	// i代表宽，j代表长
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

			//cout << "查看匹配值"<<match_ij << endl;
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
截屏 并将图片保存至当前目录
str表示保存的目录
*/
int Screen(string str)
{
	//获取当前整个屏幕DC
	HDC hDC = GetDC(GetDesktopWindow());
	//CDC *pDC = CDC::FromHandle(hDC);

	//获得颜色模式
	int BitPerPixel = GetDeviceCaps(hDC, BITSPIXEL);
	int Width = GetDeviceCaps(hDC, HORZRES);
	int Height = GetDeviceCaps(hDC, VERTRES);

	//cout << "当前屏幕色彩模式为" << BitPerPixel << "位色彩" << endl
	//	<< "屏幕宽度：" << Width << endl
	//	<< "屏幕高度：" << Height << endl << endl;

	HDC memDC;//内存DC
	memDC = CreateCompatibleDC(hDC);

	HBITMAP memBitmap;
	HGDIOBJ oldmemBitmap;//建立和屏幕兼容的bitmap
	memBitmap = CreateCompatibleBitmap(hDC, Width, Height);

	oldmemBitmap = SelectObject(memDC, memBitmap);//将memBitmap选入内存DC
	BitBlt(memDC, 0, 0, Width, Height, hDC, 0, 0, SRCCOPY);//复制屏幕图像到内存DC

														   //以下代码保存memDC中的位图到文件
														   //BITMAP bmp;
														   //GetBitmap(&bmp);//获得位图信息

	BITMAP bm;
	GetObject(memBitmap, sizeof(BITMAP), (LPBYTE)&bm);

	FILE *fp = fopen(str.c_str(), "w+b");

	BITMAPINFOHEADER bih = { 0 };//位图信息头
	bih.biBitCount = bm.bmBitsPixel;//每个像素字节大小
	bih.biCompression = BI_RGB;
	bih.biHeight = bm.bmHeight;//高度
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bm.bmWidthBytes * bm.bmHeight;//图像数据大小
	bih.biWidth = bm.bmWidth;//宽度

	BITMAPFILEHEADER bfh = { 0 };//位图文件头
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
	bfh.bfSize = bfh.bfOffBits + bm.bmWidthBytes * bm.bmHeight;//文件总的大小
	bfh.bfType = (WORD)0x4d42;

	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//写入位图文件头

	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//写入位图信息头

	byte * p = new byte[bm.bmWidthBytes * bm.bmHeight];//申请内存保存位图数据

	GetDIBits(memDC, (HBITMAP)memBitmap, 0, Height, p,
		(LPBITMAPINFO)&bih, DIB_RGB_COLORS);//获取位图数据

	fwrite(p, 1, bm.bmWidthBytes * bm.bmHeight, fp);//写入位图数据

	delete[] p;
	fclose(fp);
	SelectObject(memDC, oldmemBitmap);

	// cout << "屏幕图像已存储到文件中" << endl;
	return 0;
}

// 截取胜利图
int Screen2(string str)
{
	//获取当前整个屏幕DC
	HDC hDC = GetDC(GetDesktopWindow());
	//CDC *pDC = CDC::FromHandle(hDC);

	//获得颜色模式
	int BitPerPixel = GetDeviceCaps(hDC, BITSPIXEL);
	int Width = GetDeviceCaps(hDC, HORZRES);
	int Height = GetDeviceCaps(hDC, VERTRES);

	//cout << "当前屏幕色彩模式为" << BitPerPixel << "位色彩" << endl
	//	<< "屏幕宽度：" << Width << endl
	//	<< "屏幕高度：" << Height << endl << endl;

	HDC memDC;//内存DC
	memDC = CreateCompatibleDC(hDC);

	HBITMAP memBitmap;
	HGDIOBJ oldmemBitmap;//建立和屏幕兼容的bitmap
	memBitmap = CreateCompatibleBitmap(hDC, 450, 400); // 450 400 

	oldmemBitmap = SelectObject(memDC, memBitmap);//将memBitmap选入内存DC
	BitBlt(memDC, 0, 0, 450, 400, hDC, 0, 0, SRCCOPY);//复制屏幕图像到内存DC 
	// BitBlt(memDC, 760, 420, 450, 400, hDC, 0, 420, SRCCOPY);
														   //以下代码保存memDC中的位图到文件
														   //BITMAP bmp;
														   //GetBitmap(&bmp);//获得位图信息

	BITMAP bm;
	GetObject(memBitmap, sizeof(BITMAP), (LPBYTE)&bm);

	FILE *fp = fopen(str.c_str(), "w+b");

	BITMAPINFOHEADER bih = { 0 };//位图信息头
	bih.biBitCount = bm.bmBitsPixel;//每个像素字节大小
	bih.biCompression = BI_RGB;
	bih.biHeight = bm.bmHeight;//高度
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bm.bmWidthBytes * bm.bmHeight;//图像数据大小
	bih.biWidth = bm.bmWidth;//宽度

	BITMAPFILEHEADER bfh = { 0 };//位图文件头
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
	bfh.bfSize = bfh.bfOffBits + bm.bmWidthBytes * bm.bmHeight;//文件总的大小
	bfh.bfType = (WORD)0x4d42;

	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//写入位图文件头

	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//写入位图信息头

	byte * p = new byte[bm.bmWidthBytes * bm.bmHeight];//申请内存保存位图数据

	GetDIBits(memDC, (HBITMAP)memBitmap, 0, Height, p,
		(LPBITMAPINFO)&bih, DIB_RGB_COLORS);//获取位图数据

	fwrite(p, 1, bm.bmWidthBytes * bm.bmHeight, fp);//写入位图数据

	delete[] p;
	fclose(fp);
	SelectObject(memDC, oldmemBitmap);

	// cout << "屏幕图像已存储到文件中" << endl;
	return 0;
}


// 单击小图标，进入onmyoji
void step1()
{
	// 打开阴阳师程序（放在最小化最前面）
	ShowDesktop();
	MouseMove(120, 1050);
	Sleep(rand_number());// 等待随机时间
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
}

// 单击挑战，进入魂十挑战
void step2()
{
	int x = 1230, y = 650;
	x = x + rand_number() % 20;
	y = y + rand_number() % 20;
	MouseMove(x, y);// 移动到挑战的位置
	Sleep(3000 + rand_number());// 等待随机时间
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
}

// 单击开始，魂十战斗开始
void step3()
{
	int x = 1430, y = 700;
	x = x + rand_number() % 30;
	y = y + rand_number() % 30;
	MouseMove(x, y);// 移动到挑战的位置
	Sleep(2000 + rand_number());// 等待随机时间

	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();

	Sleep(rand_number());
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
}


/*
该测试程序，已经经过一晚上的测试。符合需求
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
		Sleep(rand_number());// 等待随机时间
		MouseMove(1000, 500);
		// 战斗过程中，需要2min左右，随着阵容的增强，可以减少时间
		Sleep(60000 + rand_number()); // 需要等待120s后左键


		MouseLeftDown();//鼠标左键按下
		Sleep(rand_number());// 等待随机时间
		MouseLeftUp();

		Sleep(rand_number());
		MouseLeftDown();//鼠标左键按下
		Sleep(rand_number());// 等待随机时间
		MouseLeftUp();

		Sleep(rand_number());
		MouseLeftDown();//鼠标左键按下
		Sleep(rand_number());// 等待随机时间
		MouseLeftUp();

		Sleep(3000 + rand_number());
	}
	//testMousePos();
	return 0;

	// 游戏愉快
}

/*
图形匹配获取位置，匹配值，遍历起始
int i_match, j_match;// 模板匹配的坐标结果
float match_degree;//模板匹配值，最大值3.7xpow(10,6)
1000, 0 是第三步int begin_i,int begin_j
*/
void GetPosition(string desktopScreen, string minOnmyoji, int &i_match, int &j_match, float &match_degree,int begin_i,int begin_j, int end_i, int end_j)
{
	Mat src = imread(desktopScreen, CV_LOAD_IMAGE_GRAYSCALE);
	Mat temp = imread(minOnmyoji, CV_LOAD_IMAGE_GRAYSCALE);
	match_degree = templateMatch(src, temp, i_match, j_match, SQDIFF, begin_i, begin_j, end_i, end_j);
	//cout << i_match << endl << j_match << endl << match_degree << endl;
}
/*
阴阳师辅助程序步骤
要求：打开阴阳师，登陆阴阳师，打开到魂十挑战界面，然后最小化。（这是必需的）
1. 完成上述要求的步骤
2. 返回桌面并截取桌面图片，保存为./JpgData/桌面.jpg
3. 模板匹配计算最下化图标的位置
4. 根据计算坐标结果 打开阴阳师
5. 打开阴阳师后截图，图像匹配，计算出阴阳师窗口的位置，阴阳师窗口大小是固定的。
需要标定好位置(311,556)，八歧大蛇在窗口下方560，右边310位置处。“挑战”在“八歧大蛇”的下方 -90，右边530
6. 移动到挑战位置，进行挑战
7. 等待3s后，点击“开始”。“开始”在“八歧大蛇”的右边728，下方-35
8. 移动到怪物位置，右边515，下方-360
9. 一直点击怪物位置，直到战斗结束。因此，战斗结束的条件（目前采用延时结束）,移动到八歧大蛇，战斗结束
10. 循环6-9步

1480 800
*/

// 魂十过程
void battleForHun10()
{
	// 2
	ShowDesktop();
	Sleep(1000);
	string desktopScreen = "./JpgData/桌面.jpg";
	string minOnmyoji = "./JpgData/最小化图标.jpg";// 需要自行截图保存
	Screen(desktopScreen);

	// 3 第三步int begin_i=1000,int begin_j=0
	int i_match, j_match;// 模板匹配的坐标结果
	float match_degree = 0.0;//模板匹配值，最大值3.7xpow(10,6)
	GetPosition(desktopScreen, minOnmyoji, i_match, j_match, match_degree, 1000, 0, 3000, 3000);

	// 4
	MouseMove(j_match + 72, i_match + 15);
	Sleep(rand_number());// 等待随机时间
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
	Sleep(1000 + rand_number());// 等待随机时间

	// 5 八歧大蛇位置747 701
	string fullScreen = "./JpgData/阴阳师窗口截屏.jpg";
	string hun10 = "./JpgData/魂十挑战界面.jpg";
	Screen(fullScreen);
	int i_match2, j_match2;// 模板匹配的坐标结果
	float match_degree2 = 0.0;//模板匹配值，最大值3.7xpow(10,6)
	GetPosition(fullScreen, hun10, i_match2, j_match2, match_degree2, 559, 20, 905, 1000);
	while (1)
	{
		// 6 
		MouseMove(j_match2 + 530 + rand_number() % 30, i_match2 - 90 + rand_number() % 30); // （向右，向下）
		Sleep(rand_number());// 等待随机时间
		MouseLeftDown();//鼠标左键按下
		Sleep(rand_number());// 等待随机时间
		MouseLeftUp();
		Sleep(1000 + rand_number());// 等待随机时间

									// 7
		Sleep(3000);
		MouseMove(j_match2 + 718 + rand_number() % 20, i_match2 - 45 + rand_number() % 20); // （向右，向下）
		Sleep(rand_number());// 等待随机时间
		MouseLeftDown();//鼠标左键按下
		Sleep(rand_number());// 等待随机时间
		MouseLeftUp();
		Sleep(rand_number());// 等待随机时间

		// 8
		int time = 25;
		int rand = rand_number() % 10;
		MouseMove(j_match2 + 510 + rand, i_match2 - 365 + rand); // （向右，向下）
		while (time--)
		{
			MouseLeftDown();//鼠标左键按下
			Sleep(2000 + rand_number());// 等待随机时间
			MouseLeftUp();
		}

		// 9
		MouseMove(j_match2 + rand, i_match2 + rand); // （向右，向下）
		Sleep(rand_number());// 等待随机时间
		MouseLeftDown();//鼠标左键按下
		Sleep(rand_number());// 等待随机时间
		MouseLeftUp();
		Sleep(rand_number());// 等待随机时间
	}
}

/* 
结界突破标定
x1 = 663,x2 = 961,x3 = 1300
y1 = 356,y2 = 486,y3 = 600
*/

void MouseLeft()
{
	Sleep(rand_number());
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
	Sleep(rand_number());// 等待随机时间
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
	string desktopScreen = "./JpgData/桌面.jpg";
	string minOnmyoji = "./JpgData/最小化图标.jpg";// 需要自行截图保存
	Screen(desktopScreen);

	// 3 第三步int begin_i=1000,int begin_j=0
	int i_match, j_match;// 模板匹配的坐标结果
	float match_degree = 0.0;//模板匹配值，最大值3.7xpow(10,6)
	GetPosition(desktopScreen, minOnmyoji, i_match, j_match, match_degree, 1000, 0, 3000, 3000);

	// 4
	MouseMove(j_match + 72, i_match + 15);
	Sleep(rand_number());// 等待随机时间
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
	Sleep(1000 + rand_number());// 等待随机时间

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
		string battleEnd = "./JpgData/战斗结束.jpg";
		string battleEndDemo = "./JpgData/战斗结束图标.jpg";// 需要自行截图保存
		string battleEnd2 = "./JpgData/战斗结束2.jpg";
		Screen(battleEnd);
		Mat src = imread(battleEnd, CV_LOAD_IMAGE_GRAYSCALE);
		Rect m_select = Rect(760, 420, 450, 400);
		Mat m_src = src(m_select);
		imwrite(battleEnd2, m_src);
		
		Sleep(1000);
		float thresholdMatch = 1000000.0;
		int i_match2, j_match2;// 模板匹配的坐标结果
		float match_degree2 = 0.0;//模板匹配值，最大值3.7xpow(10,6)
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
妖气封印
标定“妖气封印” 622 511
标定“刷新” 858 780 Rect(753, 738, 185, 80);// sad = 192509
标定“加入”1372 426 矩阵形式(1317,396,110,70) // sad = 135310
标定“开始”1431 720
标定“组队”733 789
标定“胜利”960，682 Rect(820, 550, 280, 230);// sad = 822425
*/
bool isHaveRefresh()
{
	string battleRefresh = "./JpgData/妖气封印刷新.jpg";
	string battleRefreshTemplate = "./JpgData/刷新.jpg";// 需要自行截图保存
	string battleRefresh2 = "./JpgData/妖气封印刷新2.jpg";
	int i_match3, j_match3;// 模板匹配的坐标结果
	float match_degree3 = pow(10, 7);//模板匹配值，SAD最小值6*pow(10,6)
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
	string battleJoin = "./JpgData/妖气封印加入.jpg";
	string battleJoinTemplate = "./JpgData/加入.jpg";// 需要自行截图保存
	string battleJoin2 = "./JpgData/妖气封印加入2.jpg";
	int i_match2, j_match2;// 模板匹配的坐标结果
	float match_degree2 = pow(10, 7);//模板匹配值，SAD最小值6*pow(10,6)
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
	string battleJoin = "./JpgData/战斗结束.jpg";
	string battleJoinTemplate = "./JpgData/战斗结束图标.jpg";// 需要自行截图保存
	string battleJoin2 = "./JpgData/战斗结束2.jpg";
	int i_match2, j_match2;// 模板匹配的坐标结果
	float match_degree2 = pow(10, 7);//模板匹配值，SAD最小值6*pow(10,6)
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
	string desktopScreen = "./JpgData/桌面.jpg";
	string minOnmyoji = "./JpgData/最小化图标.jpg";// 需要自行截图保存
	Screen(desktopScreen);

	// 3 第三步int begin_i=1000,int begin_j=0
	int i_match, j_match;// 模板匹配的坐标结果
	float match_degree = 0.0;//模板匹配值，最大值3.7xpow(10,6)
	GetPosition(desktopScreen, minOnmyoji, i_match, j_match, match_degree, 1000, 0, 3000, 3000);

	// 4
	MouseMove(j_match + 72, i_match + 15);
	Sleep(rand_number());// 等待随机时间
	MouseLeftDown();//鼠标左键按下
	Sleep(rand_number());// 等待随机时间
	MouseLeftUp();
	Sleep(1000 + rand_number());// 等待随机时间

	// 进入游戏后
	// 判断是否有刷新
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
			// 点击刷新
			Sleep(100);
			MouseMove(848 + rand_number() % 10, 770 + rand_number() % 10);
			Sleep(100);// 等待随机时间
			MouseLeftDown();//鼠标左键按下
			Sleep(100 + rand_number() % 20);// 等待随机时间
			MouseLeftUp();
			//Sleep(50);// 需要调试好
			// 判断是否有加入
			while (isHaveJoin())
			{
				//isHaveJoinCnt++;
				//if (isHaveJoinCnt > 50)
				//	break;
				// 点击加入
				MouseMove(1360 + rand_number() % 10, 416 + rand_number() % 10);
				Sleep(200);// 等待随机时间
				MouseLeftDown();//鼠标左键按下
				Sleep(100);// 等待随机时间
				MouseLeftUp();
				Sleep(200);// 等待随机时间
				MouseLeftDown();//鼠标左键按下
				Sleep(100);// 等待随机时间
				MouseLeftUp();
				//Sleep(100);
			}
			Sleep(300);
		}
		Sleep(7000 + rand_number());// 等待随机时间

		// 点击开始
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

		// 战斗结束 并点击组队733 789
		MouseLeft();
		Sleep(2000);
		MouseMove(723 + rand_number() % 20, 779 + rand_number() % 20);
		MouseLeft();
		Sleep(2000);

		// 没有看到刷新，可能还在上一画面
		while (!isHaveRefresh())
		{
			//isHaveRefreshCnt++;
			//if (isHaveRefreshCnt > 100)
			//	break;
			MouseMove(723 + rand_number() % 20, 779 + rand_number() % 20);
			MouseLeft();
			Sleep(2000);
		}
		cout << "已经战斗" << cnt << "次" << endl;
		cnt++;
	}
	

}

int main()
{
	cout << "开始" << endl;
	int battleWay = 1;
	switch (battleWay)
	{
	case 1: // 打魂十
		battleForHun10();
		break;
	case 2: // 打结界突破
		battleForJiejie(0,0);// (1,0)表示第一行，第二列
		break;
	case 3:// 妖气封印
		battleMonstor();
		break;
	default:
		int test = battleWay;
		//isHaveSuccess();
		//testMousePos();

		/*
		string battleJoin = "./JpgData/妖气封印加入.jpg";
		string battleJoinTemplate = "./JpgData/加入.jpg";// 需要自行截图保存
		string battleJoin2 = "./JpgData/妖气封印加入2.jpg";
		int i_match2, j_match2;// 模板匹配的坐标结果
		float match_degree2 = pow(10, 7);//模板匹配值，SAD最小值6*pow(10,6)
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
