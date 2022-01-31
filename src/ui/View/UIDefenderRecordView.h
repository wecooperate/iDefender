//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iDefender.
 
  iDefender is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UIDefenderRecordView_h_eee2f26a_2bb1_40ba_a363_aa6cb4aeb995__
#define __UIDefenderRecordView_h_eee2f26a_2bb1_40ba_a363_aa6cb4aeb995__
//******************************************************************************
#include "Model/UIRecordEventModel.h"
//******************************************************************************
namespace Ui {
class UIDefenderRecordView;
}
//******************************************************************************
class UIDefenderRecordView : public QWidget
{
	Q_OBJECT

public:
	explicit UIDefenderRecordView(QWidget* parent = nullptr);
	~UIDefenderRecordView();

protected:
	void UpdateQuery();

protected:
	void showEvent(QShowEvent* event) override;

private slots:
	void on_dateEdit_dateChanged(const QDate& date);
	void on_radioButtonAll_toggled(bool checked);
	void on_checkBoxDetail_toggled(bool checked);

private:
	Ui::UIDefenderRecordView* ui;

protected:
	UIRecordEventModel* m_Model = nullptr;
};
//******************************************************************************
#endif
