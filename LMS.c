#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b, *library = NULL;

struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
} s;

FILE *fp;
int book_count = 0;
int library_size = 0;

void prepopulateBooks();
void addBook();
void booksList();
void del();
void issueBook();
void issueList();
void searchBook();
void updateBookIndices(int index);
void reallocateLibrary();

int main() {
    int choice;
    prepopulateBooks();

    while (1) {
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Add Book\n");
        printf("2. Books List\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. Issued Book List\n");
        printf("6. Search Book\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                exit(0);

            case 1:
                addBook();
                break;

            case 2:
                booksList();
                break;

            case 3:
                del();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                issueList();
                break;

            case 6:
                searchBook();
                break;

            default:
                printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}

void prepopulateBooks() {
    FILE *file = fopen("book.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (book_count >= library_size) {
            reallocateLibrary();
        }
        sscanf(line, "%d,%49[^,],%49[^\n]", &library[book_count].id, library[book_count].bookName, library[book_count].authorName);

        // Set the current date as the book addition date
        time_t t= time(NULL);
        struct tm tm = *localtime(&t);
        char myDate[12];
        sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        strcpy(library[book_count].date, myDate);

        book_count++; 
    }

    fclose(file);
}

void reallocateLibrary() {
    library_size += 10;
    library = realloc(library, library_size * sizeof(struct books));
    if (!library) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

void addBook() {
    if (book_count >= library_size) {
        reallocateLibrary();
    }

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(library[book_count].date, myDate);

    fp = fopen("book.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &library[book_count].id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(library[book_count].bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(library[book_count].authorName);

    printf("Book Added Successfully\n");

    fwrite(&library[book_count], sizeof(library[book_count]), 1, fp);
    fclose(fp);

    book_count++;
}

void booksList() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");
int i;
    for( i = 0; i < book_count; i++) {
        printf("%-10d %-30s %-20s %s\n", library[i].id, library[i].bookName, library[i].authorName, library[i].date);
    }
}


void del() {
    int id, f = 0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Bookid to remove: ");
    scanf("%d", &id);
int i;
    for ( i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            f = 1;
            updateBookIndices(i);
            break;
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }
}





void issueBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int f = 0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    int book_id;
    scanf("%d", &book_id);

    // Check if we have book of given id
    int i;
    for ( i = 0; i < book_count; i++) {
        if (library[i].id == book_id) {
            struct student s;
            strcpy(s.date, myDate);
            s.id = book_id;
            strcpy(s.bookName, library[i].bookName);

            printf("Enter Student Name: ");
            fflush(stdin);
            gets(s.sName);

            printf("Enter Student Class: ");
            fflush(stdin);
            gets(s.sClass);

            printf("Enter Student Roll: ");
            scanf("%d", &s.sRoll);

            printf("Book Issued Successfully\n\n");

            fp = fopen("issue.txt", "ab");
            fwrite(&s, sizeof(s), 1, fp);
            fclose(fp);

            updateBookIndices(i);
            break;
        }
    }
}


void issueList() {
    system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "B.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}

void searchBook() {
    char bookName[50];
    system("cls");
    printf("<== Search Book ==>\n\n");
    printf("Enter book name to search: ");
    fflush(stdin);
    gets(bookName);

    int found = 0;
    int i;
    for ( i = 0; i < book_count; i++) {
        if (strcmp(library[i].bookName, bookName) == 0) {
            printf("Book found: ID = %d, Name = %s, Author = %s\n", library[i].id, library[i].bookName, library[i].authorName);
            found = 1;
            break;
        }
    }

    if (found==0) {
        printf("Book not available\n");
    }
}

void updateBookIndices(int index) {
	int i;
    for ( i = index; i < book_count - 1; i++) {
        library[i] = library[i + 1];
        library[i].id = i + 1; // Update the book ID
    }
    book_count--;
}




