#pragma once
#include <stdlib.h>
#include <time.h>
#include <map>
#include <string>
#include <iostream>

class FuzLogSet
{
	enum Height
	{
		ExtremelyShort = 0,
		FairlyShort = 1,
		Short = 2,
		AverageHeight = 3,
		Tall = 4,
		FairlyTall = 5,
		ExtremelyTall = 6
	};

	enum Weight
	{
		ExtremelyLight = 0,
		FairlyLight = 1,
		Light = 2,
		AverageWeight = 3,
		Heavy = 4,
		FairlyHeavy = 5,
		ExtremelyHeavy = 6
	};

	enum Strength
	{
		ExtremelyWeak = 0,
		FairlyWeak = 1,
		Weak = 2,
		AverageStrength = 3,
		Strong = 4,
		FairlyStrong = 5,
		ExtremelyStrong = 6
	};

	enum Charisma
	{
		ExtremelyBoring = 0,
		FairlyBoring = 1,
		Boring = 2,
		AverageCharisma = 3,
		Charming = 4,
		FairlyCharming = 5,
		ExtremelyCharming = 6
	};

	enum Intelliegence
	{
		ExtremelyDumb = 0,
		FairlyDumb = 1,
		Dumb = 2,
		AverageIntelliegence = 3,
		Smart = 4,
		FairlySmart = 5,
		ExtremelySmart = 6
	};
};
