#include "stdafx.h"
#include "UIShellWindow.h"
#include "ui_UIShellWindow.h"
#include <QDesktopWidget>
#include <QDesktopServices>
//******************************************************************************
UIShellWindow::UIShellWindow(QWidget* parent)
	: QShadowWindowWidget(true, 20, parent)
	, UIWidgetHelper(this)
	, ui(new Ui::UIShellWindow)
{
	QWidget* client_widget = new QWidget(this);
	ui->setupUi(client_widget);
	SetClientWidget(client_widget);

	Initialize();

	Q_CONNECT(ui->btnMenu_Close, clicked, on_btnMenu_Close_clicked);
	Q_CONNECT(ui->btnMenu_Max, clicked, on_btnMenu_Max_clicked);
	Q_CONNECT(ui->btnMenu_Min, clicked, on_btnMenu_Min_clicked);
	Q_CONNECT(ui->btnMenu_Menu, clicked, on_btnMenu_Menu_clicked);
}
//******************************************************************************
UIShellWindow::~UIShellWindow()
{
	delete ui;
}
//******************************************************************************
void UIShellWindow::Initialize()
{
	ui->widgetLeft->setProperty("flag", "navigator");

	g_UIFontIcon->SetFontIcon(ui->btnMenu_Min, emFontIconMin);
	g_UIFontIcon->SetFontIcon(ui->btnMenu_Max, emFontIconNormal);
	g_UIFontIcon->SetFontIcon(ui->btnMenu_Close, emFontIconClose);
	g_UIFontIcon->SetFontIcon(ui->btnMenu_Menu, emFontIconMenu);

	CenterWindow(1200, 700);
}
//******************************************************************************
void UIShellWindow::SetToolBar(QWidget* toolbar)
{
	if (m_ToolBar) {
		ui->layoutToolBar->removeWidget(m_ToolBar);
		m_ToolBar->hide();
	}

	m_ToolBar = toolbar;

	if (m_ToolBar) {
		ui->layoutToolBar->addWidget(m_ToolBar);
		m_ToolBar->show();
	}
}
//******************************************************************************
void UIShellWindow::SetTitle(const QString& name)
{
	ui->labTitle->setText(name);
	setWindowTitle(name);
}
//******************************************************************************
void UIShellWindow::SetTitleIcon(QChar index)
{
	g_UIFontIcon->SetFontIcon(ui->labIcon, index, 20);
	setWindowIcon(g_UIFontIcon->CreateIcon("#ffffff", index, 35, 64, 64));
}
//******************************************************************************
void UIShellWindow::ShowMenuButton(bool show)
{
	show ? ui->btnMenu_Menu->show() : ui->btnMenu_Menu->hide();
}
//******************************************************************************
void UIShellWindow::InsertNavigatorButton(const QString& name, QIcon icon, std::function<QWidget*()> creator)
{
	if (m_Buttons.find(name) != m_Buttons.end()) {
		DCHECK(!"button name conflict");
		return;
	}

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	auto button = new QToolButton(ui->widgetLeft);
	button->setText("  " + name);
	sizePolicy.setHeightForWidth(button->sizePolicy().hasHeightForWidth());
	button->setSizePolicy(sizePolicy);
	button->setMaximumSize(QSize(16777215, 50));
	button->setIconSize(QSize(20, 20));
	button->setCheckable(true);
	button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	button->setIcon(icon);

	ui->layoutLeft->insertWidget(m_Buttons.size() + 1, button);

	UINavigatorButton navigator_button;
	navigator_button.m_Name = name;
	navigator_button.m_Button = button;
	navigator_button.m_Widget = nullptr;
	navigator_button.m_WidgetCreator = creator;
	m_Buttons.insert(std::make_pair(name, std::move(navigator_button)));

	connect(button, &QToolButton::clicked, [button, this](bool checked) {
		if (!checked) {
			button->setChecked(true);
			return;
		}
		OnNavigatorSwitch(button);
	});
}
//******************************************************************************
void UIShellWindow::InsertNavigatorUrlButton(const QString& name, QIcon icon, const QString& url)
{
	InsertNavigatorButton(name, icon, [url]() {
		QDesktopServices::openUrl(QUrl(url));
		return nullptr;
	});
}
//******************************************************************************
bool UIShellWindow::Activate(UINavigatorButton* button)
{
	if (!button)
		return false;

	if (!button->m_Widget && button->m_WidgetCreator) {
		button->m_Widget = button->m_WidgetCreator();
	}

	if (!button->m_Widget) {
		button->m_Button->setChecked(false);
		if (m_ActivatedButton) {
			m_ActivatedButton->m_Button->setChecked(true);
		}
		return false;
	}

	if (m_ActivatedButton && m_ActivatedButton->m_Widget) {
		ui->layoutClient->removeWidget(m_ActivatedButton->m_Widget);
		m_ActivatedButton->m_Widget->hide();
	}

	ui->layoutClient->addWidget(button->m_Widget);
	button->m_Widget->show();

	m_ActivatedButton = button;

	return true;
}
//******************************************************************************
void UIShellWindow::Activate(const QString& name)
{
	if (m_ActivatedButton && m_ActivatedButton->m_Name == name)
		return;

	if (auto it = m_Buttons.find(name); it != m_Buttons.end()) {
		OnNavigatorSwitch(it->second.m_Button);
	}
}
//******************************************************************************
void UIShellWindow::changeEvent(QEvent* event)
{
	if (windowState() == Qt::WindowMaximized) {
		g_UIFontIcon->SetFontIcon(ui->btnMenu_Max, emFontIconMax);
		FixMaximizedMargins();
	} else if (windowState() == Qt::WindowNoState) {
		g_UIFontIcon->SetFontIcon(ui->btnMenu_Max, emFontIconNormal);
	}

	__super::changeEvent(event);
}
//******************************************************************************
void UIShellWindow::OnMenuClicked()
{
}
//******************************************************************************
void UIShellWindow::OnNavigatorSwitch(QAbstractButton* button)
{
	UINavigatorButton* navigator_button = nullptr;

	for (auto& it : m_Buttons) {
		it.second.m_Button->setChecked(false);
		if (it.second.m_Button == button) {
			navigator_button = &it.second;
		}
	}

	button->setChecked(true);

	Activate(navigator_button);
}
//******************************************************************************
void UIShellWindow::on_btnMenu_Min_clicked()
{
	showMinimized();
}
//******************************************************************************
void UIShellWindow::on_btnMenu_Max_clicked()
{
	SwitchMaximizeState();
}
//******************************************************************************
void UIShellWindow::on_btnMenu_Close_clicked()
{
	close();
}
//******************************************************************************
void UIShellWindow::on_btnMenu_Menu_clicked()
{
	OnMenuClicked();
}
//******************************************************************************
