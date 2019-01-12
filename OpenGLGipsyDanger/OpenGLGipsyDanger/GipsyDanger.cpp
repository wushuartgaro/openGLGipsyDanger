#include <Windows.h>
#include <Windowsx.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

// action key functions declaration
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
void pKeyAction();

void restoreAngles();

GLuint LoadBMP(char* fileName);

// Gipsy Danger drawing parts functions declaration
void drawSwordSidePart(GLUquadricObj *var);
void drawSwordPart(GLUquadricObj *var);
void drawSword(GLUquadricObj *var);
void drawPlasmaCannon(GLUquadricObj *var);
void drawFloatHingeJointArmor(GLUquadricObj *var);
void drawHingeJointArmor(GLUquadricObj *var);
void drawChestArmor(GLUquadricObj *var);
void drawShoulderCover();
void drawBackBooster(GLUquadricObj *var);
void drawBackConnector(GLUquadricObj *var);
void drawBackVertebraeBone();
void drawBackVertebrae();
void drawBackArmor(GLUquadricObj *var);
void drawReactor(GLUquadricObj *var);
void drawChest(GLUquadricObj *var);
void drawWaistCover();
void drawFrontVertebraeBone();
void drawFrontArmor();
void drawHips(GLUquadricObj *var);
void drawSpine(GLUquadricObj *var);
void drawFingerArmor(GLUquadricObj *var);
void drawFinger(GLUquadricObj *var, float fingerAngle1, float fingerAngle2);
void drawHandArmor(GLUquadricObj *var);
void drawLeftHand(GLUquadricObj *var);
void drawRightHand(GLUquadricObj *var);
void drawUpperArmHinge(GLUquadricObj *var);
void drawDeltoidCover(); 
void drawBicepCover(GLUquadricObj *var);
void drawTricepCover();
void drawTricepDetails(GLUquadricObj *var);
void drawUpperArmArmor(GLUquadricObj *var);
void drawTripleCover();
void drawLowerArmCover();
void drawLowerArmArmor(GLUquadricObj *var);
void drawHandJointArmor(GLUquadricObj *var);
void drawLeftArm(GLUquadricObj *var);
void drawRightArm(GLUquadricObj *var);
void drawFootCover(GLUquadricObj *var);
void drawLeftFoot(GLUquadricObj *var);
void drawRightFoot(GLUquadricObj *var);
void drawUpperLegJointArmor(GLUquadricObj *var);
void drawBackThighBone(GLUquadricObj *var);
void drawThighBoneConnection(GLUquadricObj *var);
void drawThighCover(GLUquadricObj *var);
void drawThighArmor(GLUquadricObj *var);
void drawUpperLegArmor(GLUquadricObj *var);
void drawLowerLegJointCover();
void drawLowerLegJointArmor(GLUquadricObj *var);
void drawLowerLegCover(GLUquadricObj *var);
void drawLowerLegArmor(GLUquadricObj *var);
void drawLeftLeg(GLUquadricObj *var);
void drawRightLeg(GLUquadricObj *var);
void drawHead(GLUquadricObj *var);
void drawGipsyDanger(GLUquadricObj *var);


bool scene1 = false;

//draw curve line
GLfloat ctrlpoints[3][3] = {
	{ 6, 4, 0 },{ 4, -2, 0 },{ 0, 1.5, 0 }
};

GLfloat ctrlpoints2[3][3] = {
	{ 6, 4, 0 },{ 4, -2, 0 },{ 0, 1.5, 0 }
};

// mouse movement
float lastX = 0.0f, lastY = 0.0f;

float xRotated = 1.0f, yRotated = 1.0f, zRotated = -30.0f;


float x = 0.0f, y = 0.0f, z = 7.0f;

float radius = 1.0f;
float angle = 0.01f;
float baseRadius = 0.1f;
int slices = 20, stacks = 20;

float headAngle1 = 180.0f;

float fingersAngle = 150.0f;
float leftLegAngle1 = 180.0f, leftLegAngle2 = 180.0f, leftLegAngle3 = 180.0f;
float rightLegAngle1 = 180.0f, rightLegAngle2 = 180.0f, rightLegAngle3 = 180.0f;
float leftArmAngle1 = 180.0f, leftArmAngle2 = 180.0f, leftArmAngle3 = 180.0f;
float rightArmAngle1 = 180.0f, rightArmAngle2 = 180.0f, rightArmAngle3 = 180.0f;

float bodyJointAngle = 0.0f, upperBodyJointAngle = 0.0f, hipsJointAngle = 1.0f;

