#pragma once
#include <fileioc.h>
#include "upgrade.h"

bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight);

void loadOrCreateSave(FILE* file);
void save(FILE* file);

UpgradeManager upgrades(10);

unsigned int cookies;
unsigned int cpsBase;
unsigned char cpsDecimal;
unsigned int clickAmount;

unsigned int cursorsOwned;
unsigned int cursorPrice;
unsigned int cursorCps;

unsigned int grandmasOwned;
unsigned int grandmaPrice;
unsigned int grandmaCps;