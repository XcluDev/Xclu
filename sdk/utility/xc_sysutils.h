#ifndef XCLU_SYSUTILS_H
#define XCLU_SYSUTILS_H

#include "incl_h.h"

// Sleep in the current thread
void xc_sleep_sec(float sec);
void xc_sleep_ms(int ms);

// Shutdown computer
void xc_system_shutdown();


#endif // XCLU_SYSUTILS_H
