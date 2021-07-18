#include "xc_files.h"
#include "incl_cpp.h"
#include <QtGlobal>

//---------------------------------------------------------------------
bool xc_file_exists(QString file_name) {
    return QFileInfo::exists(file_name);
    //return QFile(file_name).exists();
}

//---------------------------------------------------------------------
bool xc_folder_exists(QString folder_name) {
    return QDir(folder_name).exists();
}

//---------------------------------------------------------------------
QStringList xc_read_text_file(QString file_name) {
    xc_assert(QFileInfo(file_name).exists(), "xclu_read_text_file: file doesn't exists, `" + file_name + "`");
    QFile textFile(file_name);
    xc_assert(textFile.open(QFile::ReadOnly), "xclu_read_text_file: Can't open `" + file_name + "'");
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
void xc_write_text_file(QStringList list, QString file_name) {
    QFile textFile(file_name);
    xc_assert(textFile.open(QFile::WriteOnly | QFile::Truncate), "xclu_write_text_file: Can't write to `" + file_name + "'");
    QTextStream out(&textFile);

    for (auto &s: list) {
         out << s << endl;
     }
     textFile.close();
}

//---------------------------------------------------------------------
void xc_write_binary_file(const void *data, int n, QString file_name, bool append) {
    QFile file(file_name);
    xc_assert(file.open( (append)?
                             (QIODevice::WriteOnly | QIODevice::Append)
                             : QIODevice::WriteOnly),
              "Can't create file for writing: '" + file_name + "'");
    int written = file.write((const char *)data, n);
    xc_assert(n == written, QString("Not all data is written to file, want to write %1, but written %2")
              .arg(n).arg(written));
    file.close();
}

//---------------------------------------------------------------------
