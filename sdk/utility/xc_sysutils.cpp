#include "xc_files.h"
#include "incl_cpp.h"
#include <QtGlobal>

//---------------------------------------------------------------------
//Shutdown computer
void xc_system_shutdown() {
#ifdef XCLU_WIN
        system("shutdown /s");
#endif
#ifdef XCLU_LINUX
        system("shutdown now");
#endif
}


//---------------------------------------------------------------------
