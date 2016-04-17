/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

#include <Eigen/Eigen>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <GL/freeglut.h>

using namespace std;
using namespace Eigen;

#define sp system("pause")
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define FORD(i,a,b) for(int i=a;i>=b;--i)
#define REP(i,n) FOR(i,0,(int)n-1)
#define ll long long
#define CUBE_SIZE 20

int layer = 0;

class point {
public:
	double x, y, z;
	point() {

	}
	point(double px, double py, double pz) {
		x = px;
		y = py;
		z = pz;
	}
};

class color {

public :
	float r, g, b;

	color(float ir, float ig, float ib) {
		r = ir;
		g = ig;
		b = ib;
	}

	float * getArray() {
		float c[3];
		c[0] = r;
		c[1] = g;
		c[2] = b;
		return c;
	}
};

class State {

	/*
	0 - Front
	1 - Back
	2 - Left
	3 - Right
	4 - Up
	5 - Down
	*/

public:
	char faces[6][CUBE_SIZE][CUBE_SIZE];

	State() {
		REP(k, 6) {
			REP(i, CUBE_SIZE)
				REP(j, CUBE_SIZE)
				faces[k][i][j] = k;
		}
	}

	void printCube(int type=0) {

		if (type==0) {
			printf("~~~~~~~~~~~~~~  C U B E  ~~~~~~~~~~~~~~\n");
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					printf("  ");
				REP(j, CUBE_SIZE)
					printf("%2d", faces[1][i][j]);
				REP(j, CUBE_SIZE)
					printf("  ");
				printf("\n");
			}

			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					printf("  ");
				REP(j, CUBE_SIZE)
					printf("%2d", faces[4][i][j]);
				REP(j, CUBE_SIZE)
					printf("  ");
				printf("\n");
			}

			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					printf("%2d", faces[2][i][j]);
				REP(j, CUBE_SIZE)
					printf("%2d", faces[0][i][j]);
				REP(j, CUBE_SIZE)
					printf("%2d", faces[3][i][j]);
				printf("\n");
			}

			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					printf("  ");
				REP(j, CUBE_SIZE)
					printf("%2d", faces[5][i][j]);
				REP(j, CUBE_SIZE)
					printf("  ");
				printf("\n");
			};
			printf("\n");

		}
		else if (type==1) {
			REP(i, 3) {
				REP(k, 6) {
					REP(j, 3)
						printf("%2d", faces[k][i][j]);
					printf(" ");
				}
				printf("\n");
			}
		}
	}

	void front_anticlock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
			faces[4][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[3][CUBE_SIZE-1-i][layer];
			faces[3][CUBE_SIZE-1-i][layer] = faces[5][layer][i];
			faces[5][layer][i] = faces[2][i][CUBE_SIZE-1-layer];
			faces[2][i][CUBE_SIZE-1-layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[0][layer][CUBE_SIZE-1-i];
				faces[0][layer][CUBE_SIZE-1-i] = faces[0][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
				faces[0][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[0][CUBE_SIZE-1-layer][i];
				faces[0][CUBE_SIZE-1-layer][i] = faces[0][i][layer];
				faces[0][i][layer] = t[i];
			}
		}

	}

	void front_clock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE-1-layer][i];
			faces[4][CUBE_SIZE-1-layer][i] = faces[2][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
			faces[2][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[5][layer][CUBE_SIZE-1-i];
			faces[5][layer][CUBE_SIZE-1-i] = faces[3][i][layer];
			faces[3][i][layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[0][layer][i];
				faces[0][layer][i] = faces[0][CUBE_SIZE-1-i][layer];
				faces[0][CUBE_SIZE-1-i][layer] = faces[0][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
				faces[0][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[0][i][CUBE_SIZE-1-layer];
				faces[0][i][CUBE_SIZE-1-layer] = t[i];
			}
		}

	}

	void back_anticlock() {
		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][layer][i];
			faces[4][layer][i] = faces[2][CUBE_SIZE-1-i][layer];
			faces[2][CUBE_SIZE-1-i][layer] = faces[5][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
			faces[5][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[3][i][CUBE_SIZE-1-layer];
			faces[3][i][CUBE_SIZE-1-layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[1][layer][CUBE_SIZE-1-i];
				faces[1][layer][CUBE_SIZE-1-i] = faces[1][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
				faces[1][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[1][CUBE_SIZE-1-layer][i];
				faces[1][CUBE_SIZE-1-layer][i] = faces[1][i][layer];
				faces[1][i][layer] = t[i];
			}
		}
	}

	void back_clock() {
		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][layer][CUBE_SIZE-1-i];
			faces[4][layer][CUBE_SIZE-1-i] = faces[3][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
			faces[3][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[5][CUBE_SIZE-1-layer][i];
			faces[5][CUBE_SIZE-1-layer][i] = faces[2][i][layer];
			faces[2][i][layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[1][layer][i];
				faces[1][layer][i] = faces[1][CUBE_SIZE-1-i][layer];
				faces[1][CUBE_SIZE-1-i][layer] = faces[1][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
				faces[1][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[1][i][CUBE_SIZE-1-layer];
				faces[1][i][CUBE_SIZE-1-layer] = t[i];
			}
		}
	}

	void left_anticlock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE-1-i][layer];
			faces[4][CUBE_SIZE-1-i][layer] = faces[0][CUBE_SIZE-1-i][layer];
			faces[0][CUBE_SIZE-1-i][layer] = faces[5][CUBE_SIZE-1-i][layer];
			faces[5][CUBE_SIZE-1-i][layer] = faces[1][i][CUBE_SIZE-1-layer];
			faces[1][i][CUBE_SIZE-1-layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[2][layer][CUBE_SIZE-1-i];
				faces[2][layer][CUBE_SIZE-1-i] = faces[2][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
				faces[2][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[2][CUBE_SIZE-1-layer][i];
				faces[2][CUBE_SIZE-1-layer][i] = faces[2][i][layer];
				faces[2][i][layer] = t[i];
			}
		}
	}

	void left_clock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][i][layer];
			faces[4][i][layer] = faces[1][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
			faces[1][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[5][i][layer];
			faces[5][i][layer] = faces[0][i][layer];
			faces[0][i][layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[2][layer][i];
				faces[2][layer][i] = faces[2][CUBE_SIZE-1-i][layer];
				faces[2][CUBE_SIZE-1-i][layer] = faces[2][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
				faces[2][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[2][i][CUBE_SIZE-1-layer];
				faces[2][i][CUBE_SIZE-1-layer] = t[i];
			}
		}

	}

	void right_anticlock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][i][CUBE_SIZE-1-layer];
			faces[4][i][CUBE_SIZE-1-layer] = faces[1][CUBE_SIZE-1-i][layer];
			faces[1][CUBE_SIZE-1-i][layer] = faces[5][i][CUBE_SIZE-1-layer];
			faces[5][i][CUBE_SIZE-1-layer] = faces[0][i][CUBE_SIZE-1-layer];
			faces[0][i][CUBE_SIZE-1-layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[3][layer][CUBE_SIZE-1-i];
				faces[3][layer][CUBE_SIZE-1-i] = faces[3][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
				faces[3][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[3][CUBE_SIZE-1-layer][i];
				faces[3][CUBE_SIZE-1-layer][i] = faces[3][i][layer];
				faces[3][i][layer] = t[i];
			}
		}

	}

	void right_clock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
			faces[4][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[0][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
			faces[0][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[5][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
			faces[5][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[1][i][layer];
			faces[1][i][layer] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[3][layer][i];
				faces[3][layer][i] = faces[3][CUBE_SIZE-1-i][layer];
				faces[3][CUBE_SIZE-1-i][layer] = faces[3][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
				faces[3][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[3][i][CUBE_SIZE-1-layer];
				faces[3][i][CUBE_SIZE-1-layer] = t[i];
			}
		}

	}

	void up_anticlock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[1][layer][i];
			faces[1][layer][i] = faces[3][layer][i];
			faces[3][layer][i] = faces[0][layer][i];
			faces[0][layer][i] = faces[2][layer][i];
			faces[2][layer][i] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[4][layer][CUBE_SIZE-1-i];
				faces[4][layer][CUBE_SIZE-1-i] = faces[4][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
				faces[4][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[4][CUBE_SIZE-1-layer][i];
				faces[4][CUBE_SIZE-1-layer][i] = faces[4][i][layer];
				faces[4][i][layer] = t[i];
			}
		}
	}

	void up_clock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[1][layer][CUBE_SIZE-1-i];
			faces[1][layer][CUBE_SIZE-1-i] = faces[2][layer][CUBE_SIZE-1-i];
			faces[2][layer][CUBE_SIZE-1-i] = faces[0][layer][CUBE_SIZE-1-i];
			faces[0][layer][CUBE_SIZE-1-i] = faces[3][layer][CUBE_SIZE-1-i];
			faces[3][layer][CUBE_SIZE-1-i] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[4][layer][i];
				faces[4][layer][i] = faces[4][CUBE_SIZE-1-i][layer];
				faces[4][CUBE_SIZE-1-i][layer] = faces[4][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
				faces[4][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[4][i][CUBE_SIZE-1-layer];
				faces[4][i][CUBE_SIZE-1-layer] = t[i];
			}
		}
	}

	void down_anticlock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[0][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
			faces[0][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[3][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
			faces[3][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[1][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
			faces[1][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[2][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
			faces[2][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[5][layer][CUBE_SIZE-1-i];
				faces[5][layer][CUBE_SIZE-1-i] = faces[5][CUBE_SIZE-1-i][CUBE_SIZE-1-layer];
				faces[5][CUBE_SIZE-1-i][CUBE_SIZE-1-layer] = faces[5][CUBE_SIZE-1-layer][i];
				faces[5][CUBE_SIZE-1-layer][i] = faces[5][i][layer];
				faces[5][i][layer] = t[i];
			}
		}

	}

	void down_clock() {

		int t[CUBE_SIZE];

		REP(i, CUBE_SIZE) {
			t[i] = faces[0][CUBE_SIZE-1-layer][i];
			faces[0][CUBE_SIZE-1-layer][i] = faces[2][CUBE_SIZE-1-layer][i];
			faces[2][CUBE_SIZE-1-layer][i] = faces[1][CUBE_SIZE-1-layer][i];
			faces[1][CUBE_SIZE-1-layer][i] = faces[3][CUBE_SIZE-1-layer][i];
			faces[3][CUBE_SIZE-1-layer][i] = t[i];
		}

		if (layer==0) {
			REP(i, CUBE_SIZE-1) {
				t[i] = faces[5][layer][i];
				faces[5][layer][i] = faces[5][CUBE_SIZE-1-i][layer];
				faces[5][CUBE_SIZE-1-i][layer] = faces[5][CUBE_SIZE-1-layer][CUBE_SIZE-1-i];
				faces[5][CUBE_SIZE-1-layer][CUBE_SIZE-1-i] = faces[5][i][CUBE_SIZE-1-layer];
				faces[5][i][CUBE_SIZE-1-layer] = t[i];
			}
		}

	}


	/*
	0 - Front
	1 - Back
	2 - Left
	3 - Right
	4 - Up
	5 - Down
	*/

};

bool hollow = false;
bool change = false;
int width = 600, height = 600;
int px = -1, py = -1;

int rotationType = 0;
const double PI = 3.1415926535;
double rorationSpeed = 90;
double totalRotation = 0;
Vector3d rotationAxis;
State cube;
Quaterniond camera = Quaterniond{ AngleAxisd{1, Vector3d{0,0,0}} };

double *matrix = new double[16];
vector<point> rotationQueue;
color colorList[7] = { color(0.3,0.8,0), color(0,0.5,1), color(1,0.8,0), color(0.9,0.9,0.9),  color(1,0.4,0), color(0.9,0,0), color(0.2,0.2,0.2) };

Quaterniond cubesRotation[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

void changeState() {

	REP(a, rotationQueue.size()) {
		point mci = rotationQueue[a];
		int i = mci.z, j = mci.y, k = mci.x;
		cubesRotation[i][j][k] = Quaterniond{ AngleAxisd{ 1, Vector3d{ 0,0,0 } } };
	}

	rotationQueue.clear();
	totalRotation = 0;

	if (rotationType==1) 
		cube.front_anticlock();
	else if (rotationType==2) 
		cube.back_anticlock();
	else if (rotationType==3) 
		cube.left_anticlock();
	else if (rotationType==4) 
		cube.right_anticlock();
	else if (rotationType==5) 
		cube.up_anticlock();
	else if (rotationType==6) 
		cube.down_anticlock();

	else if (rotationType==7) 
		cube.front_clock();
	else if (rotationType==8)
		cube.back_clock();
	else if (rotationType==9)
		cube.left_clock();
	else if (rotationType==10)
		cube.right_clock();
	else if (rotationType==11)
		cube.up_clock();
	else if (rotationType==12)
		cube.down_clock();

	//cube.printCube();
	rotationType = 0;
	
}

inline double degtorad(double deg) {
	return PI*deg/180;
}

void printMatrix(double m[]) {

	REP(i, 4) {
		REP(j, 4)
			printf("% .6lf ", m[i*4 +j]);
		printf("\n");
	}
	printf("\n");

}

double* getRotationMatrix(Quaterniond &q) {

	Matrix3d rotMat = q.normalized().toRotationMatrix();
	
	matrix[0] = rotMat(0, 0);	matrix[4] = rotMat(0, 1);	matrix[8] = rotMat(0, 2);	matrix[12] = 0;
	matrix[1] = rotMat(1, 0);	matrix[5] = rotMat(1, 1);	matrix[9] = rotMat(1, 2);	matrix[13] = 0;
	matrix[2] = rotMat(2, 0);	matrix[6] = rotMat(2, 1);	matrix[10] = rotMat(2, 2);	matrix[14] = 0;
	matrix[3] = 0;				matrix[7] = 0;				matrix[11] = 0;				matrix[15] = 1;

	return matrix;

}

void keyboard(unsigned char key, int x, int y) {

	

	if (rotationType==0) {
		if (key>='1' && key<='9') {
			layer = min(CUBE_SIZE/2, key-'1');
		}
		else if (key=='+') {
			layer = min(CUBE_SIZE/2, layer+1);
		}
		else if (key=='-') {
			layer = max(0, layer-1);
		}
		if (key=='j' || key=='J') {
			int cacheLayer = layer;
			FOR(i, 1, 5) {
				layer = rand()%(CUBE_SIZE/2);
				rotationType = 1 + rand()%12;
				changeState();
			}
			layer = cacheLayer;
		}

		if (key=='Q') {
			rotationAxis = { 0, 0, 1 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( j, i, layer));
			}
			if (rorationSpeed<0)
				rorationSpeed = -rorationSpeed;
			rotationType = 1;
		}
		else if (key=='q') {
			rotationAxis = { 0, 0, 1 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( j, i, layer));
			}
			if (rorationSpeed>0)
				rorationSpeed = -rorationSpeed;
			rotationType = 7;
		}
		else if (key=='W') {
			rotationAxis = { 0, 0, 1 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( j, i, CUBE_SIZE-1-layer));
			}
			if (rorationSpeed>0)
				rorationSpeed = -rorationSpeed;
			rotationType = 2;
		}
		else if (key=='w') {
			rotationAxis = { 0, 0, 1 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( j, i, CUBE_SIZE-1-layer));
			}
			if (rorationSpeed<0)
				rorationSpeed = -rorationSpeed;
			rotationType = 8;
		}
		else if (key=='A') {
			rotationAxis = { 1, 0, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( layer, i, j ));
			}
			if (rorationSpeed>0)
				rorationSpeed = -rorationSpeed;
			rotationType = 3;
		}
		else if (key=='a') {
			rotationAxis = { 1, 0, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( layer, i, j ));
			}
			if (rorationSpeed<0)
				rorationSpeed = -rorationSpeed;
			rotationType = 9;
		}
		else if (key=='S') {
			rotationAxis = { 1, 0, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( CUBE_SIZE-1-layer, i, j ));
			}
			if (rorationSpeed<0)
				rorationSpeed = -rorationSpeed;
			rotationType = 4;
		}
		else if (key=='s') {
			rotationAxis = { 1, 0, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( CUBE_SIZE-1-layer, i, j ));
			}
			if (rorationSpeed>0)
				rorationSpeed = -rorationSpeed;
			rotationType = 10;
		}
		else if (key=='Z') {
			rotationAxis = { 0, 1, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( i, layer, j ));
			}
			if (rorationSpeed<0)
				rorationSpeed = -rorationSpeed;
			rotationType = 5;
		}
		else if (key=='z') {
			rotationAxis = { 0, 1, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( i, layer, j ));
			}
			if (rorationSpeed>0)
				rorationSpeed = -rorationSpeed;
			rotationType = 11;
		}
		else if (key=='X') {
			rotationAxis = { 0, 1, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( i, CUBE_SIZE-1-layer, j ));
			}
			if (rorationSpeed>0)
				rorationSpeed = -rorationSpeed;
			rotationType = 6;
		}
		else if (key=='x') {
			rotationAxis = { 0, 1, 0 };
			REP(i, CUBE_SIZE) {
				REP(j, CUBE_SIZE)
					rotationQueue.push_back(point( i, CUBE_SIZE-1-layer, j ));
			}
			if (rorationSpeed<0)
				rorationSpeed = -rorationSpeed;
			rotationType = 12;
		}
	}

}

void mouse(int button, int state, int x, int y) {

	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		px = x;
		py = y;
	}

	if (button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
		py = px = -1;
	}

}

