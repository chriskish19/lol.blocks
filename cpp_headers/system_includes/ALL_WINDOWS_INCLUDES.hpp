#pragma once
// all windows includes here

#include <windows.h>
#include <wrl.h> // microsoft com_ptr

// avoid conflicts with stl...
#if defined(min)
#undef min
#endif
#if defined(max)
#undef max
#endif