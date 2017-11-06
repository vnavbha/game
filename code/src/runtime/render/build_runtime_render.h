#pragma once

#ifdef BUILD_RUNTIME_RENDER
#define RUNTIME_RENDER_API __declspec(dllexport)   
#else  
#define RUNTIME_RENDER_API __declspec(dllimport)   
#endif  

