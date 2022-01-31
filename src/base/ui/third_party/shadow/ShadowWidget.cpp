//******************************************************************************
/*++
	FileName:		ShadowWidget.cpp
	Description:

--*/
//******************************************************************************
#include "stdafx.h"
#include "ShadowWidget.h"
#include <QPainter>
#include <QtMath>
//******************************************************************************
static int MakeAlpha(int i, double mask, int size)
{
	if (i == size)
		mask *= 1.2;

	double f = 1 - cos((double)i / size * 3.14 / 2);

	return int(fabs((i * mask) * f));
}
//******************************************************************************
static QImage MakeShadowImage(int shadow_size, bool activated = false, int border_size = 0)
{
	int size = shadow_size * 2 + 10;

	QImage image(size, size, QImage::Format_ARGB32);
	image.fill(QColor(Qt::black));
	QSize image_size = image.size();

	double alpha_mask = activated ? 4.0 : 4.0;

	for (int y = shadow_size; y < image_size.height() - shadow_size; y++) {
		for (int x = 0; x < shadow_size; x++) {
			int i = x;
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	for (int y = shadow_size; y < image_size.height() - shadow_size; y++) {
		for (int x = image_size.width() - shadow_size - 1; x < image_size.width(); x++) {
			int i = image_size.width() - x;
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	for (int y = 0; y < shadow_size; y++) {
		int i = y;
		for (int x = shadow_size; x < image_size.width() - shadow_size; x++) {
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	for (int y = image_size.height() - shadow_size - 1; y < image_size.height(); y++) {
		int i = image_size.height() - y;
		for (int x = shadow_size; x < image_size.width() - shadow_size; x++) {
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	int parent_round_size = 3;

	for (int x = 0; x < shadow_size + parent_round_size; x++) {
		for (int y = 0; y < shadow_size + parent_round_size; y++) {
			int xx = (shadow_size + parent_round_size) - x;
			int yy = (shadow_size + parent_round_size) - y;
			int i = int(sqrt(double(xx * xx + yy * yy)));
			i = std::min<int>(shadow_size + parent_round_size, i);
			i -= parent_round_size;
			i = shadow_size - i;
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	for (int x = image_size.width() - shadow_size - parent_round_size; x < image_size.width(); x++) {
		for (int y = 0; y < shadow_size + parent_round_size; y++) {
			int xx = (shadow_size + parent_round_size) - (image_size.width() - x);
			int yy = (shadow_size + parent_round_size) - y;
			int i = int(sqrt(double(xx * xx + yy * yy)));
			i = std::min<int>(shadow_size + parent_round_size, i);
			i -= parent_round_size;
			i = shadow_size - i;
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	for (int x = 0; x < shadow_size + parent_round_size; x++) {
		for (int y = image_size.height() - shadow_size - parent_round_size; y < image_size.height(); y++) {
			int xx = (shadow_size + parent_round_size) - x;
			int yy = (shadow_size + parent_round_size) - (image_size.height() - y);
			int i = int(sqrt(double(xx * xx + yy * yy)));
			i = std::min<int>(shadow_size + parent_round_size, i);
			i -= parent_round_size;
			i = shadow_size - i;
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	for (int x = image_size.width() - shadow_size - parent_round_size; x < image_size.width(); x++) {
		for (int y = image_size.height() - shadow_size - parent_round_size; y < image_size.height(); y++) {
			int xx = (shadow_size + parent_round_size) - (image_size.width() - x);
			int yy = (shadow_size + parent_round_size) - (image_size.height() - y);
			int i = int(sqrt(double(xx * xx + yy * yy)));
			i = std::min<int>(shadow_size + parent_round_size, i);
			i -= parent_round_size;
			i = shadow_size - i;
			int alpha = MakeAlpha(i, alpha_mask, shadow_size);
			image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
		}
	}

	int border_R = 165;
	int border_G = 165;
	int border_B = 165;

	if (activated) {
		border_R = 68;
		border_G = 138;
		border_B = 255;
	}

	for (int i = 0; i < border_size; i++) {
		for (int y = shadow_size - 1; y < image_size.height() - shadow_size + 1; y++) {
			int x = shadow_size - i - 1;
			image.setPixelColor(x, y, QColor(border_R, border_G, border_B, 255));
		}
	}

	for (int i = 0; i < border_size; i++) {
		for (int y = shadow_size - 1; y < image_size.height() - shadow_size + 1; y++) {
			int x = image_size.width() - shadow_size - 1 + i + 1;
			image.setPixelColor(x, y, QColor(border_R, border_G, border_B, 255));
		}
	}

	for (int i = 0; i < border_size; i++) {
		for (int x = shadow_size; x < image_size.width() - shadow_size; x++) {
			int y = shadow_size - i - 1;
			image.setPixelColor(x, y, QColor(border_R, border_G, border_B, 255));
		}
	}

	for (int i = 0; i < border_size; i++) {
		for (int x = shadow_size; x < image_size.width() - shadow_size; x++) {
			int y = image_size.height() - shadow_size - 1 + i + 1;
			image.setPixelColor(x, y, QColor(border_R, border_G, border_B, 255));
		}
	}

	return image;
}
//******************************************************************************
static bool MakeRect(const QRect& rect, QPoint top_left, QRect* rect_array, int rect_count)
{
	if (rect_count != 9)
		return false;

	QRect* rects = rect_array;

	int width = rect.width();
	int height = rect.height();

	if (top_left.x() <= 0)
		return false;
	if (top_left.y() <= 0)
		return false;
	if (top_left.x() >= width / 2)
		return false;
	if (top_left.y() >= height / 2)
		return false;

	int x1 = rect.left() + 0;
	int x2 = rect.left() + top_left.x();
	int x3 = rect.left() + width - top_left.x();
	int x4 = rect.left() + width;

	int y1 = rect.top() + 0;
	int y2 = rect.top() + top_left.y();
	int y3 = rect.top() + height - top_left.y();
	int y4 = rect.top() + height;

	rects[0] = QRect(QPoint(x1, y1), QPoint(x2, y2));
	rects[1] = QRect(QPoint(x2 + 1, y1), QPoint(x3, y2));
	rects[2] = QRect(QPoint(x3 + 1, y1), QPoint(x4, y2));

	rects[3] = QRect(QPoint(x1, y2 + 1), QPoint(x2, y3));
	rects[4] = QRect(QPoint(x2 + 1, y2 + 1), QPoint(x3, y3));
	rects[5] = QRect(QPoint(x3 + 1, y2 + 1), QPoint(x4, y3));

	rects[6] = QRect(QPoint(x1, y3 + 1), QPoint(x2, y4));
	rects[7] = QRect(QPoint(x2 + 1, y3 + 1), QPoint(x3, y4));
	rects[8] = QRect(QPoint(x3 + 1, y3 + 1), QPoint(x4, y4));

	return true;
}
//******************************************************************************
bool QShadowImage::SetImage(const QImage& image, QPoint point)
{
	m_Image = image;

	return MakeRect(QRect(0, 0, m_Image.width(), m_Image.height()), point, m_ImageGridRect, 9);
}
//******************************************************************************
void QShadowImage::DrawBorder(QPainter* painter, QRect rect) const
{
	QRect rects[9];

	MakeRect(rect, m_ImageGridRect[0].bottomRight(), rects, 9);

	for (int i = 0; i < 9; i++) {
		if (i == 4)
			continue;

		const QRect& rect_src = m_ImageGridRect[i];
		const QRect& rect_dest = rects[i];

		painter->drawImage(rect_dest, m_Image, rect_src);
	}
}
//******************************************************************************
QShadowWidget::QShadowWidget(int shadow_size, bool can_resize, QWidget* parent)
	: m_ShadowSize(shadow_size)
	, QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlag(Qt::FramelessWindowHint);
	setWindowFlag(Qt::WindowSystemMenuHint);
	setMouseTracking(true);

	QImage image = MakeShadowImage(shadow_size, false);
	m_ShadowImage.SetImage(image, QPoint(shadow_size + 1, shadow_size + 1));
}
//******************************************************************************
void QShadowWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	m_ShadowImage.DrawBorder(&painter, rect());
}
//******************************************************************************
