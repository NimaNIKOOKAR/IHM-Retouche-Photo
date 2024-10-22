#include "selectionnable.h"

namespace tool {
    Selectionable::Selectionable(const ColorPickerWidget & cp, const QString & name, const QIcon & icon, bool free)
    : Tool(name, icon), _colorPicker(&cp) ,_free(free) {}

    void Selectionable::initialize(ui::ImageArea *) {}
    void Selectionable::onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &) {}
    void Selectionable::onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &) {}
    void Selectionable::onClear() {};

    void Selectionable::pressed(ui::ImageArea & area, QImage & image,  QPoint & click, ui::Selection & selection, QMouseEvent & e) {
        if(image.rect().contains(click) || this->_free) {
            this->onMousePressed(area, selection, click, image, e, *this->_colorPicker);
        }
    }

    void Selectionable::released(ui::ImageArea & area, QImage & image,  QPoint & click, ui::Selection & selection, QMouseEvent & e) {
        if(image.rect().contains(click) || this->_free) {
            this->onMouseReleased(area, selection, click, image, e, *this->_colorPicker);
        }
    }

    void Selectionable::moved(ui::ImageArea & area, QImage & image,  QPoint & click ,ui::Selection & selection, QMouseEvent & e, bool hold) {
        if(image.rect().contains(click) || this->_free) {
            this->onMouseMoved(area, selection, click, image, e, *this->_colorPicker, hold);
        }
    }

    void Selectionable::keyPressed(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QKeyEvent & e) {
        this->onKeyPress(area, selection, click, image, e, *this->_colorPicker);
    }

    void Selectionable::keyReleased(ui::ImageArea & area, QImage & image, QPoint & click, ui::Selection & selection, QKeyEvent & e) {
        this->onKeyReleased(area, selection, click, image, e, *this->_colorPicker);
    }

    void Selectionable::selectionCleared() {
        this->onClear();
    }
}
