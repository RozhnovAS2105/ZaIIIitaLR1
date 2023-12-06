#include <iostream>
#include <string>
#include <fstream>
#include <locale>

using namespace std;

struct file_shifr
{
    string inputfile, outputfile;
    string key;
};

/*Это шаблонная функция correctnumber, которая запрашивает у пользователя ввод числа в заданном диапазоне.
В случае ошибки ввода она выводит сообщение об ошибке и запрашивает ввод повторно.*/
//кайф шаблонной функцию - ее гибкость. работа с разными типами данных
template <typename T>
T correctnumber(T min, T max) 
{
    T x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < min) || (x > max)) 
    {
        cout << "Ошибка! Введите корректное число: >= " << min << " и =< " << max << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}

void Shifr(file_shifr f, int x)
{
    //k - символ ключа, n - итоговый символ, symbol - символ из входного файла
    char symbol;
    int keyi = 0;
    unsigned char n;
    unsigned char k;

    cout << "\nВведите название файла для ввода" << endl;
    cin >> f.inputfile;
    cout << "Введите название файла для вывода" << endl;
    cin >> f.outputfile;
    cout << "Введите ключ для кодирования" << endl;
    //cin >> f.key;
    cin.ignore();
    getline(cin, f.key);

    ifstream in; //поток чтения из файла
    ofstream out; //поток для записи в файл
    //бинарный режим помогает корректно обрабатывать текст, предотвращая искажения в тексте.
    in.open(f.inputfile + ".txt", ios::binary);
    out.open(f.outputfile + ".txt", ios::binary);

    if ((!in.is_open()) || (!out.is_open()))
    {
        cout << "\nОшибка! \nПроверьте существование файла с таким названием." << endl;
    }

    while (in.get(symbol))
    {
        // Получение символа ключа для текущего символа из файла
        k = f.key[keyi % f.key.size()];
        if (x == 1) {
            n = symbol + k;
        }

        else
            n = symbol - k;

        keyi += 1;
        out.put(n);

    }

    cout << "\nТекст успешно преобразован";
    in.close();
    out.close();
}

/*Создаем объект 'file_shifr' и входим в цикл, предлагая пользователю выбрать команду.
В зависимости от выбора вызывается функция 'Shifr' для шифрования(при x = 1), дешифрования(x = 2)
ну и конечно же завершение программы*/
int main()
{
    locale::global(locale(""));
    file_shifr f;
    int option = -1;
    while (option)
    {
        cout << "\nЧто Вы хотите сделать?\n1.Зашифровать текст 2. Расшифровать текст 0.Выход" << endl;
        option = correctnumber(0, 2);
        switch (option)
        {
        case 1:
        {
            Shifr(f, 1);
            break;
        }
        case 2:
        {
            Shifr(f, 2);
            break;
        }
        case 0:
        {
            return 0;
        }
        default: cout << "Введите корректный номер (0-2)";
            break;
        }

    }

}
