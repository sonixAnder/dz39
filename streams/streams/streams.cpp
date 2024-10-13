#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
//изначально нету файла "дериктория", её нужно будет создать через эту прогу
class Directory
{
private:
    string companyName;
    string owner;
    string phone;
    string address;
    string activity;

public:
    Directory() {}

    Directory(const string& companyName, const string& owner, const string& phone, const string& address, const string& activity) :
        companyName(companyName), owner(owner), phone(phone), address(address), activity(activity) {}

    string getCompanyName() const { return companyName; }
    string getOwner() const { return owner; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getActivity() const { return activity; }

    void display() const
    {
        cout << "Фирма: " << companyName << endl;
        cout << "Владелец: " << owner << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
        cout << "Активность: " << activity << endl;
        cout << "------------------------------" << endl;
    }
};

vector<Directory> loadFromFile(const string& filename)
{
    vector<Directory> directory;
    ifstream file(filename);

    if (file.is_open())
    {
        string companyName, owner, phone, address, activity;
        while (getline(file, companyName) &&
            getline(file, owner) &&
            getline(file, phone) &&
            getline(file, address) &&
            getline(file, activity)) {
            Directory entry(companyName, owner, phone, address, activity);
            directory.push_back(entry);
        }
        file.close();
    }
    return directory;
}

void saveToFile(const string& filename, const vector<Directory>& directory) {
    ofstream file(filename);

    if (file.is_open())
    {
        for (const auto& entry : directory)
        {
            file << entry.getCompanyName() << endl;
            file << entry.getOwner() << endl;
            file << entry.getPhone() << endl;
            file << entry.getAddress() << endl;
            file << entry.getActivity() << endl;
        }
        file.close();
    }
}

vector<Directory> searchByName(const vector<Directory>& directory, const string& name)
{
    vector<Directory> results;
    for (const auto& entry : directory)
    {
        if (entry.getCompanyName() == name)
        {
            results.push_back(entry);
        }
    }
    return results;
}

vector<Directory> searchByOwner(const vector<Directory>& directory, const string& owner)
{
    vector<Directory> results;
    for (const auto& entry : directory)
    {
        if (entry.getOwner() == owner)
        {
            results.push_back(entry);
        }
    }
    return results;
}

vector<Directory> searchByPhone(const vector<Directory>& directory, const string& phone)
{
    vector<Directory> results;
    for (const auto& entry : directory)
    {
        if (entry.getPhone() == phone)
        {
            results.push_back(entry);
        }
    }
    return results;
}

vector<Directory> searchByActivity(const vector<Directory>& directory, const string& activity)
{
    vector<Directory> results;
    for (const auto& entry : directory)
    {
        if (entry.getActivity() == activity)
        {
            results.push_back(entry);
        }
    }
    return results;
}

int main()
{
    setlocale(LC_ALL, "ru");
    vector<Directory> directory = loadFromFile("directory.txt");

    int choice;
    do
    {
        cout << "Меню:" << endl;
        cout << "1. Поиск по названию фирмы" << endl;
        cout << "2. Поиск по владельцу" << endl;
        cout << "3. Поиск по номеру телефона" << endl;
        cout << "4. Поиск по роду деятельности" << endl;
        cout << "5. Показать все записи" << endl;
        cout << "6. Добавить новую запись" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите цифру: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name;
            cout << "Введите имя фирмы: ";
            cin.ignore();
            getline(cin, name);
            vector<Directory> results = searchByName(directory, name);
            if (results.empty())
            {
                cout << "Записей не найдено." << endl;
            }
            else
            {
                for (const auto& entry : results)
                {
                    entry.display();
                }
            }
            break;
        }
        case 2:
        {
            string owner;
            cout << "Введите владельца: ";
            cin.ignore();
            getline(cin, owner);
            vector<Directory> results = searchByOwner(directory, owner);
            if (results.empty())
            {
                cout << "Записей не найдено." << endl;
            }
            else
            {
                for (const auto& entry : results)
                {
                    entry.display();
                }
            }
            break;
        }
        case 3:
        {
            string phone;
            cout << "Введите номер телефона: ";
            cin.ignore();
            getline(cin, phone);
            vector<Directory> results = searchByPhone(directory, phone);
            if (results.empty())
            {
                cout << "Записей не найдено." << endl;
            }
            else
            {
                for (const auto& entry : results)
                {
                    entry.display();
                }
            }
            break;
        }
        case 4:
        {
            string activity;
            cout << "Введите род деятельности: ";
            cin.ignore();
            getline(cin, activity);
            vector<Directory> results = searchByActivity(directory, activity);
            if (results.empty())
            {
                cout << "Записей не найдено." << endl;
            }
            else
            {
                for (const auto& entry : results)
                {
                    entry.display();
                }
            }
            break;
        }
        case 5:
        {
            if (directory.empty())
            {
                cout << "Справочник пустая." << endl;
            }
            else
            {
                for (const auto& entry : directory)
                {
                    entry.display();
                }
            }
            break;
        }
        case 6:
        {
            string companyName, owner, phone, address, activity;
            cout << "Введите название фирмы: ";
            cin.ignore();
            getline(cin, companyName);
            cout << "Введите имя владельца: ";
            getline(cin, owner);
            cout << "Введите номер телефона: ";
            getline(cin, phone);
            cout << "Введите адрес: ";
            getline(cin, address);
            cout << "Введите род деятельности: ";
            getline(cin, activity);
            Directory entry(companyName, owner, phone, address, activity);
            directory.push_back(entry);
            cout << "Запись добавлена." << endl;
            break;
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Ошибка." << endl;
        }
    } while (choice != 0);

    // Save data to a file
    saveToFile("directory.txt", directory);

    return 0;
}
