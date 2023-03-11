#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

#define ZERO 256 // 0
#define TWO 240 // 2
#define FOUR 112 // 4
#define EIGHT 128 // 8
#define SIXTEEN 176 // 16
#define THIRTYTOW 48 // 32
#define SIXTYFOUR 144 // 64
#define HUNDREDTWENTYEIGHT 272 // 128
#define TWOHUNDREDFIFTYSIX 80 // 256
#define FIVEHUNDREDTWELVE 80 // 512
#define THOUSANDTWENTYFOUR 64 // 1024
#define TWOTHOUSANDFORTYEIGHT 64 // 2048

#define ZERO_ 256 // 0 ����
#define TWO_ 255 // 2 ����
#define FOUR_ 119 // 4 ����
#define EIGHT_ 136 // 8 ����
#define SIXTEEN_ 187 // 16 ����
#define THIRTYTOW_ 51 // 32 ����
#define SIXTYFOUR_ 153 // 64 ����
#define HUNDREDTWENTYEIGHT_ 273 // 128 ����
#define TWOHUNDREDFIFTYSIX_ 85 // 256 ����
#define FIVEHUNDREDTWELVE_ 85 // 512 ����
#define THOUSANDTWENTYFOUR_ 68 // 1024 ����
#define TWOTHOUSANDFORTYEIGHT_ 68 // 2048 ����


int screen[16] =
{
 0,0,0,0,
 0,0,0,0,
 0,0,0,0,
 0,0,0,0
};
// 0: �������, 2,4,8,16,....: �� ���ڷ� ����, �Ŀ� ����� �� �״�� ���

int width[4] = { 0,0,0,0 };//�� ������ (���ʺ��� �������) Ȯ�� ����, 0: Ȯ���ؾ���, 1: Ȯ���� �ʿ� ����
int length[4] = { 0,0,0,0 };// �� ������ (���ʺ��� �������) Ȯ�� ����, 0: Ȯ���ؾ���, 1: Ȯ���� �ʿ� ����
int check_appear = 1;//���������� �������� �ʾҴ��� üũ (�������� �� 1, �������� �ʾ��� �� 0 )
int screen_type = 0;//���� ��ҽ� ���� ȭ�� ������ ����, (0: ����, 1: ���ӿ���ȭ��, 2: ����ȭ��, 3: ���� ����)
int continue_num = 0;//�Ͻ����� �� ����ϱ⸦ ���Ͽ��� ��� appear�� �ѹ� �� �ݺ��Ǵ� ��츦 �������� ����

void gotoxy(int x, int y);//Ŀ���̵�(��)
void CursorView(char show);//Ŀ�������(��)
void color(int color_num);//���ڻ� ����(��)
void print_start_screen();//ȭ�����
void active();//��� Ȱ���� �߽�, ���� �����ϴ� �Լ�
void print_screen();//���� screen ���, ��� ����� ���� �ڿ� ����� �� �����
void appear();//�� ����, ������ ��ġ(space), ������ ��(num 1�Ǵ� 2 (Ȧ��, ¦��)) �Է¹ް� ȭ�鿡 ���------2 �Ǵ� 4 ���, �� �Ǵ� �� �ִ� �� ����
void main_screen();//����ȭ���� ���� (���ӽ���, ����, ���α׷� ���� ����)
void main_finish_screen();//����ȭ�鿡�� ������ ��� �ٽù���
void finish_screen();//���� ���θ� �ٽ� ���´�, �׸��� ����, �Ǵ� ���� ȭ������ ���ư���
void end_screen();//��� �۵��� ���߰� ������ ����
void end_stop();//���ӵ��� �Ͻ����� ȭ��, �������� ���ư��� �������� ���´�
void information_screen();//��������, ���� ȭ��


void check_up();//���� ���� Ȯ��, ���
void check_down();//�Ʒ��ΰ��� Ȯ��, ���
void check_left();//���ʰ��� Ȯ��, ���
void check_right();//�����ʰ��� Ȯ��, ���
void move_up(int a);//���� �����̱�
void move_down(int b);//�Ʒ��� �����̱�
void move_left(int c);//�������� �����̱�
void move_right(int d);//���������� �����̱�

int check_end();//���̻� ������ ������ �� �ִ��� üũ(������ �� ������ 1, ������ 0 ��ȯ)

void screen_test();//��ũ�� ���� �׽�Ʈ�ϱ�
void check_bug(); //����ã��(2,4,8...�� ������ �ٸ� ���ڰ� ���ð��)


void wjatn();//������

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show)//Ŀ�������(��)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void color(int color_num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_num);
}

void print_start_screen()
{
	system("mode con cols=80 lines=30");
	color(238);
	for (int i = 0; i <= 30; i++)
	{
		for (int l = 0; l <= 80; l++)
		{
			gotoxy(l, i);
			printf("��");
		}
	}
	
	color(102);
	for (int i = 5; i <= 16; i++)
	{
		for (int l = 10; l <= 32; l = l + 2)
		{
			gotoxy(l, i);
			printf("��");
		}
	}

	color(256);
	for (int i = 7; i <= 14; i++)
	{
		for (int l = 14; l <= 28; l = l + 2)
		{
			gotoxy(l, i);
			printf("��");
		}
	}
	gotoxy(20, 10);
}

void active()
{
	char ch;
	int check_num = 0;

	//end_screen();
	
	while (1)//�� �ű�� �� ����
	{
		if (check_end() == 0)
		{
			//color(232);
			//gotoxy(37, 4);
			//printf("���ӿ���");
			end_screen();
		}

		if (check_num % 2 == 0 && check_appear == 1)
		{
			if (continue_num == 0)
			{
				appear();//�� ������ ��ġ, ���ڷ� ����
				//gotoxy(50, 5);
				//color(232);
				//printf("���ڻ���");

				continue_num = 0;
			}
		}
		//color(232);
		//gotoxy(50, 4);
		//printf("Ȯ��: %d", check_num);//�Լ� �ݺ� Ƚ�� Ȯ��

		//screen_test();//ȭ�� ��� �׽�Ʈ
		print_screen();//ȭ�����

		ch = _getch();
		switch (ch)
		{
		case UP:
			check_up(); break;
		case DOWN:
			check_down(); break;
		case LEFT:
			check_left(); break;
		case RIGHT:
			check_right(); break;
		case ESC:
			end_stop();
		}

		//color(232);
		//gotoxy(50, 5);
		//printf("        ");//���ڻ��� �۾� �����

		//screen_test();//ȭ�� ��� �׽�Ʈ
		print_screen();//ȭ�����

		if (check_end() == 0)
		{
			//color(232);
			//gotoxy(37, 4);
			//printf("���ӿ���");
			end_screen();
		}
		check_num++;
		//check_bug();//���� üũ
		Sleep(100);
	}
}

