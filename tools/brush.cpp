#include "brush.h"

#include <QDebug>

namespace tool {
    Brush::Brush()
        : Tool("Brush", QIcon(":/image/test/icons/16x16/ressource/image/test/icons/16x16/Circle.png")) {

    }

    Brush::Brush(QListWidget *)
        : Tool("Brush", QIcon(":/image/test/icons/16x16/ressource/image/test/icons/16x16/Circle.png")) {

    }

    void Brush::use() const {
        qDebug() << "Hello Brush";
    }
}
