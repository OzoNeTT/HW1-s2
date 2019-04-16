#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <cctype>
#include <cstdio>    

namespace fs = std::filesystem;

std::vector<std::string> split(std::string s, std::string delimiter);
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

class Stock
{
protected:
	std::string name;
	std::string city;
	int size;

public:
	Stock(std::string name, std::string city, int size)
	{
		 this->name=name;
		 this->city=city;
		 this->size=size;
	}

	std::string getName() {
		return this->name;
	}

	virtual int sizeQty()
	{
		return this->size;
	}

	virtual std::string getCity()
	{
		return this->city;
	}
	virtual std::string toString() = NULL{}
	virtual size_t getSize() = 0;
	virtual size_t amount() = 0;
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
		friend std::ostream& operator<< (std::ostream &out, StockWearValue &value)
		{
			out << "{Size: " << value.size << "; Height: " << value.height << "; Count: " << value.count << "}";
			return out;
		}
		virtual std::string toString() {
			return std::to_string(this->size) + "/" + std::to_string(this->height) + "/" + std::to_string(this->count);
		}
		int getSizeSize()
		{
			return this->size;
		}
		int getCount()
		{
			return this->count;
		}

	} bar;
	WearStock(std::string name, std::string city, int size) : Stock(name, city, size){}
	void addWears(std::vector<std::string>, std::vector<std::vector<StockWearValue>> sizes);
	bool addwear(std::string, std::vector<StockWearValue>);
	void setCount(std::string, StockWearValue);
	friend std::ostream& operator<< (std::ostream &, WearStock &);
	int sizeQty();
	size_t getSize()
	{
		return bar.getSizeSize();
	}
	std::string getCity();
	auto &getProducts()
	{
		return this->products;
	}
	std::string toString();
	size_t amount() override;
	static WearStock* fromString(std::string data);
private:
	std::map<std::string, std::vector<StockWearValue>> products;
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
		int getCount() const
		{
			return this->count;
		}
		bool operator==(StockShoeValue& b)
		{
			return this->size == b.size;
		}
		friend std::ostream& operator<< (std::ostream &out, StockShoeValue &value)
		{
			out << "{Size: " << value.size << "; Count: " << value.count << "}";
			return out;
		}
		virtual std::string toString() {
			return std::to_string(this->size) + "/" + std::to_string(this->count);
		}

		int getSizeSize()
		{
			return this->size;
		}
	} barr;
	ShoeStock(std::string name, std::string city, int size) : Stock(name, city, size) {}
	void addWears(std::vector<std::string>, std::vector<std::vector<StockShoeValue>> sizes);
	bool addwear(std::string, std::vector<StockShoeValue>);
	void setCount(std::string, StockShoeValue);
	friend std::ostream& operator<< (std::ostream &, ShoeStock &);
	int sizeQty();
	std::string getCity();
	size_t getSize()
	{
		return barr.getSizeSize();
	}
	auto &getProducts()
	{
		return this->products;
	}
	std::string toString();
	size_t amount() override;
	static ShoeStock* fromString(std::string data);
private:
	std::map<std::string, std::vector<StockShoeValue>> products;
};

class DataBase {
	std::string name;
public:
	DataBase(std::string);
	void save();
	void save(Stock*);
	std::vector<Stock*> getData();
	std::vector<Stock*> search(std::string stockName);
	size_t countElements();
};