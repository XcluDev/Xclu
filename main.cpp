#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QStyleFactory>
#include <QDebug>
#include <QMessageBox>

//для настройки антиалиасинга
#include <QSurfaceFormat>

#include "console.h"


int main(int argc, char *argv[])
{
    //Создание приложения
    QApplication app(argc, argv);

    //Запуск приложения с отловом исключений
    //Про отлов исключений:
    //https://doc.qt.io/qt-5/exceptionsafety.html
    //Чтобы что-то сохранилось при быстром выходе - aboutToQuit() signal.
    int result = -1;
    int except = 0;
    QString except_message = "";
    try {

        //тест - вывод шрифтов
        //xclu::print_fonts();

        //Установка темы
        XcluTheme::set_theme(&app);


        //Описание - используется для записи настроек QSettings
        QCoreApplication::setApplicationName("XCLU");
        QCoreApplication::setOrganizationName("XCLU");
        QCoreApplication::setOrganizationDomain("xclu.shop");
        QCoreApplication::setApplicationVersion("1.111");
        //QCommandLineParser parser;
        //parser.setApplicationDescription(QCoreApplication::applicationName());
        //parser.addHelpOption();
        //parser.addVersionOption();
        //parser.addPositionalArgument("file", "The file(s) to open.");
        //parser.process(app);

        //const QStringList posArgs = parser.positionalArguments();
        //for (const QString &file : posArgs) {
        //    MainWindow *newWin = new MainWindow(file);
        //    newWin->tile(mainWin);
        //    newWin->show();
        //    mainWin = newWin;
        //}


        //Антиалиасинг
        //QSurfaceFormat fmt;
        //fmt.setSamples(4);
        //QSurfaceFormat::setDefaultFormat(fmt);

        //-------------------------------------------
        MainWindow *mainWin = new MainWindow;
        mainWin->show();

        mainWin->setup();   //запуск процессов - считывание списка модулей, открытие файлов

        result = app.exec();
        //-------------------------------------------
    }
    catch(XCluException& e) {
        except = 1; except_message = QString("XClu exception:\n") +  e.whatQt();
    }
    catch(XCluCriticalException& e) {
        except = 1; except_message = QString("XClu critical exception:\n") +  e.whatQt();
    }
    catch(std::exception& e) {
        except = 1; except_message = QString("Exception:\n") + e.what();
    }
    catch(...) {
        except = 1; except_message = "Unhandled exception";
    }
    if (except) {
        QMessageBox msgBox;
        except_message += "\nExiting now...";
        msgBox.setText(except_message);
        msgBox.exec();
    }

    return result;


}
