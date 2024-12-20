#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;



class Book {
public:
	string name, author, genre;
	Book(string e_name, string e_author, string e_genre) {
		name = e_name;
		author = e_author;
		genre = e_genre;
	}
	virtual void displayInfo() {
		cout << "Название: " << name << endl;
		cout << "Автор: " << author << endl;
		cout << "Жанр: " << genre << endl;
	}
    void modify(string new_genre) {
        genre = new_genre;
    }
};

class Fiction : public Book {
public:
	Fiction(string e_name, string e_author, string e_genre) : Book(e_name, e_author, e_genre) {}
	void displayInfo() override {
		Book::displayInfo();
		cout << "Художественная " << endl;
	}
};

class NonFiction : public Book {
public:
	NonFiction(string e_name, string e_author, string e_genre) : Book(e_name, e_author, e_genre) {}
	void displayInfo() override {
		Book::displayInfo();
		cout << "Не художественная " << endl;
	}
};

template <typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;

public:
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    void display() const {
        cout << "Pair: (" << first << ", " << second << ")" << endl;
    }
};

vector<Book> library;

void addition() {
    string nothing, name1, auth1, genre1;
    int type;
    getline(cin, nothing);;
    getline(cin, name1);
    getline(cin, auth1);
    getline(cin, genre1);
    cout << "введите 1, если книга относиться к художественной литературе или 0, если не относится" << endl;
    cin >> type;
    if (type == 1) {
        Fiction newbook(name1, auth1, genre1);
        library.push_back(newbook);
    }
    else {
        NonFiction newbook(name1, auth1, genre1);
        library.push_back(newbook);
    }

}

void search() {
    string nothing;
    getline(cin, nothing);
    string lookforname;
    getline(cin, lookforname);
    cout << endl;
    int found = 0;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].name == lookforname) {
            library[i].displayInfo();
            found = 1;
        }
    }
    if (found == 0) {
        cout << "такой книги нет в библиотеке" << endl;
    }
}

void sortirovka() {
    sort(library.begin(), library.end(), [](const Book& a, const Book& b) {
        return a.author < b.author; });
}

void changing() {
    string nothing;
    getline(cin, nothing);
    string lookforname;
    getline(cin, lookforname);
    string newgenre;
    int found = 0;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].name == lookforname) {
            found=i;
        }
    }
    if (found == 0) {
        cout << "такой книги нет в библиотеке" << endl;
    }
    else {
        library[found].displayInfo();
        cout << "Выберите новый жанр" << endl;
        getline(cin, newgenre);
        library[found].modify(newgenre);
        library[found].displayInfo();
    }
}

void emmission() {
    for (int i = 0; i < library.size(); i++) {
        library[i].displayInfo();
        cout << endl;
    }
}

void saving(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка" << endl;
        return;
    }
    for (int i = 0; i < library.size(); i++) {
        outFile << library[i].name << " : " << library[i].author << " : " << library[i].genre << "\n";
    }
    outFile.close();
    cout << "библиотека сохранена в файл " << filename << endl;
}

int main()
{
    string nothing;
    Fiction ex("Имя Розы", "Умберто Эко", "детектив");
    NonFiction ex2("Страна Хатти","Александр Немировский","Исторический");
    library.push_back(ex);
    library.push_back(ex2);
    string lookforname;
    setlocale(LC_ALL, "");
    system("chcp 1251");
    ofstream f1("products.txt");
    f1.close();
    int action;
    do {
        cout << "1. Добавить книгу\n";
        cout << "2. Поиск книги\n";
        cout << "3. Сортировка книг по автору\n";
        cout << "4. Изменить жанр книги\n";
        cout << "5. Вывод\n";
        cout << "6. Сохранить в файл\n";
        cout << "0. Завершить программу\n";
        cout << endl;
        cout << "Выберите действие: ";
        cin >> action;
        switch (action) {
        case 1:
            addition();
            break;
        case 2:
            search();
            break;
        case 3:
            sortirovka();
            break;
        case 4:
            changing();
            break;
        case 5:
            emmission();
        case 6:
            saving("output.txt");
            break;
        case 0:
            cout << "Программа завершена.\n";
            break;
        default:
            cout << "Нет такого действия. Попробуйте снова.\n";
        }
    } while (action != 0);
    return 0;
}
