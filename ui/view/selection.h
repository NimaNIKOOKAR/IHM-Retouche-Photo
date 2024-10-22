#pragma once

#include <QObject>
#include <QSet>
#include <QPoint>
#include <QPainter>

namespace ui {
    class Selection : public QObject {
        Q_OBJECT
        private:
            QSet<QPoint> _pixels;
            QColor _color;

        public:
            Selection(const QSet<QPoint> & = {}, const QColor & = QColor(0, 148, 255, 96));

            inline const QSet<QPoint> selection() const {return this->_pixels;}

            void paint(QPainter &, const QPoint &, const QImage &, float);

            void select(const QPoint &);
            void select(const QSet<QPoint> &);
            void select(const QVector<QPoint> &);
            void select(const QRect &);
            void select(const QImage &, const QColor &);

            void unselect(const QPoint &);
            void unselect(const QSet<QPoint> &);
            void unselect(const QVector<QPoint> &);
            void unselect(const QRect &);
            void unselect(const QImage &, const QColor &);

            void invert(const QImage &);
            void invert(unsigned int, unsigned int);

            inline bool contain(const QPoint & point) const {return this->_pixels.contains(point);};
            inline bool empty() const {return this->_pixels.empty();}

        public slots:
            void clear(bool silent = true);

        signals:
            void selected(const QPoint &);
            void unselected(const QPoint &);
            void cleared();
    };
}
