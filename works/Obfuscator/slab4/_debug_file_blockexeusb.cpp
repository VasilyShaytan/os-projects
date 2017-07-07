


#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

#ifdef _UNICODE
#  define _tcout wcout
#else
#  define _tcout cout
#endif 



int KeyToRegestrSystem(DWORD keyValue)
{
	
	_TCHAR szPath[] = ( decrypt::dec_debug(_T( "_debug_System\\CurrentControlSet\\Control\\StorageDevicePolicies\\")));

	HKEY hKey;

	
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		_tcout << ( decrypt::dec_debug(_T( "_debug_При создании ключа произошла ошибка"))) << endl;
		return 1;
	}

	
	if (RegSetValueEx(hKey, ( decrypt::dec_debug(_T( "_debug_ExecuteProtect"))), 0, REG_DWORD, (const BYTE*)&keyValue, sizeof(keyValue)) != ERROR_SUCCESS) {
		_tcout << ( decrypt::dec_debug(_T( "_debug_При записи строки произошла ошибка"))) << endl;
		return 2;
	}

	
	if (RegCloseKey(hKey) != ERROR_SUCCESS) {
		_tcout << ( decrypt::dec_debug(_T( "_debug_При закрытии ключа произошла ошибка"))) << endl;
		return 3;
	};
	return 0;
}


int KeyToRegestr(DWORD keyValue)
{
	
	_TCHAR szPath[] = ( decrypt::dec_debug(_T( "_debug_Software\\Policies\\Microsoft\\Windows\\RemovableStorageDevices\\{53f5630d-b6bf-11d0-94f2-00a0c91efb8b}\\")));

	HKEY hKey;

	
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		_tcout << ( decrypt::dec_debug(_T( "_debug_При создании ключа произошла ошибка"))) << endl;
		return 1;
	}

	
	if (RegSetValueEx(hKey, ( decrypt::dec_debug(_T( "_debug_Deny_Execute"))), 0, REG_DWORD, (const BYTE*)&keyValue, sizeof(keyValue)) != ERROR_SUCCESS) {
		_tcout << ( decrypt::dec_debug(_T( "_debug_При записи строки произошла ошибка"))) << endl;
		return 2;
	}

	
	if (RegCloseKey(hKey) != ERROR_SUCCESS) {
		_tcout << ( decrypt::dec_debug(_T( "_debug_При закрытии ключа произошла ошибка"))) << endl;
		return 3;
	};
	return 0;
}


void PrintMenu()
{
	cout <<  decrypt::dec_debug(_T( "_debug_1 - Включить блокировку\n"));
	cout <<  decrypt::dec_debug(_T( "_debug_2 - Отключить блокировку\n"));
	cout <<  decrypt::dec_debug(_T( "_debug_3 - Выход из программы\n"));
	cout <<  decrypt::dec_debug(_T( "_debug_> "));
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	int choice;
	cout <<  decrypt::dec_debug(_T( "_debug_Главное меню:\n"));
	do {
		PrintMenu(); 
		cin >> choice; 

		switch (choice) {
		case 1: 
			((KeyToRegestr(1) && KeyToRegestrSystem(1)) == 0) ? cout <<  decrypt::dec_debug(_T( "_debug_\nБлокировка включена.\n")) : cout <<  decrypt::dec_debug(_T( "_debug_\nУвы, блокировка не включена.\n"));
			break;
		case 2: 
			((KeyToRegestr(0) && KeyToRegestrSystem(0)) == 0) ? cout <<  decrypt::dec_debug(_T( "_debug_\nБлокировка выключена.\n")) : cout <<  decrypt::dec_debug(_T( "_debug_\nУвы, блокировка не выключена.\n"));
			break;
			
		default: 
				 
				 
			cout <<  decrypt::dec_debug(_T( "_debug_Такого пункта в меню нет.\n"));
		}
	} while (choice != 3);

	
	return 0;
}
