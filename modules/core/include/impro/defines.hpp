#ifndef IMPRO_DEFINES_HPP
#define IMPRO_DEFINES_HPP

#if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__) && defined IMPROAPI_EXPORTS
#  define IMPRO_EXPORTS __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define IMPRO_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define IMPRO_EXPORTS
#endif

#ifndef IMPRO_EXTERN_C
#  ifdef __cplusplus
#    define IMPRO_EXTERN_C extern "C"
#  else
#    define IMPRO_EXTERN_C
#  endif
#endif

#endif // IMPRO_DEFINES_HPP

