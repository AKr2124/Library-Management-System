#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Book {
public:
    char name[30];
    char author[30];
    int id;
    Book *next;

    Book(const char *n, const char *a, int i) {
        strcpy(name, n);
        strcpy(author, a);
        id = i;
        next = nullptr;
    }
};

class Student {
public:
    char name[30];
    char email[20];
    char book[20];
    char author[30];
    int id;
    Student *next;

    Student(const char *n, const char *e, const char *b, const char *a, int i) {
        strcpy(name, n);
        strcpy(email, e);
        strcpy(book, b);
        strcpy(author, a);
        id = i;
        next = nullptr;
    }
};

class Library {
private:
    Book *start_lib;
    Student *start;

public:
    Library() : start_lib(nullptr), start(nullptr) {}

    void initialize_lib();
    void greetings();
    void main_menu();
    void book_issue();
    void book_return();
    void display_students();
    void add_book(const char *, const char *, int);
    void delete_book(int);
};

void Library::initialize_lib() {
    start_lib = new Book("The Kite Runner", "Khaled Hosseini", 101);
    Book *ptr = start_lib;

    ptr->next = new Book("To Kill A Mockingbird", "Harper Lee", 102);
    ptr = ptr->next;

    ptr->next = new Book("The Alchemist", "Paulo Coelho", 103);
    ptr = ptr->next;

    ptr->next = new Book("Pride And Prejudice", "Jane Austen", 104);
    ptr = ptr->next;

    ptr->next = new Book("A Tale Of Two Cities", "Charles Dickens", 105);
}

void Library::greetings() {
    cout << "\n\n";
    cout << "\t\t\t     ****************************************\n";
    cout << "\t\t\t     *                                      *\n";
    cout << "\t\t\t     *     WELCOME TO STUDENT LIBRARY       *\n";
    cout << "\t\t\t     *                                      *\n";
    cout << "\t\t\t     ****************************************\n";
    cout << "\n\n\t\t\t     Press any key to continue: ";
    cin.get();
}

void Library::main_menu() {
    int choice;
    do {
        cout << "\n\n";
        cout << "\n\t\t\t*************************************************\n";
        cout << "\n\t\t\t\t      MAIN MENU: ";
        cout << "\n\t\t\t\t     1. ISSUE OF BOOKS ";
        cout << "\n\t\t\t\t     2. RETURN OF BOOKS ";
        cout << "\n\t\t\t\t     3. DISPLAY STUDENT DETAILS ";
        cout << "\n\t\t\t\t     4. EXIT\n ";
        cout << "\n\t\t\t*************************************************\n";
        cout << "\n\t\t\t\t      Enter your choice: ";
        cin >> choice;
        cin.ignore();  // consume newline character left by cin

        switch (choice) {
            case 1:
                book_issue();
                break;
            case 2:
                book_return();
                break;
            case 3:
                display_students();
                break;
            case 4:
                exit(0);
            default:
                cout << "\n\t\t\t\t      ...Invalid Option!...\n";
                cout << "\n\t\t\t\t      Press any key to try again: ";
                cin.get();
        }
    } while (choice != 4);
}

void Library::book_issue() {
    Book *ptr;
    Student *ptr2, *new_student;
    int i = 1, id, flag = 0;

    if (start_lib == nullptr) {
        cout << "\n\t\t\t\t No books left in the library to issue!\n\t\t\t\t Sorry for the inconvenience!\n";
    } else {
        ptr = start_lib;
        cout << "\n\t*************** Books Available: ****************\n";
        while (ptr != nullptr) {
            cout << "\n\t_________________________________________________\n";
            cout << "\n\t Book " << i;
            cout << "\n\t Book Title: " << ptr->name;
            cout << "\n\t Name of Author: " << ptr->author;
            cout << "\n\t Book ID: " << ptr->id;
            cout << "\n\t_________________________________________________\n";
            ptr = ptr->next;
            i++;
        }
        cout << "\n\n\t Enter the Book ID: ";
        cin >> id;
        cin.ignore();  // consume newline character left by cin

        ptr = start_lib;
        while (ptr != nullptr) {
            if (ptr->id == id) {
                flag = 1;
                break;
            }
            ptr = ptr->next;
        }

        if (flag == 1) {
            ptr = start_lib;
            while (ptr->id != id) {
                ptr = ptr->next;
            }
            char student_name[30], student_email[20];
            cout << "\n\t Enter Student Details:\n ";
            cout << "\n\t Enter your Name: ";
            cin.getline(student_name, 30);
            cout << "\n\t Enter your Email: ";
            cin.getline(student_email, 20);
            new_student = new Student(student_name, student_email, ptr->name, ptr->author, ptr->id);
            cout << "\n\t Issue of Book ID " << new_student->id << " done successfully!\n";
            if (start == nullptr) {
                start = new_student;
            } else {
                ptr2 = start;
                while (ptr2->next != nullptr) {
                    ptr2 = ptr2->next;
                }
                ptr2->next = new_student;
            }
            delete_book(new_student->id);
        } else {
            cout << "\n\t\t      ...Invalid Option!...\n";
        }
    }
    cout << "\n\n\t Press any key to go to the main menu: ";
    cin.get();
}

