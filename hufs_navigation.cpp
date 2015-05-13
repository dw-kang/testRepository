#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
 
void DoDisplay();
void DoKeyboard(unsigned char key, int x, int y);
void DoMenu(int value);
void reshape(GLsizei width, GLsizei height);

void drawRoad();					// 도로를 기준으로 전체적으로 그리는 함수
void drawLine();					// 중앙선
void drawDoro(GLfloat num);			// 도로
void drawIndo(GLfloat num);			// 인도
void drawSine(GLfloat len);			// 시냇가
void drawSDoro(GLint num);			// 부분 도로
void drawUDoro(GLint num);			// 언덕 도로
void drawBuilding();				// 1x1x1 베이스 건물
void drawDorm();					// 기숙사 건물
void drawGate();					// 정문
void drawTree();					// 나무
void drawTennis();					// 테니스장
void drawUndong();					// 운동장
void drawNetu();					// 자연과학대학
void drawGong();					// 공대
void drawGongBuilding();				// 공대건물
void drawLib();						// 도서관
void drawZucha();					// 주차장
void drawBon();						// 본관
void drawEomoon();					// 어문학관
void drawInmoon();					// 인문경상관
void drawLake();					// 명수당
GLubyte *LoadBmp(const char *Path, int *Width, int *Height);	// 텍스쳐 맵핑 함수


GLfloat xAngle, yAngle, zAngle;		// 좌표축
GLfloat ex, ey=5, ez=44.5;			// 관찰자의 위치
GLfloat tx=60, ty=-50, tz=100;		// 관찰자의 시점
GLfloat lx, ly=1, lz;				// 관찰자의 각도
GLfloat ortho=25;					// 화면 투영  
float ar;
int winWidth, winHeight;			// 화면 비율

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow){
	
	glutInitWindowPosition(100,100);	// 화면 위치
	glutInitWindowSize(700, 500);		// 화면 크기
	glutCreateWindow("HUFS Navigation Ver.1.0 ");		// 화면 생성 및 제목 표시줄
	glutDisplayFunc(DoDisplay);			// 화면 출력 함수 등록
	glutKeyboardFunc(DoKeyboard);		// 키보드 콜백 함수 등록
	glutReshapeFunc(reshape);			// 화면 변경시 콜백 함수 등록
	glutMainLoop();
	return 0;

}

