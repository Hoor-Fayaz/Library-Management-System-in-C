<b>Library Management System Documentation</b>
<br>
Overview
The Library Management System is a console-based application written in C. It allows users to add, list, remove, and issue books. Additionally, it maintains a record of issued books. The application uses structures, file handling, and standard input/output operations to manage the library's data.
Structures
struct books   This structure holds information about a book, including its ID, name, author, and date of addition.
struct student   This structure holds information about a student and the book they have issued, including the student's ID, name, class, roll number, the name of the book issued, and the date of issuance.
File Pointers
FILE *fp   A file pointer used for handling file operations such as reading from and writing to files. 2 files are used: books.txt (data of books stored in library) and issue.txt (data of issued books and student info).
Main Function
int main()
The main function contains an infinite loop that displays the main menu of the library management system. It prompts the user to select an option and calls the corresponding function based on the user's choice.
Menu Options
1.	Add Book: Calls the addBook function to add a new book to the library.
2.	Books List: Calls the booksList function to display all available books.
3.	Remove Book: Calls the del function to remove a book from the library.
4.	Issue Book: Calls the issueBook function to issue a book to a student.
5.	Issued Book List: Calls the issueList function to display all issued books.
6.	Search Book: Calls the searchBook function to search a book which user wants to search.
7.	Exit: Exits the application.
Functions
void addBook()
•	Purpose: Adds a new book to the library.
•	Process:
o	Gets the current date and stores it in the date field of the books structure.
o	Prompts the user to enter the book's ID, name, and author.
o	Writes the book information to the books.txt file.
void booksList()
•	Purpose: Displays a list of all available books.
•	Process:
o	Clears the console screen.
o	Reads book information from the books.txt file and prints it in a formatted manner.
void del()
•	Purpose: Removes a book from the library.
•	Process:
o	Prompts the user to enter the ID of the book to be removed.
o	Reads book information from the books.txt file and writes all records except the one with the matching ID to a temporary file.
o	Renames the temporary file to books.txt to reflect the deletion.
void issueBook()
•	Purpose: Issues a book to a student.
•	Process:
o	Gets the current date and stores it in the date field of the student structure.
o	Prompts the user to enter the book ID and checks if the book is available.
o	Prompts the user to enter the student's name, class, and roll number.
o	Writes the issued book information to the issue.txt file.
void issueList()
•	Purpose: Displays a list of all issued books.
•	Process:
o	Clears the console screen.
o	Reads issued book information from the issue.txt file and prints it in a formatted manner.
Conditions and Loops
•	Infinite Loop in main(): Continuously displays the main menu until the user chooses to exit.
•	File Operations:
o	fread() is used to read records from files.
o	fwrite() is used to write records to files.
o	remove() and rename() are used in the del function to update the books.txt file after a deletion.
Conclusion
This Library Management System demonstrates basic file handling, use of structures, and menu-driven programming in C. It provides a simple yet effective way to manage a small library, allowing for the addition, removal, and issuance of books, as well as maintaining records of issued books.
