//
// Created by max on 10/01/17.
//

#pragma once


#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>

class SearchRecipientDialog : public QDialog
{
    Q_OBJECT

    /*
     * UI element: search for a recipient (or add a new one).
     *
     * Layout:
     *
     *      [ SEARCH BAR TEXT LINE EDIT ] [ Search ]
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
    void onClickSearch();

    void recipientIdChanged(int);
    void searchBarContentChanged(QString);

private:
    QVBoxLayout * toplevelLayout;
    QHBoxLayout * searchbarLayout;
    QHBoxLayout * addOkayLayout;

    QLineEdit   * searchBar;
    QPushButton * searchButton;
    QScrollArea * searchResultScrollView;
    QPushButton * cancelButton;
    QPushButton * addButton;
    QPushButton * okayButton;

    /**
     * Selected recipient ID.
     */
    int _recId {-1};
};



