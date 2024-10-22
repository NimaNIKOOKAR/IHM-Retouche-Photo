#include "triangle.h"

namespace tool {
    Triangle::Triangle(const ColorPickerWidget & cp)
    : Selectionable(cp, "Triangle", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-triangle3.png"), true), _clicked(0,0), _hold(false), _multy(false) {

    }

    void Triangle::onMousePressed(ui::ImageArea &, ui::Selection & s, const QPoint & clicked, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(!this->_multy) {
            s.clear();
        }

        if(e.button() == Qt::LeftButton) {
            this->_clicked = clicked;
            this->_hold = true;
        }
    }

    void Triangle::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_hold = false;
        }
    }

    void Triangle::onMouseMoved(ui::ImageArea &, ui::Selection & s, const QPoint & position, const QImage & image, const QMouseEvent &, const ColorPickerWidget &, bool) {
        if(this->_hold) {
            s.clear();
            QVector<QPoint> selection;
            int rows = position.y() - this->_clicked.y();
            int x = 0;
            int decal = 1;

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < decal; j++) {
                    QPoint pos(x + j + this->_clicked.x(), i + this->_clicked.y());
                    if(image.rect().contains(pos)) {
                        selection.push_back(pos);
                    }

                    pos = QPoint(x - j + this->_clicked.x(), i + this->_clicked.y());
                    if(image.rect().contains(pos)) {
                        selection.push_back(pos);
                    }
                }
                decal++;
            }

            s.select(selection);
        }
    }

    void Triangle::onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = true;
            qDebug() << "ctrl";
        }
    }

    void Triangle::onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = false;
        }
    }
}
