//坦克类实现
#include "stdafx.h"
#include "Tank.h"

Tank::Tank()//默认构造函数
{
	life = 2;
	TankType = TANK_TYPE_ENEMY;
	rank = TANK_LEVEL1;
	speed = TANK_SPEED_SLOW;
	direct = DIR_UP;
	bullet = NULL;
}

//构造函数
Tank::Tank(int thingt, CString path, int x1, int y1, int x2, int y2, int tankt, int r, int d)
	:Thing(thingt, path, x1, y1, x2, y2)
{
	TankType = tankt;
	if (tankt == TANK_TYPE_PLAYER)
		life = 2;
	else
		life = 1;
	rank = r;
	switch (r)
	{
	case TANK_LEVEL1:speed = TANK_SPEED_SLOW; break;
	case TANK_LEVEL2:speed = TANK_SPEED_MEDIUM; break;
	case TANK_LEVEL3:speed = TANK_SPEED_FAST; break;
	}
	direct = d;
	bullet = NULL;
}

Tank::~Tank()//析构函数
{
	delete bullet;
}

void Tank::Move(HWND hWnd, UINT nChar, Map *m, Tank *t)//移动函数
{
	if (TankType == TANK_TYPE_PLAYER)
	{
		switch (nChar)
		{
		case 'w':
		case 'W':
			direct = DIR_UP;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\player_level1_up.png"));
			else if (rank == TANK_LEVEL2)
				SetPicture(TEXT(".\\res\\tank\\player_level2_up.png"));
			else if (rank == TANK_LEVEL3)
				SetPicture(TEXT(".\\res\\tank\\player_level3_up.png"));
			SetTimer(hWnd, TIMER_DIR_UP, 10, NULL);
			break;
		case 'a':
		case 'A':
			direct = DIR_LEFT;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\player_level1_left.png"));
			else if (rank == TANK_LEVEL2)
				SetPicture(TEXT(".\\res\\tank\\player_level2_left.png"));
			else if (rank == TANK_LEVEL3)
				SetPicture(TEXT(".\\res\\tank\\player_level3_left.png"));
			SetTimer(hWnd, TIMER_DIR_LEFT, 10, NULL);
			break;
		case 's':
		case 'S':
			direct = DIR_DOWN;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\player_level1_down.png"));
			else if (rank == TANK_LEVEL2)
				SetPicture(TEXT(".\\res\\tank\\player_level2_down.png"));
			else if (rank == TANK_LEVEL3)
				SetPicture(TEXT(".\\res\\tank\\player_level3_down.png"));
			SetTimer(hWnd, TIMER_DIR_DOWN, 10, NULL);
			break;
		case 'd':
		case 'D':
			direct = DIR_RIGHT;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\player_level1_right.png"));
			else if (rank == TANK_LEVEL2)
				SetPicture(TEXT(".\\res\\tank\\player_level2_right.png"));
			else if (rank == TANK_LEVEL3)
				SetPicture(TEXT(".\\res\\tank\\player_level3_right.png"));
			SetTimer(hWnd, TIMER_DIR_RIGHT, 10, NULL);
			break;
		}
	}
	else
	{
		int p = rand() % 4;
		Block *temp = NULL;

		if (p == 0)		//上
		{
			direct = DIR_UP;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\enemy_level1_up.png"));
			else if (rank == TANK_LEVEL2)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level2_up.png"));
			else if (rank == TANK_LEVEL3)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level3_up.png"));

			rc.top -= speed;
			rc.bottom -= speed;

			//判断是否与方块碰撞
			for (int r = 0; r < 15; r++)
			{
				int c;
				for (c = 0; c < 15; c++)
				{
					temp = m->GetMap(r, c);
					if (temp == NULL)
						break;
					if ((rc.top < 0) || (IsMeet(this, temp) && !temp->GetIsTank()))
					{
						rc.top += speed;
						rc.bottom += speed;
						break;
					}
				}
				if (c < 15)
					break;
			}//end double for

			//判断是否与玩家坦克碰撞
			if (IsMeet(this, t))
			{
				rc.top += speed;
				rc.bottom += speed;
			}
		}
		else if (p == 1)	//下
		{
			direct = DIR_DOWN;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\enemy_level1_down.png"));
			else if (rank == TANK_LEVEL2)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level2_down.png"));
			else if (rank == TANK_LEVEL3)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level3_down.png"));

			rc.top += speed;
			rc.bottom += speed;

			//判断是否与方块碰撞
			for (int r = 0; r < 15; r++)
			{
				int c;
				for (c = 0; c < 15; c++)
				{
					temp = m->GetMap(r, c);
					if (temp == NULL)
						break;
					if ((rc.bottom > GAME_HEIGHT) || (IsMeet(this, temp) && !temp->GetIsTank()))
					{
						rc.top -= speed;
						rc.bottom -= speed;
						break;
					}
				}
				if (c < 15)
					break;
			}//end double for

			//判断是否与玩家坦克碰撞
			if (IsMeet(this, t))
			{
				rc.top -= speed;
				rc.bottom -= speed;
			}
		}
		else if (p == 2)	//左
		{
			direct = DIR_LEFT;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\enemy_level1_left.png"));
			else if (rank == TANK_LEVEL2)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level2_left.png"));
			else if (rank == TANK_LEVEL3)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level3_left.png"));

			rc.left -= speed; 
			rc.right -= speed;

			//判断是否与方块碰撞
			for (int r = 0; r < 15; r++)
			{
				int c;
				for (c = 0; c < 15; c++)
				{
					temp = m->GetMap(r, c);
					if (temp == NULL)
						break;
					if ((rc.left < 0) || (IsMeet(this, temp) && !temp->GetIsTank()))
					{
						rc.left += speed;
						rc.right += speed;
						break;
					}
				}
				if (c < 15)
					break;
			}//end double for

			//判断是否与玩家坦克碰撞
			if (IsMeet(this, t))
			{
				rc.left += speed;
				rc.right += speed;
			}
		}
		else				//右
		{
			direct = DIR_RIGHT;
			if (rank == TANK_LEVEL1)
				SetPicture(TEXT(".\\res\\tank\\enemy_level1_right.png"));
			else if (rank == TANK_LEVEL2)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level2_right.png"));
			else if (rank == TANK_LEVEL3)					
				SetPicture(TEXT(".\\res\\tank\\enemy_level3_right.png"));

			rc.left += speed;
			rc.right += speed;

			//判断是否与方块碰撞
			for (int r = 0; r < 15; r++)
			{
				int c;
				for (c = 0; c < 15; c++)
				{
					temp = m->GetMap(r, c);
					if (temp == NULL)
						break;
					if ((rc.right > GAME_WIDTH) || (IsMeet(this, temp) && !temp->GetIsTank()))
					{
						rc.left -= speed;
						rc.right -= speed;
						break;
					}
				}
				if (c < 15)
					break;
			}//end double for

			//判断是否与玩家坦克碰撞
			if (IsMeet(this, t))
			{
				rc.left -= speed;
				rc.right -= speed;
			}
		}//end if-else


	}
}

