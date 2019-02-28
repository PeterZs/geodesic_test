#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <GL/glut.h>
#include <vector>

#include </usr/include/eigen3/Eigen/Eigen>
#include </usr/include/eigen3/Eigen/Dense>
#include </usr/include/eigen3/Eigen/Cholesky>
#include </usr/include/eigen3/Eigen/LU>
#include </usr/include/eigen3/Eigen/Sparse>
#include </usr/include/eigen3/Eigen/SparseQR>
#include </usr/include/eigen3/Eigen/SparseLU>
#include </usr/include/eigen3/Eigen/IterativeLinearSolvers>

#include "object.h"
#include "physic.h"

using namespace std;
using namespace Eigen;

#define pi 3.1415926535898
#define min(a,b) (((a) < (b)) ? (a) : (b))
object::object()
{
	getObjData();
	calNormal();
        getIsoline();
}

object::~object()
{
	
}


void object::getIsoline()
{
	int i,j;
        int step_now;
	double step_len=(disMax-disMin)/20.00000001;
	double isovalue_now=disMin;
	int onlyone; //��ֵ�ߴ�������������Ψһһ�����ڵ� ���� Ψһһ��С�ڵ�
	int sum;
	myvector loc_now[3]; //��ǰ�����ε��������궥���λ��
	double valueOfdis[3]; //��ǰ�����ε���������ľ��뺯����ֵ
	myvector begin_loc,end_loc; //isoline�Ŀ�ʼ��ͽ�����

       for(step_now=1;step_now<=20;step_now++)
       {    
          isovalue_now+=step_len;
     for(i=0;i<num_face;i++)
	{
		sum=0;
		testface testface_now=mytestfaces[i];
		for(j=0;j<3;j++)
		{
			if(myvertexs[testface_now.index_vertex[j]].valueOfdis<=isovalue_now)
			{
				sum+=0;
			}
			else
			{
				sum+=1;
			}
		}
		if(sum==1||sum==2)
		{
			for(j=0;j<3;j++)
			{
				loc_now[j]=myvertexs[testface_now.index_vertex[j]].location;
				valueOfdis[j]=myvertexs[testface_now.index_vertex[j]].valueOfdis;
			}
			if(sum==1)
			{
				for(j=0;j<3;j++)
				{
					if(myvertexs[testface_now.index_vertex[j]].valueOfdis>isovalue_now)
					{
						onlyone=j;
					}
				}
			}
			else if(sum==2)
			{
				for(j=0;j<3;j++)
				{
					if(myvertexs[testface_now.index_vertex[j]].valueOfdis<=isovalue_now)
					{
						onlyone=j;
					}
				}
			}
			if(onlyone!=0)
			{
				myvector change=loc_now[0];
				loc_now[0]=loc_now[onlyone];
				loc_now[onlyone]=change;

				double vch=valueOfdis[0];
				valueOfdis[0]=valueOfdis[onlyone];
				valueOfdis[onlyone]=vch;
			}
			//���Բ�ֵ
	        //P=P1+(isovalueһV1)(P2һP1)/(V2һV1) 
			begin_loc=loc_now[0]+(isovalue_now-valueOfdis[0])/(valueOfdis[1]-valueOfdis[0])*(loc_now[1]-loc_now[0]);
			end_loc=loc_now[0]+(isovalue_now-valueOfdis[0])/(valueOfdis[2]-valueOfdis[0])*(loc_now[2]-loc_now[0]);
			myisolines.push_back(isoline(begin_loc,end_loc));
			
		}	
	}

     }
	
}


void  object::testdraw()
{
	int i;
	int siz=mytestfaces.size();
	testface now;
	glColor3d(0,1,1);
	for(i=0;i<siz;i++)
	{
		now=mytestfaces[i];
		glBegin(GL_POLYGON);
		{
			glVertex3d(myvertexs[now.index_vertex[0]].location.x,myvertexs[now.index_vertex[0]].location.y,myvertexs[now.index_vertex[0]].location.z);
			glVertex3d(myvertexs[now.index_vertex[1]].location.x,myvertexs[now.index_vertex[1]].location.y,myvertexs[now.index_vertex[1]].location.z);
			glVertex3d(myvertexs[now.index_vertex[2]].location.x,myvertexs[now.index_vertex[2]].location.y,myvertexs[now.index_vertex[2]].location.z);
		}
		glEnd();
	}
}

