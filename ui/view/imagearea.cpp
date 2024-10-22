#include "imagearea.h"

#include <QKeySequence>
#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <cmath>

#include <QColorTransform>

#include "../effect/contrast.h"
#include "../effect/blackandwhite.h"

namespace ui {
    ImageArea::ImageArea()
    : _selection(),
      _fileinfo(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/New"),
      _image(800, 600, QImage::Format_RGBA32FPx4),
      _checkboard(ImageArea::Generate_Checkboard(4, 4, 16)),
      _transformation(),
      _position(0, 0),
      _lastPos(0, 0),
      _pixelPosition(0, 0),
      _repercution(nullptr),
      _zoom(1.f),
      _status(NEW),
      _mouseClickHold(false),
      _emitModification(false),
      _receiveModification(true) {
        this->setMouseTracking(true);
        this->setFocusPolicy(Qt::StrongFocus);
        this->_image.fill(QColorConstants::White);
    }

    ImageArea::ImageArea(const QFileInfo & info, QWidget *)
    : _selection(),
      _fileinfo(info),
      _image(info.absoluteFilePath()),
      _checkboard(ImageArea::Generate_Checkboard(4, 4, 16)),
      _transformation(),
      _position(0, 0),
      _lastPos(0, 0),
      _pixelPosition(0, 0),
      _repercution(nullptr),
      _zoom(1.f),
      _status(ORIGINAL),
      _mouseClickHold(false),
      _emitModification(false),
      _receiveModification(true) {
        this->setMouseTracking(true);
        this->setFocusPolicy(Qt::StrongFocus);
        this->_image = this->_image.convertToFormat(QImage::Format_RGBA32FPx4);
    }

    void ImageArea::paintEvent(QPaintEvent * e) {
        QWidget::paintEvent(e);
        QPainter painter(this);

        QRect drawZone(
            this->_position.x(),
            this->_position.y(),
            this->_image.width() * this->_zoom,
            this->_image.height() * this->_zoom
        );

        painter.drawRect(drawZone);
        painter.drawImage(drawZone, this->_checkboard);
        painter.drawImage(drawZone, this->_image);

        this->_selection.paint(painter, QPoint(drawZone.x(), drawZone.y()), this->_image, this->_zoom);

        QPoint pixelPosition = this->_pixelPosition;
        if(this->_image.rect().contains(pixelPosition)) {
            painter.drawRect(this->_position.x() + pixelPosition.x() * this->_zoom, this->_position.y() + pixelPosition.y() * this->_zoom, this->_zoom, this->_zoom);
        }
    }

    void ImageArea::mouseMoveEvent(QMouseEvent * e) {
        this->_pixelPosition = this->_position - this->_lastPos;

        if(this->_pixelPosition.x() <= 0 && this->_pixelPosition.y() <= 0) {
            this->_pixelPosition.setX(abs(this->_pixelPosition.x()) / this->_zoom);
            this->_pixelPosition.setY(abs(this->_pixelPosition.y()) / this->_zoom);
        }

        emit this->mouseMoved(*this, this->_image, this->_pixelPosition, this->_selection, *e, this->_mouseClickHold);
        this->_lastPos = e->pos();

        this->repaint();
    }

    void ImageArea::mousePressEvent(QMouseEvent * e) {
        this->_mouseClickHold = true;

        QPoint pixelPosition = this->_position - this->_lastPos;
        if(pixelPosition.x() <= 0 && pixelPosition.y() <= 0) {
            pixelPosition.setX(abs(pixelPosition.x()) / this->_zoom);
            pixelPosition.setY(abs(pixelPosition.y()) / this->_zoom);
        }

        emit this->mousePressed(*this, this->_image, pixelPosition, this->_selection, *e);
        this->repaint();
    }

    void ImageArea::mouseReleaseEvent(QMouseEvent * e) {
        this->_mouseClickHold = false;

        this->_pixelPosition = this->_position - this->_lastPos;
        if(this->_pixelPosition.x() <= 0 && this->_pixelPosition.y() <= 0) {
            this->_pixelPosition.setX(abs(this->_pixelPosition.x()) / this->_zoom);
            this->_pixelPosition.setY(abs(this->_pixelPosition.y()) / this->_zoom);
        }

        emit this->mouseReleased(*this, this->_image, this->_pixelPosition, this->_selection, *e);
        this->repaint();
    }

    void ImageArea::keyPressEvent(QKeyEvent * event) {
        switch(event->key()) {
            case Qt::Key_Down:
                this->_pixelPosition.setY(this->_pixelPosition.y() + 1);
                break;

            case Qt::Key_Up:
                this->_pixelPosition.setY(this->_pixelPosition.y() - 1);
                break;

            case Qt::Key_Left:
                this->_pixelPosition.setX(this->_pixelPosition.x() - 1);
                break;

            case Qt::Key_Right:
                this->_pixelPosition.setX(this->_pixelPosition.x() + 1);
                break;

            case Qt::Key_R:
                this->changeZoom(1.0);
                this->_lastPos = QPoint(0, 0);
                this->_position = QPoint(0, 0);
        }

        if(this->_pixelPosition.x() <= 0 && this->_pixelPosition.y() <= 0) {
            this->_pixelPosition.setX(abs(this->_pixelPosition.x()) / this->_zoom);
            this->_pixelPosition.setY(abs(this->_pixelPosition.y()) / this->_zoom);
        }

        emit this->keyboardPress(*this, this->_image, this->_pixelPosition,this->_selection, *event);
        this->repaint();
    }

    void ImageArea::keyReleaseEvent(QKeyEvent * event) {
        if(this->_pixelPosition.x() <= 0 && this->_pixelPosition.y() <= 0) {
           this->_pixelPosition.setX(abs(this->_pixelPosition.x()) / this->_zoom);
            this->_pixelPosition.setY(abs(this->_pixelPosition.y()) / this->_zoom);
        }

        emit this->keyboardRelease(*this, this->_image, this->_pixelPosition,this->_selection, *event);
        this->repaint();
    }

    void ImageArea::wheelEvent(QWheelEvent *event) {
        if(event->angleDelta().y() > 0) {
            this->increaseZoom();
        }
        else if(event->angleDelta().y() < 0) {
            this->decreaseZoom();
        }
    }

    void ImageArea::changeZoom(double value) {
        this->_zoom = value;
        emit this->zoomChanged(value);
        this->repaint();
    }

    void ImageArea::increaseZoom() {
        if(this->_zoom > 2) {
            this->_zoom = std::floor(this->_zoom + 1);
        }
        else {
            this->_zoom *= 1.1;
        }
        emit this->zoomChanged(this->_zoom);
        this->repaint();
    }

    void ImageArea::decreaseZoom() {
        if(this->_zoom > 0.15) {
            if(this->_zoom > 2) {
                this->_zoom = std::floor(this->_zoom - 1);
            }
            else {
                this->_zoom *= 0.9;
            }
            emit this->zoomChanged(this->_zoom);
            this->repaint();
        }
    }

    void ImageArea::setImage(const QImage & image) {
        this->_image = image;
        this->_checkboard = ImageArea::Generate_Checkboard(this->_image.width()/2, this->_image.height()/2, 1);

        emit this->imageChanged(image);
    }

    void ImageArea::setColor(const QPoint & pixel, const QColor & color, const QImage * origin) {
        if(this->_repercution != nullptr && origin != nullptr) {
            this->_repercution->apply(pixel, color , origin,  &this->_image);
        }
        else {
            if(this->_image.rect().contains(pixel)) {
                this->_image.setPixelColor(pixel, color);
            }
        }

        this->_status |= MODIFIED;
        emit this->modified(pixel, color);
    }

    void ImageArea::setScale(const QPoint & scaling, Qt::TransformationMode mode) {
        this->setImage(this->_image.scaled(scaling.x(), scaling.y(), Qt::IgnoreAspectRatio, mode));
        this->repaint();
    }

    void ImageArea::setSize(const QPoint & anchor, const QPoint & cliping) {
        QImage copy = this->_image;
        this->_image = QImage(cliping.x(), cliping.y(), QImage::Format_RGB32);
        if(anchor.x() + cliping.x() < this->_image.width() && anchor.y() + cliping.y() < this->_image.height()) {
            int i = 0, j = 0;
            for(int x = 0; x <= cliping.x(); x++) {
                for(int y = 0; y <= cliping.x(); y++) {
                    this->setColor(QPoint(i, j), copy.pixelColor(anchor.x() + x, anchor.y() + y));
                    j++;
                }
                i++;
                j = 0;
            }
        }
        else {
            QMessageBox::critical(this, "Erreur de rognage", "Valeurs pour le rognage invalide.");
        }
    }

    void ImageArea::transform(const QTransform & transformation, Qt::TransformationMode mode) {
        this->_image = this->_image.transformed(transformation, mode);
        this->_transformation = transformation;
        this->_selection.clear();
        this->repaint();

        emit this->transformed(transformation, mode);
    }

    void ImageArea::effect(const effect::Effect & effect) {
        effect.use(this->_selection, this->_image);
        this->repaint();

        emit this->effected(effect);
    }

    void ImageArea::save() {
        if((this->_status & NEW) != 0) {
            QString path = QFileDialog::getSaveFileName(nullptr, "", "New");
            this->_fileinfo = QFileInfo(path);
        }

        this->setModified(false);
        this->setNew(false);
        this->setOriginal(false);

        this->save(this->_fileinfo.absoluteFilePath());
    }

    void ImageArea::save(const QString & path) {
        if(!QFile::exists(path)) {
            QFile newFile(path);
            newFile.open(QFile::ReadOnly);
        }

        this->_image.save(path);
        this->_fileinfo.setFile(path);

        this->setModified(false);
        this->setNew(false);
        this->setOriginal(false);

        emit this->saved(this->_image, this->_fileinfo);
    }

    QImage ImageArea::Generate_Checkboard(qsizetype nbsquare_v, qsizetype nbsquare_h, qsizetype size) {
        QImage img(size*nbsquare_v, size*nbsquare_h, QImage::Format_RGB32);
        img.fill(QColorConstants::White);

        bool gray = true;
        for(int c = 0; c < nbsquare_v; c++) {
            for(int r = 0; r < nbsquare_h; r++) {
                for(int w = 0; w < size-1; w++) {
                    for(int h = 0; h < size-1; h++) {
                        img.setPixelColor(w + (size * r) , h + (size * c), gray ? QColorConstants::LightGray : QColorConstants::White);
                    }
                }
                gray = !gray;
            }
            gray = !gray;
        }

        return img;
    }

    void ImageArea::increaseBrightness() {
        effect::Contrast c(1.2, 1.0);
        this->effect(c);
        // Utilisation de la méthode effecte pour que les modification de l'image
        // actuelle soit aussi effectuer sur les autres images.
    }

    void ImageArea::decreaseBrightness() {
        effect::Contrast c(0.8, 1.0);
        this->effect(c);
    }

    void ImageArea::increaseContrast() {
        effect::Contrast c(1.0, 1.2);
        this->effect(c);
    }

    void ImageArea::decreaseContrast() {
        effect::Contrast c(1.0, 0.8);
        this->effect(c);
    }

    void ImageArea::blackAndWhite() {
        effect::BlackAndWhite bw;
        this->effect(bw);
    }

    void ImageArea::deleteCurrentSelection() {
        for(auto & pixel : this->_selection.selection()) {
            this->setColor(pixel, QColor(0, 0, 0, 0));
        }
    }
}
