#include "rectangle.h"

namespace tool {
    Rectangle::Rectangle(const ColorPickerWidget & cp)
    : Selectionable(cp, "Rectangle", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-rectangle.png"), true), _clicked(0,0), _hold(false), _multy(false) {

    }

    void Rectangle::onMousePressed(ui::ImageArea &, ui::Selection & s, const QPoint & clicked, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(!this->_multy) {
            s.clear();
        }

        if(e.button() == Qt::LeftButton) {
            this->_clicked = clicked;
            this->_hold = true;
        }
    }

    void Rectangle::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_hold = false;
        }
    }

    void Rectangle::onMouseMoved(ui::ImageArea &, ui::Selection & s, const QPoint & c, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool) {
        if(this->_hold) {
            s.clear();
            if(this->_clicked.x() < c.x() || this->_clicked.y() < c.y()) {
                s.select(QRect(this->_clicked, c));
            }
            else {
                s.select(QRect(c, this->_clicked));
            }
        }
    }

    void Rectangle::onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = true;
            qDebug() << "ctrl";
        }
    }

    void Rectangle::onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = false;
        }
    }
}
