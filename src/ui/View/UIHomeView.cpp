//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "UIHomeView.h"
#include "ui_UIHomeView.h"
#include <QMessageBox>
//******************************************************************************
constexpr auto SERVICE_INSTANCE_NAME = _T("Global\\iDefender-0C4BF928BE85485DB65873B475099863");
//******************************************************************************
UIHomeView::UIHomeView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UIHomeView)
{
	ui->setupUi(this);

	UpdateState(false);
}
//******************************************************************************
UIHomeView::~UIHomeView()
{
	delete ui;
}
//******************************************************************************
void UIHomeView::UpdateState(bool showError)
{
	ui->btnStart->setEnabled(true);

	cxHandle handle = OpenMutex(MUTANT_QUERY_STATE, FALSE, SERVICE_INSTANCE_NAME);

	if (!m_Started && !handle && showError) {
		// TODO(Get Valid ErrorCode)
		QMessageBox::critical(this,
			g_UIManager->GetView(SCHEME_MAIN_VIEW)->windowTitle(),
			tr("Start Failed, Please Check Driver Signature"),
			QMessageBox::Ok);
	}

	m_Started = handle != NULL;

	if (m_Started) {
		ui->btnStart->setText(tr("Stop"));
		ui->btnStart->setProperty("type", "danger");
		ui->btnStart->style()->unpolish(ui->btnStart);
		ui->btnStart->style()->polish(ui->btnStart);
		ui->labelImage->setPixmap(QPixmap(QString::fromUtf8(":/res/enable.png")));
		ui->labelInfo->setText(tr("iDefender is running"));
	} else {
		ui->btnStart->setText(tr("Start"));
		ui->btnStart->setProperty("type", "primary");
		ui->btnStart->style()->unpolish(ui->btnStart);
		ui->btnStart->style()->polish(ui->btnStart);
		ui->labelImage->setPixmap(QPixmap(QString::fromUtf8(":/res/disable.png")));
		ui->labelInfo->setText(tr("iDefender is stoped"));
	}
}
//******************************************************************************
void UIHomeView::ExecuteServiceCommand(LPCTSTR Command)
{
	CString path = g_Path->GetCurrentPath(_T("iDefenderService.exe"));

	SHELLEXECUTEINFO info = { sizeof(info) };
	info.lpVerb = _T("runas");
	info.lpFile = path;
	info.lpParameters = Command;
	info.nShow = SW_HIDE;
	info.fMask = SEE_MASK_NOCLOSEPROCESS;

	if (!ShellExecuteEx(&info))
		return;

	if (info.hProcess) {
		WaitForSingleObject(info.hProcess, INFINITE);
		CloseHandle(info.hProcess);
	}
}
//******************************************************************************
void UIHomeView::on_btnStart_clicked()
{
	ui->btnStart->setEnabled(false);

	g_WorkerLooper->PostRunnable([this]() {
		ExecuteServiceCommand(m_Started ? _T("/uninstall") : _T("/start"));

		g_MainLooper->PostRunnable(
			[this]() {
				UpdateState(true);
			},
			500);
	});
}
//******************************************************************************