float leftLegAxis[3][3] = { { 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };
float rightLegAxis[3][3] = { { 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };

float movingDirection = 0.0f;
bool leftFrontMax = false, rightFrontMax = false, leftBackMax = false, rightBackMax = false;
bool firstWalk = true, leftFrontWalked = false, rightFrontWalked = false, leftBackWalked = false, rightBackWalked = true;

float reactorRotateAngle = 0.0f;
float cannonRotateAngle = 0.0f;

float xPosition = 0.0f, yPosition = 0.0f, zPosition = 0.05f;

float zoomLevel = -7.0f;
float seaWaveMovement = 1.0f;


float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
float mat_ambient_color[] = { 0.0f, 0.0f, 1.0f, 1.0f };
float mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

bool lightOn = 0;

bool ambientOn = 1;
bool diffuseOn = 1;
bool specularOn = 1;

bool weather = 0;


float boneLength = 2.0f;

bool textureOn = false;

//sword toggles
bool xKeyDown = false, zKeyDown = false;
bool swordOn = false, strengthenSword = false;;
bool leftToggle = true, rightToggle = true, swordToggle = false;

//sword animation
bool swordAnimation = false, swordAnimation2 = false;
float swordVariable1 = 0.0f, swordVariable2 = 0.0f, swordVariable3 = 0.0f, swordVariable4 = 0.0f, swordVariable6 = 0.0f, swordVariable7 = 0.0f;
float swordVariable8 = 0.0f;
int swordVariable5 = 0, swordVariable9 = 0;

//plasma cannon toggles
bool cKeyDown = false, vKeyDown = false;
bool cannonOn = false, shootCannon = false;
bool cannonToggle = false;


//plasma cannon animation
float ballXPosition = 0.0f, ballYPosition = 0.0f, ballZPosition = 0.15f;
float ballRotateAngle = 0.0f, ballSize = 0.0f;
bool shootToggle = false;


//walking toggles
bool wKeyDown = false;

//gliding toggles
bool eKeyDown = false;

//movement toggles
bool toggle1 = false, toggle2 = false, toggle3 = false, toggle4 = false, toggle5 = false;
bool armToggle = false, legToggle = false, fingerToggle = false;
bool leftKeyDown = false, rightKeyDown = false, upKeyDown = false, downKeyDown = false;

//movement actions
float upArmAngle1ForLeft = 0.0f, downArmAngle1ForLeft = 0.0f, rightArmAngle1ForLeft = 0.0f, leftArmAngle1ForLeft = 0.0f;
float upArmAngle2ForLeft = 0.0f, downArmAngle2ForLeft = 0.0f, rightArmAngle2ForLeft = 0.0f, leftArmAngle2ForLeft = 0.0f;
float upArmAngle3ForLeft = 0.0f, downArmAngle3ForLeft = 0.0f, rightArmAngle3ForLeft = 0.0f, leftArmAngle3ForLeft = 0.0f;
float upLegAngle1ForLeft = 0.0f, downLegAngle1ForLeft = 0.0f, rightLegAngle1ForLeft = 0.0f, leftLegAngle1ForLeft = 0.0f;
float upLegAngle2ForLeft = 0.0f, downLegAngle2ForLeft = 0.0f, rightLegAngle2ForLeft = 0.0f, leftLegAngle2ForLeft = 0.0f;
float upLegAngle3ForLeft = 0.0f, downLegAngle3ForLeft = 0.0f, rightLegAngle3ForLeft = 0.0f, leftLegAngle3ForLeft = 0.0f;
float upFingerAngle1ForLeft = 150.0f, downFingerAngle1ForLeft = 150.0f;
float upFingerAngle2ForLeft = 150.0f, downFingerAngle2ForLeft = 150.0f;
float upFingerAngle3ForLeft = 150.0f, downFingerAngle3ForLeft = 150.0f;
float upFingerAngle4ForLeft = 150.0f, downFingerAngle4ForLeft = 150.0f;
float upFingerAngle5ForLeft = 150.0f, downFingerAngle5ForLeft = 150.0f;
float upArmAngle1ForRight = 0.0f, downArmAngle1ForRight = 0.0f, rightArmAngle1ForRight = 0.0f, leftArmAngle1ForRight = 0.0f;
float upArmAngle2ForRight = 0.0f, downArmAngle2ForRight = 0.0f, rightArmAngle2ForRight = 0.0f, leftArmAngle2ForRight = 0.0f;
float upArmAngle3ForRight = 0.0f, downArmAngle3ForRight = 0.0f, rightArmAngle3ForRight = 0.0f, leftArmAngle3ForRight = 0.0f;
float upLegAngle1ForRight = 0.0f, downLegAngle1ForRight = 0.0f, rightLegAngle1ForRight = 0.0f, leftLegAngle1ForRight = 0.0f;
float upLegAngle2ForRight = 0.0f, downLegAngle2ForRight = 0.0f, rightLegAngle2ForRight = 0.0f, leftLegAngle2ForRight = 0.0f;
float upLegAngle3ForRight = 0.0f, downLegAngle3ForRight = 0.0f, rightLegAngle3ForRight = 0.0f, leftLegAngle3ForRight = 0.0f;
float upFingerAngle1ForRight = 150.0f, downFingerAngle1ForRight = 150.0f;
float upFingerAngle2ForRight = 150.0f, downFingerAngle2ForRight = 150.0f;
float upFingerAngle3ForRight = 150.0f, downFingerAngle3ForRight = 150.0f;
float upFingerAngle4ForRight = 150.0f, downFingerAngle4ForRight = 150.0f;
float upFingerAngle5ForRight = 150.0f, downFingerAngle5ForRight = 150.0f;
float leftHeadAngle = 0.0f, rightHeadAngle = 0.0f, leftBodyAngle = 0.0f, rightBodyAngle = 0.0f;

float tempFingerAngle = 150.0f;

//Gipsy Danger texture
GLuint armorTexture, metalTexture, backConnectorTexture, reactorOutringTexture, reactorTurn1Texture, eyesTexture;
GLuint redTexture, plasmaTexture, plasmaTexture2, plasmaTexture3, cannonTexture, boostFlame;
GLuint armorTexture1, armorTexture2, glossyMetal, glass, camourflage, flame, mechanical;

GLuint textureArray[6], textureArray2[3];

int tCount1 = 0, tCount2 = 0;

GLuint sunTexture, moonTexture, nightSea;

//London Tower Bridge texture
GLuint roof, smallTower, towerFront, baseBridgeTexture, sideFenceTexture, base, seaTexture, roadTexture;
GLuint sandStoneTexture, bridgeTexture, brickRoadTexture;

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
			zRotated += xPos - lastX;
			xRotated += yPos - lastY;
			lastX = xPos;
			lastY = yPos;
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		lastX = GET_X_LPARAM(lParam);
		lastY = GET_Y_LPARAM(lParam);
		break;
	case WM_LBUTTONUP:
		if (!textureOn)
			//textureOn = true;
			break;
	case WM_MOUSEWHEEL:
		zoomLevel += GET_WHEEL_DELTA_WPARAM(wParam) / 120.0f;
		break;
	case WM_KEYUP:
		switch (wParam) {
		case 'X':
			if (cannonOn)
				break;
			xKeyDown = false;
			swordAnimation = false;
			swordOn = !swordOn;
			break;
		case 'Z':
			zKeyDown = false;
			swordAnimation2 = false;
			strengthenSword = !strengthenSword;
			break;
		case 'V':
			vKeyDown = false;
			//swordAnimation2 = false;
			//strengthenSword = !strengthenSword;
			shootToggle = true;
			ballRotateAngle = -cannonRotateAngle;
			break;
		case 'Q':
			while (!leftFrontWalked)
				qKeyAction();
			while (!rightFrontWalked)
				qKeyAction();
			break;
		case 'E':
			eKeyDown = false;
			bodyJointAngle = 0.0f;
			upperBodyJointAngle = 0.0f;
			reactorRotateAngle /= 2;
			break;
		case VK_LEFT:
			//leftKeyDown = false;
			break;
		case VK_RIGHT:
			//rightKeyDown = false;
			break;
		case VK_UP:
			//upKeyDown = false;
			break;
		case VK_DOWN:
			//downKeyDown = false;
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			if (!leftKeyDown) {
				leftKeyDown = true;
			}
			else {
				leftKeyAction();
			}
			break;
		case VK_RIGHT:
			if (!rightKeyDown) {
				rightKeyDown = true;
			}
			else {
				rightKeyAction();
			}
			break;
		case VK_UP:
			if (!upKeyDown) {
				upKeyDown = true;
			}
			else {
				upKeyAction();
			}
			break;
		case VK_DOWN:
			if (!downKeyDown) {
				downKeyDown = true;
			}
			else {
				downKeyAction();
			}
			break;
		case VK_PRIOR:
			if (fingersAngle >= 60.0f)
				fingersAngle -= 2.0f;
			break;
		case VK_NEXT:
			if (fingersAngle <= 180.0f)
				fingersAngle += 2.0f;
			break;
		case 'I':
			zoomLevel += 1.0f;
			break;
		case 'O':
			zoomLevel -= 1.0f;
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
			if (!eKeyDown) {
				eKeyDown = true;
			}
			else {
				eKeyAction();
			}
			break;
		case 'Q':
			qKeyAction();
			break;

		case 'T':
			if (textureOn)
				glDisable(GL_TEXTURE_2D);
			else
				glEnable(GL_TEXTURE_2D);
			textureOn = !textureOn;
			break;
		case 'G':
			if (lightOn)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			lightOn = !lightOn;
			break;
		case 'Y':
			if (tCount1 < 5) {
				tCount1++;
			}
			else {
				tCount1 = 0;
			}
			break;
		case 'H':
			if (tCount2 < 2) {
				tCount2++;
			}
			else {
				tCount2 = 0;
			}
			break;
		case 'L':
			leftToggle = !leftToggle;
			break;
		case 'R':
			rightToggle = !rightToggle;
			break;
		case 'P':
			pKeyAction();
			break;
		case 'X':
			if (cannonOn)
				break;
			if (!xKeyDown) {
				xKeyDown = true;
			}
			else {
				if (!swordOn) {
					swordAnimation = true;
					//zoomLevel = 0.1f;
					if (swordVariable1 <= 0.05f)
						swordVariable1 += 0.01f;
					if (swordVariable2 <= 40.0f)
						swordVariable2 += 10.00f;
					if (swordVariable3 <= 0.08f)
						swordVariable3 += 0.01f;
					if (swordVariable4 <= 0.35f)
						swordVariable4 += 0.07f;
					if (swordVariable5 < 17)
						swordVariable5 += 1;
					if (swordVariable6 <= 2.00f)
						swordVariable6 += 0.10f;
					if (swordVariable7 < 2.70f)
						swordVariable7 += 0.16f;
				}
				else {
					swordAnimation = true;
					if (swordVariable1 >= 0.0f && swordVariable4 == 0.10f)
						swordVariable1 -= 0.01f;
					if (swordVariable2 >= 0.0f && swordVariable4 == 0.10f)
						swordVariable2 -= 10.00f;
					if (swordVariable3 >= 0.0f && swordVariable4 == 0.10f)
						swordVariable3 -= 0.01f;
					if (swordVariable4 >= 0.10f)
						swordVariable4 -= 0.07f;
					if (swordVariable5 >= 0)
						swordVariable5 -= 1;
					if (swordVariable6 >= 0.00f)
						swordVariable6 -= 0.10f;
					if (swordVariable7 > 0.00f)
						swordVariable7 -= 0.16f;
				}
			}
			break;
		case 'Z':
			if (!zKeyDown) {
				zKeyDown = true;
			}
			else {
				if (!strengthenSword) {
					swordAnimation2 = true;
					if (swordVariable8 <= 90.0f)
						swordVariable8 += 20.0f;
				}
				else {
					swordAnimation2 = true;
					if (swordVariable8 >= 0.0f)
						swordVariable8 -= 20.0f;
				}
			}
			break;
		case 'C':
			if (swordOn)
				break;
			cannonOn = !cannonOn;
			break;
		case 'V':
			if (!vKeyDown) {
				vKeyDown = true;
			}
			else {
				ballRotateAngle = -cannonRotateAngle*2.0f;
			}
			break;
		case 'B':
			armToggle = !armToggle;
			break;
		case 'N':
			legToggle = !legToggle;
			break;
		case 'M':
			fingerToggle = !fingerToggle;
			break;
		case 0x30:
			scene1 = !scene1;
			break;
		case 0x31:
			if (armToggle || legToggle || fingerToggle)
				toggle1 = !toggle1;
			else
				ambientOn = !ambientOn;
			break;
		case 0x32:
			if (armToggle || legToggle || fingerToggle)
				toggle2 = !toggle2;
			else
				diffuseOn = !diffuseOn;
			break;
		case 0x33:
			if (armToggle || legToggle || fingerToggle)
				toggle3 = !toggle3;
			else
				specularOn = !specularOn;
			break;
		case 0x34:
			if (armToggle || legToggle || fingerToggle)
				toggle4 = !toggle4;
			else {
				if (weather)
					glDisable(GL_LIGHT0);
				else
					glEnable(GL_LIGHT0);
				weather = !weather;
			}
			break;
		case 0x35:
			if (armToggle || legToggle || fingerToggle)
				toggle5 = !toggle5;
			break;
		case VK_SPACE:
			if (armToggle || legToggle || fingerToggle)
				restoreAngles();
			else {
				xRotated = 1.0f;
				yRotated = 1.0f;
				zRotated = -30.0f;
				zoomLevel = -7.0f;
				x = 0.0f;
				y = 0.0f;
				z = 7.0f;
				xPosition = 0.0f;
				if(scene1)
					yPosition = 2.0f;
				else
					yPosition = 0.0f;
				zPosition = 0.0f;
			}
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
	//glColor3f(1.0f, 1.0f, 1.0f);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return texture;
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


void restoreAngles() {
	upArmAngle1ForLeft = 0.0f;
	downArmAngle1ForLeft = 0.0f;
	rightArmAngle1ForLeft = 0.0f;
	leftArmAngle1ForLeft = 0.0f;
	upArmAngle2ForLeft = 0.0f;
	downArmAngle2ForLeft = 0.0f;
	rightArmAngle2ForLeft = 0.0f;
	leftArmAngle2ForLeft = 0.0f;
	upArmAngle3ForLeft = 0.0f;
	downArmAngle3ForLeft = 0.0f;
	rightArmAngle3ForLeft = 0.0f;
	leftArmAngle3ForLeft = 0.0f;
	upLegAngle1ForLeft = 0.0f;
	downLegAngle1ForLeft = 0.0f;
	rightLegAngle1ForLeft = 0.0f;
	leftLegAngle1ForLeft = 0.0f;
	upLegAngle2ForLeft = 0.0f;
	downLegAngle2ForLeft = 0.0f;
	rightLegAngle2ForLeft = 0.0f;
	leftLegAngle2ForLeft = 0.0f;
	upLegAngle3ForLeft = 0.0f;
	downLegAngle3ForLeft = 0.0f;
	rightLegAngle3ForLeft = 0.0f;
	leftLegAngle3ForLeft = 0.0f;
	upFingerAngle1ForLeft = 150.0f;
	downFingerAngle1ForLeft = 150.0f;
	upFingerAngle2ForLeft = 150.0f;
	downFingerAngle2ForLeft = 150.0f;
	upFingerAngle3ForLeft = 150.0f;
	downFingerAngle3ForLeft = 150.0f;
	upFingerAngle4ForLeft = 150.0f;;
	downFingerAngle4ForLeft = 150.0f;
	upFingerAngle5ForLeft = 150.0f;
	downFingerAngle5ForLeft = 150.0f;
	upArmAngle1ForRight = 0.0f;
	downArmAngle1ForRight = 0.0f;
	rightArmAngle1ForRight = 0.0f;
	leftArmAngle1ForRight = 0.0f;
	upArmAngle2ForRight = 0.0f;
	downArmAngle2ForRight = 0.0f;
	rightArmAngle2ForRight = 0.0f;
	leftArmAngle2ForRight = 0.0f;
	upArmAngle3ForRight = 0.0f;
	downArmAngle3ForRight = 0.0f;
	rightArmAngle3ForRight = 0.0f;
	leftArmAngle3ForRight = 0.0f;
	upLegAngle1ForRight = 0.0f;
	downLegAngle1ForRight = 0.0f;
	rightLegAngle1ForRight = 0.0f;
	leftLegAngle1ForRight = 0.0f;
	upLegAngle2ForRight = 0.0f;
	downLegAngle2ForRight = 0.0f;
	rightLegAngle2ForRight = 0.0f;
	leftLegAngle2ForRight = 0.0f;
	upLegAngle3ForRight = 0.0f;
	downLegAngle3ForRight = 0.0f;
	rightLegAngle3ForRight = 0.0f;
	leftLegAngle3ForRight = 0.0f;
	upFingerAngle1ForRight = 0.0f;
	downFingerAngle1ForRight = 150.0f;
	upFingerAngle2ForRight = 150.0f;
	downFingerAngle2ForRight = 150.0f;
	upFingerAngle3ForRight = 150.0f;
	downFingerAngle3ForRight = 150.0f;
	upFingerAngle4ForRight = 150.0f;
	downFingerAngle4ForRight = 150.0f;
	upFingerAngle5ForRight = 150.0f;
	downFingerAngle5ForRight = 150.0f;
	leftHeadAngle = 0.0f; 
	rightHeadAngle = 0.0f; 
	leftBodyAngle = 0.0f;
	rightBodyAngle = 0.0f;

	leftLegAngle1 = 180.0f;
	leftLegAngle2 = 180.0f;
	leftLegAngle3 = 180.0f;
	rightLegAngle1 = 180.0f;
	rightLegAngle2 = 180.0f;
	rightLegAngle3 = 180.0f;
	leftArmAngle1 = 180.0f;
	leftArmAngle2 = 180.0f;
	leftArmAngle3 = 180.0f;
	rightArmAngle1 = 180.0f;
	rightArmAngle2 = 180.0f;
	rightArmAngle3 = 180.0f;
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
	if (!textureOn) {
		glLineWidth(1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
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
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
	}
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
		gluCylinder(var, radius / 28, radius / 28, boneLength, 6, stacks);
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

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
		drawFilledCube();
		//glDeleteTextures(1, &armorTexture);
	}
	glPopMatrix();

}

void drawSwordSidePart(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.10f, 0.0f, 0.08f);
		if (swordAnimation2 && swordToggle) {
			glRotatef(-swordVariable8, 0.0f, 1.0f, 0.0f);
		}
		if (strengthenSword) {
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		}

		glScalef(0.07f, 0.025f, 0.03f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.10f, 0.0f, 0.08f);
		if (swordAnimation2 && swordToggle) {
			glRotatef(swordVariable8, 0.0f, 1.0f, 0.0f);
		}
		if (strengthenSword) {
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		}

		glScalef(0.07f, 0.025f, 0.03f);
		drawFilledCube();
	}
	glPopMatrix();
}

void drawSwordPart(GLUquadricObj *var) {
	glPushMatrix();
	{
		glScalef(0.08f, 0.005f, 0.05f);
		drawFilledCube();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.0f, 0.08f);
		glScalef(0.10f, 0.025f, 0.03f);
		drawFilledCube();
	}
	glPopMatrix();
	drawSwordSidePart(var);
}

