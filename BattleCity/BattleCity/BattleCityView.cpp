
// BattleCityView.cpp : CBattleCityView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BattleCity.h"
#endif

#include "BattleCityDoc.h"
#include "BattleCityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//全局变量
int EnemyLoop = 0;//控制延迟
int StopLoop = 0;//控制敌人停止运动的时间
bool stop = false;//敌人是否停止

// CBattleCityView

IMPLEMENT_DYNCREATE(CBattleCityView, CView)

BEGIN_MESSAGE_MAP(CBattleCityView, CView)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CBattleCityView 构造/析构

CBattleCityView::CBattleCityView()
{
	// TODO:  在此处添加构造代码
	srand((unsigned)time(0));//设置随机种子值

	//变量声明
	int p;
	int rk;
	CString temp;
	fstream file;

	//变量设置
	stage = 1;
	EnemyAppear = 1;
	EnemyCount = 20;
	status = GAME_DOING;

	//加载背景
	background = new CImage;
	Info = new CImage;
	rcInfo = new CRect;
	background->Load(TEXT(".\\res\\background\\background.png"));
	Info->Load(TEXT(".\\res\\background\\Info.png"));
	rcInfo->SetRect(GAME_WIDTH, 0, GAME_WIDTH + INFO_WIDTH, GAME_HEIGHT);

	//地图设置
	map = new Map(stage);

	//坦克设置
	Player = new Tank(THING_TANK, TEXT(".\\res\\tank\\player_level1_up.png"), 5 * BLOCK_LENGTH + 2, 14 * BLOCK_LENGTH + 2, 5 * BLOCK_LENGTH + 32 - 2, 14 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_PLAYER, TANK_LEVEL1, DIR_UP);
	EnemyFlag[0] = ENEMY_APPEAR;
	for (int i = 1; i < 20; i++)
		EnemyFlag[i] = ENEMY_HIDE;
	temp.Format(TEXT(".\\res\\enemy\\enemy%d.dat"), stage);//加载敌方坦克
	file.open(temp, ios::in);
	for (int i = 0; i < 20; i++)
	{
		file >> rk;
		temp.Format(TEXT(".\\res\\tank\\enemy_level%d_down.png"), rk);
		p = rand() % 3;
		if (p == 0)
			Enemy[i] = new Tank(THING_TANK, temp, 0 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 32 - 2, 0 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_ENEMY, rk, DIR_DOWN);
		else if (p == 2)
			Enemy[i] = new Tank(THING_TANK, temp, 7 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 2, 7 * BLOCK_LENGTH + 32 - 2, 0 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_ENEMY, rk, DIR_DOWN);
		else
			Enemy[i] = new Tank(THING_TANK, temp, 14 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 2, 14 * BLOCK_LENGTH + 32 - 2, 0 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_ENEMY, rk, DIR_DOWN);
	}

	//奖品设置
	Block *b = NULL;
	for (int r = 0; r < 13; r++)//最下面2行不设置奖品
	{
		for (int c = 0; c < 15; c++)
		{
			b = map->GetMap(r, c);
			if (b->GetIsReward() && b->GetBlockType() != BLOCK_TYPE_BLANK&&b->GetBlockType() != BLOCK_TYPE_GRASS)
			{
				int p = rand() % 4 + 70;
				switch (p)
				{
				case REWARD_TYPE_LEVELUP:temp.Format(TEXT(".\\res\\reward\\levelup.png")); break;
				case REWARD_TYPE_LIFEUP:temp.Format(TEXT(".\\res\\reward\\lifeup.png")); break;
				case REWARD_TYPE_STRENGTH:temp.Format(TEXT(".\\res\\reward\\strength.png")); break;
				case REWARD_TYPE_TIMESTOP:temp.Format(TEXT(".\\res\\reward\\timestop.png")); break;
				}
				reward.push_back(new Reward(THING_REWARD, temp, c*BLOCK_LENGTH, r*BLOCK_LENGTH, c*BLOCK_LENGTH + 32, r*BLOCK_LENGTH + 32, p));
			}
		}
	}
}

CBattleCityView::~CBattleCityView()
{
}

BOOL CBattleCityView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBattleCityView 绘制

