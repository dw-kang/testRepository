#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
 
void DoDisplay();
void DoKeyboard(unsigned char key, int x, int y);
void DoMenu(int value);
void reshape(GLsizei width, GLsizei height);

void drawRoad();					// ���θ� �������� ��ü������ �׸��� �Լ�
void drawLine();					// �߾Ӽ�
void drawDoro(GLfloat num);			// ����
void drawIndo(GLfloat num);			// �ε�
void drawSine(GLfloat len);			// �ó���
void drawSDoro(GLint num);			// �κ� ����
void drawUDoro(GLint num);			// ��� ����
void drawBuilding();				// 1x1x1 ���̽� �ǹ�
void drawDorm();					// ����� �ǹ�
void drawGate();					// ����
void drawTree();					// ����
void drawTennis();					// �״Ͻ���
void drawUndong();					// ���
void drawNetu();					// �ڿ����д���
void drawGong();					// ����
void drawGongBuilding();				// ����ǹ�
void drawLib();						// ������
void drawZucha();					// ������
void drawBon();						// ����
void drawEomoon();					// ��а�
void drawInmoon();					// �ι�����
void drawLake();					// �����
GLubyte *LoadBmp(const char *Path, int *Width, int *Height);	// �ؽ��� ���� �Լ�


GLfloat xAngle, yAngle, zAngle;		// ��ǥ��
GLfloat ex, ey=5, ez=44.5;			// �������� ��ġ
GLfloat tx=60, ty=-50, tz=100;		// �������� ����
GLfloat lx, ly=1, lz;				// �������� ����
GLfloat ortho=25;					// ȭ�� ����  
float ar;
int winWidth, winHeight;			// ȭ�� ����

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow){
	
	glutInitWindowPosition(100,100);	// ȭ�� ��ġ
	glutInitWindowSize(700, 500);		// ȭ�� ũ��
	glutCreateWindow("HUFS Navigation Ver.1.0 ");		// ȭ�� ���� �� ���� ǥ����
	glutDisplayFunc(DoDisplay);			// ȭ�� ��� �Լ� ���
	glutKeyboardFunc(DoKeyboard);		// Ű���� �ݹ� �Լ� ���
	glutReshapeFunc(reshape);			// ȭ�� ����� �ݹ� �Լ� ���
	glutMainLoop();
	return 0;

}

void DoKeyboard(unsigned char key, int x, int y){	// Ű���� �ݹ� �Լ�

     switch(key) {

		case '1':								// ����~��Ÿ�
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-4;ey=5;ez=0;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '2':								// ��ȸ������~��Ÿ�
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=7;ey=5;ez=24;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '3':								// �����~��Ÿ�
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-12.7;ey=5;ez=24;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '4':								// ����
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-1.5;ey=5.2;ez=49.3;
			tx=60;ty=-51;tz=108;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '5':								// ������
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-0.9;ey=4.1;ez=55.6;
			tx=-97;ty=-80;tz=215;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;
	
		case '6':								// ����
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=5.2;ey=5.2;ez=71.6;
			tx=86;ty=-51;tz=115;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;	

		case '7':								// ���
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=5.2;ey=5.5;ez=77.9;
			tx=-61;ty=-50;tz=200;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;	

		case '9':					// �ݴ��� ����
			ortho = 25;
			xAngle=0;yAngle=0;zAngle=0;
			ex=4;ey=4.5;ez=44.5;
			tx=-71;ty=-72;tz=135;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '0':					// ����
			ortho = 25;
			xAngle=0;yAngle=0;zAngle=0;
			ex=0;ey=5;ez=44.5;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

     }
     glutPostRedisplay();

}

void reshape(int w, int h){			// Reshape �ݹ� �Լ�

	float aspectRatio;
	winWidth = w;
	winHeight = h;
	aspectRatio = (GLfloat)w / (GLfloat)h;		// ��ȭ�� ȭ�� ���� ����
	glViewport(0, 0, w, h);						// ���� �̹����� ����ϴ� ����Ʈ ũ�� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(w<=h)									// ȭ�� ������ ���� ���������� ���� �缳��
		glOrtho(-ortho, ortho, -ortho/aspectRatio, ortho/aspectRatio, -120, 120);
	else
		glOrtho(-ortho*aspectRatio, ortho*aspectRatio, -ortho, ortho, -120, 120);
		
}

void DoDisplay(){			// ȭ�� ��� ���� ��� �Լ�

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �÷� ����, ���� ���� �ʱ�ȭ
	glEnable(GL_DEPTH_TEST);							// ���� �׽�Ʈ Ȱ��ȭ

	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);							// �𵨺� ����
	glLoadIdentity();
	
	gluLookAt(ex, ey, ez, tx, ty, tz, lx, ly, lz);		// Ű���� �Է¿� ���� ���� ��ȯ

	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

	drawRoad();											// ���θ� ������ ������ ���

	glPopMatrix();

	glFlush();											// ȭ�� ���
}

