
// BattleCityView.cpp : CBattleCityView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BattleCity.h"
#endif

#include "BattleCityDoc.h"
#include "BattleCityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//ȫ�ֱ���
int EnemyLoop = 0;//�����ӳ�
int StopLoop = 0;//���Ƶ���ֹͣ�˶���ʱ��
bool stop = false;//�����Ƿ�ֹͣ

// CBattleCityView

IMPLEMENT_DYNCREATE(CBattleCityView, CView)

BEGIN_MESSAGE_MAP(CBattleCityView, CView)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CBattleCityView ����/����

CBattleCityView::CBattleCityView()
{
	// TODO:  �ڴ˴���ӹ������
	srand((unsigned)time(0));//�����������ֵ

	//��������
	int p;
	int rk;
	CString temp;
	fstream file;

	//��������
	stage = 1;
	EnemyAppear = 1;
	EnemyCount = 20;
	status = GAME_DOING;

	//���ر���
	background = new CImage;
	Info = new CImage;
	rcInfo = new CRect;
	background->Load(TEXT(".\\res\\background\\background.png"));
	Info->Load(TEXT(".\\res\\background\\Info.png"));
	rcInfo->SetRect(GAME_WIDTH, 0, GAME_WIDTH + INFO_WIDTH, GAME_HEIGHT);

	//��ͼ����
	map = new Map(stage);

	//̹������
	Player = new Tank(THING_TANK, TEXT(".\\res\\tank\\player_level1_up.png"), 5 * BLOCK_LENGTH + 2, 14 * BLOCK_LENGTH + 2, 5 * BLOCK_LENGTH + 32 - 2, 14 * BLOCK_LENGTH + 32 - 2, TANK_TYPE_PLAYER, TANK_LEVEL1, DIR_UP);
	EnemyFlag[0] = ENEMY_APPEAR;
	for (int i = 1; i < 20; i++)
		EnemyFlag[i] = ENEMY_HIDE;
	temp.Format(TEXT(".\\res\\enemy\\enemy%d.dat"), stage);//���صз�̹��
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

	//��Ʒ����
	Block *b = NULL;
	for (int r = 0; r < 13; r++)//������2�в����ý�Ʒ
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBattleCityView ����

void CBattleCityView::OnDraw(CDC* pDC)
{
	CBattleCityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

	//ʵ��˫���弼����ͼ��ֹ��˸
	CRect rc;
	GetClientRect(&rc);

	CImage memImg;
	memImg.Create(rc.Width(), rc.Height(), 24);//BPP(��3������)����������
	HDC hdc = memImg.GetDC();

	//��ͼ��ʼ
	background->Draw(hdc, rc);//��Ϸ����
	Info->Draw(hdc, *rcInfo);//��Ϸ��Ϣ����
	DrawGameInfo(hdc);//��Ϸ��Ϣ
	DrawReward(hdc);//��Ʒ
	DrawTank(hdc);//̹��
	DrawMap(hdc);//��ͼ����
	DrawBullet(hdc);//�ӵ�
	if (status == GAME_FINISH)
	{
		CImage finish;
		finish.Load(TEXT(".\\res\\other\\game_over.png"));
		finish.Draw(hdc, 200, 220, finish.GetWidth(), finish.GetHeight());
	}
	//��ͼ����

	memImg.Draw(pDC->m_hDC, rc);//��ͼ������

	memImg.ReleaseDC();

	//���ö�ʱ��
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


// CBattleCityView ���

#ifdef _DEBUG
void CBattleCityView::AssertValid() const
{
	CView::AssertValid();
}

void CBattleCityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBattleCityDoc* CBattleCityView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBattleCityDoc)));
	return (CBattleCityDoc*)m_pDocument;
}
#endif //_DEBUG


