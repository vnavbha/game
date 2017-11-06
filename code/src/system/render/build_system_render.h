#pragma once

#ifdef BUILD_SYSTEM_RENDER
	#define SYSTEM_RENDER_API __declspec(dllexport)   
#else  
	#define SYSTEM_RENDER_API __declspec(dllimport)   
#endif  
