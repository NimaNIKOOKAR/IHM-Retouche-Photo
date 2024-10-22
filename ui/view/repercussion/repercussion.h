#pragma once

#include <QString>
#include <QPoint>
#include <QImage>
#include <QListWidgetItem>

namespace ui {
    class Repercution : public QListWidgetItem {
        public:
            Repercution(const QString & name) : QListWidgetItem(name) {}
   virtual ~Repercution() {}

            virtual void apply(const QPoint &, const QColor &, const QImage *, QImage *) = 0;
    };
}
