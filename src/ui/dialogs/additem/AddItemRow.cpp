//
// Created by max on 28/03/17.
//

#include <data/DbHandler.h>
#include "AddItemRow.h"

AddItemRow::AddItemRow(QWidget * parent)
: QWidget(parent)
{
    itemLayout = new QHBoxLayout;
    itemLayout->setSpacing(1);
    itemLayout->setContentsMargins(0, 0, 0, 0);

    itemName   = new QLineEdit;
    QRegExpValidator * validator = new QRegExpValidator;
    QRegExp regExp;
    regExp.setPatternSyntax(QRegExp::Wildcard);
    regExp.setPattern("?*");
    validator->setRegExp(regExp);
    itemName->setValidator(validator);

    itemPrice = new QLineEdit;
    itemPrice->setValidator(new QDoubleValidator(-10000, 10000, 2));

    itemCategory = createCategoryCombobox();

    itemLayout->addWidget(itemName, 6);
    itemLayout->addWidget(itemPrice, 1);
    itemLayout->addWidget(itemCategory, 3);

    setLayout(itemLayout);
    setMinimumHeight(20);

    connect(itemName, SIGNAL(textChanged(QString)), this, SLOT(onAnyContentChanged()));
    connect(itemPrice, SIGNAL(textChanged(QString)), this, SLOT(onAnyContentChanged()));
    connect(itemCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(onAnyContentChanged()));
}

QComboBox *
AddItemRow::createCategoryCombobox()
{
    QComboBox * comboBox = new QComboBox;

    QSqlQuery query ("SELECT id, name FROM Category ORDER BY name COLLATE NOCASE ASC;");
    DbHandler::getInstance()->getDatabase().exec();

    while (query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();

        comboBox->addItem(name, QVariant(id));
    }
    comboBox->setCurrentIndex(-1);

    return comboBox;
}

bool
AddItemRow::rowValid() const
{
    return itemName->hasAcceptableInput() && itemPrice->hasAcceptableInput()
            && (itemCategory->currentIndex() >= 0);
}

std::tuple<QString, QString, int>
AddItemRow::getValues() const
{
    std::tuple<QString, QString, int> const tuple = std::make_tuple(itemName->text(), itemPrice->text(),
                                                                    itemCategory->currentData().toInt());
    return tuple;
}

void
AddItemRow::onAnyContentChanged()
{
    emit contentChanged();
}

void 
AddItemRow::setValues(QString const& name, QString const& price, int const& categoryId)
{
    itemName->setText(name);
    itemPrice->setText(price);
    
    int const index = itemCategory->findData(categoryId);
    if (index != -1) itemCategory->setCurrentIndex(index);
    else std::fprintf(stderr, "CategoryID %d not found for combo box.\n", categoryId);
}
