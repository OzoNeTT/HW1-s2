#include "main.h"

DataBase::DataBase(string name)
{
	this->name = name;
}
void DataBase::save() {
	ofstream f2(this->name, ios::app);
	f2 << "";
	f2.close();
}

void DataBase::save(Stock* stock) {
	ofstream f2(this->name, ios::app);
	f2 << stock->toString() + "\r\n";
	f2.close();
}

vector<Stock*> DataBase::getData()
{
	vector<Stock*> stocks;
	ifstream f(this->name);
	string str;

	while (getline(f, str))
	{
		if (str.find("WearStock") != std::string::npos) {
			stocks.push_back(WearStock::fromString(str));
		}
		else if (str.find("ShoeStock") != std::string::npos) {
			stocks.push_back(ShoeStock::fromString(str));
		}
	}
	f.close();
	return stocks;
}

vector<Stock*> DataBase::search(string stockName)
{
	vector<Stock*> res;
	vector<Stock*> v = this->getData();
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->getName() == stockName)
			res.push_back(v[i]);
	}

	return res;
}

size_t DataBase::countElements()
{
	size_t result = 0;
	vector<Stock*> v = this->getData();
	for (auto it : v) {
		result += it->amount();
	}
	return result;
}
