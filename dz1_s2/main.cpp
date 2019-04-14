#include "main.h"
using namespace std;


vector<string> &split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

string ReplaceAll(string str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

void help()
{
	std::cout << endl;
	std::cout << "	create <DB name> - to create a new DB" << endl;
	std::cout << "	edit <DB name> - to edit existed DB" << endl;
	std::cout << "	list - to see all created DB" << endl;
	std::cout << "	view <DB name> - see the DB in console" << endl;
	std::cout << "	search <DB name> - search Stocks in DB" << endl;
	std::cout << "	count <DB name> - count elements on each Stock" << endl;
	std::cout << "	sort <DB name> - to sort DB" << endl;
	std::cout << endl;
}

void createDB(string dbname)
{
	DataBase db(dbname + ".txt");
	db.save();
}

void showList()
{
	cout << "	Existed DB: \n\n";
	string path;		
	for (fs::recursive_directory_iterator i(path), end; i != end; i++)
	{
		if (!fs::is_directory(i->path()) && i->path().extension() == ".txt")
		{				
			cout << "	" << i->path() << "\n";
		}
	}
}

void editDB(string dbname)
{
	cout << "		YOU OPENED THE \"" << dbname << "\"" << "\n\t TO SEE DB - open\n\t TO ADD SOME ELEMENTS - add\n\t TO REMOVE ELEMENTS remove" << endl <<  ">> ";
	string fans;
	string ans;
	string answer;
	bool contin = true;
	string city; string name; int qty;	int size; int height; int count; string type;
	int qtyOfElem; int qtyOfSizes;
	getline(cin, fans);
	
	if (fans == "open")
	{
		string x;
		ifstream inFile;

		inFile.open(dbname);
		if (!inFile) {
			cout << "Unable to open file";
		}

		while (inFile >> x) {
			cout << x << endl;
		}

		inFile.close();
	}
	else if (fans == "add")
	{
		while (contin)
		{
			while (true) {
				cout << "	What kind of stock you want? If Shoes - type shoe, if Wear - type wear!" << endl;
				getline(cin, ans);
				if (ans == "wear")
				{
					cout << "Enter name of stock: "; getline(cin, name);
					cout << "Enter the city: "; getline(cin, city);
					cout << "Enter the max stock size: "; cin >> qty;
					WearStock* a = new WearStock(name, city, qty);
					cout << "Enter qty of different products: "; cin >> qtyOfElem;
					for (int i = 0; i < qtyOfElem; i++) {
						vector<WearStock::StockWearValue> sizes;
						cin.ignore();
						cout << "Enter the type of product: "; getline(cin, type);
						cout << "Enter qty of different sizes: "; cin >> qtyOfSizes;
						for (int j = 0; j < qtyOfSizes; j++)
						{
							cout << "	ENTER SIZES FOR " << type << " FOR " << j + 1 << " SIZETYPE!" << endl;
							cout << "Enter size: "; cin >> size;
							cout << "Enter height: "; cin >> height;
							cout << "Enter count: "; cin >> count;
							sizes.push_back(WearStock::StockWearValue(size, height, count));
						}
						bool isSuccess = a->addwear(type, sizes);
						if (!isSuccess) {
							std::cout << "Size of stock is not so big! If you want to add less things firstly remove existed empty one!" << std::endl;
						}
					}
					DataBase db(dbname);
					db.save(a);
					break;
				}
				else if (ans == "shoe")
				{
					cout << "Enter name of stock: "; getline(cin, name);
					cout << "Enter the city: "; getline(cin, city);
					cout << "Enter the max stock size: "; cin >> qty;
					ShoeStock* a = new ShoeStock(name, city, qty);
					cout << "Enter qty of different products: "; cin >> qtyOfElem;
					for (int i = 0; i < qtyOfElem; i++) {
						vector<ShoeStock::StockShoeValue> sizes;
						cin.ignore();
						cout << "Enter the type of product: "; getline(cin, type);
						cout << "Enter qty of different sizes: "; cin >> qtyOfSizes;
						for (int j = 0; j < qtyOfSizes; j++)
						{
							cout << "	ENTER SIZES FOR " << type << " FOR " << j + 1 << " SIZETYPE!" << endl;
							cout << "Enter size: "; cin >> size;
							cout << "Enter count: "; cin >> count;
							sizes.push_back(ShoeStock::StockShoeValue(size, count));
						}
						bool isSuccess = a->addwear(type, sizes);
						if (!isSuccess) {
							std::cout << "Size of stock is not so big! If you want to add less things firstly remove existed empty one!" << std::endl;
						}
						
					}
					DataBase db(dbname);
					db.save(a);
					break;
				}
				else
					cout << "	There are no such a answer, choose from fallowing!" << endl;
			}
			while (true) {
				cout << "	Want to add more? y/n" << endl << ">> ";
				cin.ignore();
				getline(cin, answer);
				if (answer == "n") {
					contin = false;
					break;
				}
				else if (answer == "y") {
					contin = true;
					break;
				}
				else
					cout << "	Incorrect answer! Type y or n!" << endl;
			}

		}
	}
	else if (fans == "remove")
	{
		std::ifstream file_in;

		file_in.open(dbname);

		if (!file_in)
		{
			cout << "	Sorry, the file can't be opened!" << std::endl;
		}
		string x;
		ifstream inFile;

		inFile.open(dbname);
		if (!inFile) {
			cout << "Unable to open file";
		}

		int iter = 1;
		while (inFile >> x) {
			cout <<" " << iter << "  " << x << endl;
			iter++;
		}

		inFile.close();
		std::cout << "	Enter string number: " << std::endl << ">> ";
		int i_number_line_delete = 0; //для хранения номера строки который нужно удалить
		std::cin >> i_number_line_delete; 	cin.ignore();
		int i_number_line_now = 0; //счётчик строк
		std::string line; //для хранения строки
		std::string line_file_text; //для хранения текста файла
		while (getline(file_in, line))
		{
			i_number_line_now++;
			if (!(i_number_line_now == i_number_line_delete))
			{
				line_file_text.insert(line_file_text.size(), line); 
				line_file_text.insert(line_file_text.size(), "\r\n");
			}
		}
		file_in.close();
		std::ofstream file_out;
		file_out.open(dbname, std::ios::trunc | std::ios::binary); 
		file_out.write(line_file_text.c_str(), line_file_text.size());
		file_out.clear();
	}
	else
		cout << "	There no such comand! " << endl;

}

void view(string dbname)
{
	string x;
	ifstream inFile;

	inFile.open(dbname);
	if (!inFile) {
		cout << "Unable to open file";
	}

	while (inFile >> x) {
		cout << x << endl;
	}

	inFile.close();
}

void searchForName(string dbname)
{
	string answer;
	cout << "		YOU SEARCH IN " << dbname << endl;
	DataBase db(dbname);
	cout << "	Enter the name of stock you want to find: " << endl << ">> ";
	getline(cin, answer);
	vector<Stock*> res = db.search(answer);
	for (auto i = 0; i < res.size(); i++)
	{
		if (res[i] != nullptr)
			cout << res[i]->toString() << endl;
		else
			cout << "	Not found!" << endl;
	}
}

void countElem(string dbname)
{
	DataBase db(dbname);
	size_t res = db.countElements(); 
	cout << "	There are " << res << " elements in DB" << endl;
	auto v = db.getData();
	
	size_t amountWear = 0;
	size_t amountShoe = 0;

	for (auto pointer : v) {
		WearStock *wear = dynamic_cast<WearStock *>(pointer);
		if (wear) {
			amountWear += pointer->amount();
		} else {
			amountShoe += pointer->amount();
		}
	}

	cout << "	Qty of products in WearStock: " << amountWear << endl;
	cout << "	Qty of products in ShoeStock: " << amountShoe << endl;
}

void sortDB(string dbname)
{
	ifstream inFile;
	inFile.open(dbname);
	if (!inFile.fail())
	{
		

	}
	else {
		cout << "	Error Opening File" << endl;
	}
}

void starter()
{
	string answer;

	cout << "		Hello User! I am a DB creator! Type \"help\" to see list of comands!" << endl;
	while (true)
	{
		cout << endl << ">> ";
		getline(cin, answer);
		vector<string> comand = split(answer, ' ');
		if (answer == "help")
			help();
		else if (comand[0] == "create" && comand.size()==2) {
			createDB(comand[1]);
		}
		else if (answer == "list") {
			showList();
		}
		else if (comand[0] == "edit" && comand.size() == 2) {
			editDB(comand[1]);
		}
		else if (comand[0] == "view" && comand.size() == 2) {
			view(comand[1]);
		}
		else if (comand[0] == "search" && comand.size() == 2){
			searchForName(comand[1]);
		}
		else if (comand[0] == "count" && comand.size() == 2){
			countElem(comand[1]);
		}
		else if (comand[0] == "sort" && comand.size() == 2) {
			sortDB(comand[1]);
		}
		else
			cout << "	Sorry, there are no such comand!" << endl;
		
	}
}

int main()
{
	starter();

	system("Pause");
	return 0;
}