void CBattleCityView::OnDraw(CDC* pDC)
{
	CBattleCityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	//实行双缓冲技术绘图防止闪烁
	CRect rc;
	GetClientRect(&rc);

	CImage memImg;
	memImg.Create(rc.Width(), rc.Height(), 24);//BPP(第3个参数)按主观设置
	HDC hdc = memImg.GetDC();

	//绘图开始
	background->Draw(hdc, rc);//游戏背景
	Info->Draw(hdc, *rcInfo);//游戏信息背景
	DrawGameInfo(hdc);//游戏信息
	DrawReward(hdc);//奖品
	DrawTank(hdc);//坦克
	DrawMap(hdc);//地图方块
	DrawBullet(hdc);//子弹
	if (status == GAME_FINISH)
	{
		CImage finish;
		finish.Load(TEXT(".\\res\\other\\game_over.png"));
		finish.Draw(hdc, 200, 220, finish.GetWidth(), finish.GetHeight());
	}
	//绘图结束

	memImg.Draw(pDC->m_hDC, rc);//绘图到窗口

	memImg.ReleaseDC();

	//设置定时器
	if (status == GAME_DOING)
		SetTimer(TIMER_PAINT, 10, NULL);
	if (EnemyAppear == 1)
		SetTimer(TIMER_ENEMY, 10, NULL);
	if (EnemyCount <= 0)
	{
		stage++;
		stage %= TOTAL_STAGE + 1;
		if (stage == 0)
			stage++;
		InitStage(stage);
	}
}


// CBattleCityView 诊断

#ifdef _DEBUG
void CBattleCityView::AssertValid() const
{
	CView::AssertValid();
}

void CBattleCityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBattleCityDoc* CBattleCityView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBattleCityDoc)));
	return (CBattleCityDoc*)m_pDocument;
}
#endif //_DEBUG


//自定义函数实现
void CBattleCityView::DrawTank(HDC hdc)//绘制坦克
{
	CImage *temp = NULL;
	if (Player != NULL)
	{
		temp = Player->GetPicture();
		temp->Draw(hdc, *(Player->GetRC()));
	}

	srand((unsigned)time(0));//设置随机种子值

	int dir = 0;
	CPoint BulletCenter;
	CRect *rc = NULL;

	for (int i = 0; i < 20; i++)
	{
		if (EnemyFlag[i] == ENEMY_APPEAR)
		{
			dir = Enemy[i]->GetDirect();
			rc = Enemy[i]->GetRC();
			temp = Enemy[i]->GetPicture();
			temp->Draw(hdc, *(rc));

			if (!stop)
			{
				switch (dir)
				{
				case DIR_UP:
					BulletCenter.x = (rc->left + rc->right) / 2;
					BulletCenter.y = (rc->top + rc->bottom) / 2 - (rc->Width() / 2 + BULLET_LENGTH / 2);
					break;
				case DIR_DOWN:
					BulletCenter.x = (rc->left + rc->right) / 2;
					BulletCenter.y = (rc->top + rc->bottom) / 2 + (rc->Width() / 2 + BULLET_LENGTH / 2);
					break;
				case DIR_LEFT:
					BulletCenter.x = (rc->left + rc->right) / 2 - (rc->Width() / 2 + BULLET_LENGTH / 2);
					BulletCenter.y = (rc->top + rc->bottom) / 2;
					break;
				case DIR_RIGHT:
					BulletCenter.x = (rc->left + rc->right) / 2 + (rc->Width() / 2 + BULLET_LENGTH / 2);
					BulletCenter.y = (rc->top + rc->bottom) / 2;
					break;
				}

				Enemy[i]->ShootBullet(THING_BULLET, TEXT(".\\res\\other\\bullet.png"), BulletCenter.x - BULLET_LENGTH / 2, BulletCenter.y - BULLET_LENGTH / 2, BulletCenter.x + BULLET_LENGTH / 2, BulletCenter.y + BULLET_LENGTH / 2);

				unsigned j = 0;
				for (j = 0; j < bullet.size(); j++)//判断子弹是否存在
				{
					if (bullet[j] == Enemy[i]->GetBullet())
						break;
				}
				if (Enemy[i]->GetBullet() != NULL&&j >= bullet.size())
					bullet.push_back(Enemy[i]->GetBullet());

				Enemy[i]->Move(this->m_hWnd, 0, map, Player);
			}//end stop
		}
	}
}

