//******************************************************************************
/*++
	FileName:		FramelessHelper.cpp
	Description:

--*/
//******************************************************************************
#include "stdafx.h"
#include "FramelessHelper.h"
#include <QWidget>
//******************************************************************************
void QMouseHitTestData::HitTest(const QPoint& point, const QRect& rect, int edge_size)
{
	m_IsOnLeftEdge = point.x() <= edge_size;
	m_IsOnRightEdge = point.x() + edge_size >= rect.width();
	m_IsOnTopEdge = point.y() <= edge_size;
	m_IsOnBottomEdge = point.y() + edge_size >= rect.height();
}
//******************************************************************************
bool QMouseHitTestData::IsOnEdge()
{
	return m_IsOnLeftEdge || m_IsOnRightEdge || m_IsOnTopEdge || m_IsOnBottomEdge;
}
//******************************************************************************
bool QMouseHitTestData::IsOnTopLeftEdge()
{
	return m_IsOnTopEdge && m_IsOnLeftEdge;
}
//******************************************************************************
bool QMouseHitTestData::IsOnTopRightEdge()
{
	return m_IsOnTopEdge && m_IsOnRightEdge;
}
//******************************************************************************
bool QMouseHitTestData::IsOnBottomLeftEdge()
{
	return m_IsOnBottomEdge && m_IsOnLeftEdge;
}
//******************************************************************************
bool QMouseHitTestData::IsOnBottomRightEdge()
{
	return m_IsOnBottomEdge && m_IsOnRightEdge;
}
//******************************************************************************
QFramelessHelper::QFramelessHelper(QObject* parent)
	: QObject(parent)
{
}
//******************************************************************************
void QFramelessHelper::Initialize(QWidget* widget, QWidget* shadow_widget, int shadow_size)
{
	m_Widget = widget;
	m_Widget->setMouseTracking(true);
	m_Widget->setAttribute(Qt::WA_Hover, true);
	m_Widget->installEventFilter(this);

	m_ShadowWidget = shadow_widget;
	m_ShadowSize = shadow_size;
}
//******************************************************************************
void QFramelessHelper::SetWidgetMoveable(bool moveable)
{
	m_Moveable = moveable;
}
//******************************************************************************
void QFramelessHelper::SetWidgetResizable(bool resizable)
{
	m_Resizable = resizable;
}
//******************************************************************************
bool QFramelessHelper::IsWidgetResizable() const
{
	return m_Moveable;
}
//******************************************************************************
bool QFramelessHelper::IsWidgetMoveable() const
{
	return m_Resizable;
}
//******************************************************************************
bool QFramelessHelper::HandleMousePressEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton) {
		return false;
	}

	m_MousePressed = true;
	m_MousePoint = event->globalPos() - m_Widget->pos();
	m_MouseHitTestData.HitTest(m_MousePoint, m_Widget->frameGeometry(), m_ShadowSize);

	return true;
}
//******************************************************************************
bool QFramelessHelper::HandleMouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton) {
		return false;
	}

	m_MousePressed = false;

	return true;
}
//******************************************************************************
bool QFramelessHelper::HandleMouseMoveEvent(QMouseEvent* event)
{
	if (m_Widget->isMaximized())
		return true;

	if (!m_MousePressed)
		return true;

	if (m_MouseHitTestData.IsOnEdge())
		ResizeWidget(event->globalPos());
	else
		m_Widget->move(event->globalPos() - m_MousePoint);

	return true;
}
//******************************************************************************
bool QFramelessHelper::HandleLeaveEvent(QMouseEvent* event)
{
	if (!m_MousePressed) {
		m_Widget->unsetCursor();
	}

	return true;
}
//******************************************************************************
bool QFramelessHelper::HandleHoverMoveEvent(QMouseEvent* event)
{
	if (m_Resizable && !m_MousePressed) {
		UpdateCursor(event->pos());
	}

	return true;
}
//******************************************************************************
bool QFramelessHelper::HandleMouseButtonDblClick(QMouseEvent* event)
{
	if (m_Widget->isMaximized()) {
		m_ShadowWidget->setContentsMargins(m_ShadowSize, m_ShadowSize, m_ShadowSize, m_ShadowSize);
		m_Widget->showNormal();
	} else {
		m_ShadowWidget->setContentsMargins(0, 0, 0, 0);
		m_Widget->showMaximized();
	}

	return true;
}
//******************************************************************************
bool QFramelessHelper::eventFilter(QObject* object, QEvent* event)
{
	QMouseEvent* mouse_event = (QMouseEvent*)(event);

	switch (event->type()) {
	case QEvent::MouseButtonPress:
		return HandleMousePressEvent(mouse_event);

	case QEvent::MouseMove:
		return HandleMouseMoveEvent(mouse_event);

	case QEvent::HoverMove:
		return HandleHoverMoveEvent(mouse_event);

	case QEvent::MouseButtonRelease:
		return HandleMouseReleaseEvent(mouse_event);

	case QEvent::Leave:
		return HandleLeaveEvent(mouse_event);

	case QEvent::MouseButtonDblClick:
		return HandleMouseButtonDblClick(mouse_event);

	default:
		break;
	}

	return QObject::eventFilter(object, event);
}
//******************************************************************************
void QFramelessHelper::ResizeWidget(const QPoint& point)
{
	QRect rect = m_Widget->frameGeometry();

	int left = rect.left();
	int top = rect.top();
	int right = rect.right();
	int bottom = rect.bottom();
	rect.getCoords(&left, &top, &right, &bottom);

	int min_width = m_Widget->minimumWidth();
	int min_height = m_Widget->minimumHeight();

	int edge_size = m_ShadowSize;

	if (m_MouseHitTestData.IsOnTopLeftEdge()) {
		left = point.x() - edge_size;
		top = point.y() - edge_size;
	} else if (m_MouseHitTestData.IsOnBottomLeftEdge()) {
		left = point.x() - edge_size;
		bottom = point.y() + edge_size;
	} else if (m_MouseHitTestData.IsOnTopRightEdge()) {
		right = point.x() + edge_size;
		top = point.y() - edge_size;
	} else if (m_MouseHitTestData.IsOnBottomRightEdge()) {
		right = point.x() + edge_size;
		bottom = point.y() + edge_size;
	} else if (m_MouseHitTestData.m_IsOnLeftEdge) {
		left = point.x() - edge_size;
	} else if (m_MouseHitTestData.m_IsOnRightEdge) {
		right = point.x() + edge_size;
	} else if (m_MouseHitTestData.m_IsOnTopEdge) {
		top = point.y() - edge_size;
	} else if (m_MouseHitTestData.m_IsOnBottomEdge) {
		bottom = point.y() + edge_size;
	}

	QRect new_rect(QPoint(left, top), QPoint(right, bottom));

	if (new_rect.isValid()) {
		if (min_width > new_rect.width()) {
			if (left != rect.left())
				new_rect.setLeft(rect.left());
			else
				new_rect.setRight(rect.right());
		}
		if (min_height > new_rect.height()) {
			if (top != rect.top())
				new_rect.setTop(rect.top());
			else
				new_rect.setBottom(rect.bottom());
		}

		m_Widget->setGeometry(new_rect);
	}
}
//******************************************************************************
void QFramelessHelper::UpdateCursor(const QPoint& point)
{
	if (m_Widget->isFullScreen() || m_Widget->isMaximized()) {
		if (m_CursorModified) {
			m_Widget->unsetCursor();
			m_CursorModified = false;
		}
		return;
	}

	QMouseHitTestData hitest_data;
	hitest_data.HitTest(point, m_Widget->frameGeometry(), m_ShadowSize);

	if (hitest_data.IsOnTopLeftEdge() || hitest_data.IsOnBottomRightEdge()) {
		m_Widget->setCursor(Qt::SizeFDiagCursor);
		m_CursorModified = true;
	} else if (hitest_data.IsOnTopRightEdge() || hitest_data.IsOnBottomLeftEdge()) {
		m_Widget->setCursor(Qt::SizeBDiagCursor);
		m_CursorModified = true;
	} else if (hitest_data.m_IsOnLeftEdge || hitest_data.m_IsOnRightEdge) {
		m_Widget->setCursor(Qt::SizeHorCursor);
		m_CursorModified = true;
	} else if (hitest_data.m_IsOnTopEdge || hitest_data.m_IsOnBottomEdge) {
		m_Widget->setCursor(Qt::SizeVerCursor);
		m_CursorModified = true;
	} else {
		if (m_CursorModified) {
			m_Widget->unsetCursor();
			m_CursorModified = false;
		}
	}
}
//******************************************************************************
