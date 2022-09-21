#pragma once
//Engine into dll
#ifdef EM_PLATFORM_WINDOWS
	#ifdef EM_BUILD_DLL
		#define EM_API __declspec(dllexport)
	#else
		#define EM_API __declspec(dllimport)
	#endif 
#else
	#error support Windows only!
#endif

#define BIT(x) (x << 1)