void print_screen()
{
	for (int fst = 0; fst <= 3; fst++)//1��° �� ���
	{
		switch (screen[fst])//���ھ��� ����
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO_); break;
		case 4:
			color(FOUR_); break;
		case 8:
			color(EIGHT_); break;
		case 16:
			color(SIXTEEN_); break;
		case 32:
			color(THIRTYTOW_); break;
		case 64:
			color(SIXTYFOUR_); break;
		case 128:
			color(HUNDREDTWENTYEIGHT_); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX_); break;
		case 512:
			color(FIVEHUNDREDTWELVE_); break;
		case 1024:
			color(THOUSANDTWENTYFOUR_); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT_); break;
		}
		gotoxy(14 + (fst * 4), 7);
		printf("0000");

		switch (screen[fst])//���� ��
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO); break;
		case 4:
			color(FOUR); break;
		case 8:
			color(EIGHT); break;
		case 16:
			color(SIXTEEN); break;
		case 32:
			color(THIRTYTOW); break;
		case 64:
			color(SIXTYFOUR); break;
		case 128:
			color(HUNDREDTWENTYEIGHT); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX); break;
		case 512:
			color(FIVEHUNDREDTWELVE); break;
		case 1024:
			color(THOUSANDTWENTYFOUR); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT); break;
		}

		if (screen[fst] < 10)//1�ڸ����� ���
		{
			gotoxy(14 + (fst * 4), 8);
			printf("  %d ", screen[fst]);
		}
		else if (screen[fst] < 100)//2�ڸ����� ���
		{
			gotoxy(14 + (fst * 4), 8);
			printf(" %d ", screen[fst]);
		}
		else if (screen[fst] < 1000)//3�ڸ����� ���
		{
			gotoxy(14 + (fst * 4), 8);
			printf(" %d", screen[fst]);
		}
		else if (screen[fst] < 10000)//4�ڸ����� ���
		{
			gotoxy(14 + (fst * 4), 8);
			printf("%d", screen[fst]);
		}
	}

	for (int scd = 0; scd <= 3; scd++)//2��° �� ���
	{
		switch (screen[scd + 4])//���ھ��� ����
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO_); break;
		case 4:
			color(FOUR_); break;
		case 8:
			color(EIGHT_); break;
		case 16:
			color(SIXTEEN_); break;
		case 32:
			color(THIRTYTOW_); break;
		case 64:
			color(SIXTYFOUR_); break;
		case 128:
			color(HUNDREDTWENTYEIGHT_); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX_); break;
		case 512:
			color(FIVEHUNDREDTWELVE_); break;
		case 1024:
			color(THOUSANDTWENTYFOUR_); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT_); break;
		}
		gotoxy(14 + (scd * 4), 9);
		printf("0000");

		switch (screen[scd + 4])//���� ��
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO); break;
		case 4:
			color(FOUR); break;
		case 8:
			color(EIGHT); break;
		case 16:
			color(SIXTEEN); break;
		case 32:
			color(THIRTYTOW); break;
		case 64:
			color(SIXTYFOUR); break;
		case 128:
			color(HUNDREDTWENTYEIGHT); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX); break;
		case 512:
			color(FIVEHUNDREDTWELVE); break;
		case 1024:
			color(THOUSANDTWENTYFOUR); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT); break;
		}

		if (screen[scd + 4] < 10)//1�ڸ����� ���
		{
			gotoxy(14 + (scd * 4), 10);
			printf("  %d ", screen[scd + 4]);
		}
		else if (screen[scd + 4] < 100)//2�ڸ����� ���
		{
			gotoxy(14 + (scd * 4), 10);
			printf(" %d ", screen[scd + 4]);
		}
		else if (screen[scd + 4] < 1000)//3�ڸ����� ���
		{
			gotoxy(14 + (scd * 4), 10);
			printf(" %d", screen[scd + 4]);
		}
		else if (screen[scd + 4] < 10000)//4�ڸ����� ���
		{
			gotoxy(14 + (scd * 4), 10);
			printf("%d", screen[scd + 4]);
		}
	}

	for (int trd = 0; trd <= 3; trd++)//3��° �� ���
	{
		switch (screen[trd + 8])//���ھ��� ����
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO_); break;
		case 4:
			color(FOUR_); break;
		case 8:
			color(EIGHT_); break;
		case 16:
			color(SIXTEEN_); break;
		case 32:
			color(THIRTYTOW_); break;
		case 64:
			color(SIXTYFOUR_); break;
		case 128:
			color(HUNDREDTWENTYEIGHT_); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX_); break;
		case 512:
			color(FIVEHUNDREDTWELVE_); break;
		case 1024:
			color(THOUSANDTWENTYFOUR_); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT_); break;
		}
		gotoxy(14 + (trd * 4), 11);
		printf("0000");

		switch (screen[trd + 8])//���� ��
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO); break;
		case 4:
			color(FOUR); break;
		case 8:
			color(EIGHT); break;
		case 16:
			color(SIXTEEN); break;
		case 32:
			color(THIRTYTOW); break;
		case 64:
			color(SIXTYFOUR); break;
		case 128:
			color(HUNDREDTWENTYEIGHT); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX); break;
		case 512:
			color(FIVEHUNDREDTWELVE); break;
		case 1024:
			color(THOUSANDTWENTYFOUR); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT); break;
		}

		if (screen[trd + 8] < 10)//1�ڸ����� ���
		{
			gotoxy(14 + (trd * 4), 12);
			printf("  %d ", screen[trd + 8]);
		}
		else if (screen[trd + 8] < 100)//2�ڸ����� ���
		{
			gotoxy(14 + (trd * 4), 12);
			printf(" %d ", screen[trd + 8]);
		}
		else if (screen[trd + 8] < 1000)//3�ڸ����� ���
		{
			gotoxy(14 + (trd * 4), 12);
			printf(" %d", screen[trd + 8]);
		}
		else if (screen[trd + 8] < 10000)//4�ڸ����� ���
		{
			gotoxy(14 + (trd * 4), 12);
			printf("%d", screen[trd + 8]);
		}
	}

	for (int fth = 0; fth <= 3; fth++)//4��° �� ���
	{
		switch (screen[fth + 12])//���ھ��� ����
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO_); break;
		case 4:
			color(FOUR_); break;
		case 8:
			color(EIGHT_); break;
		case 16:
			color(SIXTEEN_); break;
		case 32:
			color(THIRTYTOW_); break;
		case 64:
			color(SIXTYFOUR_); break;
		case 128:
			color(HUNDREDTWENTYEIGHT_); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX_); break;
		case 512:
			color(FIVEHUNDREDTWELVE_); break;
		case 1024:
			color(THOUSANDTWENTYFOUR_); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT_); break;
		}
		gotoxy(14 + (fth * 4), 13);
		printf("0000");

		switch (screen[fth + 12])//���� ��
		{
		case 0:
			color(ZERO); break;
		case 2:
			color(TWO); break;
		case 4:
			color(FOUR); break;
		case 8:
			color(EIGHT); break;
		case 16:
			color(SIXTEEN); break;
		case 32:
			color(THIRTYTOW); break;
		case 64:
			color(SIXTYFOUR); break;
		case 128:
			color(HUNDREDTWENTYEIGHT); break;
		case 256:
			color(TWOHUNDREDFIFTYSIX); break;
		case 512:
			color(FIVEHUNDREDTWELVE); break;
		case 1024:
			color(THOUSANDTWENTYFOUR); break;
		case 2048:
			color(TWOTHOUSANDFORTYEIGHT); break;
		}

		if (screen[fth + 12] < 10)//1�ڸ����� ���
		{
			gotoxy(14 + (fth * 4), 14);
			printf("  %d ", screen[fth + 12]);
		}
		else if (screen[fth + 12] < 100)//2�ڸ����� ���
		{
			gotoxy(14 + (fth * 4), 14);
			printf(" %d ", screen[fth + 12]);
		}
		else if (screen[fth + 12] < 1000)//3�ڸ����� ���
		{
			gotoxy(14 + (fth * 4), 14);
			printf(" %d", screen[fth + 12]);
		}
		else if (screen[fth + 12] < 10000)//4�ڸ����� ���
		{
			gotoxy(14 + (fth * 4), 14);
			printf("%d", screen[fth + 12]);
		}
	}


	/*
	int a = 0;
	for (int i = 4; i <= 7; i++)
	{
		for (int l = 8; l <= 14; l = l + 2)
		{
			gotoxy(l, i);
			if (screen[a] == 0)
			{
				color(256);
				printf("��");
			}
			else
			{
				switch (screen[a])
				{
				case 2:
					color(TWO); break;
				case 4:
					color(FOUR); break;
				case 8:
					color(EIGHT); break;
				case 16:
					color(SIXTEEN); break;
				case 32:
					color(THIRTYTOW); break;
				case 64:
					color(SIXTYFOUR); break;
				case 128:
					color(HUNDREDTWENTYEIGHT); break;
				case 256:
					color(TWOHUNDREDFIFTYSIX); break;
				case 1024:
					color(THOUSANDTWENTYFOUR); break;
				case 2048:
					color(TWOTHOUSANDFORTYEIGHT); break;
				}
				if (screen[a] < 10)
				{
					printf("%d ", screen[a]);
				}
				else if (screen[a] >= 10)
				{
					printf("%d", screen[a]);
				}
			}
			a++;
		}
	}*/
}

