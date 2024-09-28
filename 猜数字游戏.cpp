#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include <windows.h>				//用到了定时函数sleep()
#include <math.h>
#include <string.h>
#include<iostream>
#include<ctime>
#include <wchar.h>
#include<Windows.h>
#pragma comment(lib,"Winmm.lib")	//引用Winmm.lib链接库


#define  High 720
#define Width 960
#define MAX 10000


int button_judge(int x, int y);	//按钮函数
void game();//游戏实现函数
void rule();//规则说明函数


int r[5][4] = { {200, 100, 760, 150},{400,300,550,350},{400,400,550,450},{300,200,500,400 },{400,500,550,550} };//三个按钮的二维数组

RECT u1 = { r[0][0], r[0][1], r[0][2], r[0][3] }; //rect对象用来存储一个矩形框的左上角坐标、宽度和高度。
RECT u2 = { r[1][0], r[1][1], r[1][2], r[1][3] };
RECT u3 = { r[2][0], r[2][1], r[2][2], r[2][3] };
RECT u4 = { r[3][0], r[3][1], r[3][2], r[3][3] };
RECT u5 = { r[4][0], r[4][1], r[4][2], r[4][3] };


//按钮返回函数
int button_judge(int x, int y)
{
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	if (x > r[4][0] && x<r[4][2] && y>r[4][1] && y < r[4][3])return 5;
	return 0;
}

