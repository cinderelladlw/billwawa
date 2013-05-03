#include "tank.h"
#include "state.h"
#include <iostream>

SiegeState::SiegeState( SiegeTank* pTank ) : m_pTank(pTank)
{

}

void SiegeState::move( int x, int y )
{
	std::cout << "Can't move in siege mode." << std::endl;
}

void SiegeState::attack()
{
	std::cout << "Attacking for 100" << std::endl;
}


TankState::TankState( SiegeTank* pTank ) : m_pTank(pTank)
{

}

void TankState::move( int x, int y )
{
	std::cout << "Move to (" << x << ", " << y << ")" << std::endl;
}

void TankState::attack()
{
	std::cout << "Attacking for 20" << std::endl;
}

