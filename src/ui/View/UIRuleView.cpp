#include "stdafx.h"
#include "UIRuleView.h"
#include "ui_UIRuleView.h"
#include <QDesktopServices>
//******************************************************************************
constexpr auto kUrlDocument = "https://wecooperate.github.io/docs/%E8%A7%84%E5%88%99%E5%BC%95%E6%93%8E";
//******************************************************************************
UIRuleView::UIRuleView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UIRuleView)
{
	ui->setupUi(this);
}
//******************************************************************************
UIRuleView::~UIRuleView()
{
	delete ui;
}
//******************************************************************************
void UIRuleView::on_btnLocate_clicked()
{
	g_PathLocate->LocateFile(g_Path->GetCurrentPath(_T("rules")));
}
//******************************************************************************
void UIRuleView::on_btnDocument_clicked()
{
	QDesktopServices::openUrl(QUrl(kUrlDocument));
}
//******************************************************************************