void DoKeyboard(unsigned char key, int x, int y){	// 키보드 콜백 함수

     switch(key) {

		case '1':								// 정문~사거리
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-4;ey=5;ez=0;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '2':								// 사회교육원~사거리
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=7;ey=5;ez=24;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '3':								// 기숙사~사거리
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-12.7;ey=5;ez=24;
			tx=60;ty=-50;tz=100;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '4':								// 공대
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-1.5;ey=5.2;ez=49.3;
			tx=60;ty=-51;tz=108;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '5':								// 도서관
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=-0.9;ey=4.1;ez=55.6;
			tx=-97;ty=-80;tz=215;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;
	
		case '6':								// 본관
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=5.2;ey=5.2;ez=71.6;
			tx=86;ty=-51;tz=115;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;	

		case '7':								// 어문관
			ortho = 10;
			xAngle=0;yAngle=0;zAngle=0;
			ex=5.2;ey=5.5;ez=77.9;
			tx=-61;ty=-50;tz=200;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;	

		case '9':					// 반대편 전경
			ortho = 25;
			xAngle=0;yAngle=0;zAngle=0;
			ex=4;ey=4.5;ez=44.5;
			tx=-71;ty=-72;tz=135;
			lx=0;ly=1;lz=0;
			reshape(winWidth, winHeight);
			break;

		case '0':					// 전경
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

void reshape(int w, int h){			// Reshape 콜백 함수

	float aspectRatio;
	winWidth = w;
	winHeight = h;
	aspectRatio = (GLfloat)w / (GLfloat)h;		// 변화된 화면 비율 저장
	glViewport(0, 0, w, h);						// 투영 이미지를 출력하는 뷰포트 크기 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(w<=h)									// 화면 비율에 따라 직교투영의 영역 재설정
		glOrtho(-ortho, ortho, -ortho/aspectRatio, ortho/aspectRatio, -120, 120);
	else
		glOrtho(-ortho*aspectRatio, ortho*aspectRatio, -ortho, ortho, -120, 120);
		
}

void DoDisplay(){			// 화면 출력 내용 등록 함수

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 컬러 버퍼, 깊이 버퍼 초기화
	glEnable(GL_DEPTH_TEST);							// 깊이 테스트 활성화

	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);							// 모델뷰 설정
	glLoadIdentity();
	
	gluLookAt(ex, ey, ez, tx, ty, tz, lx, ly, lz);		// 키보드 입력에 따른 시점 전환

	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

	drawRoad();											// 도로를 포함한 폴리곤 출력

	glPopMatrix();

	glFlush();											// 화면 출력
}

void drawRoad(){						// 도로를 포함한 건물 그리는 함수

	glPushMatrix();
	
	glRotatef(-5, 0.0f, 1.0f, 0.0f);		// 도로를 위해 회전

	drawDoro(18);						// 18m 도로 그리기
	drawIndo(18);						// 18m 인도 그리기
	drawSine(18);						// 18m 시냇물 그리기
	
	glPushMatrix();;					// 교문 그리기
	drawGate();
	glTranslatef(0, 0, 0.5);			
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	drawGate();
	glPopMatrix();						// 교문 그리기 끝

	glPushMatrix();						// 나무 그리기 영역 시작
	
	glTranslatef(-1.2, 0.1, 2);			// 처음 그릴 나무로 이동
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// 처음 나무 그릴 각도로 회전
	drawTree();							// 나무 그리기

	for(int i=0; i<15; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}

	glTranslatef(2.2, 0, 0);			// 길 건너편으로 이동
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// 정문 방향으로 회전
	for(int i=0; i<16; i++){
		drawTree();						// 나무 그리기
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
	}
	glPopMatrix();						// 나무 그리기 영역 끝


	glTranslatef(0, 0, 17.8);			// 다음 도로로 이동
	glRotatef(10, 0.0f, 1.0f, 0.0f);	// 도로를 위해 회전
	drawDoro(9);						// 9m 도로 그리기
	drawIndo(9);						// 9m 인도 그리기
	drawSine(9);

	glPushMatrix();						// 테니스장 그리기 영역 시작
	glTranslatef(-3.7, 0, 1.5);			// 테니스장을 위해 이동
	drawTennis();
	glTranslatef(0, 0, 2.1);			// 테니스장을 위해 이동
	drawTennis();
	glPopMatrix();						// 테니스장 그리기 영역 끝

	glPushMatrix();						// 나무 그리기 영역 시작
	glTranslatef(-1.2, 0.1, 0);			// 처음 그릴 나무로 이동
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// 처음 나무 그릴 각도로 회전
	drawTree();							// 나무 그리기
	for(int i=0; i<7; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glTranslatef(2.2, -1, 0);			// 길 건너편으로 이동
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// 정문 방향으로 회전
	for(int i=0; i<8; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glPopMatrix();						// 나무 그리기 영역 끝


	glTranslatef(0, 0, 8.8);			// 다음 도로로 이동


	glPushMatrix();						// 9m짜리 도로 다음의 언덕쪽 짤도로 구역 시작
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	drawSDoro(3);						// 3m 도로+인도 그리기
	glTranslatef(0, 0, 5.6);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	drawUDoro(1);						// 3m 도로 그리기
	glTranslatef(0, 1, 2.8);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	drawUDoro(5);						// 5m 도로 그리기
	glTranslatef(0, 1, 4.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	drawUDoro(2);						// 2m 도로 그리기
	glTranslatef(0, 1, 1.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	drawUDoro(2);						// 2m 도로 그리기	
	glTranslatef(0, 1, 1.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	drawUDoro(3);						// 3m 도로 그리기
	glTranslatef(0, 1, 2.8);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	drawSDoro(4);						// 4m 도로 그리기
	
	glPushMatrix();						// 사회교육원 건물 그리기 구역
	glTranslatef(-3, 0, 3);				// 사회교육원1 건물 이동
	glRotatef(180, 0.0f, 1.0f, 0.0f);	// 사회교육원1 건물 회전
	glScalef(0.3, 0.5, 0.5);			// 사회교육원1 건물 크기 변형
	drawDorm();							// 사회교육원1 그리기
	glTranslatef(0, 0, 5);				// 사회교육원2 건물 이동
	glRotatef(90, 0.0f, 1.0f, 0.0f);	// 사회교육원2 건물 회전
	glScalef(0.5, 1, 1);				// 사회교육원2 건물 크기 변형
	drawDorm();							// 사회교육원2 그리기
	glTranslatef(13, 0, 7);				// 사회교육원3 건물 이동
	glRotatef(-90, 0.0f, 1.0f, 0.0f);	// 사회교육원3 건물 회전
	glScalef(1, 1, 2);					// 사회교육원3 건물 크기 변형
	drawDorm();							// 사회교육원3 그리기
	glPopMatrix();						// 사회교육원 건물 그리기 구역
	
	glPopMatrix();						// 9m짜리 도로 다음의 언덕쪽 짤도로 구역 끝

	glRotatef(-10, 0.0f, 1.0f, 0.0f);
	drawSDoro(36);						// 36m 도로+인도 그리기
	drawSine(36);

	glPushMatrix();						// 정심대도부터 공대까지 나무 구간
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// 처음 나무 그릴 각도로 회전
	glTranslatef(1.2, -3.5, 0);
	drawTree();							// 나무 그리기
	for(int i=0; i<31; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glTranslatef(-2.2, -1, 0);			// 길 건너편으로 이동
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// 정문 방향으로 회전
	for(int i=0; i<5; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glTranslatef(0, -2, 0);				// 다음 나무로 이동
	for(int i=0; i<25; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glPopMatrix();						// 정심대도부터 공대까지 나무 구간

	glPushMatrix();						// 기숙사 건물+도로 그리기 구역 시작
	glTranslatef(-1, 0, 2);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	drawDoro(9);						// 기숙사 가는 도로
	drawIndo(9);						// 기숙사 가는 인도

	glPushMatrix();						// 기숙사 가는 도로의 나무 구간
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// 처음 나무 그릴 각도로 회전
	glTranslatef(1.2, -1, 0);
	drawTree();							// 나무 그리기
	for(int i=0; i<9; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glTranslatef(-2.2, -1, 0);			// 길 건너편으로 이동
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// 정문 방향으로 회전
	for(int i=0; i<10; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glPopMatrix();						// 기숙사 가는 도로의 나무 구간

	glTranslatef(-1.5, 0, 11.5);			// 기숙사1 건물 이동
	glRotatef(90, 0.0f, 1.0f, 0.0f);	// 기숙사1 건물 회전
	glScalef(0.5, 0.5, 0.6);			// 기숙사1 건물 크기 변형
	drawDorm();							// 기숙사1 그리기
	glTranslatef(0, 0, 10);				// 기숙사2 건물 이동
	drawDorm();							// 기숙사2 그리기
	glTranslatef(-7, 0.7, 0);			// 기숙사3 건물 이동
	drawDorm();							// 기숙사3 그리기
	glTranslatef(0, 0, -10);				// 기숙사4 건물 이동
	drawDorm();							// 기숙사4 그리기
	glPopMatrix();						// 기숙사 건물+도로 그리기 구역 끝

	glPushMatrix();						// 운동장, 주차장, 자연대, 공대 그리기 구역 시작
	glTranslatef(3, 0.1, 17);			// 운동장 위치로 이동
	drawUndong();						// 운동장 그리기
	glTranslatef(0, 0, 8);				// 주차장 위치로 이동
	drawZucha();						// 주차장 그리기
	glTranslatef(10, 2, -1);				// 자연대 위치로 이동
	drawNetu();							// 자연대 그리기
	glTranslatef(-10, -2, 6);			// 공대 위치로 이동
	drawGong();							// 공대 그리기
	glTranslatef(-8.5, 0, 2);			// 도서관 위치로 이동
	drawLib();							// 도서관 그리기
	glPopMatrix();						// 운동장, 주차장, 자연대, 공대 그리기 구역 끝

	glTranslatef(0, 0, 35.4);			// 다음 도로로 이동
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	drawDoro(15);						// 15m 도로 그리기
	drawIndo(15);						// 15m 인도 그리기
		
	glPushMatrix();						// 공대에서 본관까지의 나무 구간
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// 처음 나무 그릴 각도로 회전
	glTranslatef(1.2, -1, 0);
	drawTree();							// 나무 그리기
	for(int i=0; i<13; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glTranslatef(-2.5, -1, 0);			// 길 건너편으로 이동
	glRotatef(180, 0.0f, 0.0f, 1.0f);	// 반대 방향으로 회전
	for(int i=0; i<14; i++){
		glTranslatef(0, -1, 0);			// 다음 나무로 이동
		drawTree();						// 나무 그리기
	}
	glPopMatrix();						// 공대에서 본관까지의 나무 구간 끝

	glPushMatrix();						// 명수당 그리는 구간
	glTranslatef(2, 0, 8);				// 명수당 위치로 이동
	drawLake();
	glPopMatrix();						// 명수당 그리는 구간 끝

	// 노천극장 가능?

	glTranslatef(0, 0, 14.5);			// 다음 도로로 이동
	glRotatef(-40, 0.0f, 1.0f, 0.0f);
	drawDoro(16);						// 16m 도로 그리기
	drawIndo(16);						// 16m 인도 그리기

	glPushMatrix();						// 본관 그리는 구역
	glTranslatef(7, 3, 5);				// 본관 그릴 위치로 이동
	drawBon();							// 본관 그리기
	glPopMatrix();						// 본관 그리는 구역 끝
	
	glPushMatrix();						// 어문관 그리는 구역
	glTranslatef(-6, 3, 12);				// 어문관 그릴 위치로 이동
	drawEomoon();						// 어문관 그리기
	glPopMatrix();						// 어문관 그리는 구역 끝

	// 인문관

	glTranslatef(0, 0, 15.5);			// 다음 도로로 이동
	glRotatef(10, 0.0f, 1.0f, 0.0f);
	drawDoro(5);						// 5m 도로 그리기
	drawIndo(5);						// 5m 인도 그리기


	glPopMatrix();
	glutPostRedisplay();
}

void drawUDoro(GLint num){

	switch(num){
	case 1:									// 3m 올라가는 도로 처리 부분
		glBegin(GL_POLYGON);				// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(-1, 1, 3);
		glEnd();
		
		glBegin(GL_LINES);					// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 2.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);			// 왼쪽 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 3);
		glVertex3f(-1, 1.1, 3);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);				// 왼쪽 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 3);
		glVertex3f(-1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);			// 왼쪽 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 3);
		glVertex3f(-1.6, 1.1, 3);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// 오른쪽 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(1, 1.1, 3);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// 오른쪽 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 3);
		glVertex3f(1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 오른쪽 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 3);
		glVertex3f(1.6, 1.1, 3);
		glEnd();

		break;

		case 2:								// 3m 도로 처리 부분
		glBegin(GL_POLYGON);				// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 2);
		glVertex3f(-1, 1, 2);
		glEnd();
		
		glBegin(GL_LINES);					// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 1.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 2);
		glVertex3f(-1, 1.1, 2);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 2);
		glVertex3f(-1.1, 1.1, 2);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 2);
		glVertex3f(-1.6, 1.1, 2);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 2);
		glVertex3f(1, 1.1, 2);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 2);
		glVertex3f(1.1, 1.1, 2);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 2);
		glVertex3f(1.6, 1.1, 2);
		glEnd();

		break;

		case 3:									// 5m 올라가는 도로 처리 부분
		glBegin(GL_POLYGON);					// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(-1, 1, 3);
		glEnd();
		
		glBegin(GL_LINES);						// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 2.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// 왼쪽 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 3);
		glVertex3f(-1, 1.1, 3);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);					// 왼쪽 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 3);
		glVertex3f(-1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// 왼쪽 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 3);
		glVertex3f(-1.6, 1.1, 3);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// 오른쪽 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 3);
		glVertex3f(1, 1.1, 3);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);					// 오른쪽 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 3);
		glVertex3f(1.1, 1.1, 3);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// 오른쪽 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 1.1, 3);
		glVertex3f(1.6, 1.1, 3);
		glEnd();

		break;

		case 5:									// 5m 올라가는 도로 처리 부분
		glBegin(GL_POLYGON);					// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 5);
		glVertex3f(-1, 1, 5);
		glEnd();
		
		glBegin(GL_LINES);						// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 1.1, 4.7);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// 왼쪽 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, -0.5);
		glVertex3f(-1, 1, 5);
		glVertex3f(-1, 1.1, 5);
		glVertex3f(-1, 0.1, -0.5);
		glEnd();
		
		glBegin(GL_POLYGON);					// 왼쪽 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1,   0.1, -0.5);
		glVertex3f(-1,   1.1, 5);
		glVertex3f(-1.1, 1.1, 5);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// 왼쪽 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, -0.5);
		glVertex3f(-1.1, 0.1, -0.5);
		glVertex3f(-1.1, 1.1, 5);
		glVertex3f(-1.6, 1.1, 5);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);				// 오른쪽 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 1, 5);
		glVertex3f(1, 1.1, 5);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);					// 오른쪽 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   1.1, 5);
		glVertex3f(1.1, 1.1, 5);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);				// 오른쪽 보도 블럭
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
	case 3:									// 3m 도로 처리 부분
		glBegin(GL_POLYGON);				// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 1);
		glVertex3f(1, 0, 6);
		glVertex3f(-1, 0, 6);
		glEnd();
		
		glBegin(GL_LINES);					// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 5.5);
		glEnd();

		glPushMatrix();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, 3.8);
		glVertex3f(-1, 0, 6);
		glVertex3f(-1, 0.1, 6);
		glVertex3f(-1, 0.1, 3.8);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, 3.8);
		glVertex3f(-1,   0.1, 3.8);
		glVertex3f(-1,   0.1, 6);
		glVertex3f(-1.1, 0.1, 6);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, 3.5);
		glVertex3f(-1.1, 0.1, 3.5);
		glVertex3f(-1.1, 0.1, 6);
		glVertex3f(-1.6, 0.1, 6);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 6);
		glVertex3f(1, 0.1, 6);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   0.1, 6);
		glVertex3f(1.1, 0.1, 6);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 0.1, 6);
		glVertex3f(1.6, 0.1, 6);
		glEnd();

		glPopMatrix();

		break;

		case 4:								// 4cm 도로 처리 부분
		glBegin(GL_POLYGON);				// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 4);
		glVertex3f(-1, 0, 4);
		glEnd();
		
		glBegin(GL_LINES);					// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 3.5);
		glEnd();

		glPushMatrix();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, 0);
		glVertex3f(-1, 0, 4);
		glVertex3f(-1, 0.1, 4);
		glVertex3f(-1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, 0);
		glVertex3f(-1,   0.1, 0);
		glVertex3f(-1,   0.1, 4);
		glVertex3f(-1.1, 0.1, 4);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, 0);
		glVertex3f(-1.1, 0.1, 0);
		glVertex3f(-1.1, 0.1, 4);
		glVertex3f(-1.6, 0.1, 4);
		glEnd();

		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 4);
		glVertex3f(1, 0.1, 4);
		glVertex3f(1, 0.1, 0);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1,   0.1, 0);
		glVertex3f(1,   0.1, 4);
		glVertex3f(1.1, 0.1, 4);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(1.6, 0.1, 0);
		glVertex3f(1.1, 0.1, 0);
		glVertex3f(1.1, 0.1, 4);
		glVertex3f(1.6, 0.1, 4);
		glEnd();

		glPopMatrix();

		break;

		case 36:							// 26cm 도로 처리 부분
		glBegin(GL_POLYGON);				// 도로 아스팔트 부분
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, 0, 36);
		glVertex3f(-1, 0, 36);
		glEnd();
		
		glBegin(GL_LINES);					// 도로 중앙선
		glLineWidth(10);
		glColor3f(1, 0.5, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 35.5);
		glEnd();

		glPushMatrix();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(-1, 0, 3);
		glVertex3f(-1, 0, 36);
		glVertex3f(-1, 0.1, 36);
		glVertex3f(-1, 0.1, 3);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(-1.1, 0.1, 3);
		glVertex3f(-1,   0.1, 3);
		glVertex3f(-1,   0.1, 36);
		glVertex3f(-1.1, 0.1, 36);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
		glBegin(GL_POLYGON);
		glVertex3f(-1.6, 0.1, 3);
		glVertex3f(-1.1, 0.1, 3);
		glVertex3f(-1.1, 0.1, 36);
		glVertex3f(-1.6, 0.1, 36);
		glEnd();
	
		glColor3f(0.5, 0.5, 0.5);	// 도로와 보도 블럭 사이
		glBegin(GL_POLYGON);
		glVertex3f(1, 0, 3);
		glVertex3f(1, 0, 36);
		glVertex3f(1, 0.1, 36);
		glVertex3f(1, 0.1, 3);
		glEnd();
		
		glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
		glVertex3f(1.1, 0.1, 3);
		glVertex3f(1,   0.1, 3);
		glVertex3f(1,   0.1, 36);
		glVertex3f(1.1, 0.1, 36);
		glEnd();
		
		glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
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
	
	glBegin(GL_POLYGON);				// 도로 아스팔트 부분
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, len);
	glVertex3f(-1, 0, len);
	glEnd();
	
	glBegin(GL_LINES);					// 도로 중앙선
	glLineWidth(10);
	glColor3f(1, 0.5, 0);
	glVertex3f(0, 0.1, 0);
	glVertex3f(0, 0.1, len-0.5);
	glEnd();

}

