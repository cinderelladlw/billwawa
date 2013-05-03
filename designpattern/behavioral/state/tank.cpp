#include "tank.h"
#include "state.h"
#include <iostream>

SiegeTank::SiegeTank()
{
	m_pTankState = new TankState(this);
	m_pSiegeState = new SiegeState(this);
	m_pSiegeTankState = m_pTankState;
}

void SiegeTank::setState( ISiegeTankState* pSiegeTankMode )
{
	m_pSiegeTankState = pSiegeTankMode;
}

void SiegeTank::move( int x, int y )
{
	m_pSiegeTankState->move(x, y);
}

void SiegeTank::attack()
{
	m_pSiegeTankState->attack();
}

void SiegeTank::enterTankMode()
{
	m_pSiegeTankState = m_pTankState;
	std::cout << "Switch to tank mode" << std::endl;
}

void SiegeTank::enterSiegeMode()
{
	m_pSiegeTankState = m_pSiegeState;
	std::cout << "Switch to siege mode" << std::endl;
}

