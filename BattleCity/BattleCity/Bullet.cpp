//�ӵ���ʵ��
#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()//Ĭ�Ϲ��캯��
{
	FromTank = NULL;
	source = TANK_TYPE_ENEMY;
	direct = DIR_UP;
	speed = BULLET_SPEED_SLOW;
}

//���캯��
Bullet::Bullet(int t, CString path, int x1, int y1, int x2, int y2, Tank *tk)
	:Thing(t, path, x1, y1, x2, y2)
{
	FromTank = tk;
	source = tk->GetTankType();
	direct = tk->GetDirect();
	switch (tk->GetRank())
	{
	case TANK_LEVEL1:speed = BULLET_SPEED_SLOW; break;
	case TANK_LEVEL2:speed = BULLET_SPEED_MEDIUM; break;
	case TANK_LEVEL3:speed = BULLET_SPEED_FAST; break;
	}
}

Bullet::~Bullet()//��������
{
	FromTank = NULL;
}

void Bullet::Move()//�ӵ��ƶ�
{
	Block *temp = NULL;

	switch (direct)
	{
	case DIR_UP:
		rc.top -= speed;
		rc.bottom -= speed;
		break;
	case DIR_DOWN:
		rc.top += speed;
		rc.bottom += speed;
		break;
	case DIR_LEFT:
		rc.left -= speed;
		rc.right -= speed;
		break;
	case DIR_RIGHT:
		rc.left += speed;
		rc.right += speed;
		break;
	}
}