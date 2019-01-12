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

bool scene1 = false;

GLfloat ctrlpoints[3][3] = {
	{ 6, 4, 0 },{ 4, -2, 0 },{ 0, 1.5, 0 }
};

float xRotated = 1.0f, yRotated = 1.0f, zRotated = -30.0f;


float x = 0.0f, y = 0.0f, z = 1.0f;

float radius = 1.0f;
float angle = 0.01f;
float baseRadius = 0.1f;
int slices = 20, stacks = 20;

float headAngle1 = 180.0f;

float fingersAngle = 180.0f;
float leftLegAngle1 = 180.0f, leftLegAngle2 = 180.0f, leftLegAngle3 = 180.0f;
float rightLegAngle1 = 180.0f, rightLegAngle2 = 180.0f, rightLegAngle3 = 180.0f;
float leftArmAngle1 = 180.0f, leftArmAngle2 = 180.0f, leftArmAngle3 = 180.0f;
float rightArmAngle1 = 180.0f, rightArmAngle2 = 180.0f, rightArmAngle3 = 180.0f;

float bodyJointAngle = 1.0f, upperBodyJointAngle = 0.0f;

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

bool textureOn = false;

//Gipsy Danger texture
GLuint armorTexture, metalTexture, backConnectorTexture, reactorOutringTexture, reactorTurn1Texture, eyesTexture;

//London Tower Bridge texture
GLuint roof, smallTower, towerFront, baseBridgeTexture, sideFenceTexture, base, seaTexture, roadTexture;
GLuint sandStoneTexture, bridgeTexture, brickRoadTexture;

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
			textureOn = false;
			break;
		}
		break;
	case WM_LBUTTONUP:
		if(!textureOn)
			//textureOn = true;
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
		case 'T':
			textureOn = !textureOn;
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
		case 0x30:
			scene1 = !scene1;
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

	armorTexture = LoadBMP("textures/armor_texture.bmp");
}

GLuint LoadBMP(char* fileName) {
	if (textureOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
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
	else
		return 0;
}

GLuint LoadBMPForReactor(char* fileName) {
	glColor3f(1.0f, 1.0f, 1.0f);
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
		gluCylinder(var, radius/28, radius/28, boneLength, 6, stacks);
	}
	glPopMatrix();
	
}

