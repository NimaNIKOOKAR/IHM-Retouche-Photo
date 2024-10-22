#include "ellipse.h"

namespace tool {
    Ellipse::Ellipse(const ColorPickerWidget & cp)
    : Selectionable(cp, "Ellipse", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-ellipse.png"), true), _clicked(0,0), _hold(false), _multy(false) {

    }

    void Ellipse::onMousePressed(ui::ImageArea &, ui::Selection & s, const QPoint & clicked, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(!this->_multy) {
            s.clear();
        }

        if(e.button() == Qt::LeftButton) {
            this->_clicked = clicked;
            this->_hold = true;
        }
    }

    void Ellipse::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_hold = false;
        }
    }

    void Ellipse::onMouseMoved(ui::ImageArea &, ui::Selection & s, const QPoint & c, const QImage & img, const QMouseEvent &, const ColorPickerWidget &, bool) {
        if(this->_hold) {
            s.clear();
            QVector<QPoint> selection;

            int cx = this->_clicked.x();
            int cy = this->_clicked.y();

            int width = c.x() - this->_clicked.x();
            int height = c.y() - this->_clicked.y();

            for(int i = 0; i < width; i++) {
                int dx = i - width / 2;
                int x = cx + dx;

                int h = qRound(height * qSqrt(width * width / 4.0 - dx * dx) / width);
                for(int dy = 1; dy < h; dy++) {
                    QPoint p(x, cy + dy);
                    if(img.rect().contains(p)) {
                        selection.push_back(p);
                    }

                    p = QPoint(x, cy - dy);
                    if(img.rect().contains(p)) {
                        selection.push_back(p);
                    }
                }

                if(h >= 0) {
                    QPoint p(x, cy);
                    if(img.rect().contains(p)) {
                        selection.push_back(p);
                    }
                }
            }

            s.select(selection);
        }
    }

    void Ellipse::onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = true;
            qDebug() << "ctrl";
        }
    }

    void Ellipse::onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_multy = false;
        }
    }
}