void mouseWheel(int button, int dir, int x, int y){

	double factor = 0.05;
	Quaterniond qz = Quaterniond{ AngleAxisd{ dir*factor, Vector3d{ 0, 0, 1 } } };
	camera = qz*camera;

}

void motion(int x, int y) {

	if (px!=-1 && py!=-1) {
		double factor = 0.005;
		Quaterniond qx = Quaterniond{ AngleAxisd{ (y-py)*factor, Vector3d{ 1, 0, 0 } } };
		Quaterniond qy = Quaterniond{ AngleAxisd{ (x-px)*factor, Vector3d{ 0, 1, 0 } } };
		camera = qx*qy*camera;
	}
	px = x;
	py = y;

}

void reshape(int w, int h) {

	double widthScale = (double)w/width, heightScale = (double)h/height;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2*widthScale, 2*widthScale, -2*heightScale, 2*heightScale, -5, 5);
	glMatrixMode(GL_MODELVIEW);
}

void drawFace(float *a, float *b, float *c, float *d, int face) {

	glColor3fv(colorList[face].getArray());
	glBegin(GL_QUADS);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();

}

void drawCube(float *a, float *b, float *c, float *d, 
			  float *e, float *f, float *g, float *h,
			  int x, int y, int z) {

	int front=6, back=6, left=6, right=6, up=6, down=6;

	/*
	0 - Front
	1 - Back
	2 - Left
	3 - Right
	4 - Up
	5 - Down
	*/

	if (z==0)
		front = cube.faces[0][y][x];
	if (z==CUBE_SIZE-1)
		back = cube.faces[1][y][CUBE_SIZE-1-x];

	if (y==0)
		up = cube.faces[4][CUBE_SIZE-1-z][x];
	if (y==CUBE_SIZE-1)
		down = cube.faces[5][z][x];

	if (x==0)
		left = cube.faces[2][y][CUBE_SIZE-1-z];
	if (x==CUBE_SIZE-1)
		right = cube.faces[3][y][z];

	if (!hollow || front!=6)
		drawFace(a, b, c, d, front);	// Front
	if (!hollow || back!=6)
		drawFace(f, e, h, g, back);		// Back
	if (!hollow || left!=6)
		drawFace(e, a, d, h, left);		// Left
	if (!hollow || right!=6)
		drawFace(b, f, g, c, right);	// Right
	if (!hollow || up!=6)
		drawFace(e, f, b, a, up);		// Up
	if (!hollow || down!=6)
		drawFace(d, c, g, h, down);		// Down

}

