#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "vertex.h"
using namespace std;

vertex::vertex()
{
	;
}

vertex::vertex(myvector location)
{
	this->location=location;
	index_HE_towards=-1; //-1��ʾ��û���ҵ�һ�����������
}

vertex::~vertex()
{
	;
}
