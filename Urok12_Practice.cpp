#include <iostream>
using namespace std;
class String
{
protected:
	//Строка
	char* string;
	//Размер строки
	int size;
public:
	//Конструктор без параметров
	String()
	{
		cout << "String Constructor: " << this << endl;
		this->string = nullptr;
		this->size = 0;
	}
	//Конструктор с параметрами
	String(const char* string)
		:string{ string ? new char[strlen(string) + 1] : nullptr }
	{
		cout << "String Constructor: " << this << endl;
		if (string)
			strcpy_s(this->string, strlen(string)+1, string);
		this->size = strlen(string) + 1;
	}
	//Конструктор копирования
	String(const String& other)
	{
		cout << "Copy Constructor: " << this << endl;
 		string = new char[strlen(other.string) + 1];
		strcpy_s(string, other.size, other.string);
		this->size = other.size;
	}
	//Конструктор присваивания
	String& operator=(const String& other)
	{
		cout << "Equal Constructor: " << this << endl;
		string = new char[strlen(other.string) + 1];
		strcpy_s(string, other.size, other.string);
		this->size = other.size;
		return *this;
	}
	//Получение длины строки
	int getSize()const
	{
		return size;
	}
	//get функция для строки
	const char* getString()const
	{
		return string;
	}
	//Очистка строки(сделать строку пустой)
	void clear()
	{
		delete[] string;
		size = 0;
	}
	//Деструктор
	~String()
	{
		cout << "Destructor String: " << this << endl;
		clear();
	}
	//Конкатация строк(+=)
	String operator+=(std::string other)
	{
		int k = 0;
		this->size += other.length();
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
		{
			if (i >= size - other.length()-1 && i < size)
				temp[i] = other[k++];
			else
				temp[i] = string[i];
		}
		delete[] string;
		string = new char[size];
		for (int i = 0; i < size; i++)
		{
			string[i] = temp[i];
		}
		return *this;
	}
	friend String operator+(const String& str1, const String& str2);
};
//Конкатация строк(+)
String operator+(const String& str1, const String& str2)
{
	String temp;
	temp.string = new char[strlen(str1.string) + strlen(str2.string) + 1];
	temp.size = strlen(str1.string) + strlen(str2.string) + 1;
	for (int i = 0; i < temp.size; i++)
	{
		if (i < strlen(str1.string))
		{
			temp.string[i] = str1.string[i];
		}
		else
		{
			temp.string[i] = str2.string[i-strlen(str1.string)];
		}
	}
	return temp;
}
//operator==
bool operator==(const String& str1, const String& str2)
{
	return str1.getString() == str2.getString();
}
//operator!=
bool operator!=(const String& str1, const String& str2)
{
	return str1.getString() != str2.getString();
}

//Класс Битовая строка
class ByteString : public String
{
public:
	//Конструктор без параметров
	ByteString() :String()
	{
		cout << "Byte String Constructor: " << this << endl;
	}
	//Конструктор с параметрами
	ByteString(const char* string) : String(string)
	{
		cout << "Byte String Constructor: " << this << endl;
		for (int i = 0; i < size; i++)
		{
			if (this->string[i] != 0 || this->string[i] != 1)
			{
				break;
			}
		}
	}

	~ByteString()
	{
		cout << "Byte String Destructor: " << this << endl;
	}

};

int main()
{
	String str1("Marshall");
	cout << "Str1: " << str1.getString() << "\t";
	cout << "Str1 is size: " << str1.getSize() << endl << endl;
	String str2("Mathers");
	cout << "Str2: " << str2.getString() << "\t";
	cout << "Str2 is size: " << str2.getSize() << endl << endl;

	String str3(str1);
	cout << "Str3: " << str3.getString() << "\t";
	cout << "Str3 is size: " << str3.getSize() << endl << endl;

	str3 = str2;
	cout << "Str3: " << str3.getString() << "\t";
	cout << "Str3 is size: " << str3.getSize() << endl << endl;

	str3 += " hello!";
	cout << "Str3: " << str3.getString() << "\t";
	cout << "Str3 is size: " << str3.getSize() << endl << endl;

	String str4 = str1 + str2;
	cout << "Str4: " << str4.getString() << "\t";
	cout << "Str4 is size: " << str4.getSize() << endl << endl;
	
	if (str1 != str2)
		cout << "They are not equal!\n";
	else
		cout << "They are equal\n";

	if (str1 == str1)
		cout << "They are equal!\n";
	else
		cout << "They are not equal\n";

	ByteString byteString("0101001");
	cout << "Byte String: " << byteString.getString() << "\t";
	cout << "Byte String size is: " << byteString.getSize() << endl << endl;

	return 0;
}