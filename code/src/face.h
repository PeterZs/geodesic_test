#ifndef _FACE_
#define _FACE_

#include <math.h>
#include "myvector.h"

class face 
{
public:

	int index_HE;
	double area;
	myvector normal;
	int is_non_obtuse; //�ǲ��Ƕ�������

	myvector gradientOfu; //�Ⱥ������ݶ�
	myvector gradientOfdis; //���뺯�����ݶ� 

	face(){}
	~face(){}
	
	face(int index_HE,double area,int is_non_obtuse,myvector normal):index_HE(index_HE),area(area),is_non_obtuse(is_non_obtuse),normal(normal){}
};
#endif