void drawSword(GLUquadricObj *var) {
	glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);

	if (swordAnimation && swordToggle) {
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.0f, swordVariable4);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < swordVariable5; i++) {
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, i / 7.0f);
					drawSwordPart(var);
				}
				glPopMatrix();
			}
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.05f, swordVariable4*2);
			gluCylinder(var, radius / 50.0f, radius / 50.0f, swordVariable6, slices, stacks);
			glTranslatef(0.0f, -0.10f, 0.0f);
			gluCylinder(var, radius / 50.0f, radius / 50.0f, swordVariable6, slices, stacks);
			glTranslatef(0.0f, 0.05f, 0.0f);
			gluCylinder(var, radius / 50.0f, radius / 50.0f, swordVariable6, slices, stacks);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.0f, swordVariable7);
			glScalef(0.2f, 0.7f, 1.0f);
			gluCylinder(var, radius / 5.0f, 0.0f, 0.3f, 4, stacks);
		}
		glPopMatrix();
	}
	else {
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.0f, 0.35f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			//draw small sword parts
			for (int i = 0; i < 17; i++) {
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, i / 7.0f);
					drawSwordPart(var);
				}
				glPopMatrix();
			}
			if (swordAnimation2 && swordToggle) {
				for (int i = 0; i < 17; i++) {
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, i / 7.0f);
						drawSwordSidePart(var);
					}
					glPopMatrix();
				}
			}
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.05f, 0.7f);
			gluCylinder(var, radius / 50.0f, radius / 50.0f, 2.0f, slices, stacks);
			glTranslatef(0.0f, -0.10f, 0.0f);
			gluCylinder(var, radius / 50.0f, radius / 50.0f, 2.0f, slices, stacks);
			glTranslatef(0.0f, 0.05f, 0.0f);
			gluCylinder(var, radius / 50.0f, radius / 50.0f, 2.0f, slices, stacks);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.25f, 0.0f, 2.75f);
			glScalef(0.2f, 0.7f, 1.0f);
			gluCylinder(var, radius / 5.0f, 0.0f, 0.3f, 4, stacks);
		}
		glPopMatrix();
	}

}

void drawPlasmaElectricEffect() {
	if (ballZPosition <= 0.15f) {
		//draw plasma electic effect
		glPushMatrix(); {
			glTranslatef(1.0f, 0.0f, 0.0f);
			glRotatef(-100.0f, 0, 1, 0);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, plasmaTexture3);
			glLineWidth(5.0);
			glScalef(0.15f, 0.1f, 0.1f);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= 100; i++)
				glEvalCoord1f((GLfloat)i / 100.0);
			glEnd();
		}
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
	}
	
}


void drawPlasmaCannon(GLUquadricObj *var) {
	glPushMatrix(); {

		//draw cannon
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.25f);
			gluCylinder(var, radius / 4.8f, radius / 4.9f, 0.05f, 12, stacks);
			glTranslatef(0.0f, 0.0f, 0.05f);
			gluCylinder(var, radius / 5.0f, radius / 8.0f, 0.25f, slices, stacks);
			gluDisk(var, 0.0f, radius / 5.0f, slices , stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.25f);
				gluDisk(var, radius / 11.0f, radius / 8.0f, slices, stacks);
				glBindTexture(GL_TEXTURE_2D, plasmaTexture);
				glTranslatef(0.0f, 0.0f, 0.001f);
				gluDisk(var, radius/ 9.5f, radius / 8.5f, slices, stacks);
			}
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
			glTranslatef(0.0f, 0.0f, 0.20f);
			gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.10f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.10f);
				gluDisk(var, radius / 11.5f, radius / 10.0f, slices, stacks);
			}
			glPopMatrix();
			glTranslatef(0.0f, 0.0f, 0.02f);
			gluCylinder(var, radius / 11.5f, radius / 11.5f, 0.10f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.10f);
				glRotatef(-cannonRotateAngle, 0.0f, 0.0f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, plasmaTexture2);
				gluCylinder(var, radius / 16.0f, radius / 11.5f, 0.01f, slices, stacks);
				//gluDisk(var, radius / 16.0f, radius / 11.5f, slices, stacks);
			}
			glPopMatrix();
			glTranslatef(0.0f, 0.0f, 0.02f);
			glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
			gluCylinder(var, radius / 16.0f, radius / 16.0f, 0.10f, slices, stacks);
			glPushMatrix(); 
			{
				glTranslatef(0.0f, 0.0f, 0.10f);
				gluDisk(var, radius / 18.0f, radius / 16.0f, slices, stacks);
			}
			glPopMatrix();

		
			glPushMatrix();
			{
			glTranslatef(0.0f, 0.0f, 0.07f);
			glRotatef(cannonRotateAngle, 0.0f, 0.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, cannonTexture);
			gluCylinder(var, 0.015f, radius / 18.0f,  0.01f, slices, stacks);
			}
			glPopMatrix();
			
			
		}
		glPopMatrix();

		//draw transformed fingers
		glPushMatrix();
		{
			if (vKeyDown) {
				ballRotateAngle = cannonRotateAngle*2.0f;
				if(ballSize < 0.2f)
					ballSize += 0.0010f;
			}
			else {
				ballRotateAngle = -cannonRotateAngle;
			}
				
			glRotatef(ballRotateAngle, 0.0f, 0.0f, 1.0f);
			glPushMatrix();
			{
				glTranslatef(0.0f, -0.25f, 0.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
				drawPlasmaElectricEffect();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.2f, 0.10f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
				drawPlasmaElectricEffect();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.17f, 0.17f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
				drawPlasmaElectricEffect();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.2f, 0.10f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
				drawPlasmaElectricEffect();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.17f, 0.17f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
				drawPlasmaElectricEffect();
			}
			glPopMatrix();
		}
		glPopMatrix();
		

		//draw cannon ball 
		GLfloat light_position1[] = { (xPosition*0.05f)+ ballXPosition, ballYPosition, (-yPosition*0.025f)+ ballZPosition, 0.0 };

		GLfloat light_plasma[] = { 23 / 255.0f, 114 / 255.0f, 254 / 255.0f, 1.0 };

		glLightfv(GL_LIGHT1, GL_SPECULAR, light_plasma);

		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

		glPushMatrix();
		{
			glTranslatef(light_position1[0], light_position1[1], light_position1[2]);
			glRotatef(-cannonRotateAngle * 5, 1.0f, 1.0f, 1.0f);
			glColor3f(255 / 255.0f, 255 / 255.0f, 255 / 255.0f);
			glBindTexture(GL_TEXTURE_2D, plasmaTexture3);
			gluSphere(var, ballSize, slices, stacks);
		}
		glPopMatrix();
		/*
		glPushMatrix();
		{
		glTranslatef(0.0f, 0.0f, 0.15f);
		glRotatef(-cannonRotateAngle * 5, 1.0f, 1.0f, 1.0f);
		glColor3f(255 / 255.0f, 255 / 255.0f, 255 / 255.0f);
		glBindTexture(GL_TEXTURE_2D, plasmaTexture3);
		gluSphere(var, radius / 25.0f, slices, stacks);
		}
		glPopMatrix();
		*/
	}
	glPopMatrix();
}