void drawIndo(GLfloat len){
	
	glPushMatrix();

	glColor3f(0.5, 0.5, 0.5);	// 좌측 도로와 보도 블럭 사이
	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(-1, 0, len);
	glVertex3f(-1, 0.1, len);
	glVertex3f(-1, 0.1, 0);
	glEnd();
	
	glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
	glVertex3f(-1.1, 0.1, 0);
	glVertex3f(-1,   0.1, 0);
	glVertex3f(-1,   0.1, len);
	glVertex3f(-1.1, 0.1, len);
	glEnd();
	
	glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
	glBegin(GL_POLYGON);
	glVertex3f(-1.6, 0.1, 0);
	glVertex3f(-1.1, 0.1, 0);
	glVertex3f(-1.1, 0.1, len);
	glVertex3f(-1.6, 0.1, len);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);	// 우측 도로와 보도 블럭 사이
	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, len);
	glVertex3f(1, 0.1, len);
	glVertex3f(1, 0.1, 0);
	glEnd();
	
	glBegin(GL_POLYGON);		// 도로와 보도 블럭 사이
	glVertex3f(1.1, 0.1, 0);
	glVertex3f(1,   0.1, 0);
	glVertex3f(1,   0.1, len);
	glVertex3f(1.1, 0.1, len);
	glEnd();
	
	glColor3f(0.9, 0.9, 0.9);	// 보도 블럭
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
	
	glPushMatrix();					// 어문관 올라가는 도로
	glScalef(1, 1, 0.5);
	glRotatef(-35, 0.0f, 0.0f, 1.0f);// 도로 회전
	glRotatef(90, 0.0f, 1.0f, 0.0f);// 도로 회전
	drawDoro(5.5);
	drawIndo(5.5);
	glRotatef(-35, 1.0f, 0.0f, 0.0f);// 도로 회전
	glRotatef(180, 0.0f, 1.0f, 0.0f);// 도로 회전
	drawDoro(2);
	drawIndo(2);
	glPopMatrix();					// 어문관 올라가는 도로 끝

	glPushMatrix();					// 어문관1 건물
	glTranslatef(-4, 0, -1);
	glScalef(2, 2, 2);
	drawBuilding();
	glPopMatrix();					// 어문관1 건물 끝

	glPushMatrix();					// 어문관2 건물
	glTranslatef(-4, 0, 1.5);
	glScalef(3, 2, 1);
	drawBuilding();					// 어문관2 그리기
	glPopMatrix();					// 어문관2 건물 끝

	glPushMatrix();					// 어문관3 건물
	glTranslatef(-6.5, 0, -2.5);
	glScalef(4, 2, 1);
	drawBuilding();					// 어문관3 그리기
	glPopMatrix();					// 어문관3 건물 끝
}

