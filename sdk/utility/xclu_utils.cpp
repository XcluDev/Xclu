#include "xclu_utils.h"
#include "incl_cpp.h"
#include <QtGlobal>

//---------------------------------------------------------------------
//замена подчеркивания на пробел в заголовках: Abc_Def -> "Abc Def"
QString xclu_remove_underscore(QString title) {
    return title.replace('_', ' ');
}

//---------------------------------------------------------------------
QStringList xclu_read_text_file(QString file_name) {
    xclu_assert(QFileInfo(file_name).exists(), "xclu_read_text_file: file doesn't exists, `" + file_name + "`");
    QFile textFile(file_name);
    xclu_assert(textFile.open(QFile::ReadOnly), "xclu_read_text_file: Can't open `" + file_name + "'");
    QTextStream in(&textFile);

    QStringList list;
    while(!in.atEnd()) {
        QString line = in.readLine();
        list.append(line);
    }
    textFile.close();

    return list;
}

//---------------------------------------------------------------------
void xclu_write_text_file(QStringList list, QString file_name) {
    QFile textFile(file_name);
    xclu_assert(textFile.open(QFile::WriteOnly | QFile::Truncate), "xclu_write_text_file: Can't write to `" + file_name + "'");
    QTextStream out(&textFile);

    for (auto &s: list) {
         out << s << endl;
     }
     textFile.close();
}

//---------------------------------------------------------------------
