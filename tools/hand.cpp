#include "hand.h"

namespace tool {
    Hand::Hand(const ColorPickerWidget & cp)
    : Editable(cp, "Main", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/transform-move.png"), true), _leftButton(false) {}

    void Hand::onMousePressed(ui::ImageArea & area, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            area.setCursor(QCursor(Qt::CursorShape::ClosedHandCursor));
            this->_leftButton = true;
        }
    }

    void Hand::onMouseReleased(ui::ImageArea & area, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            area.setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
            area.setLast_Positon(e.pos());
            this->_leftButton = false;
        }
    }

    void Hand::onMouseMoved(ui::ImageArea & area, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &, bool hold) {
        if(hold && this->_leftButton) {
            QPoint move = e.pos() - area.last_position();
            area.setPosition(QPoint(area.position().x() + move.x(),area.position().y() + move.y()));
            area.setLast_Positon(e.pos());
        }
    }
}
