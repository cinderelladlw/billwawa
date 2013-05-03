#ifndef __TANK_H__
#define __TANK_H__

class TankState;
class SiegeState;
class ISiegeTankState;

class SiegeTank
{
public:
	SiegeTank();

	void enterTankMode();
	void enterSiegeMode();

public:
	void attack();
	void move(int x, int y);
	
private:
	void setState(ISiegeTankState* pSiegeTankMode);

private:
	TankState* m_pTankState;
	SiegeState* m_pSiegeState;
	ISiegeTankState* m_pSiegeTankState;
};
#endif