void appear()//�� ����, ������ ��ġ(space), ������ ��(num 1�Ǵ� 0 (Ȧ��, ¦��) ���� �� ȭ�鿡 ���------2 �Ǵ� 4 ���, �� �Ǵ� �� �ִ� �� ����
{
	srand(time(NULL));
	int space = rand() % 2;//�� ���� ��� ���ϱ�
	int num = rand() % 16;//ȭ���� ������ ��ġ ���ϱ�
	int place = 2;

	if (space == 0)
		place = 2;
	else if (space == 1)
		place = 4;

	while (1)
	{
		if (screen[num] != 0)
		{
			num = rand() % 16;
		}
		else if (screen[num] == 0)
		{
			screen[num] = place;
			break;
		}
	}
}

void main_screen()
{
	char ch_main;
	int main_y = 8;

	color(238);
	for (int i = 0; i <= 30; i++)
	{
		for (int l = 0; l <= 80; l++)
		{
			gotoxy(l, i);
			printf("��");
		}
	}
	color(233);
	gotoxy(30, 4);
	printf("��");
	gotoxy(17, 4);
	printf("��");
	gotoxy(21, 8);
	printf("�� ����");
	color(224);
	gotoxy(21, 4);
	printf("2 0 4 8");
	gotoxy(21, 10);
	printf("����");
	gotoxy(21, 12);
	printf("����");
	color(233);
	gotoxy(18, main_y);
	printf("��");
	color(235);
	gotoxy(16, 16);
	printf("����: [�����̽���]");

	while (1)
	{
		ch_main = _getch();
		switch (ch_main)
		{
		case UP:
		{
			color(224);
			gotoxy(18, main_y);
			printf("  ");
			color(224);
			gotoxy(21, 8);
			printf("�� ����");
			gotoxy(21, 10);
			printf("����");
			gotoxy(21, 12);
			printf("����");
			if (main_y == 8)
				main_y = 12;
			else
				main_y -= 2;
			break;
		}
		case DOWN:
		{
			color(224);
			gotoxy(18, main_y);
			printf("  ");
			color(224);
			gotoxy(21, 8);
			printf("�� ����");
			gotoxy(21, 10);
			printf("����");
			gotoxy(21, 12);
			printf("����");
			if (main_y == 12)
				main_y = 8;
			else
				main_y += 2;
			break;
		}
		case 32:
		{
			if (main_y == 8)//���ӽ���
			{
				print_start_screen();
				active();
			}
			else if (main_y == 10)//��������
			{
				color(238);
				gotoxy(25, 5);
				printf("            ");
				gotoxy(20, 8);
				printf("            ");
				gotoxy(20, 10);
				printf("            ");
				gotoxy(20, 12);
				printf("            ");
				gotoxy(16, 16);
				printf("                      ");
				gotoxy(14, main_y);
				printf("     ");
				information_screen();
			}
			else if (main_y == 12)//����
			{
				color(238);
				gotoxy(20, 5);
				printf("              ");
				gotoxy(16, 8);
				printf("              ");
				gotoxy(16, 10);
				printf("              ");
				gotoxy(16, 12);
				printf("              ");
				gotoxy(16, 16);
				printf("                     ");
				gotoxy(16, main_y);
				printf("  ");
				main_finish_screen();
			}
			break;
		}
		}
		color(233);
		gotoxy(18, main_y);
		printf("��");
		if (main_y == 8)
		{
			gotoxy(21, 8);
			printf("�� ����");
		}
		else if (main_y == 10)
		{
			gotoxy(21, 10);
			printf("����");
		}
		else if (main_y == 12)
		{
			gotoxy(21, 12);
			printf("����");
		}
		//gotoxy(18, 20);
		//printf("%d", main_y);
	}
}

