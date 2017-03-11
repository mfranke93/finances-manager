//
// Created by max on 10/01/17.
//

#pragma once


#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTableView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <data/RecipientObjectStore.h>

class SearchRecipientDialog : public QDialog
{
    Q_OBJECT

    /*
     * UI element: search for a recipient (or add a new one).
     *
     * Layout:
     *
     *      [ SEARCH BAR TEXT LINE EDIT            ]
     *
     *      [                                      ]
     *      [                                      ]
     *      [        Search results                ]
     *      [                                      ]
     *      [                                      ]
     *
     *      [ Cancel ]       [ Add ]        [ Okay ]
     *
     */
signals:
    /**
     * Gets emitted as true iff search bar content is valid.
     */
    void searchButtonEnabled(bool);
    /**
     * Gets emitted as true iff a search result is selected.
     */
    void okayButtonEnabled(bool);
public:
    SearchRecipientDialog();
    ~SearchRecipientDialog() = default;

    int const& getSelectedRecId() const { return _recId; }

protected slots:
    void onClickCancel();
    void onClickAdd();
    void onClickOkay();

    void recipientIdChanged(int);
    void searchBarContentChanged(QString);

protected:

private:
    QVBoxLayout * toplevelLayout;
    QHBoxLayout * addOkayLayout;

    QLineEdit   * searchBar;
    QScrollArea * searchResultScrollView;
    QTableView  * searchResultTable;
    QPushButton * cancelButton;
    QPushButton * addButton;
    QPushButton * okayButton;

    RecipientObjectStore store;

    /**
     * Selected recipient ID.
     */
    int _recId {-1};
};



