#pragma once

#include "tool.h"

#include "colorpickerwidget.h"

namespace tool {
    class Selectionable : public Tool {
        private:
            const ColorPickerWidget * _colorPicker;
            bool _free;

        public:
            Selectionable(const ColorPickerWidget &, const QString & = "NaN", const QIcon & = QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/transform-crop.png"), bool = false);

            inline const ColorPickerWidget * colorPicker() const {return this->_colorPicker;}

            virtual void onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &) = 0;
            virtual void onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &) = 0;
            virtual void onMouseMoved(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool) = 0;

            virtual void onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &);
            virtual void onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &);

            virtual void onClear();

            virtual void initialize(ui::ImageArea *);

        public slots:
            virtual void pressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &) final;
            virtual void released(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &) final;
            virtual void moved(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &, bool) final;

            virtual void keyPressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &) final;
            virtual void keyReleased(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &) final;

            virtual void selectionCleared() final;
    };
}
