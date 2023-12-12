#include "upgrade.h"

void UpgradeManager::add(const Upgrade& upgrade)
{
	if (numUpgrades == capacity)
		reallocUpgradeArray(capacity * 2);

	upgrades[numUpgrades++] = upgrade;
}

void UpgradeManager::remove(unsigned char index)
{
	if (index < 0 || index >= numUpgrades)
		return;
	
	for (unsigned char i = index + 1; i < numUpgrades; i++)
	{
		upgrades[i - 1] = upgrades[i];
	}

	numUpgrades--;
}

Upgrade& UpgradeManager::get(unsigned char index) const
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

bool UpgradeManager::save(FILE* file)
{
	if (!file)
		return false;

	fwrite(&numUpgrades, sizeof(int), 1, file);

	for (int i = 0; i < numUpgrades; i++)
	{
		const Upgrade& upgrade = upgrades[i];

		fwrite(upgrade.name, sizeof(size_t), 1, file);
		fwrite(upgrade.description, sizeof(size_t), 1, file);

		fwrite(&upgrade.price, sizeof(unsigned int), 1, file);
		fwrite(&upgrade.id, sizeof(unsigned int), 1, file);
	}

	return true;
}

bool UpgradeManager::load(FILE* file)
{
	if (!file)
		return false;

	int savedUpgrades;
	if (fread(&savedUpgrades, sizeof(int), 1, file) != 1)
		return false;

	if (savedUpgrades > capacity)
		reallocUpgradeArray(savedUpgrades);

	for (int i = 0; i < savedUpgrades; i++)
	{
		Upgrade upgrade;

		size_t nameLength;
		size_t descriptionLength;

		if (fread(&nameLength, sizeof(size_t), 1, file) != 1 || fread(&descriptionLength, sizeof(size_t), 1, file) != 1)
			return false;

		char* nameBuffer = new char[nameLength + 1];
		char* descriptionBuffer = new char[descriptionLength + 1];

		if (fread(nameBuffer, sizeof(char), nameLength, file) != nameLength || fread(descriptionBuffer, sizeof(char), descriptionLength, file) != 1)
			return false;

		nameBuffer[nameLength] = '\0';
		descriptionBuffer[descriptionLength] = '\0';
		upgrade.name = nameBuffer;
		upgrade.description = descriptionBuffer;

		if (fread(&upgrade.price, sizeof(unsigned int), 1, file) != 1)
		{
			delete[] nameBuffer;
			delete[] descriptionBuffer;

			return false;
		}

		upgrades[numUpgrades++] = upgrade;

		delete[] nameBuffer;
		delete[] descriptionBuffer;
	}
}

void UpgradeManager::reallocUpgradeArray(unsigned char newCapacity)
{
	upgrades = (Upgrade*)realloc(upgrades, sizeof(Upgrade) * newCapacity);
	capacity = newCapacity;
}