void drawRoad(){						// ���θ� ������ �ǹ� �׸��� �Լ�

	glPushMatrix();
	
	glRotatef(-5, 0.0f, 1.0f, 0.0f);		// ���θ� ���� ȸ��

	drawDoro(18);						// 18m ���� �׸���
	drawIndo(18);						// 18m �ε� �׸���
	drawSine(18);						// 18m �ó��� �׸���
	
	glPushMatrix();;					// ���� �׸���
	drawGate();
	glTranslatef(0, 0, 0.5);			
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	drawGate();
	glPopMatrix();						// ���� �׸��� ��

	glPushMatrix();						// ���� �׸��� ���� ����
	
	glTranslatef(-1.2, 0.1, 2);			// ó�� �׸� ������ �̵�
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// ó�� ���� �׸� ������ ȸ��
	drawTree();							// ���� �׸���

	for(int i=0; i<15; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}

	glTranslatef(2.2, 0, 0);			// �� �ǳ������� �̵�
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// ���� �������� ȸ��
	for(int i=0; i<16; i++){
		drawTree();						// ���� �׸���
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
	}
	glPopMatrix();						// ���� �׸��� ���� ��


	glTranslatef(0, 0, 17.8);			// ���� ���η� �̵�
	glRotatef(10, 0.0f, 1.0f, 0.0f);	// ���θ� ���� ȸ��
	drawDoro(9);						// 9m ���� �׸���
	drawIndo(9);						// 9m �ε� �׸���
	drawSine(9);

	glPushMatrix();						// �״Ͻ��� �׸��� ���� ����
	glTranslatef(-3.7, 0, 1.5);			// �״Ͻ����� ���� �̵�
	drawTennis();
	glTranslatef(0, 0, 2.1);			// �״Ͻ����� ���� �̵�
	drawTennis();
	glPopMatrix();						// �״Ͻ��� �׸��� ���� ��

	glPushMatrix();						// ���� �׸��� ���� ����
	glTranslatef(-1.2, 0.1, 0);			// ó�� �׸� ������ �̵�
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// ó�� ���� �׸� ������ ȸ��
	drawTree();							// ���� �׸���
	for(int i=0; i<7; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glTranslatef(2.2, -1, 0);			// �� �ǳ������� �̵�
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// ���� �������� ȸ��
	for(int i=0; i<8; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glPopMatrix();						// ���� �׸��� ���� ��


	glTranslatef(0, 0, 8.8);			// ���� ���η� �̵�


	glPushMatrix();						// 9m¥�� ���� ������ ����� ©���� ���� ����
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	drawSDoro(3);						// 3m ����+�ε� �׸���
	glTranslatef(0, 0, 5.6);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	drawUDoro(1);						// 3m ���� �׸���
	glTranslatef(0, 1, 2.8);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	drawUDoro(5);						// 5m ���� �׸���
	glTranslatef(0, 1, 4.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	drawUDoro(2);						// 2m ���� �׸���
	glTranslatef(0, 1, 1.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	drawUDoro(2);						// 2m ���� �׸���	
	glTranslatef(0, 1, 1.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	drawUDoro(3);						// 3m ���� �׸���
	glTranslatef(0, 1, 2.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	drawSDoro(4);						// 4m ���� �׸���
	
	glPushMatrix();						// ��ȸ������ �ǹ� �׸��� ����
	glTranslatef(-3, 0, 3);				// ��ȸ������1 �ǹ� �̵�
	glRotatef(180, 0.0f, 1.0f, 0.0f);	// ��ȸ������1 �ǹ� ȸ��
	glScalef(0.3, 0.5, 0.5);			// ��ȸ������1 �ǹ� ũ�� ����
	drawDorm();							// ��ȸ������1 �׸���
	glTranslatef(0, 0, 5);				// ��ȸ������2 �ǹ� �̵�
	glRotatef(90, 0.0f, 1.0f, 0.0f);	// ��ȸ������2 �ǹ� ȸ��
	glScalef(0.5, 1, 1);				// ��ȸ������2 �ǹ� ũ�� ����
	drawDorm();							// ��ȸ������2 �׸���
	glTranslatef(13, 0, 7);				// ��ȸ������3 �ǹ� �̵�
	glRotatef(-90, 0.0f, 1.0f, 0.0f);	// ��ȸ������3 �ǹ� ȸ��
	glScalef(1, 1, 2);					// ��ȸ������3 �ǹ� ũ�� ����
	drawDorm();							// ��ȸ������3 �׸���
	glPopMatrix();						// ��ȸ������ �ǹ� �׸��� ����
	
	glPopMatrix();						// 9m¥�� ���� ������ ����� ©���� ���� ��

	glRotatef(-10, 0.0f, 1.0f, 0.0f);
	drawSDoro(36);						// 36m ����+�ε� �׸���
	drawSine(36);

	glPushMatrix();						// ���ɴ뵵���� ������� ���� ����
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// ó�� ���� �׸� ������ ȸ��
	glTranslatef(1.2, -3.5, 0);
	drawTree();							// ���� �׸���
	for(int i=0; i<31; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glTranslatef(-2.2, -1, 0);			// �� �ǳ������� �̵�
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// ���� �������� ȸ��
	for(int i=0; i<5; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glTranslatef(0, -2, 0);				// ���� ������ �̵�
	for(int i=0; i<25; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glPopMatrix();						// ���ɴ뵵���� ������� ���� ����

	glPushMatrix();						// ����� �ǹ�+���� �׸��� ���� ����
	glTranslatef(-1, 0, 2);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	drawDoro(9);						// ����� ���� ����
	drawIndo(9);						// ����� ���� �ε�

	glPushMatrix();						// ����� ���� ������ ���� ����
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// ó�� ���� �׸� ������ ȸ��
	glTranslatef(1.2, -1, 0);
	drawTree();							// ���� �׸���
	for(int i=0; i<9; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glTranslatef(-2.2, -1, 0);			// �� �ǳ������� �̵�
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// ���� �������� ȸ��
	for(int i=0; i<10; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glPopMatrix();						// ����� ���� ������ ���� ����

	glTranslatef(-1.5, 0, 11.5);			// �����1 �ǹ� �̵�
	glRotatef(90, 0.0f, 1.0f, 0.0f);	// �����1 �ǹ� ȸ��
	glScalef(0.5, 0.5, 0.6);			// �����1 �ǹ� ũ�� ����
	drawDorm();							// �����1 �׸���
	glTranslatef(0, 0, 10);				// �����2 �ǹ� �̵�
	drawDorm();							// �����2 �׸���
	glTranslatef(-7, 0.7, 0);			// �����3 �ǹ� �̵�
	drawDorm();							// �����3 �׸���
	glTranslatef(0, 0, -10);				// �����4 �ǹ� �̵�
	drawDorm();							// �����4 �׸���
	glPopMatrix();						// ����� �ǹ�+���� �׸��� ���� ��

	glPushMatrix();						// ���, ������, �ڿ���, ���� �׸��� ���� ����
	glTranslatef(3, 0.1, 17);			// ��� ��ġ�� �̵�
	drawUndong();						// ��� �׸���
	glTranslatef(0, 0, 8);				// ������ ��ġ�� �̵�
	drawZucha();						// ������ �׸���
	glTranslatef(10, 2, -1);				// �ڿ��� ��ġ�� �̵�
	drawNetu();							// �ڿ��� �׸���
	glTranslatef(-10, -2, 6);			// ���� ��ġ�� �̵�
	drawGong();							// ���� �׸���
	glTranslatef(-8.5, 0, 2);			// ������ ��ġ�� �̵�
	drawLib();							// ������ �׸���
	glPopMatrix();						// ���, ������, �ڿ���, ���� �׸��� ���� ��

	glTranslatef(0, 0, 35.4);			// ���� ���η� �̵�
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	drawDoro(15);						// 15m ���� �׸���
	drawIndo(15);						// 15m �ε� �׸���
		
	glPushMatrix();						// ���뿡�� ���������� ���� ����
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// ó�� ���� �׸� ������ ȸ��
	glTranslatef(1.2, -1, 0);
	drawTree();							// ���� �׸���
	for(int i=0; i<13; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glTranslatef(-2.5, -1, 0);			// �� �ǳ������� �̵�
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// �ݴ� �������� ȸ��
	for(int i=0; i<14; i++){
		glTranslatef(0, -1, 0);			// ���� ������ �̵�
		drawTree();						// ���� �׸���
	}
	glPopMatrix();						// ���뿡�� ���������� ���� ���� ��

	glPushMatrix();						// ����� �׸��� ����
	glTranslatef(2, 0, 8);				// ����� ��ġ�� �̵�
	drawLake();
	glPopMatrix();						// ����� �׸��� ���� ��

	// ��õ���� ����?

	glTranslatef(0, 0, 14.5);			// ���� ���η� �̵�
	glRotatef(-40, 0.0f, 1.0f, 0.0f);
	drawDoro(16);						// 16m ���� �׸���
	drawIndo(16);						// 16m �ε� �׸���

	glPushMatrix();						// ���� �׸��� ����
	glTranslatef(7, 3, 5);				// ���� �׸� ��ġ�� �̵�
	drawBon();							// ���� �׸���
	glPopMatrix();						// ���� �׸��� ���� ��
	
	glPushMatrix();						// ��� �׸��� ����
	glTranslatef(-6, 3, 12);				// ��� �׸� ��ġ�� �̵�
	drawEomoon();						// ��� �׸���
	glPopMatrix();						// ��� �׸��� ���� ��

	// �ι���

	glTranslatef(0, 0, 15.5);			// ���� ���η� �̵�
	glRotatef(10, 0.0f, 1.0f, 0.0f);
	drawDoro(5);						// 5m ���� �׸���
	drawIndo(5);						// 5m �ε� �׸���


	glPopMatrix();
	glutPostRedisplay();
}

void drawUDoro(GLint num){

	switch(num){
	case 1:									// 3m �ö󰡴� ���� ó�� �κ�
		glBegin(GL_POLYGON);				// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(-1, 1, 3);
		glEnd();
		
		glBegin(GL_LINES);					// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 2.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);			// ���� ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 3);
		glVertex3f(-1, 1.1, 3);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);				// ���� ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 3);
		glVertex3f(-1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);			// ���� ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 3);
		glVertex3f(-1.6, 1.1, 3);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// ������ ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(1, 1.1, 3);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// ������ ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 3);
		glVertex3f(1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ������ ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 3);
		glVertex3f(1.6, 1.1, 3);
		glEnd();

		break;

		case 2:								// 3m ���� ó�� �κ�
		glBegin(GL_POLYGON);				// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 2);
		glVertex3f(-1, 1, 2);
		glEnd();
		
		glBegin(GL_LINES);					// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 1.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 2);
		glVertex3f(-1, 1.1, 2);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 2);
		glVertex3f(-1.1, 1.1, 2);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 2);
		glVertex3f(-1.6, 1.1, 2);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 2);
		glVertex3f(1, 1.1, 2);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 2);
		glVertex3f(1.1, 1.1, 2);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 2);
		glVertex3f(1.6, 1.1, 2);
		glEnd();

		break;

		case 3:									// 5m �ö󰡴� ���� ó�� �κ�
		glBegin(GL_POLYGON);					// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(-1, 1, 3);
		glEnd();
		
		glBegin(GL_LINES);						// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 2.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// ���� ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 3);
		glVertex3f(-1, 1.1, 3);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);					// ���� ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 3);
		glVertex3f(-1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// ���� ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 3);
		glVertex3f(-1.6, 1.1, 3);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// ������ ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(1, 1.1, 3);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);					// ������ ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 3);
		glVertex3f(1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// ������ ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 3);
		glVertex3f(1.6, 1.1, 3);
		glEnd();

		break;

		case 5:									// 5m �ö󰡴� ���� ó�� �κ�
		glBegin(GL_POLYGON);					// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 5);
		glVertex3f(-1, 1, 5);
		glEnd();
		
		glBegin(GL_LINES);						// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 4.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// ���� ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 5);
		glVertex3f(-1, 1.1, 5);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);					// ���� ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 5);
		glVertex3f(-1.1, 1.1, 5);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// ���� ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 5);
		glVertex3f(-1.6, 1.1, 5);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// ������ ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 5);
		glVertex3f(1, 1.1, 5);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);					// ������ ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 5);
		glVertex3f(1.1, 1.1, 5);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// ������ ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 5);
		glVertex3f(1.6, 1.1, 5);
		glEnd();

		break;
	}
}

void drawSDoro(GLint num){

	switch(num){
	case 3:									// 3m ���� ó�� �κ�
		glBegin(GL_POLYGON);				// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 1);
		glVertex3f(1, 0, 6);
		glVertex3f(-1, 0, 6);
		glEnd();
		
		glBegin(GL_LINES);					// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 5.5);
		glEnd();

		glPushMatrix();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, 3.8);
		glVertex3f(-1, 0, 6);
		glVertex3f(-1, 0.1, 6);
		glVertex3f(-1, 0.1, 3.8);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, 3.8);
		glVertex3f(-1,   0.1, 3.8);
		glVertex3f(-1,   0.1, 6);
		glVertex3f(-1.1, 0.1, 6);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, 3.5);
		glVertex3f(-1.1, 0.1, 3.5);
		glVertex3f(-1.1, 0.1, 6);
		glVertex3f(-1.6, 0.1, 6);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 6);
		glVertex3f(1, 0.1, 6);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   0.1, 6);
		glVertex3f(1.1, 0.1, 6);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 0.1, 6);
		glVertex3f(1.6, 0.1, 6);
		glEnd();

		glPopMatrix();

		break;

		case 4:								// 4cm ���� ó�� �κ�
		glBegin(GL_POLYGON);				// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 4);
		glVertex3f(-1, 0, 4);
		glEnd();
		
		glBegin(GL_LINES);					// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 3.5);
		glEnd();

		glPushMatrix();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, 0);
		glVertex3f(-1, 0, 4);
		glVertex3f(-1, 0.1, 4);
		glVertex3f(-1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, 0);
		glVertex3f(-1,   0.1, 0);
		glVertex3f(-1,   0.1, 4);
		glVertex3f(-1.1, 0.1, 4);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, 0);
		glVertex3f(-1.1, 0.1, 0);
		glVertex3f(-1.1, 0.1, 4);
		glVertex3f(-1.6, 0.1, 4);
		glEnd();

		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 4);
		glVertex3f(1, 0.1, 4);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   0.1, 4);
		glVertex3f(1.1, 0.1, 4);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 0.1, 4);
		glVertex3f(1.6, 0.1, 4);
		glEnd();

		glPopMatrix();

		break;

		case 36:							// 26cm ���� ó�� �κ�
		glBegin(GL_POLYGON);				// ���� �ƽ���Ʈ �κ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 36);
		glVertex3f(-1, 0, 36);
		glEnd();
		
		glBegin(GL_LINES);					// ���� �߾Ӽ�
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 35.5);
		glEnd();

		glPushMatrix();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, 3);
		glVertex3f(-1, 0, 36);
		glVertex3f(-1, 0.1, 36);
		glVertex3f(-1, 0.1, 3);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(-1.1, 0.1, 3);
		glVertex3f(-1,   0.1, 3);
		glVertex3f(-1,   0.1, 36);
		glVertex3f(-1.1, 0.1, 36);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, 3);
		glVertex3f(-1.1, 0.1, 3);
		glVertex3f(-1.1, 0.1, 36);
		glVertex3f(-1.6, 0.1, 36);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// ���ο� ���� �� ����
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 3);
		glVertex3f(1, 0, 36);
		glVertex3f(1, 0.1, 36);
		glVertex3f(1, 0.1, 3);
		glEnd();
		
		glBegin(GL_POLYGON);		// ���ο� ���� �� ����
		glVertex3f(1.1, 0.1, 3);
		glVertex3f(1,   0.1, 3);
		glVertex3f(1,   0.1, 36);
		glVertex3f(1.1, 0.1, 36);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// ���� ��
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 3);
		glVertex3f(1.1, 0.1, 3);
		glVertex3f(1.1, 0.1, 36);
		glVertex3f(1.6, 0.1, 36);
		glEnd();

		glPopMatrix();

		break;
	}
}

