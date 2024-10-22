#include "imagemenulambda.h"

namespace ui {
    ImageMenuLambda::ImageMenuLambda(dialog::ReScaleDialog * rescale, dialog::ReSizeDialog * resize,ViewManager * manager)
    : _menu(nullptr), _rescale(rescale), _resize(resize), _viewManager(manager), _area(nullptr) {
        QObject::connect(this->_viewManager, SIGNAL(changedView(ImageArea*)), this, SLOT(viewChange(ImageArea*)));
    }

    void ImageMenuLambda::initializeMenu(const QMenu * menu) {
        this->_menu = menu;
    }

    void ImageMenuLambda::viewChange(ImageArea * area) {
        if(this->_menu != nullptr) {
            if(this->_area != nullptr) {
                QObject::disconnect(this->_menu->actions().at(Actions::RESIZE), SIGNAL(triggered()), this->_resize, SLOT(use()));
                QObject::disconnect(this->_menu->actions().at(Actions::RESCALE), SIGNAL(triggered()), this->_rescale, SLOT(use()));
                QObject::disconnect(this->_menu->actions().at(Actions::TURN)->menu()->actions().at(0), SIGNAL(triggered()), this, SLOT(turn_V()));
                QObject::disconnect(this->_menu->actions().at(Actions::TURN)->menu()->actions().at(1), SIGNAL(triggered()), this, SLOT(turn_H()));
                QObject::disconnect(this->_menu->actions().at(Actions::ROTATE)->menu()->actions().at(0), SIGNAL(triggered()), this, SLOT(turn_left()));
                QObject::disconnect(this->_menu->actions().at(Actions::ROTATE)->menu()->actions().at(1), SIGNAL(triggered()), this, SLOT(turn_right()));
            }

            this->_area = area;

            if(this->_area != nullptr) {
                QObject::connect(this->_menu->actions().at(Actions::RESIZE), SIGNAL(triggered()), this->_resize, SLOT(use()));
                QObject::connect(this->_menu->actions().at(Actions::RESCALE), SIGNAL(triggered()), this->_rescale, SLOT(use()));
                QObject::connect(this->_menu->actions().at(Actions::TURN)->menu()->actions().at(0), SIGNAL(triggered()), this, SLOT(turn_V()));
                QObject::connect(this->_menu->actions().at(Actions::TURN)->menu()->actions().at(1), SIGNAL(triggered()), this, SLOT(turn_H()));
                QObject::connect(this->_menu->actions().at(Actions::ROTATE)->menu()->actions().at(0), SIGNAL(triggered()), this, SLOT(turn_left()));
                QObject::connect(this->_menu->actions().at(Actions::ROTATE)->menu()->actions().at(1), SIGNAL(triggered()), this, SLOT(turn_right()));
            }
        }
    }

    void ImageMenuLambda::turn_H() {
        if(this->_area != nullptr) {
            QTransform t;
            t.rotate(180, Qt::XAxis);
            this->_area->transform(t);
        }
    }

    void ImageMenuLambda::turn_V() {
        if(this->_area != nullptr) {
            QTransform t;
            t.rotate(180, Qt::YAxis);
            this->_area->transform(t);
        }
    }

    void ImageMenuLambda::turn_left() {
        if(this->_area != nullptr) {
            QTransform t;
            t.rotate(-90);
            this->_area->transform(t);
        }
    }

    void ImageMenuLambda::turn_right() {
        if(this->_area != nullptr) {
            QTransform t;
            t.rotate(90);
            this->_area->transform(t);
        }
    }
}
