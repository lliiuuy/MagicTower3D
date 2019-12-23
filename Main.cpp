#include "Config.h"
#include "GameManager.h"

bool fullScreen = false; // �Ƿ�ȫ��

GameManager* gameManager;

int counter = 0;

unsigned short adjust = 4;
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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (gameManager->isGameOver())
			gameManager->newGame();
	}
	else if (key == GLFW_KEY_R && action == GLFW_REPEAT)
	{
		counter++;
		if (counter >= 50)
		{
			gameManager->newGame();
			counter = 0;
		}
	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE)
		counter = 0;
	if (action == GLFW_REPEAT || action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			gameManager->spinPlayer(true);
			break;
		case GLFW_KEY_D:
			gameManager->spinPlayer(false);
			break;
		case GLFW_KEY_W:
			gameManager->movePlayer(true);
			break;
		case GLFW_KEY_S:
			gameManager->movePlayer(false);
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
	int widthOrigin = width;
	if (width != height * 4 / 3)
		width = height * 4 / 3;
	gameManager->setWindow(width, height, widthOrigin, height);

	glViewport((widthOrigin - width)/2, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	gluPerspective(60.0f, width * 1.3f  / height, 0.025f, 1000.0f); // ����ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	double posX, posY;
	glfwGetCursorPos(window ,&posX, &posY);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		gameManager->mouseButtonClick((int)posX, (int)posY);
}

int main()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(1600, 1200, "MagicTower3D", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // ָ����Ⱦ����
	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // ��ȡ��Ⱦ���ڴ�С

	initGL();
	glViewport(0, 0, width, height); // ������

	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	gluPerspective(60.0f, width * 1.3f / height, 0.025f, 1000.0f); // ����ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���

	timerInit();

	gameManager = new GameManager(width, height, width, height);
	gameManager->init();

	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, resizeCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	while (!glfwWindowShouldClose(window))
	{
		float start = timerGetTime();
		while (timerGetTime() < start + float(steps[adjust] * 2.0f)) {} // ����֡��
		gameManager->drawScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	gameManager->save();

	return 0;
}