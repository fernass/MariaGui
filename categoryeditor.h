#ifndef CATEGORYEDITOR_H
#define CATEGORYEDITOR_H

#include "globaldata.h"

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDialogButtonBox>

class categoryEditor : public QDialog
{
    Q_OBJECT

public:
    categoryEditor(globaldata*, QWidget* parent = nullptr, category* = nullptr);
private slots:
    int addNewKeyrodsClicked(void);
    int okClicked(void);
private:
    QHBoxLayout* hl_Main;
    QVBoxLayout* vl_left;
    QVBoxLayout* vl_right;
    QHBoxLayout* hl_Cat;
    QHBoxLayout* hl_Kw;
    QScrollArea* sa;
    QVector<QLineEdit*> leKeywords_vec;
    QLineEdit* leCategory;
    QLabel* lblCategory;
    QLabel* lblKeywords;
    QPushButton* pbNewKeyword;
    QPushButton* pbOk;
    QPushButton* pbCancel;
    QDialogButtonBox* bb;
    globaldata* data;

    const int numKeywordBoxes = 3;
};

#endif // CATEGORYEDITOR_H
