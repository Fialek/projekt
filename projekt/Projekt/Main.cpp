#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

void czytajDane(char *litera, int *rozmiar)
{
	cout << "\nPodaj litere: ";
	cin >> *litera;

	cout << "\nPodaj rozmiar: ";
	cin >> *rozmiar;
}

void inicjalizujFigure(int *figura, int rozmiar)
{
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
				cout << 1;
			}
			else
			{
				cout << 0;
			}
		}
		rozmiar2--;
		cout << "\n";
	}


}

int main()
{
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	char litera;
	int rozmiar;
	int pozycja[2] = { 0 };
	int *figura = nullptr;

	czytajDane(&litera, &rozmiar);

	inicjalizujFigure(figura, rozmiar);


	_getch();
	return 0;
}

