#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <vector>
using namespace std;

int windowid;

//GLfloat lx = 0.0f, lz = -1.0f; // actual vector representing the camera's direction
//GLfloat x = 0.0f, z = 5.0f;// XZ position of the camera

std::vector<std::vector<int>> map;

// Camera motion
GLfloat angle = 0.0; // angle of rotation for the camera direction
GLfloat lx = 0.0f, lz = -1.0f; // actual vector representing the camera's direction
GLfloat x = 0.0f, z = 5.0f;// XZ position of the camera

GLfloat navX = 0.0f;
GLfloat navZ = 300.0f;

GLfloat navY = 0.0;

bool can_move(int x_, int z_) {
	std::cout << " [x] = " << x_ << "[z] = " << z_ << std::endl;
	x_ /= 10;
	z_ /= 10;
	std::cout << "[x] = " << x_ << "[z] = " << z_ << std::endl;
	if (x_ > 20 || z_ > 20 || x_ <= 0 || z_ <= 0) return true;
	else {
		if (map[z_-1][x_-1] == 0) {
			return true;
		}
		else {
			std::cout << "wall" << std::endl;
			return false;
		}
		
	}
}


void drawObject_1(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(10);
	glTranslatef(0, 4, 0); 
	glutSolidSphere(5.0f, 20, 20);
	glPopMatrix();
}

void drawObject_2(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(10, 0, 0);
	glutSolidCube(10);
	glPopMatrix();
}


/*-[Keyboard Callback]-------------------------------------------------------*/
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a': // lowercase character 'a'
		cout << "You just pressed 'a'" << endl;
		if(can_move(navX-1,navZ)) navX -= 1;
		break;
	case 'd': // lowercase character 'd'
		cout << "You just pressed 'd'" << endl;
		if (can_move(navX+1, navZ)) navX += 1;
		break;
	case 'w': // lowercase character 'w'
		cout << "You just pressed 'w'" << endl;
		if (can_move(navX, navZ-1)) navZ -= 1;
		break;
	case 's': // lowercase character 's'
		cout << "You just pressed 's'" << endl;
		if (can_move(navX+1, navZ)) navZ += 1;
		break;

	case 32 :
		cout << "space";
		if (navY == 0) navY = 30; else navY = 0;
		break;
	case 27: // Escape key
		glutDestroyWindow(windowid);
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		cout << "You just pressed 'left'" << endl;
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		cout << "You just pressed 'right'" << endl;
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		cout << "You just pressed 'up'" << endl;
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		cout << "You just pressed 'down'" << endl;
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

/*-[MouseClick Callback]-----------------------------------------------------*/
void onMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		cout << "Middle button clicked at position "
			<< "x: " << x << " y: " << y << endl;
	}
}

/* ========================================================== */

/*-[Reshape Callback]--------------------------------------------------------*/
void reshapeFunc(int x, int y) {
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return

	glMatrixMode(GL_PROJECTION); //Set a new projection matrix
	glLoadIdentity();
	//Angle of view: 40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0

	//glOrtho(-1.0*(GLdouble)x/(GLdouble)y,(GLdouble)x/(GLdouble)y,0.0,0.0,5,20.0);
	gluPerspective(40, (GLdouble)x / (GLdouble)y, 0.1, 300);
	glViewport(0, 0, x, y);  //Use the whole window for rendering

	// TASK 2:
	//glViewport(0, 0, x/2, y/2);  //Use the whole window for rendering
}

/* ========================================================== */

void renderLabyrinth(void/*const std::vector<std::vector<int>>& map*/) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
		
	for (size_t i = 0; i < 20; i++) {
		glLoadIdentity();
		gluLookAt(navX, navY, navZ, navX, 0.0, 0, 0.0f, 1.0f, 0.0f);
		glTranslatef(5.0f, 0.0f,5.0+10*i);
		for (size_t j = 0; j < 20; j++) {
			if (map[i][j] == 1) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glPushMatrix();
				glTranslatef(10.0f, 0.0f, 0.0f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glutSolidCube(10);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glPushMatrix();
				glColor3f(0.0f, 0.0f, 1.0f);
				glutSolidCube(10);
			}
			else {
				if (i == 10 && j == 9) drawObject_1();
				if (i == 10 && j == 10) drawObject_2();
				glPushMatrix();
				glTranslatef(10.0f, 0.0f, 0.0f); //0.5
			}
		}
	}
	glutSwapBuffers();
}

void print_map(void) {
	for (size_t i = 0; i < 20; i++) {
		for (size_t j = 0; j < 20; j++) {
			std::cout << (map[i][j] == 1 ? "\033[32m":"\033[0m")<< map[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void idleFunc(void) {
	glutPostRedisplay();
}

void init_labyrinth(void) {
	map.push_back({ 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 });
	map.push_back({ 1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1 });
	map.push_back({ 1,0,1,0,0,1,0,1,0,1,1,1,1,0,1,1,0,1,0,0 });
	map.push_back({ 1,0,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1,0,1 });
	map.push_back({ 1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,0,1 });
	map.push_back({ 1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1 });
	map.push_back({ 1,1,0,1,1,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1 });
	map.push_back({ 1,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,0,1,0,1 });
	map.push_back({ 1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1 });
	map.push_back({ 1,1,1,1,0,1,0,1,0,0,0,0,1,1,1,1,1,1,0,1 });
	map.push_back({ 1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 });
	map.push_back({ 1,1,0,1,0,1,1,1,0,0,0,0,1,0,1,1,1,0,1,1 });
	map.push_back({ 0,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,1,0,1,1 });
	map.push_back({ 1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,1 });
	map.push_back({ 1,1,0,0,0,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1 });
	map.push_back({ 1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1 });
	map.push_back({ 1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,0,0,0,1 });
	map.push_back({ 1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1 });
	map.push_back({ 1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0 });
	map.push_back({ 1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1 });
}

int main(int argc, char** argv) {

	/*=== INIT WINDOW ===*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(500, 500); //determines the initial position of the window
	glutInitWindowSize(800, 600); //determines the size of the window
	windowid = glutCreateWindow("01 Uebung"); // create and name window
	
	init_labyrinth();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(onMouseClick);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*=== REGISTER CALLBACKS ===*/
	
	//glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshapeFunc);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderLabyrinth);
	
	glutIdleFunc(idleFunc);

	glutSpecialFunc(processSpecialKeys);

	/*=== start main loop ===*/
	glutMainLoop();
}