void object::drawwithNormal()
{
        drawIsoline();  
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 2.0f); 
	int i,j;
	int key[3];
	int siz=mytestfaces.size();
	testface now;
	glColor3d(0.8,0.8,0.8);
	for(i=0;i<siz;i++)
	{
		now=mytestfaces[i];

		for(j=0;j<3;j++)
		{
			key[j]=floor((myvertexs[now.index_vertex[j]].valueOfdis-disMin)/(disMax-disMin)*7.0);
		}
		
		glBegin(GL_TRIANGLES);
		{
			glColor3dv(physic::color[key[0]]);
			glNormal3d(myvertexs[now.index_vertex[0]].normal.x,myvertexs[now.index_vertex[0]].normal.y,myvertexs[now.index_vertex[0]].normal.z);
			glVertex3d(myvertexs[now.index_vertex[0]].location.x,myvertexs[now.index_vertex[0]].location.y,myvertexs[now.index_vertex[0]].location.z);
			
			glColor3dv(physic::color[key[1]]);
			glNormal3d(myvertexs[now.index_vertex[1]].normal.x,myvertexs[now.index_vertex[1]].normal.y,myvertexs[now.index_vertex[1]].normal.z);
			glVertex3d(myvertexs[now.index_vertex[1]].location.x,myvertexs[now.index_vertex[1]].location.y,myvertexs[now.index_vertex[1]].location.z);
			
			glColor3dv(physic::color[key[2]]);
			glNormal3d(myvertexs[now.index_vertex[2]].normal.x,myvertexs[now.index_vertex[2]].normal.y,myvertexs[now.index_vertex[2]].normal.z);
			glVertex3d(myvertexs[now.index_vertex[2]].location.x,myvertexs[now.index_vertex[2]].location.y,myvertexs[now.index_vertex[2]].location.z);
		}
		glEnd();
	}

        glDisable(GL_POLYGON_OFFSET_FILL);

        
        
}

void object::drawIsoline()
{
	int i;
	int siz=myisolines.size();
	glColor3d(0,0,0);
	for(i=0;i<siz;i++)
	{
		glBegin(GL_LINES);
		{
			glVertex3d(myisolines[i].begin_loc.x,myisolines[i].begin_loc.y,myisolines[i].begin_loc.z);
			glVertex3d(myisolines[i].end_loc.x,myisolines[i].end_loc.y,myisolines[i].end_loc.z);
		}
		glEnd();
	}

}

int object::calData(int index[3],double data[3][3],double &area,myvector &normal) //�Ƕ� 0����Ҫ����� 1���߳� 2
{
	int i;
	myvector here[3];
	int one,two;
	for(i=0;i<3;i++)
	{
		one=index[i%3]; two=index[(i+1)%3];
		here[i]=myvector(myvertexs[two].location-myvertexs[one].location);
		data[i][2]=here[i].len();
	}

	normal=here[0].cross(here[1]);
	normal.normalize();

	double cosData[3];
	int returnValue;
	for(i=0;i<3;i++)
	{
		cosData[i]=here[i].dot(here[(i+2)%3]*-1)/here[i].len()/here[(i+2)%3].len();
		data[i][0]=acos(cosData[i]); //������
	}
	if(cosData[0]>=0&&cosData[1]>=0&&cosData[2]>=0)
	{
		returnValue=1;
	}
	else
	{
		returnValue=0;
	}
	
	if(returnValue==1)
	{
		for(i=0;i<3;i++)
		{
			data[i][1]=(here[i].len_sq()/tan(data[(i+2)%3][0])+here[(i+2)%3].len_sq()/tan(data[(i+4)%3][0]))/8.0;
		}
	}
	else
	{
		;
	}
	//�����ؾ��ع�ʽ
	double p=(data[0][2]+data[1][2]+data[2][2])/2.0;
	area=sqrtf(p*(p-data[0][2])*(p-data[1][2])*(p-data[2][2]));
	
	return returnValue;
}