void drawBallJoint(GLUquadricObj *var) {
	glPushMatrix();
	{
		gluSphere(var, radius / 25.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawHingeJoint(GLUquadricObj *var) {
	glPushMatrix();
	{
		gluSphere(var, radius / 25.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawCover() {
	glPushMatrix();
	{	
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		glBindTexture(GL_TEXTURE_2D, armorTexture);
		drawFilledCube();
		glDeleteTextures(1, &armorTexture);
	}
	glPopMatrix();
	
}

void drawFloatHingeJointArmor(GLUquadricObj *var) {

	glPushMatrix(); {
		glTranslatef(-0.17f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);
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
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);
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
	texture = LoadBMP("armor_texture.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix(); {
		glTranslatef(0.0f, 0.0f, 2.02f);
		glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f,1.5f,1.0f);
		gluCylinder(var,radius/4.0f,radius/4.5f,0.08f,slices,stacks);
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
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
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		gluCylinder(var, radius / 8.0f, radius / 6.0f, 0.5f, 7, stacks * 2);
		glDeleteTextures(1, &texture);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			gluDisk(var, 0.0f, radius / 8.0f, 7, 20);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		texture = LoadBMP("armor_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			gluCylinder(var, radius / 6.5f, radius / 5.8f, 0.45f, 7, stacks * 2);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
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
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glScalef(0.5f,1.5f,1.0f);
		gluCylinder(var, radius / 6.0f, radius / 4.5f, 0.3f, 10, stacks*5);
		glDeleteTextures(1, &texture);
		glPushMatrix();
		{
			texture = LoadBMP("back_connector.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glColor3f(119 / 255.0f, 99 / 255.0f, 94 / 255.0f);
			glTranslatef(0.0f, 0.0f, 0.05f);
			gluDisk(var, 0.0f, radius / 6.0f, 10, 20);
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void drawBackVertebraeBone() {
	glPushMatrix(); {
		glScalef(0.08f, 0.01f, 0.1f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
	glDeleteTextures(1, &texture);
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
			texture = LoadBMP("armor_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluCylinder(var, radius / 4, radius / 3, 0.1f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluCylinder(var, radius / 3, radius / 4, 0.1f, slices, stacks);
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(var, 0, radius / 4, slices, stacks);
			}
			glPopMatrix();
			
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix(); {
			
			texture = LoadBMPForReactor("reactor_outring_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluCylinder(var, radius / 5, radius / 4, 0.02f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix(); {
			glRotatef(-reactorRotateAngle,0.0f,0.0f,1.0f);
			
			texture = LoadBMPForReactor("reactor_turn1_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluCylinder(var, radius / 5, radius / 12, 0.1f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			texture = LoadBMPForReactor("reactor_outring_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			gluSphere(var, radius / 12, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix(); {
			glTranslatef(0.0f, 0.0f, 0.025f);
			glRotatef(reactorRotateAngle, 0.0f, 0.0f, 1.0f);
			
			texture = LoadBMPForReactor("reactor_turn1_texture.bmp");
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
			
			texture = LoadBMP("armor_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
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
			glDeleteTextures(1, &texture);
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
		
		texture = LoadBMP("armor_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
	glDeleteTextures(1, &texture);
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
				glTranslatef(0.0f, 0.80f, -0.1f);
				glRotatef(-5.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.40f, 0.15f, 0.25f);
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
					
					texture = LoadBMP("metal_texture.bmp");
					glBindTexture(GL_TEXTURE_2D, texture);
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
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);
					glScalef(3.3f, 1.0f, 1.0f);
					gluCylinder(var, radius / 7.5f, radius / 7.5f, 0.8f, slices, stacks);
					gluDisk(var, 0.0f, radius / 7.5f, slices, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.8f);
						gluDisk(var, 0.0f, radius / 7.5f, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
				glDeleteTextures(1, &texture);
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
				
				texture = LoadBMP("metal_texture.bmp");
				glBindTexture(GL_TEXTURE_2D, texture);
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
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
	
}

void drawFingerArmor(GLUquadricObj *var) {
	glPushMatrix(); {
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		
		texture = LoadBMP("armor_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
			glDeleteTextures(1, &texture);
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
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
			glDeleteTextures(1, &texture);
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
			drawCover();
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
			drawCover();
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
		
		texture = LoadBMP("armor_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);
	}
	glPopMatrix();
}

void drawTricepCover() {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
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
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
				glDeleteTextures(1, &texture);
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
			
			texture = LoadBMP("metal_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);
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
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glTranslatef(0.0f, 0.0f, 0.2f);
		gluCylinder(var,radius/7.0f,radius/8.0f,0.5f,6,stacks);
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
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
	texture = LoadBMP("metal_texture.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.15f, 0.1f);
		glRotatef(45.0f,0.0f,0.0f,1.0f);
		gluCylinder(var, radius / 10.0f, 0.0f, 0.4f, 4, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.03f);
			glColor3f(0.0f, 0.0f, 0.0f);
			gluDisk(var, 0.0f, radius / 14.0f, 4 ,stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
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

void drawFootCover(GLUquadricObj *var) {
	glPushMatrix();
	{
		//draw front foot sole
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		
		texture = LoadBMP("armor_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();
		{
			glScalef(4.0f, 0.9f, 1.0f);
			glTranslatef(0.0f,-0.5f,0.0f);
			glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 14.0f, radius / 10.0f, 0.4f, 4, stacks);
			gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.4f);;
				gluDisk(var, 0.0f, radius / 10.0f, 4, stacks);
			}
			glPopMatrix();
			
			glTranslatef(0.0f, 0.0f, -0.31f);
			gluCylinder(var, radius / 18.0f, radius / 14.0f, 0.3f, 4, stacks);
			gluDisk(var, 0.0f, radius / 18.0f, 4, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.3f);;
				gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.15f, -0.78f, 0.0f);
			glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f,0.0f,1.0f,0.0f);
			gluCylinder(var, radius / 14.0f, radius / 14.0f, 0.30f, 3, stacks);
			gluDisk(var, 0.0f, radius / 14.0f, 3, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.30f);;
				gluDisk(var, 0.0f, radius / 14.0f, 3, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		//draw heel sole
		glPushMatrix();
		{
			glScalef(3.0f, -0.6f, 1.0f);
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 14.0f, radius / 10.0f, 0.4f, 4, stacks);
			gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.4f);;
				gluDisk(var, 0.0f, radius / 10.0f, 4, stacks);
			}
			glPopMatrix();

			glTranslatef(0.0f, 0.0f, -0.31f);
			gluCylinder(var, radius / 18.0f, radius / 14.0f, 0.3f, 4, stacks);
			gluDisk(var, 0.0f, radius / 18.0f, 4, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.3f);;
				gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw foot side
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.2f, 0.0f);
			glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
			glPushMatrix();
			{
				glTranslatef(0.3f, 0.0f, 0.0f);
				glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.2f, 4, stacks);
				gluDisk(var, 0.0f, radius / 10.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.2f);
					gluDisk(var, 0.0f, radius / 10.0f, 4, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.27f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
				gluCylinder(var, radius / 12.0f, radius / 18.0f, 0.25f, 4, stacks);
				gluDisk(var, 0.0f, radius / 12.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.25f);
					gluDisk(var, 0.0f, radius / 18.0f, 4, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw foot top
		glPushMatrix();
		{
			glTranslatef(0.0f,0.0f,0.0f);
			glPushMatrix();
			{
				glScalef(1.5f, 0.7f, 1.0f);
				glTranslatef(0.0f, -0.6f, 0.1f);
				glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(var, radius / 8.0f, radius / 4.0f, 0.4f, 4, stacks);
				gluDisk(var, 0.0f, radius / 8.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);;
					gluDisk(var, 0.0f, radius / 4.0f, 4, stacks);
				}
				glPopMatrix();

				glTranslatef(0.0f, 0.0f, -0.31f);
				gluCylinder(var, radius / 11.0f, radius / 8.0f, 0.3f, 4, stacks);
				gluDisk(var, 0.0f, radius / 11.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.3f);;
					gluDisk(var, 0.0f, radius / 8.0f, 4, stacks);
				}
				glPopMatrix();
				glDeleteTextures(1, &texture);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0.0f, -0.1f, 0.20f);
				glRotatef(-25.0f,1.0f,0.0f,0.0f);
				glPushMatrix();
				{
					glTranslatef(0.0f, -0.20f, 0.02f);
					glScalef(0.15f, 0.05f, 0.15f);
					drawCover();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.15f, -0.10f, 0.0f);
					glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(80.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.1f, 0.025f, 0.15f);
					drawCover();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(-0.15f, -0.10f, 0.0f);
					glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-80.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.1f, 0.025f, 0.15f);
					drawCover();
				}
				glPopMatrix();
			}
			glPopMatrix();	
			
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawLeftFoot(GLUquadricObj *var) {
	// draw front foot
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.2f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		boneLength = 0.6f;
		drawBone(var);
	}
	glPopMatrix();
	// draw heel
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.4f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		boneLength = 0.2f;
		drawBone(var);
	}
	glPopMatrix();
	// draw foot cover
	drawFootCover(var);
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
	// draw foot cover
	glPushMatrix();
	{
		glScalef(-1.0f, 1.0f, 1.0f);
		drawFootCover(var);
	}
	glPopMatrix();
	boneLength = 2.0f;
}

void drawUpperLegJointArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glTranslatef(0.15f,0.0f,0.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		//supporting pole
		gluCylinder(var, radius / 15.0f, radius / 15.0f, 0.6f, 6, stacks);
		gluDisk(var, 0.0f, radius / 15.0f, 6, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.6f);
			gluDisk(var, 0.0f, radius / 15.0f, 6, stacks);
		}
		glPopMatrix();
		
		// big side screw
		glPushMatrix(); {
			glTranslatef(0.0f, 0.0f, -0.1f);
			gluCylinder(var, radius / 7.0f, radius / 7.0f, 0.1f, 6, stacks);
			gluDisk(var, 0.0f, radius / 7.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(var, 0.0f, radius / 7.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		// inside scew
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
		glDeleteTextures(1, &texture);
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
			
			texture = LoadBMP("metal_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
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
			glDeleteTextures(1, &texture);
			
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
			
			texture = LoadBMP("armor_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.2f);
				gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.8f, 6, stacks);
			}
			glPopMatrix();
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
		glPushMatrix(); {
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
			
			texture = LoadBMP("metal_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
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
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
	}
	glPopMatrix();
	
}

void drawBackThighBone(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(-0.075f, -0.025f, -0.1f);
		glPushMatrix();
		{
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
			
			texture = LoadBMP("metal_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			glPushMatrix(); {
				gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.2f, 4, stacks);
				gluDisk(var, 0.0f, radius / 12.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.2f);
					gluDisk(var, 0.0f, radius / 12.0f, 4, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			//glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.2f);
				gluCylinder(var, radius / 17.0f, radius / 17.0f, 0.8f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.08f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 14.0f, radius / 14.0f, 0.16f, 3, stacks);
			gluDisk(var, 0.0f, radius / 14.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.16f);
				gluDisk(var, 0.0f, radius / 14.0f, 3, stacks);
			}
			glPopMatrix();
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawThighBoneConnection(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
		
		texture = LoadBMP("armor_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);
	}
	glPopMatrix();
}

void drawThighCover(GLUquadricObj *var) {
	glPushMatrix();
	{
		
		//draw outside cover
		glPushMatrix(); {
			glTranslatef(0.18f,-0.05f,0.0f);
			glRotatef(-85.0f,0.0f,0.0f,1.0f);
			glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.25f,0.025f,0.35f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.06f, 0.30f, 0.10f);
			glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.15f, 0.02f, 0.25f);
			drawCover();
		}
		glPopMatrix();
		
		glPushMatrix(); {
			glTranslatef(0.22f, -0.08f, 0.8f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.25f, 0.04f, 0.65f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.12f, 0.30f, 0.90f);
			glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.15f, 0.02f, 0.55f);
			drawCover();
		}
		glPopMatrix();

		//draw inside cover
		glPushMatrix(); {
			glTranslatef(-0.32f, 0.32f, 1.05f);
			glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-110.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.13f, 0.025f, 0.45f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.40f, 0.0f, 1.1f);
			glRotatef(-85.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.15f, 0.025f, 0.45f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.32f, 0.10f, 0.5f);
			glRotatef(-105.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.38f, 0.025f, 0.12f);
			drawCover();
		}
		glPopMatrix();


		//draw back cover
		glPushMatrix(); {
			glTranslatef(-0.1f, -0.25f, 0.9f);
			//glRotatef(-110.0f, 0.0f, 0.0f, 1.0f);
			//glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.13f, 0.025f, 0.15f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.1f, -0.35f, 1.0f);
			glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.10f, 0.025f, 0.30f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.10f, -0.35f, 0.8f);
			glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.10f, 0.025f, 0.55f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.25f, -0.30f, 0.9f);
			glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
			//glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.15f, 0.025f, 0.40f);
			drawCover();
		}
		glPopMatrix();
		//draw front cover
		glPushMatrix(); {
			glTranslatef(-0.10f, 0.40f, 0.9f);
			glRotatef(-1.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.12f, 0.025f, 0.45f);
			drawCover();
		}
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(0.0f, 0.40f, 1.6f);
			glRotatef(-1.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.12f, 0.05f, 0.25f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0f, 0.45f, 1.6f);
			glRotatef(-90.0f,0.0f,1.0f,0.0f);
			glRotatef(-1.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.10f, 0.02f, 0.18f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.20f, 0.20f, 1.5f);
			glRotatef(-80.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.25f, 0.02f, 0.08f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.25f, 0.40f, 1.6f);
			glRotatef(-130.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.15f, 0.02f, 0.08f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.35f, 0.20f, 1.7f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.15f, 0.02f, 0.08f);
			drawCover();
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
			drawBackThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawBackThighBone(var);
			drawThighBoneConnection(var);
			glPushMatrix();
			{
				glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
				
				texture = LoadBMP("metal_texture.bmp");
				glBindTexture(GL_TEXTURE_2D, texture);
				glTranslatef(0.05f, 0.1f, 1.05f);
				glScalef(0.2f, 0.1f, 0.1f);
				drawFilledCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
		
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
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
		
		//draw Thigh Cover
		drawThighCover(var);
		
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

void drawLowerLegJointCover() {
	glPushMatrix();
	{
		glRotatef(180.0f,1.0f,0.0f,0.0f);
		//first
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.20f, 0.02f);
			glScalef(0.1f, 0.05f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.10f, -0.05f, 0.0f);
			glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(80.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.1f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.10f, -0.05f, 0.0f);
			glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-80.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.1f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		//second
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.20f, 0.12f);
			glRotatef(30.0f,1.0f,0.0f,0.0f);
			glScalef(0.1f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.10f, -0.05f, 0.1f);
			glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.025f, 0.04f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.10f, -0.05f, 0.1f);
			glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.025f, 0.04f);
			drawCover();
		}
		glPopMatrix();
		//third
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.20f, 0.22f);
			glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.1f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.15f, -0.10f, 0.16f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.025f, 0.04f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.15f, -0.10f, 0.16f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.025f, 0.04f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
}

void drawLowerLegJointArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);
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
	//draw lower leg joint cover
	glPushMatrix();
	{
		drawLowerLegJointCover();
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
}

void drawLowerLegCover(GLUquadricObj *var) {
	glPushMatrix();
	{
		//draw upper knee cap
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.3f, 0.3f);
			glRotatef(15.0f,1.0f,0.0f,0.0f);
			glScalef(0.15f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.20f, 0.25f, 0.28f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.08f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.25f, 0.05f, 0.25f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(85.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.17f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(0.20f, 0.25f, 0.28f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.08f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.0f, 0.22f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.20f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();

		//draw lower knee cap	
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.25f, 0.43f);
			//glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.15f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.25f, 0.05f, 0.37f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.25f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.20f, 0.25f, 0.43f);
			glRotatef(-5.0f,1.0f,0.0f,0.0f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.08f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.28f, 0.0f, 0.37f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(100.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.20f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		
		//draw shin cover
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.2f, 0.70f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.15f, 0.025f, 0.10f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.25f, 0.0f, 0.65f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.25f, 0.025f, 0.1f);
			drawCover();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(0.25f, -0.05f, 0.675f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.25f, 0.025f, 0.15f);
			drawCover();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.12f, 0.97f);
			glScalef(0.15f, 0.025f, 0.22f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.2f, 0.0f, 0.97f);
			glRotatef(115.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.025f, 0.22f);
			drawCover();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			glTranslatef(-0.2f, 0.0f, 0.97f);
			glRotatef(65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.15f, 0.025f, 0.22f);
			drawCover();
		}
		glPopMatrix();

		//draw calf cover
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.65f, 0.67f);
			glScalef(0.075f, 0.025f, 0.12f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.10f, -0.60f, 0.68f);
			glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.075f, 0.025f, 0.15f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.10f, -0.60f, 0.68f);
			glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.075f, 0.025f, 0.15f);
			drawCover();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0f, -0.50f, 1.40f);
			glScalef(0.1f, 0.05f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.15f, -0.35f, 1.15f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(80.0f,0.0f,0.0f,1.0f);
			glScalef(0.3f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.15f, -0.35f, 1.15f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-80.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.3f, 0.025f, 0.05f);
			drawCover();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.15f, -0.35f, 1.25f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(80.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.10f, 0.025f, 0.10f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.15f, -0.35f, 1.25f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-80.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.10f, 0.025f, 0.10f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawLowerLegArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);
		//draw shin details
		glPushMatrix();
		{
			glTranslatef(0.2f, 0.15f, 0.4f);
			glRotatef(15.0f,1.0f,0.0f,0.0f);
			drawBackThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawBackThighBone(var);
			
			texture = LoadBMP("metal_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glPushMatrix();
			{
				glTranslatef(0.17f, 0.0f, 0.9f);
				glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.40f, 6, stacks);
				gluDisk(var, 0.0f, radius / 10.0f, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.40f);
					gluDisk(var, 0.0f, radius / 10.0f, 6, stacks);
				}
				glPopMatrix();
				glDeleteTextures(1, &texture);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.2f, 0.0f, 0.30f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			drawBackThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawBackThighBone(var);
		}
		glPopMatrix();
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glDeleteTextures(1, &texture);

		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		
		texture = LoadBMP("metal_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
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
		//draw lower leg ventilation holes
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
			glDeleteTextures(1, &texture);
		}
		glPopMatrix();
		//draw lower leg cover
		drawLowerLegCover(var);
	}
	glPopMatrix();
}

void drawLeftLeg(GLUquadricObj *var) {
	glPushMatrix();
	{
		boneLength = 1.2f;
		drawBone(var);
		glPushMatrix(); {
			glScalef(0.95f, 1.0f, 0.70f);
			drawUpperLegArmor(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.2f); //Switch origin to prefered rotate point.
			glRotatef(leftLegAngle2, leftLegAxis[1][0], leftLegAxis[1][1], leftLegAxis[1][2]); //Rotating joint.
			drawHingeJoint(var);
			glPushMatrix(); {
				glScalef(0.8f, 1.0f, 0.70f);
				drawLowerLegJointArmor(var);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
				//glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				//glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 2.2f;
				drawBone(var);
				glPushMatrix(); {
					glTranslatef(0.0f,0.0f,-0.3f);
					glScalef(0.85f, 0.8f, 1.3f);
					drawLowerLegArmor(var);
				}
				glPopMatrix();
				
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 2.2f);
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
		boneLength = 1.2f;
		drawBone(var);
		glPushMatrix(); {
			glScalef(-1.0f, 1.0f, 1.0f);
			glPushMatrix(); {
				glScalef(0.95f, 1.0f, 0.70f);
				drawUpperLegArmor(var);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.2f); //Switch origin to prefered rotate point.
			glRotatef(rightLegAngle2, rightLegAxis[1][0], rightLegAxis[1][1], rightLegAxis[1][2]); //Rotating joint.
			drawHingeJoint(var);
			glPushMatrix(); {
				glScalef(-1.0f, 1.0f, 1.0f);
				glPushMatrix(); {
					glScalef(0.8f, 1.0f, 0.70f);
					drawLowerLegJointArmor(var);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
				//glTranslatef(-2.0f, 1.0f, 0.0f); //Switch origin back to previous point.
				//glTranslatef(4.0f, 0.0f, 0.0f); //Move to desired draw location.
				boneLength = 2.2f;
				drawBone(var);
				glPushMatrix(); {
					glScalef(-1.0f, 1.0f, 1.0f);
					glPushMatrix(); {
						glTranslatef(0.0f, 0.0f, -0.3f);
						glScalef(0.85f, 0.8f, 1.3f);
						drawLowerLegArmor(var);
					}
					glPopMatrix();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 2.2f);
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


void drawHead(GLUquadricObj *var) {
	glPushMatrix();
	{
		// draw eyes
		glPushMatrix();
		{
			glColor3f(0.8f, 0.7f, 0.0f);
			texture = LoadBMP("eyes_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.2f, 1.4f, 1.0f);
			gluCylinder(var, radius / 7.0f, radius / 9.0f, 0.15f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		//draw helmet top
		glPushMatrix();
		{
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
			texture = LoadBMP("armor_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glTranslatef(0.0f, 0.07f, 0.10f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.2f, 1.4f, 1.0f);
			gluSphere(var, radius / 9.0f, slices, stacks);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);	
		//draw helmet cover
		glPushMatrix();
		{
			glTranslatef(0.0f,0.14f,-0.225f);
			glRotatef(-30.0f,1.0f,0.0f,0.0f);
			glPushMatrix();
			{
				glTranslatef(0.08f, -0.10f, 0.26f);
				glRotatef(-50.0f,0.0f,0.0f,1.0f);
				glScalef(0.12f, 0.01f, 0.015f);
				drawCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.08f, -0.10f, 0.26f);
				glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.12f, 0.01f, 0.015f);
				drawCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		//draw chin cover
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.15f, -0.12f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(45.0f,0.0f,1.0f,0.0f);
			glScalef(0.05f,0.01f,0.05f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.16f, -0.16f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.07f, 0.01f, 0.04f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.13f, 0.10f, -0.06f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.12f, 0.02f, 0.06f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(0.13f, 0.10f, -0.06f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.12f, 0.02f, 0.06f);
			drawCover();
		}
		glPopMatrix();
		//draw back cover
		glPushMatrix();
		{
			glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -0.12f, 0.06f);
			glScalef(0.15f, 0.07f, 0.10f);
			drawCover();
		}
		glPopMatrix();

		// draw ear cover
		glPushMatrix();
		{
			glTranslatef(0.17f, 0.05f, 0.05f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.06f, 0.03f, 0.08f);
			drawCover();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(0.17f, 0.05f, 0.05f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.06f, 0.03f, 0.08f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
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
	glPushMatrix();
	{
		glTranslatef(xPosition, yPosition, zPosition);
		if (scene1) {
			glTranslatef(0.0f, 0.0f, 0.7f);
			glScalef(0.7f, 0.7f, 0.7f);
		}
		drawSpine(var);


		glPushMatrix();
		{
			glTranslatef(0.0f, -0.2f, 1.9f); //Switch origin to prefered rotate point.
			glRotatef(headAngle1, 0.0f, 0.0f, 0.1f); //Rotating joint.
			drawBallJoint(var);
			drawHead(var);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(1.0f, 0.0f, 1.85f); //Switch origin to prefered rotate point.
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
			glTranslatef(xPosition, yPosition, zPosition);
			if (scene1) {
				glTranslatef(0.0f, 0.0f, 0.7f);
				glScalef(0.7f, 0.7f, 0.7f);
			}
			glPushMatrix();
			{
				glTranslatef(-1.0f, 0.0f, 1.85f); //Switch origin to prefered rotate point.
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
				glTranslatef(xPosition, yPosition, zPosition);
				if (scene1) {
					glTranslatef(0.0f, 0.0f, 0.7f);
					glScalef(0.7f, 0.7f, 0.7f);
				}
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
				glTranslatef(xPosition, yPosition, zPosition);
				if (scene1) {
					glTranslatef(0.0f, 0.0f, 0.7f);
					glScalef(0.7f, 0.7f, 0.7f);
				}
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
		glPopMatrix();
		
	}
	glPopMatrix();
}

void drawCylinderandCone(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.0f, 1.0f);
		glColor3f((float)148 / 255.0f, (float)132 / 255.0f, (float)119 / 255.0f);
		gluCylinder(var, baseRadius, 0.0f, 0.3f, slices, stacks);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.0f, -1.0f);
		//glColor3f(0.7f, 0.5f, 0.0f);
		glColor3f((float)192 / 255.0f, (float)175 / 255.0f, (float)155 / 255.0f);
		gluCylinder(var, baseRadius*0.9, baseRadius*0.9, 2.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawFilledCone(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.0f, 1.0f);
		glColor3f((float)188 / 255.0f, (float)187 / 255.0f, (float)169 / 255.0f);
		texture = LoadBMP("roof.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		gluCylinder(var, baseRadius*3.0f, 0.05f, 0.6f, 4, 1);
		glDeleteTextures(1, &texture);
		glPushMatrix(); {
			glColor3f((float)188 / 255.0f, (float)174 / 255.0f, (float)129 / 255.0f);
			glTranslatef(0.0f, 0.0f, 0.2f);
			gluCylinder(var, baseRadius*1.0f, 0, 0.8f, 4, 1);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawTower(GLUquadricObj *var) {
	texture = LoadBMP("small_tower.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	{
		glTranslatef(-2.0, 0.0, 0.0);
		drawCylinderandCone(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1.5, 0.0, 0.0);
		drawCylinderandCone(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1.5, -0.5, 0.0);
		drawCylinderandCone(var);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-2.0, -0.5, 0.0);
		drawCylinderandCone(var);
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glPushMatrix();
	{
		glColor3f((float)206 / 255.0f, (float)190 / 255.0f, (float)167 / 255.0f);
		texture = LoadBMP("tower_front.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		glTranslatef(-1.7f, -0.3f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.25f, 0.25f, 0.8f);
			glTranslatef(0.0f, 0.0f, 0.3f);
			drawFilledCube();
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		glPushMatrix();
		{
			glTranslatef(-0.05f, 0.05f, 0.0f);
			glRotatef(45, 0, 0, 1);
			drawFilledCone(var);
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void drawSideFence() {
	glPushMatrix();
	{
		glTranslatef(5.0f, 0.19f, -0.85f);
		glScalef(3.5f, 0.005f, 0.03f);
		glColor3f((float)24 / 255.0f, (float)120 / 255.0f, (float)207 / 255.0f);
		//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		//drawFilledCube();
	}
	glPopMatrix();
}

void drawSuspendLine() {
	glPushMatrix();
	{
		glTranslatef(3.4f, -0.9f, 0.0f);
		glScalef(0.005f, 1.0f, 0.005f);
		for (int i = 4; i > 0; i--) {
			glPushMatrix(); {
				glScalef(1.0f, i / 8.0f, 1.0f);
				glTranslatef(-i*50.0f, 1.0f, 0.0f);
				////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
				drawFilledCube();
			}
			glPopMatrix();

		}
	}
	glPopMatrix();
}

void drawSuspension() {
	texture = LoadBMP("base_bridge_texture.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f((float)29 / 255.0f, (float)187 / 255.0f, (float)212 / 255.0f);
	////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
	glPushMatrix(); {
		glScalef(0.5f, 0.5f, 1.0f);
		glTranslatef(-10.0f, -1.9f, 0.0f);
		//glRotatef(180.0f, 1, 0, 0);
		//glRotatef(180.0f,0 ,0, 1);
		glLineWidth(5.0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 100; i++)
			glEvalCoord1f((GLfloat)i / 100.0);
		glEnd();

		glPushMatrix();
		{
			glScalef(1.05f, 0.9f, 1.0f);
			glTranslatef(-0.35f, 0.40f, 0.0f);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= 100; i++)
				glEvalCoord1f((GLfloat)i / 100.0);
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);

	drawSuspendLine();
	glPushMatrix();
	{
		glScalef(1.0f, 0.7f, 1.0f);
		//glRotatef(180.0f, 0, 1, 0);
		glTranslatef(-7.5f, -0.3f, 0.0f);
		drawSuspendLine();
	}
	glPopMatrix();

}

void drawBase(GLUquadricObj *var) {

	glPushMatrix();
	{
		glTranslatef(-1.0f, -1.0f, -0.9f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);

		glPushMatrix();
		{
			glTranslatef(0.08f, 0.8f, 0.0f);
			glScalef(0.92f, 0.2f, 0.02f);
			texture = LoadBMP("road_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glColor3f(0.0f, 0.0f, 0.0f);
			////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
			drawFilledCube();
			glDeleteTextures(1, &texture);
			glPushMatrix();
			{
				texture = LoadBMP("side_fence_texture.bmp");
				glBindTexture(GL_TEXTURE_2D, texture);
				glTranslatef(-0.7f, 0.8f, 48.0f);
				glScalef(0.2f, 1.0f, 55.0f);
				drawSideFence();
				glPushMatrix();
				{
					glTranslatef(0.0f, -1.98f, 0.0f);
					drawSideFence();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glDeleteTextures(1, &texture);
			glPushMatrix();
			{
				texture = LoadBMP("base_bridge_texture.bmp");
				glBindTexture(GL_TEXTURE_2D, texture);
				glTranslatef(0.0f, 0.0f, -1.6f);
				glScalef(1.0f, 1.0f, 0.2f);
				glColor3f((float)215 / 255.0f, (float)215 / 255.0f, (float)215 / 255.0f);
				////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
				drawFilledCube();
			}
			glPopMatrix();

		}
		glPopMatrix();
		glPushMatrix(); {
			glColor3f((float)29 / 255.0f, (float)187 / 255.0f, (float)212 / 255.0f);
			////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
			glTranslatef(-0.45f, 1.0f, -0.23f);
			glRotatef(82, 0, 1, 0);
			gluCylinder(var, baseRadius*0.2, baseRadius*0.2, 1.45, slices, stacks);
			glPushMatrix(); {
				glTranslatef(0.0f, -0.38f, 0.0f);
				gluCylinder(var, baseRadius*0.2, baseRadius*0.2, 1.45, slices, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);

	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1.7f, -0.2f, -1.5f);
		glScalef(0.5f, 0.5f, 0.45f);
		glColor3f((float)168 / 255.0f, (float)150 / 255.0f, (float)133 / 255.0f);
		texture = LoadBMP("base.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		gluCylinder(var, baseRadius * 14, baseRadius * 14, 1.5, slices, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 1.5f);
			glColor3f((float)168 / 255.0f, (float)150 / 255.0f, (float)133 / 255.0f);
			//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
			gluDisk(var, 0.0f, 1.4f, slices, 20);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
		//sea wave effect
		glPushMatrix();
		{
			glRotatef(seaWaveMovement, 0, 0, 1);
			if (weather)
				glColor3f((float)131 / 255.0f, (float)101 / 255.0f, (float)49 / 255.0f);
			else
				glColor3f((float)33 / 255.0f, (float)91 / 255.0f, (float)95 / 255.0f);
			texture = LoadBMP("sea_texture.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
			//glColor3f((float)128 / 255.0f, (float)128 / 255.0f, (float)128 / 255.0f);
			gluDisk(var, 0.0f, 15.0f, slices, 20);
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
	}
	glPopMatrix();

}



void drawRoad(GLUquadricObj *var) {
	glPushMatrix();
	{
		texture = LoadBMP("road_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glTranslatef(-5.5f, -0.2f, -0.90f);
		glScalef(4.0f, 0.2f, 0.02f);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawFilledCube();

		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -2.0f);
			glScalef(1.0f, 1.0f, 0.2f);
			glColor3f((float)215 / 255.0f, (float)215 / 255.0f, (float)215 / 255.0f);
			drawFilledCube();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glPushMatrix();
	{
		texture = LoadBMP("sand_stone_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glColor3f((float)206 / 255.0f, (float)190 / 255.0f, (float)167 / 255.0f);
		glScalef(0.1f, 0.2f, 0.1f);
		glTranslatef(52.0f, -1.0f, -1.2f);
		drawFilledCube();
		glDeleteTextures(1, &texture);
		glPushMatrix();
		{
			glColor3f((float)168 / 255.0f, (float)150 / 255.0f, (float)133 / 255.0f);
			texture = LoadBMP("small_tower.bmp");
			glBindTexture(GL_TEXTURE_2D, texture);
			glTranslatef(0.0f, 0.7f, -8.0f);
			gluCylinder(var, baseRadius * 3, baseRadius * 3, 8.0, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, -1.4f, 0.0f);
				gluCylinder(var, baseRadius * 3, baseRadius * 3, 8.0, slices, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glDeleteTextures(1, &texture);
	}
	glPopMatrix();
	glPushMatrix();
	{
		texture = LoadBMP("side_fence_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		glTranslatef(0.0f, -0.20f, 0.0f);
		drawSideFence();
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.39f, 0.0f);
			drawSideFence();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);


}

void drawSmallFence() {
	glPushMatrix();
	{
		glRotatef(45, 0, 1, 0);
		glScalef(0.005f, 0.005f, 0.05f);
		glColor3f((float)239 / 255.0f, (float)232 / 255.0f, (float)213 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glRotatef(-45, 0, 1, 0);
		glScalef(0.005f, 0.005f, 0.05f);
		glColor3f((float)239 / 255.0f, (float)232 / 255.0f, (float)213 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();
}

void drawFence() {

	texture = LoadBMP("bridge_texture.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	{
		glTranslatef(0.0f, 1.0f, 0.5f);
		glScalef(1.0f, 0.55f, 1.5f);
		glColor3f((float)210 / 255.0f, (float)184 / 255.0f, (float)161 / 255.0f);
		//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.0f, 1.0f, 6.2f);
		glScalef(1.0f, 0.05f, 0.4f);
		glColor3f((float)189 / 255.0f, (float)251 / 255.0f, (float)255 / 255.0f);
		//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		drawFilledCube();
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
}

void drawBridge() {
	glPushMatrix();
	{

		glTranslatef(-0.15f, -0.10f, 0.8f);
		glScalef(1.7f, 0.05f, 0.02f);
		texture = LoadBMP("brick_road_texture.bmp");
		glBindTexture(GL_TEXTURE_2D, texture);
		glColor3f((float)108 / 255.0f, (float)86 / 255.0f, (float)63 / 255.0f);
		drawFilledCube();
		glDeleteTextures(1, &texture);
		drawFence();
		glPushMatrix();
		{
			glTranslatef(0.0f, -2.0f, 0.0f);
			drawFence();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix(); {
		glTranslatef(-1.5f, -0.05f, 0.88f);
		for (int i = 0; i < 36; i++) {
			glPushMatrix();
			{
				glTranslatef(i / 12.0, 0.0f, 0.0f);
				drawSmallFence();
			}
			glPopMatrix();
		}

		glPushMatrix(); {
			glTranslatef(0.0f, -0.10f, 0.0f);
			for (int i = 0; i < 36; i++) {
				glPushMatrix();
				{
					glTranslatef(i / 12.0, 0.0f, 0.0f);
					drawSmallFence();
				}
				glPopMatrix();
			}
		}glPopMatrix();
	}
	glPopMatrix();


}


void drawSea(GLUquadricObj *var) {
	texture = LoadBMP("sea_texture.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix(); {
		if (weather)
			glColor3f((float)108 / 255.0f, (float)75 / 255.0f, (float)4 / 255.0f);
		else
			glColor3f((float)44 / 255.0f, (float)120 / 255.0f, (float)94 / 255.0f);
		//glColor3f((float)82 / 255, (float)109 / 255, (float)109 / 255);	
		glTranslatef(0.0f, 0.0f, -1.5f);
		gluDisk(var, 0.0f, 10.0f, slices, 20);
	}
	glPopMatrix();
	glDeleteTextures(1, &texture);
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
	

	if (scene1) {
		glBindTexture(GL_TEXTURE_2D, texture);
		drawSea(var);
		drawTower(var);
		drawBridge();
		drawBase(var);

		drawRoad(var);
		glPushMatrix(); {
			glRotatef(90.0f, 1, 0, 0);
			drawSuspension();
			glPushMatrix(); {
				glTranslatef(0.0f, 0.0f, 0.4f);
				drawSuspension();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			//glTranslatef(-0.7f,-0.4f, 0.0f);
			//glRotatef(180.0f, 0, 0, 1);
			glScalef(-1.0f, 1.0f, 1.0f);
			drawTower(var);
			glPushMatrix(); {
				glTranslatef(0.0f, -0.3f, 0.0f);
				drawBridge();
			}
			glPopMatrix();
			drawBase(var);
			drawRoad(var);
			glPushMatrix(); {
				glRotatef(90.0f, 1, 0, 0);
				drawSuspension();
				glPushMatrix(); {
					glTranslatef(0.0f, 0.0f, 0.4f);
					drawSuspension();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	

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

		if (seaWaveMovement < 360)
			seaWaveMovement += 0.000005f;
		else
			seaWaveMovement = 0.0f;

		display();

		SwapBuffers(hdc);
	}
	glDisable(GL_LIGHTING);
	//glDisable(GL_STENCIL_TEST);
	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}