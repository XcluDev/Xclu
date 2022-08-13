#include "xc_files.h"
#include "incl_cpp.h"
#include <QtGlobal>
#include <QDirIterator>

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
QStringList xc_folder_list_files(QString folder_name, QStringList extensions)
{
    if (!extensions.isEmpty()) {
        for (auto &s: extensions) {
            s = "*." + s;
        }
    }
    else {
        extensions << "*.*";
    }

    QStringList list;

    QDirIterator iter(folder_name, extensions); //, QDirIterator::Subdirectories);
    while (iter.hasNext()) {
        QString file = iter.next();
        list.push_back(file);
        //qDebug() << file;
    }
    return list;
}

//---------------------------------------------------------------------
QStringList xc_folder_list_files(QString folder_name, QString extension)
{
    QStringList extensions;
    if (!extension.isEmpty()) {
        extensions << extension;
    }
    return xc_folder_list_files(folder_name, extensions);
}

//---------------------------------------------------------------------
uint64 xc_file_size(QString file_name) {
    QFileInfo file(file_name);
    xc_assert(file.exists(), QString("xc_file_size error - file '%1' doesn't exists").arg(file_name));
    return file.size();
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
//Read binary file
//Use result.data() for data access
//read_bytes == -1 means read all file, if >=0 - read part of the file
QByteArray xc_read_binary_file(QString file_name, int read_bytes) {
    QFile file(file_name);
    xc_assert(file.open(QIODevice::ReadOnly), "Can't create file for reading: '" + file_name + "'");
    if (read_bytes == -1) {
        return file.readAll();
    }
    return file.read(read_bytes);
}


//---------------------------------------------------------------------