void Library::book_return() {
    Student *ptr, *preptr;
    char bookname[30], authorname[30];
    int id, identity, flag = 0;

    cout << "\n\n\t*************** Books Submission: ****************\n";
    cout << "\n\n\t Enter your Book ID: ";
    cin >> identity;
    cin.ignore();  // consume newline character left by cin

    ptr = start;
    while (ptr != nullptr) {
        if (ptr->id == identity) {
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }

    if (flag == 1) {
        ptr = start;
        if (start->id == identity) {
            cout << "\n\t_________________________________________________\n";
            cout << "\n\t Student Name: " << start->name;
            cout << "\n\t Student Email: " << start->email;
            cout << "\n\t Name of Book Issued: " << start->book;
            cout << "\n\t_________________________________________________\n";
            strcpy(bookname, start->book);
            strcpy(authorname, start->author);
            id = start->id;
            start = start->next;
            delete ptr;
            add_book(bookname, authorname, id);
        } else {
            while (ptr->id != identity) {
                preptr = ptr;
                ptr = ptr->next;
            }
            cout << "\n\t_________________________________________________\n";
            cout << "\n\t Student Name: " << ptr->name;
            cout << "\n\t Student Email: " << ptr->email;
            cout << "\n\t Name of Book Issued: " << ptr->book;
            cout << "\n\t Book ID: " << ptr->id;
            cout << "\n\t_________________________________________________\n";
            strcpy(bookname, ptr->book);
            strcpy(authorname, ptr->author);
            id = ptr->id;
            preptr->next = ptr->next;
            delete ptr;
            add_book(bookname, authorname, id);
        }
        cout << "\n\t Return of Book ID " << id << " done successfully!\n";
        cout << "\n\t Thank you! Do visit again!\n";
    } else {
        cout << "\n\tSorry, the book doesn't exist! Please recheck the entered ID.\n";
    }

    cout << "\n\n\t Press any key to go to the main menu: ";
    cin.get();
}

void Library::display_students() {
    Student *ptr = start;

    while (ptr != nullptr) {
        cout << "\n\t************* Details of Students: **************\n";
        cout << "\n\t_________________________________________________\n";
        cout << "\n\t\t Student Name: " << ptr->name;
        cout << "\n\t\t Student Email: " << ptr->email;
        cout << "\n\t\t Name of Book Issued: " << ptr->book;
        cout << "\n\t\t Book ID: " << ptr->id;
        cout << "\n\t_________________________________________________\n";
        ptr = ptr->next;
    }

    cout << "\n\n\t Press any key to go to the main menu: ";
    cin.get();
}

void Library::delete_book(int id) {
    Book *ptr, *preptr;

    if (start_lib->id == id) {
        ptr = start_lib;
        start_lib = start_lib->next;
        delete ptr;
    } else {
        ptr = start_lib;
        while (ptr->id != id) {
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = ptr->next;
        delete ptr;
    }
}

void Library::add_book(const char *bookname, const char *authorname, int id) {
    Book *ptr, *new_book;

    new_book = new Book(bookname, authorname, id);

    if (start_lib == nullptr) {
        start_lib = new_book;
    } else {
        ptr = start_lib;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = new_book;
    }
}

int main() {
    Library lib;
    lib.initialize_lib();
    lib.greetings();
    lib.main_menu();
    return 0;
}