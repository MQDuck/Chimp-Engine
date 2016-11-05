#include "ChimpEditor.h"
#include "ui_ChimpEditor.h"

ChimpEditor::ChimpEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChimpEditor)
{
    ui->setupUi(this);
}

ChimpEditor::~ChimpEditor()
{
    delete ui;
}
