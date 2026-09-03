#ifndef C_PREPROCESSOR_GNU_TYPEOF_H

// Local Includes
#include <preprocessor/stdc_version.h>

#if defined(__GNUC__)
    #define c_pp_gnu_typeof __typeof__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= C_PP_STDC_VERSION_23)
    #define c_pp_gnu_typeof typeof
#else
    #define c_pp_gnu_typeof
#endif // #if defined(__GNUC__)

#endif // #ifndef C_PREPROCESSOR_GNU_TYPEOF_H