void drawDoro(GLfloat len){
	
	glBegin(GL_POLYGON);				// ���� �ƽ���Ʈ �κ�
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, len);
	glVertex3f(-1, 0, len);
	glEnd();
	
	glBegin(GL_LINES);					// ���� �߾Ӽ�
	glLineWidth(10);
	glColor3f(1, 0.5, 0);
	glVertex3f(0, 0.1, 0);
	glVertex3f(0, 0.1, len-0.5);
	glEnd();

}

void drawIndo(GLfloat len){
	
	glPushMatrix();

	glColor3f(0.5, 0.5, 0.5);	// ���� ���ο� ���� �� ����
	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(-1, 0, len);
	glVertex3f(-1, 0.1, len);
	glVertex3f(-1, 0.1, 0);
	glEnd();
	
	glBegin(GL_POLYGON);		// ���ο� ���� �� ����
	glVertex3f(-1.1, 0.1, 0);
	glVertex3f(-1,   0.1, 0);
	glVertex3f(-1,   0.1, len);
	glVertex3f(-1.1, 0.1, len);
	glEnd();
	
	glColor3f(0.9, 0.9, 0.9);	// ���� ��
	glBegin(GL_POLYGON);
	glVertex3f(-1.6, 0.1, 0);
	glVertex3f(-1.1, 0.1, 0);
	glVertex3f(-1.1, 0.1, len);
	glVertex3f(-1.6, 0.1, len);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);	// ���� ���ο� ���� �� ����
	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, len);
	glVertex3f(1, 0.1, len);
	glVertex3f(1, 0.1, 0);
	glEnd();
	
	glBegin(GL_POLYGON);		// ���ο� ���� �� ����
	glVertex3f(1.1, 0.1, 0);
	glVertex3f(1,   0.1, 0);
	glVertex3f(1,   0.1, len);
	glVertex3f(1.1, 0.1, len);
	glEnd();
	
	glColor3f(0.9, 0.9, 0.9);	// ���� ��
	glBegin(GL_POLYGON);
	glVertex3f(1.6, 0.1, 0);
	glVertex3f(1.1, 0.1, 0);
	glVertex3f(1.1, 0.1, len);
	glVertex3f(1.6, 0.1, len);
	glEnd();

	glPopMatrix();

}

