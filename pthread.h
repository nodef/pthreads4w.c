#pragma once
#include "pthreads4w/pthread.h"

#ifdef PTHREADS4W_IMPLEMENTATION
#define HAVE_CONFIG_H
#define __PTW32_STATIC_LIB
#include "pthreads4w/pthread.c"
#undef HAVE_CONFIG_H
#endif
