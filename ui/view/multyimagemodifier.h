#pragma once

#include <QObject>

#include <QCheckBox>
#include <QComboBox>
#include <QVector>
#include <QListWidget>

#include "viewmanager.h"
#include "repercussion/repercussion.h"

namespace ui {
class MultyImageModifier : public QObject  {
        Q_OBJECT
        private:
            ViewManager * _manager;
            ImageArea * _current;

            QSet<ImageArea *> _targets;
            QVector<QSharedPointer<Repercution>> _repercutions;

            QCheckBox * _emitCheckbox;
            QCheckBox * _receiveCheckbox;
            QListWidget * _samplingList;

            QString _tmp_test;
            QStringList _tmp_test_2;

        public:
            MultyImageModifier() = delete;
            MultyImageModifier(ViewManager *, QCheckBox * emitCheckbox, QCheckBox * receiveCheckbox, QListWidget * samplinglist);

            inline const QVector<QSharedPointer<Repercution>> & repercutions() const {return this->_repercutions;}

        public slots:
            void changeCurrentRepercution(QListWidgetItem*);
            void changeCurrentImage(ImageArea *);

            void modify(const QPoint &, const QColor &);
            void transform(const QTransform &, Qt::TransformationMode);
            void effect(const effect::Effect &);

            void changeCurrentAsTarget(bool);

            void pushTarget(ImageArea *);
            void eraseTarget(ImageArea *);

            void push(QSharedPointer<Repercution> repercution);
    };
}
