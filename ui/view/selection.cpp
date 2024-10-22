#include "selection.h"

#include <QDebug>

namespace ui {
    Selection::Selection(const QSet<QPoint> & preselection,const QColor & color)
        : _pixels(preselection), _color(color) {}

    void Selection::paint(QPainter & painter, const QPoint & position, const QImage & image, float zoom) {
        for(auto & pixel : this->_pixels) {
            if(image.rect().contains(pixel)) {
                painter.fillRect(position.x() + pixel.x() * zoom, position.y() + pixel.y() * zoom, zoom, zoom, this->_color);
            }
        }
    }

    void Selection::select(const QPoint & point) {
        this->_pixels.insert(point);
        emit this->selected(point);
    }

    void Selection::select(const QSet<QPoint> & selection) {
        for(auto & pixel : selection) {
            this->select(pixel);
        }
    }

    void Selection::select(const QVector<QPoint> & selection) {
        for(auto & pixel : selection) {
            this->select(pixel);
        }
    }

    void Selection::select(const QRect & selection) {
        for(int x = 0; x < selection.width(); x++) {
            for(int y = 0; y < selection.height(); y++) {
                this->select(QPoint(selection.x() + x, selection.y() + y));
            }
        }
    }

    void Selection::select(const QImage & image, const QColor & color) {
        for(int x = 0; x < image.width(); x++) {
            for(int y = 0; y < image.width(); y++) {
                if(image.pixel(x, y) == color.rgba()) {
                    this->select(QPoint(x, y));
                }
            }
        }
    }

    void Selection::unselect(const QPoint & point) {
        this->_pixels.erase(this->_pixels.find(point));
        emit this->unselected(point);
    }

    void Selection::unselect(const QSet<QPoint> & selection) {
        for(auto & pixel : selection) {
            this->unselect(pixel);
        }
    }

    void Selection::unselect(const QVector<QPoint> & selection) {
        for(auto & pixel : selection) {
            this->unselect(pixel);
        }
    }

    void Selection::unselect(const QRect & selection) {
        for(int x = selection.x(); x < selection.width(); x++) {
            for(int y = selection.y(); y < selection.height(); y++) {
                this->unselect(QPoint(x, y));
            }
        }
    }

    void Selection::unselect(const QImage & image, const QColor & color) {
        for(auto & point : this->_pixels) {
            if(image.pixel(point) == color.rgb()) {
                this->unselect(point);
            }
        }
    }

    void Selection::invert(const QImage & image) {
        this->invert(image.width(), image.height());
    }

    void Selection::invert(unsigned int w, unsigned int h) {
        QSet<QPoint> current = this->_pixels;
        this->clear();
        for(unsigned int x = 0; x < w; x++) {
            for(unsigned int y = 0; y < h; y++) {
                QPoint point = QPoint(x, y);
                if(!current.contains(point)) {
                    this->select(point);
                }
            }
        }
    }

    void Selection::clear(bool silent) {
        this->_pixels.clear();
        if(!silent) {
            emit this->cleared();
        }
    }
}
