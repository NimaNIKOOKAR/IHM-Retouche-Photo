#pragma once

#include "tool.h"

#include "colorpickerwidget.h"

namespace tool {
    class Editable : public Tool {
        private:
            const ColorPickerWidget * _colorPicker;
            bool _free;

        public:
            Editable(const ColorPickerWidget &, const QString & = "NaN", const QIcon & = QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-freehand.png"), bool = false);

            inline const ColorPickerWidget * colorPicker() const {return this->_colorPicker;}

            virtual void onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &) = 0;
            virtual void onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &) = 0;
            virtual void onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool) = 0;

            virtual void onKeyPress(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &);
            virtual void onKeyReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &);

            virtual void initialize(ui::ImageArea *);

        public slots:
            virtual void pressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &) final;
            virtual void released(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &) final;
            virtual void moved(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &, bool) final;

            virtual void keyPressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &) final;
            virtual void keyReleased(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &) final;

            virtual void selectionCleared();
    };
}