void drawSine(GLfloat len){

	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.2, 0.8);
	glVertex3f(2, -0.5, 0);
	glVertex3f(2, -0.5, len);
	glVertex3f(2.5, -0.5, len);
	glVertex3f(2.5, -0.5, 0);
	glEnd();
	glPopMatrix();

}

void drawLake(){
	
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.2, 0.8);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 7);
	glVertex3f(2, 0, 8);
	glVertex3f(4, 0, 7);
	glVertex3f(4, 0, 0);
	glEnd();
	glPopMatrix();
}

void drawEomoon(){
	
	glPushMatrix();					// ��� �ö󰡴� ����
	glScalef(1, 1, 0.5);
	glRotatef(-35, 0.0f, 0.0f, 1.0f);// ���� ȸ��
	glRotatef(90, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	drawDoro(5.5);
	drawIndo(5.5);
	glRotatef(-35, 1.0f, 0.0f, 0.0f);// ���� ȸ��
	glRotatef(180, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	drawDoro(2);
	drawIndo(2);
	glPopMatrix();					// ��� �ö󰡴� ���� ��

	glPushMatrix();					// ���1 �ǹ�
	glTranslatef(-4, 0, -1);
	glScalef(2, 2, 2);
	drawBuilding();
	glPopMatrix();					// ���1 �ǹ� ��

	glPushMatrix();					// ���2 �ǹ�
	glTranslatef(-4, 0, 1.5);
	glScalef(3, 2, 1);
	drawBuilding();					// ���2 �׸���
	glPopMatrix();					// ���2 �ǹ� ��

	glPushMatrix();					// ���3 �ǹ�
	glTranslatef(-6.5, 0, -2.5);
	glScalef(4, 2, 1);
	drawBuilding();					// ���3 �׸���
	glPopMatrix();					// ���3 �ǹ� ��
}

void drawBon(){

	glPushMatrix();					// ���� ��� �κ�
	glTranslatef(2, 0, 0);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	glScalef(1, 2.5, 1.5);
	drawBuilding();
	glPopMatrix();

	glPushMatrix();					// ���� ���� �κ�
	glTranslatef(2.8, 0, 0.3);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glScalef(4, 2, 1.3);
	drawBuilding();
	glPopMatrix();
	
	glPushMatrix();					// ���� ������ �κ�
	glTranslatef(2.8, 0, 0.3);
	glRotatef(-30, 0.0f, 1.0f, 0.0f);
	glScalef(1.3, 2, 4);
	drawBuilding();
	glPopMatrix();

	glPushMatrix();				// ���� �ö󰡴� ����
	glTranslatef(-1, 0, 5);
	glScalef(1, 1, 0.5);
	glRotatef(35, 0.0f, 0.0f, 1.0f);// ���� ȸ��
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	drawDoro(5.5);
	drawIndo(5.5);
	glPopMatrix();
	
	glPushMatrix();				// ���� ���� ����
	glTranslatef(4.5, 0, -4);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	glScalef(0.5, 1, 1);
	drawDoro(6);
	glPopMatrix();
	
	glPushMatrix();				// ���� ���� ����
	glTranslatef(-0.8, 0, -1.3);
	glRotatef(0, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	glScalef(0.5, 1, 1);
	drawDoro(7);
	glPopMatrix();
}

void drawLib(){
	glPushMatrix();
	GLUquadricObj *obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(0, 3, 0);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// ȸ��
	gluCylinder(obj, 1.2, 1.2, 3, 20, 20);	// ��� ������
	
	glColor3f(0.65, 0.65, 0.65);
	glTranslatef(0, 0, 3);
	gluDisk(obj, 0, 1.2, 50, 50);			// �������� ����
	gluDeleteQuadric(obj);
	glPopMatrix();

	glPushMatrix();						// ������ ª�� �κ� �ǹ�
	glTranslatef(0, 3,0);
	glRotatef(-120, 0.0f, 1.0f, 0.0f);	// ȸ��
	glScalef(2, 2, 3);		
	drawBuilding();
	glPopMatrix();

	glPushMatrix();						// ������ �� �κ� �ǹ�
	glTranslatef(-1.5, 3, 0);
	glScalef(2, 2, 6);
	drawBuilding();
	glPopMatrix();

	glPushMatrix();				// ������ ������
	glTranslatef(-4, 3, -8);
	glScalef(0.8, 1, 0.8);
	drawZucha();
	glPopMatrix();

	glPushMatrix();				// ������ �ö󰡴� ����
	glTranslatef(5, 0, -3);
	glScalef(1, 1, 0.5);
	glRotatef(-30, 0.0f, 0.0f, 1.0f);// ���� ȸ��
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	drawDoro(6);
	drawIndo(6);
	glPopMatrix();
	
	glPushMatrix();				// ������ ���� ����
	glTranslatef(0, 3, -3);
	glScalef(1, 1, 0.5);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	drawDoro(3);
	drawIndo(3);
	glPopMatrix();
}

void drawGong(){

	glPushMatrix();
	glScalef(1.5, 2, 4);			// ����1 �ǹ� ũ�� ����
	drawGongBuilding();				// ����1 �ǹ� �׸���
	glPopMatrix();

	glPushMatrix();
	glScalef(4, 2, 1.5);			// ����2 �ǹ� ũ�� ����
	glTranslatef(1.1, 0, -0.1);		// ����2 �ǹ� �̵�
	glRotatef(270, 0.0f, 1.0f, 0.0f);// ����2 �ǹ� ȸ��
	drawGongBuilding();				// ����2 �ǹ� �׸���
	glPopMatrix();
	
	glPushMatrix();
	glScalef(1.5, 2, 4);			// ����3 �ǹ� ũ�� ����
	glTranslatef(3.1, 0, 1);		// ����3 �ǹ� �̵�
	glRotatef(180, 0.0f, 1.0f, 0.0f);// ����3 �ǹ� ȸ��
	drawGongBuilding();				// ����3 �ǹ� �׸���
	glPopMatrix();
	
	glPushMatrix();
	glScalef(4, 2, 1.5);			// ����4 �ǹ� ũ�� ����
	glTranslatef(0.1, 0, 2.8);		// ����4 �ǹ� �̵�
	glRotatef(90, 0.0f, 1.0f, 0.0f);// ����4 �ǹ� ȸ��
	drawGongBuilding();				// ����4 �ǹ� �׸���
	glPopMatrix();
}

void drawGongBuilding(){
	
	GLubyte *data;
	int Width, Height;
	GLint EnvMode = GL_REPLACE;
	GLint TexFilter = GL_LINEAR;

     // �ؽ�ó �̹��� �غ�
	data = LoadBmp("gong.bmp", &Width, &Height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
	free(data);

     // �ؽ�ó ȯ�� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, EnvMode);

     // �ؽ�ó ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexFilter);

		GLfloat build[][3] = {			// �ǹ� �� ��ǥ ����
			{0, 0, 0},
			{0, 1, 0},
			{1, 1, 0},
			{0, 1, 1},
			{1, 1, 1},
			{0, 0, 0},
			{1, 0, 0},
			{0, 0, 1},
			{1, 0, 1}
		};

		glBegin(GL_POLYGON);				// �ǹ� õ��
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[1]);
		glVertex3fv(build[2]);
		glVertex3fv(build[4]);
		glVertex3fv(build[3]);
		glEnd();

		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.6, 0.6, 0.6);
		glVertex3fv(build[1]);
		glVertex3fv(build[5]);
		glVertex3fv(build[6]);
		glVertex3fv(build[2]);
		glEnd();
		
		glBegin(GL_POLYGON);				// �ǹ� �ٴ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[5]);
		glEnd();
		
		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.64, 0.64, 0.64);	
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[3]);
		glVertex3fv(build[4]);
		glEnd();
		
		
		glEnable(GL_TEXTURE_2D);			// �ؽ��� Ȱ��ȭ
		glBegin(GL_POLYGON);				// �ٱ��� �ǹ�
		glColor3f(0, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3fv(build[7]);
		glTexCoord2f(1, 1);
		glVertex3fv(build[5]);
		glTexCoord2f(0, 1);
		glVertex3fv(build[1]);
		glTexCoord2f(0, 0);
		glVertex3fv(build[3]);
		glEnd();
		glDisable(GL_TEXTURE_2D);			// �ؽ��� ��Ȱ��ȭ
		
		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.66, 0.66, 0.66);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[4]);
		glVertex3fv(build[2]);
		glEnd();
}

