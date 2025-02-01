#pragma once

//Работа с интерпретатором Python.

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

