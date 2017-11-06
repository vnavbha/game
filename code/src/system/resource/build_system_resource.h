#pragma once

#ifdef BUILD_SYSTEM_RESOURCE
#define SYSTEM_RESOURCE_API __declspec(dllexport)   
#else  
#define SYSTEM_RESOURCE_API __declspec(dllimport)   
#endif  


