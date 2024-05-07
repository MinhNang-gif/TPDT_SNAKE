#include "mylib.h"
#define MAX 100
int sl = 4;
int score = 0;
int ms;
//================ khu vuc khai bao nguyen mau ham ============
void ve_tuong_tren();
void ve_tuong_duoi();
void ve_tuong_phai();
void ve_tuong_duoi();
void ve_tuong();
void khoi_tao_ran(int toadox[], int toadoy[]);
void xoa_du_lieu_cu(int toadox[], int toadoy[]);
void ve_ran(int toadox[], int toadoy[]);
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int& xqua, int& yqua);
void them(int a[], int x);
void xoa(int a[], int vt);
bool kt_ran_cham_tuong(int x0, int y0);
bool kt_ran_cham_duoi(int toadox[], int toadoy[]);
bool kt_ran(int toadox[], int toadoy[]);
void tao_qua(int& xqua, int& yqua, int toadox[], int toadoy[]);
bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[]);
bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0);
void hien_thi_diem(int diem);
void tinh_diem();
void hien_thi_game_over(int diem);
void hien_thi_lua_chon();
void chon_muc_do();
//============= ham main - xu ly chinh ==============
int main()
{
	chon_muc_do();
	//---------------
	bool gameover = false;
	int toadox[MAX], toadoy[MAX];
	ve_tuong();
	khoi_tao_ran(toadox, toadoy);
	ve_ran(toadox, toadoy);
	//===================== kiem tra va tao qua ==============
	srand(time(NULL));
	int xqua = 0, yqua = 0;
	//tao qua
	tao_qua(xqua, yqua, toadox, toadoy);
	int x = 50, y = 13;// dinh hinh vi tri can di chuyen cho ran
	int check = 2;
	while (gameover == false)
	{
		gotoXY(0, 0);
		hien_thi_diem(score);
		//system("cls");
		//========= backspace
		xoa_du_lieu_cu(toadox, toadoy);
		// 0 : di xuong
		//1: di len
		//2: qua phai
		//3: trai
		//========= dieu khien
		if (_kbhit())
		{
			char kitu = _getch();
			if (kitu == -32)
			{
				kitu = _getch();
				if (kitu == 72 && check != 0)//di len
				{
					check = 1;
				}
				else if (kitu == 80 && check != 1)//di xuong
				{
					check = 0;
				}
				else if (kitu == 77 && check != 3)//di phai
				{
					check = 2;
				}
				else if (kitu == 75 && check != 2)//di trai
				{
					check = 3;
				}
			}
		}
		//========= thuc hien di chuyen
		if (check == 0)
		{
			y++;//di xuong
		}
		else if (check == 1)
		{
			y--;//di len
		}
		else if (check == 2)
		{
			x++;//di qua phai
		}
		else if (check == 3)
		{
			x--;//di qua trai	
		}
		xu_ly_ran(toadox, toadoy, x, y, xqua, yqua);
		//========== kiem tra =========
		gameover = kt_ran(toadox, toadoy);
		Sleep(ms);
	}
	hien_thi_game_over(score);
	hien_thi_lua_chon();
	_getch();
	return 0;
}
//============ khu vuc dinh nghia ham =============
void ve_tuong_tren()
{
	int x = 10, y = 1;
	while (x <= 100)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}
void ve_tuong_duoi()
{
	int x = 10, y = 26;
	while (x <= 100)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}
