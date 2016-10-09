//
// Created by max on 30/09/16.
//

#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QSqlError>
#include "ui/table/ExpenditureView.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    QTabWidget * tabs;
};
