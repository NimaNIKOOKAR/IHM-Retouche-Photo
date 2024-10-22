#include "editable.h"

namespace tool {
    Editable::Editable(const ColorPickerWidget & cp, const QString & name, const QIcon & icon, bool free)
    : Tool(name, icon), _colorPicker(&cp), _free(free) {}

    void Editable::initialize(ui::ImageArea *) {}
    void Editable::onKeyPress(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &) {}
    void Editable::onKeyReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &) {}

    void Editable::pressed(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QMouseEvent & e) {
        if(image.rect().contains(click) || this->_free) {
            this->onMousePressed(area, image, click, selection, e, *this->_colorPicker);
        }
    }

    void Editable::released(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QMouseEvent & e) {
        if(image.rect().contains(click) || this->_free) {
            this->onMouseReleased(area, image, click, selection, e, *this->_colorPicker);
        }
    }

    void Editable::moved(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QMouseEvent & e, bool hold) {
        if(image.rect().contains(click) || this->_free) {
            this->onMouseMoved(area, image, click, selection, e, *this->_colorPicker, hold);
        }
    }

    void Editable::keyPressed(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QKeyEvent & e) {
        this->onKeyPress(area, image, click, selection, e, *this->_colorPicker);
    }

    void Editable::keyReleased(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QKeyEvent & e) {
        this->onKeyReleased(area, image, click, selection, e, *this->_colorPicker);
    }

    void Editable::selectionCleared() {}
}
