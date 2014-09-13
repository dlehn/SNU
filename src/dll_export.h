#ifndef DLL_EXPORT_H
#define DLL_EXPORT_H

#ifdef SNU_DLL_EXPORTS
#define SNU_PUBLIC _declspec(dllexport)
#else
#define SNU_PUBLIC _declspec(dllimport)
#endif

#endif