#pragma once

#include "../selectionnable.h"

#include <dialog/sizedialog.h>

namespace tool {
    class Color : public Selectionable{
        private:
            QSharedPointer<dialog::SizeDialog> _config;
            QPoint _lastClicked;
            bool _ctrl;

        public:
            Color(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &);
            virtual void onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &);

            void select(ui::Selection &, const QPoint &, const QImage &);
    };
}