void buildRubiksCube() {

	double big_szie = 2.4;
	double small_size = big_szie/CUBE_SIZE;
	double intercube_spacing = small_size*0.05;

	double start = big_szie/2 + intercube_spacing*(CUBE_SIZE-1)/2;

	for (double z = start; z>-start; z-= small_size+intercube_spacing) {
		for (double y = start; y>-start; y-= small_size+intercube_spacing) {
			for (double x = -start; x<start; x += small_size+intercube_spacing) {

				int cx = (int)round((x+big_szie/2)/(small_size+intercube_spacing));
				int cy = (int)round((-y+big_szie/2)/(small_size+intercube_spacing));
				int cz = (int)round((-z+big_szie/2)/(small_size+intercube_spacing));

				glPushMatrix();
				glMultMatrixd(getRotationMatrix(cubesRotation[cz][cy][cx]));

				float v[8][3] = { 
					{ x, y, z },
					{ x+small_size, y, z },
					{ x+small_size, y-small_size, z },
					{ x, y-small_size, z },
					{ x, y, z-small_size },
					{ x+small_size, y, z-small_size },
					{ x+small_size, y-small_size, z-small_size },
					{ x, y-small_size, z-small_size } 
				};

				drawCube(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], cx, cy, cz);
				glPopMatrix();
			}
		}
	}


}

void updateRotation() {

	
	REP(a, rotationQueue.size()) {
		point mci = rotationQueue[a];
		int i = mci.z, j = mci.y, k = mci.x;
		Quaterniond qr = Quaterniond{ AngleAxisd{ degtorad(rorationSpeed), rotationAxis} };
		cubesRotation[i][j][k] = qr*cubesRotation[i][j][k];
	}

	totalRotation += rorationSpeed;

	if (totalRotation>=90 || totalRotation<=-90) {
		changeState();
	}

}

void display() {

	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();
	glMultMatrixd(getRotationMatrix(camera));
	
	buildRubiksCube();

	if (rotationType) {
		updateRotation();
	}

	glutSwapBuffers();
	glutPostRedisplay();

}

void init() {

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutMouseWheelFunc(mouseWheel);
	REP(i, CUBE_SIZE) {
		REP(j, CUBE_SIZE) {
			REP(k, CUBE_SIZE) {
				cubesRotation[i][j][k] = Quaterniond{ AngleAxisd{1,Vector3d{0,0,0}} };
			}
		}
	}

}

int main(int argc, char *argv[]) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rubics Cube");

	init();

	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glutMainLoop();
	return 0;

}

// :)