#include "main.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) // Функция деления строки по параметру
{
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)){
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)// Функция деления строки по параметру
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::vector<std::string> split(std::string s, std::string delimiter) { // Функция деления строки по параметру
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

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {// Функция замены строки на параметр
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

void removeDB(std::string dbname) //удаления текстового файла
{
	
	if (remove(dbname.c_str()) != 0)  //удаляем
		std::cout << "	<<Error of deleting file!>>"; //не смогли
	else 
		std::cout << "	<<File is successfully removed!>>"; //смогли
}

void help() //меню помощь
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

void createDB(std::string dbname) //создание текстового файла по названию
{
	DataBase db(dbname); //инициализируем
	db.save(); //сохраняем
}

void showList() //выводим список баз данных
{
	std::cout << "\tExisted DB: \n\n";
	std::string path;
	for (fs::recursive_directory_iterator i(path), end; i != end; i++){ //смотрим в дирректории 
		if (!fs::is_directory(i->path()) && i->path().extension() == ".txt"){	//если в дирректории и есть формат .txt	
			std::cout << "\t" << i->path().filename().string() << "\n"; //выводим название файла 
		}
	}
}
 
void editDB(std::string dbname) //функция изменения базы данных
{
	std::cout << "\tYOU OPENED THE \"" << dbname << "\"" << "\n\tTO SEE DB - open\n\tTO ADD SOME ELEMENTS - add\n\tTO REMOVE ELEMENTS remove" << std::endl <<  ">> ";
	std::string fans;
	std::string ans;
	std::string answer;
	bool contin = true;
	std::string city; 
	std::string name; 
	int qty = 0; 
	int size = 0; 
	int height = 0; 
	int count = 0; 
	std::string type;
	int qtyOfElem = 0; 
	int qtyOfSizes = 0;
	getline(std::cin, fans);
	
	if (fans == "open") //открываем
	{
		std::string x;
		std::ifstream inFile;

		inFile.open(dbname); //открываем файл
		if (!inFile) { //не смогли открыть 
			std::cout << "\t<<Unable to open file!>>\n";
		}

		while (inFile >> x) { //пока файл не окончен
			std::cout << x << std::endl; //выводим содержание
		} 

		inFile.close(); //закрываем
	}
	else if (fans == "add") //добавляем
	{
		while (contin) 
		{
			while (true) { 
				std::cout << "\tWhat kind of stock you want? If Shoes - type shoe, if Wear - type wear!" << std::endl << ">> ";

				getline(std::cin, ans);

				if (ans == "wear")
				{
					try
					{
						//заполняем основные параметры
						std::cout << " Enter name of stock: "; getline(std::cin, name);
						std::cout << " Enter the city: "; getline(std::cin, city);
						std::cout << " Enter the max stock size: ";
						if (!(std::cin >> qty))
							throw std::exception("\t<<Input error, only integers allow!>>");

						WearStock* a = new WearStock(name, city, qty); //объявляем атрибуд инициализировав через конструктор
						std::cout << " Enter qty of different products: ";
						if (!(std::cin >> qtyOfElem))
							throw std::exception("\t<<Input error, only integers allow!>>");

						//через цикл заполняем типы продуктов и количество размеров для них
						for (int i = 0; i < qtyOfElem; i++) {
							std::vector<WearStock::StockWearValue> sizes;
							std::cin.ignore();

							std::cout << " Enter the type of product: "; getline(std::cin, type);
							std::cout << " Enter qty of different sizes: ";
							if (!(std::cin >> qtyOfSizes))
								throw std::exception("\t<<Input error, only integers allow!>>");
							//через цикл заполняем размеры
							for (int j = 0; j < qtyOfSizes; j++)
							{
								std::cout << "	ENTER SIZES FOR " << type << " FOR " << j + 1 << " SIZETYPE!" << std::endl;
								std::cout << " Enter size: ";
								std::cin >> size;
								if (!(std::cin >> size))
									throw std::exception("\t<<Input error, only integers allow!>>");
								std::cout << " Enter height: ";
								std::cin >> height;
								if (!(std::cin >> height))
									throw std::exception("\t<<Input error, only integers allow!>>");
								std::cout << " Enter count: ";
								std::cin >> count;
								if (!(std::cin >> count))
									throw std::exception("\t<<Input error, only integers allow!>>");

								//добавляем в вектор размеров, используя конструктор размеров 
								sizes.push_back(WearStock::StockWearValue(size, height, count));
							}
							//пытаемся добавить размеры для склада 
							bool isSuccess = a->addwear(type, sizes);

							if (!isSuccess) { //выводим сообщение, если добавить не смогли
								std::cout << "	<<Size of stock is not so big! If you want to add less things firstly remove existed empty one!>>" << std::endl;
							}
							//инициализируем бд
							DataBase db(dbname);
							//сохраняем по переданному складу 
							db.save(a);
						}

					}
					catch(std::exception& ex)
					{
						std::cout << "Error: " << ex.what() << std::endl;
						std::cin.clear();
						while (std::cin.get() != '\n');
					}
					break;

				}
				else if (ans == "shoe") //аналогично как с wear
				{
					try {
						std::cout << " Enter name of stock: "; getline(std::cin, name);
						std::cout << " Enter the city: "; getline(std::cin, city);
						std::cout << " Enter the max stock size: ";
						if (!(std::cin >> qty))
							throw std::exception("\t<<Input error, only integers allow!>>");
						
						ShoeStock* a = new ShoeStock(name, city, qty);
						std::cout << " Enter qty of different products: ";
						if (!(std::cin >> qtyOfElem))
							throw std::exception("\t<<Input error, only integers allow!>>");
						
						for (int i = 0; i < qtyOfElem; i++) {
							std::vector<ShoeStock::StockShoeValue> sizes;
							std::cin.ignore();
							std::cout << " Enter the type of product: "; getline(std::cin, type);
							std::cout << " Enter qty of different sizes: ";
							if (!(std::cin >> qtyOfSizes))
								throw std::exception("\t<<Input error, only integers allow!>>");

							for (int j = 0; j < qtyOfSizes; j++)
							{
								std::cout << "	ENTER SIZES FOR " << type << " FOR " << j + 1 << " SIZETYPE!" << std::endl;
								std::cout << " Enter size: ";
								if (!(std::cin >> size))
									throw std::exception("\t<<Input error, only integers allow!>>");
								
								std::cout << " Enter count: ";
								if (!(std::cin >> count))
									throw std::exception("\t<<Input error, only integers allow!>>");
								
								sizes.push_back(ShoeStock::StockShoeValue(size, count));
							}
							bool isSuccess = a->addwear(type, sizes);
							if (!isSuccess) {
								std::cout << "\t<<Size of stock is not so big! If you want to add less things firstly remove existed empty one!>>" << std::endl;
							}

						}
						DataBase db(dbname);
						db.save(a);
					}
					catch (std::exception& ex)
					{
						std::cout << "Error: " << ex.what() << std::endl;
						std::cin.clear();
						while (std::cin.get() != '\n');
					}
					
					break;
				}
				else // выводим сообщение, если пользователь ошибся командой
					std::cout << "\t<<There are no such a answer, choose from fallowing!>>" << std::endl;
			}
			while (true) { // спрашиваем хочет ли он продолжить?
				std::cout << "\tWant to add more? |y/n|" << std::endl << ">> ";
				//std::cin.ignore();
				//getline(std::cin, answer);
				std::cin >> answer;
				if (answer == "n") {
					contin = false;
					std::cin.ignore();
					break;
				}
				else if (answer == "y") {
					contin = true;
					std::cin.ignore();
					break;
				}
				else
					std::cout << "\t<<Incorrect answer! Type |y| or |n| !>>" << std::endl;
			}

		}		
	}
	else if (fans == "remove")
	{
		//содержание
		std::string x;
		std::ifstream inFile;
		
		inFile.open(dbname);
		if (!inFile) {
			std::cout << "\t<<Unable to open file>>";
		}
		
		int iter = 1;
		while (inFile >> x) {
			std::cout << " " << iter << "  " << x << std::endl;
			iter++;
		}
		
		inFile.close();

		//удаление

		std::ifstream file_in;

		file_in.open(dbname);

		if (file_in.peek() == std::ifstream::traits_type::eof()) {
			std::cout << "\t<<File is emty!>>\n" << std::endl;
			file_in.close();
		}
		else 
		{
			if (!file_in) // Проверяем, открылся ли файл
			{
				std::cout << "\t<<Sorry, the file can't be opened!>>" << std::endl;
			}
			try {
				std::cout << "\tEnter string number: " << std::endl << ">> ";
				int i_number_line_delete = 0;
				if (!(std::cin >> i_number_line_delete))
					throw std::exception("\t<<Input error, only integers allow!>>");
				
				std::cin.ignore();
				if (i_number_line_delete < iter) //если наша страка меньше существующих
				{
					int i_number_line_now = 0;
					std::string line;
					std::string line_file_text;
					while (getline(file_in, line)) //бегаем по строкам
					{
						i_number_line_now++;
						if (!(i_number_line_now == i_number_line_delete)) //если не нашли то переключаемся по строкам
						{
							line_file_text.insert(line_file_text.size(), line);
							line_file_text.insert(line_file_text.size(), "\r\n");
						}
					}
					file_in.close(); //закрываем
					std::ofstream file_out;
					file_out.open(dbname, std::ios::trunc | std::ios::binary); //открываем
					file_out.write(line_file_text.c_str(), line_file_text.size()); //перезаписываем
					file_out.clear();
				}
				else
				{
					std::cout << "\t<<Sorry, this string isn't exists!>>\n";
					file_in.close();
				}
			}
			catch(std::exception& ex)
			{
				std::cout << "Error: " << ex.what() << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			}

		}
	}
	else if (fans == "exit")
	{
		std::cout << "\tYou exited...\n";
	}
	else
	std::cout << "	<<There no such comand!>>" << std::endl;

}

void view(std::string dbname) //смотрим содержание
{
	DataBase db(dbname); //инициализируем бд
	auto v = db.getData(); //в вектор получаем содержимое бд
	for (auto pointer : v) {
		WearStock *wear = dynamic_cast<WearStock *>(pointer);//пытаемся привести к одному типу
		if (wear) {// смогли?
			std::cout << *wear << std::endl; //выводим
		}
		else {//нет?
			ShoeStock *wear = dynamic_cast<ShoeStock *>(pointer); //приводим к другому
			std::cout << *wear << std::endl; //выводим
		}
	}
}

void searchForName(std::string dbname) //поиск в бд по Названию
{
	std::string answer;
	std::cout << "\t\tYOU SEARCH IN " << dbname << std::endl;
	DataBase db(dbname);

	std::cout << "\tEnter the name of stock you want to find: " << std::endl << ">> ";
	getline(std::cin, answer);
	std::vector<Stock*> res = db.search(answer); //ищем
	for (auto i = 0; i < res.size(); i++)
	{
		if (res[i] != nullptr)
			std::cout << res[i]->toString() << std::endl; // выводим найденные
		else
			std::cout << "\t<<Not found!>>" << std::endl;
	}
}

void countElem(std::string dbname) //подсчет элементов
{
	DataBase db(dbname);
	size_t res = db.countElements(); 
	std::cout << "\tThere are " << res << " elements in DB" << std::endl;
	auto v = db.getData();
	
	size_t amountWear = 0;
	size_t amountShoe = 0;

	for (auto pointer : v) { //ищем по вектору
		WearStock *wear = dynamic_cast<WearStock *>(pointer); //пытаемся преобразовать к типу
		if (wear) { //преобразовали?
			amountWear += pointer->amount(); //добавляем в счет
		} else { //нет?
			amountShoe += pointer->amount(); //значит в другой 
		}
	}

	std::cout << "\tQty of products in WearStock: " << amountWear << std::endl;
	std::cout << "\tQty of products in ShoeStock: " << amountShoe << std::endl;
}

void sortDB(std::string dbname) //сортируем
{
	try {
		int answer = 0;
		std::cout << "\tYou want to sort by alphabet(1) or Qty on Stock(2)?" << std::endl << ">> ";
		if (!(std::cin >> answer))
			throw std::exception("\t<<Input error, only integers allow!>>");
	

		std::cin.ignore();
		if (answer == 1) {
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
				std::cout << "\t<<Error Opening File!>>" << std::endl;
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
				std::cout << "\t<<Error Opening File!>>" << std::endl;
			}
		}
		else {
			std::cout << "\t<<You made a wrong choice!>>" << std::endl;
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}

void pickDB(std::string dbname)
{
	try {
		std::cout << "\tYou want to pick from city(1) or size(2)?" << std::endl << ">> ";
		int ans = 0;
		if (!(std::cin >> ans))
			throw std::exception("\t<<Input error, only integers allow!>>");

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
					if (it->getCity() == city)
					{
						temp.push_back(it);
					}
				}
				std::cout << " Enter file name with .txt" << std::endl << ">> ";
				while (!(newfile.find(".txt") != std::string::npos)) {

					getline(std::cin, newfile);
					if (!(newfile.find(".txt") != std::string::npos))
						std::cout << "\t<<Please enter DB name with .txt!>>\n";
				}
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
			std::cout << "\tYou want to pick \"low\" or \"high\" sizes?" << std::endl << ">> "; std::cin.ignore(); getline(std::cin, answer);
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
								[](std::pair<std::string, std::vector<WearStock::StockWearValue>> pair) {
								return std::find_if(pair.second.begin(), pair.second.end(),
									[](WearStock::StockWearValue value) {
									return value.getSizeSize() < 40;
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
								[](std::pair<std::string, std::vector<ShoeStock::StockShoeValue>> pair) {
								return std::find_if(pair.second.begin(), pair.second.end(),
									[](ShoeStock::StockShoeValue value) {
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
					std::cout << "\tEnter file name with .txt\n>> ";
					while (!(newfile.find(".txt") != std::string::npos)) {

						getline(std::cin, newfile);
						if (!(newfile.find(".txt") != std::string::npos))
							std::cout << "\t<<Please enter DB name with .txt!>>\n";
					}
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
					std::cout << "\t<<Error Opening File!>>" << std::endl;
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
									[](WearStock::StockWearValue value) {
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
								[](std::pair<std::string, std::vector<ShoeStock::StockShoeValue>> pair) {
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
					std::cout << "\tEnter file name with .txt\n>> ";

					while (!(newfile.find(".txt") != std::string::npos)) {

						getline(std::cin, newfile);
						if (!(newfile.find(".txt") != std::string::npos))
							std::cout << "\t<<Please enter DB name with .txt!>>\n";
					}
					DataBase ndbb(newfile);

					if (temp.empty()) {
						std::cout << "\t<<No such Stock!>>" << std::endl;
					}
					else {
						for (const auto &it : temp) {
							ndbb.save(it);
						}
					}
				}
				else {
					std::cout << "\t<<Error Opening File!>>" << std::endl;
				}
			}
			else
				std::cout << "\t<<Sorry, wrong choice!>>" << std::endl;
		}
		else
			std::cout << "\t<<There is no such choice!>>" << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
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
	std::cout << "\t\tHello User! I am a DB redactor! Type \"help\" to see list of comands!" << std::endl;
	while (true)
	{
		std::cout << std::endl << ">> ";
		getline(std::cin, answer);
		if (answer != "") {
			std::vector<std::string> comand = split(answer, ' ');
			if(comand.size() > 2)
				comand.resize(2);
			if (comand.size() == 2)
			{
				if (!(comand[1].find(".txt") != std::string::npos )) {
					std::cout << "\t<<Please enter DB name with .txt!>>\n";
					continue;
				}
			}
			std::transform(comand[0].begin(), comand[0].end(), comand[0].begin(), (int(*)(int))std::tolower);

			if (comand[0] == "help" || comand[0] + " " == "help ") {
				help();
			}
			else if (comand[0] == "create" && comand.size() == 2) {
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