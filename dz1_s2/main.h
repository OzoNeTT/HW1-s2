#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

vector<string> split(string s, string delimiter);
string ReplaceAll(string str, const string& from, const string& to);

class Stock
{
protected:
	string name;
	string city;
	int size;

public:
	Stock(string name, string city, int size)
	{
		 this->name=name;
		 this->city=city;
		 this->size=size;
	}

	string getName() {
		return this->name;
	}

	virtual int sizeQty()
	{
		return this->size;
	}
	virtual string toString() = NULL;

};

class WearStock : public Stock
{
public:
	class StockWearValue
	{
		int size;
		int height;
		int count;

	public:
		StockWearValue()
		{
			this->size = 0;
			this->height = 0;
			this->count = 0;
		}
		StockWearValue(int size, int height)
		{
			this->size = size;
			this->height = height;
		}
		StockWearValue(int size, int height, int count)
		{
			this->size = size;
			this->height = height;
			this->count = count;
		}
		bool operator==(StockWearValue& b)
		{
			return this->height == b.height && this->size == b.size;
		}
		friend ostream& operator<< (ostream &out, StockWearValue &value)
		{
			out << "{Size: " << value.size << "; Height: " << value.height << "; Count: " << value.count << "}";
			return out;
		}
		virtual string toString() {
			return to_string(this->size) + "/" + to_string(this->height) + "/" + to_string(this->count);
		}

	};
	WearStock(string name, string city, int size) : Stock(name, city, size){}
	void addWears(vector<string>, vector<vector<StockWearValue>> sizes);
	void addwear(string, vector<StockWearValue>);
	void setCount(string, StockWearValue);
	friend ostream& operator<< (ostream &, WearStock &);
	int sizeQty();
	string toString();
	static WearStock* fromString(string data);
private:
	map<string, vector<StockWearValue>> products;
};

class ShoeStock : public Stock
{
public:
	class StockShoeValue
	{
		int size;
		int count;
	public:
		StockShoeValue()
		{
			this->size = 0;
			this->count = 0;
		}
		StockShoeValue(int size, int count)
		{
			this->size = size;
			this->count = count;
		}
		bool operator==(StockShoeValue& b)
		{
			return this->size == b.size;
		}
		friend ostream& operator<< (ostream &out, StockShoeValue &value)
		{
			out << "{Size: " << value.size << "; Count: " << value.count << "}";
			return out;
		}
		virtual string toString() {
			return to_string(this->size) + "/" + to_string(this->count);
		}
	};
	ShoeStock(string name, string city, int size) : Stock(name, city, size) {}
	void addWears(vector<string>, vector<vector<StockShoeValue>> sizes);
	void addwear(string, vector<StockShoeValue>);
	void setCount(string, StockShoeValue);
	friend ostream& operator<< (ostream &, ShoeStock &);
	int sizeQty();
	string toString();
	static ShoeStock* fromString(string data);
private:
	map<string, vector<StockShoeValue>> products;
};

class DataBase {
	string name;
public:
	DataBase(string);
	void save();
	void save(Stock*);
	vector<Stock*> getData();
	Stock* search(string stockName);
};