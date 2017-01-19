#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

#define rozmiarPlanszy 30
#pragma warning(disable:4996)

void czytajDane(char *litera, int *rozmiar)
{
	cout << "\nPodaj litere: ";
	cin >> *litera;

	cout << "\nPodaj rozmiar: ";
	cin >> *rozmiar;
}

int *przygotujFigure( int rozmiar)
{
	int *figura;

	figura = new int[rozmiar*rozmiar];
	memset(figura, 0, rozmiar*rozmiar * sizeof(int));

	int rozmiar2 = rozmiar-1;
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x= 0; x < rozmiar; x++)
		{
			if (x == y || x==rozmiar2)
			{
				auto pozycja = &figura[y*rozmiar];
				pozycja[x] = 1;
			}
		}
		rozmiar2--;
	}

	return figura;
}

void inicjalizacjaOkna(int *rozmiarOkna)
{
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	rozmiarOkna[0] = csbi.srWindow.Right - csbi.srWindow.Left;
	rozmiarOkna[1] = csbi.srWindow.Bottom - csbi.srWindow.Top;	
}

void rysujFigure(int rozmiar, int *pozycja, int zoom, int *figura, char litera, int *rozmiarOkna)
{
	system("cls");

	int obecnyRozmiar = rozmiar + zoom;
	figura = przygotujFigure( obecnyRozmiar);

	int obecnaPozycja[2] = { pozycja[0], pozycja[1] - obecnyRozmiar };

	for (int entery = 0; entery < obecnaPozycja[1];entery++)
	{
		cout << "\n";
	}

	for (int y = obecnaPozycja[1]; y < obecnaPozycja[1] + obecnyRozmiar; y++)
	{
		for (int spacje = 0; spacje < obecnaPozycja[0]; spacje++)
		{
			cout << " ";
		}
		auto pos = &figura[(y- obecnaPozycja[1])*obecnyRozmiar];
		for (int x = 0; x < obecnyRozmiar; x++)
		{
			if (pos[x] == 1)
			{
				cout << litera;
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}

}

enum RUCH
{
	GORA = 72,
	LEWO = 75,
	PRAWO = 77,
	DOL = 80
};

enum ZOOM
{
	PLUS = 43,
	MINUS = 45
};

bool ruch(RUCH strona, int*pozycja, int rozmiar, int zoom, int *rozmiarOkna)
{
	int obecnyRozmiar = rozmiar + zoom;
	if (strona == RUCH::GORA)
	{
		if (pozycja[1] - obecnyRozmiar > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (strona == RUCH::DOL)
	{
		if (pozycja[1] <rozmiarOkna[1])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (strona == RUCH::LEWO)
	{
		if (pozycja[0] >0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (strona == RUCH::PRAWO)
	{
		if (pozycja[0] + obecnyRozmiar < rozmiarOkna[0]+1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool zoom(ZOOM zoom, int rozmiar, int *rozmiarOkna);

int main()
{
	char litera;
	int rozmiarFigury;
	int pozycja[2] = { 0 };
	int rozmiarOkna[2];
	int *figura = nullptr;
	int zoom;


	inicjalizacjaOkna(rozmiarOkna);

	czytajDane(&litera, &rozmiarFigury);
	pozycja[1] = rozmiarOkna[1];
	zoom = 0;

	rysujFigure(rozmiarFigury, pozycja, zoom, figura, litera, rozmiarOkna);

	int klawisz = 0;
	while (klawisz != 27)
	{
		klawisz = getch();
		if (klawisz == RUCH::GORA)
		{
			if (ruch(RUCH::GORA, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[1]--;
				rysujFigure(rozmiarFigury, pozycja, zoom, figura, litera, rozmiarOkna);
			}
		}
		else if (klawisz == RUCH::DOL)
		{
			if (ruch(RUCH::DOL, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[1]++;
				rysujFigure(rozmiarFigury, pozycja, zoom, figura, litera, rozmiarOkna);
			}
		}
		else if (klawisz == RUCH::LEWO)
		{
			if (ruch(RUCH::LEWO, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[0]--;
				rysujFigure(rozmiarFigury, pozycja, zoom, figura, litera, rozmiarOkna);
			}
		}
		else if (klawisz == RUCH::PRAWO)
		{
			if (ruch(RUCH::PRAWO, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[0]++;
				rysujFigure(rozmiarFigury, pozycja, zoom, figura, litera, rozmiarOkna);
			}
		}
		else if (klawisz == ZOOM::PLUS)
		{

		}
	}
	return 0;
}

