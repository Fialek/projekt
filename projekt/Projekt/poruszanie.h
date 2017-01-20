#pragma once

void poruszanie(int *pozycja, int rozmiarFigury, int zoom, int litera, int*rozmiarOkna)
{
	int klawisz = 0;
	while (klawisz != 27) // ESC
	{
		klawisz = _getch();
		if (klawisz == RUCH::GORA)
		{
			if (ruch(RUCH::GORA, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[1]--;
				rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);
			}
		}
		else if (klawisz == RUCH::DOL)
		{
			if (ruch(RUCH::DOL, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[1]++;
				rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);
			}
		}
		else if (klawisz == RUCH::LEWO)
		{
			if (ruch(RUCH::LEWO, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[0]--;
				rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);
			}
		}
		else if (klawisz == RUCH::PRAWO)
		{
			if (ruch(RUCH::PRAWO, pozycja, rozmiarFigury, zoom, rozmiarOkna))
			{
				pozycja[0]++;
				rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);
			}
		}
		else if (klawisz == ZOOM::PLUS)
		{
			if (zmienWielkosc(ZOOM::PLUS, zoom, rozmiarFigury, rozmiarOkna))
			{
				pozycja[0] = 0;
				pozycja[1] = rozmiarOkna[1];
				zoom += 2;
				rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);
			}
		}
		else if (klawisz == ZOOM::MINUS)
		{
			if (zmienWielkosc(ZOOM::MINUS, zoom, rozmiarFigury, rozmiarOkna))
			{
				pozycja[0] = 0;
				pozycja[1] = rozmiarOkna[1];
				zoom -= 2;
				rysujFigure(rozmiarFigury, pozycja, zoom, litera, rozmiarOkna);
			}
		}
		void inicjalizacjaOkna(int *rozmiarOkna);
	}
}