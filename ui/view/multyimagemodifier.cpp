#include "multyimagemodifier.h"


namespace ui {
    MultyImageModifier::MultyImageModifier(ViewManager * manager, QCheckBox * emitCheckbox, QCheckBox * receiveCheckbox, QListWidget * samplingList)
    : _manager(manager), _current(nullptr), _emitCheckbox(emitCheckbox), _receiveCheckbox(receiveCheckbox), _samplingList(samplingList) {
        QObject::connect(manager, SIGNAL(changedView(ImageArea*)), this, SLOT(changeCurrentImage(ImageArea*)));

        QObject::connect(manager, SIGNAL(createdView(ImageArea*)), this, SLOT(pushTarget(ImageArea*)));
        QObject::connect(manager, SIGNAL(deletedView(ImageArea*)), this, SLOT(eraseTarget(ImageArea*)));

        QObject::connect(samplingList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changeCurrentRepercution(QListWidgetItem*)));
    }

    void MultyImageModifier::push(QSharedPointer<Repercution> r) {
        this->_repercutions.push_back(r);
        this->_samplingList->addItem(r.get());
    }

    void MultyImageModifier::changeCurrentImage(ImageArea * area) {
        if(this->_current != nullptr) {
            QObject::disconnect(this->_emitCheckbox, SIGNAL(toggled(bool)), this->_current, SLOT(changeModificationEmit(bool)));

            QObject::disconnect(this->_receiveCheckbox, SIGNAL(toggled(bool)), this, SLOT(changeCurrentAsTarget(bool)));
            QObject::disconnect(this->_receiveCheckbox, SIGNAL(toggled(bool)), this->_current, SLOT(changeModificationReceive(bool)));

            QObject::disconnect(this->_current, SIGNAL(modified(QPoint,QColor)), this, SLOT(modify(QPoint,QColor)));
            QObject::disconnect(this->_current, SIGNAL(transformed(QTransform,Qt::TransformationMode)), this, SLOT(transform(QTransform,Qt::TransformationMode)));
            QObject::disconnect(this->_current, SIGNAL(effected(effect::Effect)), this, SLOT(effect(effect::Effect)));
        }

        this->_current = area;

        if(this->_current != nullptr) {
            if(this->_current->repercution() == nullptr && !this->_repercutions.empty()) {
                this->_current->setRepercution(this->_repercutions.at(0).get());
            }

            if(this->_current->isReceivingModification()) {
                this->_targets.insert(this->_current);
            }

            this->_emitCheckbox->setChecked(this->_current->isEmitingModification());
            this->_receiveCheckbox->setChecked(this->_current->isReceivingModification());

            QObject::connect(this->_emitCheckbox, SIGNAL(toggled(bool)), this->_current, SLOT(changeModificationEmit(bool)));

            QObject::connect(this->_receiveCheckbox, SIGNAL(toggled(bool)), this, SLOT(changeCurrentAsTarget(bool)));
            QObject::connect(this->_receiveCheckbox, SIGNAL(toggled(bool)), this->_current, SLOT(changeModificationReceive(bool)));

            QObject::connect(this->_current, SIGNAL(modified(QPoint,QColor)), this, SLOT(modify(QPoint,QColor)));
            QObject::connect(this->_current, SIGNAL(transformed(QTransform,Qt::TransformationMode)), this, SLOT(transform(QTransform,Qt::TransformationMode)));
            QObject::connect(this->_current, SIGNAL(effected(effect::Effect)), this, SLOT(effect(effect::Effect)));
        }
        else {
            this->_emitCheckbox->setChecked(false);
            this->_receiveCheckbox->setChecked(false);
        }
    }

    void MultyImageModifier::changeCurrentRepercution(QListWidgetItem * e) {
        if(this->_current != nullptr) {
            this->_current->setRepercution(dynamic_cast<Repercution *>(e));
        }
    }

    void MultyImageModifier::modify(const QPoint & point, const QColor & color) {
        if(this->_current != nullptr && this->_current->isEmitingModification()) {
            for(auto * area : this->_targets) {
                if(area != this->_current) {
                    area->setColor(point, color, &this->_current->image());
                }
            }
        }
    }

    void MultyImageModifier::transform(const QTransform & transformation, Qt::TransformationMode mode) {
        if(this->_current != nullptr && this->_current->isEmitingModification()) {
            for(auto * area : this->_targets) {
                if(area != this->_current) {
                    area->transform(transformation, mode);
                }
            }
        }
    }

    void MultyImageModifier::effect(const effect::Effect & effect) {
        if(this->_current != nullptr && this->_current->isEmitingModification()) {
            for(auto * area : this->_targets) {
                if(area != this->_current) {
                    area->effect(effect);
                }
            }
        }
    }

    void MultyImageModifier::changeCurrentAsTarget(bool status) {
        if(this->_current == nullptr) {
            return;
        }

        if(status) {
            this->_targets.insert(this->_current);
        }
        else {
            this->_targets.remove(this->_current);
        }
    }

    void MultyImageModifier::pushTarget(ImageArea * area) {
        if(area->isReceivingModification()) {
            this->_targets.insert(area);
        }
    }

    void MultyImageModifier::eraseTarget(ImageArea * area) {
        this->_targets.remove(area);
    }
}
