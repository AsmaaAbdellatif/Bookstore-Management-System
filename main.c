/*
Student Name    : Asmaa Abdellatif
Student Number  : 1230259
Lecture Section : 6
Lab Section     : 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAXSIZE 100
#define  NAMESIZE 50

void displayMainMenu();   	                                 // displays the main menu shown above
void addBook(char[][NAMESIZE],int[], double[], int*);        // adds information for a new book
void removeBook(char[][NAMESIZE],int[], double[], int*);  	 // removes information of old book
void searchForBook(char[][NAMESIZE],int[], double[], int);   // searches for a book in the store
void printBooks(char[][NAMESIZE],int[], double[], int);      // print the information
void uploadDataFile(char[][NAMESIZE],int[], double[], int*); // uploads book data from file
void updateDataFile(char[][NAMESIZE],int[], double[], int);  // saves book data updates to file


int main()
{
    int option, bins[MAXSIZE], prices[MAXSIZE], size=0, names[MAXSIZE][NAMESIZE] ;
    printf("Welcome to My BookStore Management System:\n");
    uploadDataFile(names,bins,prices,&size);
    do
    {
        displayMainMenu();
        scanf("%d",&option);
        switch(option)
        {
        case 1 :
            addBook(names,bins,prices,&size);
            break;
        case 2 :
            removeBook(names,bins,prices,&size);
            break;
        case 3 :
            searchForBook(names,bins,prices,size);
            break;
        case 4 :
            printBooks(names,bins,prices,size);
            break;
        case 5 :
            updateDataFile(names,bins,prices,size);
            break;
        default:
            printf("No such operation! Please try again.\n");
            break;
        }
    }
    while (option!=5);
    printf("\nThank you for using My BookStore Management System. GoodBye.\n");
    return 0;
}

void uploadDataFile(char names[][NAMESIZE], int bins[], double prices[], int *size)
{
    printf("\nUploading data file...\n");
    FILE *file = fopen("books.txt", "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    while (fscanf(file, "%s %d %lf", names[*size], &bins[*size], &prices[*size]) != EOF)
    {
        (*size)++;
        if (*size >= MAXSIZE)
        {
            break;
        }
    }

    for(int i=0 ; i<*size ; i++)
    {
        printf("Book Name : %s ,Book Bin : %d , Book Prices : %0.2f\n",names[i],  bins[i], prices[i]);

    }

    fclose(file);
    printf("Data File uploaded\n\n");
}

void displayMainMenu()
{
    printf("\nPlease Select an Operation <1-4>:\n");
    printf("1- Add a Book:\n");
    printf("2- Remove a Book:\n");
    printf("3- Search for a book:\n");
    printf("4- Print Book List:\n");
    printf("5- Exit System:\n");
}
void addBook(char names[][NAMESIZE],int bins[], double prices[], int*size)
{
    int new_bin = 0 ;
    double new_price = 0;
    int Flag = 0;
    char name[50];
    int shift_index;
    if(*size < MAXSIZE)
    {
        printf("Enter bin number for book\n");
        scanf("%d",&new_bin);
        for(int bin_index = 0 ; bin_index < *size ; bin_index++)
        {
            if(bins[bin_index] == new_bin)
            {
                printf("THE BIN NUMBER YOU ENTERED IS ALREADY EXISTS AND IT'S PRICE IS %.2f AND IT'S NAME IS %s\n", prices[bin_index],names[bin_index]);
                Flag = 1;
                break;
            }
        }

        if(Flag == 0)
        {
            // bins = 50 ---> 30 40 60 80
            int smallest_index = 0;
            while(bins[smallest_index] < new_bin)
            {
                smallest_index++;
            }
            smallest_index--;
            //printf("smallest_index: %d\n", smallest_index);
            // smallest_index : 1 -> 40
            // ex. size = 4 -> shift_index = 3 (80) -> 3 > 1 ??
            (*size)++;
            // since i increase the size by 1 I need to take the correct size before increment
            for(shift_index = *size-2 ; shift_index > smallest_index ; shift_index--)
            {
                //printf("Size is: %d\n", *size);
                // first loop : shift_index = 3 --> bins[3] = 80 --> bins[4] = 80 & prices[4] = prices for 80.
                // second loop : shift_index = 2 --> bins[2] = 60 --> bins[3] = 60 & prices[3] = prices for 60.
                // third loop : shift_index = 1 --> 1 > smallest?? no

                bins[shift_index+1] = bins[shift_index];
                prices[shift_index+1] = prices[shift_index];
                strcpy(names[shift_index+1],names[shift_index]);

                //printf("pins[shift_index + 1] : %d     prices[shift_index+1] : %f\n", bins[shift_index+1],  prices[shift_index+1]);
            }
            // bins --> 30 40 60 60 80 shift_index = 1
            shift_index++; // -> 2
            bins[shift_index] = new_bin;
            printf("Enter name of book\n");
            scanf("%s",name);
            //printf("%s\n", name);
            printf("Enter price of book\n");
            scanf("%lf",&new_price);
            prices[shift_index] = new_price;
            strcpy(names[shift_index], name);
            //printf("%d      %0.2f\n",bins[shift_index], prices[shift_index] );
            printf("Book with bin %d has been added\n",new_bin);

            /*printf("-------------- Your Books --------------\n");
            for(int i=0 ; i<*size ; i++)
            {
                printf("Book Name: %s , Book Bin : %d , Book Prices : %0.2f\n", names[i], bins[i], prices[i]);

            }*/
        }
    }
    else
    {
        printf("THERE IS NO SIZE IN THIS ARRAY\n");
    }
}
void removeBook(char names[][NAMESIZE],int bins[], double prices[], int*size)
{
    int removed_bin = 0 ;
    int Flag = 0;
    int shift_index;
    if(*size < MAXSIZE && *size > 0)
    {
        printf("Enter bin number for book to remove\n");
        scanf("%d",&removed_bin);
        int bin_removed_index = 0;

        while (bins[bin_removed_index] != removed_bin && bin_removed_index < *size)
        {
            bin_removed_index++;
        }

        if(bin_removed_index >= *size)
        {
            printf("BOOK WITH BIN %d DOSE NOT EXIST\n", removed_bin);
            Flag = 1;
        }

        if(Flag == 0)
        {
            for(shift_index = bin_removed_index ; shift_index < *size ; shift_index++)
            {
                bins[shift_index] = bins[shift_index+1];
                prices[shift_index] = prices[shift_index+1];
                strcpy(names[shift_index],names[shift_index+1]);
            }

            (*size)--;
            printf("Book with bin %d has been removed\n",removed_bin);

            /*printf("-------------- Your Books --------------\n");
            for(int i=0 ; i<*size ; i++)
            {
                printf("Book Name: %s , Book Bin : %d , Book Prices : %0.2f\n", names[i], bins[i], prices[i]);

            }*/
        }
    }
    else
    {
        printf("THERE IS NO BOOKS IN THE ARRAY\n");
    }
}
void searchForBook(char names[][NAMESIZE],int bins[], double prices[], int size)
{
    if(size > 0)
    {
        int i,j,k ;
        printf("Enter bin number for book to search for\n");
        scanf("%d",&k);
        for(i = 0 ; i < size ; i++)
        {
            if(k == bins [i])
            {
                j=1;
                printf("Name = %-50s bin# = %d\t price = %0.2f\n",names[i],bins[i],prices[i]);
                break;
            }
        }
        if(j == 0)
        {
            printf("AN ERROR OCCURED! THE BIN NUMBER IS NOT EXIST\n");
        }
    }
    else
    {
        printf("THE LIST IS EMPTY\n");
    }
}
void printBooks(char names[][NAMESIZE],int bins[], double prices[], int size)
{
    //printf("%d\n",size);
    int i ;
    for(i = 0 ; i < size ; i ++)
    {
        printf("Name = %-50s bin # = %d\t price = %0.2f\n",names[i], bins[i],prices[i]);
    }
    printf("\n");
}
void updateDataFile(char names[][NAMESIZE],int bins[], double prices[], int size)
{
    printf("Updating data file...\n");
    FILE * file;
    file = fopen("books.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s\t%d\t%.2f\n",names[i], bins[i], prices[i]);
    }
    fclose(file);
    printf("Data File updated\n");
}
