#include "dataset.h"
#include "category.h"

dataset::dataset(/* args */)
{
}

//#############################################################################
//#############################################################################
dataset::dataset(dataset& _ds)
{
    date = _ds.date;
    rating = _ds.rating;
    message = _ds.message;
    categories = _ds.categories;
}

//#############################################################################
//#############################################################################
dataset::~dataset()
{
}

//#############################################################################
//#############################################################################

void dataset::set_date(QString& _date_)
{
    date = _date_;
}


//#############################################################################
//#############################################################################

void dataset::set_rating(QString& _rating_)
{
    rating = _rating_;
}

//#############################################################################
//#############################################################################

void dataset::set_message(QString& _message_)
{
    message = _message_;
}

//#############################################################################
//#############################################################################

QString dataset::get_date()
{
    return date;
}

//#############################################################################
//#############################################################################

QString dataset::get_rating()
{
    return rating;
}

//#############################################################################
//#############################################################################

QString dataset::get_message()
{
    return message;
}

//#############################################################################
//#############################################################################
void dataset::add_category(category* _cat_)
{
    categories.insert(_cat_);
}

//#############################################################################
//#############################################################################

QSet<category*>& dataset::get_category(void){
    return categories;
}


//#############################################################################
//#############################################################################

QDataStream& operator>>(QDataStream& dataStream, dataset& ds)
{
//    uint32_t size;
//    category* cat = new category();

    dataStream >> ds.date;
    dataStream >> ds.rating;
    dataStream >> ds.message;

/*    dataStream >> size;
    for(uint32_t i=0; i<size; i++)
    {
        dataStream >> *cat;
        ds.categories.insert(cat);
    }*/

    return dataStream;
}

//#############################################################################
//#############################################################################

QDataStream& operator<<(QDataStream& dataStream, const dataset& ds)
{
    dataStream << ds.date;
    dataStream << ds.rating;
    dataStream << ds.message;

/*    uint32_t size = ds.categories.size();
    dataStream << size;
    for(auto& i : ds.categories)
    {
        dataStream << *i;
    }*/
    return dataStream;
}

//#############################################################################
//#############################################################################
bool dataset::check_type(QString type)
{
    bool found = false;

    for(auto& cat : categories)
    {
        if(cat->get_type().contains(type)) return true;
    }
    return found;
}
//#############################################################################
//#############################################################################
void dataset::delete_category(category* _cat)
{
    for(int i=0; i<categories.size(); i++)
    {
        QSet<category*>::Iterator iter = categories.find(_cat);
        categories.erase(iter);
    }
}
