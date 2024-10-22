#include "polygone.h"

namespace tool {
    Polygone::Polygone(const ColorPickerWidget & cp)
    : Selectionable(cp, "Polygone", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-polygon.png"), true), _preview(true) {

    }

    void Polygone::initialize(ui::ImageArea *) {
        this->_polygon.clear();
    }

    void Polygone::onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &) {

    }

    void Polygone::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint & clicked, const QImage &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            if(this->_preview == false) {
                this->_polygon.clear();
            }
            this->_preview = true;
            this->_polygon << clicked;
        }
        else if(e.button() == Qt::RightButton) {
            this->_preview = false;
        }
    }

    void Polygone::onMouseMoved(ui::ImageArea &, ui::Selection & s, const QPoint & clicked, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool) {
        s.clear();
        QPolygon poly = this->_polygon;

        if(this->_preview) {
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

    void Polygone::onClear() {
        this->_polygon.clear();
    }
}
