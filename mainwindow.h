#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "csvreader.h"
#include "globaldata.h"

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_data_TableView(void);
    void init_Gui(void);

private slots:
    int newProject(void);
    int openCSV(void);
    int save_project_state_as();
    int save_project_state();
    int restore_project_state();
    int openCategoryEditor(void);
    void update_category_TableView(void);
    void applyCategories(void);
    void sortColumn(int index);
    void showStatisticsWindow(void);
    void editCategory(void);
    void deleteCategory(void);
    void exportData(void);

private:
    Ui::MainWindow *ui;
    QHeaderView* header;
    globaldata* data;
    csv_reader* reader;
    QStandardItemModel* modelDatasets;
    QStandardItemModel* modelCategories;

    QString saveFile; //name of project file. Only available, if saved as before
};
#endif // MAINWINDOW_H
