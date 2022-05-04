#include "csvreader.h"

#include <QFile>
#include <QTextStream>

csv_reader::csv_reader()
{
}

//#############################################################################
//#############################################################################

csv_reader::csv_reader(QString _filename)
{
    filename = _filename;
}

//#############################################################################
//#############################################################################

csv_reader::~csv_reader()
{
}

//#############################################################################
//#############################################################################

void csv_reader::init_csv_reader(QString csv_file)
{
    filename = csv_file;
}

//#############################################################################
//#############################################################################

int csv_reader::read_csv()
{
    QFile csvFile(filename);

    if(csvFile.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QTextStream fs(&csvFile);

        while (!fs.atEnd())
        {
            QString s;
            s = fs.readLine();
            csv_vec.push_back(s);
        }

    }
    else
        return -1;

    return 0;
}

//#############################################################################
//#############################################################################

QStringList& csv_reader::get_csv_vec()
{
    return csv_vec;
}
