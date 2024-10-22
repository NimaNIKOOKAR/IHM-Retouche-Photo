#pragma once

#include <QVector>
#include <QSharedPointer>
#include <QListWidget>
#include <QPushButton>

#include <tools/tool.h>

#include "../view/viewmanager.h"

namespace ui {
using Toolbox = QListWidget;
    class ToolboxRegister : public QObject {
        Q_OBJECT
        public:
            Toolbox * _selectionToolbox;
            Toolbox * _editToolbox;
            ViewManager * _viewManager;
            QPushButton * _configButton;

            QVector<QSharedPointer<tool::Tool>> _tools;

            tool::Tool * _currentTool;
            ImageArea * _currentImage;

        public:
            ToolboxRegister(Toolbox * selectionToolbox = nullptr, Toolbox * editTooblox = nullptr, ViewManager * = nullptr, QPushButton * = nullptr);

            enum ToolType {
                SELECTION,
                EDIT
            };

            inline void setSelectionToolbox(Toolbox * toolbox) {this->_selectionToolbox = toolbox;}
            inline void setEditToolbox(Toolbox * toolbox) {this->_editToolbox = toolbox;}
            inline void setViewManager(ViewManager * viewManager) {this->_viewManager = viewManager;}
            inline void setConfigurationButton(QPushButton * button) {this->_configButton = button;}

            inline const Toolbox * selectionToolbox() const {return this->_selectionToolbox;}
            inline const Toolbox * editToolbox() const {return this->_editToolbox;}

            void add(QSharedPointer<tool::Tool>, ToolType);
            void update();

        public slots:
            void updateCurrentTool(QListWidgetItem *);
            void updateCurrentView(ImageArea *);
    };
}