//游戏实现函数
void game() {
	closegraph();//关闭绘图环境
	initgraph(Width, High);	//初始化920*720的画布
	IMAGE img_bj2;
	loadimage(&img_bj2, _T("D:\\两个小游戏素材\\beijing1.jpg"));
	putimage(0, 0, &img_bj2);

	int c = 8;//c: 猜数次数计数器;
	int a, z, t, i, m, s, j, k, l[4], val, val2, val3, val4, val5, val6;                   //j:数字正确的位数 k:位置正确的位数;
	int Time;

	srand((unsigned)time(NULL));                             //随机数种子(否则便是伪随机数);
	z = rand() % MAX + 1;      //计算机想一个随机数z;

	setbkmode(TRANSPARENT);//这个函数用于设置当前设备图案填充和文字输出时的背景模式。
	settextcolor(GREEN);// 设置当前文字颜色
	settextstyle(30, 0, _T("宋体"));//设置字号、字体

	wchar_t p1[10];// 定义字符串缓冲区，并接收用户输入
	mciSendString(L"close bk2", NULL, 0, NULL);
	InputBox(p1, 10, L"请输入猜测的数字\n共有8次机会\n退出可直接输入0");


	val = _wtoi(p1);// 将用户输入转换为数字

	int* q1 = &val;

FLAG1:
	while (1)
	{
		if (val == 0)
		{
			exit(0);
		}
		if (val >= 10000)
		{
			wchar_t p3[100];
			InputBox(p3, 10, L"输入过大\n请重新输入：\n退出可直接输入0");
			val3 = _wtoi(p3);// 将用户输入转换为数字
			val = val3;
			goto FLAG1;

		}
		if (val < 0)
		{
			wchar_t p4[100];
			InputBox(p4, 10, L"输入过小\n请重新输入：\n退出可直接输入0");
			val = _wtoi(p4);// 将用户输入转换为数字
			q1 = &val4;
			goto FLAG1;
		}
		a = z, j = 0, k = 0, l[0] = l[1] = l[2] = l[3] = 0;
		for (i = 1; i < 5; i++)                         //i:原数中的第i位数,个位为第一位，千位为第四位;
		{
			s = val;
			m = 1;
			for (t = 1; t < 5; t++)                   //人所猜想的数;
			{
				if (a % 10 == s % 10)              //若第i位与人猜的第t位相同;
				{
					if (m && t != l[0] && t != l[1] && t != l[2] && t != l[3])//若该位置上的数字尚未与其它数字相同;
					{                                                        //避免出现重复比较；
						j++;
						m = 0;
						l[j - 1] = t; 	 //记录相同数字时该数字在所猜数字中的位置;
					}
					if (i == t) k++; 	//若位置也相同，则正确位置的数量k加1;
				}
				s /= 10;
			}
			a /= 10;
		}
		if (k != 4)
		{
			c--;
			if (c == 3)
			{
				wchar_t  k2[100] = L"";
				swprintf(k2, 100, L"提示信息： %d A %d B\n你只剩最后三次机会了 加油！\n退出可直接输入0", k, j);//转化为字符
				wchar_t p5[100];
				InputBox(p5, 100, k2);
				val = _wtoi(p5);// 将用户输入转换为数字
				q1 = &val5;
				goto FLAG1;
			}
			else if (c <= 0)
			{

				solidrectangle(r[0][0], r[0][1], r[0][2], r[0][3]);//这个函数用于画无边框的填充矩形
				setbkmode(TRANSPARENT);//这个函数用于设置当前设备图案填充和文字输出时的背景模式。
				settextcolor(RED);// 设置当前文字颜色
				drawtext(_T("挑战失败"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
			FLAG2:				wchar_t p6[10];
				InputBox(p6, 10, L"重新开始请按1\n退出请按0");
				val6 = _wtoi(p6);
				if (val6 == 0)
				{
					exit(0);
				}
				if (val6 == 1)
				{
					game();
				}
			}
			wchar_t  k1[100] = L"";
			swprintf(k1, 100, L"提示信息： %d A %d B\nA代表数字和位置都猜对\nB代表数字猜对，但位置不对\n请继续输入:\n退出可直接输入0", k, j);//转化为字符
			wchar_t p2[100];// 定义字符串缓冲区，并接收用户输入
			InputBox(p2, 100, k1);
			val = _wtoi(p2);// 将用户输入转换为数字

			q1 = &val2;//使用户重新输入的数字为上面的p1
			goto FLAG1;
		}

		else if (k == 4)	//k==4表示答对了
		{

			if (c == 8)
			{
				drawtext(_T("\n太棒了！你只用了1次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open unbelievable.mp3 alias bk3"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk3 repeat"), NULL, 0, NULL);
				Time = 15;
				while (1)
				{

					Sleep(100);
					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk3 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}

				break;
			}
			else if (c == 7)
			{
				drawtext(_T("\n太棒了！你只用了2次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open excellent.mp3 alias bk4"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk4 repeat"), NULL, 0, NULL);
				Time = 12;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk4 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			else if (c == 6)
			{
				drawtext(_T("\n太棒了！你只用了3次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open amazing.mp3 alias bk5"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk5 repeat"), NULL, 0, NULL);
				Time = 8;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk5 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			else if (c == 5)
			{
				drawtext(_T("\n太棒了！你只用了4次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open unbelievable.mp3 alias bk3"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk3 repeat"), NULL, 0, NULL);
				Time = 8;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk3 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			else if (c == 4)
			{
				drawtext(_T("\n太棒了！你只用了5次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open amazing.mp3 alias bk5"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk5 repeat"), NULL, 0, NULL);
				Time = 8;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk5 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			else if (c == 3)
			{
				drawtext(_T("\n你用了6次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open excellent.mp3 alias bk4"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk4 repeat"), NULL, 0, NULL);
				Time = 8;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk4 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			else if (c == 2)
			{
				drawtext(_T("\n你用了7次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open great.mp3 alias bk6"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk6 repeat"), NULL, 0, NULL);
				Time = 8;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk6 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			else if (c == 1)
			{
				drawtext(_T("\n你只用了8次机会就猜对了！"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
				mciSendString(_T("open good.mp3 alias bk7"), NULL, 0, NULL);		//播放音乐
				mciSendString(_T("play bk7 repeat"), NULL, 0, NULL);
				Time = 8;
				while (1)
				{
					Sleep(100);

					Time--;
					if (Time == 0)
					{
						mciSendString(_T("close bk7 "), NULL, 0, NULL);
						goto FLAG2;
					}
				}
				break;
			}
			break;
		}
	}
}


//游戏说明
void rule() {
	closegraph();//关闭绘图环境
	initgraph(Width, High);	//初始化920*720的画布
	IMAGE img_bj2;
	loadimage(&img_bj2, _T("D:\\两个小游戏素材\\beijing1.jpg"));
	putimage(0, 0, &img_bj2);
	wchar_t p8[10];
	InputBox(p8, 10, L"猜测的数字范围在0~9999之间\n玩家总共猜测次数为8次\n提示信息中的A代表数字和位置都猜对\nB代表数字猜对，但位置不对\n根据玩家使用的次数判定成绩等级\n\n开始游戏请按1\n退出游戏请按0");
	int val8 = _wtoi(p8);
	if (val8 == 0)
	{
		exit(0);
	}
	if (val8 == 1)
	{
		game();
	}

}

//主函树
int main()
{

	int i, event = 0;
	initgraph(Width, High);	//初始化920*720的画布
	IMAGE img_bj1;
	loadimage(&img_bj1, _T("D:\\两个小游戏素材\\beijing1.jpg"));
	putimage(0, 0, &img_bj1);
	mciSendString(_T("open beijing.mp3 alias bk1"), NULL, 0, NULL);		//播放背景音乐
	mciSendString(_T("play bk1 repeat"), NULL, 0, NULL);
	setfillcolor(RGB(135, 206, 250));
	solidrectangle(r[0][0], r[0][1], r[0][2], r[0][3]);//这个函数用于画无边框的填充矩形
	setbkmode(TRANSPARENT);//这个函数用于设置当前设备图案填充和文字输出时的背景模式。
	settextcolor(GREEN);// 设置当前文字颜色
	settextstyle(30, 0, _T("宋体"));//设置字号、字体
	drawtext(_T("欢迎来到猜数字游戏"), &u1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u1内输入文字，水平居中，垂直居中，单行显示
	settextcolor(RGB(30, 144, 255));// 设置当前文字颜色
	drawtext(_T("开始游戏"), &u2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u2内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("退出游戏"), &u3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u3内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("游戏说明"), &u5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域u3内输入文字，水平居中，垂直居中，单行显示
	MOUSEMSG m;//鼠标指针

	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）

				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(20);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			//按照按钮判断左键单击后的操作
			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 2:
				mciSendString(_T("open start.mp3 alias bk2"), NULL, 0, NULL);
				mciSendString(_T("play bk2 repeat"), NULL, 0, NULL);
				game();

			case 3:
				closegraph();//关闭绘图环境
				mciSendString(_T("close bk1"), NULL, 0, NULL);//关闭音乐
				exit(0);//正常退出
			case 5:
				rule();
			}

		}
	}
}
