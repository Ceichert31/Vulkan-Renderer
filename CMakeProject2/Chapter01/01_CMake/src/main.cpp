#include <stdio.h>
#include <../../../Shared/glfw/include/GLFW/glfw3.h>

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 800;

/// <summary>
/// Creates a GLFW window
/// </summary>
/// <param name="windowTitle"></param>
/// <returns></returns>
GLFWwindow* InitWindow(const char* windowTitle, uint32_t& outWidth, uint32_t& outHeight) 
{
	//Set error callback
	glfwSetErrorCallback([](int error, const char* description) 
		{
			printf("GLFW Error (%i): %s\n", error, description);
		});

	//Init glfw
	if (!glfwInit()) return nullptr;

	//True full screen or taskbar showing
	const bool isFullscreen = !outWidth || !outHeight;
	
	//Set api settings to none
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	//Allow resizeablility based on fullscreen
	glfwWindowHint(GLFW_RESIZABLE, isFullscreen ? GLFW_FALSE : GLFW_TRUE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	int x = 0;
	int y = 0;
	int w = mode->width;
	int h = mode->height;

	if (isFullscreen) 
	{
		//Get fulls size of monitor
		glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
	}
	else 
	{
		w = outWidth;
		h = outHeight;
	}

	//Create window
	GLFWwindow* window = glfwCreateWindow(w, h, windowTitle, monitor, nullptr);

	//If window creation fails terminate
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	//Set window dimensions
	if (isFullscreen) glfwSetWindowPos(window, x, y);
	glfwGetWindowSize(window, &w, &h);

	outWidth = (uint32_t)w;
	outHeight = (uint32_t)h;

	//Setup window close key
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int action, int) 
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
			{
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		});

	return window;
}

int main()
{
	printf("Hello World!\n");

	GLFWwindow* window = InitWindow("GLFW example", (uint32_t&)WIDTH, (uint32_t&)HEIGHT);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
