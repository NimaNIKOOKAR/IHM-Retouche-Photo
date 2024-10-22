#include "rectangleTriangle.h"

namespace tool {
    RectangleTriangle::RectangleTriangle(const ColorPickerWidget & cp)
    : Selectionable(cp, "Triangle Rectangle", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-triangle.png"), true), _clicked(0,0), _hold(false), _multy(false) {

    }

    void RectangleTriangle::onMousePressed(ui::ImageArea &, ui::Selection & s, const QPoint & clicked, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(!this->_multy) {
            s.clear();
        }

        if(e.button() == Qt::LeftButton) {
            this->_clicked = clicked;
            this->_hold = true;
        }
    }

    void RectangleTriangle::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_hold = false;
        }
    }

    void RectangleTriangle::onMouseMoved(ui::ImageArea &, ui::Selection & s, const QPoint & position, const QImage & image, const QMouseEvent &, const ColorPickerWidget &, bool) {
        if(this->_hold) {
            s.clear();
            QVector<QPoint> selection;
            int rows = position.y() - this->_clicked.y();
            for(int i = 0; i < rows; i++) {
                for(int j  = 0; j <= i; j++) {
                    QPoint pixel = QPoint(this->_clicked.x() + j, this->_clicked.y() + i);
                    if(image.rect().contains(pixel)) {
                        selection.push_back(pixel);
                    }
                }
            }
            s.select(selection);
        }
    }

    void RectangleTriangle::onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = true;
            qDebug() << "ctrl";
        }
    }

    void RectangleTriangle::onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = false;
        }
    }
}
