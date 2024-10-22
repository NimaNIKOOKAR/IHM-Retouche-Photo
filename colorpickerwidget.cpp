#include "colorpickerwidget.h"

#include <QColorDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPushButton>
#include <QKeyEvent>

ColorPickerWidget::ColorPickerWidget(QWidget *parent)
    : QWidget(parent), _currentColor(QColorConstants::Black) {
    this->_mainLayout = new QVBoxLayout(this);

    this->_colorListWidget = new QListWidget(this);
    this->_mainLayout->addWidget(this->_colorListWidget);

    this->_currentColorLayout = new QHBoxLayout();

    this->_currentColorLabel = new QLabel("Couleur courrante :", this);
    this->_currentColorLayout->addWidget(this->_currentColorLabel);

    this->_currentColorFrame = new QFrame(this);
    this->_currentColorFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->_currentColorLayout->addWidget(this->_currentColorFrame);

    this->_mainLayout->addLayout(this->_currentColorLayout);

    this->_addColorButton = new QPushButton("Ajouter une couleur", this);
    QObject::connect(this->_addColorButton, SIGNAL(released()), this, SLOT(addColor()));
    this->_mainLayout->addWidget(this->_addColorButton);

    this->_modifyColorButton = new QPushButton("Modifier la couleur courrante", this);
    QObject::connect(this->_modifyColorButton, SIGNAL(released()), this, SLOT(modifyColor()));
    this->_mainLayout->addWidget(this->_modifyColorButton);

    this->_duplicateColorButton = new QPushButton("Dupliquer la couleur courrante", this);
    QObject::connect(this->_duplicateColorButton, SIGNAL(released()), this, SLOT(duplicateCurrent()));
    this->_mainLayout->addWidget(this->_duplicateColorButton);

    this->_eraseColorButton = new QPushButton("Effacer la couleur courrante de la liste", this);
    QObject::connect(this->_eraseColorButton, SIGNAL(released()), this, SLOT(eraseSelectedColor()));
    this->_mainLayout->addWidget(this->_eraseColorButton);

    this->_chooseColorButton = new QPushButton("Valider", this);
    QObject::connect(this->_chooseColorButton, &QPushButton::clicked, this, &ColorPickerWidget::close);
    this->_mainLayout->addWidget(this->_chooseColorButton);

    this->setFrameColor(this->_currentColor);

    this->setWindowTitle("Couleur courrante");
    this->setWindowIcon(QIcon(":/icon/ressource/image/icon/icon.png"));

    this->addColor(QColorConstants::Black);

    QObject::connect(this->_colorListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseColor(QListWidgetItem*)));
    QObject::connect(this->_colorListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyColor(QListWidgetItem*)));
}

ColorPickerWidget::~ColorPickerWidget() {
    delete this->_colorListWidget;
    delete this->_currentColorLayout;
    delete this->_currentColorLabel;
    delete this->_currentColorFrame;
    delete this->_addColorButton;
    delete this->_modifyColorButton;
    delete this->_chooseColorButton;
    delete this->_duplicateColorButton;
    delete this->_mainLayout;
}

void ColorPickerWidget::setCurrentColor(const QColor & color) {
    if(color.isValid()) {
        QListWidgetItem * item = new QListWidgetItem(this->_colorListWidget);
        item->setBackground(QBrush(color));
        this->_currentColor = color;
        this->setFrameColor(this->_currentColor);
    }
}


void ColorPickerWidget::setFrameColor(const QColor & color) {
    if(color.isValid()) {
        QPalette palette;
        palette.setColor(QPalette::Window, color);
        this->_currentColorFrame->setAutoFillBackground(true);
        this->_currentColorFrame->setPalette(palette);
    }
}

void ColorPickerWidget::addColor() {
    this->addColor(QColorDialog::getColor(Qt::white, this, "Choix de la couleur"));
}

void ColorPickerWidget::addColor(const QColor & color) {
    if(color.isValid()) {
        QListWidgetItem *item = new QListWidgetItem(this->_colorListWidget);
        item->setBackground(QBrush(color));
    }
}

void ColorPickerWidget::eraseSelectedColor() {
    this->_colorListWidget->takeItem(this->_colorListWidget->currentRow());
}

void ColorPickerWidget::eraseColor() {
    this->eraseColor(this->_colorListWidget->currentItem()->background().color());
}

void ColorPickerWidget::eraseColor(const QColor & color) {
    if(color.isValid()) {
        for(int i = 0; i < this->_colorListWidget->count() ; i++) {
            if(this->_colorListWidget->item(i)->background().color() == color) {
                this->_colorListWidget->takeItem(i);
            }
        }
    }
}

void ColorPickerWidget::modifyColor() {
    this->modifyColor(this->_colorListWidget->currentItem());
}

void ColorPickerWidget::modifyColor(QListWidgetItem* item) {
    QListWidgetItem * selectedItem = item;
    if(selectedItem) {
        QColor color = QColorDialog::getColor(selectedItem->background().color(), this, "Modification de l'image");
        if (color.isValid()) {
            selectedItem->setBackground(QBrush(color));
            this->_currentColor = color;
            this->setFrameColor(color);
            emit this->currentColorChange(this->_currentColor);
        }
    }
}

void ColorPickerWidget::chooseColor() {
    this->_currentColor = this->_colorListWidget->currentItem()->background().color();
    this->setFrameColor(this->_currentColor);
    emit this->currentColorChange(this->_currentColor);
    this->close();
}

void ColorPickerWidget::chooseColor(QListWidgetItem * item) {
    this->_currentColor = item->background().color();
    this->setFrameColor(this->_currentColor);
    emit this->currentColorChange(this->_currentColor);
    qDebug() << "Color Selected !" << this->_currentColor;
}

void ColorPickerWidget::duplicateCurrent() {
    this->addColor(this->currentColor());
}

