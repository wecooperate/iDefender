//******************************************************************************
/*++
	FileName:		FramelessHelper.h
	Description:

--*/
//******************************************************************************
#ifndef __FramelessHelper_h_39268e91_9662_4a95_817b_12163c57b8ec__
#define __FramelessHelper_h_39268e91_9662_4a95_817b_12163c57b8ec__
//******************************************************************************
#include <QObject>
#include <QHash>
#include <QMouseEvent>
//******************************************************************************
struct QMouseHitTestData
{
	bool m_IsOnLeftEdge;
	bool m_IsOnRightEdge;
	bool m_IsOnTopEdge;
	bool m_IsOnBottomEdge;

	void HitTest(const QPoint& point, const QRect& rect, int edge_size);
	bool IsOnEdge();
	bool IsOnTopLeftEdge();
	bool IsOnTopRightEdge();
	bool IsOnBottomLeftEdge();
	bool IsOnBottomRightEdge();
};
//******************************************************************************
class QFramelessHelper : public QObject
{
	Q_OBJECT

public:
	explicit QFramelessHelper(QObject* parent = nullptr);

public:
	void Initialize(QWidget* widget, QWidget* shadow_widget, int shadow_size);

public:
	void SetWidgetMoveable(bool moveable);
	void SetWidgetResizable(bool resizable);

public:
	bool IsWidgetMoveable() const;
	bool IsWidgetResizable() const;

protected:
	bool HandleMousePressEvent(QMouseEvent* event);
	bool HandleMouseReleaseEvent(QMouseEvent* event);
	bool HandleMouseMoveEvent(QMouseEvent* event);
	bool HandleLeaveEvent(QMouseEvent* event);
	bool HandleHoverMoveEvent(QMouseEvent* event);
	bool HandleMouseButtonDblClick(QMouseEvent* event);

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event);

protected:
	void ResizeWidget(const QPoint& point);
	void UpdateCursor(const QPoint& point);

protected:
	QWidget* m_Widget = nullptr;
	QWidget* m_ShadowWidget = nullptr;
	int m_ShadowSize = 0;
	bool m_Moveable = true;
	bool m_Resizable = true;

protected:
	bool m_CursorModified = false;
	bool m_MousePressed = false;
	QPoint m_MousePoint;
	QMouseHitTestData m_MouseHitTestData;
};
//******************************************************************************
#endif
