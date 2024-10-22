#pragma once

#include <QPolygon>

#include "../selectionnable.h"

namespace tool {
    class Quad : public Selectionable {
        private:
            QPolygon _polygon;

        public:
            Quad(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void initialize(ui::ImageArea *);
            virtual void onClear();
    };
}
