#pragma once
#include "upgrade.h"

class Building
{
public:
	const char* name;
	Number price;
	unsigned int amount;
	unsigned int cpsPerOwned;
	unsigned char cpsDecimalPerOwned;

	bool show;
	bool showBackground;

	Building(const char* name, Number price, unsigned int cpsPerOwned, int x, int y, unsigned int amount, bool show, bool showBackground, unsigned char cpsDecimalPerOwned);

	void SetXY(int x, int y);

	void draw();

	void showInList();
	void showInListBackground();

private:
	int x;
	int y;
};