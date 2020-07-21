#include "python/pythoncore.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "incl_qtcpp.h"

PythonCore PYTHON;

//про отложенный запуск DLL
//https://stackoverflow.com/questions/39112148/deploy-a-qt-c-shared-librarys-dll-in-subfolder-of-the-main-executable

//Проект по встраиванию питона
//https://code.qt.io/cgit/pyside/pyside-setup.git/tree/examples/scriptableapplication

//Добавить путь для запуска:
//set PATH=%PATH%;D:\perevalovds.com\_2020\Xclu\Xclu-bin\Python38;D:\perevalovds.com\_2020\Xclu\Xclu-bin\Python38\DLLs

//---------------------------------------------------------------------
void PythonCore::setup() {

    //wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    //if (program == NULL) {
    //    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    //   exit(1);
    //}
    qDebug() << "Python startup...";

    //QString prog_name = QString("progr");
    //Py_SetProgramName((wchar_t*)prog_name.utf16());  // optional but recommended
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print('Today is', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        qDebug() << "Python error" << endl;
        exit(120);
    }
    //PyMem_RawFree((wchar_t*)prog_name.utf16());   //Free memory!

}

//---------------------------------------------------------------------
