#include "main.h"

void ShoeStock::addWears(vector<string> names, vector<vector<StockShoeValue>> sizes)
{
	for (int i = 0; i < names.size(); i++)
	{
		this->products[names[i]] = sizes[i];
	}
}

bool ShoeStock::addwear(string name, vector<StockShoeValue> sizes)
{
	this->products[name] = sizes;
	if (this->amount() > this->size) {
		this->products.erase(name);
		return false;
	}
	return true;
}

void ShoeStock::setCount(string name, StockShoeValue value)
{
	vector<StockShoeValue> j = this->products[name];
	for (int i = 0; i < j.size(); i++)
	{
		if (j[i] == value)
			j[i] = value;
	}
}

int ShoeStock::sizeQty()
{
	return 0;
}

string ShoeStock::toString()
{
	string result = "ShoeStock{" + name + ";" + city + ";" + to_string(size);
	for (auto i = products.begin(); i != products.end(); i++)
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

size_t ShoeStock::amount()
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

ShoeStock* ShoeStock::fromString(string data)
{
	vector<string> d1 = split(data, ";");
	ShoeStock* w = new ShoeStock(ReplaceAll(d1[0], "ShoeStock{", ""), d1[1], atoi(d1[2].c_str()));
	for (int i = 3; i < d1.size(); i++) {
		vector<string> d2 = split(d1[i], "=");
		vector<ShoeStock::StockShoeValue> sizes;
		vector<string> d3 = split(d2[1], ",");
		for (int j = 0; j < d3.size(); j++) {
			vector<string> d4 = split(d3[j], "/");
			sizes.push_back(ShoeStock::StockShoeValue(atoi(d4[0].c_str()), atoi(d4[1].c_str())));
		}
		w->addwear(d2[0], sizes);
	}
	return w;
}

ostream & operator<<(ostream &out, ShoeStock &stock)
{
	out << "Name: " << stock.name << ". City: " << stock.city << ". Size: " << stock.size << endl << "Clothers: " << endl;
	for (auto i = stock.products.begin(); i != stock.products.end(); i++)
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