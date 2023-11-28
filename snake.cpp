#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

string UMainMenu[6] = {"", "Start Playing", "Ranking List", "Quit The Game"};
string SMainMenu[6] = {"", "> Start Playing <", "> Ranking List <", "> Quit The Game <"};

struct Player
{
	string Name;
	int Score;
	bool operator < (const Player &t) const
	{
		return Score > t.Score;
	}
};vector<Player> Rank;
struct Map
{
	char Ch;
	int Type;
	/*0 = null 1 = wall 2 = blue @ 1pt 3 = purple @ 2pt 4 = yellow @ 3pt*/
	/*5 = green # snake Head 6 = green * snake Body*/
}M[20][20];
struct Location
{
	int x, y;
}Head, Tail;

int Current_Score = 0;

int GetTm();
char GetKb();
void SetColor(int fore, int back);
void Print_RankList();
void Start(int opt);
void Print_Menu(int pt);
void Init_GUI();
void Back_To_Menu();
void Game();
void Print_Map();
void Init_Map();
bool Check(int x, int y);

int GetTm() {return clock() / CLOCKS_PER_SEC; }

char GetKb() {return char(_getch());}

void SetColor(int fore, int back)
{
	unsigned char color = fore + (back << 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Back_To_Menu()
{
	while(true)
	{
		char opt = GetKb();
		if(opt != 'q') opt = GetKb();
		else break;
	}
	Init_GUI();
}

void Print_RankList()
{
	system("CLS");
	int len = Rank.size();
	SetColor(14, 0);
	printf("     ----------------\n"
		   "     |  High Score  |\n"
		   "     ----------------\n\n");
	if(len == 0)
	{
	    SetColor(12, 0);
		printf("There is currently no record!\n");
	}
	else
	{
		sort(Rank.begin(), Rank.end());
		for(int i = 0; i < len; i++)
		{
			i <= 2 ? SetColor(12, 0) : SetColor(15, 0);
			printf("Name: %s      Score: %d", Rank[i].Name.c_str(), Rank[i].Score);
			SetColor(15, 0); printf("\n");
		}
	}
	printf("\nPress 'q' to go back.\n");
	Back_To_Menu();
}

void Start(int opt)
{
	if(opt == 1) Game(); 
	if(opt == 2) Print_RankList();
	if(opt == 3) exit(0);
}

void Print_Menu(int pt) 
{
	system("CLS");
	SetColor(14, 0);
	printf("     ---------------------\n"
	       "     |     Snake FoP     |\n"
	       "     |  Design By: ZiHe  |\n"
	       "     ---------------------\n\n"
	);
	SetColor(11, 0); 
	printf("Press 'w' or 's' to move up or down.\n"
		   "Press 'c' to confirm.\n\n");
	SetColor(15, 0);
	for(int i = 1; i <= 3; i++) 
	{
		printf("%d. ", i);
		i != pt ? SetColor(15, 0) : SetColor(0, 15);
		printf("%s", i == pt ? SMainMenu[i].c_str() : UMainMenu[i].c_str());
		SetColor(15, 0); printf("\n");
	}
}

void Init_GUI()
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	
	int pt = 1;
	Print_Menu(pt); 
	while(true)
	{
		char opt = GetKb();
		if(opt == 'w') pt = max(1, pt - 1), Print_Menu(pt);
		if(opt == 's') pt = min(3, pt + 1), Print_Menu(pt);
		if(opt == 'c') Start(pt);
	}
}
void Init_Map()
{
	for(int i = 1; i <= 17; i++) for(int j = 1; j <= 17; j++) M[i][j].Ch = ' ', M[i][j].Type = 0;
	for(int j = 1; j <= 17; j++)
	{
		M[1][j].Ch = M[17][j].Ch = '-';
		M[1][j].Type = M[17][j].Type = 1;
	}
	for(int i = 2; i <= 16; i++)
	{
		M[i][1].Ch = M[i][17].Ch = '|';
		M[i][1].Type = M[i][17].Type = 1;
	}
	Head.x = 8, Head.y = 8, Tail.x =8, Tail.y = 5;
	M[8][7].Ch = M[8][6].Ch = M[8][5].Ch = '*';
	M[8][7].Type = M[8][6].Type = M[8][5].Type = 6;
	M[8][8].Ch = '#'; M[8][8].Type = 5;
}

void Print_Map(int opt)
{
	system("CLS");
	for(int i = 1; i <= 17; i++)
	{
		for(int j = 1; j <= 17; j++)
		{
			if(M[i][j].Type <= 1) SetColor(15, 0);
			if(M[i][j].Type == 2) SetColor(15, 1);
			if(M[i][j].Type == 3) SetColor(15, 5);
			if(M[i][j].Type == 4) SetColor(15, 6);
			if(M[i][j].Type >= 5 && opt == 0) SetColor(15, 10);
			if(M[i][j].Type >= 5 && opt == 1) SetColor(15, 4);
			printf("%c", M[i][j]);
		}
		if(i == 1)
		{
			SetColor(11, 0);
		    printf("     Current Score: %d", Current_Score);
		    SetColor(15, 0);
		}
		if(i == 3) 
		{
			SetColor(12, 0);
		    printf("     Press Space To Pause");
		    SetColor(15, 0);
		}
		printf("\n");
	}
}

bool Check(int x, int y)
{
	if(x == 1 || y == 1) return false;
	return true;
}

Location Get_Tail(int x, int y)
{
		
}

void Game()
{
	Init_Map();
	Print_Map(0);
	Current_Score = 0;
	int PT = GetTm();
	while(true)
	{
		int opt = GetKb();
		int CT = GetTm();
		if(CT != PT)
		{
			int x = Head.x, y = Head.y;
			if(opt == 'w')
			{
				x--;
				if(!check(x, y)) 
				{
					Print_Map(1);
					break;
				}
				M[Head.x][Head.y].Ch = '*', M[Head.x][Head.y].Type = 5;
				
			}
		}
		PT = CT;
	}
}

int main()
{

	Init_GUI();
	return 0;
}

