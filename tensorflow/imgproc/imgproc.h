#ifndef  TFAPI_EXPORTS
#define TFAPI_EXPORTS
#endif

#if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__) && defined TFAPI_EXPORTS
#  define TF_EXPORTS __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define TF_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define TF_EXPORTS
#endif

#ifndef TF_EXTERN_C
#  ifdef __cplusplus
#    define TF_EXTERN_C extern "C"
#  else
#    define TF_EXTERN_C
#  endif
#endif

#if defined WIN32 || defined _WIN32
#  define TF_CDECL __cdecl
#  define TF_STDCALL __stdcall
#else
#  define TF_CDECL
#  define TF_STDCALL
#endif

#ifndef TFAPI
#  define TFAPI(rettype) TF_EXTERN_C TF_EXPORTS rettype TF_CDECL
#endif

//#include <stddef.h>
//#include <stdint.h>
#include <cstdlib>
#include <cstring>


TFAPI(void) tfePixel32ToPixelFloat(unsigned char* pixels, int width, int height, float inputMean, float scale, bool flipUpsideDown, bool swapBR, float* result);

TFAPI(void) tfePixel32ToPixelByte(unsigned char* pixels, int width, int height, float inputMean, float scale, bool flipUpsideDown, bool swapBR, unsigned char* result);

TFAPI(void) tfePixel24ToPixelFloat(unsigned char* pixels, int width, int height, float inputMean, float scale, bool flipUpsideDown, bool swapBR, float* result);

TFAPI(void) tfePixel24ToPixelByte(unsigned char* pixels, int width, int height, float inputMean, float scale, bool flipUpsideDown, bool swapBR, unsigned char* result);
