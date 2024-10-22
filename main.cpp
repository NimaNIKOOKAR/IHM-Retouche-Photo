#include "mainwindow.h"

#include <QApplication>
#include <QQuickStyle>
#include <QFile>
#include <colorpickerwidget.h>

QString getStyleSheet(const QString & path) {
    QFile file(path);
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    application.setStyleSheet(getStyleSheet(":/stylesheet/ressource/stylesheet/QTWhite.css"));

    MainWindow window;
    window.show();

    return application.exec();
}
