#include "toolRegister.h"

#include <QDebug>

namespace ui {
ToolboxRegister::ToolboxRegister(Toolbox * selectionToolbox, Toolbox * editTooblox, ViewManager * manager, QPushButton * configButton)
    : _selectionToolbox(selectionToolbox), _editToolbox(editTooblox), _viewManager(manager), _configButton(configButton) , _currentTool(nullptr), _currentImage(nullptr) {
        configButton->setEnabled(false);
    }

    void ToolboxRegister::add(QSharedPointer<tool::Tool> tool, ToolType type) {
        this->_tools.push_back(tool);
        if(type == ToolType::EDIT) {
            this->_editToolbox->addItem(tool.get());
        }
        else if(type == ToolType::SELECTION) {
            this->_selectionToolbox->addItem(tool.get());
        }
    }

    void ToolboxRegister::update() {
        QObject::connect(this->_selectionToolbox, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(updateCurrentTool(QListWidgetItem*)));
        QObject::connect(this->_editToolbox, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(updateCurrentTool(QListWidgetItem*)));

        QObject::connect(this->_viewManager, SIGNAL(changedView(ImageArea*)), this, SLOT(updateCurrentView(ImageArea*)));
        QObject::connect(this->_viewManager, SIGNAL(createdView(ImageArea*)), this, SLOT(updateCurrentView(ImageArea*)));
    }

    void ToolboxRegister::updateCurrentTool(QListWidgetItem * item) {
        if(item->listWidget() == this->_editToolbox) {
            this->_selectionToolbox->setCurrentRow(-1);
        }
        else if(item->listWidget() == this->_selectionToolbox) {
            this->_editToolbox->setCurrentRow(-1);
        }

        if(this->_currentTool != nullptr && this->_currentImage != nullptr) {
            QObject::disconnect(this->_currentImage, SIGNAL(mousePressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(pressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::disconnect(this->_currentImage, SIGNAL(mouseReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(released(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::disconnect(this->_currentImage, SIGNAL(mouseMoved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)), this->_currentTool, SLOT(moved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)));

            QObject::disconnect(this->_currentImage, SIGNAL(keyboardPress(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyPressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));
            QObject::disconnect(this->_currentImage, SIGNAL(keyboardRelease(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));

            QObject::disconnect(&this->_currentImage->selection(), SIGNAL(cleared()), this->_currentTool, SLOT(selectionCleared()));

            if(this->_currentTool->HaveConfigurationDialog()) {
                QObject::disconnect(this->_configButton, SIGNAL(released()), this->_currentTool, SLOT(showConfiguration()));
            }
        }

        this->_currentTool = dynamic_cast<tool::Tool*>(item);

        if(this->_currentTool != nullptr && this->_currentImage != nullptr) {
            this->_currentImage->setCursor(QCursor(this->_currentTool->shape()));
            QObject::connect(this->_currentImage, SIGNAL(mousePressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(pressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::connect(this->_currentImage, SIGNAL(mouseReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(released(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::connect(this->_currentImage, SIGNAL(mouseMoved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)), this->_currentTool, SLOT(moved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)));

            QObject::connect(this->_currentImage, SIGNAL(keyboardPress(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyPressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));
            QObject::connect(this->_currentImage, SIGNAL(keyboardRelease(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));

            QObject::connect(&this->_currentImage->selection(), SIGNAL(cleared()), this->_currentTool, SLOT(selectionCleared()));

            QObject::connect(this->_configButton, SIGNAL(released()), this->_currentTool, SLOT(showConfiguration()));
            this->_configButton->setEnabled(this->_currentTool->HaveConfigurationDialog());

        }
    }

    void ToolboxRegister::updateCurrentView(ImageArea * image) {
        if(this->_currentTool != nullptr && this->_currentImage != nullptr) {
            QObject::disconnect(this->_currentImage, SIGNAL(mousePressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(pressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::disconnect(this->_currentImage, SIGNAL(mouseReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(released(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::disconnect(this->_currentImage, SIGNAL(mouseMoved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)), this->_currentTool, SLOT(moved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)));

            QObject::disconnect(this->_currentImage, SIGNAL(keyboardPress(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyPressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));
            QObject::disconnect(this->_currentImage, SIGNAL(keyboardRelease(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));

            QObject::disconnect(&this->_currentImage->selection(), SIGNAL(cleared()), this->_currentTool, SLOT(selectionCleared()));

            if(this->_currentTool->HaveConfigurationDialog()) {
                QObject::disconnect(this->_configButton, SIGNAL(released()), this->_currentTool, SLOT(showConfiguration()));
            }
        }

        this->_currentImage = dynamic_cast<ImageArea *>(image);

        if(this->_currentTool != nullptr && this->_currentImage != nullptr) {
            this->_currentImage->setCursor(QCursor(this->_currentTool->shape()));
            QObject::connect(this->_currentImage, SIGNAL(mousePressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(pressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::connect(this->_currentImage, SIGNAL(mouseReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)), this->_currentTool, SLOT(released(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&)));
            QObject::connect(this->_currentImage, SIGNAL(mouseMoved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)), this->_currentTool, SLOT(moved(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QMouseEvent&,bool)));

            QObject::connect(this->_currentImage, SIGNAL(keyboardPress(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyPressed(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));
            QObject::connect(this->_currentImage, SIGNAL(keyboardRelease(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)), this->_currentTool, SLOT(keyReleased(ui::ImageArea&,QImage&,QPoint&,ui::Selection&,QKeyEvent&)));

            QObject::connect(&this->_currentImage->selection(), SIGNAL(cleared()), this->_currentTool, SLOT(selectionCleared()));

            QObject::connect(this->_configButton, SIGNAL(released()), this->_currentTool, SLOT(showConfiguration()));
            this->_configButton->setEnabled(this->_currentTool->HaveConfigurationDialog());

            this->_currentTool->initialize(this->_currentImage);

        }
    }
}
