//
// Created by max on 28/03/17.
//

#pragma once


#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QRegExpValidator>
#include <QRegExp>

class AddItemRow : public QWidget
{
    Q_OBJECT

public:
    AddItemRow(QWidget * parent);
    ~AddItemRow() = default;

    bool rowValid() const;
    std::tuple<QString, QString, int> getValues() const;

signals:
    void contentChanged();

protected:
    static QComboBox * createCategoryCombobox();

protected slots:
    void onAnyContentChanged();

private:
    QHBoxLayout * itemLayout;
    QLineEdit   * itemName;
    QLineEdit   * itemPrice;
    QComboBox   * itemCategory;
};



