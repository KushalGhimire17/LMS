#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //string stream
#include <vector>

using namespace std;

class Book
{
private:
    int id;
    string title;
    string author;

public:
    Book(){}
    Book(int i, string t, string a):id(i), title(t), author(a){}

    int get_id() const
    {
        return this->id;
    }
    string get_title() const
    {
        return this->title;
    }
    string get_author() const
    {
        return this->author;
    }
    void set_title(string title)
    {
        title = title;
    }
    void set_author(string title)
    {
        author = author;
    }
    string to_string()
    {
        stringstream ss;
        ss << id <<", " <<title <<", "<<author;
        return ss.str();
    }

    static Book from_string(const string& str)
    {
        stringstream ss(str);
        string item;
        vector<string>items;

        while(getline(ss, item, ','))
        {
            items.push_back(item);
        }
        return Book(stoi(items[0]), items[1], items[2]);
    }
};

class Library
{
private:
    string filename;

public:
    Library(string filename) : filename(filename) {}

    void addBook(Book& book)
    {
        ofstream file;
        file.open(filename, ios::app);

        if(file.is_open())
        {
            file << book.to_string()<<endl;
            file.close();
        }
        else
        {
            cerr<<"\nUnable to open file"<<endl;
        }
    }

    vector<Book> getBooks()
    {
        vector<Book> books;
        ifstream file(filename);
        string line;

        if(file.is_open())
        {
            while(getline(file, line))
            {
                books.push_back(Book::from_string(line));
            }
            file.close();
        }
        else
        {
            cerr<<"\nUnable to open file"<<endl;
        }

        return books;
    }

    void updateBook(int id, string& new_title, string& new_author)
    {
        vector<Book> books = getBooks();
        ofstream file(filename);

        if(file.is_open())
        {
            for(auto &book : books)
            {
                if(book.get_id() == id)
                {
                    book.set_title(new_title);
                    book.set_author(new_author);
                }
                file <<book.to_string()<<endl;
            }
            file.close();
        }
        else
        {
            cerr<<"\nUnable to open file"<<endl;
        }
    }

    void deleteBook(int id)
    {
        vector<Book> books = getBooks();
        ofstream file(filename);

        if(file.is_open())
        {
            for(auto &book : books)
            {
                if(book.get_id() != id)
                {
                    file << book.to_string()<<endl;
                }
            }
            file.close();
        }
        else
        {
            cerr << "\nUnable to open"<<endl;
        }
    }
};

void displayMenu()
{
    cout<<"\n Library Management System"<<endl;
    cout <<" 1. Add Book"<<endl;
    cout <<" 2. View Book"<<endl;
    cout <<" 3. Update Book"<<endl;
    cout <<" 4. Delete Book"<<endl;
    cout <<" 5. Exit"<<endl;
}
int main()
{
    int choice;
    Library library("library.text");

    while(true)
    {
        displayMenu();
        cin>>choice;

        switch(choice)
        {
        case 1:{
            int id;
            string title, author;

            cout<<"\nEnter book ID: ";
            cin>>id;
            cin.ignore();
            cout<<"\nEnter book title: ";
            getline(cin, title);
            cout<<"\nEnter book author: ";
            getline(cin, author);
            Book b(id, title, author);
            library.addBook(b);
            break;}
        case 2:{
            vector<Book> books = library.getBooks();
            for(const auto &book : books)
            {
                cout<<"ID: "<<book.get_id() <<", Title: "<<book.get_title()<<", Author: "<<book.get_author()<<endl;
            }
            break;}
        case 3:{
            int id;
            string title, author;

            cout<<"\nEnter book id to update: ";
            cin>>id;

            cout<<"\nEnter new book title: ";
            getline(cin, title);
            cout<<"\nEnter new book author: ";
            getline(cin, author);
            library.updateBook(id, title, author);
            break;}
        case 4:{
            int id;

            cout<<"\nEnter book id to delete: ";
            cin>>id;
            library.deleteBook(id);
            break;}
        case 5:{
            return 0;}
        default:
            cout<<"\nInvalid Choice"<<endl;
        }
    }


    return 0;
}
