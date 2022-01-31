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
#include "UIDefenderRecordView.h"
#include "ui_UIDefenderRecordView.h"
#include <QSortFilterProxyModel>
//******************************************************************************
UIDefenderRecordView::UIDefenderRecordView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UIDefenderRecordView)
{
	ui->setupUi(this);

	g_UICommon->InitTreeView(ui->treeView);
}
//******************************************************************************
UIDefenderRecordView::~UIDefenderRecordView()
{
	delete ui;
}
//******************************************************************************
void UIDefenderRecordView::UpdateQuery()
{
	if (!m_Model)
		return;

	bool is_all = ui->radioButtonAll->isChecked();
	bool is_detail = ui->checkBoxDetail->isChecked();
	QDate date = ui->dateEdit->date();

	m_Model->SetQuery(is_all ? nullptr : &date, is_detail);

	auto view = ui->treeView;

	view->setColumnHidden(emRecordEventIndexProcessPath, true);
	view->setColumnHidden(emRecordEventIndexProcessCommandline, true);
	view->setColumnHidden(emRecordEventIndexEventType, true);
	view->setColumnHidden(emRecordEventIndexCount, is_detail);

	if (m_Model->rowCount() > 0) {
		for (int i = 0; i < m_Model->columnCount(); i++) {
			view->resizeColumnToContents(i);
		}
		view->setColumnWidth(emRecordEventIndexCount, 70);
	}
}
//******************************************************************************
void UIDefenderRecordView::showEvent(QShowEvent* event)
{
	if (m_Model)
		return;

	g_MainLooper->PostRunnable([this]() {
		auto model = new QSortFilterProxyModel(this);
		model->setSourceModel(m_Model = new UIRecordEventModel());
		ui->treeView->setModel(model);
		ui->dateEdit->setDate(QDate::currentDate());
	});
}
//******************************************************************************
void UIDefenderRecordView::on_dateEdit_dateChanged(const QDate& date)
{
	UpdateQuery();
}
//******************************************************************************
void UIDefenderRecordView::on_radioButtonAll_toggled(bool checked)
{
	UpdateQuery();
}
//******************************************************************************
void UIDefenderRecordView::on_checkBoxDetail_toggled(bool checked)
{
	UpdateQuery();
}
//******************************************************************************
