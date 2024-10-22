#pragma once

#include <QWidget>
#include <QFileInfo>
#include <QSharedPointer>
#include <QPainter>
#include <QShortcut>
#include <QKeyEvent>

#include "selection.h"
#include "repercussion/repercussion.h"
#include "../effect/effect.h"

namespace ui {
    class ImageArea : public QWidget {
        Q_OBJECT
        private:
            Selection _selection;
            QFileInfo _fileinfo;
            QImage _image;
            QImage _checkboard;
            QTransform _transformation;

            QPoint _position;
            QPoint _lastPos;
            QPoint _pixelPosition;

            Repercution * _repercution;

            double _zoom;

            uint8_t _status;

            bool _mouseClickHold;
            bool _emitModification;
            bool _receiveModification;

        protected:
            enum ImageStatus {
                NONE        = 0,
                ORIGINAL    = 1,
                MODIFIED    = 2,
                NEW         = 4
            };

        public:
            ImageArea();
            ImageArea(const QFileInfo &, QWidget * = nullptr);

            inline const QFileInfo & file() const {return this->_fileinfo;}
            inline const QImage & image() const {return this->_image;}
            inline const Repercution * repercution() const {return this->_repercution;}
            inline const QTransform & transformation() const {return this->_transformation;}
            inline const Selection & selection() const {return this->_selection;}

            inline double zoom() const {return this->_zoom;}

            inline bool isOriginal() const {return (this->_status & ORIGINAL) != 0;}
            inline bool isModified() const {return (this->_status & MODIFIED) != 0;}
            inline bool isNew() const {return (this->_status & NEW) != 0;}
            inline bool isMouseHolded() const {return this->_mouseClickHold;}

            inline bool isEmitingModification() const {return this->_emitModification;}
            inline bool isReceivingModification() const {return this->_receiveModification;}

            inline const QPoint & position() const {return this->_position;}
            inline const QPoint & last_position() const {return this->_lastPos;}

            inline void setOriginal(bool original) {this->_status = original ? this->_status | ORIGINAL : this->_status & ~ORIGINAL;}
            inline void setModified(bool modified) {this->_status = modified ? this->_status | MODIFIED : this->_status & ~MODIFIED;}
            inline void setNew(bool news) {this->_status = news ? this->_status | NEW : this->_status & ~NEW;}
            inline void setZoom(float zoom) {this->_zoom = zoom;}
            inline void setMouseHold(bool hold) {this->_mouseClickHold = hold;}
            inline void setPosition(const QPoint & position) {this->_position = position;}
            inline void setLast_Positon(const QPoint & lastPosition) {this->_lastPos = lastPosition;}

            inline void setRepercution(Repercution * repercution) {this->_repercution = repercution;}

            virtual void paintEvent(QPaintEvent *);

            virtual void mouseMoveEvent(QMouseEvent *);
            virtual void mousePressEvent(QMouseEvent *);
            virtual void mouseReleaseEvent(QMouseEvent *);

            virtual void keyPressEvent(QKeyEvent *);
            virtual void keyReleaseEvent(QKeyEvent *);

            virtual void wheelEvent(QWheelEvent *);

            static QImage Generate_Checkboard(qsizetype, qsizetype, qsizetype);

        public slots:
            inline void changeModificationEmit(bool status) {this->_emitModification = status;}
            inline void changeModificationReceive(bool status) {this->_receiveModification = status;}
            inline void clearSelection() {this->_selection.clear(false); this->repaint();}

            void increaseZoom();
            void decreaseZoom();
            void changeZoom(double);

            void setImage(const QImage &);
            void setColor(const QPoint &, const QColor &, const QImage * = nullptr);
            void setScale(const QPoint &, Qt::TransformationMode = Qt::TransformationMode::FastTransformation);
            void setSize(const QPoint &, const QPoint &);

            void transform(const QTransform &, Qt::TransformationMode = Qt::TransformationMode::FastTransformation);
            void effect(const effect::Effect &);

            void save();
            void save(const QString &);

           void increaseBrightness();
           void decreaseBrightness();
           void increaseContrast();
           void decreaseContrast();

           void blackAndWhite();
           void deleteCurrentSelection();

        signals:
            void zoomChanged(double);

            void imageChanged(const QImage &);

            void modified(const QPoint &, const QColor &);
            void transformed(const QTransform &, Qt::TransformationMode);
            void effected(const effect::Effect &);

            void saved(const QImage &, const QFileInfo &);

            void mousePressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &);
            void mouseReleased(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &);
            void mouseMoved(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &, bool);
            void keyboardPress(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &);
            void keyboardRelease(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &);
    };
}

