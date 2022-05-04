#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "categoryeditor.h"
#include "statisticswindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_Gui();
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newProject);
    connect(ui->actionimport, &QAction::triggered, this, &MainWindow::openCSV);
    connect(ui->action_ffnen, &QAction::triggered, this, &MainWindow::restore_project_state);
    connect(ui->actionSpeichern_unter, &QAction::triggered, this, &MainWindow::save_project_state);
    connect(ui->pbNew, &QPushButton::released,this, &MainWindow::openCategoryEditor);
    connect(this->data, &globaldata::categotries_changed, this, &MainWindow::update_category_TableView);
    connect(ui->pbApplyCat, &QPushButton::released, this, &MainWindow::applyCategories);
    connect(ui->pbStatistics, &QPushButton::released, this, &MainWindow::showStatisticsWindow);
    connect(header, SIGNAL(sectionClicked(int)),this, SLOT(sortColumn(int)));
    connect(ui->pbEdit, &QPushButton::released, this, &MainWindow::editCategory);
    connect(ui->pbDeleteCategory, &QPushButton::released, this, &MainWindow::deleteCategory);

}

//#############################################################################
//#############################################################################
void MainWindow::init_Gui(void)
{
    modelDatasets = new QStandardItemModel(1,4,this);
    modelDatasets->setHorizontalHeaderItem(0,new QStandardItem(QString("Monat")));
    modelDatasets->setHorizontalHeaderItem(1,new QStandardItem(QString("Bewertung")));
    modelDatasets->setHorizontalHeaderItem(2,new QStandardItem(QString("Kommentar")));
    modelDatasets->setHorizontalHeaderItem(3,new QStandardItem(QString("Kategorie")));

    header = ui->tvDatasets->horizontalHeader();
    header->setSortIndicator(0, Qt::AscendingOrder);
    header->setSortIndicatorShown(true);

    ui->tvDatasets->setModel(modelDatasets);

    ui->tvDatasets->setColumnWidth(0,75);
    ui->tvDatasets->setColumnWidth(1,25);
    ui->tvDatasets->setColumnWidth(2,450);
    ui->tvDatasets->horizontalHeader()->setStretchLastSection(true);

    modelCategories = new QStandardItemModel(1,2,this);
    modelCategories->setHorizontalHeaderItem(0, new QStandardItem(QString("Kategorie")));
    modelCategories->setHorizontalHeaderItem(1, new QStandardItem(QString("Stichworte")));

    ui->tvCategories->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvCategories->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tvCategories->setModel(modelCategories);

    ui->tvCategories->setColumnWidth(0,100);
    ui->tvCategories->setColumnWidth(1,400);
//    ui->tvCategories->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tvCategories->horizontalHeader()->setStretchLastSection(true);

    data = new globaldata();
}

//#############################################################################
//#############################################################################
MainWindow::~MainWindow()
{
    delete ui;
}

//#############################################################################
//#############################################################################
int MainWindow::newProject(void)
{

    delete data;
    init_Gui();
    // it is necessary to re-define this connection, because the when a new project is setup the global data instance "data" is deleted and created again.
    // with a custom signal, it is necessary to setup the connection again!
    connect(this->data, &globaldata::categotries_changed, this, &MainWindow::update_category_TableView);

    return 0;
}

//#############################################################################
//#############################################################################
int MainWindow::openCSV()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("CSV Öffnen"), "/", tr("CSV Dateien (*.csv)"));

    reader = new csv_reader(filename);

    if(reader->read_csv())
    {
        return -1;
    }

    QStringList list = reader->get_csv_vec();
    data->tokenize_data(list);
//    data_vec = data->get_data_vec();

    update_data_TableView();

    delete reader;

    return 0;
}

//#############################################################################
//#############################################################################
void MainWindow::update_data_TableView(void)
{
    modelDatasets->clear();
    modelDatasets->setHorizontalHeaderItem(0,new QStandardItem(QString("Monat")));
    modelDatasets->setHorizontalHeaderItem(1,new QStandardItem(QString("Bewertung")));
    modelDatasets->setHorizontalHeaderItem(2,new QStandardItem(QString("Kommentar")));
    modelDatasets->setHorizontalHeaderItem(3,new QStandardItem(QString("Kategorie")));

    ui->tvDatasets->setColumnWidth(0,75);
    ui->tvDatasets->setColumnWidth(1,25);
    ui->tvDatasets->setColumnWidth(2,450);
    ui->tvDatasets->horizontalHeader()->setStretchLastSection(true);

    QVector<dataset*> data_vec = data->get_data_vec();

    std::uint32_t size = data_vec.size();
    for(std::uint32_t i=0; i<size; i++)
    {
        QStandardItem* date = new QStandardItem(data_vec[i]->get_date());
        modelDatasets->setItem(i, 0, date);
        QStandardItem* rating = new QStandardItem(data_vec[i]->get_rating());
        modelDatasets->setItem(i, 1, rating);
        QStandardItem* message = new QStandardItem(data_vec[i]->get_message());
        modelDatasets->setItem(i, 2, message);

        QSet<category*> qs =  data_vec[i]->get_category();
        QString s;
        for(auto& c : qs)
        {
            s.push_back(c->get_type()+"; ");
        }
        QStandardItem* category = new QStandardItem(s);
        modelDatasets->setItem(i,3,category);

    }
}