void main_finish_screen()
{
	int main_finish_y = 11;
	char ch_finish;
	color(233);
	gotoxy(18, 11);
	printf("��");
	gotoxy(21, 11);
	printf("��");
	color(224);
	gotoxy(17, 9);
	printf("���� �Ͻðڽ��ϱ�?");
	gotoxy(20, 13);
	printf("�ƴϿ�");

	while (1)
	{
		ch_finish = _getch();

		switch (ch_finish)
		{
		case UP:
		{
			gotoxy(18, main_finish_y);
			printf("  ");
			if (main_finish_y == 11)
				main_finish_y = 13;
			else if (main_finish_y == 13)
				main_finish_y = 11;
			break;
		}
		case DOWN:
		{
			gotoxy(18, main_finish_y);
			printf("  ");
			if (main_finish_y == 11)
				main_finish_y = 13;
			else if (main_finish_y == 13)
				main_finish_y = 11;
			break;
		}
		case 32:
		{
			if (main_finish_y == 11)
			{
				exit(0);
			}
			else if (main_finish_y == 13)
			{
				main_screen();
			}
		}
		}
		color(233);
		gotoxy(18, main_finish_y);
		printf("��");
		if (main_finish_y == 11)
		{
			gotoxy(21, 11);
			printf("��");
			color(224);
			gotoxy(20, 13);
			printf("�ƴϿ�");
		}
		else if (main_finish_y == 13)
		{
			gotoxy(20, 13);
			printf("�ƴϿ�");
			color(224);
			gotoxy(21, 11);
			printf("��");
		}
	}
}

void finish_screen()
{
	int finish_y = 11;
	char ch_finish;
	color(233);
	gotoxy(43, 11);
	printf("��");
	gotoxy(55, 11);
	printf("��");
	gotoxy(43, 9);
	printf("���� �Ͻðڽ��ϱ�?");
	gotoxy(48, 11);
	printf("��");
	gotoxy(47, 13);
	printf("�ƴϿ�");

	while (1)
	{
		ch_finish = _getch();

		switch (ch_finish)
		{
		case UP:
		{
			gotoxy(43, finish_y);
			printf("  ");
			gotoxy(55, finish_y);
			printf("  ");
			if (finish_y == 11)
				finish_y = 13;
			else if (finish_y == 13)
				finish_y = 11;
			break;
		}
		case DOWN:
		{
			gotoxy(43, finish_y);
			printf("  ");
			gotoxy(55, finish_y);
			printf("  ");
			if (finish_y == 11)
				finish_y = 13;
			else if (finish_y == 13)
				finish_y = 11;
			break;
		}
		case 32:
		{
			if (finish_y == 11)
			{
				exit(0);
			}
			else if (finish_y == 13)
			{
				if (screen_type == 0)// ����
				{

				}
				else if (screen_type == 1)// ���ӿ���ȭ��
				{
					screen_type = 0;
					color(238);
					gotoxy(38, 9);
					printf("                          ");
					gotoxy(38, 11);
					printf("                          ");
					gotoxy(38, 13);
					printf("                          ");
					end_screen();
				}
				else if (screen_type == 2)//����ȭ��
				{

				}
				else if (screen_type == 3)//���ӵ���
				{

				}
			}
		}
		}
		color(233);
		gotoxy(43, finish_y);
		printf("��");
		gotoxy(55, finish_y);
		printf("��");
	}
}