void drawFloatHingeJointArmor(GLUquadricObj *var) {

	glPushMatrix(); {
		glTranslatef(-0.17f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
		//glDeleteTextures(1, &metalTexture);
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
		//glDeleteTextures(1, &metalTexture);
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

	glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
	glPushMatrix(); {
		glTranslatef(0.0f, 0.0f, 2.02f);
		glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.5f, 1.0f);
		gluCylinder(var, radius / 4.0f, radius / 4.5f, 0.08f, slices, stacks);
	}
	glPopMatrix();
	//glDeleteTextures(1, &armorTexture);
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

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
		gluCylinder(var, radius / 8.0f, radius / 6.0f, 0.5f, 7, stacks * 2);
		//glDeleteTextures(1, &armorTexture);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			gluDisk(var, 0.0f, radius / 8.0f, 7, 20);
		}
		glPopMatrix();
		//glDeleteTextures(1, &metalTexture);
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			gluCylinder(var, radius / 6.5f, radius / 5.8f, 0.45f, 7, stacks * 2);
		}
		glPopMatrix();
		//glDeleteTextures(1, &armorTexture);
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

		if (eKeyDown) {
			glPushMatrix(); {
				glTranslatef(0.0f, 0.0f, -0.75f);
				glBindTexture(GL_TEXTURE_2D, boostFlame);
				gluCylinder(var, 0.0f, radius / 7.5f, 0.75f, slices, stacks * 2);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawBackConnector(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(-0.3f, 0.7f, 1.3f);
		glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		glScalef(0.5f, 1.5f, 1.0f);
		gluCylinder(var, radius / 6.0f, radius / 4.5f, 0.3f, 10, stacks * 5);
		//glDeleteTextures(1, &metalTexture);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, backConnectorTexture);
			glColor3f(119 / 255.0f, 99 / 255.0f, 94 / 255.0f);
			glTranslatef(0.0f, 0.0f, 0.05f);
			gluDisk(var, 0.0f, radius / 6.0f, 10, 20);
			//glDeleteTextures(1, &backConnectorTexture);
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void drawBackVertebraeBone() {
	glPushMatrix(); {
		glScalef(0.08f, 0.01f, 0.1f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
	//glDeleteTextures(1, &metalTexture);
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
			glScalef(1.0f - (i / 90.0f), 1.0f, 1.0f);
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
		glRotatef(-67.0f, 1.0f, 0.0f, 0.0f);
		glPushMatrix(); {
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);

			glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
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

		glPushMatrix(); {

			glBindTexture(GL_TEXTURE_2D, reactorOutringTexture);
			gluCylinder(var, radius / 5, radius / 4, 0.02f, slices, stacks);
		}
		glPopMatrix();

		GLfloat light_position2[] = { 0.0f,0.0f, 0.0f, 0.0 };

		GLfloat light_reactor[] = { 239 / 255.0f, 150 / 255.0f, 4 / 255.0f, 1.0 };

		glLightfv(GL_LIGHT2, GL_SPECULAR, light_reactor);

		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		
		//glEnable(GL_LIGHT2);


		if (vKeyDown) {
			reactorRotateAngle = reactorRotateAngle*1.2f;
		}

		glPushMatrix();
		{
			glTranslatef(light_position2[0], light_position2[1], light_position2[2]);
			glRotatef(-reactorRotateAngle, 1.0f, 1.0f, 1.0f);
			glColor3f(255 / 255.0f, 255 / 255.0f, 255 / 255.0f);
			glBindTexture(GL_TEXTURE_2D, plasmaTexture);
			//gluSphere(var, radius / 25.0f, slices, stacks);
		}
		glPopMatrix();

		glPushMatrix(); {
			glRotatef(-reactorRotateAngle, 0.0f, 0.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, reactorTurn1Texture);
			gluCylinder(var, radius / 5, radius / 12, 0.1f, slices, stacks);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			glBindTexture(GL_TEXTURE_2D, reactorOutringTexture);
			gluSphere(var, radius / 12, slices, stacks);
		}
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(0.0f, 0.0f, 0.025f);
			glRotatef(reactorRotateAngle, 0.0f, 0.0f, 1.0f);

			glBindTexture(GL_TEXTURE_2D, reactorTurn1Texture);
			gluCylinder(var, radius / 25.0f, radius / 16.0f, 0.01f, slices, stacks);
		}
		glPopMatrix();


		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
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
			//glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();

	}
	glPopMatrix();
}


void drawChest(GLUquadricObj *var) {
	//texture = LoadBMP("textures/armor_texture.bmp");
	//glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix(); {
		glTranslatef(0.0f, -0.2f, 0.0f);
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
	////glDeleteTextures(1, &texture);
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
	glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
	glPushMatrix(); {
		glTranslatef(0.0f, 0.05f, -0.1f);
		glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.08f, 0.1f, 0.2f);

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
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
	//glDeleteTextures(1, &armorTexture);
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
				glScalef(-1.0f, 1.0f, 1.0f);
				drawWaistCover();
			}
			glPopMatrix();

			glTranslatef(0.0f, 0.0f, -0.2f);
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
			glRotatef(hipsJointAngle, 1.0f, 0.0f, 0.0f);
			if (fingerToggle ) {
				if (leftKeyDown)
					glRotatef(leftBodyAngle, 0.0f, 0.0f, -1.0f);
				if (rightKeyDown)
					glRotatef(rightBodyAngle, 0.0f, 0.0f, 1.0f);
			}
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

					glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
				//glDeleteTextures(1, &metalTexture);
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

				glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
				glScalef(0.2f, 0.1f, 0.30f);
				drawFilledCube();
			}
			glPopMatrix();
			//glDeleteTextures(1, &metalTexture);
		}
		glPopMatrix();

	}
	glPopMatrix();

}

void drawFingerArmor(GLUquadricObj *var) {
	glPushMatrix(); {
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
		glTranslatef(-0.15f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		gluCylinder(var, radius / 5.5f, radius / 5.5f, 0.50f, 4, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.5f);
			gluDisk(var, 0.0f, radius / 5.5f, 4, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.5f);
				gluDisk(var, 0.0f, radius / 5.5f, 4, stacks);
			}
			glPopMatrix();
			//glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFinger(GLUquadricObj *var, float fingerAngle1, float fingerAngle2) {
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
			glRotatef(fingerAngle1, 0.0f, 1.0f, 0.0f); //Rotating joint.
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
					glRotatef(fingerAngle2, 0.0f, 1.0f, 0.0f); //Rotating joint.
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
	}
	glPopMatrix();

}

void drawHandArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		//draw palm details
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);


		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
			//glDeleteTextures(1, &metalTexture);
		}
		glPopMatrix();

		// draw hand back details
		glPushMatrix();
		{
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);
			glTranslatef(0.0f, 0.0f, -0.09f);
			glPushMatrix(); {
				glTranslatef(0.10f, -0.07f, -0.05f);
				glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.08f, 0.01f, 0.05f);
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
		if (leftToggle && armToggle ) {
			if (upKeyDown)
				glRotatef(upArmAngle3ForLeft, 0.0f, 1.0f, 0.0f);
			if (downKeyDown)
				glRotatef(downArmAngle3ForLeft, 0.0f, -1.0f, 0.0f);
		}
		glScalef(-1.0f, 1.0f, 1.0f);
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
				if (leftToggle && fingerToggle ) {
					tempFingerAngle = fingersAngle;
					fingersAngle = upFingerAngle3ForLeft;
				}

				drawFinger(var, fingersAngle, fingersAngle);
				fingersAngle = tempFingerAngle;
			}
			glPopMatrix();
			//draw index finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.5f, -0.9f);
				if (leftToggle && fingerToggle) {
					tempFingerAngle = fingersAngle;
					fingersAngle = upFingerAngle2ForLeft;
				}

				drawFinger(var, fingersAngle, fingersAngle);
				fingersAngle = tempFingerAngle;
			}
			glPopMatrix();
			//draw ring finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, -0.3f, -0.9f);
				if (leftToggle && fingerToggle ) {
					tempFingerAngle = fingersAngle;
					fingersAngle = upFingerAngle4ForLeft;
				}

				drawFinger(var, fingersAngle, fingersAngle);
				fingersAngle = tempFingerAngle;
			}
			glPopMatrix();
			//draw little finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.25f);
				glTranslatef(0.0f, -0.6f, -0.9f);
				if (leftToggle && fingerToggle) {
					tempFingerAngle = fingersAngle;
					fingersAngle = upFingerAngle5ForLeft;
				}

				drawFinger(var, fingersAngle, fingersAngle);
				fingersAngle = tempFingerAngle;
			}
			glPopMatrix();
			//draw thumb
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.28f);
				glTranslatef(0.0f, 0.8f, -0.3f);
				glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
				if (leftToggle && fingerToggle) {
					tempFingerAngle = fingersAngle;
					fingersAngle = upFingerAngle1ForLeft;
				}

				drawFinger(var, fingersAngle, fingersAngle);
				fingersAngle = tempFingerAngle;
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
		if (rightToggle && armToggle ) {
			if (upKeyDown)
				glRotatef(upArmAngle3ForRight, 0.0f, -1.0f, 0.0f);
			if (downKeyDown)
				glRotatef(downArmAngle3ForRight, 0.0f, 1.0f, 0.0f);
		}
		glScalef(1.0f, 1.0f, 1.0f);
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
				if (rightToggle && fingerToggle ) {
					fingersAngle = upFingerAngle3ForRight;
				}
				drawFinger(var, fingersAngle, fingersAngle);
			}
			glPopMatrix();
			//draw index finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.5f, -0.9f);
				if (rightToggle && fingerToggle ) {
					fingersAngle = upFingerAngle2ForRight;
				}
				drawFinger(var, fingersAngle, fingersAngle);
			}
			glPopMatrix();
			//draw ring finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, -0.3f, -0.9f);
				if (rightToggle && fingerToggle ) {
					fingersAngle = upFingerAngle4ForRight;
				}
				drawFinger(var, fingersAngle, fingersAngle);
			}
			glPopMatrix();
			//draw little finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.25f);
				glTranslatef(0.0f, -0.6f, -0.9f);
				if (rightToggle && fingerToggle ) {
					fingersAngle = upFingerAngle5ForRight;
				}
				drawFinger(var, fingersAngle, fingersAngle);
			}
			glPopMatrix();
			//draw thumb
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.28f);
				glTranslatef(0.0f, 0.8f, -0.3f);
				glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
				if (rightToggle && fingerToggle ) {
					fingersAngle = upFingerAngle1ForRight;
				}
				drawFinger(var, fingersAngle, fingersAngle);
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
		glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.30f, 0.04f, 0.20f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.05f, 0.18f, 0.25f);
		glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
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
	glPushMatrix();
	{
		glColor3f(105 / 255.0f, 33 / 255.0f, 47 / 255.0f);
		glBindTexture(GL_TEXTURE_2D, redTexture);
		glTranslatef(-0.14f, 0.2f, -0.03f);
		glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.30f, 0.01f, 0.02f);
		drawFilledCube();
	}
	glPopMatrix();
}

