#pragma once

class costAreaPair
{
public:
    int cost, area;

	costAreaPair()
	{
		cost = 0;
		area = 0;
	}

	costAreaPair(int a, int c)
	{
		cost = c;
		area = a;
	}
};

