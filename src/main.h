#pragma once
#include <fileioc.h>
#include "upgrade.h"
#include "building.h"

bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight);
Number pow(Number base, int exponent);

void calculateCps();
void calculateCpsToGive();
void drawUI();

void loadOrCreateSave();
void save();

clock_t lastUpdate;

UpgradeManager upgrades(10);
Building cursorBuilding("Cursor", Number(0, 15), 0, 225, 60, 0, false, true, 1);
Building grandmaBuilding("Grandma", Number(0, 100), 1, 225, 88, 0, false, true, 0);
Building farmBuilding("Farm", Number(0, 100, 1), 8, 225, 116, 0, false, false, 0);
Building mineBuilding("Mine", Number(0, 0, 12), 47, 225, 144, 0, false, false, 0);

Building* buildings[] = { &cursorBuilding, &grandmaBuilding, &farmBuilding, &mineBuilding };

Number cookies(0, 0);
unsigned int cpsBase;
unsigned char cpsDecimal;
Number clickAmount(0, 1000);
Number totalCookiesBaked;

unsigned int cursorsOwned;
unsigned int cursorPrice;
unsigned int cursorCps;

unsigned int grandmasOwned;
unsigned int grandmaPrice;
unsigned int grandmaCps;