#include <iostream>

int main()
{
	uint64_t x = 5; 

	for (uint8_t i = 0; i < 64; ++i)
	{
		uint64_t y = 1;
		y = y << i;
		if ((x & y))
		{
			std::cout << i << '\n';
		}
	}
	



	return 0;
}