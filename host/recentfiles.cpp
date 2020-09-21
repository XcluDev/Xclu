#include <QtWidgets>
#include "incl_cpp.h"
#include "recentfiles.h"
#include "mainwindow.h"

//---------------------------------------------------------------------
RecentFiles::RecentFiles(QMenu *menu)
{
    connect(menu, &QMenu::aboutToShow, this, &RecentFiles::updateRecentFileActions);

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = menu->addAction(QString(), this, &RecentFiles::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }

}

//---------------------------------------------------------------------
void RecentFiles::updateRecentFileActions() {
    //QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    XCLU_SETTINGS

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for ( ; i < count; ++i) {
        const QString fileName = QFileInfo(recentFiles.at(i)).fileName();
        recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        recentFileActs[i]->setData(recentFiles.at(i));
        recentFileActs[i]->setVisible(true);
    }
    for ( ; i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);
}

//---------------------------------------------------------------------
void RecentFiles::openRecentFile() {
    if (const QAction *action = qobject_cast<const QAction *>(sender())) {
        if (!MainWindow::window()->maybeSave()) return;
        MainWindow::window()->openProject(action->data().toString());
    }
}

//---------------------------------------------------------------------
QStringList RecentFiles::readRecentFiles(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(Settings::recentProjects());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        result.append(settings.value(Settings::file()).toString());
    }
    settings.endArray();
    return result;
}

//---------------------------------------------------------------------
void RecentFiles::writeRecentFiles(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(Settings::recentProjects());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        settings.setValue(Settings::file(), files.at(i));
    }
    settings.endArray();
}

//---------------------------------------------------------------------
bool RecentFiles::hasRecentFiles() {
    //QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    XCLU_SETTINGS
    const int count = settings.beginReadArray(Settings::recentProjects());
    settings.endArray();
    return count > 0;
}

//---------------------------------------------------------------------
void RecentFiles::prependToRecentFiles(const QString &fileName) {
    //QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    XCLU_SETTINGS

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    MainWindow::window()->updateMenusVisible();
}

//---------------------------------------------------------------------