void drawBicepCover(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
		glTranslatef(0.10f, 0.23f, 0.80f);
		glPushMatrix();
		{
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.7f, 1.7f, 1.0f);
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			gluCylinder(var, radius / 12.0f, radius / 5.0f, 0.2f, 4, stacks);
			gluDisk(var, 0.0f, radius / 12.0f, 4, stacks);
		}
		glPopMatrix();
		//glDeleteTextures(1, &armorTexture);
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
			glRotatef(-100.0f, 0.0f, 0.0f, 1.0f);
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
				//glDeleteTextures(1, &metalTexture);
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
				glTranslatef(i / 15.0f, 0.0f, i / 40.0f);
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
					glTranslatef(0.0f, 0.03f*i, 0.0f);
					glScalef(0.28f, 0.005f, 0.05f);
					drawFilledCube();
				}
				glPopMatrix();
			}

		}
		glPopMatrix();
		//glDeleteTextures(1, &metalTexture);
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
			glTranslatef(0.0f, 0.0f, -0.15f);
			glScalef(0.2f, 1.0f, 1.2f);
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
		glTranslatef(0.1f, 0.19f, 0.4f);
		if (cannonToggle && cannonOn) {
			glTranslatef(-0.15f, 0.1f, 0.1f);
			glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		}
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.1f, 0.01f, 0.35f);
			drawCover();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.17f, 0.12f, 0.4f);
		if (swordToggle && swordAnimation) {
			glTranslatef(swordVariable1, 0.0f, 0.0f);
			glRotatef(swordVariable2, 0.0f, 0.0f, 1.0f);
		}
		else if (swordToggle && swordOn) {
			glTranslatef(0.05f, 0.0f, 0.0f);
			glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		}
		if (cannonToggle && cannonOn) {
			glTranslatef(0.05f, 0.0f, 0.0f);
			glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		}
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
		if (swordToggle && swordAnimation) {
			glTranslatef(swordVariable3, 0.0f, 0.0f);
		}
		else if (swordToggle  && swordOn) {
			glTranslatef(0.08f, 0.0f, 0.0f);
		}
		if (cannonToggle && cannonOn) {
			glTranslatef(0.08f, 0.0f, 0.0f);
		}
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
		if (cannonToggle && cannonOn) {
			glTranslatef(0.0f, -0.05f, 0.0f);
		}
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

	glPushMatrix();
	{
		if (cannonToggle && cannonOn) {
			glTranslatef(-0.1f, 0.0f, 0.0f);
		}
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
			glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.5f, 0.5f, 1.0f);
			drawTripleCover();
		}
		glPopMatrix();
	}
	glPopMatrix();
	

}

void drawLowerArmArmor(GLUquadricObj *var) {
	//draw lower arm details
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		glTranslatef(0.0f, 0.0f, 0.2f);
		gluCylinder(var, radius / 7.0f, radius / 8.0f, 0.5f, 6, stacks);
	}
	glPopMatrix();
	//glDeleteTextures(1, &metalTexture);
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
	glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.15f, 0.1f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		gluCylinder(var, radius / 10.0f, 0.0f, 0.4f, 4, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.03f);
			glColor3f(1.0f, 1.0f, 1.0f);
			gluDisk(var, 0.0f, radius / 14.0f, 4, stacks);
		}
		glPopMatrix();
		//glDeleteTextures(1, &metalTexture);
	}
	glPopMatrix();
	glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
}



void drawHandJointArmor(GLUquadricObj *var) {
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.1f, 0.0f);
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
			glTranslatef(0.0f, 0.0f, 1.2f);
			if(cannonOn && leftToggle)
				glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(leftArmAngle2, 1.0f, 0.0f, 0.0f);

			if (leftToggle && armToggle ) {
				if (leftKeyDown)
					glRotatef(leftArmAngle2ForLeft, 0.0f, 1.0f, 0.0f);
				if (rightKeyDown)
					glRotatef(rightArmAngle2ForLeft, 0.0f, -1.0f, 0.0f);
				if (upKeyDown)
					glRotatef(upArmAngle2ForLeft, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downArmAngle2ForLeft, 1.0f, 0.0f, 0.0f);
			}
			drawHingeJoint(var);
			glPushMatrix(); {
				glScalef(1.0f, 1.0f, 1.0f);
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
					glScalef(1.0f, 1.0f, 1.0f);
					swordToggle = leftToggle;
					cannonToggle = leftToggle;
					drawLowerArmArmor(var);
					if ((swordAnimation && leftToggle) || (swordOn && leftToggle)) {
						drawSword(var);
					}
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.8f);
					drawHingeJoint(var);
					glPushMatrix(); {
						glScalef(1.0f, 1.0f, 1.0f);
						drawHandJointArmor(var);
					}
					glPopMatrix();
					glTranslatef(0.0f, 0.0f, 0.2f);
					if (cannonOn && leftToggle) {
						glEnable(GL_LIGHT1);
						drawPlasmaCannon(var);
					}
						
					else {
						if(!rightToggle)
							glDisable(GL_LIGHT1);
						drawLeftHand(var);
					}
						
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
			if (cannonOn && rightToggle)
				glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(rightArmAngle2, 1.0f, 0.0f, 0.0f);
			if (rightToggle && armToggle ) {
				if (leftKeyDown)
					glRotatef(leftArmAngle2ForLeft, 0.0f, 1.0f, 0.0f);
				if (rightKeyDown)
					glRotatef(rightArmAngle2ForLeft, 0.0f, -1.0f, 0.0f);
				if (upKeyDown)
					glRotatef(upArmAngle2ForLeft, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downArmAngle2ForLeft, 1.0f, 0.0f, 0.0f);
			}
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
					swordToggle = rightToggle;
					cannonToggle = rightToggle;
					drawLowerArmArmor(var);
					if ((swordAnimation && rightToggle) || (swordOn && rightToggle)) {
						drawSword(var);
					}
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
					if (cannonOn && rightToggle) {
						glEnable(GL_LIGHT1);
						drawPlasmaCannon(var);
					}

					else {
						glDisable(GL_LIGHT1);
						drawRightHand(var);
					}
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

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
		glPushMatrix();
		{
			glScalef(4.0f, 0.9f, 1.0f);
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
		glPushMatrix();
		{
			glTranslatef(0.15f, -0.78f, 0.0f);
			glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
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
			glTranslatef(0.0f, 0.0f, 0.0f);
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
				//glDeleteTextures(1, &armorTexture);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0.0f, -0.1f, 0.20f);
				glRotatef(-25.0f, 1.0f, 0.0f, 0.0f);
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
	if (leftToggle && legToggle ) {
		if (leftKeyDown)
			glRotatef(leftLegAngle3ForLeft, 0.0f, 0.0f, -1.0f);
		if (leftKeyDown)
			glRotatef(rightLegAngle3ForLeft, 0.0f, 0.0f, 1.0f);
		if (upKeyDown)
			glRotatef(upLegAngle3ForLeft, -1.0f, 0.0f, 0.0f);
		if (downKeyDown)
			glRotatef(downLegAngle3ForLeft, 1.0f, 0.0f, 0.0f);
	}
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
	if (rightToggle && legToggle ) {
		if (leftKeyDown)
			glRotatef(leftLegAngle3ForRight, 0.0f, 0.0f, -1.0f);
		if (leftKeyDown)
			glRotatef(rightLegAngle3ForRight, 0.0f, 0.0f, 1.0f);
		if (upKeyDown)
			glRotatef(upLegAngle3ForRight, -1.0f, 0.0f, 0.0f);
		if (downKeyDown)
			glRotatef(downLegAngle3ForRight, 1.0f, 0.0f, 0.0f);
	}
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		glTranslatef(0.15f, 0.0f, 0.0f);
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
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
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
		//glDeleteTextures(1, &metalTexture);
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

			glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
			//glDeleteTextures(1, &metalTexture);

			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

			glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.2f);
				gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.8f, 6, stacks);
			}
			glPopMatrix();
			//glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();
		glPushMatrix(); {
			glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);


			glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
			//glDeleteTextures(1, &metalTexture);
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

			glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
			//glDeleteTextures(1, &metalTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawThighBoneConnection(GLUquadricObj *var) {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
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
		//glDeleteTextures(1, &armorTexture);
	}
	glPopMatrix();
}