void drawNetu(){
	glPushMatrix();
	glScalef(2, 3, 5);				// �ڿ��� �ǹ� ũ�� ����
	drawBuilding();					// �ڿ��� �ǹ� �׸���
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 0.6);			// ���� �� ����
	glTranslatef(-2, 0, 4);			// ���� �̵�
	glRotatef(40, 0.0f, 0.0f, 1.0f);// ���� ȸ��
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	glScalef(0.5, 1, 1);
	drawDoro(3.5);					// ���� �׸���
	drawIndo(3.5);					// �ε� �׸�
	glPopMatrix();

	glPushMatrix();
//	glRotatef(-40, 0.0f, 0.0f, 1.0f);// ���� ȸ��
	glTranslatef(-2, 0, 2.5);			// ���� �̵�
	glRotatef(90, 0.0f, 1.0f, 0.0f);// ���� ȸ��
	glScalef(0.3, 1, 1);
	drawDoro(2);					// ���� �׸���
	drawIndo(2);					// �ε� �׸���
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 0, 6);			// ����� �̵�
	glScalef(4, 2, 2);			// ����� ũ�� ����
	drawBuilding();					// ����� �׸���
	glPopMatrix();
}

void drawZucha(){
	
	GLubyte *data;
	int Width, Height;
	GLint EnvMode = GL_REPLACE;
	GLint TexFilter = GL_LINEAR;

     // �ؽ�ó �̹��� �غ�
     glEnable(GL_TEXTURE_2D);
     data = LoadBmp("zucha.bmp", &Width, &Height);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
     free(data);

     // �ؽ�ó ȯ�� ����
     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, EnvMode);

     // �ؽ�ó ���� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexFilter);

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 4);
	glTexCoord2f(0, 1);
	glVertex3f(4, 0, 4);
	glTexCoord2f(0, 0);
	glVertex3f(4, 0, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawUndong(){
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 7);
	glVertex3f(4, 0, 7);
	glVertex3f(4, 0, 0);
	glEnd();
}