void end_screen()
{
	int arrow_y = 10;
	char ch_end;

	color(233);
	gotoxy(42, 10);
	printf("��");
	gotoxy(56, 10);
	printf("��");
	gotoxy(46, 10);
	printf("�ٽ��ϱ�");
	gotoxy(46, 12);
	printf("����ȭ��");
	gotoxy(46, 14);
	printf("��������");
	color(235);
	gotoxy(42, 16);
	printf("����: [�����̽���]");
	while (1)
	{
		color(225);
		gotoxy(38, 6);
		printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�");
		gotoxy(38, 7);
		printf("�� �ǣ��ͣ�  �ϣ֣ţ� ��");
		gotoxy(38, 8);
		printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�");
		Sleep(30);
		gotoxy(38, 6);
		printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١�");
		gotoxy(38, 7);
		printf("�� �ǣ��ͣ�  �ϣ֣ţ� ��");
		gotoxy(38, 8);
		printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١�");
		Sleep(30);
		if (_kbhit())
		{
			ch_end = _getch();
			switch (ch_end)
			{
			case UP:
			{
				gotoxy(42, arrow_y);
				printf("  ");
				gotoxy(56, arrow_y);
				printf("  ");
				if (arrow_y == 10)
					arrow_y = 14;
				else
					arrow_y -= 2;
				break;
			}
			case DOWN:
			{
				gotoxy(42, arrow_y);
				printf("  ");
				gotoxy(56, arrow_y);
				printf("  ");
				if (arrow_y == 14)
					arrow_y = 10;
				else
					arrow_y += 2;
				break;
			}
			case 32:
			{
				if (arrow_y == 10)//�ٽ��ϱ�
				{
					color(238);
					gotoxy(38, 6);
					printf("                          ");
					gotoxy(38, 7);
					printf("                          ");
					gotoxy(38, 8);
					printf("                          ");
					gotoxy(38, 9);
					printf("                          ");
					gotoxy(38, 10);
					printf("                          ");
					gotoxy(38, 12);
					printf("                          ");
					gotoxy(38, 14);
					printf("                          ");
					gotoxy(38, 16);
					printf("                          ");
					for (int q = 0; q <= 15; q++)
					{
						screen[q] = 0;
					}
					active();
				}
				else if (arrow_y == 12)//����ȭ��
				{

				}
				else if (arrow_y == 14)//��������
				{
					screen_type = 1;
					color(238);
					gotoxy(38, 6);
					printf("                          ");
					gotoxy(38, 7);
					printf("                          ");
					gotoxy(38, 8);
					printf("                          ");
					gotoxy(38, 9);
					printf("                          ");
					gotoxy(38, 10);
					printf("                          ");
					gotoxy(38, 12);
					printf("                          ");
					gotoxy(38, 14);
					printf("                          ");
					gotoxy(38, 16);
					printf("                          ");
					finish_screen();
				}
				break;
			}
			}
		}
		color(233);
		gotoxy(42, arrow_y);
		printf("��");
		gotoxy(56, arrow_y);
		printf("��");
		//gotoxy(40, 3);
		//printf("%d", arrow_y);
	}
}

void end_stop()//���ӵ��� �Ͻ����� ȭ��, �������� ���ư��� �������� ���´�
{
	int arrow_y = 10;
	char ch_end;

	color(233);
	gotoxy(42, 10);
	printf("��");
	gotoxy(56, 10);
	printf("��");
	gotoxy(46, 10);
	printf("����ϱ�");
	gotoxy(46, 12);
	printf("�ٽ��ϱ�");
	gotoxy(46, 14);
	printf("��������");
	color(235);
	gotoxy(42, 16);
	printf("����: [�����̽���]");
	while (1)
	{
		if (_kbhit())
		{
			ch_end = _getch();
			switch (ch_end)
			{
			case UP:
			{
				gotoxy(42, arrow_y);
				printf("  ");
				gotoxy(56, arrow_y);
				printf("  ");
				if (arrow_y == 10)
					arrow_y = 14;
				else
					arrow_y -= 2;
				break;
			}
			case DOWN:
			{
				gotoxy(42, arrow_y);
				printf("  ");
				gotoxy(56, arrow_y);
				printf("  ");
				if (arrow_y == 14)
					arrow_y = 10;
				else
					arrow_y += 2;
				break;
			}
			case 32:
			{
				if (arrow_y == 10)//����ϱ�
				{
					color(238);
					gotoxy(38, 6);
					printf("                          ");
					gotoxy(38, 7);
					printf("                          ");
					gotoxy(38, 8);
					printf("                          ");
					gotoxy(38, 9);
					printf("                          ");
					gotoxy(38, 10);
					printf("                          ");
					gotoxy(38, 12);
					printf("                          ");
					gotoxy(38, 14);
					printf("                          ");
					gotoxy(38, 16);
					printf("                          ");
					continue_num = 1;
					active();
				}
				else if (arrow_y == 12)//�ٽ��ϱ�
				{
					color(238);
					gotoxy(38, 6);
					printf("                          ");
					gotoxy(38, 7);
					printf("                          ");
					gotoxy(38, 8);
					printf("                          ");
					gotoxy(38, 9);
					printf("                          ");
					gotoxy(38, 10);
					printf("                          ");
					gotoxy(38, 12);
					printf("                          ");
					gotoxy(38, 14);
					printf("                          ");
					gotoxy(38, 16);
					printf("                          ");
					for (int q = 0; q <= 15; q++)
					{
						screen[q] = 0;
					}
					continue_num = 0;
					active();
				}
				else if (arrow_y == 14)//��������
				{
					screen_type = 1;
					color(238);
					gotoxy(38, 6);
					printf("                          ");
					gotoxy(38, 7);
					printf("                          ");
					gotoxy(38, 8);
					printf("                          ");
					gotoxy(38, 9);
					printf("                          ");
					gotoxy(38, 10);
					printf("                          ");
					gotoxy(38, 12);
					printf("                          ");
					gotoxy(38, 14);
					printf("                          ");
					gotoxy(38, 16);
					printf("                          ");
					finish_screen();
				}
				break;
			}
			}
		}
		color(233);
		gotoxy(42, arrow_y);
		printf("��");
		gotoxy(56, arrow_y);
		printf("��");
	}
}

void information_screen()
{
	color(224);
	gotoxy(18, 7);
	printf("��ǿ� ����");
	Sleep(10);
	gotoxy(18, 10);
	printf("����Ű (");
	color(235);
	printf("��,��,��, ��");
	color(224);
	printf("): ");
	color(233);
	printf("���̵�");
	Sleep(10);
	gotoxy(18, 12);
	color(224);
	printf("ESC: ");
	color(233);
	printf("�Ͻ����� & ����");
	Sleep(10);
	gotoxy(18, 14);
	color(224);
	printf("SPACEBAR");
	color(233);
	printf(": ����");
	color(233);
	gotoxy(14, 10);
	printf("��");
	gotoxy(14, 12);
	printf("��");
	gotoxy(14, 14);
	printf("��");

	gotoxy(8, 21);
	color(235);
	printf("�� ������ 2048�� ��Ģ�� �״�� �����ϴ�.");
	gotoxy(8, 23);
	printf("������ ã�Ұų� �߰��ϰ� ���� ����� �ִٸ�");
	color(233);
	gotoxy(8, 24);
	printf("fantaandgom@gmail.com");
	color(235);
	printf("���� ���� ��Ź�帳�ϴ�.");

	color(224);
	gotoxy(16, 17);
	printf("����ȭ������ ���ư���");

	int arrow_y = 13;
	char ch_information;
	color(233);
	gotoxy(12, 17);
	printf("��");
	gotoxy(39, 17);
	printf("��");

	while (1)
	{
		if (_kbhit())
		{
			ch_information = _getch();
			if (ch_information == 32)
				main_screen();
		}
	}
}


