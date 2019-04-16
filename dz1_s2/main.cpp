#include "main.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)){
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

void removeDB(std::string dbname)
{
	
	if (remove(dbname.c_str()) != 0)
		std::cout << "	<<Error of deleting file!>>";
	else
		std::cout << "	<<File is successfully removed!>>";
}

void help()
{
	std::cout << std::endl;
	std::cout << "\tcreate <DB name>    - to create a new DB" << std::endl;
	std::cout << "\tedit <DB name>      - to edit existed DB" << std::endl;
	std::cout << "\tlist                - to see all created DB" << std::endl;
	std::cout << "\tview <DB name>      - see the DB in console" << std::endl;
	std::cout << "\tsearch <DB name>    - search Stocks in DB" << std::endl;
	std::cout << "\tcount <DB name>     - count elements on each Stock" << std::endl;
	std::cout << "\tsort <DB name>      - to sort DB" << std::endl;
	std::cout << "\tdelete <DB name>    - to delete DB" << std::endl;
	std::cout << "\tpick <DB name>      - to pick Stocks with defined paramentrs" << std::endl;
	std::cout << "\thow                 - to see string saving format" << std::endl;
	std::cout << "\texit                - to exit from DB redactor" << std::endl;
	std::cout << std::endl;
}

void createDB(std::string dbname)
{
	DataBase db(dbname + ".txt");
	db.save();
}

void showList()
{
	std::cout << "\tExisted DB: \n\n";
	std::string path;
	for (fs::recursive_directory_iterator i(path), end; i != end; i++){
		if (!fs::is_directory(i->path()) && i->path().extension() == ".txt"){				
			std::cout << "\t" << i->path().filename().string() << "\n";
		}
	}
}