void CBattleCityView::DrawMap(HDC hdc)//绘制地图方块
{
	CImage *temp = NULL;
	Block *btemp = NULL;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			btemp = map->GetMap(i, j);
			temp = btemp->GetPicture();
			if (temp != NULL)
				temp->Draw(hdc, *(btemp->GetRC()));
		}
	}
}

void CBattleCityView::DrawReward(HDC hdc)//绘制奖品
{
	CImage *temp = NULL;
	for (unsigned i = 0; i < reward.size(); i++)
	{
		temp = reward[i]->GetPicture();
		temp->Draw(hdc, *(reward[i]->GetRC()));
	}
	if (stop)
		SetTimer(TIMER_TIMESTOP, 10, NULL);
}

void CBattleCityView::DrawBullet(HDC hdc)//绘制子弹
{
	CImage *temp = NULL;
	for (unsigned i = 0; i < bullet.size(); i++)
	{
		temp = bullet[i]->GetPicture();
		bullet[i]->Move();
		if (!IsBulletMeet(bullet[i]))
			temp->Draw(hdc, *(bullet[i]->GetRC()));
		else
			i--;
	}
}

void CBattleCityView::DrawGameInfo(HDC hdc)//绘制游戏信息
{
	SetBkColor(hdc, RGB(93, 95, 59));//设置文字背景色
	SetTextColor(hdc, RGB(255, 255, 255));//设置文字颜色

	CString temp;

	temp.Format(TEXT("Stage %d"), stage);
	TextOut(hdc, 545, 20, temp, temp.GetLength());

	temp.Format(TEXT("剩余敌人数：%d"), EnemyCount);
	TextOut(hdc, 515, 100, temp, temp.GetLength());

	temp.Format(TEXT("操作说明"));
	TextOut(hdc, 540, 220, temp, temp.GetLength());
	temp.Format(TEXT("w：上"));
	TextOut(hdc, 550, 245, temp, temp.GetLength());
	temp.Format(TEXT("s：下"));
	TextOut(hdc, 550, 270, temp, temp.GetLength());
	temp.Format(TEXT("a：左"));
	TextOut(hdc, 550, 295, temp, temp.GetLength());
	temp.Format(TEXT("d：右"));
	TextOut(hdc, 550, 320, temp, temp.GetLength());
	temp.Format(TEXT("j：开炮"));
	TextOut(hdc, 545, 345, temp, temp.GetLength());

	temp.Format(TEXT("剩余生命值：%d"), Player->GetLife());
	TextOut(hdc, 520, 440, temp, temp.GetLength());
}

bool CBattleCityView::IsBulletMeet(Bullet *b)//子弹是否与其它物品发生碰撞
{
	CRect *rc = NULL;
	Tank *t = NULL;
	Block *temp = NULL;
	vector<Bullet*>::iterator iter;

	rc = b->GetRC();
	t = b->GetFromTank();
	for (iter = bullet.begin(); iter < bullet.end(); iter++)//获取b在vector中的迭代器位置
	{
		if (*iter == b)
			break;
	}//end for

	//是否到达边界
	if (rc->left<0 || rc->right>GAME_WIDTH || rc->top<0 || rc->bottom>GAME_HEIGHT)
	{
		bullet.erase(iter);
		t->DestroyBullet();
		return true;
	}

	//是否与方块碰撞
	for (int r = 0; r < 15; r++)
	{
		for (int c = 0; c < 15; c++)
		{
			temp = map->GetMap(r, c);
			if (Thing::IsMeet(temp, b) && !temp->GetIsBullet())
			{
				if (t->GetRank() >= temp->GetRank())
				{
					if (temp->GetBlockType() == BLOCK_TYPE_BASE)
					{
						map->SetMap(r, c, BLOCK_TYPE_LOSE);
						KillTimer(TIMER_PAINT);
						status = GAME_FINISH;			//结束游戏
					}
					else
						map->SetMap(r, c, BLOCK_TYPE_BLANK);
				}
				bullet.erase(iter);
				t->DestroyBullet();
				return true;
			}//end if
		}
	}//end double for
	
	//是否与坦克碰撞
	if (t->GetTankType() == TANK_TYPE_PLAYER)
	{
		for (int i = 0; i < 20; i++)
		{
			if (EnemyFlag[i] == ENEMY_APPEAR && Thing::IsMeet(Enemy[i], b))
			{
				EnemyFlag[i] = ENEMY_BEATEN;
				bullet.erase(iter);
				t->DestroyBullet();
				if (EnemyCount > 0)
					EnemyCount--;
				return true;
			}
		}
	}
	else if (Thing::IsMeet(Player, b))
	{
		Player->SetRC(14, 5);
		if (Player->GetLife() > 0)
			Player->DecreaseLife();
		else
		{
			KillTimer(TIMER_PAINT);
			status = GAME_FINISH;
		}
		bullet.erase(iter);
		t->DestroyBullet();
		return true;
	}

	return false;
}

