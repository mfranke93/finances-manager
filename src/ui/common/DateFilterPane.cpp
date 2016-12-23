//
// Created by max on 17/11/16.
//

#include "DateFilterPane.h"

DateFilterPane::DateFilterPane(QWidget * parent, QDate const& start, QDate const& end)
: QWidget(parent), start(start), end(end)
{
    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    comboBox = new QComboBox;
    mainLayout->addWidget(comboBox, 1);
    mainLayout->addStretch(3);

    setLayout(mainLayout);
    setMaximumHeight(40);

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelectedComboBoxItem(int)));
}

void
DateFilterPane::setValidRange(std::pair<QDate, QDate> const& range)
{
    if (range.first != start || range.second != end)
    {
        start = range.first;
        end = range.second;

        rebuildComboBox();
    }
}

void
DateFilterPane::onClickReset()
{
    rebuildComboBox();
}

void
DateFilterPane::onEndDateChanged(QDate dummy)
{
    emit dateRangeChanged();
}

void
DateFilterPane::onStartDateChanged(QDate dummy)
{
    emit dateRangeChanged();
}

std::pair<QDate, QDate>
DateFilterPane::getRange() const
{
    int const idx = comboBox->currentIndex();
    if (idx >= 0 && static_cast<size_t>(idx) < filters.size())
    {
        DateRangeFilter drf = filters.at(idx);
        return drf.range();
    }

    return std::make_pair(
            start, end
    );
}

void
DateFilterPane::onDateRangeChanged(std::pair<QDate, QDate> range)
{
    // TODO cleanup all this mess

    //onClickReset();
    emit dateRangeChanged();
}

void
DateFilterPane::rebuildComboBox()
{
    if (comboBox == nullptr) return;
    comboBox->clear();
    filters.clear();

    // full range
    {
        QDate e = std::max(end, QDate::currentDate());
        DateRangeFilter drf (start, e);
        comboBox->addItem("All time");
        filters.push_back(drf);
    }

    comboBox->insertSeparator(1);
    filters.push_back(DateRangeFilter{}); // for indexing. TODO: not so pretty

    // last week
    {
        QDate e = std::max(end, QDate::currentDate());
        QDate s = std::max(e.addDays(-7), start);
        DateRangeFilter drf(s, e);
        comboBox->addItem("Last 7 days");
        filters.push_back(drf);
    }

    // last month
    {
        QDate e = std::max(end, QDate::currentDate());
        QDate s = std::max(e.addMonths(-1), start);
        DateRangeFilter drf(s, e);
        comboBox->addItem("Last month");
        filters.push_back(drf);
    }

    // last year
    {
        QDate e = std::max(end, QDate::currentDate());
        QDate s = std::max(e.addYears(-1), start);
        DateRangeFilter drf(s, e);
        comboBox->addItem("Last year");
        filters.push_back(drf);
    }

    comboBox->insertSeparator(5);
    filters.push_back(DateRangeFilter{}); // for indexing. TODO: not so pretty

    // add for all months
    bool notLastMonth {true};
    for (QDate q = start; q <= end || notLastMonth; q = q.addMonths(1))
    {
        QDate startOfMonth (q.year(), q.month(), 1);
        if (start > startOfMonth) startOfMonth = start;
        QDate endOfMonth (q.year(), q.month(), q.daysInMonth());
        if (end < endOfMonth) endOfMonth = end;
        if (q > end)
        {
            notLastMonth = false;
        }

        DateRangeFilter drf (startOfMonth, endOfMonth);
        if (notLastMonth || drf.contains(end))
        {
            QString monthName = startOfMonth.longMonthName(startOfMonth.month());
            monthName += QString(" ") + QString::number(startOfMonth.year());

            comboBox->addItem(monthName);
            filters.push_back(drf);
        }
    }
}

void
DateFilterPane::onSelectedComboBoxItem(int idx)
{
    if (idx >= 0 && static_cast<size_t>(idx) < filters.size())
    {
        DateRangeFilter drf = filters.at(idx);
        onDateRangeChanged(drf.range());
    }
}
