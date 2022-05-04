#include "globaldata.h"
#include "config.h"

#include <QFile>
#include <QTextStream>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <codecvt>

using namespace std;

globaldata::globaldata()
{
    category* cat = new category("Empty");
    categories_vec.push_back(cat);
}

//#############################################################################
//#############################################################################

globaldata::~globaldata()
{
}


//#############################################################################
//#############################################################################

int globaldata::tokenize_data(QStringList raw_data)
{
    for(auto &s : raw_data)
    {
        int counter = 0;

        dataset* ds = new dataset();
        QStringList keywords = s.split(qdelimiter);

        for(QString token : keywords)
        {
            if(counter==0) //date
            {
                ds->set_date(token);
            }
            else if(counter==1) //rating
            {
                ds->set_rating(token);
            }
            else if(counter==2) //message
            {
                ds->set_message(token);
            }
            else
            {
                break;
            }
            counter++;
        }

        data_vec.push_back(ds);

    }
    return 0;
}


//#############################################################################
//#############################################################################

QVector<dataset*>& globaldata::get_data_vec(void)
{
    return this->data_vec;
}

//#############################################################################
//#############################################################################

QVector<category*>& globaldata::get_ctagories_vec(void)
{
    return this->categories_vec;
}

//#############################################################################
//#############################################################################

void globaldata::export_data()
{
    QFile myfile("export_datasets.csv");
    QFile myfile1("export_datasets.csv");

//    locale dt("de_DE.utf-8");
//    std::locale utf8_locale(std::locale());
//    myfile.imbue(dt);
//    myfile.open("data_categorised.csv", std::ios::app);
    myfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&myfile);
    myfile1.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out1(&myfile1);

    for(auto &i : data_vec)
    {
        QSet<category*> cat = i->get_category();
        if(!cat.empty())
        {
            out << i->get_date() <<L";"<< i->get_rating() <<L";"<< i->get_message() << L";";
            for(auto &c : cat)
            {
                out << c->get_type() <<L";";
            }
            out << L"\n";
        }
        else
        {
            if(!i->get_message().isEmpty())
            {
                out1 << i->get_date() <<L";"<< i->get_rating() <<L";"<< i->get_message() << L";";
                for(auto &c : cat)
                {
                    out1 << c->get_type() <<L";";
                }
                out1 << L"\n";

            }
        }
    }
    myfile.flush();
    myfile.close();
    myfile1.flush();
    myfile1.close();
}

//#############################################################################
//#############################################################################
int globaldata::analyse_data()
{
    int pos;
    for(auto &ds : data_vec)
    {
        QString msg = ds->get_message();

        for(auto &cat : categories_vec)
        {
            if(msg.isEmpty() && cat->get_type().contains("Empty"))
            {
                if(!ds->check_type("Empty"))
                {
                    cat->set_dataset(ds);
                    ds->add_category(cat);
                }
            }
            else
            {
                QStringList keywords = cat->get_keywords();
                for(QString& kw : keywords)
                {
                    pos = msg.indexOf(kw,Qt::CaseSensitivity::CaseInsensitive);
                    if(pos != -1)
                    {
                        cat->set_dataset(ds);
                        ds->add_category(cat);
                    }
                }
            }
        }
    }
    return 0;
}

//#############################################################################
//#############################################################################
void globaldata::add_category(category& _cat)
{
    int index = this->category_is_available(_cat.get_type());
    if(index >= 0)
    {
        categories_vec[index]->updateCategory(_cat);
    }
    else
    {
        category* cat = new category(_cat);
        categories_vec.push_back(cat);
    }
    emit categotries_changed();
}

//#############################################################################
//#############################################################################
void globaldata::delete_category(QString _type)
{
    for(int i=0; i<categories_vec.size(); i++)
    {
         if(categories_vec[i]->get_type().contains(_type))
        {
             QVector<dataset*> dataset_vec = categories_vec[i]->get_dataset_vec();
             for(auto& ds : dataset_vec)
             {
                 ds->delete_category(categories_vec[i]);
             }
             categories_vec.remove(i,1);
             break;
        }
    }
}

//#############################################################################
//#############################################################################
int globaldata::category_is_available(QString _type)
{
    int isAvailable = -1;
    for(int i=0; i<categories_vec.size(); i++)
    {
        if(categories_vec[i]->get_type().contains(_type))
        {
            isAvailable = i;
            break;
        }
    }
    return isAvailable;
}

//#############################################################################
//#############################################################################
void globaldata::add_dataset(dataset& _ds)
{
    dataset* ds = new dataset(_ds);
    data_vec.push_back(ds);
}

//#############################################################################
//#############################################################################
int globaldata::save_data(QDataStream& stream)
{
    uint32_t size;

    size = data_vec.size();
    stream << size;
    for(uint32_t i=0; i<size; i++)
    {
        stream << *data_vec[i];
    }

    size = categories_vec.size();
    stream << size;
    for(uint32_t i=0; i<size; i++)
    {
        stream << *categories_vec[i];
    }

    return 0;
}


//#############################################################################
//#############################################################################
int globaldata::restore_data(QDataStream& stream)
{
    uint32_t size;

    stream >> size;
    for(uint32_t i=0; i<size; i++)
    {
        dataset ds;
        stream >> ds;
        this->add_dataset(ds);
    }

    stream >> size;
    for(uint32_t i=0; i<size; i++)
    {
        category cat;
        stream >> cat;
        if(cat.get_type().contains("Empty")) continue; //the Empty category is a standard one added when "data" is constructed
        this->add_category(cat);

    }

    return 0;
}

//#############################################################################
//#############################################################################
category* globaldata::get_Category(QString _type)
{
    bool found = false;
    int pos = -1;

    for(int i=0; i<categories_vec.size(); i++)
    {
        if(categories_vec[i]->get_type().contains(_type))
        {
            found = true;
            pos = i;
            break;
        }
    }
    if(found) return categories_vec[pos];
    return nullptr;
}
