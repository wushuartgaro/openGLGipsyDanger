#include <Windows.h>
#include <Windowsx.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

void leftKeyAction();
void rightKeyAction();
void upKeyAction();
void downKeyAction();
void wKeyAction();
void aKeyAction();
void sKeyAction();
void dKeyAction();
void qKeyAction();
void eKeyAction();

GLfloat ctrlpoints[3][3] = {
	{ 6, 4, 0 },{ 4, -2, 0 },{ 0, 1.5, 0 }
};

float xRotated = 1.0f, yRotated = 1.0f, zRotated = -30.0f;


float x = 0.0f, y = 0.0f, z = 1.0f;

float radius = 1.0f;
float baseRadius = 0.1f;
int slices = 20, stacks = 20;

float fingersAngle = 180.0f;
float leftLegAngle1 = 180.0f, leftLegAngle2 = 180.0f, leftLegAngle3 = 180.0f;
float rightLegAngle1 = 180.0f, rightLegAngle2 = 180.0f, rightLegAngle3 = 180.0f;
float leftArmAngle1 = 180.0f, leftArmAngle2 = 180.0f, leftArmAngle3 = 180.0f;
float rightArmAngle1 = 180.0f, rightArmAngle2 = 180.0f, rightArmAngle3 = 180.0f;

float bodyJointAngle = 0.0f, upperBodyJointAngle = 0.0f;

float leftLegAxis[3][3] = { {1.0f,0.0f,0.0f},{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };
float rightLegAxis[3][3] = { { 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };

bool leftFrontMax = false, rightFrontMax = false, leftBackMax = false, rightBackMax = false;
bool firstWalk = true, leftFrontWalked = false, rightFrontWalked = true, leftBackWalked = false, rightBackWalked = true;

float reactorRotateAngle = 0.0f;

float xPosition = 0.0f, yPosition = 0.0f, zPosition = 0.0f;

float zoomLevel = -7.0f;
float seaWaveMovement = 1.0f;


float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
float mat_ambient_color[] = { 0.0f, 0.0f, 1.0f, 1.0f };
float mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

bool lightOn = 1;

bool ambientOn = 0;
bool diffuseOn = 0;
bool specularOn = 0;

bool weather = 0;


float boneLength = 2.0f;

GLuint texture;

BITMAP BMP;
HBITMAP hBMP = NULL;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_MOUSEMOVE:
		switch (wParam) {
		case MK_LBUTTON:
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			zRotated = xPos;
			xRotated = yPos;
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		zoomLevel += GET_WHEEL_DELTA_WPARAM(wParam)/120.0f;
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			leftKeyAction();
			break;
		case VK_RIGHT:
			rightKeyAction();
			break;
		case VK_UP:
			upKeyAction();
			break;
		case VK_DOWN:
			downKeyAction();
			break;
		case VK_PRIOR:
			if(fingersAngle > 45.0f)
				fingersAngle -= 1.0f;
			break;
		case VK_NEXT:
			if (fingersAngle <= 180.0f)
				fingersAngle += 1.0f;
			break;
		case 'I':
			zoomLevel += 1.0f;
			break;
		case 'O':
			zoomLevel -= 1.0f;
			break;
		case 'C':
			weather = !weather;
			break;
		case 'W':
			wKeyAction();
			break;
		case 'A':
			aKeyAction();
			break;
		case 'S':
			sKeyAction();
			break;
		case 'D':
			dKeyAction();
			break;
		case 'E':
			eKeyAction();
			break;
		case 'Q':
			qKeyAction();
			break;
		case 0x31:
			ambientOn = !ambientOn;
			break;
		case 0x32:
			diffuseOn = !diffuseOn;
			break;
		case 0x33:
			specularOn = !specularOn;
			break;
		case VK_SPACE:
			xRotated = 1.0f;
			yRotated = 1.0f;
			zRotated = -30.0f;
			zoomLevel = -7.0f;
			x = 0.0f;
			y = 0.0f;
			z = 1.0f;
		case 0x34:
			if (lightOn)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);

			lightOn = !lightOn;
			break;
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}

GLuint LoadBMP(char* fileName) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return texture;
}


void drawLinePyramid() {
	glBegin(GL_LINE_LOOP);
	{
		// Bottom Face 
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		// Front Face 
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		// Left Face
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		// Right and Back Face
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	}
	glEnd();
}