void drawThighCover(GLUquadricObj *var) {
	glPushMatrix();
	{

		//draw outside cover
		glPushMatrix(); {
			glTranslatef(0.18f, -0.05f, 0.0f);
			glRotatef(-85.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.25f, 0.025f, 0.35f);
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
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
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
			glTranslatef(0.1f, 0.15f, 0.2f);
			drawThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawThighBone(var);
			drawThighBoneConnection(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.1f, -0.15f, 0.2f);
			glScalef(1.1f, 1.1f, 1.2f);
			drawBackThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawBackThighBone(var);
			drawThighBoneConnection(var);
			glPushMatrix();
			{
				glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);

				glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
			glTranslatef(0.20f, 0.15f, 1.70f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(var, radius / 12.0f, radius / 12.0f, 0.55f, 8, stacks);
			gluDisk(var, 0.0f, radius / 12.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.55f);
				gluDisk(var, 0.0f, radius / 12.0f, 8, stacks);
			}
			glPopMatrix();
			//glDeleteTextures(1, &metalTexture);
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
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
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
			glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.10f, 0.0f, -0.3f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
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
	//glDeleteTextures(1, &metalTexture);
}

void drawLowerLegCover(GLUquadricObj *var) {
	glPushMatrix();
	{
		//draw upper knee cap
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.3f, 0.3f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
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
			glRotatef(-5.0f, 1.0f, 0.0f, 0.0f);
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
			glRotatef(80.0f, 0.0f, 0.0f, 1.0f);
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		glTranslatef(0.0f, 0.15f, 0.5f);
		//draw joint connector
		glPushMatrix();
		{
			glTranslatef(0.15f, 0.0f, 0.0f);
			glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.03f, 0.1f, 0.08f);
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
		//glDeleteTextures(1, &metalTexture);
		//draw shin details
		glPushMatrix();
		{
			glTranslatef(0.2f, 0.15f, 0.4f);
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			drawBackThighBone(var);
			glTranslatef(-0.2f, 0.0f, 0.0f);
			drawBackThighBone(var);

			glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
				//glDeleteTextures(1, &metalTexture);
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

		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
		//draw lower leg booster
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.15f, 0.30f);
			glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
			gluCylinder(var, radius / 3.5f, radius / 5.5f, 0.5f, 8, stacks);
			gluDisk(var, 0.0f, radius / 3.5f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.5f);
				gluDisk(var, 0.0f, radius / 5.5f, 8, stacks);
			}
			glPopMatrix();
			if (eKeyDown) {
				glPushMatrix(); {
					glTranslatef(0.0f, 0.0f, 0.5f);
					glBindTexture(GL_TEXTURE_2D, boostFlame);
					gluCylinder(var, radius / 6.5f, 0.0f, 0.55f, slices, stacks * 2);
				}
				glPopMatrix();
			}
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
		//glDeleteTextures(1, &metalTexture);

		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);


		glBindTexture(GL_TEXTURE_2D, textureArray2[tCount2]);
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
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
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
			//glDeleteTextures(1, &metalTexture);
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
			if (leftToggle && legToggle ) {
				if (leftKeyDown)
					glRotatef(leftLegAngle2ForLeft, 0.0f, 0.0f, -1.0f);
				if (rightKeyDown)
					glRotatef(rightLegAngle2ForLeft, 0.0f, 0.0f, 1.0f);
				if (upKeyDown)
					glRotatef(upLegAngle2ForLeft, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downLegAngle2ForLeft, 1.0f, 0.0f, 0.0f);
			}
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
					glTranslatef(0.0f, 0.0f, -0.3f);
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
			if (rightToggle && legToggle) {
				if (leftKeyDown)
					glRotatef(leftLegAngle2ForRight, 0.0f, 0.0f, -1.0f);
				if (rightKeyDown)
					glRotatef(rightLegAngle2ForRight, 0.0f, 0.0f, 1.0f);
				if (upKeyDown)
					glRotatef(upLegAngle2ForRight, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downLegAngle2ForRight, 1.0f, 0.0f, 0.0f);
			}
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
			glBindTexture(GL_TEXTURE_2D, eyesTexture);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.2f, 1.4f, 1.0f);
			gluCylinder(var, radius / 7.0f, radius / 9.0f, 0.15f, slices, stacks);
		}
		glPopMatrix();
		//glDeleteTextures(1, &eyesTexture);
		//draw helmet top
		glPushMatrix();
		{
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

			glBindTexture(GL_TEXTURE_2D, textureArray[tCount1]);
			glTranslatef(0.0f, 0.07f, 0.10f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.2f, 1.4f, 1.0f);
			gluSphere(var, radius / 9.0f, slices, stacks);
		}
		glPopMatrix();
		//glDeleteTextures(1, &armorTexture);
		//draw helmet cover
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.14f, -0.225f);
			glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
			{
				glTranslatef(0.08f, -0.10f, 0.26f);
				glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);
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
		glPushMatrix();
		{
			glTranslatef(-0.025f, 0.04f, 0.07f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glColor3f(105 / 255.0f, 33 / 255.0f, 47 / 255.0f);
			glBindTexture(GL_TEXTURE_2D, redTexture);
			gluCylinder(var, radius / 5.0f, radius / 5.0f, 0.05f, 6, stacks);
			gluDisk(var, 0.0f, radius / 5.0f, 6, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.05f);
				gluDisk(var, 0.0f, radius / 5.0f, 6, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//draw chin cover
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.15f, -0.12f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.05f, 0.01f, 0.05f);
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
	if (leftToggle) {
		if (armToggle) {
			if (toggle1) {
				leftArmAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				leftArmAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				leftArmAngle3ForLeft += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				leftLegAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				leftLegAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				leftLegAngle3ForLeft += 1.0f;
			}
		}
		if (fingerToggle) {
			if (toggle4) {
				leftHeadAngle += 1.0f;
			}
			if (toggle5) {
				leftBodyAngle += 1.0f;
			}
		}
	}
	if (rightToggle) {
		if (armToggle) {
			if (toggle1) {
				leftArmAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				leftArmAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				leftArmAngle3ForRight += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				leftLegAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				leftLegAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				leftLegAngle3ForRight += 1.0f;
			}
		}
		if (fingerToggle) {
			if (toggle4) {
				leftHeadAngle += 1.0f;
			}
			if (toggle5) {
				leftBodyAngle += 1.0f;
			}
		}
	}

}

void rightKeyAction() {
	if (leftToggle) {
		if (armToggle) {
			if (toggle1) {
				rightArmAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				rightArmAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				rightArmAngle3ForLeft += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				rightLegAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				rightLegAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				rightLegAngle3ForLeft += 1.0f;
			}
		}
	}
	if (rightToggle) {
		if (armToggle) {
			if (toggle1) {
				rightArmAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				rightArmAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				rightArmAngle3ForRight += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				rightLegAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				rightLegAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				rightLegAngle3ForRight += 1.0f;
			}
		}
	}
	if (fingerToggle) {
		if (toggle4) {
			rightHeadAngle += 1.0f;
		}
		if (toggle5) {
			rightBodyAngle += 1.0f;
		}
	}
	
}

void upKeyAction() {
	if (leftToggle) {
		if (armToggle) {
			if (toggle1) {
				upArmAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				upArmAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				upArmAngle3ForLeft += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				upLegAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				upLegAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				upLegAngle3ForLeft += 1.0f;
			}
		}
		if (fingerToggle) {
			if (toggle1) {
				if (upFingerAngle1ForLeft >= 60.0f)
					upFingerAngle1ForLeft -= 2.0f;	
			}
			if (toggle2) {
				if (upFingerAngle2ForLeft >= 60.0f)
					upFingerAngle2ForLeft -= 2.0f;
			}
			if (toggle3) {
				if (upFingerAngle3ForLeft >= 60.0f)
					upFingerAngle3ForLeft -= 2.0f;
			}
			if (toggle4) {
				if (upFingerAngle4ForLeft >= 60.0f)
					upFingerAngle4ForLeft -= 2.0f;
			}
			if (toggle5) {
				if (upFingerAngle5ForLeft >= 60.0f)
					upFingerAngle5ForLeft -= 2.0f;
			}
		}
	}
	if (rightToggle) {
		if (armToggle) {
			if (toggle1) {
				upArmAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				upArmAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				upArmAngle3ForRight += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				upLegAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				upLegAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				upLegAngle3ForRight += 1.0f;
			}
		}
		if (fingerToggle) {
			if (toggle1) {
				if (upFingerAngle1ForRight >= 60.0f)
					upFingerAngle1ForRight -= 2.0f;
			}
			if (toggle2) {
				if (upFingerAngle2ForRight >= 60.0f)
					upFingerAngle2ForRight -= 2.0f;
			}
			if (toggle3) {
				if (upFingerAngle3ForRight >= 60.0f)
					upFingerAngle3ForRight -= 2.0f;
			}
			if (toggle4) {
				if (upFingerAngle4ForRight >= 60.0f)
					upFingerAngle4ForRight -= 2.0f;
			}
			if (toggle5) {
				if (upFingerAngle5ForRight >= 60.0f)
					upFingerAngle5ForRight -= 2.0f;
			}
		}
	}
}

void downKeyAction() {
	if (leftToggle) {
		if (armToggle) {
			if (toggle1) {
				downArmAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				downArmAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				downArmAngle3ForLeft += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				downLegAngle1ForLeft += 1.0f;
			}
			if (toggle2) {
				downLegAngle2ForLeft += 1.0f;
			}
			if (toggle3) {
				downLegAngle3ForLeft += 1.0f;
			}
		}
		if (fingerToggle) {
			if (toggle1) {
				if (upFingerAngle1ForLeft <= 180.0f)
					upFingerAngle1ForLeft += 2.0f;
			}
			if (toggle2) {
				if (upFingerAngle2ForLeft <= 180.0f)
					upFingerAngle2ForLeft += 2.0f;
			}
			if (toggle3) {
				if (upFingerAngle3ForLeft <= 180.0f)
					upFingerAngle3ForLeft += 2.0f;
			}
			if (toggle4) {
				if (upFingerAngle4ForLeft <= 180.0f)
					upFingerAngle4ForLeft += 2.0f;
			}
			if (toggle5) {
				if (upFingerAngle5ForLeft <= 180.0f)
					upFingerAngle5ForLeft += 2.0f;
			}
		}
	}
	if (rightToggle) {
		if (armToggle) {
			if (toggle1) {
				downArmAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				downArmAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				downArmAngle3ForRight += 1.0f;
			}
		}
		if (legToggle) {
			if (toggle1) {
				downLegAngle1ForRight += 1.0f;
			}
			if (toggle2) {
				downLegAngle2ForRight += 1.0f;
			}
			if (toggle3) {
				downLegAngle3ForRight += 1.0f;
			}
		}
		if (fingerToggle) {
			if (toggle1) {
				if (upFingerAngle1ForRight <= 180.0f)
					upFingerAngle1ForRight += 2.0f;
			}
			if (toggle2) {
				if (upFingerAngle2ForRight <= 180.0f)
					upFingerAngle2ForRight += 2.0f;
			}
			if (toggle3) {
				if (upFingerAngle3ForRight <= 180.0f)
					upFingerAngle3ForRight += 2.0f;
			}
			if (toggle4) {
				if (upFingerAngle4ForRight <= 180.0f)
					upFingerAngle4ForRight += 2.0f;
			}
			if (toggle5) {
				if (upFingerAngle5ForRight <= 180.0f)
					upFingerAngle5ForRight += 2.0f;
			}
		}
	}
	
}

void wKeyAction() {
	movingDirection = 0.0f;
}

void aKeyAction() {
	movingDirection = 270.0f;
}

void sKeyAction() {
	movingDirection = 180.0f;
}

void dKeyAction() {
	movingDirection = 90.0f;
}

void qKeyAction() {
	if (!leftFrontWalked) {
		if (!cannonOn) {
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
		}

		if (!leftFrontMax && leftLegAngle1 >= 150.0f && leftLegAngle2 <= 250.0f) {
			leftLegAngle1 -= 1.5f;
			leftLegAngle2 += 2.5f;
		}
		else {
			leftFrontMax = true;
		}
		if (leftFrontMax) {
			if (leftLegAngle2 >= 220.0f) {
				leftLegAngle2 -= 1.5f;
			}

			if (leftLegAngle2 < 220.0f && leftLegAngle1 <= 180.0f) {
				leftLegAngle1 += 1.5f;
				leftLegAngle2 -= 1.5f;
				
				if(movingDirection == 0.0f)
					yPosition -= 0.01f;
				else if (movingDirection == 180.0f)
					yPosition += 0.01f;
				else if (movingDirection == 270.0f)
					xPosition -= 0.01f;
				else if (movingDirection == 90.0f)
					xPosition += 0.01f;
			}

		}
		if (leftLegAngle1 == 180.0f) {
			firstWalk = false;
			leftFrontMax = false;
			leftFrontWalked = true;
			rightFrontWalked = false;
		}
	}
	else {
		if (!cannonOn) {
			rightArmAngle1 += 0.2f;
			rightArmAngle2 += 0.3f;
			leftArmAngle1 -= 0.2f;
			leftArmAngle2 -= 0.3f;
		}

		if (!rightFrontMax && rightLegAngle1 >= 150.0f && rightLegAngle2 <= 250.0f) {
			rightLegAngle1 -= 1.5f;
			rightLegAngle2 += 2.5f;
		}
		else {
			rightFrontMax = true;
		}
		if (rightFrontMax) {
			if (rightLegAngle2 >= 220.0f)
				rightLegAngle2 -= 1.5f;
			if (rightLegAngle2 < 220.0f && rightLegAngle1 <= 180.0f) {
				rightLegAngle1 += 1.5f;
				rightLegAngle2 -= 1.5f;
				if (movingDirection == 0.0f)
					yPosition -= 0.01f;
				else if (movingDirection == 180.0f)
					yPosition += 0.01f;
				else if (movingDirection == 270.0f)
					xPosition -= 0.01f;
				else if (movingDirection == 90.0f)
					xPosition += 0.01f;
			}

		}
		if (rightLegAngle1 == 180.0f) {
			rightFrontMax = false;
			leftFrontWalked = false;
			rightFrontWalked = true;
		}
	}
}

void eKeyAction() {

	bodyJointAngle = 30.0f;
	upperBodyJointAngle = 5.0f;
	reactorRotateAngle *= 2;

	if (movingDirection == 0.0f)
		yPosition -= 0.5f;
	else if (movingDirection == 180.0f)
		yPosition += 0.5f;
	else if (movingDirection == 270.0f)
		xPosition -= 0.5f;
	else if (movingDirection == 90.0f)
		xPosition += 0.5f;
}

void pKeyAction() {

}

void drawGipsyDanger(GLUquadricObj *var) {
	glPushMatrix();
	{
		
		if (scene1) {
			glTranslatef(0.0f, 2.5f, 0.4f);
			glScalef(0.7f, 0.7f, 0.7f);
		}
		glTranslatef(xPosition, yPosition, zPosition);
		glRotatef(movingDirection, 0.0f, 0.0f, 1.0f);
		glRotatef(bodyJointAngle, 1.0f, 0.0f, 0.0f);

		//draw spine
		drawSpine(var);

		// draw head
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.2f, 1.9f); //Switch origin to prefered rotate point.
			glRotatef(headAngle1, 0.0f, 0.0f, 0.1f); //Rotating joint.
			if (fingerToggle ) {
				if (leftKeyDown)
					glRotatef(leftHeadAngle, 0.0f, 0.0f, -1.0f);
				if (rightKeyDown)
					glRotatef(rightHeadAngle, 0.0f, 0.0f, 1.0f);
			}
			drawBallJoint(var);
			drawHead(var);
		}
		glPopMatrix();


		//draw left leg
		glPushMatrix();
		{
			glTranslatef(0.5f, 0.0f, 0.0f); //Switch origin to prefered rotate point.
			glRotatef(leftLegAngle1, leftLegAxis[0][0], leftLegAxis[0][1], leftLegAxis[0][2]);  //Rotating joint.
			if (leftToggle && legToggle ) {
				if (leftKeyDown)
					glRotatef(leftLegAngle1ForLeft, 0.0f, 0.0f, 1.0f);
				if(rightKeyDown)
					glRotatef(rightLegAngle1ForLeft, 0.0f, 0.0f, -1.0f);
				if (upKeyDown)
					glRotatef(upLegAngle1ForLeft, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downLegAngle1ForLeft, 1.0f, 0.0f, 0.0f);
			}
			drawBallJoint(var);
			glPushMatrix();
			{
				drawLeftLeg(var);
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw right leg
		glPushMatrix();
		{
			glTranslatef(-0.5f, 0.0f, 0.0f); //Switch origin to prefered rotate point.
			glRotatef(rightLegAngle1, rightLegAxis[0][0], rightLegAxis[0][1], rightLegAxis[0][2]); //Rotating joint.
			if (rightToggle && legToggle ) {
				if (leftKeyDown)
					glRotatef(leftLegAngle1ForRight, 0.0f, 0.0f, 1.0f);
				if (rightKeyDown)
					glRotatef(rightLegAngle1ForRight, 0.0f, 0.0f, -1.0f);
				if (upKeyDown)
					glRotatef(upLegAngle1ForRight, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downLegAngle1ForRight, 1.0f, 0.0f, 0.0f);
			}

			drawBallJoint(var);
			glPushMatrix();
			{
				drawRightLeg(var);
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw right arm
		glPushMatrix();
		{
			glTranslatef(-1.0f, 0.0f, 1.85f); //Switch origin to prefered rotate point.
			glRotatef(rightArmAngle1, 1.0f, 0.0f, 0.0f); //Rotating joint.

			if (rightToggle && armToggle ) {
				if (leftKeyDown)
					glRotatef(leftArmAngle1ForRight, 0.0f, 1.0f, 0.0f);
				if(rightKeyDown)
					glRotatef(rightArmAngle1ForRight, 0.0f, -1.0f, 0.0f);
				if(upKeyDown)
					glRotatef(upArmAngle1ForRight, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downArmAngle1ForRight, 1.0f, 0.0f, 0.0f);
			}

			drawBallJoint(var);
			if (cannonOn && rightToggle) {
				glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);
			}
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

		//draw left arm
		glPushMatrix();
		{
			glTranslatef(1.0f, 0.0f, 1.85f); //Switch origin to prefered rotate point.
			glRotatef(leftArmAngle1, 1.0f, 0.0f, 0.0f); //Rotating joint.

			if (leftToggle && armToggle ) {
				if (leftKeyDown)
					glRotatef(leftArmAngle1ForLeft, 0.0f, 1.0f, 0.0f);
				if (rightKeyDown)
					glRotatef(rightArmAngle1ForLeft, 0.0f, -1.0f, 0.0f);
				if (upKeyDown)
					glRotatef(upArmAngle1ForLeft, -1.0f, 0.0f, 0.0f);
				if (downKeyDown)
					glRotatef(downArmAngle1ForLeft, 1.0f, 0.0f, 0.0f);
			}


			drawBallJoint(var);
			if (cannonOn && leftToggle) {
				glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);
			}
			glPushMatrix(); {
				drawUpperArmArmor(var);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.1f, 0.0f, 0.0f);
				drawLeftArm(var);
			}
			glPopMatrix();
		}
		glPopMatrix();

	}
	glPopMatrix();
}

/*

*/
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

		glBindTexture(GL_TEXTURE_2D, roof);
		gluCylinder(var, baseRadius*3.0f, 0.05f, 0.6f, 4, 1);
		//glDeleteTextures(1, &roof);
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

	glBindTexture(GL_TEXTURE_2D, smallTower);
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
	//glDeleteTextures(1, &smallTower);
	glPushMatrix();
	{
		glColor3f((float)206 / 255.0f, (float)190 / 255.0f, (float)167 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, towerFront);
		////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		glTranslatef(-1.7f, -0.3f, 0.0f);
		glPushMatrix();
		{
			glScalef(0.25f, 0.25f, 0.8f);
			glTranslatef(0.0f, 0.0f, 0.3f);
			drawFilledCube();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.25f, 0.0f, 0.26f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.25f, 0.02f, 0.8f);
			drawFilledCube();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.3f, 0.0f, 0.26f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.25f, 0.02f, 0.8f);
			drawFilledCube();
		}
		glPopMatrix();

		//glDeleteTextures(1, &towerFront);
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
		glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
		drawFilledCube();
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

	glBindTexture(GL_TEXTURE_2D, baseBridgeTexture);
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
	//glDeleteTextures(1, &baseBridgeTexture);

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

			glBindTexture(GL_TEXTURE_2D, roadTexture);
			glColor3f(0.0f, 0.0f, 0.0f);
			////glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
			drawFilledCube();
			//glDeleteTextures(1, &roadTexture);
			glPushMatrix();
			{

				glBindTexture(GL_TEXTURE_2D, sideFenceTexture);
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
			//glDeleteTextures(1, &sideFenceTexture);
			glPushMatrix();
			{

				glBindTexture(GL_TEXTURE_2D, baseBridgeTexture);
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
		//glDeleteTextures(1, &baseBridgeTexture);

	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1.7f, -0.2f, -1.5f);
		glScalef(0.5f, 0.5f, 0.45f);
		glColor3f((float)168 / 255.0f, (float)150 / 255.0f, (float)133 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, base);
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
		//glDeleteTextures(1, &base);
		//sea wave effect
		glPushMatrix();
		{
			glRotatef(seaWaveMovement, 0, 0, 1);
			if (weather)
				glColor3f((float)131 / 255.0f, (float)101 / 255.0f, (float)49 / 255.0f);
			else
				glColor3f((float)33 / 255.0f, (float)91 / 255.0f, (float)95 / 255.0f);

			if(weather)
				glBindTexture(GL_TEXTURE_2D, seaTexture);
			else
				glBindTexture(GL_TEXTURE_2D, nightSea);
			//glColor3f((float)255 / 255.0f, (float)255 / 255.0f, (float)255 / 255.0f);
			//glColor3f((float)128 / 255.0f, (float)128 / 255.0f, (float)128 / 255.0f);
			gluDisk(var, 0.0f, 15.0f, slices, 20);
		}
		glPopMatrix();
		//glDeleteTextures(1, &seaTexture);
	}
	glPopMatrix();

}



