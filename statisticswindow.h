#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include "globaldata.h"

#include <QDialog>
#include <QWidget>
#include <QStandardItemModel>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class statisticswindow; }
QT_END_NAMESPACE

class statisticswindow : public QDialog
{
    Q_OBJECT
public:
    explicit statisticswindow(globaldata*, QWidget *parent = nullptr);

public:
    ~statisticswindow();

signals:

private:
    Ui::statisticswindow* ui;

    QStandardItemModel* modelStatistics;
};

#endif // STATISTICSWINDOW_H
