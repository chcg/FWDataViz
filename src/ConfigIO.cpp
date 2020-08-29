#include "PluginDefinition.h"

void ConfigIO::init() {
   const std::wstring sPluginFolder{ L"FWDataViz" };
   TCHAR sPluginDirectory[MAX_PATH];

   ::SendMessage(nppData._nppHandle, NPPM_GETNPPDIRECTORY, MAX_PATH, (LPARAM)sPluginDirectory);
   ::PathAppendW(sPluginDirectory, (L"plugins\\" + sPluginFolder).c_str());

   ::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)pluginConfigDir);

   // if no existing config path, create it
   if (!PathFileExists(pluginConfigDir))
   {
      ::CreateDirectory(pluginConfigDir, NULL);
   }

   ::PathAppendW(pluginConfigDir, sPluginFolder.c_str());

   // if no existing config file, create it
   if (!PathFileExists(pluginConfigDir)) {
      ::CreateDirectory(pluginConfigDir, NULL);
   }

   // if config files are missing copy them from the plugins folder
   const std::wstring sDefaultsPrefix{ L"defaults_" };

   TCHAR sDefaultsFile[MAX_PATH];
   TCHAR sConfigFile[MAX_PATH];


   for (int i{}; i < CONFIG_FILE_COUNT; i++) {
      ::PathCombine(sConfigFile, pluginConfigDir, CONFIG_FILES[i].c_str());

      if (!PathFileExists(sConfigFile)) {
         ::PathCombine(sDefaultsFile, sPluginDirectory, (sDefaultsPrefix + CONFIG_FILES[i]).c_str());
         ::CopyFile(sDefaultsFile, sConfigFile, TRUE);
      }
   }
}

std::wstring ConfigIO::getConfigStringW(LPCWSTR fileName, LPCWSTR sectionName, LPCWSTR keyName, LPCWSTR defaultValue) {
   const int bufSize{ 32000 };
   wchar_t ftBuf[bufSize];
   DWORD retLen{};

   retLen = GetPrivateProfileStringW(sectionName, keyName, defaultValue, ftBuf, bufSize, fileName);

   return std::wstring{ ftBuf };
}

int ConfigIO::getPref(LPCWSTR fileName, LPCWSTR sectionName, LPCWSTR key, int default) {
   return ::GetPrivateProfileInt(sectionName, key, default, fileName);
}

void ConfigIO::setPref(LPCWSTR fileName, LPCWSTR sectionName, LPCWSTR key, int val) {
   ::WritePrivateProfileString(sectionName, key, TO_LPCWSTR(val), fileName);
}

void ConfigIO::TokenizeW(LPCWSTR str, std::vector<std::wstring> &results, LPCWSTR delim) {
   std::size_t nStart{}, nEnd{};
   std::wstring text{ str };

   while ((nEnd = text.find(delim, nStart)) != std::wstring::npos) {
      if (nEnd > nStart) {
         results.emplace_back(text.substr(nStart, nEnd - nStart));
      }
      nStart = nEnd + 1;
   }
   if (nStart < text.length()) {
      results.emplace_back(text.substr(nStart));
   }
}

void ConfigIO::TokenizeW(LPCWSTR str, std::vector<int> &results, LPCWSTR delim) {
   std::vector<std::wstring> interims{};
   TokenizeW(str, interims, delim);

   for (auto istr : interims) {
      results.emplace_back(std::stoi(istr));
   }
}
