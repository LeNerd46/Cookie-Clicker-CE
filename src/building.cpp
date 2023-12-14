#include "building.h"
#include <graphx.h>
#include <math.h>

Building::Building(const char* name, Number price, unsigned int cpsPerOwned, int x, int y, unsigned int amount, bool show, bool showBackground, unsigned char cpsDecimalPerOwned)
{
	this->name = name;
	this->price = price;
	this->cpsPerOwned = cpsPerOwned;
	this->cpsDecimalPerOwned = cpsDecimalPerOwned;

	this->amount = amount;
	this->x = x;
	this->y = y;

	this->show = false;
	this->showBackground = showBackground;
}

void Building::SetXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Building::draw()
{
	gfx_SetColor(0xFE);
	gfx_FillRectangle(x, y, 95, 25);

	gfx_SetTextFGColor(0x21);
	gfx_SetTextXY(232, y + 15);
	gfx_PrintInt(price.hundreds, 1);

	if (show)
	{
		gfx_PrintStringXY(name, x + 7, y + 5);

		gfx_SetTextXY(305, y + 5);
		gfx_PrintUInt(amount, 1);
	}
	else
		gfx_PrintStringXY("???", x + 7, y + 5);
}

void Building::showInList()
{
	if (!show)
		show = true;
}

void Building::showInListBackground()
{
	if (!showBackground)
		showBackground = true;
}
