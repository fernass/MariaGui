#ifndef CSVREADER_H
#define CSVREADER_H

#include <QString>
#include <QStringList>

class csv_reader
{
private:
    QStringList csv_vec;
    QString filename;

public:
    csv_reader();
    csv_reader(QString);
    ~csv_reader();
    void init_csv_reader(QString);
    int read_csv();
    QStringList& get_csv_vec();
};


#endif // CSVREADER_H
