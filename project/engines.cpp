#include "engines.h"
#include "pythoncore.h"

Engines ENGINES;

//---------------------------------------------------------------------
void Engines::setup() {
    PYTHON.setup();
}

//---------------------------------------------------------------------
void Engines::free() {
    PYTHON.free();
}

//---------------------------------------------------------------------