void check_up()
{
	move_up(0);
	move_up(1);
	move_up(2);
	move_up(3);

	int re_a = 0;//��� �� ���� ��찡 12�� �̻��� ���(=���̻� ��� �� �ִ� ĭ�� ���� ���) ī��Ʈ�ϱ� ���� ����

	while (1)//���̻� ��� �� ���� �� ���� �ݺ��ϱ� ����
	{
		for (int i = 0; i <= 11; i++)
		{
			if (screen[i] == 0 && screen[i + 4] != 0)//ĭ�� ������� �� ��ĭ ����
			{
				screen[i] = screen[i + 4];
				screen[i + 4] = 0;
				check_appear = 1;
			}
			else//��� �� ���� ��찡 ���� ��� re ī��Ʈ
			{
				re_a++;
			}
		}
		if (re_a >= 12)//���̻� ��� �� ������ Ȯ��
		{
			break;
		}
		re_a = 0;
	}

	/*/
	for (int i = 0; i <= 3; i++)//������ ��� ���� ��� (Ư���� ���)
	{
		if (screen[i] == screen[i + 4] == screen[i + 8] == screen[i + 12])
		{
			screen[i] += screen[i];
			screen[i + 4] += screen[i];
			screen[i + 8] = 0;
			screen[i + 12] = 0;
		}
	}

	if (screen[4] == screen[8])//----- 2,3 �� ���� Ȯ�� �� ������ ��� �ٸ� �࿡�� ��ĥ ����� �� ����
	{
		screen[4] += screen[8];
		screen[8] = screen[12];
		width[0] = 1;
	}
	else if (screen[5] == screen[9])
	{
		screen[5] += screen[9];
		screen[9] = screen[13];
		width[1] = 1;
	}
	else if (screen[6] == screen[10])
	{
		screen[6] += screen[10];
		screen[10] = screen[14];
		width[2] = 1;
	}
	else if (screen[7] == screen[11])
	{
		screen[7] += screen[11];
		screen[11] = screen[15];
		width[3] = 1;
	}


	if (screen[8] == screen[12] && width[0] == 0)//-----  3~4�� Ȯ�� �� ���� ����
	{
		screen[8] += screen[12];
		screen[12] = 0;
	}
	else if (screen[9] == screen[13] && width[1] == 0)
	{
		screen[9] += screen[13];
		screen[13] = 0;
	}
	else if (screen[10] == screen[14] && width[2] == 0)
	{
		screen[10] += screen[14];
		screen[14] = 0;
	}
	else if (screen[11] == screen[15] && width[3] == 0)
	{
		screen[11] += screen[15];
		screen[15] = 0;
	}


	if (screen[0] == screen[4] && width[0] == 0)//-----  1~2�� Ȯ�� �� ���� ����
	{
		screen[0] += screen[4];
		screen[4] = screen[8];
		screen[8] = screen[12];
		screen[12] = 0;
	}
	else if (screen[1] == screen[5] && width[1] == 0)
	{
		screen[1] += screen[5];
		screen[5] = screen[9];
		screen[9] = screen[13];
		screen[13] = 0;
	}
	else if (screen[2] == screen[6] && width[2] == 0)
	{
		screen[2] += screen[6];
		screen[6] = screen[10];
		screen[10] = screen[14];
		screen[14] = 0;
	}
	else if (screen[3] == screen[7] && width[3] == 0)
	{
		screen[3] += screen[7];
		screen[7] = screen[11];
		screen[11] = screen[15];
		screen[15] = 0;
	}

	width[0] = 0;//�� �� Ȯ�ο��� �ʱ�ȭ
	width[1] = 0;
	width[2] = 0;
	width[3] = 0;
	*/
	//������
}

void check_down()
{
	move_down(0);
	move_down(1);
	move_down(2);
	move_down(3);

	int re_b = 0;//��� �� ���� ��찡 12�� �̻��� ���(=���̻� ��� �� �ִ� ĭ�� ���� ���) ī��Ʈ�ϱ� ���� ����

	while (1)//���̻� ��� �� ���� �� ���� �ݺ��ϱ� ����
	{
		for (int i = 0; i <= 11; i++)
		{
			if (screen[i + 4] == 0 && screen[i] != 0)//ĭ�� ������� �� ��ĭ ����
			{
				screen[i + 4] = screen[i];
				screen[i] = 0;
				check_appear = 1;
			}
			else//��� �� ���� ��찡 ���� ��� re ī��Ʈ
			{
				re_b++;
			}
		}
		if (re_b >= 12)//���̻� ��� �� ������ Ȯ��
		{
			break;
		}
		re_b = 0;
	}
}

void check_left()
{
	move_left(0);
	move_left(4);
	move_left(8);
	move_left(12);

	int re_c = 0;//��� �� ���� ��찡 12�� �̻��� ���(=���̻� ��� �� �ִ� ĭ�� ���� ���) ī��Ʈ�ϱ� ���� ����

	while (1)//���̻� ��� �� ���� �� ���� �ݺ��ϱ� ����
	{
		for (int i = 0; i <= 15; i++)
		{
			if (i != 3 && i != 7 && i != 11 && i != 15)
			{
				if (screen[i] == 0 && screen[i + 1] != 0)//ĭ�� ������� �� ��ĭ ����
				{
					screen[i] = screen[i + 1];
					screen[i + 1] = 0;
					check_appear = 1;
				}
				else//��� �� ���� ��찡 ���� ��� re ī��Ʈ
				{
					re_c++;
				}
			}
		}
		if (re_c >= 12)//���̻� ��� �� ������ Ȯ��
		{
			break;
		}
		re_c = 0;
	}
}

