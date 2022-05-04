#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QDataStream>

class dataset;

class category
{
public:
    category();
    category(QString);
    category(QString, QStringList);
    category(category&);
    ~category();
    int read_cvs(QString csv_file);

    void set_type(QString);
    void set_keyword(QString);
    void set_dataset(dataset*);
    void set_average(float&);
    void set_count(uint32_t&);

    QStringList get_keywords();
    QString get_type();
    float get_average(void);
    uint32_t get_count(void);
    QVector<dataset*>& get_dataset_vec(void);

    void updateCategory(category&);


    friend QDataStream& operator>>(QDataStream&, category&);
    friend QDataStream& operator<<(QDataStream&, const category&);

private:
    QString type;
    QStringList keywords;
    QVector<dataset*> dataset_vec;
    float average; // average rating of datasets belonging to the category
    uint32_t count; //number of datasets belonging to the category
};


#endif // CATEGORY_H
