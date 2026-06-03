#pragma once

// keeps track of how many hero classes have been created
 enum  class HeroClass : uint8_t
{
	PALADIN,
	MAGE,
	HEALER,
	NUM_CLASSES,
};

 size_t getSize();
 size_t optimalSizeForVector();