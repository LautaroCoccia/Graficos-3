#ifndef EXPORT_H
	#define EXPORT_API __declspec(dllexport)
#else
	#define EXPORT_API __declspec(dllimport)
#endif