#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int menu(void);
void display(int i);
void date_search(void);
void enter(void);
void save(void);
void load(void);

struct catalog {
    char date[80]; //day.month
    char year[80]; //year
    char note[80];
} cat[MAX];

int top = 0; // last location used

int main(void)
{
    int choice;

    load();   // read in notebook

    do {
        choice = menu();
        switch(choice) {
            case 1: enter();  // enter note
            break;
            case 2: date_search();  // search by date
            break;
            case 3: save();
        } 

    } while(choice!=4);

    return 0;
}

// return a menu selection.
int menu(void)
{
    int i;
    char str[80];

    printf("Write Notes:\n");
    printf("  1. Enter\n");
    printf("  2. Search by date\n");
    printf("  3. Save notes\n");
    printf("  4. Quit\n");

    do {
        printf("Choose your selection: ");
        gets(str);
        i = atoi(str);
        printf("\n");
    } while(i<1 || i>4);

    return i;
}

// Enter books into database.
void enter(void)
{
    int i;

    for(i=top; i<MAX; i++) {
        printf("Enter year (Enter to quit): ");
        gets(cat[i].year);
        if(!*cat[i].year) break;
        printf("Enter date: ");
        gets(cat[i].date);
        printf("Enter note: ");
        gets(cat[i].note);
    }
    top = i;
}

void date_search(void)
{
    char year[80];
    char date[80];
    int i, found;

    printf("year: ");
    gets(year);
    found = 0;

    for(i=0; i<top; i++)
    if(!strcmp(year, cat[i].year)) {
        printf("\n");
        printf("date: ");
        gets(date);

        if(!strcmp(date, cat[i].date)) {
        display(i);
        found = 1;
        printf("\n");
        }

    }

    if(!found) printf("Not Found\n");
}

void display(int i)
{
    printf("%s\n", cat[i].note);
}

// Load the notebook file.
void load(void)
{
    FILE *fp;

    if((fp = fopen("notebook", "rb")) == NULL) {
        printf("Notebook file not on disk.\n");
        return;
    }

    if(fread(&top, sizeof top, 1, fp) != 1) {  /* read count */
        printf("Error reading count.\n");
        exit(1);
    }

    if(fread(cat, sizeof cat, 1, fp) != 1)  {  /* read data */
        printf("Error reading notebook data.\n");
        exit(1);
    }

    fclose(fp);
}

// Save the notebook file.
void save(void)
{
    FILE *fp;

    if((fp = fopen("notebook", "wb")) == NULL) {
        printf("Cannot open notebook file.\n");
        exit(1);
    }

    if(fwrite(&top, sizeof top, 1, fp) != 1) {  /* write count */
        printf("Error writing count.\n");
        exit(1);
    }
    if(fwrite(cat, sizeof cat, 1, fp) != 1) {  /* write data */
        printf("Error writing notebook data.\n");
        exit(1);
    }

    fclose(fp);
}