void CBattleCityView::InitStage(int s)//初始化关卡
{
	//清除上一关的资源
	background->ReleaseGDIPlus();
	Info->ReleaseGDIPlus();
	delete background;
	delete Info;
	delete rcInfo;
	for (int i = 0; i < 20; i++)
		delete Enemy[i];
	delete map;
	for (unsigned i = 0; i < reward.size(); i++)
		delete reward[i];
	reward.clear();
	for (unsigned i = 0; i < bullet.size(); i++)
		delete bullet[i];
	bullet.clear();

	//加载背景
	background = new CImage;
	Info = new CImage;
	rcInfo = new CRect;
	background->Load(TEXT(".\\res\\background\\background.png"));
	Info->Load(TEXT(".\\res\\background\\Info.png"));
	rcInfo->SetRect(GAME_WIDTH, 0, GAME_WIDTH + INFO_WIDTH, GAME_HEIGHT);

	//变量声明
	int p;
	int rk;
	CString temp;
	fstream file;

	//变量设置
	EnemyAppear = 1;
	EnemyCount = 20;
	status = GAME_DOING;

	//地图设置
	map = new Map(stage);

	//坦克设置
	Player->SetRC(14, 5);//回到原点
	EnemyFlag[0] = ENEMY_APPEAR;
	for (int i = 1; i < 20; i++)
		EnemyFlag[i] = ENEMY_HIDE;
	temp.Format(TEXT(".\\res\\enemy\\enemy%d.dat"), stage);//加载敌方坦克
	file.open(temp, ios::in);
	for (int i = 0; i < 20; i++)
	{
		file >> rk;
		temp.Format(TEXT(".\\res\\tank\\enemy_level%d_down.png"), rk);
		p = rand() % 3;
		if (p == 0)
			Enemy[i] = new Tank(THING_TANK, temp, 0 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 32 - 2, 0 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_ENEMY, rk, DIR_DOWN);
		else if (p == 2)
			Enemy[i] = new Tank(THING_TANK, temp, 7 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 2, 7 * BLOCK_LENGTH + 32 - 2, 0 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_ENEMY, rk, DIR_DOWN);
		else
			Enemy[i] = new Tank(THING_TANK, temp, 14 * BLOCK_LENGTH + 2, 0 * BLOCK_LENGTH + 2, 14 * BLOCK_LENGTH + 32 - 2, 0 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_ENEMY, rk, DIR_DOWN);
	}

	//奖品设置
	Block *b = NULL;
	for (int r = 0; r < 13; r++)//最下面2行不设置奖品
	{
		for (int c = 0; c < 15; c++)
		{
			b = map->GetMap(r, c);
			if (b->GetIsReward() && b->GetBlockType() != BLOCK_TYPE_BLANK&&b->GetBlockType() != BLOCK_TYPE_GRASS)
			{
				int p = rand() % 4 + 70;
				switch (p)
				{
				case REWARD_TYPE_LEVELUP:temp.Format(TEXT(".\\res\\reward\\levelup.png")); break;
				case REWARD_TYPE_LIFEUP:temp.Format(TEXT(".\\res\\reward\\lifeup.png")); break;
				case REWARD_TYPE_STRENGTH:temp.Format(TEXT(".\\res\\reward\\strength.png")); break;
				case REWARD_TYPE_TIMESTOP:temp.Format(TEXT(".\\res\\reward\\timestop.png")); break;
				}
				reward.push_back(new Reward(THING_REWARD, temp, c*BLOCK_LENGTH, r*BLOCK_LENGTH, c*BLOCK_LENGTH + 32, r*BLOCK_LENGTH + 32, p));
			}
		}
	}
}


// CBattleCityView 消息处理程序


