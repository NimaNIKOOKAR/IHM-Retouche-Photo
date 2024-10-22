#include "filemenulambda.h"

#include <QApplication>
#include <QDebug>

namespace ui {
    FilemenuLambda::FilemenuLambda(FileSelector * fileselector, ViewManager * manager)
    : _fileSelector(fileselector), _viewManager(manager) {}

    FilemenuLambda::~FilemenuLambda() {}

    void FilemenuLambda::initializeMenu(const QMenu * menu) {
        QObject::connect(menu->actions().at(Actions::QUIT), SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
        QObject::connect(menu->actions().at(Actions::OPEN), SIGNAL(triggered()), this->_fileSelector, SLOT(pushItem()));
        QObject::connect(menu->actions().at(Actions::OPEN_DIR), SIGNAL(triggered()), this->_fileSelector, SLOT(setTreeRootPath()));

        QObject::connect(menu->actions().at(Actions::SAVE), SIGNAL(triggered()), this->_viewManager, SLOT(saveCurrentView()));
        QObject::connect(menu->actions().at(Actions::SAVE_AS), SIGNAL(triggered()), this->_viewManager, SLOT(saveAsCurrentView()));
        QObject::connect(menu->actions().at(Actions::SAVE_ALL), SIGNAL(triggered()), this->_viewManager, SLOT(saveAll()));
        QObject::connect(menu->actions().at(Actions::NEW), SIGNAL(triggered()), this->_viewManager, SLOT(newView()));

        QObject::connect(menu->actions().at(Actions::CLOSE), SIGNAL(triggered()), this->_viewManager, SLOT(deleteCurrentView()));
    }
}
