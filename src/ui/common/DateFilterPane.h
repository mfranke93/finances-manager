//
// Created by max on 17/11/16.
//

#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDateEdit>

class DateFilterPane : public QWidget
{
    Q_OBJECT
signals:
    void dateRangeChanged();
public:
    friend class PlotTab;
    DateFilterPane() = delete;
    DateFilterPane(QWidget * parent, QDate const& start, QDate const& end);
    ~DateFilterPane() = default;
    DateFilterPane(DateFilterPane const&) = delete;
    DateFilterPane& operator= (DateFilterPane const&) = delete;

    bool isActive() const;
    std::pair<QDate, QDate> getRange() const;

    void setValidRange(std::pair<QDate, QDate> const&);

public slots:
    void onDateRangeChanged(std::pair<QDate, QDate>);

protected slots:
    void onClickReset();
    void onStartDateChanged(QDate);
    void onEndDateChanged(QDate);
private:
    QHBoxLayout * mainLayout;

    QPushButton * resetButton;
    QPushButton * startButton;
    QPushButton * endButton;

    QDateEdit * startEdit;
    QDateEdit * endEdit;
};



