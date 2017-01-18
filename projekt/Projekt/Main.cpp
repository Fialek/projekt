#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

#define rozmiarPlanszy 30


void czytajDane(char *litera, int *rozmiar)
{
	cout << "\nPodaj litere: ";
	cin >> *litera;

	cout << "\nPodaj rozmiar: ";
	cin >> *rozmiar;

	system("cls");
}

void przygotujFigure(int *figura, int rozmiar)
{
	if (figura != nullptr)
		delete figura;

	figura = new int[rozmiar*rozmiar];
	memset(figura, 0, rozmiar*rozmiar * sizeof(int));

	int rozmiar2 = rozmiar-1;
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x= 0; x < rozmiar; x++)
		{
			if (x == y || x==rozmiar2)
			{
				auto pozycja = &figura[x];
				*pozycja = 1;
			}
		}
		rozmiar2--;
	}
}

void inicjalizacjaOkna(int *rozmiarOkna)
{
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	rozmiarOkna[0] = r.right;
	rozmiarOkna[1] = r.bottom;

	/*for (int y = 0; y <= rozmiarPlanszy; y++)
	{
		for (int x = 0;x <= rozmiarPlanszy; x++)
		{
			if (y == 0 || y==rozmiarPlanszy)
			{
				cout << "-";
			}
			else if (x == 0 || x == rozmiarPlanszy)
			{
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << "\n";
	}*/
}

void rysujFigure(int rozmiar, int *pozycja, int zoom, int *figura, char litera, int *rozmiarOkna)
{
	int obecnyRozmiar = rozmiar + zoom;
	przygotujFigure(figura, obecnyRozmiar);

	int obecnaPozycja[2] = { pozycja[0], pozycja[1] - obecnyRozmiar };

	for (int entery = 0; entery < obecnaPozycja[1] - obecnyRozmiar;entery++)
	{
		cout << "\n";
	}

	for (int x = obecnaPozycja[0]; x < obecnaPozycja[0] + obecnyRozmiar; x++)
	{
		for (int spacje = 0; spacje < obecnaPozycja[0]; spacje++)
		{
			cout << " ";
		}
		for (int y = obecnaPozycja[1]; y < obecnaPozycja[1] + obecnyRozmiar; y++)
		{
			auto pos = &figura[x];
			cout << pos[y];
		}
		cout << "\n";
	}

}

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

	_getch();
	return 0;
}

