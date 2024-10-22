#include "selectionmenulambda.h"

namespace ui {
    SelectionMenuLambda::SelectionMenuLambda(ViewManager * manager)
    : _menu(nullptr), _manager(manager) {

    }

    void SelectionMenuLambda::initializeMenu(const QMenu * menu) {
        this->_menu = menu;
        QObject::connect(this->_manager, SIGNAL(changedView(ImageArea*)), this, SLOT(viewChanged(ImageArea*)));
    }

    void SelectionMenuLambda::viewChanged(ImageArea * area) {
        if(area != nullptr && this->_menu != nullptr) {
            QObject::connect(this->_menu->actions().at(Actions::SUPPR), SIGNAL(triggered()), area, SLOT(deleteCurrentSelection()));
            QObject::connect(this->_menu->actions().at(Actions::UNSELECT), SIGNAL(triggered()), &area->selection(), SLOT(clear()));
        }
    }
}
