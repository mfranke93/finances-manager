#include "ChartArea.h"

void
ChartArea::mousePressEvent(QGraphicsSceneMouseEvent * evt)
{
    if (evt->button() == Qt::MouseButton::LeftButton)
    {
        pressScenePos = evt->scenePos().x();
        isValid = true;
    }
}

void
ChartArea::mouseReleaseEvent(QGraphicsSceneMouseEvent * evt)
{
    switch (evt->button())
    {
        case Qt::MouseButton::LeftButton:
            {
                if (isValid)
                {
                    auto start = pressScenePos;
                    auto end   = evt->scenePos().x();
                    if (end < start) std::swap(start, end);

                    auto rect = plotArea();
                    rect.moveLeft(start);
                    auto newRect = QRect(start, rect.y(), end-start, rect.height());
                    zoomIn(newRect);

                    isValid = false;
                }
            }
            break;
        case Qt::MouseButton::RightButton:
            {
                zoomReset();
            }
            break;
        default:
            break;
    }
}
