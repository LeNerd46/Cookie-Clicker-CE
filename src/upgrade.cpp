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

void Number::add(Number amount)
{
	decimals += amount.decimals;

	hundreds += amount.hundreds + ((decimals - (decimals % 1000)) * 0.001);
	decimals %= 1000;

	thousands += amount.thousands + ((hundreds - (hundreds % 1000)) * 0.001);
	hundreds %= 1000;

	millions += amount.millions + ((thousands - (thousands % 1000)) * 0.001);
	thousands %= 1000;

	billions += amount.billions + ((millions - (millions % 1000)) * 0.001);
	millions %= 1000;

	trillions += amount.trillions + ((billions - (billions % 1000)) * 0.001);
	billions %= 1000;
}

void Number::sub(Number amount)
{
	trillions -= amount.trillions;

	if (billions - amount.billions < 0)
	{
		trillions--;
		billions += 1000;
	}

	billions -= amount.billions;

	if (millions - amount.millions < 0)
	{
		billions--;
		millions += 1000;
	}

	millions -= amount.millions;

	if (thousands - amount.thousands < 0)
	{
		millions--;
		thousands += 1000;
	}

	thousands -= amount.thousands;

	if (hundreds - amount.hundreds < 0)
	{
		thousands--;
		hundreds += 1000;
	}

	hundreds -= amount.hundreds;

	if (decimals - amount.decimals < 0)
	{
		hundreds--;
		decimals += 1000;
	}

	decimals -= amount.decimals;
}

Number Number::mult(Number amount)
{
	Number result;

	result.decimals = decimals * amount.decimals;

	if (result.decimals >= 1000)
	{
		result.hundreds = result.decimals / 1000;
		result.decimals %= 1000;
	}

	result.hundreds += hundreds * amount.hundreds;

	if (result.hundreds >= 1000)
	{
		result.thousands = result.hundreds / 1000;
		result.hundreds %= 1000;
	}

	result.thousands += thousands * amount.thousands;

	if (result.thousands >= 1000)
	{
		result.millions = result.thousands / 1000;
		result.thousands %= 1000;
	}

	result.millions += millions * amount.millions;

	if (result.millions >= 1000)
	{
		result.billions = result.millions / 1000;
		result.millions %= 1000;
	}
	
	result.billions += billions * amount.billions;

	if (result.billions >= 1000)
	{
		result.trillions += result.billions / 1000;
		result.billions %= 1000;
	}

	result.trillions += trillions * result.trillions;
}

char Number::compareTo(Number amount)
{
	if (trillions == amount.trillions && billions == amount.billions && millions == amount.millions && thousands == amount.thousands && hundreds == amount.hundreds && decimals == amount.decimals)
		return 0;
	else if (trillions > amount.trillions)
		return 1;
	else if (billions > amount.billions)
		return 1;
	else if (millions > amount.millions)
		return 1;
	else if (thousands > amount.thousands)
		return 1;
	else if (hundreds > amount.hundreds)
		return 1;
	else if (decimals > amount.decimals)
		return 1;
	else
		return -1;
}

void Number::setValue(int decimals, int hundreds, int thousands, int millions, int billions, int trillions)
{
	this->decimals = decimals;
	this->hundreds = hundreds;
	this->thousands = thousands;
	this->millions = millions;
	this->billions = billions;
	this->trillions = trillions;
}