void check_right()
{
	move_right(0);
	move_right(4);
	move_right(8);
	move_right(12);

	int re_d = 0;//��� �� ���� ��찡 12�� �̻��� ���(=���̻� ��� �� �ִ� ĭ�� ���� ���) ī��Ʈ�ϱ� ���� ����

	while (1)//���̻� ��� �� ���� �� ���� �ݺ��ϱ� ����
	{
		for (int i = 0; i <= 15; i++)
		{
			if (i != 3 && i != 7 && i != 11 && i != 15)
			{
				if (screen[i + 1] == 0 && screen[i] != 0)//ĭ�� ������� �� ��ĭ ����
				{
					screen[i + 1] = screen[i];
					screen[i] = 0;
					check_appear = 1;
				}
				else//��� �� ���� ��찡 ���� ��� re ī��Ʈ
				{
					re_d++;
				}
			}
		}
		if (re_d >= 12)//���̻� ��� �� ������ Ȯ��
		{
			break;
		}
		re_d = 0;
	}
}

//-------------------------------------------------------------------------�߰� ���� �� ��ġ�� ��� ���� �����ϱ�--------
void move_up(int a)//���� �����̱�
{
	if (screen[a] == screen[a + 4] && screen[a] == screen[a + 8] && screen[a] == screen[a + 12])//���� ���� ���
	{
		if (screen[a] != 0 && screen[a + 12])
		{
			screen[a] += screen[a + 4];
			screen[a + 4] = 0;
			screen[a + 8] += screen[a + 12];
			screen[a + 12] = 0;
			check_appear = 1;
		}
	}
	else if (screen[a] == screen[a + 4])//1~2�� �������
	{
		screen[a] += screen[a + 4];
		screen[a + 4] = 0;
		check_appear = 1;
		
		if (screen[a + 8] == screen[a + 12])//3~4�� �������
		{
			screen[a + 8] += screen[a + 12];
			screen[a + 12] = 0;
			check_appear = 1;
		}
	}
	else if (screen[a + 8] == screen[a + 12])//3~4�� �������
	{
		screen[a + 8] += screen[a + 12];
		screen[a + 12] = 0;
		check_appear = 1;
	}
	else if (screen[a + 4] == screen[a + 8])//2~3�� �������
	{
		screen[a + 4] += screen[a + 8];
		screen[a + 8] = 0;
		check_appear = 1;
	}
	else if (screen[a + 4] == 0 && screen[a + 8] == 0)//2,3�� ����ְ� 1,4�� �������
	{
		if (screen[a] == screen[a + 12])
		{
			screen[a] += screen[a + 12];
			screen[a + 12] = 0;
			check_appear = 1;
		}
	}
	else if (screen[a + 4] == 0 && screen[a] == screen[a + 8])//2�� ����ְ� 1,3�� �������
	{
		screen[a] += screen[a + 8];
		screen[a + 8] = 0;
		check_appear = 1;
	}
	else if (screen[a + 8] == 0 && screen[a + 4] == screen[a + 12])//3�� ����ְ� 2,4�� �������
	{
		screen[a + 4] += screen[a + 12];
		screen[a + 12] = 0;
		check_appear = 1;
	}
	else//�������� �ʾ��� ��
	{
		check_appear = 0;
	}
}

void move_down(int b)//�Ʒ��� �����̱�
{
	if (screen[b] == screen[b + 4] && screen[b] == screen[b + 8] && screen[b] == screen[b + 12])//���� ���� ���
	{
		if (screen[b] != 0 && screen[b + 12] != 0)
		{
			screen[b + 4] += screen[b];
			screen[b] = 0;
			screen[b + 12] += screen[b + 8];
			screen[b + 8] = 0;
			check_appear = 1;
		}
	}
	else if (screen[b + 8] == screen[b + 12])//3~4�� �������
	{
		screen[b + 12] += screen[b + 8];
		screen[b + 8] = 0;
		check_appear = 1;

		if (screen[b] == screen[b + 4])//1~2�� �������
		{
			screen[b + 4] += screen[b];
			screen[b] = 0;
			check_appear = 1;
		}
	}
	else if (screen[b] == screen[b + 4])//1~2�� �������
	{
		screen[b + 4] += screen[b];
		screen[b] = 0;
		check_appear = 1;
	}
	else if (screen[b + 4] == screen[b + 8])//2~3�� �������
	{
		screen[b + 8] += screen[b + 4];
		screen[b + 4] = 0;
		check_appear = 1;
	}
	else if (screen[b] == screen[b + 12])//2,3�� ����ְ� 1,4�� �������
	{
		if (screen[b + 4] == 0 && screen[b + 8] == 0)
		{
			screen[b + 12] += screen[b];
			screen[b] = 0;
			check_appear = 1;
		}
	}
	else if (screen[b + 4] == 0 && screen[b] == screen[b + 8])//2�� ����ְ� 1,3�� �������
	{
		screen[b + 8] += screen[b];
		screen[b] = 0;
		check_appear = 1;
	}
	else if (screen[b + 8] == 0 && screen[b + 4] == screen[b + 12])//3�� ����ְ� 2,4�� �������
	{
		screen[b + 12] += screen[b + 4];
		screen[b + 4] = 0;
		check_appear = 1;
	}
	else//�������� �ʾ��� ��
	{
		check_appear = 0;
	}
}

