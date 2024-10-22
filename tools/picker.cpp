#include "picker.h"

namespace tool {
    Picker::Picker(const ColorPickerWidget & cp)
    : Editable(cp, "Pipette", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/color-picker.png"), true) {
        QObject::connect(this, SIGNAL(colorPicked(QColor)), &cp, SLOT(addColor(QColor)));
    }

    Picker::~Picker() {
        QObject::connect(this, SIGNAL(colorPicked(QColor)), this->colorPicker(), SLOT(addColor(QColor)));
    }

    void Picker::onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &) {

    }

    void Picker::onMouseReleased(ui::ImageArea &, QImage & i, const QPoint & p, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            emit this->colorPicked(i.pixelColor(p));
        }
    }

    void Picker::onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool) {

    }
}
