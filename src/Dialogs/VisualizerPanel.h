//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma once

#include "../Utils.h"
#include "../ConfigIO.h"
#include "../NPP/DockingDlgInterface.h"
#include "../NPP/menuCmdID.h"
#include <regex>

#define FW_DEBUG_LOAD_STYLES FALSE
#define FW_DEBUG_SET_STYLES FALSE
#define FW_DEBUG_LOAD_REGEX FALSE
#define FW_DEBUG_APPLY_LEXER FALSE

#define FW_DOC_FILE_TYPE "FWVisualizerType"
#define FW_DOC_FILE_THEME "FWVisualizerTheme"
#define FW_STYLE_EOL 100
#define FW_STYLE_RANGE_START 101

extern NppData nppData;
extern ConfigIO _configIO;

using std::regex;
using std::vector;

class VisualizerPanel : public DockingDlgInterface {
public :
   VisualizerPanel() :DockingDlgInterface(IDD_VISUALIZER_DOCKPANEL) {};

   void initPanel();
   void localize();
   virtual void display(bool toShow=true);
   void setParent(HWND parent2set);

   void loadFileTypes();
   void setDocFileType(HWND hScintilla, wstring fileType);
   void onBufferActivate();
   void renderCurrentPage();
   void clearVisualize(bool sync=TRUE);

protected :
   virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
   bool getDocFileType(HWND hScintilla, wstring &fileType);
   bool getDocFileType(PSCIFUNC_T sci_func, void* sci_ptr, wstring &fileType);
   void syncListFileType();
   void visualizeFile();

   int loadStyles();
   int applyStyles();
   int loadLexer();
   void applyLexer(const size_t startLine, const size_t endLine);
   void clearLexer();

   static void setFocusOnEditor();
   void displayCaretFieldInfo(const size_t startLine, const size_t endLine);
   void clearCaretFieldInfo();
   void showWordwrapInfo(bool show);

   // File Type data
   HWND hFTList;
   std::unordered_map<wstring, wstring> mapFileDescToType;
   std::unordered_map<wstring, wstring> mapFileTypeToDesc;

   // Styleset data
   struct StyleInfo {
      int backColor;
      int foreColor;
      int bold;
      int italics;
   };

   wstring currentStyleTheme{};
   StyleInfo styleEOL;
   vector<StyleInfo> styleSet;

   // Regex data
   wstring fwVizRegexed{};

   struct RecordInfo {
      wstring label;
      string marker;
      regex regExpr;
      vector<int> fieldStarts;
      vector<int> fieldWidths;
      vector<wstring> fieldLabels;
   };

   vector<RecordInfo> recInfoList;

   // Field Info tracking
   int caretRecordStartPos, caretRecordEndPos, caretRecordRegIndex, caretEolMarkerPos;
};
