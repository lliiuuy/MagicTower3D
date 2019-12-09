#include "Config.h"
#include "MapCreator.h"

bool fullScreen = false; // 是否全屏

float rotX = 0; // 视角X轴旋转量
float rotY = 0; // 视角Y轴旋转量

unsigned short adjust = 5;
unsigned short steps[6] = { 1, 2, 4, 5, 10, 20 }; // 帧数调整的步进值



struct			 											// 计时器的结构体
{
	__int64       frequency;									// 计时器频率（所以为啥不用long）
	float         resolution;									// 计时器精度
	unsigned long mm_timer_start;								// 计时器开始的时间
	unsigned long mm_timer_elapsed;								// 计时器经过的时间
	bool		  performance_timer;							// 是否显示计时器
	__int64       performance_timer_start;						// 显示计时器开始的时间
	__int64       performance_timer_elapsed;					// 显示计时器经过的时间
} timer;

void timerInit(void)										// 初始化计时器
{
	memset(&timer, 0, sizeof(timer));						//	为计时器分配空间

	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&timer.frequency)) // 如果无法获取精确时间的显示，就使用自己的变量进行计算
	{
		timer.performance_timer = FALSE;					// 计时器无法显示
		timer.mm_timer_start = timeGetTime();				// 获取当前的时间
		timer.resolution = 1.0f / 1000.0f;					// 将计时器精度变为0.001
		timer.frequency = 1000;								// 将计时器频率设置为1000
		timer.mm_timer_elapsed = timer.mm_timer_start;
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&timer.performance_timer_start); // 如果可以换取精确时间的显示，就直接可以在系统中创建一个计数器（Counter）
		timer.performance_timer = TRUE;
		timer.resolution = (float)(((double)1.0f) / ((double)timer.frequency));
		timer.performance_timer_elapsed = timer.performance_timer_start;
	}
}

float timerGetTime() // 获取时间（毫秒）
{
	__int64 time; // 需要用64位int存储（所以为啥不用long）

	if (timer.performance_timer) // 是否用了计数器
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
	glShadeModel(GL_SMOOTH);							// 开启平滑渲染模式
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// 初始化背景(RGBA(0,0,0,0.5))-->黑色
	glClearDepth(1.0f);									// 初始化渲染深度
	glEnable(GL_DEPTH_TEST);							// 启动深度测试
	glDepthFunc(GL_LEQUAL);								// 设置进行深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // 设置自动透视修正
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
		height = 1; // 保护
	if (width == 0)
		width = 1;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // 设置投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵
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

	glfwMakeContextCurrent(window); // 指定渲染窗口
	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // 获取渲染窗口大小

	initGL();
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // 设置投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵

	timerInit();
	initObjects();

	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, resizeCallback);

	while (!glfwWindowShouldClose(window))
	{
		float start = timerGetTime();
		while (timerGetTime() < start + float(steps[adjust] * 2.0f)) {} // 控制帧数
		drawScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}