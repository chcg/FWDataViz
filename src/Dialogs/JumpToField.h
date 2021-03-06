#pragma once

#include "../Utils.h"
#include "../ConfigIO.h"
#include "../NPP/StaticDialog.h"

extern NppData nppData;
extern ConfigIO _configIO;

class JumpToField : public StaticDialog {
public:
   JumpToField() : StaticDialog() {};
   void doDialog(HINSTANCE hInst);
   void initDialog(int recordIndex, int fieldIndex, const vector<wstring>& fieldLabels);
   void setFileTypeData(const wstring& ftConfig);

protected:
   int caretRecordRegIndex;
   HWND hFieldList;

   INT_PTR CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
   void localize();
   void onJumpBtnClick();
};
