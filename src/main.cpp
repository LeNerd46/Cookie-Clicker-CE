#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <debug.h>

#include "gfx/gfx.h"
#include "upgrade.h"
#include "main.h"
#include "building.h"

int main(void)
{
	loadOrCreateSave();

	gfx_Begin();
	gfx_SetDrawBuffer();
	gfx_SetColor(0xE0);
	gfx_SetTextFGColor(0xE0);
	gfx_SetPalette(mypalette, sizeof_mypalette, 0);

	int x = 150;
	int y = 200;

	unsigned int speed = 3;
	bool pressed = false;
	bool previousPress = false;

	bool savePress = false;
	bool previousSavePress = false;

	unsigned int factoriesOwned = 0;
	unsigned int factoryPrice = 130000;

	unsigned int banksOwned = 0;
	unsigned int bankPrice = 1000000;

	unsigned int templesOwned = 0;
	long int templePrice = 20000000;

	lastUpdate = clock();

	// Upgrades
	Upgrade reinforcedIndexFinger(100, "Reinforced Index Finger", "The mouse and cursors are twice as efficient", "prod prod", 0, plainCursor, 1);
	Upgrade carpalTunnelPreventionCream(500, "Carpal tunnel prevention cream", "The mouse are cursors are twice as efficient", "it... it hurts to click...", 0, cursorUpgradePink, 2);
	Upgrade ambidextrous(10000, "Ambidextrous", "The mouse and cursors are twice as efficient", "Look ma, both hands!", 0, cursorUpgradePink, 3);

	Upgrade forwardsFromGrandma(1000, "Forwards from grandma", "Grandmas are twice as efficient", "RE:RE:thought you'd get a kick out of this ;))", 0, plainCursor, 4);
	Upgrade steelPLatedRollingPins(5000, "Steel-plated rolling pins", "Grandmas are twice as efficient", "Just what you kneaded", 0, plainCursor, 5);

	do
	{
		kb_Scan();
		drawUI();

		calculateCpsToGive();

		pressed = kb_IsDown(kb_Key2nd);
		savePress = kb_IsDown(kb_KeyEnter);

		// Maybe find a better way to do this?
		// Dude I have no clue how it actually gives it to you
		// Nevermind it's based on your total cookies baked
		// I think I figured out, when your total baked cookies is the base price of the building two behind whatever building your checking, it will unlock
		if (!farmBuilding.showBackground && totalCookiesBaked.compareTo(Number(0, 15)) == 0) // Cursor
			farmBuilding.showInListBackground();
		if (!mineBuilding.showBackground && totalCookiesBaked.compareTo(Number(0, 100)) == 0) // Grandma
			mineBuilding.showInListBackground();

		for (unsigned char i = 0; i < sizeof(buildings) / sizeof(buildings[0]); i++)
		{
			if (buildings[i]->showBackground)
				buildings[i]->draw();

			if (!buildings[i]->show && (totalCookiesBaked.compareTo(buildings[i]->price) == 0 || totalCookiesBaked.compareTo(buildings[i]->price) == 1))
				buildings[i]->showInList();
		}

		// Factory
		/*gfx_FillRectangle(225, 172, 95, 25);
		gfx_PrintStringXY("Factory", 232, 177);

		gfx_SetTextXY(305, 177);
		gfx_PrintUInt(factoriesOwned, 1);

		gfx_SetTextXY(232, 187);
		gfx_PrintUInt(factoryPrice, 1);

		// Bank
		gfx_FillRectangle(225, 200, 95, 25);
		gfx_PrintStringXY("Bank", 232, 205);

		gfx_SetTextXY(305, 205);
		gfx_PrintUInt(banksOwned, 1);

		gfx_SetTextXY(232, 215);
		gfx_PrintUInt(bankPrice, 1);

		// Temple
		gfx_FillRectangle(225, 228, 95, 25);
		gfx_PrintStringXY("Temple", 232, 233);

		gfx_SetTextXY(305, 233);
		gfx_PrintUInt(templesOwned, 1);

		gfx_SetTextXY(232, 243);
		gfx_PrintUInt(templePrice, 1);*/

		if (kb_IsDown(kb_KeyAlpha))
			speed = 8;
		else
			speed = 3;

		if (kb_IsDown(kb_Key2))
			clickAmount = 1;

		if (savePress && !previousSavePress)
			save();

		if (kb_IsDown(kb_KeyDel))
		{
			remove("ccstor");
			gfx_End();

			return 0;
		}

		// if (kb_IsDown(kb_Key1))
			// loadOrCreateSave();

		if (kb_IsDown(kb_KeyLeft))
			x > 0 ? x -= speed : x = 0;
		else if (kb_IsDown(kb_KeyRight))
			x < 320 ? x += speed : x = 320;

		if (kb_IsDown(kb_KeyUp))
			y > 0 ? y -= speed : y = 0;
		else if (kb_IsDown(kb_KeyDown))
			y < 240 ? y += speed : y = 240;

		if (pressed && !previousPress)
		{
			if (checkCollision(x, y, 1, 1, 20, 80, 60, 60))
			{
				cookies.add(clickAmount);
				totalCookiesBaked.add(clickAmount);
			}
			else if (checkCollision(x, y, 1, 1, 225, 60, 95, 25))
			{
				if (cookies.compareTo(cursorBuilding.price) == 1 || cookies.compareTo(cursorBuilding.price) == 0)
				{
					cursorBuilding.amount++;
					cookies.sub(cursorBuilding.price);
					// cursorBuilding.price = 15 * pow(1.15, cursorBuilding.amount) + 1;
					Number first(0, 15);
					dbg_printf("No Multiplication: %i.%i\n", first.hundreds, first.decimals);
					first = pow(Number(15, 1), cursorBuilding.amount);
					dbg_printf("Power: %i.%i\n", first.hundreds, first.decimals);
					first = first.mult(Number(0, 15));
					dbg_printf("After Multiplication and power: %i.%i\n", first.hundreds, first.decimals);
					first.add(Number(0, 1));
					dbg_printf("Add 1: %i.%i\n", first.hundreds, first.decimals);

					cursorBuilding.price = first;
					cpsDecimal += cursorBuilding.cpsDecimalPerOwned;

					if (cursorBuilding.amount == 1)
					{
						upgrades.add(reinforcedIndexFinger);
						upgrades.add(carpalTunnelPreventionCream);
					}
					else if (cursorBuilding.amount == 10)
						upgrades.add(ambidextrous);
				}
			}
			else if (checkCollision(x, y, 1, 1, 225, 90, 95, 25))
			{
				// Grandma

				if (cookies.compareTo(grandmaBuilding.price) == 0)
				{
					grandmaBuilding.amount++;
					cookies.sub(grandmaBuilding.price);
					grandmaBuilding.price = 100 * pow(1.15, grandmaBuilding.amount) + 1;
					cpsBase += grandmaBuilding.cpsPerOwned;

					if (grandmaBuilding.amount == 1)
						upgrades.add(forwardsFromGrandma);
					else if (grandmaBuilding.amount == 5)
						upgrades.add(steelPLatedRollingPins);
				}
			}
			else if (checkCollision(x, y, 1, 1, 225, 120, 95, 25))
			{
				// Farm
				if (cookies.compareTo(farmBuilding.price) == 0)
				{
					farmBuilding.amount++;
					cookies.sub(farmBuilding.price);
					farmBuilding.price = 1100 * pow(1.15, farmBuilding.amount) + 1;
					cpsBase += farmBuilding.cpsPerOwned;
				}
			}
			else if (checkCollision(x, y, 1, 1, 225, 150, 95, 25))
			{
				// Mine
				if (cookies.compareTo(mineBuilding.price) == 0)
				{
					mineBuilding.amount++;
					cookies.sub(mineBuilding.price);
					mineBuilding.price = 12000 * pow(1.15, mineBuilding.amount) + 1;
					cpsBase += mineBuilding.cpsPerOwned;
				}
			}
		}

		unsigned int startX = 225;
		unsigned int startY = 30;

		for (unsigned char i = 0; i < upgrades.count(); i++)
		{
			Upgrade upgrade = upgrades.get(i);

			gfx_SetColor(0x61);
			gfx_Rectangle(startX, startY, 17, 17);
			gfx_RLETSprite(upgrade.icon, startX + 1, startY + 1);

			if (checkCollision(x, y, 1, 1, startX, startY, 17, 17))
			{
				if (pressed && !previousPress && (cookies.compareTo(upgrade.price) == 1 || cookies.compareTo(upgrade.price) == 0))
				{
					cookies.sub(upgrade.price);
					upgrade.purchased = true;

					if (upgrade.id == 1 || upgrade.id == 2)
					{
						cpsDecimal *= 2;
						cursorBuilding.cpsDecimalPerOwned *= 2;
						clickAmount.add(clickAmount);
					}
					else if (upgrade.id == 4 || upgrade.id == 5)
						grandmaBuilding.cpsPerOwned *= 2;

					upgrades.remove(i);

					calculateCps();
				}
				else
				{
					gfx_SetColor(0x45);
					gfx_FillRectangle(120, 15, 105, 50);
					gfx_PrintStringXY(upgrade.name, 122, 17);
					gfx_SetTextXY(122, 50);
					gfx_PrintUInt(upgrade.price, 1);
					gfx_PrintString(" cookies");
				}
			}

			startX += 17;
		}

		gfx_RLETSprite(cookie, 20, 80);
		gfx_RLETSprite(cursorUpgradeNew, 50, 145);
		gfx_RLETSprite(cursor, x, y);

		previousPress = pressed;
		previousSavePress = savePress;

		gfx_BlitBuffer();

	} while (kb_Data[6] != kb_Clear);

	gfx_End();
}

bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight)
{
	return firstX < secondX + secondWidth // First object's left side is to the left of the second object's right side,         first object is on the right
		&& firstX + firstWidth > secondX // First object's right side is to the right of the second object's left side,         first object is on the left
		&& firstY < secondY + secondHeight // The first object's top is above the second object's bottom,                       first object is underneath
		&& firstY + firstHeight > secondY; // The first object's bottom is lower than the second object's top,                  first object is above
}

Number pow(Number base, int exponent)
{
	if (exponent == 0)
		return Number(0, 1);
	else if (exponent == 1)
		return base;

	Number result = pow(base, exponent / 2);
	result.mult(result);

	if (exponent % 2)
		result.mult(base);

	return result;
}

void calculateCps()
{
	cpsBase = 0;
	cpsDecimal = 0;

	for (unsigned char i = 0; i < (sizeof(buildings) / sizeof(buildings[i])); i++)
	{
		cpsBase += buildings[i]->amount * buildings[i]->cpsPerOwned;
		cpsDecimal += buildings[i]->amount * buildings[i]->cpsDecimalPerOwned;
	}
}

void calculateCpsToGive()
{
	clock_t now = clock();
	float elapsedTime = (now - lastUpdate) / (float)CLOCKS_PER_SEC;

	if (cpsDecimal >= 10)
	{
		cpsDecimal -= 10;
		cpsBase++;
	}

	float earnedCookies = elapsedTime * (cpsBase + cpsDecimal / static_cast<float>(10));

	if (earnedCookies >= 1)
	{
		int decimal = fmod(earnedCookies, 1);

		cookies.add(Number(decimal * 1000, earnedCookies - decimal));
		totalCookiesBaked.add(Number(decimal * 1000, earnedCookies - decimal));
		earnedCookies -= earnedCookies;
		lastUpdate = now;
	}
}