void drawRoad(GLUquadricObj *var) {
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, roadTexture);
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
	//glDeleteTextures(1, &roadTexture);
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, sandStoneTexture);
		glColor3f((float)206 / 255.0f, (float)190 / 255.0f, (float)167 / 255.0f);
		glScalef(0.1f, 0.2f, 0.1f);
		glTranslatef(52.0f, -1.0f, -1.2f);
		drawFilledCube();
		//glDeleteTextures(1, &sandStoneTexture);
		glPushMatrix();
		{
			glColor3f((float)168 / 255.0f, (float)150 / 255.0f, (float)133 / 255.0f);

			glBindTexture(GL_TEXTURE_2D, smallTower);
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
		//glDeleteTextures(1, &smallTower);
	}
	glPopMatrix();
	glPushMatrix();
	{

		glBindTexture(GL_TEXTURE_2D, sideFenceTexture);
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
	//glDeleteTextures(1, &sideFenceTexture);


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

	glBindTexture(GL_TEXTURE_2D, bridgeTexture);
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
	//glDeleteTextures(1, &bridgeTexture);
}

void drawBridge() {
	glPushMatrix();
	{

		glTranslatef(-0.15f, -0.10f, 0.8f);
		glScalef(1.7f, 0.05f, 0.02f);
		glBindTexture(GL_TEXTURE_2D, brickRoadTexture);
		glColor3f((float)108 / 255.0f, (float)86 / 255.0f, (float)63 / 255.0f);
		drawFilledCube();
		//glDeleteTextures(1, &brickRoadTexture);
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
	if(weather)
		glBindTexture(GL_TEXTURE_2D, seaTexture);
	else
		glBindTexture(GL_TEXTURE_2D, nightSea);
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
	//glDeleteTextures(1, &seaTexture);
}

void display()
{
	glMatrixMode(GL_MODELVIEW);

	//glClearColor((float)121 / 255, (float)168 / 255, (float)224 / 255, 1.0f);
	//glClearColor((float)60 / 255, (float)128 / 255, (float)191 / 255, 1.0f);
	//glClearColor((float)69 / 255, (float)156 / 255, (float)236 / 255, 1.0f);


	if (weather) {
		glClearColor((float)45 / 255, (float)55 / 255, (float)181 / 255, 1.0f);
	}
	else {
		glClearColor((float)0 / 255, (float)0 / 255, (float)0 / 255, 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	GLUquadricObj *var = NULL;

	(GLUquadricObj *)var = gluNewQuadric();
	gluQuadricNormals(var, GLU_SMOOTH);
	gluQuadricTexture(var, GL_TRUE);


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

	//glEnable(GL_LIGHT0); //enable the light after setting the properties
	

	GLfloat no_shininess[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat low_shininess[] = { 5.0f, 5.0f, 5.0f, 0.0f };
	GLfloat high_shininess[] = { 100.0f, 100.0f, 100.0f, 100.0f };
	GLfloat mat_emission[] = { 0.5f, 0.5f, 0.5f, 0.0f };

	glPushMatrix();
	{
		glTranslatef(light_position[0], light_position[1], light_position[2]);
		//glColor3f(255 / 255.0f, 255 / 255.0f, 255 / 255.0f);
		if(weather)
			glBindTexture(GL_TEXTURE_2D, sunTexture);
		else
			glBindTexture(GL_TEXTURE_2D, moonTexture);
		gluSphere(var, radius / 4.0f, slices, stacks);
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

	//gluQuadricDrawStyle(var, GLU_FILL);

	drawGipsyDanger(var);


	if (scene1) {
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
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	armorTexture = LoadBMP("textures/armor_texture.bmp");
	armorTexture1 = LoadBMP("textures/armor_texture_2.bmp");
	armorTexture2 = LoadBMP("textures/armor_texture_1.bmp");
	metalTexture = LoadBMP("textures/metal_texture.bmp");
	glossyMetal = LoadBMP("textures/glossy_metal.bmp");
	glass = LoadBMP("textures/glass.bmp");
	camourflage = LoadBMP("textures/camouflage.bmp");
	flame = LoadBMP("textures/flame.bmp");
	mechanical = LoadBMP("textures/mechanical.bmp");

	backConnectorTexture = LoadBMP("textures/back_connector.bmp");
	reactorOutringTexture = LoadBMP("textures/reactor_outring_texture.bmp");
	reactorTurn1Texture = LoadBMP("textures/reactor_turn1_texture.bmp");
	eyesTexture = LoadBMP("textures/eyes_texture.bmp");
	redTexture = LoadBMP("textures/red_texture.bmp");
	plasmaTexture = LoadBMP("textures/plasma_texture.bmp");
	plasmaTexture2 = LoadBMP("textures/plasma_texture2.bmp");
	plasmaTexture3 = LoadBMP("textures/plasma_texture3.bmp");
	cannonTexture = LoadBMP("textures/cannon_texture.bmp");
	boostFlame = LoadBMP("textures/boost_flame.bmp");

	textureArray[0] = armorTexture;
	textureArray[1] = armorTexture1;
	textureArray[2] = armorTexture2;
	textureArray[3] = glass;
	textureArray[4] = camourflage;
	textureArray[5] = flame;

	textureArray2[0] = metalTexture;
	textureArray2[1] = glossyMetal;
	textureArray2[2] = mechanical;

	sunTexture = LoadBMP("textures/sun_texture.bmp");
	moonTexture = LoadBMP("textures/moon_texture.bmp");
	nightSea = LoadBMP("textures/night_sea.bmp");

	roof = LoadBMP("textures/roof.bmp");
	smallTower = LoadBMP("textures/small_tower.bmp");
	towerFront = LoadBMP("textures/tower_front.bmp");
	baseBridgeTexture = LoadBMP("textures/base_bridge_texture.bmp");
	roadTexture = LoadBMP("textures/road_texture.bmp");
	sideFenceTexture = LoadBMP("textures/side_fence_texture.bmp");
	base = LoadBMP("textures/base.bmp");
	seaTexture = LoadBMP("textures/sea_texture.bmp");
	
	sandStoneTexture = LoadBMP("textures/sand_stone_texture.bmp");
	bridgeTexture = LoadBMP("textures/bridge_texture.bmp");
	brickRoadTexture = LoadBMP("textures/brick_road_texture.bmp");

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

		if (reactorRotateAngle < 360)
			cannonRotateAngle += 10.0f;
		else
			cannonRotateAngle = 0.0f;

		if (seaWaveMovement < 360)
			seaWaveMovement += 0.000005f;
		else
			seaWaveMovement = 0.0f;

		if (shootToggle && cannonOn) {
			if (ballZPosition <= 15.0f) {
				ballZPosition += 0.5f;
			}
			else {
				shootToggle = false;
				ballZPosition = 0.15f;
				ballSize = radius / 23.0f;
			}

		}

		display();

		SwapBuffers(hdc);
	}

	glDeleteTextures(1, &armorTexture);
	glDeleteTextures(1, &armorTexture1);
	glDeleteTextures(1, &armorTexture2);
	glDeleteTextures(1, &metalTexture);
	glDeleteTextures(1, &glossyMetal);

	glDeleteTextures(1, &glass);
	glDeleteTextures(1, &camourflage);
	glDeleteTextures(1, &flame); 
	glDeleteTextures(1, &mechanical);

	glDeleteTextures(1, &backConnectorTexture);
	glDeleteTextures(1, &reactorOutringTexture);
	glDeleteTextures(1, &reactorTurn1Texture);
	glDeleteTextures(1, &eyesTexture);
	glDeleteTextures(1, &redTexture);
	glDeleteTextures(1, &plasmaTexture);
	glDeleteTextures(1, &plasmaTexture2);
	glDeleteTextures(1, &plasmaTexture3);
	glDeleteTextures(1, &cannonTexture);
	glDeleteTextures(1, &boostFlame);
	
	glDeleteTextures(1, &sunTexture);
	glDeleteTextures(1, &moonTexture);
	glDeleteTextures(1, &nightSea);
	
	glDeleteTextures(1, &roof);
	glDeleteTextures(1, &armorTexture);
	glDeleteTextures(1, &smallTower);
	glDeleteTextures(1, &towerFront);
	glDeleteTextures(1, &baseBridgeTexture);
	glDeleteTextures(1, &sideFenceTexture);
	glDeleteTextures(1, &seaTexture);
	glDeleteTextures(1, &roadTexture);
	glDeleteTextures(1, &sandStoneTexture);
	glDeleteTextures(1, &bridgeTexture);
	glDeleteTextures(1, &brickRoadTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDisable(GL_LIGHTING);
	//glDisable(GL_STENCIL_TEST);
	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}