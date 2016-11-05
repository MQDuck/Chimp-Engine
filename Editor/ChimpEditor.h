#ifndef CHIMPEDITOR_H
#define CHIMPEDITOR_H

#include <QMainWindow>

namespace Ui {
class ChimpEditor;
}

class ChimpEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ChimpEditor(QWidget *parent = 0);
    ~ChimpEditor();
    
private:
    Ui::ChimpEditor *ui;
};

#endif // CHIMPEDITOR_H
