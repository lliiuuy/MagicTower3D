#include "Config.h"
#include "MapCreator.h"

bool fullScreen = false; // �Ƿ�ȫ��

float rotX = 0; // �ӽ�X����ת��
float rotY = 0; // �ӽ�Y����ת��

unsigned short adjust = 5;
unsigned short steps[6] = { 1, 2, 4, 5, 10, 20 }; // ֡�������Ĳ���ֵ



struct			 											// ��ʱ���Ľṹ��
{
	__int64       frequency;									// ��ʱ��Ƶ�ʣ�����Ϊɶ����long��
	float         resolution;									// ��ʱ������
	unsigned long mm_timer_start;								// ��ʱ����ʼ��ʱ��
	unsigned long mm_timer_elapsed;								// ��ʱ��������ʱ��
	bool		  performance_timer;							// �Ƿ���ʾ��ʱ��
	__int64       performance_timer_start;						// ��ʾ��ʱ����ʼ��ʱ��
	__int64       performance_timer_elapsed;					// ��ʾ��ʱ��������ʱ��
} timer;

void timerInit(void)										// ��ʼ����ʱ��
{
	memset(&timer, 0, sizeof(timer));						//	Ϊ��ʱ������ռ�

	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&timer.frequency)) // ����޷���ȡ��ȷʱ�����ʾ����ʹ���Լ��ı������м���
	{
		timer.performance_timer = FALSE;					// ��ʱ���޷���ʾ
		timer.mm_timer_start = timeGetTime();				// ��ȡ��ǰ��ʱ��
		timer.resolution = 1.0f / 1000.0f;					// ����ʱ�����ȱ�Ϊ0.001
		timer.frequency = 1000;								// ����ʱ��Ƶ������Ϊ1000
		timer.mm_timer_elapsed = timer.mm_timer_start;
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&timer.performance_timer_start); // ������Ի�ȡ��ȷʱ�����ʾ����ֱ�ӿ�����ϵͳ�д���һ����������Counter��
		timer.performance_timer = TRUE;
		timer.resolution = (float)(((double)1.0f) / ((double)timer.frequency));
		timer.performance_timer_elapsed = timer.performance_timer_start;
	}
}

float timerGetTime() // ��ȡʱ�䣨���룩
{
	__int64 time; // ��Ҫ��64λint�洢������Ϊɶ����long��

	if (timer.performance_timer) // �Ƿ����˼�����
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&time);

		return ((float)(time - timer.performance_timer_start) * timer.resolution) * 1000.0f;
	}
	else
	{
		return((float)(timeGetTime() - timer.mm_timer_start) * timer.resolution) * 1000.0f;
	}
}

void initGL()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// ����ƽ����Ⱦģʽ
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// ��ʼ������(RGBA(0,0,0,0.5))-->��ɫ
	glClearDepth(1.0f);									// ��ʼ����Ⱦ���
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glDepthFunc(GL_LEQUAL);								// ���ý�����Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // �����Զ�͸������
}

bool initObjects()
{
	bool status = false;
	return status;
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(rotX, 1, 0, 0);
	glRotatef(360.0f - rotY, 0, 1, 0);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (fullScreen)
		{
			GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
			glfwSetWindowPos(window, 0, 0);
			glfwSetWindowSize(window, mode->width, mode->height);
			fullScreen = !fullScreen;
		}
		else
		{
			glfwSetWindowSize(window, 800, 600);
			fullScreen = !fullScreen;
		}
	}
	if (action == GLFW_REPEAT || action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			rotX--;
			break;
		case GLFW_KEY_DOWN:
			rotX++;
			break;
		case GLFW_KEY_LEFT:
			rotY++;
			break;
		case GLFW_KEY_RIGHT:
			rotY--;
			break;
		case GLFW_KEY_W:
			/*view->x -= (float)sin(rotY * M_PI / 180) * 2.0f;
			view->y -= (float)sin(rotX * M_PI / 180) * 2.0f;
			view->z -= (float)cos(rotY * M_PI / 180) * 2.0f;
			*/
			break;
		case GLFW_KEY_S:
			break;
		}
	}
}

void resizeCallback(GLFWwindow* window, int width, int height)
{
	if (height == 0)
		height = 1; // ����
	if (width == 0)
		width = 1;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // ����ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���
}

int main()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "MagicTower3D", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // ָ����Ⱦ����
	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // ��ȡ��Ⱦ���ڴ�С

	initGL();
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // ����ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���

	timerInit();
	initObjects();

	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, resizeCallback);

	while (!glfwWindowShouldClose(window))
	{
		float start = timerGetTime();
		while (timerGetTime() < start + float(steps[adjust] * 2.0f)) {} // ����֡��
		drawScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}