void drawUI()
{
	gfx_FillScreen(0xC7);

	gfx_SetTextFGColor(0xFB);

	// Line Separators
	gfx_SetColor(0x61);
	gfx_FillRectangle(100, 0, 5, 240);
	gfx_FillRectangle(220, 0, 5, 240);

	// Cookie Count
	gfx_SetTextXY(15, 40);
	gfx_PrintInt(cookies.hundreds, 1);

	// Text
	gfx_SetTextFGColor(0xFE);
	gfx_PrintString(" cookies");
	gfx_PrintStringXY("per second: ", 10, 50);
	gfx_PrintInt(cpsBase, 1);

	if (cpsDecimal != 0)
	{
		gfx_PrintChar('.');
		gfx_PrintInt(cpsDecimal, 1);
	}

	gfx_PrintStringXY("Store", 255, 15);

	// Store Icons
	gfx_SetColor(0x93);

	//Upgrades
	gfx_FillRectangle(225, 15, 95, 25);

	// Store Icon
	gfx_SetColor(0xC7);
	gfx_FillRectangle(225, 15, 95, 25);
	gfx_PrintStringXY("Store", 255, 15);
}

#define TO_SERIALIZE(F) \
    F(cookies) \
    F(cpsBase) \
    F(cpsDecimal) \
    F(clickAmount) \
    F(totalCookiesBaked) \
	F(cursorBuilding) \
	F(grandmaBuilding) \
	F(farmBuilding) \
	F(mineBuilding) \
	F(upgrades) \

#define SERIALIZE(var) fread(&(var), sizeof(var), 1, file);
#define DESERIALIZE(var) fwrite(&(var), sizeof(var), 1, file);

#define NO_OPT __attribute__ ((optnone))

void loadOrCreateSave() NO_OPT
{
	FILE* file = fopen("ccstor", "r");

	if (file)
	{
		TO_SERIALIZE(SERIALIZE);
	}
	else
	{
		cookies = Number(0, 0);
		cpsBase = 0;
		cpsDecimal = 0;
		clickAmount = Number(0, 1);
		totalCookiesBaked = Number(0, 0);
	}

	fclose(file);
}

void save() NO_OPT
{
	FILE* file = fopen("ccstor", "w");

	if (file)
		TO_SERIALIZE(DESERIALIZE);

	fclose(file);
}