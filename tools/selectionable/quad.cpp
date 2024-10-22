#include "quad.h"

namespace tool {
    Quad::Quad(const ColorPickerWidget & cp)
        : Selectionable(cp, "Quadrilatère", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-quad.png"), true) {

    }

    void Quad::initialize(ui::ImageArea *) {
        this->_polygon.clear();
    }

    void Quad::onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &) {

    }

    void Quad::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint & clicked, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            if(this->_polygon.count() >= 4) {
                this->_polygon.clear();
            }
            this->_polygon << clicked;
        }
    }

    void Quad::onMouseMoved(ui::ImageArea &, ui::Selection & s, const QPoint & clicked, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool) {
        s.clear();
        QPolygon poly = this->_polygon;

        if(this->_polygon.count() < 4) {
            poly << clicked;
        }

        QRect boundingBox = poly.boundingRect();
        for(int x = 0; x < boundingBox.width(); x++) {
            for(int y = 0; y < boundingBox.height(); y++) {
                QPoint p(boundingBox.x() + x, boundingBox.y() + y);
                if(poly.containsPoint(p, Qt::FillRule::OddEvenFill)) {
                    s.select(p);
                }
            }
        }
    }

    void Quad::onClear() {
        this->_polygon.clear();
    }
}
