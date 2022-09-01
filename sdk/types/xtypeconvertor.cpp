#include "xtypeconvertor.h"

#include "xarray.h"
#include "xraster.h"
#include "xsoundtypes.h"
#include "xcalldatatypes.h"

//---------------------------------------------------------------------
#define  XTYPEDEF(name, id) template<> XType cpptype_to_XType<name>() { return XType::name; }
XTYPESLIST
#undef  XTYPEDEF
//---------------------------------------------------------------------