void Tank::Stop(HWND hWnd, UINT nChar)//停止移动函数
{
	switch (nChar)
	{
	case 'w':
	case 'W':
		KillTimer(hWnd, TIMER_DIR_UP);
		break;
	case 'a':
	case 'A':
		KillTimer(hWnd, TIMER_DIR_LEFT);
		break;
	case 's':
	case 'S':
		KillTimer(hWnd, TIMER_DIR_DOWN);
		break;
	case 'd':
	case 'D':
		KillTimer(hWnd, TIMER_DIR_RIGHT);
		break;
	}
}

void Tank::ShootBullet(int t, CString path, int x1, int y1, int x2, int y2)//发射子弹
{		
	if (bullet == NULL)
	{
		if (TankType == TANK_TYPE_ENEMY)//敌人有一定概率开炮
		{
			double p = (double)rand() / RAND_MAX;
			if (p > 0.3)
				return;
		}

		bullet = new Bullet(t, path, x1, y1, x2, y2, this);
	}
}

void Tank::DestroyBullet()//销毁子弹
{
	delete bullet;
	bullet = NULL;
}

void Tank::ImproveLife()//增加生命数
{
	life++;
}

void Tank::DecreaseLife()//减少生命数
{
	life--;
}

void Tank::ImproveRank()//提升等级
{
	if (rank < TANK_LEVEL3)
		rank++;
	switch (rank)
	{
	case TANK_LEVEL2:
		speed = TANK_SPEED_MEDIUM;
		break;
	case TANK_LEVEL3:
		speed = TANK_SPEED_FAST;
		break;
	}
}

void Tank::SetRC(int r, int c)//设置位置
{
	rc.left = c*BLOCK_LENGTH + 2;
	rc.top = r*BLOCK_LENGTH + 2;
	rc.right = c*BLOCK_LENGTH + BLOCK_LENGTH - 2;
	rc.bottom = r*BLOCK_LENGTH + BLOCK_LENGTH - 2;
}