void drawBon(){

	glPushMatrix();					// 본관 가운데 부분
	glTranslatef(2, 0, 0);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	glScalef(1, 2.5, 1.5);
	drawBuilding();
	glPopMatrix();

	glPushMatrix();					// 본관 왼쪽 부분
	glTranslatef(2.8, 0, 0.3);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glScalef(4, 2, 1.3);
	drawBuilding();
	glPopMatrix();
	
	glPushMatrix();					// 본관 오른쪽 부분
	glTranslatef(2.8, 0, 0.3);
	glRotatef(-30, 0.0f, 1.0f, 0.0f);
	glScalef(1.3, 2, 4);
	drawBuilding();
	glPopMatrix();

	glPushMatrix();				// 본관 올라가는 도로
	glTranslatef(-1, 0, 5);
	glScalef(1, 1, 0.5);
	glRotatef(35, 0.0f, 0.0f, 1.0f);// 도로 회전
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// 도로 회전
	drawDoro(5.5);
	drawIndo(5.5);
	glPopMatrix();
	
	glPushMatrix();				// 본관 앞의 도로
	glTranslatef(4.5, 0, -4);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);// 도로 회전
	glScalef(0.5, 1, 1);
	drawDoro(6);
	glPopMatrix();
	
	glPushMatrix();				// 본관 앞의 도로
	glTranslatef(-0.8, 0, -1.3);
	glRotatef(0, 0.0f, 1.0f, 0.0f);// 도로 회전
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
	glRotatef(-90, 1.0f, 0.0f, 0.0f);	// 회전
	gluCylinder(obj, 1.2, 1.2, 3, 20, 20);	// 가운데 원통형
	
	glColor3f(0.65, 0.65, 0.65);
	glTranslatef(0, 0, 3);
	gluDisk(obj, 0, 1.2, 50, 50);			// 원통형의 윗면
	gluDeleteQuadric(obj);
	glPopMatrix();

	glPushMatrix();						// 도서관 짧은 부분 건물
	glTranslatef(0, 3,0);
	glRotatef(-120, 0.0f, 1.0f, 0.0f);	// 회전
	glScalef(2, 2, 3);		
	drawBuilding();
	glPopMatrix();

	glPushMatrix();						// 도서관 긴 부분 건물
	glTranslatef(-1.5, 3, 0);
	glScalef(2, 2, 6);
	drawBuilding();
	glPopMatrix();

	glPushMatrix();				// 도서관 주차장
	glTranslatef(-4, 3, -8);
	glScalef(0.8, 1, 0.8);
	drawZucha();
	glPopMatrix();

	glPushMatrix();				// 도서관 올라가는 도로
	glTranslatef(5, 0, -3);
	glScalef(1, 1, 0.5);
	glRotatef(-30, 0.0f, 0.0f, 1.0f);// 도로 회전
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// 도로 회전
	drawDoro(6);
	drawIndo(6);
	glPopMatrix();
	
	glPushMatrix();				// 도서관 옆의 도로
	glTranslatef(0, 3, -3);
	glScalef(1, 1, 0.5);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// 도로 회전
	drawDoro(3);
	drawIndo(3);
	glPopMatrix();
}

