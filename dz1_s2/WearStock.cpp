#include "main.h"

void WearStock::addWears(std::vector<std::string> names, std::vector<std::vector<StockWearValue>> sizes)
{
	for (int i = 0; i < names.size(); i++)
	{
		this->products[names[i]] = sizes[i];
	}
}

bool WearStock::addwear(std::string name, std::vector<StockWearValue> sizes)
{
	this->products[name] = sizes;
	if (this->amount() > this->size) {
		this->products.erase(name);
		return false;
	}
	return true;
}

void WearStock::setCount(std::string name, StockWearValue value)
{
	std::vector<StockWearValue> j = this->products[name];
	for (int i = 0; i < j.size(); i++)
	{
		if (j[i] == value)
			j[i] = value;
	}
}

int WearStock::sizeQty()
{
	return this->size;
}

std::string WearStock::getCity()
{
	return this->city;
}

std::string WearStock::toString()
{
	std::string result = "WearStock{" + name + ";" + city + ";" + std::to_string(size);
	for (std::map<std::string, std::vector<WearStock::StockWearValue>>::iterator i = products.begin(); i != products.end(); i++)
	{
		result += ";" + i->first + "=";
		for (int j = 0; j < i->second.size(); j++)
		{
			result += i->second[j].toString();
			if (j != i->second.size() - 1)
				result += ",";
		}
	}
	return result + "}";
}

size_t WearStock::amount()
{
	size_t result = 0;
	for (auto it : this->products)
	{
		for (auto product : it.second) {
			result += product.getCount();
		}
	}
	return result;
}

WearStock* WearStock::fromString(std::string data)
{
	std::vector<std::string> d1 = split(data, ";");
	WearStock* w = new WearStock(ReplaceAll(d1[0], "WearStock{", ""), d1[1], atoi(d1[2].c_str()));
	for (int i = 3; i < d1.size(); i++) {
		std::vector<std::string> d2 = split(d1[i], "=");
		std::vector<WearStock::StockWearValue> sizes;
		std::vector<std::string> d3 = split(d2[1], ",");
		for (int j = 0; j < d3.size(); j++) {
			std::vector<std::string> d4 = split(d3[j], "/");
			sizes.push_back(WearStock::StockWearValue(atoi(d4[0].c_str()), atoi(d4[1].c_str()), atoi(d4[2].c_str())));
		}
		w->addwear(d2[0], sizes);
	}
	return w;
}

std::ostream & operator<<(std::ostream &out, WearStock &stock)
{
	out << "Name: " << stock.name << ". City: " << stock.city << ". Size: " << stock.size << std::endl << "Clothers: " << std::endl;
	for (std::map<std::string, std::vector<WearStock::StockWearValue>>::iterator i = stock.products.begin(); i != stock.products.end(); i++)
	{
		out << i->first << ": ";
		for (int j = 0; j < i->second.size(); j++)
		{
			out << i->second[j] << " ";
		}
		out << std::endl;
	}
	return out;
}