#include "ignore.h"

namespace ui {
    void Ignore::apply(const QPoint & point, const QColor & color, const QImage *, QImage * image) {
        if(image->rect().contains(point)) {
            image->setPixelColor(point, color);
        }
    }
}