void drawGong(){

	glPushMatrix();
	glScalef(1.5, 2, 4);			// 공대1 건물 크기 변형
	drawGongBuilding();				// 공대1 건물 그리기
	glPopMatrix();

	glPushMatrix();
	glScalef(4, 2, 1.5);			// 공대2 건물 크기 변형
	glTranslatef(1.1, 0, -0.1);		// 공대2 건물 이동
	glRotatef(270, 0.0f, 1.0f, 0.0f);// 공대2 건물 회전
	drawGongBuilding();				// 공대2 건물 그리기
	glPopMatrix();
	
	glPushMatrix();
	glScalef(1.5, 2, 4);			// 공대3 건물 크기 변형
	glTranslatef(3.1, 0, 1);		// 공대3 건물 이동
	glRotatef(180, 0.0f, 1.0f, 0.0f);// 공대3 건물 회전
	drawGongBuilding();				// 공대3 건물 그리기
	glPopMatrix();
	
	glPushMatrix();
	glScalef(4, 2, 1.5);			// 공대4 건물 크기 변형
	glTranslatef(0.1, 0, 2.8);		// 공대4 건물 이동
	glRotatef(90, 0.0f, 1.0f, 0.0f);// 공대4 건물 회전
	drawGongBuilding();				// 공대4 건물 그리기
	glPopMatrix();
}

