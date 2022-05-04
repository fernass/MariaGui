#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "dataset.h"
#include "category.h"

#include <QStringList>
#include <QString>
#include <QObject>


class globaldata : public QObject
{
    Q_OBJECT
public:
    globaldata();
    ~globaldata();
    int tokenize_data(QStringList);
    int analyse_data();
    void export_data();
    QVector<dataset*>& get_data_vec(void);
    QVector<category*>& get_ctagories_vec(void);
    int tokenize_categories();

    void add_category(category&);
    void add_dataset(dataset&);

    category* get_Category(QString);
    int category_is_available(QString);
    void delete_category(QString);

    int save_data(QDataStream&);
    int restore_data(QDataStream&);
signals:
    void categotries_changed(void);
private:
    QVector<dataset*> data_vec;
    QVector<category*> categories_vec;
};

#endif // GLOBALDATA_H
