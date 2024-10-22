#include "bucket.h"

namespace tool {
    Bucket::Bucket(const ColorPickerWidget & cp)
    : Editable(cp, "Pot de peinture", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/actions-fill-color-icon.png")) {}

    void Bucket::onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &) {}

    void Bucket::onMouseReleased(ui::ImageArea & a, QImage & i, const QPoint & p, const ui::Selection & s, const QMouseEvent & e, const ColorPickerWidget & cp) {
        if(e.button() == Qt::LeftButton) {
            this->fill(a, i, p, s, cp.currentColor());
        }
    }

    void Bucket::onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool) {

    }

    void Bucket::onKeyReleased(ui::ImageArea & area, QImage & img, const QPoint & click, const ui::Selection & selection, const QKeyEvent & e, const ColorPickerWidget & cp) {
        if(e.key() == Qt::Key_Return) {
            this->fill(area, img, click, selection, cp.currentColor());
        }
    }

    void Bucket::fill(ui::ImageArea & a, QImage & i, const QPoint & p, const ui::Selection & s, const QColor & color) {
        if(!s.empty() && s.contain(p)) {
            for(auto & point : s.selection()) {
                a.setColor(point, color);
            }
        }
        else {
            for(int x = 0; x < i.width(); x++) {
                for(int y = 0; y < i.height(); y++) {
                    a.setColor(QPoint(x,y), color);
                }
            }
        }
    }
}
