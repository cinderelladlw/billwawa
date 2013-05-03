class SiegeTank;

class ISiegeTankState
{
public:
	virtual void move(int x, int y) = 0;
	virtual void attack() = 0;
};

class SiegeState : public ISiegeTankState
{
public:
	SiegeState(SiegeTank* pTank);

	virtual void move(int x, int y);

	virtual void attack();

private:
	SiegeTank* m_pTank;
};

class TankState : public ISiegeTankState
{
public:
	TankState(SiegeTank* pTank);

	virtual void move(int x, int y);

	virtual void attack();

private:
	SiegeTank* m_pTank;
};

