#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include "gfx/gfx.h"
#include "main.h"
#include <math.h>
#include <time.h>
#include <debug.h>

int main(void)
{
	gfx_Begin();
	gfx_SetDrawBuffer();
	gfx_SetColor(0xE0);
	gfx_SetTextFGColor(0xE0);
	gfx_SetPalette(mypalette, sizeof_mypalette, 0);

	int x = 150;
	int y = 200;

	unsigned int speed = 1;
	bool pressed = false;
	bool previousPress = false;

	unsigned int cookies = 0;
	float cps = 0;

	int cpsBase = 0;
	int cpsDecimal = 0;

	unsigned int cursorsOwned = 0;
	unsigned int cursorPrice = 15;

	unsigned int grandmasOwned = 0;
	unsigned int grandmaPrice = 100;

	clock_t lastUpdate = clock();

	// Maybe have a cursor and hold down a button to make the cursor move faster
	// (If you want to go from one side of the screen to another, it would take a while normally but you want it to move slowly too so you have control when you're trying to press something)

	do
	{
		kb_Scan();
		gfx_FillScreen(0xC7);

		clock_t now = clock();
		float elapsedTime = (now - lastUpdate) / (float)CLOCKS_PER_SEC;

		if (cpsDecimal >= 10)
		{
			cpsDecimal = 0;
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
		// gfx_SetTextScale(3, 3);
		gfx_PrintString(" cookies");
		gfx_PrintStringXY("per second: ", 10, 50);
		gfx_PrintInt(cpsBase, 1);

		if (cpsDecimal != 0)
		{
			gfx_PrintChar('.');
			gfx_PrintInt(cpsDecimal, 1);
		}

		gfx_PrintStringXY("Store", 255, 15);

		dbg_printf("Cookies Per Second: %f\n", cps);

		// Store Icons

		//Cursor
		gfx_SetColor(0x93);
		gfx_FillRectangle(225, 60, 95, 25);
		gfx_PrintStringXY("Cursor", 232, 65);

		gfx_SetTextXY(305, 65);
		gfx_PrintUInt(cursorsOwned, 1);

		gfx_SetTextXY(235, 75);
		gfx_PrintUInt(cursorPrice, 1);

		// Grandma
		gfx_FillRectangle(225, 90, 95, 25);
		gfx_PrintStringXY("Grandma", 232, 95);

		gfx_SetTextXY(305, 95);
		gfx_PrintUInt(grandmasOwned, 1);

		gfx_SetTextXY(235, 105);
		gfx_PrintUInt(grandmaPrice, 1);

		if (kb_IsDown(kb_KeyAlpha))
			speed = 5;
		else
			speed = 1;

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
				cookies++;
			else if (checkCollision(x, y, 3, 3, 225, 60, 95, 25))
			{
				if (cookies >= cursorPrice)
				{
					cursorsOwned++;
					cookies -= cursorPrice;
					cursorPrice = 15 * pow(1.15, cursorsOwned) + 1;
					cpsDecimal++;
					cps = roundf(cps * 10) / 10;
				}
			}
			else if (checkCollision(x, y, 3, 3, 225, 90, 95, 25))
			{
				if (cookies >= grandmaPrice)
				{
					grandmasOwned++;
					cookies -= grandmaPrice;
					grandmaPrice = 100 * pow(1.15, grandmasOwned) + 1;
					cpsBase += 1;
				}
			}
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
