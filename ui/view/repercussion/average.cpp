#include "average.h"

namespace ui {
    void Average::apply(const QPoint & point, const QColor & color, const QImage * origin, QImage * image) {
        QPoint newPoint(point.x() * image->width() / origin->width(), point.y() * image->height() / origin->height());
        image->setPixelColor(newPoint, color);
    }
}
