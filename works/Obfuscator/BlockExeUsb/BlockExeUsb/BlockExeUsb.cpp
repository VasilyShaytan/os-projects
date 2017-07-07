// BlockExeUsb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

#ifdef _UNICODE
#  define _tcout wcout
#else
#  define _tcout cout
#endif // _UNICODE


//запись ключа в реестр
int KeyToRegestrSystem(DWORD keyValue)
{
	// Путь ключа
	_TCHAR szPath[] = _T("System\\CurrentControlSet\\Control\\StorageDevicePolicies\\");

	HKEY hKey;

	// Создаем ключ в ветке HKEY_LOCAL_MACHINE
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		_tcout << _T("При создании ключа произошла ошибка") << endl;
		return 1;
	}

	// Пишем значение в созданный ключ
	if (RegSetValueEx(hKey, TEXT("ExecuteProtect"), 0, REG_DWORD, (const BYTE*)&keyValue, sizeof(keyValue)) != ERROR_SUCCESS) {
		_tcout << _T("При записи строки произошла ошибка") << endl;
		return 2;
	}

	// Закрываем описатель ключа
	if (RegCloseKey(hKey) != ERROR_SUCCESS) {
		_tcout << _T("При закрытии ключа произошла ошибка") << endl;
		return 3;
	};
	return 0;
}

//запись ключа  в реестр
int KeyToRegestr(DWORD keyValue)
{
	// Путь ключа
	_TCHAR szPath[] = _T("Software\\Policies\\Microsoft\\Windows\\RemovableStorageDevices\\{53f5630d-b6bf-11d0-94f2-00a0c91efb8b}\\");

	HKEY hKey;

	// Создаем ключ в ветке HKEY_LOCAL_MACHINE
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		_tcout << _T("При создании ключа произошла ошибка") << endl;
		return 1;
	}

	// Пишем значение в созданный ключ
	if (RegSetValueEx(hKey, TEXT("Deny_Execute"), 0, REG_DWORD, (const BYTE*)&keyValue, sizeof(keyValue)) != ERROR_SUCCESS) {
		_tcout << _T("При записи строки произошла ошибка") << endl;
		return 2;
	}

	// Закрываем описатель ключа
	if (RegCloseKey(hKey) != ERROR_SUCCESS) {
		_tcout << _T("При закрытии ключа произошла ошибка") << endl;
		return 3;
	};
	return 0;
}

//печать меню в консоль
void PrintMenu()
{
	cout << "1 - Включить блокировку\n";
	cout << "2 - Отключить блокировку\n";
	cout << "3 - Выход из программы\n";
	cout << "> ";
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Устанавливаем русскую кодовую страницу для вывода кириллицы
	//_tsetlocale(LC_ALL, _T("Russain"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//номер пункта меню
	int choice;
	cout << "Главное меню:\n";
	do {
		PrintMenu(); //печатаем меню
		cin >> choice; //считваем номер пункта

		switch (choice) {
		case 1: //создание ключа блокирующего exe
			((KeyToRegestr(1) && KeyToRegestrSystem(1)) == 0) ? cout << "\nБлокировка включена.\n" : cout << "\nУвы, блокировка не включена.\n";
			break;
		case 2: //создание ключа разблокирующего exe
			((KeyToRegestr(0) && KeyToRegestrSystem(0)) == 0) ? cout << "\nБлокировка выключена.\n" : cout << "\nУвы, блокировка не выключена.\n";
			break;
			/*case 3: //прощание перед выходом
			cout << "Goodbye!\n";
			break;*/
		default: //
				 //PrintMenu();
				 //cin >> choice;
			cout << "Такого пункта в меню нет.\n";
		}
	} while (choice != 3);

	//_tsystem(_T("pause"));
	return 0;
}