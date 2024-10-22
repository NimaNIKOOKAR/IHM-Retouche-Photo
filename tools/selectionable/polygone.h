#pragma once

#include "../selectionnable.h"

namespace tool {
    class Polygone : public Selectionable {
        private:
            QPolygon _polygon;
            bool _preview;

        public:
            Polygone(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void initialize(ui::ImageArea *);
            virtual void onClear();
    };
}
