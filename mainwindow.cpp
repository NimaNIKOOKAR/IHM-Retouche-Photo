#include "mainwindow.h"

#include <QApplication>
#include <QMimeData>
#include <QColorDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <colorpickerwidget.h>

#include <ui/menu/filemenulambda.h>
#include <ui/menu/displaymenulambda.h>
#include <ui/menu/imagemenulambda.h>
#include <ui/menu/selectionmenulambda.h>

#include <ui/files/treefileselector.h>

#include <tools/hand.h>
#include <tools/picker.h>

#include <tools/selectionable/rectangle.h>
#include <tools/selectionable/rectangleTriangle.h>
#include <tools/selectionable/triangle.h>
#include <tools/selectionable/ellipse.h>
#include <tools/selectionable/polygone.h>
#include <tools/selectionable/color.h>
#include <tools/selectionable/quad.h>

#include <tools/editable/pixelpainter.h>
#include <tools/editable/pixelEraiser.h>
#include <tools/editable/bucket.h>

#include <ui/view/repercussion/ignore.h>
#include <ui/view/repercussion/clamp.h>
#include <ui/view/repercussion/average.h>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent), _fileselectorManager(nullptr), _toolRegister(nullptr), _viewManager(nullptr) {

    this->setupUi(this);
    this->setAcceptDrops(true);
    this->_imageTabs->clear();

    qDebug() << "Mark_1";

    this->_fileselectorManager = new ui::TreeFileSelector(this->_filesSelector, this->_filesSelected, this);

    QObject::connect(this->_remove_selectable_element, SIGNAL(released()), this->_fileselectorManager, SLOT(removeSelectedItem()));
    QObject::connect(this->_add_selectable_element, SIGNAL(released()), this->_fileselectorManager, SLOT(pushItem()));

    qDebug() << "Mark_2";

    ColorWindow = this->_colorPicker;

    // Connect the button's clicked signal to the openColorPicker slot
    QObject::connect(ColorWindow, &QPushButton::clicked, this, &MainWindow::openColorPicker);
    // Create an action for Ctrl+C
    ctrlCAction = new QAction(this);
    ctrlCAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C)); // Change the shortcut
    QObject::connect(ctrlCAction, &QAction::triggered, this, &MainWindow::handleCtrlCKey);
    addAction(ctrlCAction);

    qDebug() << "Mark_3";

    this->_viewManager = new ui::ViewManager(this->_fileselectorManager, this->_imageTabs);

    qDebug() << "Mark_4";

    this->_multyImageModifier = new ui::MultyImageModifier(this->_viewManager, this->_emitDrawCheckbox, this->_receiveDrawCheckbox, this->_samplingDrawList);
    this->_multyImageModifier->push(QSharedPointer<ui::Repercution>(new ui::Ignore()));
    this->_multyImageModifier->push(QSharedPointer<ui::Repercution>(new ui::Average()));

    qDebug() << "mark_5";

    this->_rescaleDialog = new dialog::ReScaleDialog(this->_viewManager);
    QObject::connect(this->_rescaleButton, SIGNAL(released()), this->_rescaleDialog, SLOT(use()));

    this->_resizeDialog = new dialog::ReSizeDialog(this->_viewManager);
    QObject::connect(this->_resizeButton, SIGNAL(released()), this->_resizeDialog, SLOT(use()));

    qDebug() << "Mark_6";
    
    this->_toolRegister = new ui::ToolboxRegister(this->_selectionToolbox, this->_editToolbox, this->_viewManager, this->_toolConfigButton);

    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Hand(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Picker(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::EDIT);

    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Rectangle(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::RectangleTriangle(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Triangle(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Ellipse(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Polygone(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Color(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Quad(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::SELECTION);

    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Pixelpainter(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::EDIT);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Pixeleraiser(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::EDIT);
    this->_toolRegister->add(QSharedPointer<tool::Tool>(new tool::Bucket(this->colorPickerWidget)), ui::ToolboxRegister::ToolType::EDIT);

    qDebug() << "Mark_6.1";



    qDebug() << "Mark_6.2";

    this->_toolRegister->update();

    qDebug() << "Mark_7";

    this->_menubarManager.insert(this->_menuFile, QSharedPointer<ui::MenuLambda>(new ui::FilemenuLambda(this->_fileselectorManager, this->_viewManager)));
    this->_menubarManager.insert(this->_menuAffichage, QSharedPointer<ui::MenuLambda>(new ui::DisplayMenuLambda(this->_viewManager)));
    this->_menubarManager.insert(this->_menuImage, QSharedPointer<ui::MenuLambda>(new ui::ImageMenuLambda(this->_rescaleDialog, this->_resizeDialog, this->_viewManager)));
    this->_menubarManager.insert(this->_menuSelection, QSharedPointer<ui::MenuLambda>(new ui::SelectionMenuLambda(this->_viewManager)));

    this->_menubarManager.update();

    qDebug() << "Mark_8";

    _actionNoirEtBlanc = new QAction(QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/color-picker-black.png"), "Convertir en Noir et Blanc", this);
    toolBarLeft->addAction(_actionNoirEtBlanc);

    connect(_actionNoirEtBlanc, &QAction::triggered, this, &MainWindow::convertToNoirEtBlancActionTriggered);

    _actionAdjustBrightnessContrast = new QAction("Ajuster la luminosité et le contraste", this);
    toolBarLeft->addAction(_actionAdjustBrightnessContrast);
    connect(_actionAdjustBrightnessContrast, &QAction::triggered, this, &MainWindow::adjustBrightnessContrastActionTriggered);

    qDebug() << "Mark_9";

    _actionAdjustBrightness = new QAction("Augmenter la luminosité", this);
    toolBarLeft->addAction(_actionAdjustBrightness);
    _actionAdjustBrightness->setVisible(false);
    connect(_actionAdjustBrightness, &QAction::triggered, this, &MainWindow::increaseBrightnessActionTriggered);

    _actionDecreaseBrightness = new QAction("Diminuer la luminosité", this);
    toolBarLeft->addAction(_actionDecreaseBrightness);
    _actionDecreaseBrightness->setVisible(false);
    connect(_actionDecreaseBrightness, &QAction::triggered, this, &MainWindow::decreaseBrightnessActionTriggered);

    qDebug() << "Mark_10";

    _actionIncreaseContrast = new QAction("Augmenter le contraste", this);
    toolBarLeft->addAction(_actionIncreaseContrast);
    _actionIncreaseContrast->setVisible(false);
    connect(_actionIncreaseContrast, &QAction::triggered, this, &MainWindow::increaseContrastActionTriggered);

    _actionDecreaseContrast = new QAction("Diminuer le contraste", this);
    toolBarLeft->addAction(_actionDecreaseContrast);
    _actionDecreaseContrast->setVisible(false);
    connect(_actionDecreaseContrast, &QAction::triggered, this, &MainWindow::decreaseContrastActionTriggered);

    qDebug() << "Mark_11";

    QObject::connect(this->_action_unselect, SIGNAL(triggered(bool)), this, SLOT(unselect()));
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e) {
    if(e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent * e) {
    this->_fileselectorManager->onDrop(e);
}

void MainWindow::openColorPicker()
{
    colorPickerWidget.show();
}
void MainWindow::handleCtrlCKey()
{
    // Trigger the ColorWindow button when Ctrl+C is pressed
    openColorPicker();
}


void MainWindow::convertToNoirEtBlancActionTriggered() {
    ui::ImageArea *currentImageArea = this->_viewManager->currentView();
    if (currentImageArea) {
        currentImageArea->blackAndWhite();
    } else {
        qDebug() << "Aucun onglet d'image actif.";
    }
}

void MainWindow::adjustBrightnessContrastActionTriggered() {
     static bool isVisible = true;
    _actionAdjustBrightness->setVisible(isVisible);
    _actionDecreaseBrightness->setVisible(isVisible);
    _actionIncreaseContrast->setVisible(isVisible);
    _actionDecreaseContrast->setVisible(isVisible);

    isVisible = !isVisible;
}

void MainWindow::increaseBrightnessActionTriggered() {
    ui::ImageArea *currentImageArea = this->_viewManager->currentView();
    if (currentImageArea) {
        currentImageArea->increaseBrightness();
    } else {
        qDebug() << "Aucun onglet d'image actif.";
    }
}

void MainWindow::decreaseBrightnessActionTriggered() {
    ui::ImageArea *currentImageArea = this->_viewManager->currentView();
    if (currentImageArea) {
        currentImageArea->decreaseBrightness();
    } else {
        qDebug() << "Aucun onglet d'image actif.";
    }
}

void MainWindow::increaseContrastActionTriggered() {
    ui::ImageArea *currentImageArea = this->_viewManager->currentView();
    if (currentImageArea) {
        currentImageArea->increaseContrast();
    } else {
        qDebug() << "Aucun onglet d'image actif.";
    }
}

void MainWindow::decreaseContrastActionTriggered() {
    ui::ImageArea *currentImageArea = this->_viewManager->currentView();
    if (currentImageArea) {
        currentImageArea->decreaseContrast();
    } else {
        qDebug() << "Aucun onglet d'image actif.";
    }
}

void MainWindow::unselect() {
    ui::ImageArea * currentImage = this->_viewManager->currentView();
    if(currentImage != nullptr) {
        currentImage->clearSelection();
    }
}

MainWindow::~MainWindow() {
    delete this->_fileselectorManager;
    delete this->_toolRegister;
    delete this->_viewManager;
    delete this->_rescaleDialog;
    delete this->_resizeDialog;
    delete this->_multyImageModifier;
}

