#ifndef RECENTFILES_H
#define RECENTFILES_H

#include "incl_h.h"
#include <QObject>

QT_BEGIN_NAMESPACE
class QWidget;
class QAction;
class QMenu;
class QMenuBar;
class QSettings;
QT_END_NAMESPACE

class RecentFiles: public QObject
{
     Q_OBJECT
public:
    RecentFiles(QMenu *menu);

    static const int MaxRecentFiles = 10;
    QAction *recentFileActs[MaxRecentFiles];

    bool hasRecentFiles();
    void prependToRecentFiles(const QString &fileName);
    QStringList readRecentFiles(QSettings &settings);
    void writeRecentFiles(const QStringList &files, QSettings &settings);

public slots:
    void updateRecentFileActions();
    void openRecentFile();
};

#endif // RECENTFILES_H
