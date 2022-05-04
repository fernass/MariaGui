#include "categoryeditor.h"


categoryEditor::categoryEditor(globaldata* _data_, QWidget* parent, category* cat)
    : QDialog(parent)
{
    data = _data_;
    hl_Main = new QHBoxLayout();
    vl_left = new QVBoxLayout();
    vl_right = new QVBoxLayout();
    hl_Cat =  new QHBoxLayout();
    hl_Kw =  new QHBoxLayout();
    sa = new QScrollArea();

    leCategory = new QLineEdit();
    lblCategory = new QLabel("Kategorie");
    lblCategory->setBuddy(leCategory);

    lblKeywords = new QLabel("Stichworte");
    pbNewKeyword = new QPushButton("neues Stichwort");
    pbOk = new QPushButton("OK");
    pbCancel = new QPushButton("abbrechen");
    bb = new QDialogButtonBox();

    bb->setOrientation(Qt::Orientation::Vertical);
    bb->addButton(pbNewKeyword, QDialogButtonBox::ActionRole);
    bb->addButton(pbOk, QDialogButtonBox::ActionRole);
    bb->addButton(pbCancel, QDialogButtonBox::ActionRole);
    vl_right->addWidget(bb);


    hl_Cat->addWidget(lblCategory);
    hl_Cat->addWidget(leCategory);

    hl_Kw->addWidget(lblKeywords);

    int numKeywords;
    QStringList kw;
    if(cat != nullptr)
    {
        kw = cat->get_keywords();
        numKeywords = kw.size();
    }
    else
        numKeywords = numKeywordBoxes;

    for(int i=0; i<numKeywords; i++)
    {
        QLineEdit* le = new QLineEdit();
        leKeywords_vec.push_back(le);
        hl_Kw->addWidget(le);
    }
    vl_left->addLayout(hl_Cat);
    vl_left->addLayout(hl_Kw);

    hl_Main->addLayout(vl_left);
    hl_Main->addLayout(vl_right);

    this->setLayout(hl_Main);

    if(cat != nullptr)
    {
        leCategory->setText(cat->get_type());
        for(int i=0; i<leKeywords_vec.size(); i++)
        {
            leKeywords_vec[i]->setText(kw[i]);
        }
    }

    connect(pbNewKeyword, &QPushButton::released,this, &categoryEditor::addNewKeyrodsClicked);
    connect(pbOk, &QPushButton::released,this, &categoryEditor::okClicked);
    connect(pbCancel, &QPushButton::released,this, &categoryEditor::close);
}

//#############################################################################
//#############################################################################
int categoryEditor::addNewKeyrodsClicked()
{
    QLineEdit* le = new QLineEdit();
    leKeywords_vec.push_back(le);
    hl_Kw->addWidget(le);

    return 0;
}

//#############################################################################
//#############################################################################
int categoryEditor::okClicked(void)
{
    QString type = this->leCategory->text();
    QStringList keywords;
    for(auto i : leKeywords_vec)
    {
        if(!i->text().isEmpty()) keywords.push_back(i->text());
    }
    category cat = category(type, keywords);
    data->add_category(cat);
    this->close();
    return 0;
}
