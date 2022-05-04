#include "statisticswindow.h"
#include "ui_statisticswindow.h"

statisticswindow::statisticswindow(globaldata* data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::statisticswindow)
{
    ui->setupUi(this);

    QVector<category*> cat_vec = data->get_ctagories_vec();
    QVector<dataset*> data_vec = data->get_data_vec();

    uint32_t size = cat_vec.size();

    modelStatistics = new QStandardItemModel(size + 1,3, this); // +1 for the total summary of all datasets
    modelStatistics->setHorizontalHeaderItem(0,new QStandardItem("Kategorie"));
    modelStatistics->setHorizontalHeaderItem(1,new QStandardItem("Anzahl Datensätze"));
    modelStatistics->setHorizontalHeaderItem(2,new QStandardItem("Durchschnittliche Bewertung"));

    ui->tvStatistics->setModel(modelStatistics);

    ui->tvStatistics->setColumnWidth(0,200);
    ui->tvStatistics->setColumnWidth(1,75);
    ui->tvStatistics->setColumnWidth(2,100);
    ui->tvStatistics->horizontalHeader()->setStretchLastSection(true);

    for(uint32_t i=0; i< size; i++)
    {
        uint32_t count = cat_vec[i]->get_count();
        float average = cat_vec[i]->get_average();

        QStandardItem* typeItem = new QStandardItem(cat_vec[i]->get_type());
        modelStatistics->setItem(i,0,typeItem);
        QStandardItem* countItem = new QStandardItem(QString::number(count));
        modelStatistics->setItem(i,1,countItem);
        QStandardItem* averageItem = new QStandardItem(QString::number(average));
        modelStatistics->setItem(i,2,averageItem);
    }

    float overall_average = 0;
    uint32_t num_datasets = data_vec.size();
    for(auto& ds : data_vec)
    {
        overall_average += ds->get_rating().toFloat();
    }

    overall_average /= num_datasets;
    QStandardItem* typeItem = new QStandardItem("Alle Datensätze");
    modelStatistics->setItem(size,0,typeItem);
    QStandardItem* countItem = new QStandardItem(QString::number(num_datasets));
    modelStatistics->setItem(size,1,countItem);
    QStandardItem* averageItem = new QStandardItem(QString::number(overall_average));
    modelStatistics->setItem(size,2,averageItem);
}

//#############################################################################
//#############################################################################
statisticswindow::~statisticswindow()
{
    delete ui;
}
