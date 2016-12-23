//
// Created by max on 17/11/16.
//

#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QComboBox>

#include <data/DateRangeFilter.h>

class DateFilterPane : public QWidget
{
    Q_OBJECT
signals:
    void dateRangeChanged();
public:
    friend class PlotTab;
    friend class ChartTab;
    DateFilterPane() = delete;
    DateFilterPane(QWidget * parent, QDate const& start, QDate const& end);
    ~DateFilterPane() = default;
    DateFilterPane(DateFilterPane const&) = delete;
    DateFilterPane& operator= (DateFilterPane const&) = delete;

    bool isActive() const;
    std::pair<QDate, QDate> getRange() const;

    void setValidRange(std::pair<QDate, QDate> const&);

protected:
    void rebuildComboBox();

public slots:
    void onDateRangeChanged(std::pair<QDate, QDate>);

protected slots:
    void onClickReset();
    void onStartDateChanged(QDate);
    void onEndDateChanged(QDate);
    void onSelectedComboBoxItem(int);
private:
    QHBoxLayout * mainLayout;

    QComboBox * comboBox;

    QDate start, end;

    std::vector<DateRangeFilter> filters;
};



