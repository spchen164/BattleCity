//��ͼ��
#pragma once

#include "Define.h"
#include "Block.h"
#include <string.h>
#include <fstream>
using namespace std;

class Map
{
public:
	Map();//Ĭ�Ϲ��캯��
	Map(int s);//���캯��
	~Map();//��������

	//���ݸ���
	void SetMap(int r, int c, int bt);//���µ�ͼ����
	void SetWallType(int w);//���ó�ǽ����

	//���ݻ�ȡ
	Block* GetMap(int r, int c);//��ͼ
	int GetStage(){ return stage; }//�ؿ�
	int GetWallType(){ return WallType; }//��ǽ����
private:
	Block* map[15][15];//��ͼ
	int stage;//�ؿ�
	int WallType;//��ǽ����
};