#pragma once

//Работа с интерпретатором Python.
//В данный момент - приостановлено.

class PythonCore
{
public:
    void setup();
    void free();

private:
    void test1();
    void test2();
};

extern PythonCore PYTHON;