void CBattleCityView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();

	switch (nIDEvent)
	{	
	case TIMER_PAINT:OnDraw(pDC); break;
	case TIMER_DIR_UP:
		Player->MoveUp(map, Enemy, EnemyFlag, reward);
		switch (Player->GetRank())
		{
		case TANK_LEVEL1:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level1_up.png"));
			break;
		case TANK_LEVEL2:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level2_up.png"));
			break;
		case TANK_LEVEL3:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level3_up.png"));
			break;
		}
		break;
	case TIMER_DIR_DOWN:
		Player->MoveDown(map, Enemy, EnemyFlag, reward);
		switch (Player->GetRank())
		{
		case TANK_LEVEL1:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level1_down.png"));
			break;
		case TANK_LEVEL2:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level2_down.png"));
			break;
		case TANK_LEVEL3:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level3_down.png"));
			break;
		}
		break;
	case TIMER_DIR_LEFT:
		Player->MoveLeft(map, Enemy, EnemyFlag, reward);
		switch (Player->GetRank())
		{
		case TANK_LEVEL1:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level1_left.png"));
			break;
		case TANK_LEVEL2:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level2_left.png"));
			break;
		case TANK_LEVEL3:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level3_left.png"));
			break;
		}
		break;
	case TIMER_DIR_RIGHT:
		Player->MoveRight(map, Enemy, EnemyFlag, reward);
		switch (Player->GetRank())
		{
		case TANK_LEVEL1:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level1_right.png"));
			break;
		case TANK_LEVEL2:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level2_right.png"));
			break;
		case TANK_LEVEL3:
			Player->SetPicture(TEXT(".\\res\\tank\\player_level3_right.png"));
			break;
		}
		break;
	case TIMER_ENEMY:
		if (EnemyLoop < 100)
		{
			EnemyLoop++;
			break;
		}
		EnemyLoop = 0;
		EnemyFlag[EnemyAppear] = ENEMY_APPEAR;
		EnemyAppear++;
		if (EnemyAppear >= 20)
			KillTimer(TIMER_ENEMY);
		break;
	case TIMER_TIMESTOP:
		if (StopLoop < 500)
		{
			StopLoop++;
			break;
		}
		StopLoop = 0;
		stop = false;
		KillTimer(TIMER_TIMESTOP);
		break;
	default:break;
	}

	ReleaseDC(pDC);

	CView::OnTimer(nIDEvent);
}


void CBattleCityView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int temp = 0;
	CRect *rc = NULL;
	CPoint BulletCenter;
	switch (nChar)
	{
	case 'j':
	case 'J':
		temp = Player->GetDirect();
		rc = Player->GetRC();
		switch (temp)
		{
		case DIR_UP:
			BulletCenter.x = (rc->left + rc->right) / 2;
			BulletCenter.y = (rc->top + rc->bottom) / 2 - (rc->Width() / 2 + BULLET_LENGTH / 2);
			break;
		case DIR_DOWN:
			BulletCenter.x = (rc->left + rc->right) / 2;
			BulletCenter.y = (rc->top + rc->bottom) / 2 + (rc->Width() / 2 + BULLET_LENGTH / 2);
			break;
		case DIR_LEFT:
			BulletCenter.x = (rc->left + rc->right) / 2 - (rc->Width() / 2 + BULLET_LENGTH / 2);
			BulletCenter.y = (rc->top + rc->bottom) / 2;
			break;
		case DIR_RIGHT:
			BulletCenter.x = (rc->left + rc->right) / 2 + (rc->Width() / 2 + BULLET_LENGTH / 2);
			BulletCenter.y = (rc->top + rc->bottom) / 2;
			break;
		}
		Player->ShootBullet(THING_BULLET, TEXT(".\\res\\other\\Bullet.png"), BulletCenter.x - BULLET_LENGTH / 2, BulletCenter.y - BULLET_LENGTH / 2, BulletCenter.x + BULLET_LENGTH / 2, BulletCenter.y + BULLET_LENGTH / 2);
		
		unsigned i;
		for (i = 0; i < bullet.size(); i++)//判断是否子弹存在
		{
			if (bullet[i] == Player->GetBullet())
				break;
		}
		if (i >= bullet.size())
			bullet.push_back(Player->GetBullet());
		break;
	default:
		Player->Move(this->m_hWnd, nChar, NULL, NULL);
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CBattleCityView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (Player != NULL)
		Player->Stop(this->m_hWnd, nChar);

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