//#############################################################################
//#############################################################################
int MainWindow::openCategoryEditor(void)
{
    categoryEditor* catEdit = new categoryEditor(data, this);
    return catEdit->exec();
}

//#############################################################################
//#############################################################################
void MainWindow::editCategory(void)
{
    QModelIndexList selection = ui->tvCategories->selectionModel()->selectedRows();
    if(selection.empty())
    {
        QMessageBox mb;
        mb.setText("Bitte vorher eine Kategorie auswählen!");
        mb.exec();
        return;
    }
    QModelIndex index = selection.at(0);
    int row = index.row();
    QStandardItem* item =  modelCategories->item(row, 0);
    QString cat = item->text();
    if(cat.contains("Empty"))
    {
        QMessageBox mb;
        mb.setText("Die Kategorie Empty kann nicht verändert werden!");
        mb.exec();
        return;
    }

    category* c = data->get_Category(cat);

    categoryEditor* catEdit = new categoryEditor(data, this, c);
    catEdit->exec();
}

//#############################################################################
//#############################################################################
void MainWindow::update_category_TableView(void)
{
    modelCategories->clear();
    modelCategories->setHorizontalHeaderItem(0, new QStandardItem(QString("Kategorie")));
    modelCategories->setHorizontalHeaderItem(1, new QStandardItem(QString("Stichworte")));
    ui->tvCategories->setColumnWidth(0,100);
    ui->tvCategories->setColumnWidth(1,400);
    ui->tvCategories->horizontalHeader()->setStretchLastSection(true);

    QVector<category*> categories_vec = data->get_ctagories_vec();

    std::uint32_t size = categories_vec.size();

    for(std::uint32_t i=0; i<size; i++)
    {
        QStandardItem* type = new QStandardItem(categories_vec[i]->get_type());
        modelCategories->setItem(i, 0, type);
        QStringList kw = categories_vec[i]->get_keywords();
        QString s;
        for(auto &j : kw)
        {
            s.append(j+"; ");
        }
        QStandardItem* keywords = new QStandardItem(s);
        modelCategories->setItem(i, 1, keywords);
    }
}

//#############################################################################
//#############################################################################
void MainWindow::applyCategories(void)
{
    QVector<category*> categories_vec = data->get_ctagories_vec();

    if(categories_vec.empty())
    {
        QMessageBox mb;
        mb.setText("Keine Kategorien definiert!");
        mb.exec();
    }
    else
    {
        data->analyse_data();
        update_data_TableView();
    }

}

//#############################################################################
//#############################################################################
void MainWindow::sortColumn(int index)
{
    int i = ui->tvDatasets->horizontalHeader()->sortIndicatorOrder();
    if(i==0)
    {
        modelDatasets->sort(index, Qt::AscendingOrder);
    }
    else
    {
        modelDatasets->sort(index, Qt::DescendingOrder);
    }
}

//#############################################################################
//#############################################################################
int MainWindow::save_project_state()
{
    QString saveFile = QFileDialog::getSaveFileName(this, tr("Datei speichern unter ..."), "/", tr("Maria-Dateien (*.mar)"));
    QFile file(saveFile);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        data->save_data(stream);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Datei kann nicht geöffnet werden");
        msgBox.exec();
        return -1;
    }

    file.flush();
    file.close();

    return 0;
}

//#############################################################################
//#############################################################################
int MainWindow::restore_project_state()
{
    QString openFile = QFileDialog::getOpenFileName(this, tr("Projektdatei öffnen"), "/", tr("Maria-Dateien (*.mar)"));

    QFile file(openFile);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        data->restore_data(stream);

//        file.flush();
        file.close();

        data->analyse_data();
        update_data_TableView();
        update_category_TableView();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Sie müssen eine Projektdatei auswählen");
        msgBox.exec();
        return -1;
    }

    return 0;
}

//#############################################################################
//#############################################################################
void MainWindow::showStatisticsWindow(void)
{
    statisticswindow* stats = new statisticswindow(data, this);
    stats->exec();
}

//#############################################################################
//#############################################################################
void MainWindow::deleteCategory(void)
{
    QModelIndexList selection = ui->tvCategories->selectionModel()->selectedRows();
    if(selection.empty())
    {
        QMessageBox mb;
        mb.setText("Bitte vorher eine Kategorie auswählen!");
        mb.exec();
        return;
    }
    QModelIndex index = selection.at(0);
    int row = index.row();
    QStandardItem* item =  modelCategories->item(row, 0);
    QString cat = item->text();
    if(cat.contains("Empty"))
    {
        QMessageBox mb;
        mb.setText("Die Kategorie Empty kann nicht entfernt werden!");
        mb.exec();
        return;
    }

    modelCategories->takeRow(row);
    data->delete_category(cat);

}
