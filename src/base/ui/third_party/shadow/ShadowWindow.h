//******************************************************************************
/*++
	FileName:		ShadowWindow.h
	Description:

--*/
//******************************************************************************
#ifndef __ShadowWindow_h_10266c41_674d_4d58_b980_f4ab01e8fafb__
#define __ShadowWindow_h_10266c41_674d_4d58_b980_f4ab01e8fafb__
//******************************************************************************
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include "ShadowWidget.h"
#include "FramelessHelper.h"
/*******************************************************************************
 * ----------------------------------
 * |shadow_window                   |
 * |  ----------------------------  |
 * |  |shadow_widget             |  |
 * |  |  ----------------------  |  |
 * |  |  |shadow_client_widget   |  |
 * |  |  | ------------------ |  |  |
 * |  |  | |client_widget   | |  |  |
 * |  |  | |                | |  |  |
 * |  |  | ------------------ |  |  |
 * |  |  ----------------------  |  |
 * |  |                          |  |
 * |  ----------------------------  |
 * |                                |
 * ----------------------------------
 ******************************************************************************/
template<typename T>
class QShadowWindow : public T
{
public:
	explicit QShadowWindow(bool can_resize = true, int shadow_size = 20, QWidget* parent = nullptr)
		: T(parent)
		, m_ShadowSize(shadow_size)
		, m_ShadowWidget(nullptr)
		, m_ClientWidget(nullptr)
	{
		T* pT = this;
		pT->setAttribute(Qt::WA_TranslucentBackground, true);
		pT->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
		pT->setContentsMargins(0, 0, 0, 0);

		QVBoxLayout* layout = new QVBoxLayout(pT);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);

		m_ShadowWidget = new QShadowWidget(m_ShadowSize, can_resize, this);
		m_ShadowWidget->setContentsMargins(m_ShadowSize, m_ShadowSize, m_ShadowSize, m_ShadowSize);
		m_ShadowWidget->setAutoFillBackground(true);
		layout->addWidget(m_ShadowWidget);

		QVBoxLayout* main_layout = new QVBoxLayout(m_ShadowWidget);
		main_layout->setContentsMargins(0, 0, 0, 0);
		main_layout->setSpacing(0);

		QWidget* shadow_client = new QWidget(m_ShadowWidget);
		main_layout->addWidget(shadow_client);
		shadow_client->setAutoFillBackground(true);
		m_ShadowClientLayout = new QVBoxLayout(shadow_client);
		m_ShadowClientLayout->setContentsMargins(0, 0, 0, 0);
		m_ShadowClientLayout->setSpacing(0);

		m_ClientWidget = new QWidget(shadow_client);
		m_ShadowClientLayout->addWidget(m_ClientWidget);

		m_ClientLayout = new QVBoxLayout;
		m_ClientWidget->setLayout(m_ClientLayout);

		m_Helper = new QFramelessHelper(this);
		m_Helper->Initialize(this, m_ShadowWidget, m_ShadowSize);
		m_Helper->SetWidgetResizable(true);
		m_Helper->SetWidgetMoveable(true);
	}

public:
	QWidget* rootWidget() const
	{
		return m_ShadowWidget;
	}

	QWidget* clientWidget() const
	{
		return m_ClientWidget;
	}

	QLayout* clientLayout() const
	{
		return m_ClientLayout;
	}

public:
	void setRubberBandOnMove(bool enable)
	{
		m_Helper->setRubberBandOnMove(enable);
	}

	void setRubberBandOnResize(bool enable)
	{
		m_Helper->setRubberBandOnResize(enable);
	}

	void setResizable(bool resizable)
	{
		m_Helper->SetWidgetResizable(resizable);
	}

	void SetMoveable(bool moveable)
	{
		m_Helper->SetWidgetMoveable(moveable);
	}

public:
	void SetClientWidget(QWidget* client)
	{
		if (client == nullptr)
			return;

		m_ShadowClientLayout->removeWidget(m_ClientWidget);
		m_ClientWidget->deleteLater();
		m_ClientLayout->deleteLater();
		m_ClientLayout = nullptr;
		m_ClientWidget = client;
		m_ShadowClientLayout->addWidget(m_ClientWidget);
	}

	void SwitchMaximizeState()
	{
		if (isMaximized()) {
			m_ShadowWidget->setContentsMargins(m_ShadowSize, m_ShadowSize, m_ShadowSize, m_ShadowSize);
			showNormal();
		} else {
			m_ShadowWidget->setContentsMargins(0, 0, 0, 0);
			showMaximized();
		}
	}

	void FixMaximizedMargins()
	{
		m_ShadowWidget->setContentsMargins(0, 0, 0, 0);
	}

protected:
	int m_ShadowSize;
	QWidget* m_ClientWidget;
	QVBoxLayout* m_ClientLayout;
	QVBoxLayout* m_ShadowClientLayout;
	QShadowWidget* m_ShadowWidget;
	QFramelessHelper* m_Helper;
};
//******************************************************************************
typedef QShadowWindow<QWidget> QShadowWindowWidget;
typedef QShadowWindow<QDialog> QShadowDialogWidget;
//******************************************************************************
#endif
