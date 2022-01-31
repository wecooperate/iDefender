//******************************************************************************
/*++
	FileName:		ShellWindow.h
	Description:

--*/
//******************************************************************************
#ifndef __ShellWindow_h_e6f2f497_d1bf_4f7f_bd8a_2f290bf6c1d0__
#define __ShellWindow_h_e6f2f497_d1bf_4f7f_bd8a_2f290bf6c1d0__
//******************************************************************************
#include "../third_party/shadow/ShadowWindow.h"
//******************************************************************************
namespace Ui {
class UIShellWindow;
}
//******************************************************************************
struct UINavigatorButton
{
	QString m_Name;
	QAbstractButton* m_Button;
	QWidget* m_Widget;
	std::function<QWidget*()> m_WidgetCreator;
};
//******************************************************************************
class UIShellWindow
	: public QShadowWindowWidget
	, public UIWidgetHelper
{
	Q_OBJECT

public:
	UIShellWindow(QWidget* parent = 0);
	~UIShellWindow();

protected:
	void Initialize();

protected:
	void SetToolBar(QWidget* toolbar);
	void SetTitle(const QString& name);
	void SetTitleIcon(QChar index);
	void ShowMenuButton(bool show);
	void InsertNavigatorButton(const QString& name, QIcon icon, std::function<QWidget*()> creator);
	void InsertNavigatorUrlButton(const QString& name, QIcon icon, const QString& url);

	template<typename T>
	void InsertNavigatorButton(const QString& name, QIcon icon)
	{
		InsertNavigatorButton(name, icon, []() -> QWidget* {
			return new T();
		});
	}

protected:
	bool Activate(UINavigatorButton* button);
	void Activate(const QString& name);

protected:
	void changeEvent(QEvent* event) override;

protected:
	virtual void OnMenuClicked();
	virtual void OnNavigatorSwitch(QAbstractButton* button);

private slots:
	void on_btnMenu_Min_clicked();
	void on_btnMenu_Max_clicked();
	void on_btnMenu_Close_clicked();
	void on_btnMenu_Menu_clicked();

protected:
	Ui::UIShellWindow* ui;
	std::map<QString, UINavigatorButton> m_Buttons;
	UINavigatorButton* m_ActivatedButton = nullptr;
	QWidget* m_ToolBar = nullptr;
};
//******************************************************************************
#endif
