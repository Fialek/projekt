#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <iostream>

#include "definicje.h"
#include "ruch.h"
#include "poruszanie.h"

/*
Napisz program rysowania znakiem ASCII poniższej figury. Program powinien

umożliwić:

− wybór znaku kodu ASCII;

− wczytanie początkowych rozmiarów figury;

− przesuwanie figury klawiszami ←, →, ↑, ↓;

− powiększanie oraz zmniejszanie rozmiaru figury za pomocą klawiszy + i -;

− ograniczenie przesuwania i rozmiarów figury do obszaru ekranu;


Numer projektu : 170
20/01/2017
Fijałkowski Patryk

Dane wejsciowe ilustrujące możliwości programu
	Zestaw 1:
		Podany znak : ctrl
	Zestaw 2:
		Podany znak : Z
		Podany rozmiar: 1
	Zestaw 3:
		Podany znak : Z
		Podany rozmiar: 4
	Zestaw 4: 
		Podany znak: Z
		Podany rozmiar: 5

*/
bool jestLitera(int litera)	//funkcja sprawdzająca poprawność wprowadzonego znaku
{
	if (litera <= 0 || litera > 127) // znaki specjalne
	{
		_getch();
		return false;
	}

	if (litera >= 33 && litera <= 126)
		return true;

	return false;
}
void czytajDane(char *litera, int *rozmiar)	// funckja zczytująca dane wejściowe
{
	cout << "\nPodaj znak: ";
	*litera = _getch();
	while (!jestLitera(*litera))	// pętla pobierająca poprawny znak
	{
		cout << "\nPodany znak nie jest litera. Sprobuj ponownie";
		cout << "\nPodaj litere: ";

		*litera = _getch();
	}

	cout << "\nPodaj rozmiar (liczba nieparzysta i niemniejsza niz 3) :  ";
	cin >> *rozmiar;
	if ((*rozmiar) % 2 == 0)	//warunek sprawdzający parzystość wprowadzonego rozmiaru
	{
		(*rozmiar)++;
		cout << "\nLiczba jest parzysta. Zostala powieszkona do " << *rozmiar;
	}
	if (*rozmiar < 3)		//warunek sprawdzający minimalny rozmiar planszy (warunek stworzenia przekątnych)
	{
		*rozmiar = 3;
		cout << "\nLiczba mniejsza od 3. Nowy rozmiar to 3";
	}

	cout << "\nRozmiar oraz litera ustalone. Nacisnij dowolny klawisz aby kontynuowac...";
	_getch();
}

int *przygotujFigure( int rozmiar)	//przygotowanie tablicy ze znakami
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

void inicjalizacjaOkna(int *rozmiarOkna)	// pobieranie właściwości okna konsoli
{
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	rozmiarOkna[0] = csbi.srWindow.Right - csbi.srWindow.Left;
	rozmiarOkna[1] = csbi.srWindow.Bottom - csbi.srWindow.Top;	
}

void rysujFigure(int rozmiar, int *pozycja, int zoom, char litera, int *rozmiarOkna)  // zapełnianie konsoli znakami
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

bool zmienWielkosc(ZOOM zoom, int obecnyZoom, int rozmiar, int *rozmiarOkna) //funckaja odpowiadająca za sprawdzenie  poprawności operacji zoomu
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
	// wywoływanie funkcji
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