void drawLineCubic() {
	glBegin(GL_LINE_STRIP);
	// Top face (y = 1.0f)
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.0f, 1.0f, -1.0f);
	glVertex3f(-2.0f, 1.0f, -1.0f);
	glVertex3f(-2.0f, 1.0f, 1.0f);
	glVertex3f(2.0f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	// Bottom face (y = -1.0f)
	glVertex3f(2.0f, -1.0f, 1.0f);
	glVertex3f(-2.0f, -1.0f, 1.0f);
	glVertex3f(-2.0f, -1.0f, -1.0f);
	glVertex3f(2.0f, -1.0f, -1.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	// Front face  (z = 1.0f)
	glVertex3f(2.0f, 1.0f, 1.0f);
	glVertex3f(-2.0f, 1.0f, 1.0f);
	glVertex3f(-2.0f, -1.0f, 1.0f);
	glVertex3f(2.0f, -1.0f, 1.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	// Back face (z = -1.0f)
	glVertex3f(2.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, 1.0f, -1.0f);
	glVertex3f(2.0f, 1.0f, -1.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	// Left face (x = -1.0f)
	glVertex3f(-2.0f, 1.0f, 1.0f);
	glVertex3f(-2.0f, 1.0f, -1.0f);
	glVertex3f(-2.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, -1.0f, 1.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Right face (x = 1.0f)
	glVertex3f(2.0f, 1.0f, -1.0f);
	glVertex3f(2.0f, 1.0f, 1.0f);
	glVertex3f(2.0f, -1.0f, 1.0f);
	glVertex3f(2.0f, -1.0f, -1.0f);
	glEnd();
}

void drawFilledCube() {
	glBegin(GL_QUADS);
	{
		// Top Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, 1.0f, 1.0f);

		// Left Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 0); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, -1.0f, -1.0f);

		// Back Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, 1.0f, -1.0f);

		// Right Face 
		glTexCoord2f(0, 0); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3f(1.0f, -1.0f, 1.0f);

		// Bottom Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, -1.0f, -1.0f);

		// Front Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, -1.0f, 1.0f);
	}
	glEnd();
}

void drawRobotArm() {
	glPushMatrix();
	{
		drawFilledCube();

		glPushMatrix();
		{
			glTranslatef(2.0f, -1.0f, 0.0f); //Switch origin to prefered rotate point.
			glRotatef(fingersAngle, 0.0f, 0.0f, 1.0f); //Rotating joint.

			glPushMatrix();
			{
				glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				drawFilledCube();
				glPushMatrix();
				{
					glTranslatef(2.0f, -1.0f, 0.0f); //Switch origin to prefered rotate point.
					glRotatef(fingersAngle, 0.0f, 0.0f, 1.0f); //Rotating joint.

					glPushMatrix();
					{
						glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
						glTranslatef(4.0f, 0.0f, 0.0f);
						drawFilledCube();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawSphere() {
	glBegin(GL_POLYGON); {
		float radius = 0.2f;
		for (float angle = 0; angle < 2.0 * 3.1415926f; angle += 0.01) {
			glVertex3f((radius*cos(angle)), (radius*sin(angle)), 0);
		}
	}
	glEnd();
}


void drawBone(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		gluCylinder(var, radius/25, radius/25, boneLength, 6, stacks);
	}
	glPopMatrix();
	
}

void drawBallJoint(GLUquadricObj *var) {
	glPushMatrix();
	{
		gluSphere(var, radius / 22.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawHingeJoint(GLUquadricObj *var) {
	glPushMatrix();
	{
		gluSphere(var, radius / 22.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawCover() {
	glPushMatrix();
	{	
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();
	
}

void drawFloatHingeJointArmor(GLUquadricObj *var) {

	glPushMatrix(); {
		glTranslatef(-0.17f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.35f);
			gluCylinder(var, radius / 7.0f, radius / 7.0f, 0.025f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.025f);
				gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, -0.025f);
					gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawHingeJointArmor(GLUquadricObj *var) {
	//draw Hinge Joint Screw
	glPushMatrix();
	{
		glTranslatef(-0.17f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		gluCylinder(var, radius / 7.0f, radius / 7.0f, 0.30f, 8, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.30f);
			gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.30f);
				gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void drawChestArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(-0.55f, -0.15f, 1.5f);
		//glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-35.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix(); {
			glScalef(0.42f, 0.05f, 0.20f);
			drawCover();
		}
		glPopMatrix();
		//drawFrontArmor
		glPushMatrix();
		{
			glTranslatef(-0.05f, -0.1f, 0.25f);
			glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix(); {
				glScalef(0.20f, 0.05f, 0.05f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.18f, 0.15f, 0.25f);
			glRotatef(-67.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix(); {
				glScalef(0.35f, 0.05f, 0.20f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	//draw shoulder stripe
	glPushMatrix();
	{
		glTranslatef(-0.4f, 0.0f, 1.9f);
		//glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
		glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
		glPushMatrix(); {
			glScalef(0.18f, 0.05f, 0.30f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.26f, 0.0f, 2.0f);
		glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
		glPushMatrix(); {
			glScalef(0.07f, 0.02f, 0.20f);
			//glColor3f(1.0f, 0.0f, 0.0f);
			//drawFilledCube();
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.16f, -0.18f, 1.8f);
		glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix(); {
			glScalef(0.07f, 0.02f, 0.15f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.0f, 0.0f, 2.02f);
		glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f,1.5f,1.0f);
		gluCylinder(var,radius/4.0f,radius/4.5f,0.08f,slices,stacks);
	}
	glPopMatrix();
	
}

void drawShoulderCover() {
	glPushMatrix(); {
		glTranslatef(-0.80f, 0.10f, 2.3f);
		glRotatef(87.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.30f, 0.025f, 0.30f);
		drawCover();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.40f, 0.45f, 2.0f);
		glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.13f, 0.025f, 0.38f);
		drawCover();
	}
	glPopMatrix();
}

void drawBackBooster(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(-0.55f, 0.5f, 1.3f);
		glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		gluCylinder(var, radius / 8.0f, radius / 6.0f, 0.5f, 7, stacks * 2);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			gluDisk(var, 0.0f, radius / 8.0f, 7, 20);
		}
		glPopMatrix();
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			gluCylinder(var, radius / 6.5f, radius / 5.8f, 0.45f, 7, stacks * 2);
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(-0.1f, 0.15f, 0.50f);
			glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.1f, 0.01f, 0.15f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0f, 0.15f, 0.60f);
			glRotatef(80.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.05f, 0.01f, 0.15f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawBackConnector(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(-0.3f, 0.7f, 1.3f);
		glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(80.0f,1.0f,0.0f,0.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glScalef(0.5f,1.5f,1.0f);
		gluCylinder(var, radius / 6.0f, radius / 4.5f, 0.3f, 10, stacks*5);
		glPushMatrix();
		{
			glColor3f(119 / 255.0f, 99 / 255.0f, 94 / 255.0f);
			glTranslatef(0.0f, 0.0f, 0.05f);
			gluDisk(var, 0.0f, radius / 6.0f, 10, 20);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void drawBackVertebraeBone() {
	glPushMatrix(); {
		glScalef(0.08f, 0.01f, 0.1f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.08f, -0.05f, -0.03f);
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.08f, 0.01f, 0.1f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix(); {
		glScalef(-1.0f, 1.0f, 1.0f);
		glTranslatef(0.08f, -0.05f, -0.03f);
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.08f, 0.01f, 0.1f);
		drawFilledCube();
	}
	glPopMatrix();
}

void drawBackVertebrae() {
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.7f, 1.7f);
		for (int i = 0; i < 11; i++) {
			glTranslatef(0.0f, 0.0f, -0.15f);
			if (i > 4) {
				glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
			}
			else {
				glRotatef(-5.0f, 1.0f, 0.0f, 0.0f);
			}
			glScalef(1.0f-(i/90.0f), 1.0f,1.0f);
			drawBackVertebraeBone();
		}
	}
	glPopMatrix();
}

void drawBackArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		//draw head cover
		glPushMatrix();
		{
			glPushMatrix(); {
				glTranslatef(-0.08f, 0.35f, 2.4f); 
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.20f, 0.025f, 0.30f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix(); {
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-0.08f, 0.35f, 2.4f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.20f, 0.025f, 0.30f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.55f, 2.0f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.15f, 0.025f, 0.30f);
				drawCover();
				glPushMatrix();
				{
					glTranslatef(-1.0f, 0.0f, 0.0f);				
					glScalef(0.50f, 1.0f, 0.60f);
					drawCover();
					
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(-1.0f, 1.0f, 1.0f);
					glTranslatef(-1.0f, 0.0f, 0.0f);
					glScalef(0.50f, 1.0f, 0.60f);
					drawCover();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//draw shoulder cover
		glPushMatrix();
		{
			drawShoulderCover();
			glPushMatrix(); {
				glScalef(-1.0f, 1.0f, 1.0f);
				drawShoulderCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//draw back booster
		glPushMatrix();
		{
			drawBackBooster(var);
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				drawBackBooster(var);
			}
			glPopMatrix();
			
		}
		glPopMatrix();
		//draw back connector
		glPushMatrix();
		{
			drawBackConnector(var);
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				drawBackConnector(var);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void drawReactor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.45f, 1.2f);
		glRotatef(-67.0f,1.0f,0.0f,0.0f);
		glPushMatrix(); {
			glColor3f(120 / 255.0f, 99 / 255.0f, 95 / 255.0f);
			gluCylinder(var, radius / 4, radius / 3, 0.1f, slices, stacks);
		}
		glPopMatrix();
		glPushMatrix(); {
			glColor3f(1.0f, 1.0f, 1.0f);
			texture = LoadBMP("reactor_outring_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluCylinder(var, radius / 5, radius / 4, 0.02f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix(); {
			glRotatef(reactorRotateAngle,0.0f,0.0f,1.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			texture = LoadBMP("reactor_turn1_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluCylinder(var, radius / 5, radius / 12, 0.1f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			texture = LoadBMP("reactor_outring_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluSphere(var, radius / 12, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix(); {
			glTranslatef(0.0f, 0.0f, 0.025f);
			glRotatef(-reactorRotateAngle, 0.0f, 0.0f, 1.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			texture = LoadBMP("reactor_turn1_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluCylinder(var, radius / 25.0f, radius / 16.0f, 0.01f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.39f, 0.25f);
			glRotatef(33.0f, 1.0f, 0.0f, 0.0f);
			glColor3f(120 / 255.0f, 99 / 255.0f, 95 / 255.0f);
			glPushMatrix();
			{
				glScalef(0.08f, 0.05f, 0.18f);
				drawFilledCube();
			}
			glPopMatrix();

		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.45f, 0.20f, 0.2f);
			glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(67.0f, 1.0f, 0.0f, 0.0f);
			glColor3f(120 / 255.0f, 99 / 255.0f, 95 / 255.0f);
			glPushMatrix();
			{
				glScalef(0.05f, 0.05f, 0.20f);
				drawFilledCube();
			}
			glPopMatrix();

		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.45f, 0.20f, 0.2f);
			glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(67.0f, 1.0f, 0.0f, 0.0f);
			glColor3f(120 / 255.0f, 99 / 255.0f, 95 / 255.0f);
			glPushMatrix();
			{
				glScalef(0.05f, 0.05f, 0.20f);
				drawFilledCube();
			}
			glPopMatrix();

		}
		glPopMatrix();
		
	}
	glPopMatrix();
}


void drawChest(GLUquadricObj *var) {
	//texture = LoadBMP("armor_texture.bmp");
	//glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix(); {
		glTranslatef(0.0f,-0.2f,0.0f);
		drawChestArmor(var);
		glPushMatrix();
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			drawChestArmor(var);
		}
		glPopMatrix();
		glPushMatrix(); {
			drawReactor(var);
			drawBackArmor(var);
		}
		glPopMatrix();
	}
	glPopMatrix();
	//glDeleteTextures(1, &texture);
}

void drawWaistCover() {
	glPushMatrix(); {
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		//draw waist stripe
		glPushMatrix();
		{
			glTranslatef(-0.5f, 0.3f, 0.5f);
			glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix(); {
				glScalef(0.10f, 0.05f, 0.15f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.45f, 0.5f, 0.38f);
			glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
			//glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix(); {
				glScalef(0.05f, 0.05f, 0.2f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFrontVertebraeBone() {
	glPushMatrix(); {
		glTranslatef(0.0f, 0.05f, -0.1f);
		glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.08f, 0.1f, 0.2f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.30f, 0.05f, 0.1f);
		glPushMatrix();
		{
			//glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(-0.15f, 0.05f, 0.0f);
			glScalef(0.06f, 0.1f, 0.1f);
			drawFilledCube();
		}
		glPopMatrix();
		glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.18f, 0.01f, 0.1f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix(); {
		glScalef(-1.0f, 1.0f, 1.0f);
		glTranslatef(0.30f, 0.05f, 0.1f);
		glPushMatrix();
		{
			//glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(-0.15f, 0.05f, 0.0f);
			glScalef(0.06f, 0.1f, 0.1f);
			drawFilledCube();
		}
		glPopMatrix();
		glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.18f, 0.01f, 0.1f);
		drawFilledCube();
	}
	glPopMatrix();
}

void drawFrontArmor() {
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.3f, 1.0f);
		for (int i = 0; i < 5; i++) {
			glTranslatef(0.0f, 0.0f, -0.15f);
			glScalef(1.0f - (i / 90.0f), 1.0f, 1.0f);
			drawFrontVertebraeBone();
		}
		for (int i = 0; i < 3; i++) {
			drawWaistCover();
			glPushMatrix();
			{
				glScalef(-1.0f,1.0f,1.0f);
				drawWaistCover();
			}
			glPopMatrix();
			
			glTranslatef(0.0f,0.0f,-0.2f);
		}
		
	}
	glPopMatrix();
}


void drawHips(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.3f, 0.05f);
		//drawFront
		glPushMatrix();
		{
			//glColor3f(120 / 255.0f, 99 / 255.0f, 95 / 255.0f);
			glPushMatrix();
			{
				glScalef(0.15f, 0.10f, 0.10f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.15f, -0.25f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.08f, 0.30f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.35f, -0.50f);
				glRotatef(110.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.05f, 0.20f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//drawSide
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(0.25f, 0.1f, 0.20f);
				glRotatef(35.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.05f, 0.20f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.25f, 0.1f, 0.20f);
				glRotatef(35.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.05f, 0.20f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.50f, 0.3f, 0.40f);
				glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.025f, 0.20f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.50f, 0.3f, 0.40f);
				glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.025f, 0.20f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.40f, 0.53f, 0.40f);
				glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.10f, 0.08f, 0.30f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.40f, 0.53f, 0.40f);
				glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.10f, 0.08f, 0.30f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//drawBack
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.55f, -0.2f);
				glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.40f, 0.25f, 0.25f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.40f, 0.55f, 0.1f);
				glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.15f, 0.05f, 0.20f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-0.40f, 0.55f, 0.1f);
				glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.15f, 0.05f, 0.20f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.40f, 0.25f, 0.2f);
				glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.05f, 0.10f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-0.40f, 0.25f, 0.2f);
				glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.05f, 0.10f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawSpine(GLUquadricObj *var) {
	glPushMatrix();
	{
		glScalef(0.9f, 0.9f, 0.9f);
		glPushMatrix(); {
			glRotatef(bodyJointAngle, 1.0f, 0.0f, 0.0f);
			drawBallJoint(var);
			drawHingeJointArmor(var);
			glPushMatrix(); {
				glTranslatef(0.0f, 0.0f, 1.0f);
				glRotatef(upperBodyJointAngle, 1.0f, 0.0f, 0.0f);
				drawBallJoint(var);
				drawHingeJointArmor(var);
				glTranslatef(0.0f, 0.0f, -1.0f);
				//draw upper backbone
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 1.0f);
					boneLength = 0.9f;
					drawBone(var);
				}
				glPopMatrix();
				drawChest(var);
				//draw rib cage
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 1.0f);
					//glRotatef(90.0f,1.0f,0.0f,0.0f);
					glScalef(1.2f, 0.5f, 1.0f);
					glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
					gluCylinder(var, radius / 2.0f, radius / 1.4f, 0.8f, slices, stacks);
					glPushMatrix(); {
						glTranslatef(0.0f, -0.2f, 0.0f);
						glScalef(1.0f, 1.1f, 1.0f);
						gluCylinder(var, radius / 2.0f, radius / 1.5f, 0.5f, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(-1.0f, 0.0f, 1.8f);
					glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
					glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
					gluCylinder(var, radius / 5.5f, radius / 5.5f, 2.0f, slices, stacks);
					gluDisk(var, 0.0f, radius / 5.5f, slices, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 2.0f);
						gluDisk(var, 0.0f, radius / 5.5f, slices, stacks);
					}
					glPopMatrix();

				}
				glPopMatrix();
				//draw clavicle
				glPushMatrix();
				{
					glTranslatef(1.0f, 0.0f, 1.9f);
					glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
					drawBone(var);
				}
				glPopMatrix();
				//draw back vertebrae
				glPushMatrix();
				{
					glTranslatef(0.0f, -0.2f, 0.0f);
					drawBackVertebrae();
				}
				glPopMatrix();
			}
			glPopMatrix();
			
			//draw lower backbone
			glPushMatrix();
			{

				boneLength = 1.0f;
				drawBone(var);
			}
			glPopMatrix();
			//draw front abdomen
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				glScalef(0.9f, 0.9f, 0.9f);
				drawFrontArmor();
			}
			glPopMatrix();
		
			boneLength = 2.0f;
		}
		glPopMatrix();
		//draw hips
		glPushMatrix();
		{
			boneLength = 1.0f;
			glTranslatef(0.5f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			drawBone(var);
			boneLength = 2.0f;
		}
		glPopMatrix();
		drawHips(var);
		//draw hips details
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(0.30f, 0.0f, 0.25f);
				glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
				glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
				gluCylinder(var, radius / 7.0f, radius / 7.0f, 0.6f, 8, stacks);
				gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.6f);
					gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.1f);
				glScalef(0.2f,0.1f,0.30f);
				drawFilledCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
		
	}
	glPopMatrix();
	
}

void drawFingerArmor(GLUquadricObj *var) {
	glPushMatrix(); {
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		glTranslatef(-0.15f,0.0f,0.0f);
		glRotatef(45.0f,0.0f,0.0f,1.0f);
		gluCylinder(var,radius/5.5f,radius/5.5f,0.50f,4,stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.5f);
			gluDisk(var,0.0f, radius / 5.5f,4,stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.5f);
				gluDisk(var, 0.0f, radius / 5.5f, 4, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFinger(GLUquadricObj *var) {
	glPushMatrix();
	{
		
		boneLength = 0.35f;
		drawBone(var);
		glPushMatrix();
		{
			glScalef(0.9f, 0.7f, 0.9f);
			drawFingerArmor(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.1f); //Switch origin to prefered rotate point.
			glRotatef(fingersAngle, 0.0f, 1.0f, 0.0f); //Rotating joint.
			radius = 0.5f;
			drawHingeJoint(var);
			glPushMatrix();
			{
				glRotatef(90.0f,0.0f,0.0f,1.0f);
				glScalef(0.8f,1.7f,1.7f);
				drawHingeJointArmor(var);
			}
			glPopMatrix();
			
			radius = 1.0f;
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f); //Switch origin back to previous point.
				glTranslatef(0.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 0.30f;
				drawBone(var);
				glPushMatrix();
				{
					glScalef(-1.0f, 1.0f, 1.0f);
					glScalef(0.8f, 0.6f, 0.8f);
					drawFingerArmor(var);
				}
				glPopMatrix();
					
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f); //Switch origin to prefered rotate point.
					glRotatef(fingersAngle, 0.0f, 1.0f, 0.0f); //Rotating joint.
					radius = 0.5f;
					drawHingeJoint(var);
					glPushMatrix();
					{
						glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
						glScalef(0.8f, 1.7f, 1.7f);
						drawHingeJointArmor(var);
					}
					glPopMatrix();
					radius = 1.0f;
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, -0.4f); //Switch origin back to previous point.
						glTranslatef(0.0f, 0.0f, 0.0f);
						boneLength = 0.30f;
						drawBone(var);
						glPushMatrix();
						{
							glScalef(0.7f, 0.5f, 0.7f);
							drawFingerArmor(var);
						}
						glPopMatrix();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();
	
}

void drawHandArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		//draw palm details
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.1f, 0.05f);
			glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
			gluCylinder(var, radius / 8.0f, 0.0f, 0.05f, 4, stacks);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.1f, 0.05f);
			glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
			gluCylinder(var, radius / 8.0f, 0.0f, 0.05f, 4, stacks);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.1f, -0.2f, 0.05f);
			glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 16.0f, radius / 16.0f, 0.40f, 3, stacks);
			gluDisk(var, 0.0f, radius / 16.0f, 3, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.4f);
				gluDisk(var, 0.0f, radius / 16.0f, 3, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		// draw hand back details
		glPushMatrix();
		{
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
			glTranslatef(0.0f,0.0f,-0.09f);
			glPushMatrix(); {
				glTranslatef(0.10f,-0.07f,-0.05f);
				glRotatef(-10.0f,0.0f,0.0f,1.0f);
				glScalef(0.08f,0.01f,0.05f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix(); {
				glScalef(1.0f, -1.0f, 1.0f);
				glTranslatef(0.10f, -0.07f, -0.05f);
				glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.08f, 0.01f, 0.05f);
				drawCover();
			}
			glPopMatrix();
			
			glPushMatrix(); {
				glTranslatef(0.13f, 0.0f, -0.05f);
				glScalef(0.025f, 0.07f, 0.05f);
				drawCover();
			}
			glPopMatrix();
			
			glPushMatrix(); {
				glTranslatef(0.05f, 0.0f, -0.03f);
				glScalef(0.06f, 0.06f, 0.02f);
				drawCover();
			}
			glPopMatrix();
			
			glPushMatrix(); {
				glTranslatef(0.0f, -0.15f, -0.05f);
				glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.16f, 0.02f, 0.07f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix(); {
				glScalef(1.0f, -1.0f, 1.0f);
				glTranslatef(0.0f, -0.15f, -0.05f);
				glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.16f, 0.02f, 0.07f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(-0.1f, 0.0f, -0.08f);
				glScalef(0.10f, 0.10f, 0.02f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
	}
	glPopMatrix();
	
}


void drawLeftHand(GLUquadricObj *var) {
	glPushMatrix();
	{
		glScalef(-1.0f,1.0f,1.0f);
		drawHandArmor(var);
		glPushMatrix();
		{
			glScalef(0.05f, 0.17f, 0.17f);
			drawFilledCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			//draw middle finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.1f, -0.9f);
				drawFinger(var);
			}
			glPopMatrix();
			//draw index finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.5f, -0.9f);
				drawFinger(var);
			}
			glPopMatrix();
			glScalef(-1.0f, 1.0f, 1.0f);
			//draw ring finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, -0.3f, -0.9f);
				drawFinger(var);
			}
			glPopMatrix();
			glScalef(-1.0f, 1.0f, 1.0f);
			//draw little finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.25f);
				glTranslatef(0.0f, -0.6f, -5.0f);
				drawFinger(var);
			}
			glPopMatrix();
			glScalef(-1.0f, 1.0f, 1.0f);
			//draw thumb
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, 0.28f);
				glTranslatef(0.0f, -0.8f, -3.5f);
				glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
				drawFinger(var);
			}
			glPopMatrix();
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void drawRightHand(GLUquadricObj *var) {
	glPushMatrix();
	{
		drawHandArmor(var);
		glPushMatrix();
		{
			glScalef(0.05f, 0.17f, 0.17f);
			drawFilledCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			//draw middle finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.1f, -0.9f);
				drawFinger(var);
			}
			glPopMatrix();
			//draw index finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.5f, -0.9f);
				drawFinger(var);
			}
			glPopMatrix();
			//draw ring finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, -0.3f, -0.9f);
				drawFinger(var);
			}
			glPopMatrix();
			//draw little finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.25f);
				glTranslatef(0.0f, -0.6f, -5.0f);
				drawFinger(var);
			}
			glPopMatrix();
			//draw thumb
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, 0.28f);
				glTranslatef(0.0f, -0.8f, -3.5f);
				glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
				drawFinger(var);
			}
			glPopMatrix();
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void drawUpperArmHinge(GLUquadricObj *var) {
	glPushMatrix();
	{
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(var, radius / 14.0f, radius / 14.0f, 0.5f, 8.0f, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.5f);
			gluDisk(var, 0.0f, radius / 14.0f, 8.0f, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawDeltoidCover() {
	glPushMatrix(); {
		glTranslatef(-0.15f, 0.18f, 0.15f);
		glRotatef(-10.0f,1.0f, 0.0f, 0.0f);
		glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.30f,0.04f,0.20f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.05f, 0.18f, 0.25f);
		glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(20.0f,0.0f,1.0f,0.0f);
		glPushMatrix();
		{
			glScalef(0.20f, 0.025f, 0.20f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.10f, 0.18f, 0.45f);
		glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
		//glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.18f, 0.025f, 0.10f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawBicepCover(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		glTranslatef(0.10f, 0.23f, 0.80f);
		glPushMatrix();
		{
			glRotatef(90.0f,1.0f,0.0f,0.0f);
			glScalef(0.7f, 1.7f, 1.0f);
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			gluCylinder(var, radius / 12.0f, radius / 5.0f, 0.2f, 4, stacks);
			gluDisk(var, 0.0f, radius / 12.0f, 4, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawTricepCover() {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		//glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0.10f, 0.18f, 0.80f);
		glPushMatrix();
		{
			glTranslatef(0.18f, -0.2f, -0.015f);
			glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-100.0f,0.0f,0.0f,1.0f);
			glScalef(0.10f, 0.02f, 0.12f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.15f, -0.30f, -0.06f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.05f, 0.02f, 0.14f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.35f, -0.08f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-170.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.02f, 0.15f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.15f, -0.30f, -0.17f);
			glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-260.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.12f, 0.03f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.15f, -0.30f, -0.08f);
			glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-260.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.10f, 0.03f, 0.05f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawTricepDetails(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glTranslatef(0.0f, -0.05f, 0.90f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix(); {
			glScalef(1.5f, 1.0f, 1.0f);
			gluCylinder(var, radius / 7.0f, radius / 7.0f, 0.15f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.15f);
				gluDisk(var, 0.0f, radius / 7.0f, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, -0.15f);
					gluDisk(var, 0.0f, radius / 7.0f, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawUpperArmArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		//draw upper arm hinge
		glPushMatrix();
		{	glTranslatef(-0.3f, 0.0f, 0.05f);
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
			for (int i = 1; i < 5; i++) {
				glPushMatrix(); {
					glTranslatef(i / 50.0f, 0.0f, 0.0f);
					glScalef(1.0f, 2.0 / i, 2.0 / i);
					drawUpperArmHinge(var);
				}
				glPopMatrix();	
			}
			//draw upper arm hinge details
			for (int i = 0; i < 3; i++) {
				glPushMatrix();
				{
					glTranslatef(i / 15.0f, 0.0f, i/40.0f);
					glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
					glTranslatef(0.07f, 0.0f, 0.20f);
					glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
					gluCylinder(var, radius / 5.0f, radius / 5.0f, 0.05f, 8, stacks);
					glPushMatrix();
					{
						gluDisk(var, 0.0f, radius / 5.0f, 8, stacks);
						glTranslatef(0.0f, 0.0f, 0.05f);
						gluDisk(var, 0.0f, radius / 5.0f, 8, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPushMatrix(); {
				glTranslatef(0.50f, 0.0f, 0.15f);
				gluCylinder(var, radius / 15.0f, radius / 10.0f, 0.1f, 6, stacks);
				glTranslatef(0.0f, 0.0f, 0.20f);
				gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.1f, 6, stacks);
				glTranslatef(0.0f, 0.0f, -0.10f);
				gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.3f, 8, stacks);
			}
			glPopMatrix();
		
		}
		glPopMatrix();

		//draw upper arm fins
		glPushMatrix(); {
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
			glTranslatef(-0.08f, -0.1f, -0.08f);
			for (int i = 0; i < 7; i++) {
				glPushMatrix(); {
					glTranslatef(0.0f, 0.03f*i,0.0f);
					glScalef(0.28f, 0.005f, 0.05f);
					drawFilledCube();
				}
				glPopMatrix();
			}
			
		}
		glPopMatrix();
		
		//draw upper arm deltoid cover
		glPushMatrix();
		{
			
			drawDeltoidCover();
			glPushMatrix();
			{
				glScalef(1.0f, -1.0f, 1.0f);
				drawDeltoidCover();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw upper arm bicep cover
		drawBicepCover(var);
		//draw upper arm tricep cover
		drawTricepCover();
		
		//draw upper arm tricep details
		drawTricepDetails(var);
		glPushMatrix();
		{
			glTranslatef(0.0f,0.0f,-0.15f);
			glScalef(0.2f,1.0f,1.2f);
			drawTricepDetails(var);
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(-0.7f, 0.0f, 0.0f);
			drawTricepDetails(var);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawTripleCover() {
	glPushMatrix();
	{
		glTranslatef(-0.15f, -0.20f, 0.28f);
		glRotatef(-220.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.10f, 0.03f, 0.15f);
		drawCover();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.22f, -0.05f, 0.28f);
		glRotatef(-260.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.10f, 0.03f, 0.15f);
		drawCover();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.15f, 0.1f, 0.28f);
		glRotatef(-310.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.11f, 0.03f, 0.15f);
		drawCover();
	}
	glPopMatrix();
}

void drawLowerArmCover() {
	
	glPushMatrix();
	{
		glTranslatef(0.1f,0.19f,0.4f);
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.1f,0.01f,0.35f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	glPushMatrix();
	{
		glTranslatef(0.17f, 0.12f, 0.4f);
		glRotatef(-60.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.07f, 0.01f, 0.35f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	glPushMatrix();
	{
		glTranslatef(0.22f, 0.0f, 0.36f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.10f, 0.01f, 0.4f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.10f, -0.18f, 0.4f);
		glRotatef(-135.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.17f, 0.01f, 0.1f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();

	drawTripleCover();
	glPushMatrix();
	{
		glTranslatef(0.01f, 0.0f, 0.2f);
		glScalef(1.0f, 0.6f, 1.0f);
		drawTripleCover();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.10f, 0.0f);
		glRotatef(75.0f,0.0f,0.0f,1.0f);
		glRotatef(5.0f,0.0f,1.0f,0.0f);
		glScalef(0.5f, 0.5f, 1.0f);
		drawTripleCover();
	}
	glPopMatrix();

}

void drawLowerArmArmor(GLUquadricObj *var) {
	//draw lower arm details
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glTranslatef(0.0f, 0.0f, 0.2f);
		gluCylinder(var,radius/7.0f,radius/8.0f,0.5f,6,stacks);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(-0.07f, -0.6f, -0.3f);
		glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
		drawTricepDetails(var);
	}
	glPopMatrix();

	//draw lower arm armor
	drawLowerArmCover();

	//draw rocket punch booster
	glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.15f, 0.1f);
		gluCylinder(var, radius / 20.0f, 0.0f, 0.4f, 8, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.05f);
			glColor3f(0.0f, 0.0f, 0.0f);
			gluDisk(var, 0.0f, radius / 24.0f, 8 ,stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();
}



void drawHandJointArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f,0.1f,0.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.2f, 0.8f, 0.8f);
		drawHingeJointArmor(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.02f, 0.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.2f, 0.8f, 0.8f);
		drawHingeJointArmor(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.08f, 0.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.3f, 0.8f, 0.8f);
		drawHingeJointArmor(var);
	}
	glPopMatrix();
}

void drawLeftArm(GLUquadricObj *var) {
	glPushMatrix();
	{
		boneLength = 1.2f;
		drawBone(var);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.2f); //Switch origin to prefered rotate point.
			glRotatef(leftArmAngle2, 1.0f, 0.0f, 0.0f); //Rotating joint.
			drawHingeJoint(var);
			drawHingeJointArmor(var);
			drawFloatHingeJointArmor(var);
			glPushMatrix();
			{
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
				//glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				//glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 0.8f;
				drawBone(var);
				drawLowerArmArmor(var);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.8f);
					drawHingeJoint(var);
					drawHandJointArmor(var);
					glTranslatef(0.0f, 0.0f, 0.2f);
					drawLeftHand(var);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	boneLength = 2.0f;
}

void drawRightArm(GLUquadricObj *var) {
	glPushMatrix();
	{
		boneLength = 1.2f;
		drawBone(var);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.2f); 
			glRotatef(rightArmAngle2, 1.0f, 0.0f, 0.0f);
			drawHingeJoint(var);
			glPushMatrix(); {
				glScalef(-1.0f, 1.0f, 1.0f);
				drawHingeJointArmor(var);
				drawFloatHingeJointArmor(var);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
				//glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				//glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 0.8f;
				drawBone(var);
				glPushMatrix(); {
					glScalef(-1.0f, 1.0f, 1.0f);
					drawLowerArmArmor(var);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.8f);
					drawHingeJoint(var);
					glPushMatrix(); {
						glScalef(-1.0f, 1.0f, 1.0f);
						drawHandJointArmor(var);
					}
					glPopMatrix();
					glTranslatef(0.0f, 0.0f, 0.2f);
					drawRightHand(var);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	boneLength = 2.0f;
}

void drawLeftFoot(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.2f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		boneLength = 0.6f;
		drawBone(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.4f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		boneLength = 0.2f;
		drawBone(var);
	}
	glPopMatrix();
	boneLength = 2.0f;
}

void drawRightFoot(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.2f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		boneLength = 0.6f;
		drawBone(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.4f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		boneLength = 0.2f;
		drawBone(var);
	}
	glPopMatrix();
	boneLength = 2.0f;
}

void drawUpperLegJointArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glTranslatef(0.10f,0.0f,0.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(var, radius / 15.0f, radius / 15.0f, 0.5f, 6, stacks);
		gluDisk(var, 0.0f, radius / 15.0f, 6, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.4f);
			gluDisk(var, 0.0f, radius / 15.0f, 6, stacks);
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0f, 0.0f, -0.1f);
			gluCylinder(var, radius / 5.0f, radius / 5.0f, 0.1f, 6, stacks);
			gluDisk(var, 0.0f, radius / 5.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(var, 0.0f, radius / 5.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		glPushMatrix(); {
			glTranslatef(0.0f, 0.0f, 0.35f);
			glScalef(1.0f, 1.2f, 1.0f);
			gluCylinder(var, radius / 6.0f, radius / 6.0f, 0.1f, 6, stacks);
			gluDisk(var, 0.0f, radius / 6.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(var, 0.0f, radius / 6.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	//Thigh bone joint connection
	glPushMatrix();
	{
		glTranslatef(0.1f, 0.10f, 0.0f);
		glRotatef(-90.0f, 0.0f,1.0f,0.0f);
		gluCylinder(var, radius / 20.0f, radius / 20.0f, 0.4f, 4, stacks);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.075f, 0.10f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		gluCylinder(var, radius / 25.0f, radius / 25.0f, 0.2f, 4, stacks);
		gluDisk(var, 0.0f, radius / 25.0f, 4, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.2f);
			gluDisk(var, 0.0f, radius / 25.0f, 4, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawThighBone(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(-0.075f, -0.025f, -0.1f);
		glPushMatrix();
		{
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			glPushMatrix(); {
				gluCylinder(var, radius / 14.0f, radius / 14.0f, 0.8f, 4, stacks);
				gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.8f);
					gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.2f);
				gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.8f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix(); {
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
			glTranslatef(0.06f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 14.0f, radius / 14.0f, 0.12f, 6, stacks);
			gluDisk(var, 0.0f, radius / 14.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.12f);
				gluDisk(var, 0.0f, radius / 14.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
}

void drawThighBoneConnection(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		glTranslatef(0.27f, 0.0f, 0.9f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.50f, 6, stacks);
		gluDisk(var, 0.0f, radius / 10.0f, 6, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.50f);
			gluDisk(var, 0.0f, radius / 10.0f, 6, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawThighArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		//draw Thigh details
		glPushMatrix();
		{
			glTranslatef(0.1f,0.15f,0.2f);
			drawThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawThighBone(var);
			drawThighBoneConnection(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.1f, -0.15f, 0.2f);
			glScalef(1.1f,1.1f,1.2f);
			drawThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawThighBone(var);
			drawThighBoneConnection(var);
			glPushMatrix();
			{
				glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
				glTranslatef(0.05f, 0.1f, 1.05f);
				glScalef(0.2f, 0.1f, 0.15f);
				drawFilledCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glPushMatrix();
		{
			glTranslatef(0.05f, 0.15f, 1.19f);
			gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.50f, 8, stacks);
			gluDisk(var, 0.0f, radius / 10.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.45f);
				gluDisk(var, 0.0f, radius / 10.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-0.20f, 0.15f, 1.19f);
			gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.50f, 8, stacks);
			gluDisk(var, 0.0f, radius / 10.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.45f);
				gluDisk(var, 0.0f, radius / 10.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.20f, 0.15f,1.70f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.55f, 8, stacks);
			gluDisk(var, 0.0f, radius / 12.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.55f);
				gluDisk(var, 0.0f, radius / 12.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void drawUpperLegArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		drawUpperLegJointArmor(var);
		drawThighArmor(var);
	}
	glPopMatrix();
}

void drawLowerLegJointArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glTranslatef(0.10f,0.0f,-0.3f);
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		glPushMatrix();
		{
			glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
			glScalef(1.0f, 1.5f, 1.0f);
			gluCylinder(var, radius / 4.0f, radius / 4.0f, 0.2f, 10, stacks);
			gluDisk(var, 0.0f, radius / 4.0f, 10, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.2f);
				gluDisk(var, 0.0f, radius / 4.0f, 10, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.05f);
			gluCylinder(var, radius / 5.0f, radius / 5.0f, 0.35f, 8, stacks);
			gluDisk(var, 0.0f, radius / 5.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.35f);
				gluDisk(var, 0.0f, radius / 5.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.12f);
			gluCylinder(var, radius / 7.5f, radius / 7.5f, 0.6f, 8, stacks);
			gluDisk(var, 0.0f, radius / 7.5f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.6f);
				gluDisk(var, 0.0f, radius / 7.5f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-0.28f, 0.25f, 0.0f);
			gluCylinder(var, radius / 6.0f, radius / 6.0f, 0.4f, 8, stacks);
			gluDisk(var, 0.0f, radius / 6.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.4f);
				gluDisk(var, 0.0f, radius / 6.0f, 8, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.15f);
				gluCylinder(var, radius / 6.5f, radius / 6.5f, 0.4f, 8, stacks);
				gluDisk(var, 0.0f, radius / 6.5f, 8, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);
					gluDisk(var, 0.0f, radius / 6.5f, 8, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawLowerLegArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glTranslatef(0.0f,0.15f,0.5f);
		//draw joint connector
		glPushMatrix();
		{
			glTranslatef(0.15f, 0.0f, 0.0f);
			glRotatef(-30.0f,1.0f,0.0f,0.0f);
			glScalef(0.03f,0.1f,0.08f);
			drawFilledCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.15f, 0.0f, 0.0f);
			glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.03f, 0.1f, 0.08f);
			drawFilledCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.2f);
			glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.17f, 0.20f, 0.10f);
			drawFilledCube();
		}
		glPopMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		//draw shin details
		glPushMatrix();
		{
			glTranslatef(0.2f, 0.15f, 0.4f);
			glRotatef(15.0f,1.0f,0.0f,0.0f);
			drawThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawThighBone(var);
			drawThighBoneConnection(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.2f, 0.0f, 0.30f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			drawThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawThighBone(var);
		}
		glPopMatrix();
		//draw lower leg booster
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.15f, 0.30f);
			glRotatef(80.0f,1.0f,0.0f,0.0f);
			gluCylinder(var, radius / 3.5f, radius / 5.5f, 0.5f, 8, stacks);
			gluDisk(var, 0.0f, radius / 3.5f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.5f);
				gluDisk(var, 0.0f, radius / 5.5f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.20f, 0.30f);
			glRotatef(85.0f, 1.0f, 0.0f, 0.0f);
			gluCylinder(var, radius / 9.0f, radius / 9.0f, 0.5f, 8, stacks);
			gluDisk(var, 0.0f, radius / 9.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.5f);
				gluDisk(var, 0.0f, radius / 9.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		//draw calf details
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.30f, 0.30f);
			gluCylinder(var, radius / 7.0f, radius / 7.0f, 1.0f, 6, stacks);
			gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 1.0f);
				gluDisk(var, 0.0f, radius / 7.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.2f, -0.40f, 0.8f);
			glRotatef(90.0f,0.0f,1.0f,0.0f);
			gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.4f, 6, stacks);
			gluDisk(var, 0.0f, radius / 12.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.4f);
				gluDisk(var, 0.0f, radius / 12.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		{
			glTranslatef(-0.05f, -0.40f, 1.10f);
			glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.0f,3.5f,1.0f);
			gluCylinder(var, radius / 15.0f, radius / 15.0f, 0.1f, 8, stacks);
			gluDisk(var, 0.0f, radius / 15.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(var, 0.0f, radius / 15.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.05f, -0.40f, 1.10f);
			glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.0f, 3.5f, 1.0f);
			gluCylinder(var, radius / 15.0f, radius / 15.0f, 0.1f, 8, stacks);
			gluDisk(var, 0.0f, radius / 15.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(var, 0.0f, radius / 15.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawLeftLeg(GLUquadricObj *var) {
	glPushMatrix();
	{
		boneLength = 1.7f;
		drawBone(var);
		drawUpperLegArmor(var);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.7f); //Switch origin to prefered rotate point.
			glRotatef(leftLegAngle2, leftLegAxis[1][0], leftLegAxis[1][1], leftLegAxis[1][2]); //Rotating joint.
			drawHingeJoint(var);
			drawLowerLegJointArmor(var);
			glPushMatrix();
			{
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
				//glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				//glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 2.0f;
				drawBone(var);
				drawLowerLegArmor(var);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 2.0f);
					glRotatef(leftLegAngle3, leftLegAxis[2][0], leftLegAxis[2][1], leftLegAxis[2][2]); //Rotating joint.
					drawBallJoint(var);
					drawLeftFoot(var);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	boneLength = 2.0f;
}

void drawRightLeg(GLUquadricObj *var) {
	glPushMatrix();
	{
		boneLength = 1.7f;
		drawBone(var);
		glPushMatrix(); {
			glScalef(-1.0f, 1.0f, 1.0f);
			drawUpperLegArmor(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.7f); //Switch origin to prefered rotate point.
			glRotatef(rightLegAngle2, rightLegAxis[1][0], rightLegAxis[1][1], rightLegAxis[1][2]); //Rotating joint.
			drawHingeJoint(var);
			glPushMatrix(); {
				glScalef(-1.0f, 1.0f, 1.0f);
				drawLowerLegJointArmor(var);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
				//glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				//glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 2.0f;
				drawBone(var);
				glPushMatrix(); {
					glScalef(-1.0f, 1.0f, 1.0f);
					drawLowerLegArmor(var);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 2.0f);
					glRotatef(rightLegAngle3, rightLegAxis[2][0], rightLegAxis[2][1], rightLegAxis[2][2]); //Rotating joint.
					drawBallJoint(var);
					drawRightFoot(var);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	boneLength = 2.0f;
}


void leftKeyAction() {
	upperBodyJointAngle += 1.0f;
}

void rightKeyAction() {
	upperBodyJointAngle -= 1.0f;
}

void upKeyAction() {
	bodyJointAngle -= 1.0f;
}

void downKeyAction() {
	bodyJointAngle += 1.0f;
}

void wKeyAction() {
	if (!leftFrontWalked) {
		if (firstWalk) {
			rightArmAngle1 -= 0.2f;
			rightArmAngle2 -= 0.3f;
		}
		else {
			rightArmAngle1 -= 0.2f;
			rightArmAngle2 -= 0.3f;
			leftArmAngle1 += 0.2f;
			leftArmAngle2 += 0.3f;
		}
		
		if (!leftFrontMax && leftLegAngle1 >= 140.0f && leftLegAngle2 <= 250.0f) {
			leftLegAngle1 -= 1.0f;
			leftLegAngle2 += 2.0f;
		}
		else {
			leftFrontMax = true;
		}
		if (leftFrontMax) {
			if (leftLegAngle2 >= 220.0f) {
				leftLegAngle2 -= 1.0f;
			}
				
			if (leftLegAngle2 < 220.0f && leftLegAngle1 <= 180.0f) {
				leftLegAngle1 += 1.0f;
				leftLegAngle2 -= 1.0f;
				yPosition -= 0.01f;
			}

		}
		if (leftLegAngle1 == 180.0f) {
			firstWalk = false;
			leftFrontMax = false;
			leftFrontWalked = true;
		}
	}
	else {
		rightArmAngle1 += 0.2f;
		rightArmAngle2 += 0.3f;
		leftArmAngle1 -= 0.2f;
		leftArmAngle2 -= 0.3f;
		if (!rightFrontMax && rightLegAngle1 >= 140.0f && rightLegAngle2 <= 250.0f) {
			rightLegAngle1 -= 1.0f;
			rightLegAngle2 += 2.0f;
		}
		else {
			rightFrontMax = true;
		}
		if (rightFrontMax) {
			if (rightLegAngle2 >= 220.0f)
				rightLegAngle2 -= 1.0f;
			if (rightLegAngle2 < 220.0f && rightLegAngle1 <= 180.0f) {
				rightLegAngle1 += 1.0f;
				rightLegAngle2 -= 1.0f;
				yPosition -= 0.01f;
			}

		}
		if (rightLegAngle1 == 180.0f) {
			rightFrontMax = false;
			leftFrontWalked = false;
			rightFrontWalked = true;
		}
	}
	
}

void aKeyAction() {
	leftLegAngle1 -= 1.0f;
}

void sKeyAction() {
	yPosition += 0.01;
}

void dKeyAction() {
	leftLegAngle1 -= 1.0f;
}

void qKeyAction() {
	leftLegAngle1 -= 1.0f;
}

void eKeyAction() {
	leftLegAngle1 -= 1.0f;
}

void drawGipsyDanger(GLUquadricObj *var) {
	glTranslatef(xPosition, yPosition, zPosition);
	drawSpine(var);
	glPushMatrix();
	{
		glTranslatef(1.0f, 0.0f, 1.8f); //Switch origin to prefered rotate point.
		glRotatef(leftArmAngle1, 1.0f, 0.0f, 0.0f); //Rotating joint.
		drawBallJoint(var);
		drawUpperArmArmor(var);
		glPushMatrix();
		{
			glTranslatef(0.1f, 0.0f, 0.0f);
			drawLeftArm(var);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1.0f, 0.0f, 1.8f); //Switch origin to prefered rotate point.
		glRotatef(rightArmAngle1, 1.0f, 0.0f, 0.0f); //Rotating joint.
		drawBallJoint(var);
		glPushMatrix(); {
			glScalef(-1.0f, 1.0f, 1.0f);
			drawUpperArmArmor(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.1f, 0.0f, 0.0f);
			drawRightArm(var);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.5f, 0.0f, 0.0f); //Switch origin to prefered rotate point.
		glRotatef(leftLegAngle1, leftLegAxis[0][0], leftLegAxis[0][1], leftLegAxis[0][2]);  //Rotating joint.
		drawBallJoint(var);
		glPushMatrix();
		{
			drawLeftLeg(var);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.5f, 0.0f, 0.0f); //Switch origin to prefered rotate point.
		glRotatef(rightLegAngle1, rightLegAxis[0][0], rightLegAxis[0][1], rightLegAxis[0][2]); //Rotating joint.
		drawBallJoint(var);
		glPushMatrix();
		{
			drawRightLeg(var);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);

	//glClearColor((float)121 / 255, (float)168 / 255, (float)224 / 255, 1.0f);
	//glClearColor((float)60 / 255, (float)128 / 255, (float)191 / 255, 1.0f);
	//glClearColor((float)69 / 255, (float)156 / 255, (float)236 / 255, 1.0f);

	if (!weather) {
		glClearColor((float)1 / 255, (float)108 / 255, (float)178 / 255, 1.0f);
	}
	else {
		glClearColor((float)143 / 255, (float)188 / 255, (float)223 / 255, 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	GLUquadricObj *var = NULL;

	(GLUquadricObj *)var = gluNewQuadric();
	gluQuadricNormals(var, GLU_SMOOTH);
	gluQuadricTexture(var, GL_TRUE);

	glEnable(GL_TEXTURE_2D);

	GLfloat light_ambient[] = { 1.0, 1.0 ,1.0, 1.0 };
	GLfloat light_close[] = { 0.0, 0.0 ,0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat light_position[] = { x,y,z, 0.0 };


	if (ambientOn) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
	else {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_close);
	}

	if (diffuseOn) {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	}
	else {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_close);
	}

	if (specularOn) {
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	}
	else {
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_close);
	}

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0); //enable the light after setting the properties

	GLfloat no_shininess[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat low_shininess[] = { 5.0f, 5.0f, 5.0f, 0.0f };
	GLfloat high_shininess[] = { 100.0f, 100.0f, 100.0f, 100.0f };
	GLfloat mat_emission[] = { 0.5f, 0.5f, 0.5f, 0.0f };

	glPushMatrix();
	{
		glTranslatef(light_position[0], light_position[1], light_position[2]);
		glColor3f(255 / 255.0f, 255 / 255.0f, 255 / 255.0f);
		//gluSphere(var, radius / 4.0f, slices, stacks);
	}
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);



	glLoadIdentity();
	glTranslatef(0.0, 0.0, zoomLevel);

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	glRotatef(xRotated, 1.0, 0.0, 0.0);

	glRotatef(yRotated, 0.0, 1.0, 0.0);

	glRotatef(zRotated, 0.0, 0.0, 1.0);

	//gluQuadricDrawStyle(var, GLU_LINE);

	//drawRobotArm();


	drawGipsyDanger(var);

	gluDeleteQuadric(var);


	glFlush();	//Empty all GL buffers.

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.0, 0.6, 21.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_STENCIL_TEST);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	//glStencilFunc(GL_ALWAYS, 0, 1); // these are also the default parameters
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	//glEnable(GL_LIGHTING);
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (reactorRotateAngle < 360)
			reactorRotateAngle += 2.0f;
		else
			reactorRotateAngle = 0.0f;

		display();

		SwapBuffers(hdc);
	}
	glDisable(GL_LIGHTING);
	//glDisable(GL_STENCIL_TEST);
	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}