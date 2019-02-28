#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <string>
#include "test.h"

using namespace std;


void saveAsVTK()
{
  stringstream ss;
  string count_s;
  ss<<count;
  ss>>count_s;
  string name="./res/myobeject_";
  name+=count_s;
  name+=".vtk";
  FILE *fp;
  int i;
printf("%s \n",name.c_str());
  fp=fopen(name.c_str(),"w");
  printf("%s \n",name.c_str());
  fprintf(fp,"# vtk DataFile Version 2.0\n");
  fprintf(fp,"triangle\n");
  fprintf(fp,"ASCII\n");
  fprintf(fp,"DATASET UNSTRUCTURED_GRID\n");
  fprintf(fp,"POINTS %d double\n",myobject->num_vertex);
  for(i=0;i<myobject->num_vertex;i++)
    {
      fprintf(fp,"%lf %lf %lf\n",myobject->myvertexs[i].location.x,myobject->myvertexs[i].location.y,myobject->myvertexs[i].location.z);
    }
  fprintf(fp,"CELLS %d %d\n",myobject->num_face,myobject->num_face*4);
  for(i=0;i<myobject->num_face;i++)
    {
      fprintf(fp,"3 %d %d %d\n",myobject->mytestfaces[i].index_vertex[0],myobject->mytestfaces[i].index_vertex[1],myobject->mytestfaces[i].index_vertex[2]);
    }
  fprintf(fp,"CELL_TYPES %d\n",myobject->num_face);
  for(i=0;i<myobject->num_face;i++)
    {
      fprintf(fp,"5\n");
    }
  
  fprintf(fp,"POINT_DATA %d\n",myobject->num_vertex);

  fprintf(fp,"SCALARS valueOfdis double\n");
  fprintf(fp,"LOOKUP_TABLE default\n");
  for(i=0;i<myobject->num_vertex;i++)
    {
      fprintf(fp,"%lf\n",myobject->myvertexs[i].valueOfdis);
    }
  
  fprintf(fp,"NORMALS point_normal double\n");
  for(i=0;i<myobject->num_vertex;i++)
    {
      fprintf(fp,"%lf %lf %lf\n",myobject->myvertexs[i].normal.x,myobject->myvertexs[i].normal.y,myobject->myvertexs[i].normal.z);
    }

  fclose(fp);
  
}

void saveBmp(const char* name,int width,int height,unsigned char* data)
{
	/*BITMAPFILEHEADER hdr;
	BITMAPINFOHEADER infoHdr;
	infoHdr.biSize=40;
	infoHdr.biWidth=width;
	infoHdr.biHeight =height;
	infoHdr.biPlanes =1;
	infoHdr.biBitCount =24;
	infoHdr.biCompression =0;
	infoHdr.biSizeImage=width*height*3;
	infoHdr.biXPelsPerMeter=0;
	infoHdr.biYPelsPerMeter=0;
	infoHdr.biClrUsed=0;
	infoHdr.biClrImportant=0;
	
	hdr.bfType = 0x4D42;
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = 54;
	hdr.bfSize =(DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+width* height * 3);
	
	unsigned char x;
	for(int i=0;i<infoHdr.biSizeImage;i+=3)
	{
		x=data[i];
		data[i]=data[i+2];
		data[i+2]=x;
	}
	
	FILE *fd;
	fd=fopen(name,"wb");
	fwrite(&hdr,sizeof(BITMAPFILEHEADER),1,fd);
	fwrite(&infoHdr,sizeof(BITMAPINFOHEADER),1,fd);
	fwrite(data,width* height*3,1,fd);
	fclose(fd);*/
}


void saveSceneImage()
{
	int view[4];
	glGetIntegerv(GL_VIEWPORT,view);
	int bufferSize=view[2]*view[3]*3;
	void* color_buffer=malloc(bufferSize);
	glReadPixels(view[0],view[1],view[2],view[3],GL_RGB,GL_UNSIGNED_BYTE,color_buffer);
	
	string st,loc;
	loc="D:/test/test6/";
	stringstream  ss;
	ss<<count;
	ss>>st;
	st+=".bmp";
	loc+=st;
	saveBmp(loc.c_str(),view[2],view[3],(unsigned char*)color_buffer);
	free(color_buffer);	
}

void drawObject()
{
	switch(kind)
	{
	case 0:
		myobject->testdraw();
		break;
	case 1:
		myobject->drawwithNormal();
		break;
	}
}

void display(void)
{
     
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	drawObject();
      /*   glColor3d(1,0,0);
       glBegin(GL_TRIANGLES);
       glVertex3d(0,0,0);
       glVertex3d(1,0,0);
       glVertex3d(1,0,1);
       glEnd();
        glColor3d(0,1,0);
        glBegin(GL_LINES);
        glVertex3d(0,1,0.5);
        glVertex3d(1,1,0.5);
        glEnd();
      glColor3d(0,1,1);
        glBegin(GL_LINES);
        glVertex3d(0,-1,0.3);
        glVertex3d(1,-1,0.3);
        glEnd();*/


	glutSwapBuffers(); //˫����ʱ����
	glFlush();
	
	glutPostRedisplay();
}

void makeSmooth()
{
	//glEnable(GL_LINE_SMOOTH); 
	//glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glHint(GL_LINE_SMOOTH_HINT,GL_DONT_CARE);
	glLineWidth(2.2);
	
	glPointSize(1.0);
	
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_POLYGON_SMOOTH);
}

void lightControl()
{
	float light_position[] ={0,-10,0,0};
	float white_light[] ={1,1,1.5,1};
	float lmod_ambient[]={0.5,0.5,0.65,1}; 
	float spot_direction[]={0,1,0}; //�۹�Ƶ������������
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
	glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmod_ambient);

	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); 
	glClearDepth(1.0);

	//glEnable(GL_TEXTURE_2D);

}

void init()
{
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA) ;  // ˫���� RGBA(A��ʾ͸����) �����
	glutInitWindowSize(400,400) ; //���崰��λ�� 
	glutInitWindowPosition(100,100) ; //�������� 
	glutCreateWindow("geodesic_test") ; 	
	glClearColor(1,1,1,1);
        makeSmooth(); // �����	

	//�����޳� �������Ӿ�����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	lightControl();

	myobject=new object();
	mycamera=new camera();
	kind=0; //���Ի���
	count=0;
}

void reshape(int w,int h) //�״λ��ƺ���Ļ��С����ʱglutReshapeFunc()���øú���
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0,(double)w/(double)h,1,500);  
	//  void APIENTRY gluPerspective ( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) 
	//�������������������������������ͶӰ�����쳣�����ֵ�����쳣��������Ϊ��
	
	glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	mycamera->see();
}


void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'a':
		mycamera->rotate_LR(1);  
		break;
	case 'd':
		mycamera->rotate_LR(-1); //��������������ƶ�����˰�d����������ʱ����ת����ʵ�����˳ʱ����ת
		break;
	case 'w':
		mycamera->rotate_UD(1);
		break;
	case 's':
		mycamera->rotate_UD(-1);
		break;
	case 'k':
		mycamera->move(-1);
		break;
	case 'l':
		mycamera->move(1);
		break;
	case 'n':
		glDisable(GL_LIGHTING);
		kind=0; //����
		break;
	case  'b':
		glEnable(GL_LIGHTING);
		kind=1;
		break;
	case  'q':
                saveAsVTK();
		//saveSceneImage();
		count++;
		break;
	case 'o':
		exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc,char**argv)
{ 
	glutInit(&argc,argv) ; //��ʾģʽ��ʼ�� 
	init();	

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop() ; 

	
	return 0 ;
}
