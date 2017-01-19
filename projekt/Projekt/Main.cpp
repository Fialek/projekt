#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <iostream>

#include "definicje.h"
#include "poruszanie.h"

void czytajDane(char *litera, int *rozmiar)
{
	cout << "\nPodaj litere: ";
	cin >> *litera;

	cout << "\nPodaj rozmiar: ";
	cin >> *rozmiar;

	/*
	- nieparzysty rozmiar
	- rozmiar mieszczacy sie w ekranie
	- nie za maly rozmiar ? (>=3)
	*/
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

void rysujFigure(int rozmiar, int *pozycja, int zoom, char litera, int *rozmiarOkna)
{
	system("cls");

	int obecnyRozmiar = rozmiar + zoom;
	int *figura = przygotujFigure( obecnyRozmiar);

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
	delete figura;
}



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

bool zmienWielkosc(ZOOM zoom, int obecnyZoom, int rozmiar, int *rozmiarOkna)
{
	if (zoom == ZOOM::PLUS)
	{
		if (rozmiar+ obecnyZoom  < rozmiarOkna[0] && rozmiar + obecnyZoom < rozmiarOkna[1])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (zoom == ZOOM::MINUS)
	{
		if (rozmiar + obecnyZoom-2 >=3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int main()
{
	char litera;
	int rozmiarFigury;
	int pozycja[2] = { 0 };
	int rozmiarOkna[2];
	int zoom;


	inicjalizacjaOkna(rozmiarOkna);

	czytajDane(&litera, &rozmiarFigury);
	pozycja[1] = rozmiarOkna[1];
	zoom = 0;

	rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);

	poruszanie(pozycja, rozmiarFigury, zoom, litera, rozmiarOkna);

	_getch();
	return 0;
}
