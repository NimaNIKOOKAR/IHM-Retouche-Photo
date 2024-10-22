#include "blackandwhite.h"

#include <QDebug>

namespace effect {
    BlackAndWhite::BlackAndWhite() {}

    BlackAndWhite::~BlackAndWhite() {}

    void BlackAndWhite::apply(const QSet<QPoint> & points, QImage & image) const {
        if (image.isNull()) {
            qDebug() << "L'image est vide.";
            return;
        }

        for(auto & pixel : points) {
            int luminance = qGray(image.pixelColor(pixel).rgb());
            QColor newColor(luminance, luminance, luminance);
            image.setPixelColor(pixel, newColor);
        }

        qDebug() << "Conversion en noir et blanc effectuée.";
    }
}
