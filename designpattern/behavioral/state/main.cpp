#include "tank.h"
#include "state.h"

int main()
{
	SiegeTank tank;

	tank.enterTankMode();
	tank.attack();
	tank.move(1, 1);

	tank.enterSiegeMode();
	tank.attack();
	tank.move(2, 2);

	tank.enterTankMode();
	tank.attack();
	tank.move(3, 3);

	return 0;
}