void drawDorm(){

		GLfloat dorm[][3] = {		// ����� �� ��ǥ ����
			{0, 0, 0},
			{0, 6, 0},
			{4, 6, 0},
			{0, 6, 8},
			{4, 6, 8},
			{0, 0, 0},
			{4, 0, 0},
			{0, 0, 8},
			{4, 0, 8}
		};
	
		glBegin(GL_POLYGON);				// ����� �ǹ� õ��
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(dorm[1]);
		glVertex3fv(dorm[2]);
		glVertex3fv(dorm[4]);
		glVertex3fv(dorm[3]);
		glEnd();

		glBegin(GL_POLYGON);				// ����� �ǹ�
		glColor3f(0.6, 0.6, 0.6);
		glVertex3fv(dorm[1]);
		glVertex3fv(dorm[5]);
		glVertex3fv(dorm[6]);
		glVertex3fv(dorm[2]);
		glEnd();
		
		glBegin(GL_POLYGON);				// ����� �ǹ� �ٴ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(dorm[6]);
		glVertex3fv(dorm[8]);
		glVertex3fv(dorm[7]);
		glVertex3fv(dorm[5]);
		glEnd();
		
		glBegin(GL_POLYGON);				// ����� �ǹ�
		glColor3f(0.64, 0.64, 0.64);
		glVertex3fv(dorm[8]);
		glVertex3fv(dorm[7]);
		glVertex3fv(dorm[3]);
		glVertex3fv(dorm[4]);
		glEnd();
		
		glBegin(GL_POLYGON);				// ����� �ǹ�
		glColor3f(0.62, 0.62, 0.62);
		glVertex3fv(dorm[7]);
		glVertex3fv(dorm[5]);
		glVertex3fv(dorm[1]);
		glVertex3fv(dorm[3]);
		glEnd();
		
		glBegin(GL_POLYGON);				// ����� �ǹ�
		glColor3f(0.66, 0.66, 0.66);
		glVertex3fv(dorm[6]);
		glVertex3fv(dorm[8]);
		glVertex3fv(dorm[4]);
		glVertex3fv(dorm[2]);
		glEnd();

}

