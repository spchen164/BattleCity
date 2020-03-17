//��ͼ��ʵ��
#include "stdafx.h"
#include "Map.h"

Map::Map()//Ĭ�Ϲ��캯��
{
	for (int i = 0; i < 15; i++)
		memset(map[i], 0, sizeof(Block*) * 15);
	stage = 1;
	WallType = BLOCK_TYPE_WOOD;
}

Map::Map(int s)//���캯��
{
	stage = s;
	WallType = BLOCK_TYPE_WOOD;
	CString path;
	path.Format(TEXT(".\\res\\map\\map%d.dat"), s);
	
	fstream file(path, ios::in);//���ļ�

	int x1, y1, x2, y2, bt;
	CString bPath;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			x1 = j*BLOCK_LENGTH;
			y1 = i*BLOCK_LENGTH;
			x2 = x1 + BLOCK_LENGTH;
			y2 = y1 + BLOCK_LENGTH;
			file >> bt;
			switch (bt)
			{
			case BLOCK_TYPE_BLANK:
				bPath = "";
				break;
			case BLOCK_TYPE_WOOD:
				bPath.Format(TEXT(".\\res\\block\\wood.png"));
				break;
			case BLOCK_TYPE_IRON:
				bPath.Format(TEXT(".\\res\\block\\iron.png"));
				break;
			case BLOCK_TYPE_RIVER:
				bPath.Format(TEXT(".\\res\\block\\river.png"));
				break;
			case BLOCK_TYPE_GRASS:
				bPath.Format(TEXT(".\\res\\block\\grass.png"));
				break;
			case BLOCK_TYPE_BRICK:
				bPath.Format(TEXT(".\\res\\block\\brick.png"));
				break;
			case BLOCK_TYPE_BASE:
				bPath.Format(TEXT(".\\res\\block\\base.png"));
				break;
			case BLOCK_TYPE_LOSE:
				bPath.Format(TEXT(".\\res\\block\\lose.png"));
				break;
			default:
				break;
			}//end switch
			map[i][j] = new Block(THING_BLOCK, bPath, x1, y1, x2, y2, bt);
		}
	}
	file.close();//�ر��ļ�
}

Map::~Map()//��������
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			delete map[i][j];
	}
}

void Map::SetMap(int r, int c, int bt)//���µ�ͼ����
{
	delete map[r][c];
	int x1 = c*BLOCK_LENGTH;
	int y1 = r*BLOCK_LENGTH;
	int x2 = x1 + BLOCK_LENGTH;
	int y2 = y1 + BLOCK_LENGTH;
	CString path;
	switch (bt)
	{
	case BLOCK_TYPE_BLANK:
		path.Format(TEXT(""));
		break;
	case BLOCK_TYPE_WOOD:
		path.Format(TEXT(".\\res\\block\\wood.png"));
		break;
	case BLOCK_TYPE_IRON:
		path.Format(TEXT(".\\res\\block\\iron.png"));
		break;
	case BLOCK_TYPE_RIVER:
		path.Format(TEXT(".\\res\\block\\river.png"));
		break;
	case BLOCK_TYPE_GRASS:
		path.Format(TEXT(".\\res\\block\\grass.png"));
		break;
	case BLOCK_TYPE_BRICK:
		path.Format(TEXT(".\\res\\block\\brick.png"));
		break;
	case BLOCK_TYPE_BASE:
		path.Format(TEXT(".\\res\\block\\base.png"));
		break;
	case BLOCK_TYPE_LOSE:
		path.Format(TEXT(".\\res\\block\\lose.png"));
		break;
	default:
		break;
	}
	map[r][c] = new Block(THING_BLOCK, path, x1, y1, x2, y2, bt);
}

void Map::SetWallType(int w)//���ó�ǽ����
{
	WallType = w;
}

Block* Map::GetMap(int r, int c)//��ȡ��ͼ
{
	if (r < 0 || r >= 15 || c < 0 || c >= 15)
		return NULL;
	else
		return map[r][c];
}