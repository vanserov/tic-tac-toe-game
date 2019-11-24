#include "pch.h"
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;
int check(int num)
{
	if ((num == 1) || (num == 0))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int checknum(int kol)
{
	if ((kol > 2) && (kol < 20))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
class Game
{
public:
	void Masssiv(char **mass, int str, int stlb, int kol)
	{
		stroka = str;
		stolb = stlb;
		kol1 = kol;
		massiv = new char*[str];
		for (int i = 0; i < str; i++)
		{
			massiv[i] = new char[stlb];
		}
		mass1 = new string*[kol];
		for (int i = 0; i < kol; i++)
		{
			mass1[i] = new string[kol];
		}
		mass2 = new string*[kol];
		for (int i = 0; i < kol; i++)
		{
			mass2[i] = new string[kol];
		}
		for (int i = 0; i < str; i++)
		{
			for (int j = 0; j < stlb; j++)
			{
				massiv[i][j] = mass[i][j];
			}
		}
	}
	void RealTime()
	{
		system("cls");
		for (int i = 1; i <= stroka; i++)
		{
			for (int j = 1; j <= stolb; j++)
			{
				cout << "|" << "-" << i - 1 << j - 1 << "-" << "|";
			}
			cout << endl;
		}
		cout << endl << endl;
		cout << "Realtime situation" << endl;
		for (int i = 0; i < stroka; i++)
		{
			for (int j = 0; j < stolb; j++)
			{
				cout << "|" << "-" << massiv[i][j] << "-" << "|";
			}
			cout << endl;
		}
	}
	void Delete()
	{
		for (int i = 0; i < stroka; i++)
		{
			delete[] massiv[i];
		}
		for (int i = 0; i < kol1; i++)
		{
			delete[] mass1[i];
		}
		for (int i = 0; i < kol1; i++)
		{
			delete[] mass2[i];
		}

	}
	string victorycheck(char sym)
	{
				if ((checkdiaog(sym) == true) || (checkLine(sym) == true))
				{
					if (sym == 'X')
					{
						return "First win";
					}
					if (sym == '0')
					{
						return "Second win";
					}
				}
				int k = 0;
				for (int i = 0; i < stroka; i++)
				{
					for (int j = 0; j < stolb; j++)
					{
						if (massiv[i][j] != '.')
						{
							if (k == stroka * stolb)
							{
								return "tie";
							}
							k++;
						}
					}
				}
	}
	bool checkdiaog(char sym)
	{
		int t = 0;
		int r = 0;
		for (int k = 0; k < kol1; k++)
		{
			if (massiv[k][k] == sym) 
			{
				t++;
			}
			if (massiv[kol1 - k - 1][k] == sym)
			{
				r++;
			}
		}
		if (t == kol1)
		{
			return true;
		}
		else if (r == kol1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool checkLine(char sym)
	{
		int t;
		int r;
			for (int k = 0; k < kol1 /*+ i*/; k++)
			{
				t = 0;
				r = 0;
				for (int s = 0; s < kol1 /*+ j*/; s++)
				{
					if (massiv[k][s] == sym)
					{
						t++;
						if (t == kol1)
						{
							return true;
						}
					}
					if (massiv[s][k] == sym)
					{
						r++;
						if (r == kol1)
						{
							return true;
						}
					}
				}
			}
			return false;
	}
	int minimax(bool isMax, int alpha, int beta, char marker)
	{
		
		string status = victorycheck(marker);
		if (status == "First win")
		{
			return 10;
		}
		else if( status == "Second win")
		{
			return -10;
		}
		else if (status == "tie")
		{
			return 0;
		}
		
		if (isMax)
		{
			int best = -1000000;
			for (int i = 0; i < kol1; i++)
			{
				for (int j = 0; j < kol1; j++)
				{
					if (massiv[i][j] == '.')
					{
						massiv[i][j] = ComputerMarker;
						int val = minimax(!isMax, alpha ,beta,ComputerMarker);
						massiv[i][j] = '.';
						best = max(best,val);
						alpha = max(alpha,best);
						if (beta <= alpha)
						{
							return alpha;
						}
					}
				}
			}
			return beta;
		}
		else 
		{
			int best = 1000000;
			for (int i = 0; i < kol1; i++)
			{
				for (int j = 0; j < kol1; j++)
				{
					if (massiv[i][j] == '.')
					{
						massiv[i][j] = YouMarker;
						int val = minimax(!isMax, alpha, beta,YouMarker);
						massiv[i][j] = '.';
						best = min(best, val);
						beta = min(beta, best);
						if (beta >= alpha)
						{
							return beta;
						}
					}
				}
			}
			return alpha;
		}
	}
	tuple<int,int> alphabeta()
	{
		int bestval = -1000000;
		int movei = -1;
		int movej = -1;
		for (int i = 0; i < kol1; i++)
		{
			for (int j = 0; j < kol1; j++)
			{
				if (massiv[i][j] == '.')
				{
					massiv[i][j] = ComputerMarker;
					bool ter = false;
					int moveval = minimax(ter, -1000000, 1000000,YouMarker);
					massiv[i][j] = '.';
					if (moveval >= bestval)
					{
						bestval = moveval;
						movei = i;
						movej = j;
					}
				}
			}
		}
		return make_tuple(movei,movej);
	}
	int Player1(string kordin, int kor1, int kor2)
	{
		int j = 0;
		for (int i = 0; i < kol1; i++)
		{
			for (int j = 0; j < kol1; j++)
			{
				if ((kordin == mass1[i][j]) || (kordin == mass2[i][j]))
				{
					return 1;
				}
				else
				{
					massiv[kor1][kor2] = 'X';
					mass1[i][j] = kordin;
					return 0;
				}
			}
		}
	}
	void Player2()
	{
		int idx;
		int jdx;
		tie(idx, jdx) = alphabeta();
		massiv[idx][jdx] = '0';
	}

private:
	char **massiv;
	string **mass1;
	string **mass2;
	string *massempty;
	string *massindex;
	char **score;
	int stroka;
	int stolb;
	int kol1;
	int col;
	char ComputerMarker = '0';
	char YouMarker = 'X';
};
int main()
{
	Game game;
	int str;
	int stlb;
	int num;
	int kol;
	int kor1;
	int kor2;
	int playerkordin;
	char symbol;
	string kordin;
	
		cout << "Please,put the number of strings of your field: ";
		cin >> str;
		cout << "Please,put the number of column of your field: ";
		cin >> stlb;
		cout << "Please,put the number of symbols,which your need to win: ";
		cin >> kol;
		char **mass = new char*[str];
		for (int i = 0; i < str; i++)
		{
			mass[i] = new char[stlb];
		}
		for (int i = 0; i < str; i++)
		{
			for (int j = 0; j < stlb; j++)
			{
				mass[i][j] = '.';
			}
		}
		game.Masssiv(mass, str, stlb, kol);
		while (checknum(kol) != 0)
		{
			if (check(kol) == 1)
			{
				cout << "Your make a mistake,you must put the number between 3 and 19: ";
				cin >> kol;
			}
		}
		cout << "Koordinati kletok: \n";
		for (int i = 1; i <= str; i++)
		{
			for (int j = 1; j <= stlb; j++)
			{
				cout << "|" << "-" << i - 1 << j - 1 << "-" << "|";
			}
			cout << endl;
		}

		int step = 1;
		cin.ignore(std::numeric_limits<size_t>::max(), '\n');
		for (int i = 0; i < str*stlb; i++)
		{
			if (step % 2)
			{
				cout << endl << "You" << endl;
				symbol = 'X';
				cout << "Put your coordinates: ";
				getline(cin, kordin);
				if (kordin.length() == 2)
				{
					kor1 = stoi(kordin.substr(0, 1));
					kor2 = stoi(kordin.substr(1, 2));
				}
				else if (kordin.length() == 4)
				{
					kor1 = stoi(kordin.substr(0, 2));
					kor2 = stoi(kordin.substr(2, 4));
				}
				playerkordin = game.Player1(kordin, kor1, kor2);
				game.RealTime();
				while (playerkordin != 0)
				{
					if (playerkordin == 1)
					{
						cout << "This cordinate is unable,please write another coordinate: ";
						getline(cin, kordin);
						if (kordin.length() == 2)
						{
							kor1 = stoi(kordin.substr(0, 1));
							kor2 = stoi(kordin.substr(1, 2));
						}
						else if (kordin.length() == 4)
						{
							kor1 = stoi(kordin.substr(0, 2));
							kor2 = stoi(kordin.substr(2, 4));
						}
						playerkordin = game.Player1(kordin, kor1, kor2);
						game.RealTime();
					}
				}
			}
			else
			{
				cout << endl << "Computer" << endl;
				symbol = '0';
				game.Player2();
				game.RealTime();
			}
			if (step >= (kol * 2) - 1)
			{
				string prov = game.victorycheck(symbol);
				if (prov == "First win")
				{
					cout << "You win the game" << endl;
					break;
				}
				else if (prov == "Second win")
				{
					cout << "Computer win the game" << endl;
					break;
				}
				else if (prov == "continue")
				{
				}
			}
			step++;
		}
		for (int i = 0; i < str; i++)
		{
			delete[] mass[i];
		}
		game.Delete();
}