void drawTennis(){
	
	GLfloat tennis[][3] = {
		{0, 0, 0},
		{0, 0.5, 0},
		{2, 0.5, 0},
		{0, 0.5, 2},
		{2, 0.5, 2},
		{0, 0, 0},
		{2, 0, 0},
		{0, 0, 2},
		{2, 0, 2}
	};

	glBegin(GL_POLYGON);				// �״Ͻ��� ö����
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[1]);
	glVertex3fv(tennis[5]);
	glVertex3fv(tennis[6]);
	glVertex3fv(tennis[2]);
	glEnd();

	glBegin(GL_POLYGON);				// �״Ͻ��� ö����
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[2]);
	glVertex3fv(tennis[6]);
	glVertex3fv(tennis[8]);
	glVertex3fv(tennis[4]);
	glEnd();

	glBegin(GL_POLYGON);				// �״Ͻ��� ö����
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[4]);
	glVertex3fv(tennis[8]);
	glVertex3fv(tennis[7]);
	glVertex3fv(tennis[3]);
	glEnd();

	glBegin(GL_POLYGON);				// �״Ͻ��� ö����
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[7]);
	glVertex3fv(tennis[5]);
	glVertex3fv(tennis[1]);
	glVertex3fv(tennis[3]);
	glEnd();
	
	glTranslatef(0, 0.05, 0);			// �ٴ��� ǥ���ϱ� ���� �ణ ���

	glBegin(GL_POLYGON);				// �״Ͻ��� �ٴ�
	glColor3f(0, 0.8, 0);
	glVertex3fv(tennis[7]);
	glVertex3fv(tennis[5]);
	glVertex3fv(tennis[6]);
	glVertex3fv(tennis[8]);
	glEnd();
}

void drawTree(){

	glPushMatrix();

	GLUquadricObj *obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	glColor3f(0.6, 0.2, 0);				// ����
	gluCylinder(obj, 0.1, 0.1, 0.5, 20, 20);
	glTranslatef(0, 0, 0.5);
	glColor3f(0, 1, 0);					// �ʷϻ�
	gluCylinder(obj, 0.2, 0.0, 0.5, 20, 20);
	glPopMatrix();
}

