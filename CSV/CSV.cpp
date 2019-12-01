#include "CSV.h"

std::string CSV::parseData(const std::string & line, const int & column)
{
	std::stringstream ss(line);
	std::vector<std::string> data;
	std::string value;
	int numOfData = 0;

	while (std::getline(ss, value, ';'))
	{
		//value.pop_back();
		//value.erase(0, 1);
		data.push_back(value);
		numOfData++;
	}

	if (column >= numOfData)
		return "You selected wrong column";
	else
		return data.at(column);
}
//
//void CSV::loadCount2(const char * filepath)
//{
//	std::ifstream iFile(filepath);
//	std::string line;
//	HWND list = menuSelect.list;
//	Database db = Database(DB_PATH);
//
//	if (iFile.is_open())
//	{
//		while (std::getline(iFile, line))
//		{
//			std::string code = parseData(line, 0);
//			std::string count = parseData(line, 3);
//
//			CList::setItemText(list, count.c_str(), CList::findItem(list, code.c_str()), 4);
//			db.setRowValueInt(code.c_str(), "Count2", atoi(count.c_str()));
//		}
//		iFile.close();
//	}
//}
//
//void CSV::loadCount15(const char * filepath)
//{
//	std::ifstream iFile(filepath);
//	std::string line;
//	HWND list = menuSelect.list;
//	Database db = Database(DB_PATH);
//
//	if (iFile.is_open())
//	{
//		while (std::getline(iFile, line))
//		{
//			std::string code = parseData(line, 0);
//			std::string count = parseData(line, 3);
//
//			db.setRowValueInt(code.c_str(), "Count15", atoi(count.c_str()));
//			CList::setItemText(list, count.c_str(), CList::findItem(list, code.c_str()), 5);
//		}
//		iFile.close();
//	}
//}
//
//void CSV::loadName(const char * filepath)
//{
//	std::ifstream iFile(filepath);
//	std::string line;
//	HWND list = menuSelect.list;
//	Database db = Database(DB_PATH);
//
//	if (iFile.is_open())
//	{
//		while (std::getline(iFile, line))
//		{
//			std::string code = parseData(line, 0);
//			std::string name = parseData(line, 1);
//			std::string note = parseData(line, 2);
//
//			if (strcmp(CList::getDataFromRow(list, CList::findItem(list, code.c_str()), 1), "New Product") == 0)
//			{
//				CList::setItemText(list, name.c_str(), CList::findItem(list, code.c_str()), 1);
//				CList::setItemText(list, note.c_str(), CList::findItem(list, code.c_str()), 2);
//				db.setRowValueTxt(code.c_str(), "Name", name.c_str());
//				db.setRowValueTxt(code.c_str(), "Note", note.c_str());
//			}
//		}
//	}
//}