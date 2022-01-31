//******************************************************************************
/*++
	FileName:		ShadowWidget.h
	Description:

--*/
//******************************************************************************
#ifndef __ShadowWidget_h_9b4a1378_4415_4f27_b560_d3742cb47d7c__
#define __ShadowWidget_h_9b4a1378_4415_4f27_b560_d3742cb47d7c__
//******************************************************************************
#include <QWidget>
//******************************************************************************
class QShadowImage
{
public:
	bool SetImage(const QImage& image, QPoint point);
	void DrawBorder(QPainter* painter, QRect rect) const;

protected:
	QImage m_Image;
	QRect m_ImageGridRect[9];
};
//******************************************************************************
class QShadowWidget : public QWidget
{
	Q_OBJECT
public:
	QShadowWidget(int shadow_size, bool can_resize, QWidget* parent = nullptr);

	virtual void paintEvent(QPaintEvent* event);

private:
	QShadowImage m_ShadowImage;
	int m_ShadowSize;
};
//******************************************************************************
#endif