void drawGate(){

	GLfloat gateOne[][3] = {		// ���� 1�� �� ��ǥ ����
		{0, 0, 0},
		{-1.2, 1.1, 0},
		{-1.0, 1.1, 0},
		{-1.2, 1.1, 0.5},
		{-1.0, 1.1, 0.5},
		{-1.2, 0.1, 0},
		{-1.0, 0.1, 0},
		{-1.2, 0.1, 0.5},
		{-1.0, 0.1, 0.5}
	};

	GLfloat gateTwo[][3] = {
		{0, 0, 0},
		{-1.8, 0.9, 0},
		{-1.6, 0.9, 0},
		{-1.8, 0.9, 0.5},
		{-1.6, 0.9, 0.5},
		{-1.8, 0.1, 0},
		{-1.6, 0.1, 0},
		{-1.8, 0.1, 0.5},
		{-1.6, 0.1, 0.5}
	};

	GLfloat gateThree[][3] = {
		{0, 0, 0},
		{-1.8, 0.7, 0},
		{-1.2, 0.7, 0},
		{-1.8, 0.7, 0.5},
		{-1.2, 0.7, 0.5},
		{-1.8, 0.5, 0},
		{-1.2, 0.5, 0},
		{-1.8, 0.5, 0.5},
		{-1.2, 0.5, 0.5}

	};

	glBegin(GL_POLYGON);				// ���� 1�� ��
	glColor3f(0.3, 0.3, 0.3);
	glVertex3fv(gateOne[1]);
	glVertex3fv(gateOne[2]);
	glVertex3fv(gateOne[4]);
	glVertex3fv(gateOne[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// ���� 1�� ��
	glVertex3fv(gateOne[1]);
	glVertex3fv(gateOne[5]);
	glVertex3fv(gateOne[6]);
	glVertex3fv(gateOne[2]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 1�� ��
	glVertex3fv(gateOne[6]);
	glVertex3fv(gateOne[8]);
	glVertex3fv(gateOne[7]);
	glVertex3fv(gateOne[5]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 1�� ��
	glVertex3fv(gateOne[8]);
	glVertex3fv(gateOne[7]);
	glVertex3fv(gateOne[3]);
	glVertex3fv(gateOne[4]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 1�� ��
	glVertex3fv(gateOne[7]);
	glVertex3fv(gateOne[5]);
	glVertex3fv(gateOne[1]);
	glVertex3fv(gateOne[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// ���� 1�� ��
	glVertex3fv(gateOne[6]);
	glVertex3fv(gateOne[8]);
	glVertex3fv(gateOne[4]);
	glVertex3fv(gateOne[2]);
	glEnd();
	
	
	glBegin(GL_POLYGON);				// ���� 2�� ��
	glColor3f(0.3, 0.3, 0.3);
	glVertex3fv(gateTwo[1]);
	glVertex3fv(gateTwo[2]);
	glVertex3fv(gateTwo[4]);
	glVertex3fv(gateTwo[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// ���� 2�� ��
	glVertex3fv(gateTwo[1]);
	glVertex3fv(gateTwo[5]);
	glVertex3fv(gateTwo[6]);
	glVertex3fv(gateTwo[2]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 2�� ��
	glVertex3fv(gateTwo[6]);
	glVertex3fv(gateTwo[8]);
	glVertex3fv(gateTwo[7]);
	glVertex3fv(gateTwo[5]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 2�� ��
	glVertex3fv(gateTwo[8]);
	glVertex3fv(gateTwo[7]);
	glVertex3fv(gateTwo[3]);
	glVertex3fv(gateTwo[4]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 2�� ��
	glVertex3fv(gateTwo[7]);
	glVertex3fv(gateTwo[5]);
	glVertex3fv(gateTwo[1]);
	glVertex3fv(gateTwo[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// ���� 2�� ��
	glVertex3fv(gateTwo[6]);
	glVertex3fv(gateTwo[8]);
	glVertex3fv(gateTwo[4]);
	glVertex3fv(gateTwo[2]);
	glEnd();
	
	
	glBegin(GL_POLYGON);				// ���� 3�� ��
	glColor3f(0.3, 0.3, 0.3);
	glVertex3fv(gateThree[1]);
	glVertex3fv(gateThree[2]);
	glVertex3fv(gateThree[4]);
	glVertex3fv(gateThree[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// ���� 3�� ��
	glVertex3fv(gateThree[1]);
	glVertex3fv(gateThree[5]);
	glVertex3fv(gateThree[6]);
	glVertex3fv(gateThree[2]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 3�� ��
	glVertex3fv(gateThree[6]);
	glVertex3fv(gateThree[8]);
	glVertex3fv(gateThree[7]);
	glVertex3fv(gateThree[5]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 3�� ��
	glVertex3fv(gateThree[8]);
	glVertex3fv(gateThree[7]);
	glVertex3fv(gateThree[3]);
	glVertex3fv(gateThree[4]);
	glEnd();

	glBegin(GL_POLYGON);				// ���� 3�� ��
	glVertex3fv(gateThree[7]);
	glVertex3fv(gateThree[5]);
	glVertex3fv(gateThree[1]);
	glVertex3fv(gateThree[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// ���� 3�� ��
	glVertex3fv(gateThree[6]);
	glVertex3fv(gateThree[8]);
	glVertex3fv(gateThree[4]);
	glVertex3fv(gateThree[2]);
	glEnd();
	
}

void drawBuilding(){
	
		GLfloat build[][3] = {			// �ǹ� �� ��ǥ ����
			{0, 0, 0},
			{0, 1, 0},
			{1, 1, 0},
			{0, 1, 1},
			{1, 1, 1},
			{0, 0, 0},
			{1, 0, 0},
			{0, 0, 1},
			{1, 0, 1}
		};
	
		glBegin(GL_POLYGON);				// �ǹ� õ��
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[1]);
		glVertex3fv(build[2]);
		glVertex3fv(build[4]);
		glVertex3fv(build[3]);
		glEnd();

		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.6, 0.6, 0.6);
		glVertex3fv(build[1]);
		glVertex3fv(build[5]);
		glVertex3fv(build[6]);
		glVertex3fv(build[2]);
		glEnd();
		
		glBegin(GL_POLYGON);				// �ǹ� �ٴ�
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[5]);
		glEnd();
		
		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.64, 0.64, 0.64);
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[3]);
		glVertex3fv(build[4]);
		glEnd();
		
		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.62, 0.62, 0.62);
		glVertex3fv(build[7]);
		glVertex3fv(build[5]);
		glVertex3fv(build[1]);
		glVertex3fv(build[3]);
		glEnd();
		
		glBegin(GL_POLYGON);				// �ǹ�
		glColor3f(0.66, 0.66, 0.66);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[4]);
		glVertex3fv(build[2]);
		glEnd();
}

GLubyte *LoadBmp(const char *Path, int *Width, int *Height){

     HANDLE hFile;
     DWORD FileSize, dwRead;
     BITMAPFILEHEADER *fh=NULL;
     BITMAPINFOHEADER *ih;
     BYTE *pRaster;

     hFile=CreateFileA(Path,GENERIC_READ,0,NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

     if (hFile==INVALID_HANDLE_VALUE) {
          return NULL;
     }

     FileSize=GetFileSize(hFile,NULL);
     fh=(BITMAPFILEHEADER *)malloc(FileSize);
     ReadFile(hFile,fh,FileSize,&dwRead,NULL);
     CloseHandle(hFile);

     int len = FileSize - fh->bfOffBits;
     pRaster=(GLubyte *)malloc(len);
     memcpy(pRaster, (BYTE *)fh+fh->bfOffBits, len);

     // RGB�� ������ �ٲ۴�.
     for (BYTE *p=pRaster;p < pRaster + len - 3;p+=3) {
          BYTE b = *p;
          *p = *(p+2);
          *(p+2) = b;
     }

     ih=(BITMAPINFOHEADER *)((PBYTE)fh+sizeof(BITMAPFILEHEADER));
     *Width=ih->biWidth;
     *Height=ih->biHeight;

     free(fh);
     return pRaster;
}