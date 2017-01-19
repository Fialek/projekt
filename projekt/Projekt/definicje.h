#pragma once

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

bool ruch(RUCH strona, int*pozycja, int rozmiar, int zoom, int *rozmiarOkna);

void rysujFigure(int rozmiar, int *pozycja, int zoom, char litera, int *rozmiarOkna);

bool zmienWielkosc(ZOOM zoom, int obecnyZoom, int rozmiar, int *rozmiarOkna);