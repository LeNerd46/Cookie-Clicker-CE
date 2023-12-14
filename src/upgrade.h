#pragma once
#include <stdlib.h>
#include <graphx.h>
#include <fileioc.h>

struct Upgrade
{
	bool unlocked;
	bool purchased;
	unsigned int price;

	const char* name;
	const char* description;
	const char* quote;

	unsigned char type; // Upgrade or cookie (0, 1)
	unsigned int id;

	gfx_rletsprite_t* icon;

	Upgrade()
	{
		unlocked = false;
		purchased = false;
		price = 0;

		name = "";
		description = "";
		quote = "";

		type = 0;
		icon = nullptr;
		id = 0;
	}

	Upgrade(unsigned int price, const char* name, const char* description, const char* quote, unsigned char type, gfx_rletsprite_t* sprite, unsigned int id)
	{
		unlocked = false;
		purchased = false;

		this->price = price;
		this->name = name;
		this->description = description;
		this->quote = quote;
		this->type = type;

		this->icon = sprite;
		this->id = id;
	}
};

class UpgradeManager
{
public:
	UpgradeManager(int initialCapacity = 10) : capacity(initialCapacity), numUpgrades(0)
	{
		upgrades = (Upgrade*)malloc(sizeof(Upgrade) * capacity);
	}

	~UpgradeManager()
	{
		free(upgrades);
	}

	void add(const Upgrade& upgrade);

	void remove(unsigned char index);

	Upgrade& get(unsigned char index) const;

	unsigned char count() const;

	bool save(FILE* file);
	bool load(FILE* file);

private:
	Upgrade* upgrades;
	int capacity;
	int numUpgrades;

	void reallocUpgradeArray(unsigned char newCapacity);
};

struct Number
{
	int decimals;
	int hundreds;
	int thousands;
	int millions;
	int billions;
	int trillions;

	// Add more later...

	Number()
	{
		decimals = 0;
		hundreds = 0;
		thousands = 0;
		millions = 0;
		billions = 0;
		trillions = 0;
	}

	Number(int decimals)
	{
		this->decimals = decimals;

		hundreds = 0;
		thousands = 0;
		millions = 0;
		billions = 0;
		trillions = 0;
	}

	Number(int decimals, int hundreds)
	{
		this->decimals = decimals; 
		this->hundreds = hundreds;

		thousands = 0;
		millions = 0;
		billions = 0;
		trillions = 0;
	}

	Number(int decimals, int hundreds, int thousands)
	{
		this->decimals = decimals;
		this->hundreds = hundreds;
		this->thousands = thousands;

		millions = 0;
		billions = 0;
		trillions = 0;
	}

	void add(Number amount);
	void sub(Number amount);
	Number mult(Number amount);

	char compareTo(Number amount);
	void setValue(int decimals, int hundreds, int thousands, int millions, int billions, int trillions);
};