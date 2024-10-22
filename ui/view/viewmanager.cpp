#include "viewmanager.h"

#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QIcon>

namespace ui {
    ViewManager::ViewManager(FileSelector * selector, QTabWidget * tabs)
    : _selector(selector), _tabs(tabs) {
        QObject::connect(this->_selector, SIGNAL(selectItem(QFileInfo)), this, SLOT(newView(QFileInfo)));
        QObject::connect(this->_selector, SIGNAL(dropItem(QFileInfo)), this, SLOT(deleteView(QFileInfo)));
        QObject::connect(this->_tabs, SIGNAL(currentChanged(int)), this, SLOT(changeView(int)));
        QObject::connect(this->_tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteView(int)));
    }

    QVector<ImageArea *> ViewManager::areas() const {
        QVector<ImageArea *> area;
        for(int i = 0 ; i < this->_tabs->count(); i++) {
            area.push_back(dynamic_cast<ImageArea *>(this->_tabs->widget(i)));
        }
        return area;
    }

    void ViewManager::newView() {
        this->_tabs->addTab(QPointer<ImageArea>(new ImageArea()), "New");
        this->_tabs->setCurrentIndex(this->_tabs->count()-1);
        emit this->createdView(dynamic_cast<ImageArea*>(this->currentView()));
        if(this->_tabs->count() == 0) {
            emit this->changedView(this->currentView());
        }
    }

    void ViewManager::newView(const QFileInfo & info) {
        this->_tabs->addTab(QPointer<ImageArea>(new ImageArea(info)), info.fileName());
        this->_tabs->setCurrentIndex(this->_tabs->count()-1);
        emit this->createdView(dynamic_cast<ImageArea*>(this->currentView()));
        if(this->_tabs->count() == 0) {
            emit this->changedView(this->currentView());
        }
    }

    void ViewManager::deleteCurrentView() {
        if(this->currentView() == nullptr) {
            return;
        }

        if(this->currentView()->isModified()) {
            QMessageBox saveDialog;
            saveDialog.setText("Voulez vous sauvegarder les modification ?");
            saveDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            saveDialog.setDefaultButton(QMessageBox::Cancel);
            saveDialog.setIcon(QMessageBox::Icon::Warning);
            int result = saveDialog.exec();

            if(result == QMessageBox::Yes) {
                this->saveAsCurrentView();
                this->currentView()->setModified(false);
            }
        }

        this->deleteView(this->_tabs->currentIndex());
    }

    void ViewManager::deleteView(const QFileInfo & info) {
        for(int i = 0; i < this->_tabs->count(); i++) {
            ImageArea * widget = dynamic_cast<ImageArea *>(this->_tabs->widget(i));
            if(widget->file().absoluteFilePath() == info.absoluteFilePath()) {
                emit this->deletedView(widget);
                this->_tabs->removeTab(i);
                --i;
            }
        }
    }

    void ViewManager::deleteView(int index) {
        emit this->deletedView(this->currentView());
        if(this->_tabs->count() != 0) {
            emit this->changedView(this->currentView());
        }
        this->_tabs->removeTab(index);
    }

    void ViewManager::changeView(int) {
        emit this->changedView(this->currentView());
    }

    void ViewManager::saveCurrentView() {
        this->saveView(this->_tabs->currentIndex());
    }

    void ViewManager::saveView(int index) {
        ImageArea * area = dynamic_cast<ImageArea *>(this->_tabs->widget(index));
        if(area != nullptr) {
            if(area->isOriginal()) {
                QMessageBox saveDialog;
                saveDialog.setText("Voulez vous sauvegarder les modification sur le fichier original.");
                saveDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
                saveDialog.setDefaultButton(QMessageBox::Cancel);
                saveDialog.setIcon(QMessageBox::Icon::Warning);
                int result = saveDialog.exec();

                if(result == QMessageBox::Yes) {
                    area->setOriginal(false);
                }
                else if(result == QMessageBox::No) {
                    this->saveAsCurrentView();
                }
                else {
                    return;
                }
            }
            area->save();
        }
    }

    void ViewManager::saveAsCurrentView() {
        this->saveAsView(this->_tabs->currentIndex());
    }

    void ViewManager::saveAsView(int index) {
        ImageArea * area = dynamic_cast<ImageArea *>(this->_tabs->widget(index));
        if(area != nullptr) {
            QString path = QFileDialog::getSaveFileName(nullptr, "", area->file().fileName());

            if(!path.isEmpty()) {
                QFile file(path);
                file.open(QIODevice::ReadOnly);
                area->save(path);
                area->setModified(false);
                area->setOriginal(false);
                area->setNew(false);
            }
        }
    }

    void ViewManager::saveAll() {
        for(int i = 0; i < this->_tabs->count(); i++) {
            this->saveView(i);
        }
    }
}
