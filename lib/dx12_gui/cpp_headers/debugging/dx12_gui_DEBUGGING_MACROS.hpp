#pragma once

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif











// prevent problems in other headers that may use TRUE (windows.h)
#ifdef TRUE
#undef TRUE
#endif

// prevent problems in other headers that may use FALSE (windows.h)
#ifdef FALSE
#undef FALSE
#endif