void editDB(std::string dbname)
{
	std::cout << "\tYOU OPENED THE \"" << dbname << "\"" << "\n\t TO SEE DB - open\n\t TO ADD SOME ELEMENTS - add\n\t TO REMOVE ELEMENTS remove" << std::endl <<  ">> ";
	std::string fans;
	std::string ans;
	std::string answer;
	bool contin = true;
	std::string city; 
	std::string name; 
	int qty; 
	int size; 
	int height; 
	int count; 
	std::string type;
	int qtyOfElem; 
	int qtyOfSizes;
	getline(std::cin, fans);
	
	if (fans == "open")
	{
		std::string x;
		std::ifstream inFile;

		inFile.open(dbname);
		if (!inFile) {
			std::cout << "	<<Unable to open file!>>";
		}

		while (inFile >> x) {
			std::cout << x << std::endl;
		}

		inFile.close();
	}
	else if (fans == "add")
	{
		while (contin)
		{
			while (true) {
				std::cout << "	What kind of stock you want? If Shoes - type shoe, if Wear - type wear!" << std::endl << ">> ";
				getline(std::cin, ans);
				if (ans == "wear")
				{
					std::cout << " Enter name of stock: "; getline(std::cin, name);
					std::cout << " Enter the city: "; getline(std::cin, city);
					std::cout << " Enter the max stock size: "; std::cin >> qty;

					WearStock* a = new WearStock(name, city, qty);
					std::cout << " Enter qty of different products: "; std::cin >> qtyOfElem;

					for (int i = 0; i < qtyOfElem; i++) {
						std::vector<WearStock::StockWearValue> sizes;
						std::cin.ignore();

						std::cout << " Enter the type of product: "; getline(std::cin, type);
						std::cout << " Enter qty of different sizes: "; std::cin >> qtyOfSizes;
						for (int j = 0; j < qtyOfSizes; j++)
						{
							std::cout << "	ENTER SIZES FOR " << type << " FOR " << j + 1 << " SIZETYPE!" << std::endl;
							std::cout << " Enter size: "; std::cin >> size;
							std::cout << " Enter height: "; std::cin >> height;
							std::cout << " Enter count: "; std::cin >> count;
							sizes.push_back(WearStock::StockWearValue(size, height, count));
						}
						bool isSuccess = a->addwear(type, sizes);
						if (!isSuccess) {
							std::cout << "	<<Size of stock is not so big! If you want to add less things firstly remove existed empty one!>>" << std::endl;
						}
					}
					DataBase db(dbname);
					db.save(a);
					break;
				}
				else if (ans == "shoe")
				{
					std::cout << " Enter name of stock: "; getline(std::cin, name);
					std::cout << " Enter the city: "; getline(std::cin, city);
					std::cout << " Enter the max stock size: "; std::cin >> qty;

					ShoeStock* a = new ShoeStock(name, city, qty);
					std::cout << " Enter qty of different products: "; std::cin >> qtyOfElem;

					for (int i = 0; i < qtyOfElem; i++) {
						std::vector<ShoeStock::StockShoeValue> sizes;
						std::cin.ignore();
						
						std::cout << " Enter the type of product: "; getline(std::cin, type);
						std::cout << " Enter qty of different sizes: "; std::cin >> qtyOfSizes;
						for (int j = 0; j < qtyOfSizes; j++)
						{
							std::cout << "	ENTER SIZES FOR " << type << " FOR " << j + 1 << " SIZETYPE!" << std::endl;
							std::cout << " Enter size: "; std::cin >> size;
							std::cout << " Enter count: "; std::cin >> count;
							sizes.push_back(ShoeStock::StockShoeValue(size, count));
						}
						bool isSuccess = a->addwear(type, sizes);
						if (!isSuccess) {
							std::cout << "	<<Size of stock is not so big! If you want to add less things firstly remove existed empty one!>>" << std::endl;
						}
						
					}
					DataBase db(dbname);
					db.save(a);
					break;
				}
				else
					std::cout << "	<<There are no such a answer, choose from fallowing!>>" << std::endl;
			}
			while (true) {
				std::cout << "	Want to add more? |y/n|" << std::endl << ">> ";
				std::cin.ignore();
				getline(std::cin, answer);

				if (answer == "n") {
					contin = false;
					break;
				}
				else if (answer == "y") {
					contin = true;
					break;
				}
				else
					std::cout << "	<<Incorrect answer! Type |y| or |n| !>>" << std::endl;
			}

		}
	}
	else if (fans == "remove")
	{
		std::ifstream file_in;

		file_in.open(dbname);

		if (!file_in)
		{
			std::cout << "	<<Sorry, the file can't be opened!>>" << std::endl;
		}
		std::string x;
		std::ifstream inFile;

		inFile.open(dbname);
		if (!inFile) {
			std::cout << "	<<Unable to open file>>";
		}

		int iter = 1;
		while (inFile >> x) {
			std::cout <<" " << iter << "  " << x << std::endl;
			iter++;
		}

		inFile.close();
		std::cout << "	Enter string number: " << std::endl << ">> ";
		int i_number_line_delete = 0;
		std::cin >> i_number_line_delete; std::cin.ignore();
		int i_number_line_now = 0; 
		std::string line; 
		std::string line_file_text; 
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
	std::cout << "	<<There no such comand!>>" << std::endl;

}

void view(std::string dbname)
{
	std::string x;
	std::ifstream inFile;

	inFile.open(dbname);
	if (!inFile) {
		std::cout << "	<<Unable to open file!>>";
	}

	while (inFile >> x) {
		std::cout << x << std::endl;
	}

	inFile.close();
}

void searchForName(std::string dbname)
{
	std::string answer;
	std::cout << "		YOU SEARCH IN " << dbname << std::endl;
	DataBase db(dbname);

	std::cout << "	Enter the name of stock you want to find: " << std::endl << ">> ";
	getline(std::cin, answer);
	std::vector<Stock*> res = db.search(answer);
	for (auto i = 0; i < res.size(); i++)
	{
		if (res[i] != nullptr)
			std::cout << res[i]->toString() << std::endl;
		else
			std::cout << "	<<Not found!>>" << std::endl;
	}
}

void countElem(std::string dbname)
{
	DataBase db(dbname);
	size_t res = db.countElements(); 
	std::cout << "	There are " << res << " elements in DB" << std::endl;
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

	std::cout << "	Qty of products in WearStock: " << amountWear << std::endl;
	std::cout << "	Qty of products in ShoeStock: " << amountShoe << std::endl;
}

void sortDB(std::string dbname)
{
	int answer = 0;
	std::cout << "	You want to sort by alphabet(1) or Qty on Stock(2)?" << std::endl << ">> "; std::cin >> answer; std::cin.ignore();
	if (answer == 1){
		DataBase db(dbname);
		std::ifstream inFile;
		inFile.open(dbname);

		if (!inFile.fail())
		{
			std::vector<Stock*> v = db.getData();
			std::sort(v.begin(), v.end(), [](Stock *left, Stock *right) -> bool {
				return left->getName() < right->getName();
			});

			std::fstream oFile(dbname, std::ios::out);
			oFile.close();

			for (const auto &it : v) {
				db.save(it);
			}
		}
		else {
			std::cout << "	<<Error Opening File!>>" << std::endl;
		}
	}
	else if (answer == 2) {
		DataBase db(dbname);
		std::ifstream inFile;
		inFile.open(dbname);
		if (!inFile.fail())
		{
			std::vector<Stock*> v = db.getData();
			std::sort(v.begin(), v.end(), [](Stock *left, Stock *right) -> bool {
				return left->sizeQty() > right->sizeQty();
			});

			std::fstream oFile(dbname, std::ios::out);
			oFile.close();

			for (const auto &it : v) {
				db.save(it);
			}
		}
		else {
			std::cout << "	<<Error Opening File!>>" << std::endl;
		}
	}
	else {
		std::cout << "	<<You made a wrong choice!>>" << std::endl;
	}
}

void pickDB(std::string dbname)
{
	std::cout << "	You want to pick from city(1) or size(2)?" << std::endl << ">> ";
	int ans = 0;
	std::cin >> ans;
	if (ans == 1)
	{
		std::string city;
		std::string newfile;
		std::cout << " Enter city" << std::endl << ">> "; std::cin.ignore(); getline(std::cin, city);
		DataBase db(dbname);
		std::ifstream inFile;
		inFile.open(dbname);
		if (!inFile.fail())
		{
			std::vector<Stock*> temp;
			std::vector<Stock*> v = db.getData();
			for (auto &it : v)
			{
				if(it->getCity() == city)
				{
					temp.push_back(it);
				}
			}
			std::cout << " Enter file name with .txt" << std::endl << ">> "; getline(std::cin, newfile);
			DataBase ndb(newfile);

			for (const auto &it : temp) {
				ndb.save(it);
			}
		}
		else {
			std::cout << "	<<Error Opening File!>>" << std::endl;
		}
	}
	else if (ans == 2)
	{
		std::string newfile;
		std::string answer;
		std::cout << "	You want to pick \"low\" or \"high\" sizes?" << std::endl << ">> "; std::cin.ignore(); getline(std::cin, answer);
		if (answer == "low")
		{
			DataBase db(dbname);
			std::ifstream inFile;
			inFile.open(dbname);
			if (!inFile.fail()) {
				std::vector<Stock*> temp;
				std::vector<Stock*> v = db.getData();

				for (auto &it : v) {
					WearStock *wear = dynamic_cast<WearStock *>(it);
					if (wear) {
						size_t amount = std::count_if(wear->getProducts().begin(), wear->getProducts().end(), 
							[](std::pair<std::string, std::vector<WearStock::StockWearValue>> pair)	{
								return std::find_if(pair.second.begin(), pair.second.end(),
									[](WearStock::StockWearValue value)	{
										return value.getSizeSize() < 40;
									}
								) != pair.second.end();
							}
						);
						if (amount > 0) {
							temp.push_back(it);
						}
					} else {
						ShoeStock *shoe = dynamic_cast<ShoeStock *>(it);
						size_t amount = std::count_if(shoe->getProducts().begin(), shoe->getProducts().end(),
							[](std::pair<std::string, std::vector<ShoeStock::StockShoeValue>> pair)	{
								return std::find_if(pair.second.begin(), pair.second.end(),
									[](ShoeStock::StockShoeValue value)	{
										return value.getSizeSize() < 36;
									}
								) != pair.second.end();
							}
						);
						if (amount > 0) {
							temp.push_back(it);
						}
					}
				}
				std::cout << " Enter file name with .txt\n>> ";
				getline(std::cin, newfile);
				DataBase ndbb(newfile);

				if (temp.empty()) {
					std::cout << "	<<No such Stock!>>" << std::endl;
				}
				else {
					for (const auto &it : temp) {
						ndbb.save(it);
					}
				}
			}
			else {
				std::cout << "	<<Error Opening File!>>" << std::endl;
			}
		}
		else if (answer == "high")
		{
			DataBase db(dbname);
			std::ifstream inFile;
			inFile.open(dbname);
			if (!inFile.fail()) {
				std::vector<Stock*> temp;
				std::vector<Stock*> v = db.getData();

				for (auto &it : v) {
					WearStock *wear = dynamic_cast<WearStock *>(it);
					if (wear) {
						size_t amount = std::count_if(wear->getProducts().begin(), wear->getProducts().end(),
							[](std::pair<std::string, std::vector<WearStock::StockWearValue>> pair) {
							return std::find_if(pair.second.begin(), pair.second.end(),
								[](WearStock::StockWearValue value)	{
										return value.getSizeSize() > 50;
									}
								) != pair.second.end();
							}
						);
						if (amount > 0) {
							temp.push_back(it);
						}
					}
					else {
						ShoeStock *shoe = dynamic_cast<ShoeStock *>(it);
						size_t amount = std::count_if(shoe->getProducts().begin(), shoe->getProducts().end(),
							[](std::pair<std::string, std::vector<ShoeStock::StockShoeValue>> pair)	{
								return std::find_if(pair.second.begin(), pair.second.end(),
									[](ShoeStock::StockShoeValue value)
									{
										return value.getSizeSize() > 45;
									}
								) != pair.second.end();
							}
						);
						if (amount > 0) {
							temp.push_back(it);
						}
					}
				}
				std::cout << " Enter file name with .txt\n>> ";
				getline(std::cin, newfile);
				DataBase ndbb(newfile);

				if (temp.empty()) {
					std::cout << "	<<No such Stock!>>" << std::endl;
				}
				else {
					for (const auto &it : temp) {
						ndbb.save(it);
					}
				}
			}
			else {
				std::cout << "	<<Error Opening File!>>" << std::endl;
			}
		}
		else
			std::cout << "	<<Sorry, wrong choice!>>" << std::endl;
	}
	else
		std::cout << "	<<There is no such choice!>>" << std::endl;
}

void how()
{
	std::cout << "\tThe stocks are saving in .txt file as:\n\t<STOCK_TYPE>{<NAME>;<CITY>;<MAX_QTY>;<TYPE_1>=<SIZE_1>/<HEIGHT>(only if Wear)/<QTY>,<SIZE_2/...;<TYPE_n>=...}" << std::endl;
}

bool isInDir(std::string fileName)
{
	std::string path;
	for (fs::recursive_directory_iterator i(path), end; i != end; i++)
	{
		if (!fs::is_directory(i->path()) && i->path().extension() == ".txt")
		{
			if (i->path().filename().string() == fileName)
				return true;
		}
	}
	return false;
}

void starter()
{
	std::string answer;
	std::cout << "		Hello User! I am a DB redactor! Type \"help\" to see list of comands!" << std::endl;
	while (true)
	{
		std::cout << std::endl << ">> ";
		getline(std::cin, answer);
		if (answer != "") {
			std::vector<std::string> comand = split(answer, ' ');
			comand.resize(2);
			std::transform(comand[0].begin(), comand[0].end(), comand[0].begin(), (int(*)(int))std::tolower);

			if (comand[0] == "help" || comand[0] + " " == "help ") {
				help();
			}
			else if (comand[0] == "create" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				createDB(comand[1]);
			}
			else if (comand[0] == "list" || comand[0] + " " == "list ") {
				showList();
			}
			else if (comand[0] == "edit" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				editDB(comand[1]);
			}
			else if (comand[0] == "view" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				view(comand[1]);
			}
			else if (comand[0] == "search" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				searchForName(comand[1]);
			}
			else if (comand[0] == "count" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				countElem(comand[1]);
			}
			else if (comand[0] == "sort" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				sortDB(comand[1]);
			}
			else if (comand[0] == "delete" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				removeDB(comand[1]);
			}
			else if (comand[0] == "pick" && comand.size() == 2) {
				if (!isInDir(comand[1])) {
					std::cout << "	<<FILE NOT FOUND!>>" << std::endl;
					continue;
				}
				pickDB(comand[1]);
			}
			else if (comand[0] == "how" || comand[0] + " " == "how ")
				how();
			else if (comand[0] == "exit" || comand[0] + " " == "exit ")
				break;
			else
				std::cout << "	<<Sorry, there are no such comand!>>" << std::endl;
		}
		else {
			std::cout << "	<<Please enter some comand!>>" << std::endl;
		}
	}
}

int main()
{
	starter();
	std::cout << "	Good bye! Thanks for using me!" << std::endl;
	system("Pause");
	return 0;
}