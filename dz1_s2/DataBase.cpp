#include "main.h"

DataBase::DataBase(std::string name)
{
	this->name = name;
}

void DataBase::save() {
	std::ofstream f2(this->name, std::ios::app);
	f2 << "";
	f2.close();
}

void DataBase::save(Stock* stock) {
	std::ofstream f2(this->name, std::ios::app);
	f2 << stock->toString() + "\r\n";
	f2.close();
}

std::vector<Stock*> DataBase::getData()
{
	std::vector<Stock*> stocks;
	std::ifstream f(this->name);
	std::string str;

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

std::vector<Stock*> DataBase::search(std::string stockName)
{
	std::vector<Stock*> res;
	std::vector<Stock*> v = this->getData();
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->getName() == stockName)
			res.push_back(v[i]);
	}

	return res;
}

size_t DataBase::countElements()
{
	size_t result = 0;
	std::vector<Stock*> v = this->getData();
	for (auto it : v) {
		result += it->amount();
	}
	return result;
}