void move_left(int c)//�������� �����̱�
{
	if (screen[c] == screen[c + 1] && screen[c] == screen[c + 2] && screen[c] == screen[c + 3])//���� ���� ���
	{
		if (screen[c] != 0 && screen[c + 3] != 0)
		{
			screen[c] += screen[c + 1];
			screen[c + 1] = 0;
			screen[c + 2] += screen[c + 3];
			screen[c + 3] = 0;
			check_appear = 1;
		}
	}
	else if (screen[c] == screen[c + 1])//1~2�� �������
	{
		screen[c] += screen[c + 1];
		screen[c + 1] = 0;
		check_appear = 1;

		if (screen[c + 2] == screen[c + 3])//3~4�� �������
		{
			screen[c + 2] += screen[c + 3];
			screen[c + 3] = 0;
			check_appear = 1;
		}
	}
	else if (screen[c + 2] == screen[c + 3])//3~4�� �������
	{
		screen[c + 2] += screen[c + 3];
		screen[c + 3] = 0;
		check_appear = 1;
	}
	else if (screen[c + 1] == screen[c + 2])//2~3�� �������
	{
		screen[c + 1] += screen[c + 2];
		screen[c + 2] = 0;
		check_appear = 1;
	}
	else if (screen[c + 1] == 0 && screen[c + 2] == 0)//2,3�� ����ְ� 1,4�� �������
	{
		if (screen[c] == screen[c + 3])
		{
			screen[c] += screen[c + 3];
			screen[c + 3] = 0;
			check_appear = 1;
		}
	}
	else if (screen[c + 1] == 0 && screen[c] == screen[c + 2])//2�� ����ְ� 1,3�� �������
	{
		screen[c] += screen[c + 2];
		screen[c + 2] = 0;
		check_appear = 1;
	}
	else if (screen[c + 2] == 0 && screen[c + 1] == screen[c + 3])//3�� ����ְ� 2,4�� �������
	{
		screen[c + 1] += screen[c + 3];
		screen[c + 3] = 0;
		check_appear = 1;
	}
	else//�������� �ʾ��� ��
	{
		check_appear = 0;
	}
}

void move_right(int d)//���������� �����̱�
{
	if (screen[d] == screen[d + 1] && screen[d] == screen[d + 2] && screen[d] == screen[d + 3])//���� ���� ���
	{
		if (screen[d] != 0 && screen[d + 3] != 0)
		{
			screen[d + 1] += screen[d];
			screen[d] = 0;
			screen[d + 3] += screen[d + 2];
			screen[d + 2] = 0;
			check_appear = 1;
		}
	}
	if (screen[d + 2] == screen[d + 3])//3~4�� �������
	{
		screen[d + 3] += screen[d + 2];
		screen[d + 2] = 0;
		check_appear = 1;
	}
	else if (screen[d] == screen[d + 1])//1~2�� �������
	{
		screen[d + 1] += screen[d];
		screen[d] = 0;
		check_appear = 1;

		if (screen[d + 2] == screen[d + 3])//3~4�� �������
		{
			screen[d + 3] += screen[d + 2];
			screen[d + 2] = 0;
			check_appear = 1;
		}
	}
	else if (screen[d + 1] == screen[d + 2])//2~3�� �������
	{
		screen[d + 2] += screen[d + 1];
		screen[d + 1] = 0;
		check_appear = 1;
	}
	else if (screen[d + 1] == 0 && screen[d + 2] == 0)//2,3�� ����ְ� 1,4�� �������
	{
		if (screen[d] == screen[d + 3])
		{
			screen[d + 3] += screen[d];
			screen[d] = 0;
			check_appear = 1;
		}
	}
	else if (screen[d + 1] == 0 && screen[d] == screen[d + 2])//2�� ����ְ� 1,3�� �������
	{
		screen[d + 2] += screen[d];
		screen[d] = 0;
		check_appear = 1;
	}
	else if (screen[d + 2] == 0 && screen[d + 1] == screen[d + 3])//3�� ����ְ� 2,4�� �������
	{
		screen[d + 3] += screen[d + 1];
		screen[d + 1] = 0;
		check_appear = 1;
	}
	else//�������� �ʾ��� ��
	{
	check_appear = 0;
	}
}

int check_end()
{
	for (int i = 0; i <= 15; i++)
	{
		if (screen[i] == 0)
			return 1;
	}

	for (int a = 0; a <= 14; a++)
	{
		if (a != 3 && a != 7 && a != 11)
		{
			if (screen[a] == screen[a + 1])
				return 1;
		}
	}

	for (int b = 0; b <= 11; b++)
	{
		if (screen[b] == screen[b + 4])
			return 1;
	}

	return 0;

	/*
	int end_count = 0;//��ĥ �� ���� ��� ī��Ʈ
	for (int i = 0; i <= 14; i++)
	{
		if (screen[i] != screen[i + 1] && i != 3 && i != 7 && i != 11)
			end_count++;
		else if (screen[i] == screen[i + 1])
			return 1;//������ �� ����
	}
	
	for (int l = 0; l <= 11; l++)
	{
		if (screen[l] != screen[l + 4])
			end_count++;
		else if (screen[l] == screen[l + 4])
			return 1;//������ �� ����
	}

	if (end_count >= 24)
		return 0;
		*/
}



int main()
{
	CursorView(0);
	print_start_screen();
	main_screen();
}




void screen_test()
{
	gotoxy(1, 1);
	printf("%d	%d	%d	%d\n", screen[0], screen[1], screen[2], screen[3]);
	printf("%d	%d	%d	%d\n", screen[4], screen[5], screen[6], screen[7]);
	printf("%d	%d	%d	%d\n", screen[8], screen[9], screen[10], screen[11]);
	printf("%d	%d	%d	%d\n", screen[12], screen[13], screen[14], screen[15]);
}

void check_bug()
{
	int bug = 1;//���� ���� ��� 1, ������� 0
	color(232);

	for (int n = 0; n <= 15; n++)
	{
		bug = 1;
		switch (screen[n])
		{
		case 0:
			bug = 0; break;
		case 2:
			bug = 0; break;
		case 4:
			bug = 0; break;
		case 8:
			bug = 0; break;
		case 16:
			bug = 0; break;
		case 32:
			bug = 0; break;
		case 64:
			bug = 0; break;
		case 128:
			bug = 0; break;
		case 256:
			bug = 0; break;
		case 512:
			bug = 0; break;
		case 1024:
			bug = 0; break;
		case 2048:
			bug = 0; break;
		}

		if (bug == 1)
		{
			gotoxy(50, 6 + n);
			printf("screen[%d] ����", n);
		}
		else if (bug == 0)
		{
			gotoxy(50, 6 + n);
			printf("screen[%d} ����", n);
		}
	}
}