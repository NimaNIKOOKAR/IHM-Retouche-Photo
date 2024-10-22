#include "clamp.h"

namespace ui {
    void Clamp::apply(const QPoint & point, const QColor & color, const QImage *, QImage * image) {
        QPoint newPoint(
            point.x() > image->width()-1 ? image->width()-1 : point.x(),
            point.y() > image->height()-1 ? image->height()-1 : point.y()
        );
        image->setPixelColor(newPoint, color);
    }
}
