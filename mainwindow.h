#pragma once

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QPointer>

#include "ui/toolbox/toolRegister.h"
#include "ui/menu/menubarmanager.h"
#include "ui/files/fileselector.h"
#include "ui/view/viewmanager.h"
#include "ui/view/multyimagemodifier.h"

#include "dialog/rescaledialog.h"
#include "dialog/resizedialog.h"

#include <colorpickerwidget.h>

class QAction;

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT
    private:
        ui::MenubarManager  _menubarManager;

        ui::FileSelector * _fileselectorManager;
        ui::ToolboxRegister * _toolRegister;
        ui::ViewManager * _viewManager;
        ui::MultyImageModifier * _multyImageModifier;


        dialog::ReScaleDialog * _rescaleDialog;
        dialog::ReSizeDialog * _resizeDialog;

        ColorPickerWidget colorPickerWidget; // Declare ColorPickerWidget as a private member
        QPushButton *ColorWindow; // Assuming you have a QPushButton in your UI
        QAction *ctrlCAction; // New QAction for Ctrl+C

        QAction* _actionNoirEtBlanc;
        QAction* _actionAdjustBrightnessContrast;

        QAction* _actionAdjustBrightness;
        QAction* _actionDecreaseBrightness;
        QAction* _actionIncreaseContrast;
        QAction* _actionDecreaseContrast;

    public:
        MainWindow(QWidget * parent = nullptr);
       ~MainWindow();

        virtual void dropEvent(QDropEvent * e);
        virtual void dragEnterEvent(QDragEnterEvent *e);

    private slots:
        void openColorPicker(); // Slot to open the ColorPickerWidget
        void handleCtrlCKey(); // New slot for Ctrl+C

        void convertToNoirEtBlancActionTriggered();
        void adjustBrightnessContrastActionTriggered();
        void increaseBrightnessActionTriggered();
        void decreaseBrightnessActionTriggered();
        void increaseContrastActionTriggered();
        void decreaseContrastActionTriggered();

        void unselect();


};
