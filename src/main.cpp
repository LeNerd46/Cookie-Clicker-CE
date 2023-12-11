#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include "gfx/gfx.h"
#include "main.h"
#include <math.h>
#include <time.h>
#include <debug.h>
#include "upgrade.h"

int main(void)
{
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

	unsigned int cookies = 0;
	unsigned int clickAmount = 1;

	int cpsBase = 0;
	int cpsDecimal = 0;

	unsigned int cursorsOwned = 0;
	unsigned int cursorPrice = 15;
	unsigned int cursorCps = 1;

	unsigned int grandmasOwned = 0;
	unsigned int grandmaPrice = 100;
	unsigned int grandmaCps = 1;

	unsigned int farmsOwned = 0;
	unsigned int farmPrice = 1100;

	unsigned int minesOwned = 0;
	unsigned int minePrice = 12000;

	unsigned int factoriesOwned = 0;
	unsigned int factoryPrice = 130000;

	unsigned int banksOwned = 0;
	unsigned int bankPrice = 1000000;

	unsigned int templesOwned = 0;
	long int templePrice = 20000000;

	clock_t lastUpdate = clock();

	// Maybe have a cursor and hold down a button to make the cursor move faster
	// (If you want to go from one side of the screen to another, it would take a while normally but you want it to move slowly too so you have control when you're trying to press something)

	// Upgrades
	unsigned char amountOfUpgrades = 0;

	Upgrade reinforcedIndexFinger(100, "Reinforced Index Finger", "The mouse and cursors are twice as efficient", "prod prod", 0, plainCursor, 1);
	Upgrade carpalTunnelPreventionCream(500, "Carpal tunnel prevention cream", "The mouse are cursors are twice as efficient", "it... it hurts to click...", 0, cursorUpgradePink, 2);
	Upgrade ambidextrous(10000, "Ambidextrous", "The mouse and cursors are twice as efficient", "Look ma, both hands!", 0, cursorUpgradePink, 3);

	Upgrade forwardsFromGrandma(1000, "Forwards from grandma", "Grandmas are twice as efficient", "RE:RE:thought you'd get a kick out of this ;))", 0, plainCursor, 4);
	Upgrade steelPLatedRollingPins(5000, "Steel-plated rolling pins", "Grandmas are twice as efficient", "Just what you kneaded", 0, plainCursor, 5);

	UpgradeManager upgrades(10);

	do
	{
		kb_Scan();
		gfx_FillScreen(0xC7);

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
			cookies += earnedCookies;
			earnedCookies -= earnedCookies;
			lastUpdate = now;
		}

		pressed = kb_IsDown(kb_Key2nd);

		gfx_SetTextFGColor(0xFB);

		// Line Separators
		gfx_SetColor(0x61);
		gfx_FillRectangle(100, 0, 5, 240);
		gfx_FillRectangle(220, 0, 5, 240);

		// Cookie Count
		gfx_SetTextXY(15, 40);
		gfx_PrintUInt(cookies, 1);

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

		// Cursor
		gfx_FillRectangle(225, 60, 95, 25);
		gfx_PrintStringXY("Cursor", 232, 65);

		gfx_SetTextXY(305, 65);
		gfx_PrintUInt(cursorsOwned, 1);

		gfx_SetTextXY(232, 75);
		gfx_PrintUInt(cursorPrice, 1);

		// Grandma
		gfx_FillRectangle(225, 88, 95, 25);
		gfx_PrintStringXY("Grandma", 232, 93);

		gfx_SetTextXY(305, 93);
		gfx_PrintUInt(grandmasOwned, 1);

		gfx_SetTextXY(232, 103);
		gfx_PrintUInt(grandmaPrice, 1);

		// Farm
		gfx_FillRectangle(225, 116, 95, 25);
		gfx_PrintStringXY("Farm", 232, 121);

		gfx_SetTextXY(305, 121);
		gfx_PrintUInt(farmsOwned, 1);

		gfx_SetTextXY(232, 131);
		gfx_PrintUInt(farmPrice, 1);

		// Mine
		gfx_FillRectangle(225, 144, 95, 25);
		gfx_PrintStringXY("Mine", 232, 149);

		gfx_SetTextXY(305, 149);
		gfx_PrintUInt(minesOwned, 1);

		gfx_SetTextXY(232, 159);
		gfx_PrintUInt(minePrice, 1);

		// Factory
		gfx_FillRectangle(225, 172, 95, 25);
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
		gfx_PrintUInt(templePrice, 1);

		// Store Icon
		gfx_SetColor(0xC7);
		gfx_FillRectangle(225, 15, 95, 25);
		gfx_PrintStringXY("Store", 255, 15);

		// Screen Cursor
		if (kb_IsDown(kb_KeyAlpha))
			speed = 8;
		else
			speed = 3;

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
			if (checkCollision(x, y, 3, 3, 20, 80, 60, 60))
				cookies += clickAmount;
			else if (checkCollision(x, y, 3, 3, 225, 60, 95, 25))
			{
				if (cookies >= cursorPrice)
				{
					cursorsOwned++;
					cookies -= cursorPrice;
					cursorPrice = 15 * pow(1.15, cursorsOwned) + 1;
					cpsDecimal += cursorCps;

					if (cursorsOwned == 1)
					{
						upgrades.addUpgrade(reinforcedIndexFinger);
						upgrades.addUpgrade(carpalTunnelPreventionCream);
					}
					else if (cursorsOwned == 10)
						upgrades.addUpgrade(ambidextrous);
				}
			}
			else if (checkCollision(x, y, 3, 3, 225, 90, 95, 25)) 
			{
				// Grandma

				if (cookies >= grandmaPrice)
				{
					grandmasOwned++;
					cookies -= grandmaPrice;
					grandmaPrice = 100 * pow(1.15, grandmasOwned) + 1;
					cpsBase += 1;

					if (grandmasOwned == 1)
						upgrades.addUpgrade(forwardsFromGrandma);
					else if (grandmasOwned == 5)
						upgrades.addUpgrade(steelPLatedRollingPins);
				}
			}
			else if (checkCollision(x, y, 3, 3, 225, 120, 95, 25)) 
			{
				// Farm
				if (cookies >= farmPrice) 
				{
					farmsOwned++;
					cookies -= farmPrice;
					farmPrice = 1100 * pow(1.15, farmsOwned) + 1;
					cpsBase += 8;
				}
			}
			else if (checkCollision(x, y, 3, 3, 225, 150, 95, 25))
			{
				// Mine
				if (cookies >= minePrice) 
				{
					minesOwned++;
					cookies -= minePrice;
					minePrice = 12000 * pow(1.15, minesOwned) + 1;
					cpsBase += 47;
				}
			}
			else if (checkCollision(x, y, 3, 3, 225, 180, 95, 25)) 
			{
				// Factory
				if (cookies >= factoryPrice) 
				{
					factoriesOwned++;
					cookies -= factoryPrice;
					factoryPrice = 130000 * pow(1.15, factoriesOwned) + 1;
					cpsBase += 260;
				}
			}
			else if (checkCollision(x, y, 3, 3, 255, 210, 95, 25)) 
			{
				// Bank
				if (cookies >= bankPrice) 
				{
					banksOwned++;
					cookies -= bankPrice;
					bankPrice = 1400000 * pow(1.15, banksOwned) + 1;
					cpsBase += 1400;
				}
			}
			else if (checkCollision(x, y, 3, 3, 225, 240, 95, 25)) 
			{
				// Temple
				if (cookies >= templePrice) 
				{
					templesOwned++;
					cookies -= templePrice;
					templePrice = 20000000 * pow(1.15, templesOwned) + 1;
					cpsBase += 7800;
				}
			}
		}

		unsigned int startX = 225;
		unsigned int startY = 30;

		for (unsigned char i = 0; i < upgrades.count(); i++)
		{
			Upgrade upgrade = upgrades.getUpgrade(i);

			gfx_SetColor(0x61);
			gfx_Rectangle(startX, startY, 17, 17);
			gfx_RLETSprite(upgrade.icon, startX + 1, startY + 1);

			if (checkCollision(x, y, 1, 1, startX, startY, 17, 17))
			{
				if (pressed && !previousPress && cookies >= upgrade.price)
				{
					cookies -= upgrade.price;
					upgrade.purchased = true;

					if (upgrade.id == 1 || upgrade.id == 2) 
					{
						cpsDecimal *= 2;
						cursorCps *= 2;
						clickAmount *= 2;
					}
					else if (upgrade.id == 4 || upgrade.id == 5)
						grandmaCps *= 2;

					upgrades.removeUpgrade(i);
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