void drawGongBuilding(){
	
	GLubyte *data;
	int Width, Height;
	GLint EnvMode = GL_REPLACE;
	GLint TexFilter = GL_LINEAR;

     // 텍스처 이미지 준비
	data = LoadBmp("gong.bmp", &Width, &Height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
	free(data);

     // 텍스처 환경 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, EnvMode);

     // 텍스처 필터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexFilter);

		GLfloat build[][3] = {			// 건물 블럭 좌표 정의
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

		glBegin(GL_POLYGON);				// 건물 천장
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[1]);
		glVertex3fv(build[2]);
		glVertex3fv(build[4]);
		glVertex3fv(build[3]);
		glEnd();

		glBegin(GL_POLYGON);				// 건물
		glColor3f(0.6, 0.6, 0.6);
		glVertex3fv(build[1]);
		glVertex3fv(build[5]);
		glVertex3fv(build[6]);
		glVertex3fv(build[2]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 건물 바닥
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[5]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 건물
		glColor3f(0.64, 0.64, 0.64);	
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[3]);
		glVertex3fv(build[4]);
		glEnd();
		
		
		glEnable(GL_TEXTURE_2D);			// 텍스쳐 활성화
		glBegin(GL_POLYGON);				// 바깥쪽 건물
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
		glDisable(GL_TEXTURE_2D);			// 텍스쳐 비활성화
		
		glBegin(GL_POLYGON);				// 건물
		glColor3f(0.66, 0.66, 0.66);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[4]);
		glVertex3fv(build[2]);
		glEnd();
}