void ve_tuong_phai()
{
	int x = 100, y = 1;
	while (y <= 26)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
	}
}
void ve_tuong_trai()
{
	int x = 10, y = 1;
	while (y <= 26)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
	}
}
void ve_tuong()
{
	SetColor(11);
	ve_tuong_tren();
	ve_tuong_duoi();
	ve_tuong_phai();
	ve_tuong_trai();
	SetColor(7);
}
void khoi_tao_ran(int toadox[], int toadoy[])
{
	int x = 50, y = 13;
	for (int i = 0; i < sl; i++)
	{
		toadox[i] = x;
		toadoy[i] = y;
		x--;
	}
}
void ve_ran(int toadox[], int toadoy[])
{
	for (int i = 0; i < sl; i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		if (i == 0)
		{
			cout << "0";
		}
		else
		{
			cout << "o";
		}
	}
}
void xoa_du_lieu_cu(int toadox[], int toadoy[])
{
	for (int i = 0; i < sl; i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		cout << " ";
	}
}
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int& xqua, int& yqua)
{
	//b1: them toa do moi vao dau mang
	them(toadox, x); 
	them(toadoy, y); 

	if (kt_ran_an_qua(xqua, yqua, toadox[0], toadoy[0]) == false)
	{
		//b2: xoa toa do cuoi mang
		xoa(toadox, sl - 1); 
		xoa(toadoy, sl - 1); 

	}
	else
	{
		tinh_diem();
		sl--;
		tao_qua(xqua, yqua, toadox, toadoy);
	}
	//b3: ve ran
	ve_ran(toadox, toadoy);
}
void them(int a[], int x)
{
	for (int i = sl; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
	sl++;
}
void xoa(int a[], int vt)
{
	for (int i = vt; i < sl; i++)
	{
		a[i] = a[i + 1];
	}
	sl--;
}
bool kt_ran_cham_tuong(int x0, int y0)
{
	//ran cham tuong tren
	if (y0 == 1 && (x0 >= 10 && x0 <= 100))
	{
		return true;//gameover
	}
	//ran cham tuong duoi
	else if (y0 == 26 && (x0 >= 10 && x0 <= 100))
	{
		return true;//gameover
	}
	//ran cham tuong phai
	else if (x0 == 100 && (y0 >= 1 && y0 <= 26))
	{
		return true;//gameover
	}
	//ran cham tuong trai
	else if (x0 == 10 && (y0 >= 1 && y0 <= 26))
	{
		return true;//gameover
	}
	return false;
}
bool kt_ran_cham_duoi(int toadox[], int toadoy[])
{
	for (int i = 1; i < sl; i++)
	{
		if ((toadox[0] == toadox[i]) && (toadoy[0] == toadoy[i]))
		{
			return true;//gameover
		}
	}
	return false;
}
bool kt_ran(int toadox[], int toadoy[])
{
	bool kt1 = kt_ran_cham_duoi(toadox, toadoy);//gameover = true
	bool kt2 = kt_ran_cham_tuong(toadox[0], toadoy[0]);//gameover = false
	if (kt1 == true || kt2 == true)
	{
		return true;//gameover
	}
	return false;
}
void tao_qua(int& xqua, int& yqua, int toadox[], int toadoy[])
{
	do
	{
		//11 <= xqua <= 99
		xqua = rand() % (99 - 11 + 1) + 11;
		//2 <= yqua <= 25
		yqua = rand() % (25 - 2 + 1) + 2;
	} while (kt_ran_de_qua(xqua, yqua, toadox, toadoy) == true);
	int i = rand() % (15 - 1 + 1) + 1;
	SetColor(i);
	gotoXY(xqua, yqua);
	cout << "@";
	SetColor(7);//mau trang
}
bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[])
{
	for (int i = 0; i < sl; i++)
	{
		if ((xqua == toadox[i]) && (yqua == toadoy[i]))
		{
			return true;//ran de len qua
		}
	}
	return false;
}
bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0)
{
	if ((x0 == xqua) && (y0 == yqua))
	{
		return true;//ran an qua
	}
	return false;
}
void tinh_diem()
{
	score++;
}

void hien_thi_diem(int diem)
{
	cout << "Diem: " << diem;
}
void hien_thi_game_over(int diem)
{
	system("cls"); 
	gotoXY(40, 13);
	std::cout << "Game Over";
	gotoXY(40, 14);
	hien_thi_diem(diem); 
}

void hien_thi_lua_chon()
{
	gotoXY(40, 15);
	cout << "1. Choi tiep";
	gotoXY(40, 16);
	cout << "2. Thoat";
	gotoXY(40, 17);
	cout << "==================\n";
	char lc;
	do {
		gotoXY(58, 18);
		cout << "  ";
		gotoXY(40, 18);
		cout << "Lua chon cua ban: ";
		cin >> lc;
		if (lc == '1')
		{
			system("cls");
			score = 0;
			sl = 4;
			main();
		}
		else if (lc == '2') {
			system("cls");
			exit(0);
		}
	} while (lc != '1' && lc != '2');
}
void chon_muc_do() {
	system("cls");
	gotoXY(40, 10);
	cout << "CHON MUC DO:";
	gotoXY(40, 11);
	cout << "1. DE";
	gotoXY(40, 12);
	cout << "2. TRUNG BINH";
	gotoXY(40, 13);
	cout << "3. KHO";
	gotoXY(40, 14);
	cout << "4. CUC KHO";
	gotoXY(40, 15);
	cout << "==================\n";
	char lc;
	do {
		gotoXY(58, 16);
		cout << "  ";
		gotoXY(40, 16);
		cout << "Lua chon cua ban: ";
		cin >> lc;
		if (lc == '1'){
			ms = 200;
		}
		else if (lc == '2') {
			ms = 100;
		}
		else if (lc == '3') {
			ms = 50;
		}
		else if (lc == '4') {
			ms = 20;
		}
	} while (lc != '1' && lc != '2' && lc != '3' && lc != '4');
	system("cls");
}
