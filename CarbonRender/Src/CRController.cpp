#include "..\Inc\CRController.h"

void Controller::Init()
{
	sensitivity[0] = 0.2f;
	sensitivity[1] = 0.1f;

	moveSpeed = 20.0f;
	v = float3(0.0f);
}

void Controller::Update()
{
	Camera* curCam = CameraManager::Instance()->GetCurrentCamera();
	float3 curPos = curCam->GetPosition();
	curPos = curPos + (curCam->GetForward().normalize() * v.x  * moveSpeed +
						curCam->GetRight().normalize() * v.y  * moveSpeed +
						curCam->GetUp().normalize() * v.z  * moveSpeed) * FIXEDUPDATE_TIME;
	CameraManager::Instance()->GetCurrentCamera()->SetPosition(curPos);
}

void Controller::KeyDownCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	case 'w':
	case 'W':
	{
		v.x = 1.0f;
	}
	break;
	case 's':
	case 'S':
	{
		v.x = -1.0f;
	}
	break;
	case 'a':
	case 'A':
	{
		v.y = -1.0f;
	}
	break;
	case 'd':
	case 'D':
	{
		v.y = 1.0f;
	}
	break;
	case 'q':
	case 'Q':
	{
		v.z = 1.0f;
	}
	break;
	case 'e':
	case 'E':
	{
		v.z = -1.0f;
	}
	break;
	case '=':
	{
		WeatherSystem::Instance()->SetHour(WeatherSystem::Instance()->GetHour() + 0.1f);
	}
	break;
	case '-':
	{
		WeatherSystem::Instance()->SetHour(WeatherSystem::Instance()->GetHour() - 0.1f);
	}
	break;
	}
}

void Controller::KeyUpCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	case 'w':
	case 'W':
	{
		v.x = 0.0f;
	}
	break;
	case 's':
	case 'S':
	{
		v.x = 0.0f;
	}
	break;
	case 'a':
	case 'A':
	{
		v.y = 0.0f;
	}
	break;
	case 'd':
	case 'D':
	{
		v.y = 0.0f;
	}
	break;
	case 'q':
	case 'Q':
	{
		v.z = 0.0f;
	}
	break;
	case 'e':
	case 'E':
	{
		v.z = 0.0f;
	}
	break;
	}
}

void Controller::SpecialKeyDownCallback(int key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	case GLUT_ACTIVE_SHIFT:
	{
		moveSpeed *= 10.0f;
	}
	break;
	}
}

void Controller::SpecialKeyUpCallback(int key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	case GLUT_ACTIVE_SHIFT:
	{
		moveSpeed *= 0.1f;
	}
	break;
	}
}

void Controller::MouseKeyCallback(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
	{
		if (state == GLUT_DOWN)
		{
			curMouseButton = GLUT_LEFT_BUTTON;
		}
	}
	break;
	case GLUT_RIGHT_BUTTON:
	{	
		if (state == GLUT_DOWN)
		{
			curMouseButton = GLUT_RIGHT_BUTTON;
		}
	}
	break;
	case GLUT_MIDDLE_BUTTON:
	{
		if (state == GLUT_DOWN)
		{
			curMouseButton = GLUT_MIDDLE_BUTTON;
		}
	}
	break;
	}
	lastMousePos[0] = x;
	lastMousePos[1] = y;
}

void Controller::MouseMotionCallback(int x, int y)
{
	switch (curMouseButton)
	{
	case GLUT_LEFT_BUTTON:
		float3 curR = CameraManager::Instance()->GetCurrentCamera()->GetRotation();
		curR.y += (x - lastMousePos[0]) * sensitivity[0];
		curR.x += (y - lastMousePos[1]) * sensitivity[1];
		if (curR.x > 90.0f) curR.x = 90.0f;
		if (curR.x < -90.0f) curR.x = -90.0f;
		CameraManager::Instance()->GetCurrentCamera()->SetRotation(curR);
		break;
	//case GLUT_RIGHT_BUTTON:
		//break;
	//case GLUT_MIDDLE_BUTTON:
		//break;
	}
	lastMousePos[0] = x;
	lastMousePos[1] = y;
	glutPostRedisplay();
}
