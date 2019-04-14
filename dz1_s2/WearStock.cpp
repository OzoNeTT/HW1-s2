#include "main.h"

void WearStock::addWears(vector<string> names, vector<vector<StockWearValue>> sizes)
{
	for (int i = 0; i < names.size(); i++)
	{
		this->products[names[i]] = sizes[i];
	}
}

void WearStock::addwear(string name, vector<StockWearValue> sizes)
{
	this->products[name] = sizes;
}

void WearStock::setCount(string name, StockWearValue value)
{
	vector<StockWearValue> j = this->products[name];
	for (int i = 0; i < j.size(); i++)
	{
		if (j[i] == value)
			j[i] = value;
	}
}

int WearStock::sizeQty()
{
	return 0;
}

string WearStock::toString()
{
	string result = "WearStock{" + name + ";" + city + ";" + to_string(size);
	for (map<string, vector<WearStock::StockWearValue>>::iterator i = products.begin(); i != products.end(); i++)
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

WearStock* WearStock::fromString(string data)
{
	vector<string> d1 = split(data, ";");
	WearStock* w = new WearStock(ReplaceAll(d1[0], "WearStock{", ""), d1[1], atoi(d1[2].c_str()));
	for (int i = 3; i < d1.size(); i++) {
		vector<string> d2 = split(d1[i], "=");
		vector<WearStock::StockWearValue> sizes;
		vector<string> d3 = split(d2[1], ",");
		for (int j = 0; j < d3.size(); j++) {
			vector<string> d4 = split(d3[j], "/");
			sizes.push_back(WearStock::StockWearValue(atoi(d4[0].c_str()), atoi(d4[1].c_str()), atoi(d4[2].c_str())));
		}
		w->addwear(d2[0], sizes);
	}
	return w;
}

ostream & operator<<(ostream &out, WearStock &stock)
{
	out << "Name: " << stock.name << ". City: " << stock.city << ". Size: " << stock.size << endl << "Clothers: " << endl;
	for (map<string, vector<WearStock::StockWearValue>>::iterator i = stock.products.begin(); i != stock.products.end(); i++)
	{
		out << i->first << ": ";
		for (int j = 0; j < i->second.size(); j++)
		{
			out << i->second[j] << " ";
		}
		out << endl;
	}
	return out;
}