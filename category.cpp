#include "category.h"
#include "config.h"
#include "dataset.h"


category::category()
{
}

//#############################################################################
//#############################################################################

category::category(QString _type_)
{
    type = _type_;
}

//#############################################################################
//#############################################################################

category::category(QString _type_, QStringList _keywords_)
{
    type = _type_;
    keywords = _keywords_;
}

//#############################################################################
//#############################################################################
category::category(category& _cat)
{
    type = _cat.type;
    keywords = _cat.keywords;
    dataset_vec = _cat.dataset_vec;
}

//#############################################################################
//#############################################################################

category::~category()
{
}


//#############################################################################
//#############################################################################

void category::set_type(QString _type_)
{
    this->type = _type_;
}

//#############################################################################
//#############################################################################

void category::set_keyword(QString _keyword_)
{
    if(!_keyword_.isEmpty()) this->keywords.push_back(_keyword_);
}

//#############################################################################
//#############################################################################
QStringList category::get_keywords()
{
    return keywords;
}

//#############################################################################
//#############################################################################

QString category::get_type(){
    return type;
}

//#############################################################################
//#############################################################################

QDataStream& operator>>(QDataStream& dataStream, category& cat)
{
    uint32_t size;
    QString s;
//    dataset* ds = new dataset;

    dataStream >> cat.type;
    dataStream >> size;
    for(uint32_t i=0; i< size; i++)
    {
        dataStream >> s;
        cat.keywords.push_back(s);
    }

/*    dataStream >> size;
    for(uint32_t i=0; i<size; i++)
    {
        dataStream >> *ds;
        cat.dataset_vec.push_back(ds);
    }*/

    return dataStream;
}

//#############################################################################
//#############################################################################

QDataStream& operator<<(QDataStream& dataStream, const category& cat)
{
    uint32_t size;
//    dataset* ds;

    dataStream << cat.type;
    size = cat.keywords.size();
    dataStream << size;
    for(uint32_t i=0; i< size; i++)
    {
        dataStream << cat.keywords[i];
    }

/*    size = cat.dataset_vec.size();
    dataStream << size;
    for(uint32_t i=0; i<size; i++)
    {
        ds = cat.dataset_vec[i];
        dataStream << *ds;
    }*/

    return dataStream;
}

//#############################################################################
//#############################################################################
void category::set_dataset(dataset* ds)
{
    dataset_vec.push_back(ds);
}

//#############################################################################
//#############################################################################
void category::set_average(float& _average)
{
    average = _average;
}

//#############################################################################
//#############################################################################
void category::set_count(uint32_t& _count)
{
    count = _count;
}

//#############################################################################
//#############################################################################
float category::get_average(void)
{
    average = 0;
    for(auto& ds : dataset_vec)
    {
        int rating = ds->get_rating().toInt();
        average+= rating;
    }
    average /= dataset_vec.size();
    return average;
}

//#############################################################################
//#############################################################################
uint32_t category::get_count(void){
    count = dataset_vec.size();
    return count;
}

//#############################################################################
//#############################################################################
void category::updateCategory(category& _cat)
{
    type = _cat.type;
    keywords = _cat.keywords;
    dataset_vec = _cat.dataset_vec;
    average = _cat.average; // average rating of datasets belonging to the category
    count = _cat.count; //number of datasets belonging to the category
}

//#############################################################################
//#############################################################################

QVector<dataset*>& category::get_dataset_vec(void)
{
    return dataset_vec;
}