void object::getObjData()
{

	string name="/home/wtyatzoo/project/model/torus.txt";
	FILE* file=fopen(name.c_str(),"r");
	fscanf(file,"%d%d",&num_vertex,&num_face);
	printf("%d %d \n",num_vertex,num_face);
	
	int i,j;
	double x,y,z;
	vertex here;
	char  filter[5];
	for(i=0;i<num_vertex;i++)
	{
		fscanf(file,"%s%lf%lf%lf",filter,&x,&y,&z);
		myvertexs.push_back(vertex(myvector(x,y,z)));
	}
	
	printf("%lf %lf %lf \n",x,y,z);
	
	map<pair<int,int >,int > mp1,mp2,mp3;
	map<pair<int,int >,int > ::iterator it;
	int index[3];
	int one,two,help;
	int mark;
	int is;
	
	double data[3][3]; //ÿһ���������������һ���������һ����ʱ��Χ�Ƶ������������ֱߵĽǶȣ���Ҫ����� ���߳� 
	double area; //��ǰ����������ε����
	myvector normal;

	for(i=0;i<num_face;i++)
	{
		fscanf(file,"%s%d%d%d",filter,&index[0],&index[1],&index[2]);
		for(j=0;j<3;j++)
		{
			index[j]--;
		}
		
		is=calData(index,data,area,normal);

		int siz_begin=myhalfedges.size(); //����ѭ����ʼ��size

		myfaces.push_back(face(siz_begin,area,is,normal));
		mytestfaces.push_back(testface(index[0],index[1],index[2]));
		
		myvector itself; //���浱ǰhalfedge��������ʽ

		
		for(j=0;j<3;j++)
		{
			one=index[j%3]; two=index[(j+1)%3]; //��ǰ�����halfedge�������յ�
			itself=myvertexs[two].location-myvertexs[one].location;
			if(myvertexs[one].index_HE_towards==-1)
			{
				myvertexs[one].index_HE_towards=siz_begin+j;
			}
			else
			{
				;
			}
			
			if(one<two)
			{
				mark=1;
			}
			else
			{
				help=one; one=two; two=help;
				mark=-1;
			}
			int siz=myhalfedges.size(); //��ǰhalfedge��Ŀ�����ǵ�ǰ�����halfedge������
			if(mp1.find(make_pair(one,two))==mp1.end())
			{	
				if(mark==1)
				{
					mp1[make_pair(one,two)]=1;
					mp2[make_pair(one,two)]=siz; //��������halfedge�������ţ����䷴���halfedge����ʱ������ϵ
					myhalfedges.push_back(halfedge(two,one,i,siz_begin+(j+1)%3,siz_begin+((j-1)%3+3)%3,data[(j+2)%3][0],data[j][0],data[j][1],data[j][2],itself));
                    
				}
				else if(mark==-1)
				{
					mp1[make_pair(one,two)]=-1;  
					mp2[make_pair(one,two)]=siz; //��������halfedge�������ţ����䷴���halfedge����ʱ������ϵ
					myhalfedges.push_back(halfedge(one,two,i,siz_begin+(j+1)%3,siz_begin+((j-1)%3+3)%3,data[(j+2)%3][0],data[j][0],data[j][1],data[j][2],itself));
				}
				
			}
			else if(mp1[make_pair(one,two)]==1||mp1[make_pair(one,two)]==-1)
			{
				int key=mp1[make_pair(one,two)];
				if(key==1||key==-1)
				{
					int oppHE=mp2[make_pair(one,two)];
					myhalfedges[oppHE].index_oppHE=siz;
					
					if(mark==1)
					{
						myhalfedges.push_back(halfedge(two,one,i,siz_begin+(j+1)%3,siz_begin+((j-1)%3+3)%3,oppHE,data[(j+2)%3][0],data[j][0],data[j][1],data[j][2],itself));
						mp1[make_pair(one,two)]=2;
					}
					else if(mark==-1)
					{
						myhalfedges.push_back(halfedge(one,two,i,siz_begin+(j+1)%3,siz_begin+((j-1)%3+3)%3,oppHE,data[(j+2)%3][0],data[j][0],data[j][1],data[j][2],itself));
						mp1[make_pair(one,two)]=2;  
					}
				}
			}
		}
		
	}

	//����ƽ��������t
	int siz=myhalfedges.size();
	num_halfedge=siz; 
	double sumofLen=0.0;
	for(i=0;i<siz;i++)
	{
		sumofLen+=((halfedge)myhalfedges[i]).length;
	}
	double h=sumofLen/num_halfedge;
	t=h*h;
	printf("siz %d sum %.2lf t %lf\n",siz,sumofLen,t);


	//�Ⱥ�����ֵ ��0��face��u0��Ϊ1��ʣ�����Ϊ0����ʾ���ɴ˴���ɢ 
	
	for(i=0;i<num_face;i++)
	{
		for(j=0;j<3;j++)
		{
			myvertexs[mytestfaces[i].index_vertex[j]].u0=0;
		}
	}
        myvertexs[400].u0=1;
       /* for(i=0;i<3;i++)
	{
		myvertexs[mytestfaces[0].index_vertex[i]].u0=0;
	}*/
}