void drawNetu(){
	glPushMatrix();
	glScalef(2, 3, 5);				// 자연대 건물 크기 변형
	drawBuilding();					// 자연대 건물 그리기
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 0.6);			// 도로 폭 변형
	glTranslatef(-2, 0, 4);			// 도로 이동
	glRotatef(40, 0.0f, 0.0f, 1.0f);// 도로 회전
	glRotatef(-90, 0.0f, 1.0f, 0.0f);// 도로 회전
	glScalef(0.5, 1, 1);
	drawDoro(3.5);					// 도로 그리기
	drawIndo(3.5);					// 인도 그리
	glPopMatrix();

	glPushMatrix();
//	glRotatef(-40, 0.0f, 0.0f, 1.0f);// 도로 회전
	glTranslatef(-2, 0, 2.5);			// 도로 이동
	glRotatef(90, 0.0f, 1.0f, 0.0f);// 도로 회전
	glScalef(0.3, 1, 1);
	drawDoro(2);					// 도로 그리기
	drawIndo(2);					// 인도 그리기
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 0, 6);			// 세향관 이동
	glScalef(4, 2, 2);			// 세향관 크기 변형
	drawBuilding();					// 세향관 그리기
	glPopMatrix();
}

void drawZucha(){
	
	GLubyte *data;
	int Width, Height;
	GLint EnvMode = GL_REPLACE;
	GLint TexFilter = GL_LINEAR;

     // 텍스처 이미지 준비
     glEnable(GL_TEXTURE_2D);
     data = LoadBmp("zucha.bmp", &Width, &Height);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
     free(data);

     // 텍스처 환경 설정
     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, EnvMode);

     // 텍스처 필터 설정
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

		GLfloat dorm[][3] = {		// 기숙사 블럭 좌표 정의
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
	
		glBegin(GL_POLYGON);				// 기숙사 건물 천장
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(dorm[1]);
		glVertex3fv(dorm[2]);
		glVertex3fv(dorm[4]);
		glVertex3fv(dorm[3]);
		glEnd();

		glBegin(GL_POLYGON);				// 기숙사 건물
		glColor3f(0.6, 0.6, 0.6);
		glVertex3fv(dorm[1]);
		glVertex3fv(dorm[5]);
		glVertex3fv(dorm[6]);
		glVertex3fv(dorm[2]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 기숙사 건물 바닥
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(dorm[6]);
		glVertex3fv(dorm[8]);
		glVertex3fv(dorm[7]);
		glVertex3fv(dorm[5]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 기숙사 건물
		glColor3f(0.64, 0.64, 0.64);
		glVertex3fv(dorm[8]);
		glVertex3fv(dorm[7]);
		glVertex3fv(dorm[3]);
		glVertex3fv(dorm[4]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 기숙사 건물
		glColor3f(0.62, 0.62, 0.62);
		glVertex3fv(dorm[7]);
		glVertex3fv(dorm[5]);
		glVertex3fv(dorm[1]);
		glVertex3fv(dorm[3]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 기숙사 건물
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

	glBegin(GL_POLYGON);				// 테니스장 철조망
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[1]);
	glVertex3fv(tennis[5]);
	glVertex3fv(tennis[6]);
	glVertex3fv(tennis[2]);
	glEnd();

	glBegin(GL_POLYGON);				// 테니스장 철조망
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[2]);
	glVertex3fv(tennis[6]);
	glVertex3fv(tennis[8]);
	glVertex3fv(tennis[4]);
	glEnd();

	glBegin(GL_POLYGON);				// 테니스장 철조망
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[4]);
	glVertex3fv(tennis[8]);
	glVertex3fv(tennis[7]);
	glVertex3fv(tennis[3]);
	glEnd();

	glBegin(GL_POLYGON);				// 테니스장 철조망
	glColor3f(0.2, 0.2, 0.2);
	glVertex3fv(tennis[7]);
	glVertex3fv(tennis[5]);
	glVertex3fv(tennis[1]);
	glVertex3fv(tennis[3]);
	glEnd();
	
	glTranslatef(0, 0.05, 0);			// 바닥을 표시하기 위해 약간 상승

	glBegin(GL_POLYGON);				// 테니스장 바닥
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
	glColor3f(0.6, 0.2, 0);				// 갈색
	gluCylinder(obj, 0.1, 0.1, 0.5, 20, 20);
	glTranslatef(0, 0, 0.5);
	glColor3f(0, 1, 0);					// 초록색
	gluCylinder(obj, 0.2, 0.0, 0.5, 20, 20);
	glPopMatrix();
}

void drawGate(){

	GLfloat gateOne[][3] = {		// 교문 1번 블럭 좌표 정의
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

	glBegin(GL_POLYGON);				// 교문 1번 블럭
	glColor3f(0.3, 0.3, 0.3);
	glVertex3fv(gateOne[1]);
	glVertex3fv(gateOne[2]);
	glVertex3fv(gateOne[4]);
	glVertex3fv(gateOne[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// 교문 1번 블럭
	glVertex3fv(gateOne[1]);
	glVertex3fv(gateOne[5]);
	glVertex3fv(gateOne[6]);
	glVertex3fv(gateOne[2]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 1번 블럭
	glVertex3fv(gateOne[6]);
	glVertex3fv(gateOne[8]);
	glVertex3fv(gateOne[7]);
	glVertex3fv(gateOne[5]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 1번 블럭
	glVertex3fv(gateOne[8]);
	glVertex3fv(gateOne[7]);
	glVertex3fv(gateOne[3]);
	glVertex3fv(gateOne[4]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 1번 블럭
	glVertex3fv(gateOne[7]);
	glVertex3fv(gateOne[5]);
	glVertex3fv(gateOne[1]);
	glVertex3fv(gateOne[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// 교문 1번 블럭
	glVertex3fv(gateOne[6]);
	glVertex3fv(gateOne[8]);
	glVertex3fv(gateOne[4]);
	glVertex3fv(gateOne[2]);
	glEnd();
	
	
	glBegin(GL_POLYGON);				// 교문 2번 블럭
	glColor3f(0.3, 0.3, 0.3);
	glVertex3fv(gateTwo[1]);
	glVertex3fv(gateTwo[2]);
	glVertex3fv(gateTwo[4]);
	glVertex3fv(gateTwo[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// 교문 2번 블럭
	glVertex3fv(gateTwo[1]);
	glVertex3fv(gateTwo[5]);
	glVertex3fv(gateTwo[6]);
	glVertex3fv(gateTwo[2]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 2번 블럭
	glVertex3fv(gateTwo[6]);
	glVertex3fv(gateTwo[8]);
	glVertex3fv(gateTwo[7]);
	glVertex3fv(gateTwo[5]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 2번 블럭
	glVertex3fv(gateTwo[8]);
	glVertex3fv(gateTwo[7]);
	glVertex3fv(gateTwo[3]);
	glVertex3fv(gateTwo[4]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 2번 블럭
	glVertex3fv(gateTwo[7]);
	glVertex3fv(gateTwo[5]);
	glVertex3fv(gateTwo[1]);
	glVertex3fv(gateTwo[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// 교문 2번 블럭
	glVertex3fv(gateTwo[6]);
	glVertex3fv(gateTwo[8]);
	glVertex3fv(gateTwo[4]);
	glVertex3fv(gateTwo[2]);
	glEnd();
	
	
	glBegin(GL_POLYGON);				// 교문 3번 블럭
	glColor3f(0.3, 0.3, 0.3);
	glVertex3fv(gateThree[1]);
	glVertex3fv(gateThree[2]);
	glVertex3fv(gateThree[4]);
	glVertex3fv(gateThree[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// 교문 3번 블럭
	glVertex3fv(gateThree[1]);
	glVertex3fv(gateThree[5]);
	glVertex3fv(gateThree[6]);
	glVertex3fv(gateThree[2]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 3번 블럭
	glVertex3fv(gateThree[6]);
	glVertex3fv(gateThree[8]);
	glVertex3fv(gateThree[7]);
	glVertex3fv(gateThree[5]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 3번 블럭
	glVertex3fv(gateThree[8]);
	glVertex3fv(gateThree[7]);
	glVertex3fv(gateThree[3]);
	glVertex3fv(gateThree[4]);
	glEnd();

	glBegin(GL_POLYGON);				// 교문 3번 블럭
	glVertex3fv(gateThree[7]);
	glVertex3fv(gateThree[5]);
	glVertex3fv(gateThree[1]);
	glVertex3fv(gateThree[3]);
	glEnd();
	
	glBegin(GL_POLYGON);				// 교문 3번 블럭
	glVertex3fv(gateThree[6]);
	glVertex3fv(gateThree[8]);
	glVertex3fv(gateThree[4]);
	glVertex3fv(gateThree[2]);
	glEnd();
	
}

void drawBuilding(){
	
		GLfloat build[][3] = {			// 건물 블럭 좌표 정의
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
	
		glBegin(GL_POLYGON);				// 건물 천장
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[1]);
		glVertex3fv(build[2]);
		glVertex3fv(build[4]);
		glVertex3fv(build[3]);
		glEnd();

		glBegin(GL_POLYGON);				// 건물
		glColor3f(0.6, 0.6, 0.6);
		glVertex3fv(build[1]);
		glVertex3fv(build[5]);
		glVertex3fv(build[6]);
		glVertex3fv(build[2]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 건물 바닥
		glColor3f(0.8, 0.8, 0.8);
		glVertex3fv(build[6]);
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[5]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 건물
		glColor3f(0.64, 0.64, 0.64);
		glVertex3fv(build[8]);
		glVertex3fv(build[7]);
		glVertex3fv(build[3]);
		glVertex3fv(build[4]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 건물
		glColor3f(0.62, 0.62, 0.62);
		glVertex3fv(build[7]);
		glVertex3fv(build[5]);
		glVertex3fv(build[1]);
		glVertex3fv(build[3]);
		glEnd();
		
		glBegin(GL_POLYGON);				// 건물
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

     // RGB로 순서를 바꾼다.
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