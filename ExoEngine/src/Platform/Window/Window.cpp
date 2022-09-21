#include "empch.h"
#include "Window.h"


namespace EM{
	void Window::Init()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			EM_EXO_ASSERT(!glfwInit(), "\aGLFW init has failed - exit project...");
		}
		glfwSetErrorCallback(ErrorCallback);

		//specify the constraints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
		//we are setting window size able toggle
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); 

		//fullscreen
		m_monitor = glfwGetPrimaryMonitor();

		//set initialize window width & height to current 
		m_windowData.m_CurrentWidth = m_windowData.m_Width;
		m_windowData.m_CurrentHeight = m_windowData.m_Height;

		//create window
		m_window = glfwCreateWindow(m_windowData.m_CurrentWidth,
			m_windowData.m_CurrentHeight,
			m_windowData.Title.c_str(),
			NULL, NULL);

		if (!m_window)
		{
			std::cout << "Failed to create window !" << std::endl;
			glfwTerminate();
		}

		EM_EXO_INFO("Generating Window {0} : SIZE ({1},{2})", m_windowData.Title, m_windowData.m_Width, m_windowData.m_Height);
	
		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);

		glfwSwapInterval(1);

		if(glewInit() != GLEW_OK)
			EM_EXO_ASSERT(!glewInit(), "GLEW init has failed - abort program...");
		
	}
	void Window::Update()
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	void Window::End()
	{
		glfwTerminate();
	}
	void Window::ErrorCallback(int error, const char* description)
	{
	}
	void Window::Window_size_callback(GLFWwindow* window, int width, int height)
	{
	}
	void Window::Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
	}
	void Window::Mousebutton_callback(GLFWwindow* window, int button, int action, int mode)
	{
	}
	void Window::Mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
	}
	void Window::Mouseposition_callback(GLFWwindow* window, double xpos, double ypos)
	{
	}
	void Window::ToggleVsync(bool& value)
	{
	}
}