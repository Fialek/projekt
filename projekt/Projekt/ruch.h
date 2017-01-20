#pragma once

bool ruch(RUCH strona, int*pozycja, int rozmiar, int zoom, int *rozmiarOkna) //walidacja mo¿liwoœci wykonania ruchu
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
		if (pozycja[0] + obecnyRozmiar < rozmiarOkna[0] + 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
