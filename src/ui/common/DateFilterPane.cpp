//
// Created by max on 17/11/16.
//

#include "DateFilterPane.h"

DateFilterPane::DateFilterPane(QWidget * parent, QDate const& start, QDate const& end)
: QWidget(parent)
{
    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    startEdit = new QDateEdit(start);
    startEdit->setCalendarPopup(true);
    startEdit->setMinimumDate(start);
    startEdit->setMaximumDate(end);

    endEdit = new QDateEdit(end);
    endEdit->setCalendarPopup(true);
    endEdit->setMinimumDate(start);
    endEdit->setMaximumDate(end);

    resetButton = new QPushButton("Reset");

    mainLayout->addWidget(startEdit, 10);
    mainLayout->addWidget(endEdit, 10);
    mainLayout->addStretch(4);
    mainLayout->addWidget(resetButton, 4);

    setLayout(mainLayout);
    setMaximumHeight(40);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(onClickReset()));
    connect(startEdit, SIGNAL(dateChanged(QDate)), this, SLOT(onStartDateChanged(QDate)));
    connect(endEdit, SIGNAL(dateChanged(QDate)), this, SLOT(onEndDateChanged(QDate)));
}

void
DateFilterPane::setValidRange(std::pair<QDate, QDate> const& range)
{
    startEdit->setMinimumDate(range.first);
    endEdit->setMinimumDate(range.first);

    startEdit->setMaximumDate(range.second);
    endEdit->setMaximumDate(range.second);

    if (!startEdit->hasAcceptableInput())
    {
        startEdit->setDate(range.first);
    }
    if (!endEdit->hasAcceptableInput())
    {
        endEdit->setDate(range.second);
    }
}

void
DateFilterPane::onClickReset()
{
    startEdit->setDate(startEdit->minimumDate());
    endEdit->setDate(endEdit->maximumDate());
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
    return std::make_pair(
        startEdit->date(),
        endEdit->date()
    );
}