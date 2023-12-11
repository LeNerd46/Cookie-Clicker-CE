#include "upgrade.h"

void UpgradeManager::addUpgrade(const Upgrade& upgrade)
{
	if (numUpgrades == capacity)
		reallocUpgradeArray(capacity * 2);

	upgrades[numUpgrades++] = upgrade;
}

void UpgradeManager::removeUpgrade(unsigned char index)
{
	if (index < 0 || index >= numUpgrades)
		return;
	
	for (unsigned char i = index + 1; i < numUpgrades; i++)
	{
		upgrades[i - 1] = upgrades[i];
	}

	numUpgrades--;
}

Upgrade& UpgradeManager::getUpgrade(unsigned char index) const
{
	// DO NOT TRY TO GET AN UPGRADE OUT OF BOUNDS!!!!

	// if (index < 0 || index >= numUpgrades)
	// 	return nullptr;

	return upgrades[index];
}

unsigned char UpgradeManager::count() const
{
	return numUpgrades;
}

void UpgradeManager::reallocUpgradeArray(unsigned char newCapacity)
{
	upgrades = (Upgrade*)realloc(upgrades, sizeof(Upgrade) * newCapacity);
	capacity = newCapacity;
}