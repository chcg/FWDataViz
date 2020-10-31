#include "EximFileTypeDialog.h"

void EximFileTypeDialog::doDialog(HINSTANCE hInst) {
   if (!isCreated()) {
      Window::init(hInst, nppData._nppHandle);
      create(IDD_FILE_TYPE_EXIM_DIALOG);
   }

   goToCenter();

   SendMessage(_hParent, NPPM_DMMSHOW, 0, (LPARAM)_hSelf);
}

void EximFileTypeDialog::initDialog(bool bExtract) {
   localize(bExtract);

   ShowWindow(GetDlgItem(_hSelf, IDC_FTEXIM_SAVE_FILE), bExtract ? SW_SHOW : SW_HIDE);
   ShowWindow(GetDlgItem(_hSelf, IDC_FTEXIM_LOAD_FILE), bExtract ? SW_HIDE : SW_SHOW);
   ShowWindow(GetDlgItem(_hSelf, IDC_FTEXIM_APPEND), bExtract ? SW_HIDE : SW_SHOW);

   bool recentOS = Utils::checkBaseOS(WV_VISTA);
   wstring fontName = recentOS ? L"Consolas" : L"Courier New";
   int fontHeight = recentOS ? 10 : 8;

   Utils::setFont(_hSelf, IDC_FTEXIM_EDIT_CNTRL, fontName, fontHeight);
   SetFocus(GetDlgItem(_hSelf, IDC_FTEXIM_EDIT_CNTRL));
}

void EximFileTypeDialog::setFileTypeData(LPCWSTR ftConfig) {
   SetDlgItemText(_hSelf, IDC_FTEXIM_EDIT_CNTRL, ftConfig);
}

void EximFileTypeDialog::localize(bool bExtract) {
   SetWindowText(_hSelf, bExtract ? FT_EXIM_EXTRACT_DLG_TITLE : FT_EXIM_APPEND_DLG_TITLE);
   SetDlgItemText(_hSelf, IDC_FTEXIM_EDIT_LABEL, FT_EXIM_EDIT_LABEL);
   SetDlgItemText(_hSelf, IDC_FTEXIM_EDIT_CNTRL, NULL);
   SetDlgItemText(_hSelf, IDCLOSE, FT_EXIM_CLOSE_BTN);

   if (bExtract) {
      SetDlgItemText(_hSelf, IDC_FTEXIM_SAVE_FILE, FT_EXIM_SAVE_FILE_BTN);
   }
   else {
      SetDlgItemText(_hSelf, IDC_FTEXIM_LOAD_FILE, FT_EXIM_LOAD_FILE_BTN);
      SetDlgItemText(_hSelf, IDC_FTEXIM_APPEND, FT_EXIM_APPEND_BTN);
   }
}

INT_PTR CALLBACK EximFileTypeDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM) {
   switch (message) {
      case WM_COMMAND:
         switch LOWORD(wParam) {
            case IDCANCEL:
            case IDCLOSE:
               display(FALSE);
               return TRUE;
         }
         return FALSE;

      case WM_NOTIFY:
         return FALSE;

      default:
         return FALSE;
   }
}