void object::calNormal()
{
	int i,j;
	int siz=myvertexs.size();
	vertex vertex_here;
	int index_HE_begin; // one ring��ʼʱ��halfedge����
	int index_now,index_now_opp; //��ǰhalfedge�������Լ��䷴��halfedge������
	
	int index_face_now;
	myvector vector_up; //�����ϵ�����
	double area_mixed; //mixed���
        
        double area; //��У��
	double angle_sum; //one ring �ǶȺ�

	double sum;
	double cot;


        SparseLU<SparseMatrix<double>,COLAMDOrdering<int>> linearSolver; //ʹ��LU�ֽⲻҪ��QR�ֽ�

       // SparseMatrix < double > A(num_vertex,num_vertex);
        SparseMatrix < double > Lc(num_vertex,num_vertex);
       //SparseMatrix < double > t_multi_Lc(num_vertex,num_vertex);
        SparseMatrix < double > A_sub_tLc(num_vertex,num_vertex);

       // vector< Triplet< double > > tripletsForA;
        vector< Triplet< double > > tripletsForLc;
        //vector< Triplet< double > > tripletsFort_multi_Lc;
        vector< Triplet< double > > tripletsForA_sub_tLc;


	//MatrixXd A =MatrixXd::Random(num_vertex,num_vertex); // ��������
	//MatrixXd Lc=MatrixXd::Random(num_vertex,num_vertex); //������˹���ӵ�ʣ�ಿ��
        //MatrixXd t_multi_Lc=MatrixXd::Random(num_vertex,num_vertex); //t*Lc ����
	//MatrixXd A_sub_tLc=MatrixXd::Random(num_vertex,num_vertex); //A-t*Lc ����
        
	//A.fill(0);
	//Lc.fill(0);

	VectorXd u0(num_vertex);
	VectorXd ut(num_vertex);
	VectorXd divergence(num_vertex);
	VectorXd dis(num_vertex);

	
	for(i=0;i<siz;i++)
	{
		vector_up=myvector(); //���� 
		area_mixed=0; //����
                area=0;
		angle_sum=0;
		
		vertex_here=myvertexs[i];
		index_HE_begin=vertex_here.index_HE_towards;
		index_now=index_HE_begin; //��ǰ�Ĵ����halfedge����
		index_now_opp=myhalfedges[index_now].index_oppHE;
		index_face_now=myhalfedges[index_now].index_face;

		sum=0;

		do 
		{	
			cot=1.0/tan(myhalfedges[index_now].angle_towards)+1.0/tan(myhalfedges[index_now_opp].angle_towards);
                        
                        tripletsForLc.emplace_back(i,myhalfedges[index_now].index_vertex_towards,cot*0.5); //��Ϊ��ĸ�е�2�ᵽ�����

                        tripletsForA_sub_tLc.emplace_back(i,myhalfedges[index_now].index_vertex_towards,-1*0.5*cot*t); //�������ϵ����ݴ���
			//Lc(i,myhalfedges[index_now].index_vertex_towards)=cot/2.0; 

			sum+=(-1*cot*0.5);
			vector_up+=myhalfedges[index_now].itself*cot;
			angle_sum+=myhalfedges[index_now].angle_accompany;
			
			face face_here=myfaces[index_face_now];
                        area+=(face_here.area/3.0);
			if(face_here.is_non_obtuse==1)
			{
				area_mixed+=myhalfedges[index_now].area_accompany;
			}
			else
			{
				if(cos(myhalfedges[index_now].angle_accompany)>=0) //�۽�������  ���� �ýǲ��Ƕ۽�
				{
					area_mixed+=face_here.area/4.0;
				}
				else
				{
					area_mixed+=face_here.area/2.0;
				}
			}
			
			index_now=myhalfedges[index_now_opp].index_nextHE;
			index_now_opp=myhalfedges[index_now].index_oppHE;
			index_face_now=myhalfedges[index_now].index_face;
			
		} while (index_now!=index_HE_begin);

                tripletsForLc.emplace_back(i,i,sum);
		//Lc(i,i)=sum;

                //tripletsForA.emplace_back(i,i,area_mixed);
		//A(i,i)=area_mixed;

                tripletsForA_sub_tLc.emplace_back(i,i,area-sum*t);

		//ƽ����������
		myvector K=vector_up/area_mixed/2.0;
		
		myvertexs[i].area_mixed=area_mixed;
		K.normalize();
		myvertexs[i].normal=K*-1;
		
	}

        for(i=0;i<num_vertex;i++)
        {
               u0(i)=myvertexs[i].u0;
        }

        Lc.setFromTriplets(tripletsForLc.begin(),tripletsForLc.end()); 
        A_sub_tLc.setFromTriplets(tripletsForA_sub_tLc.begin(),tripletsForA_sub_tLc.end());

        Lc.makeCompressed();
        A_sub_tLc.makeCompressed();

        linearSolver.compute(A_sub_tLc);
	ut=linearSolver.solve(u0);

	for(i=0;i<num_vertex;i++)
	{
		myvertexs[i].ut=ut(i);
	}

	calGradientOfDis();

	int index_next_HE;
	int index_next_next_HE; 
	double divergence_sum;
	for(i=0;i<num_vertex;i++)
	{
		vertex_here=myvertexs[i];
		index_HE_begin=vertex_here.index_HE_towards;
		index_now=index_HE_begin; //��ǰ�Ĵ����halfedge����

		index_next_HE=myhalfedges[index_now].index_nextHE;
		index_next_next_HE=myhalfedges[index_next_HE].index_nextHE;

		index_now_opp=myhalfedges[index_now].index_oppHE;
		index_face_now=myhalfedges[index_now].index_face;

		divergence_sum=0;
		do 
		{	
			face face_here=myfaces[index_face_now];

			divergence_sum+=(myhalfedges[index_now].itself.dot(face_here.gradientOfdis)*1/tan(myhalfedges[index_now].angle_towards)
                                +myhalfedges[index_next_next_HE].itself.dot(face_here.gradientOfdis)*(-1)*1/tan(myhalfedges[index_next_next_HE].angle_towards));


			index_now=myhalfedges[index_now_opp].index_nextHE;

                        index_next_HE=myhalfedges[index_now].index_nextHE;
		        index_next_next_HE=myhalfedges[index_next_HE].index_nextHE;

			index_now_opp=myhalfedges[index_now].index_oppHE;
			index_face_now=myhalfedges[index_now].index_face;
			
		} while (index_now!=index_HE_begin);
		divergence_sum*=0.5;
		myvertexs[i].divergence=divergence_sum;
		divergence(i)=divergence_sum;
	}

        linearSolver.compute(Lc);
	dis=linearSolver.solve(divergence);

	
       /* for(i=0;i<num_vertex;i++)
        {
             dis(i)=fabs(dis(i));
        }*/

        disMin=disMax=dis(0);
	for(i=0;i<num_vertex;i++)
	{
		myvertexs[i].valueOfdis=dis(i);
		if(myvertexs[i].valueOfdis>disMax)
		{
			disMax=myvertexs[i].valueOfdis;
		}
		else if(myvertexs[i].valueOfdis<disMin)
		{
			disMin=myvertexs[i].valueOfdis;
		}
		//printf("%d %lf\n",i,dis(i));
	}
        printf("end\n");
}

void object::calGradientOfDis()
{
	int i,j;
	face face_now;
	for(i=0;i<num_face;i++)
	{
		face_now=myfaces[i];
		int index_HE_begin=face_now.index_HE;
		int index_HE_now=index_HE_begin;
		int index_HE_next;
		int index_vertex_now; //��ǰhalfedge�Ŀ�ʼ��
		myvector normal=((face)myfaces[i]).normal;
		myvector sum=myvector(); //������
		do 
		{
			index_vertex_now=myhalfedges[index_HE_now].index_vertex_begin;
			index_HE_next=myhalfedges[index_HE_now].index_nextHE;
			sum+=((normal.cross(myhalfedges[index_HE_next].itself))*myvertexs[index_vertex_now].ut);
			index_HE_now=myhalfedges[index_HE_now].index_nextHE;
		} while (index_HE_now!=index_HE_begin);
		sum/=(2*myfaces[i].area);
		myfaces[i].gradientOfu=sum;
		sum*=-1;
		sum.normalize();
		myfaces[i].gradientOfdis=sum;
	}
}
