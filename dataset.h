#ifndef DATASET_H
#define DATASET_H

#include "category.h"

#include <QSet>
#include <QString>
#include <QDataStream>

//QT_FORWARD_DECLARE_CLASS(category)
//class category;

class dataset
{
public:
    dataset();
    dataset(dataset&);
    ~dataset();
    void set_date(QString&);
    void set_rating(QString&);
    void set_message(QString&);
    QString get_date();
    QString get_rating();
    QString get_message();
    void add_category(category*);
    QSet<category*>& get_category(void);
    bool check_type(QString);
    void delete_category(category*);

    friend QDataStream& operator<<(QDataStream&, const dataset&);
    friend QDataStream& operator>>(QDataStream&, dataset&);

private:
    QString date;
    QString rating;
    QString message;
    QSet<category*> categories;
};





#endif // DATASET_H
