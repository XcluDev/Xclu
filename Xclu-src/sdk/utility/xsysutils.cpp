#include "xfiles.h"
#include "incl_cpp.h"
#include <QtGlobal>
#include <QThread>

//---------------------------------------------------------------------
// Sleep in the current thread
void xc_sleep_sec(float sec) {
    QThread::msleep(int(sec*1000));
}

//---------------------------------------------------------------------
void xc_sleep_thread_ms(int ms) {
    QThread::msleep(ms);
}

//---------------------------------------------------------------------
//Shutdown computer
void xc_system_shutdown() {
#ifdef XCLU_WINDOWS
        system("shutdown /s");
#endif
#ifdef XCLU_LINUX
        system("shutdown now");
#endif
}


//---------------------------------------------------------------------