//�Զ��庯��ʵ��
void CBattleCityView::DrawTank(HDC hdc)//����̹��
{
	CImage *temp = NULL;
	if (Player != NULL)
	{
		temp = Player->GetPicture();
		temp->Draw(hdc, *(Player->GetRC()));
	}

	srand((unsigned)time(0));//�����������ֵ

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
				for (j = 0; j < bullet.size(); j++)//�ж��ӵ��Ƿ����
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

void CBattleCityView::DrawMap(HDC hdc)//���Ƶ�ͼ����
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

void CBattleCityView::DrawReward(HDC hdc)//���ƽ�Ʒ
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

void CBattleCityView::DrawBullet(HDC hdc)//�����ӵ�
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

void CBattleCityView::DrawGameInfo(HDC hdc)//������Ϸ��Ϣ
{
	SetBkColor(hdc, RGB(93, 95, 59));//�������ֱ���ɫ
	SetTextColor(hdc, RGB(255, 255, 255));//����������ɫ

	CString temp;

	temp.Format(TEXT("Stage %d"), stage);
	TextOut(hdc, 545, 20, temp, temp.GetLength());

	temp.Format(TEXT("ʣ���������%d"), EnemyCount);
	TextOut(hdc, 515, 100, temp, temp.GetLength());

	temp.Format(TEXT("����˵��"));
	TextOut(hdc, 540, 220, temp, temp.GetLength());
	temp.Format(TEXT("w����"));
	TextOut(hdc, 550, 245, temp, temp.GetLength());
	temp.Format(TEXT("s����"));
	TextOut(hdc, 550, 270, temp, temp.GetLength());
	temp.Format(TEXT("a����"));
	TextOut(hdc, 550, 295, temp, temp.GetLength());
	temp.Format(TEXT("d����"));
	TextOut(hdc, 550, 320, temp, temp.GetLength());
	temp.Format(TEXT("j������"));
	TextOut(hdc, 545, 345, temp, temp.GetLength());

	temp.Format(TEXT("ʣ������ֵ��%d"), Player->GetLife());
	TextOut(hdc, 520, 440, temp, temp.GetLength());
}

bool CBattleCityView::IsBulletMeet(Bullet *b)//�ӵ��Ƿ���������Ʒ������ײ
{
	CRect *rc = NULL;
	Tank *t = NULL;
	Block *temp = NULL;
	vector<Bullet*>::iterator iter;

	rc = b->GetRC();
	t = b->GetFromTank();
	for (iter = bullet.begin(); iter < bullet.end(); iter++)//��ȡb��vector�еĵ�����λ��
	{
		if (*iter == b)
			break;
	}//end for

	//�Ƿ񵽴�߽�
	if (rc->left<0 || rc->right>GAME_WIDTH || rc->top<0 || rc->bottom>GAME_HEIGHT)
	{
		bullet.erase(iter);
		t->DestroyBullet();
		return true;
	}

	//�Ƿ��뷽����ײ
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
						status = GAME_FINISH;			//������Ϸ
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
	
	//�Ƿ���̹����ײ
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

void CBattleCityView::InitStage(int s)//��ʼ���ؿ�
{
	//�����һ�ص���Դ
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

	//���ر���
	background = new CImage;
	Info = new CImage;
	rcInfo = new CRect;
	background->Load(TEXT(".\\res\\background\\background.png"));
	Info->Load(TEXT(".\\res\\background\\Info.png"));
	rcInfo->SetRect(GAME_WIDTH, 0, GAME_WIDTH + INFO_WIDTH, GAME_HEIGHT);

	//��������
	int p;
	int rk;
	CString temp;
	fstream file;

	//��������
	EnemyAppear = 1;
	EnemyCount = 20;
	status = GAME_DOING;

	//��ͼ����
	map = new Map(stage);

	//̹������
	Player->SetRC(14, 5);//�ص�ԭ��
	EnemyFlag[0] = ENEMY_APPEAR;
	for (int i = 1; i < 20; i++)
		EnemyFlag[i] = ENEMY_HIDE;
	temp.Format(TEXT(".\\res\\enemy\\enemy%d.dat"), stage);//���صз�̹��
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

	//��Ʒ����
	Block *b = NULL;
	for (int r = 0; r < 13; r++)//������2�в����ý�Ʒ
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


// CBattleCityView ��Ϣ�������


void CBattleCityView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		for (i = 0; i < bullet.size(); i++)//�ж��Ƿ��ӵ�����
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (Player != NULL)
		Player->Stop(this->m_hWnd, nChar);

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
