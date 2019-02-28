#ifndef _VERTEX_
#define _VERTEX_

#include <math.h>
#include "myvector.h"
class vertex
{
public:
	myvector location;
	myvector normal;
	int index_HE_towards; //ָ���һ��halfedge������
	double area_mixed; //one ring ��Ļ�������������

	double u0; //��ʼ�Ⱥ���ֵ
	double ut; //tʱ�����Ⱥ���ֵ
	double divergence; //ɢ��ֵ
	double valueOfdis; //���뺯��ֵ
	vertex();
	vertex(myvector location);
	~vertex();
};

#endif