void Tank::MoveUp(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward)
{
	Block *temp = NULL;
	
	direct = DIR_UP;
	rc.top -= speed;
	rc.bottom -= speed;

	//判断是否与方块碰撞
	for (int r = 0; r < 15; r++)
	{
		int c;
		for (c = 0; c < 15; c++)
		{
			temp = m->GetMap(r, c);
			if (temp == NULL)
				break;
			if ((rc.top < 0) || (IsMeet(this, temp) && !temp->GetIsTank()))
			{
				rc.top += speed;
				rc.bottom += speed;
				break;
			}
		}
		if (c < 15)
			break;
	}//end double for

	//判断是否与其他坦克碰撞
	for (int i = 0; i < 20; i++)
	{
		if (EnemyFlag[i] == ENEMY_APPEAR && IsMeet(this,t[i]))
		{
				rc.top += speed;
				rc.bottom += speed;
				break;
		}
	}

	//判断是否与奖品碰撞
	vector<Reward*>::iterator iter;
	for (iter = reward.begin(); iter < reward.end(); iter++)
	{
		if (IsMeet(this, *iter))
		{
			(*iter)->Improve(*this, m);
			reward.erase(iter);
			break;
		}
	}

}

void Tank::MoveDown(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward)
{
	Block *temp = NULL;
	
	direct = DIR_DOWN;
	rc.top += speed;
	rc.bottom += speed;

	//判断是否与方块碰撞
	for (int r = 0; r < 15; r++)
	{
		int c;
		for (c = 0; c < 15; c++)
		{
			temp = m->GetMap(r, c);
			if (temp == NULL)
				break;
			if ((rc.bottom > GAME_HEIGHT) || (IsMeet(this, temp) && !temp->GetIsTank()))
			{
				rc.top -= speed;
				rc.bottom -= speed;
				break;
			}
		}
		if (c < 15)
			break;
	}//end double for

	//判断是否与其他坦克碰撞
	for (int i = 0; i < 20; i++)
	{
		if (EnemyFlag[i] == ENEMY_APPEAR && IsMeet(this, t[i]))
		{
			rc.top -= speed;
			rc.bottom -= speed;
			break;
		}
	}

	//判断是否与奖品碰撞
	vector<Reward*>::iterator iter;
	for (iter = reward.begin(); iter < reward.end(); iter++)
	{
		if (IsMeet(this, *iter))
		{
			(*iter)->Improve(*this, m);
			reward.erase(iter);
			break;
		}
	}

}

void Tank::MoveLeft(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward)
{
	Block *temp = NULL;

	direct = DIR_LEFT;
	rc.left -= speed;
	rc.right -= speed;

	//判断是否与方块碰撞
	for (int r = 0; r < 15; r++)
	{
		int c;
		for (c = 0; c < 15; c++)
		{
			temp = m->GetMap(r, c);
			if (temp == NULL)
				break;
			if ((rc.left < 0) || (IsMeet(this, temp) && !temp->GetIsTank()))
			{
				rc.left += speed;
				rc.right += speed;
				break;
			}
		}
		if (c < 15)
			break;
	}//end double for

	//判断是否与其他坦克碰撞
	for (int i = 0; i < 20; i++)
	{
		if (EnemyFlag[i] == ENEMY_APPEAR && IsMeet(this, t[i]))
		{
			rc.left += speed;
			rc.right += speed;
			break;
		}
	}

	//判断是否与奖品碰撞
	vector<Reward*>::iterator iter;
	for (iter = reward.begin(); iter < reward.end(); iter++)
	{
		if (IsMeet(this, *iter))
		{
			(*iter)->Improve(*this, m);
			reward.erase(iter);
			break;
		}
	}

}

void Tank::MoveRight(Map *m, Tank **t, int *EnemyFlag, vector<Reward*> &reward)
{
	Block *temp = NULL;

	direct = DIR_RIGHT;
	rc.left += speed;
	rc.right += speed;

	//判断是否与方块碰撞
	for (int r = 0; r < 15; r++)
	{
		int c;
		for (c = 0; c < 15; c++)
		{
			temp = m->GetMap(r, c);
			if (temp == NULL)
				break;
			if ((rc.right > GAME_WIDTH) || (IsMeet(this, temp) && !temp->GetIsTank()))
			{
				rc.left -= speed;
				rc.right -= speed;
				break;
			}
		}
		if (c < 15)
			break;
	}//end double for

	//判断是否与其他坦克碰撞
	for (int i = 0; i < 20; i++)
	{
		if (EnemyFlag[i] == ENEMY_APPEAR && IsMeet(this, t[i]))
		{
			rc.left -= speed;
			rc.right -= speed;
			break;
		}
	}

	//判断是否与奖品碰撞
	vector<Reward*>::iterator iter;
	for (iter = reward.begin(); iter < reward.end();iter++)
	{
		if (IsMeet(this, *iter))
		{
			(*iter)->Improve(*this, m);
			reward.erase(iter);
			break;
		}
	}

}
