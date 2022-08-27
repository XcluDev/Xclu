#include "xtypeutils.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
QString XTypeUtils::to_string(int i, int N, const QString array[]) {
    xc_assert(i >= 0 && i < N, QString("Can't convert type index %1 to string %2")
                                         .arg(i).arg(array[0] + "," + array[1] + ",..."));
    return array[i];
}


//---------------------------------------------------------------------
// TODO Now realization works using linear search,
// it's better to use hashmaps

int XTypeUtils::to_type(const QString &str, int N, const QString array[]) {
    //TODO ускорить через Map
    for (int i=0; i<N; i++) {
        if (str == array[i]) return i;
    }
    xc_exception(QString("Can't convert string '%1' to type %2")
                   .arg(str).arg(array[0] + "," + array[1] + ",..."));
    return 0;
}
