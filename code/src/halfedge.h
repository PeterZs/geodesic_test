#ifndef _HALFEDGE_
#define _HALFEDGE_

#include <math.h>
#include "myvector.h"

class halfedge
{
public:

	int index_vertex_towards;
	int index_vertex_begin;
	int index_face;
	int index_nextHE;
	int index_prevHE;
	int index_oppHE;
	double angle_towards; //����������������ԵĽǵĽǶ�
	double angle_accompany; //�����������������ֱߵĽǶ�(��Ϊ����ʱ���Ų�)
	double area_accompany;  //�����������������ֱߵ����������
	double length; //�߳�
	myvector itself; //����

	
	~halfedge(){}

	halfedge(int index_vertex_towards,int index_vertex_begin,int index_face,int index_nextHE,int index_prevHE,int index_oppHE,double angle_towards,
		double angle_accompany,double area_accompany,double length,myvector itself):index_vertex_towards(index_vertex_towards),index_vertex_begin(index_vertex_begin),index_face(index_face),index_nextHE(index_nextHE),index_prevHE(index_prevHE),
			index_oppHE(index_oppHE),angle_towards(angle_towards),angle_accompany(angle_accompany),area_accompany(area_accompany),length(length),itself(itself){} //����һ���ߵĵڶ���halfedge����Ϊ��һ��halfedge�Ѿ��õ������Է���߳�ʼ�����ɵõ�
	
	
    halfedge(){}

	halfedge(int index_vertex_towards,int index_vertex_begin,int index_face,int index_nextHE,int index_prevHE,double angle_towards,double angle_accompany,
		double area_accompany,double length,myvector itself):index_vertex_towards(index_vertex_towards),index_vertex_begin(index_vertex_begin),index_face(index_face),index_nextHE(index_nextHE),index_prevHE(index_prevHE)
		,angle_towards(angle_towards),angle_accompany(angle_accompany),area_accompany(area_accompany),length(length),itself(itself){} //����һ���ߵĵ�һ��halfedge���޷�Ԥ֪�ڶ���halfedge�������ʳ�ʼ��ʱ������

};
#endif