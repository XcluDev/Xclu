#include "python/pythoncore.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "incl_qtcpp.h"

PythonCore PYTHON;

/*
про отложенный запуск DLL
https://stackoverflow.com/questions/39112148/deploy-a-qt-c-shared-librarys-dll-in-subfolder-of-the-main-executable

Проект по встраиванию питона
https://code.qt.io/cgit/pyside/pyside-setup.git/tree/examples/scriptableapplication

Добавить путь для запуска в BAT, на один раз:
set PYTHONHOME="D:\perevalovds.com\_2020\Xclu\Xclu-bin\Python38"
set PYTHONPATH="...Python38;...Python38\DLLs;...Python38\Lib;...Python38\site-packages"
(вместо многоточий - полный путь)
В PATH добавить
...Python38
...Python38\DLLs
...Python38\Lib
...Python38\site-packages
...Python38\Scripts

Для разработки - добавил в глобальный Path пути к питону.
А для запуска на других компьютерах - нужно будет добавлять при запуске, сделать отложенный запуск DLL.
Сделать программу-запускатель,
которая ставит PATH и затем запускает нашу программу.

Примеры работы C++->Python:
https://docs.python.org/3/extending/embedding.html


*/



//---------------------------------------------------------------------
void PythonCore::setup() {
    //test1();
    test2();
}

//---------------------------------------------------------------------
//https://docs.python.org/3/extending/embedding.html
void PythonCore::test1() {

    //wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    //if (program == NULL) {
    //    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    //   exit(1);
    //}
    qDebug() << "Python startup...";

    //QString prog_name = QString("progr");
    //Py_SetProgramName((wchar_t*)prog_name.utf16());  // optional but recommended
    Py_Initialize();

    qDebug() << "   run script...";
    PyRun_SimpleString("from time import time,ctime\n"
                       "print('Today is', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        qDebug() << "Python error" << endl;
        exit(120);
    }
    qDebug() << "finished...";
    //PyMem_RawFree((wchar_t*)prog_name.utf16());   //Free memory!


}

//---------------------------------------------------------------------
void PythonCore::free() {
    Py_Finalize();
}

//---------------------------------------------------------------------
void PythonCore::test2() {
  /*  PyObject *pName, *pModule, *pFunc;
        PyObject *pArgs, *pValue;
        int i;

        if (argc < 3) {
            fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
            return 1;
        }

        Py_Initialize();
        pName = PyUnicode_DecodeFSDefault(argv[1]);
        //Error checking of pName left out

        pModule = PyImport_Import(pName);
        Py_DECREF(pName);

        if (pModule != NULL) {
            pFunc = PyObject_GetAttrString(pModule, argv[2]);
            //pFunc is a new reference

            if (pFunc && PyCallable_Check(pFunc)) {
                pArgs = PyTuple_New(argc - 3);
                for (i = 0; i < argc - 3; ++i) {
                    pValue = PyLong_FromLong(atoi(argv[i + 3]));
                    if (!pValue) {
                        Py_DECREF(pArgs);
                        Py_DECREF(pModule);
                        fprintf(stderr, "Cannot convert argument\n");
                        return 1;
                    }
                    //pValue reference stolen here:
                    PyTuple_SetItem(pArgs, i, pValue);
                }
                pValue = PyObject_CallObject(pFunc, pArgs);
                Py_DECREF(pArgs);
                if (pValue != NULL) {
                    printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                    Py_DECREF(pValue);
                }
                else {
                    Py_DECREF(pFunc);
                    Py_DECREF(pModule);
                    PyErr_Print();
                    fprintf(stderr,"Call failed\n");
                    return 1;
                }
            }
            else {
                if (PyErr_Occurred())
                    PyErr_Print();
                fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
            }
            Py_XDECREF(pFunc);
            Py_DECREF(pModule);
        }
        else {
            PyErr_Print();
            fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
            return 1;
        }
        if (Py_FinalizeEx() < 0) {
            return 120;
        }
    */
}

//---------------------------------------------------------------------

