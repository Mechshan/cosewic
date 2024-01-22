#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cosewic.h"


//just print instructions to screen for main and 4
void printMenu(int type)
{

    switch (type)
    {

        //main
    case 0:
        printf("=======================================================\n"
            "         Canada Species at Risk Analysis\n"
            "            (Data Years: 2010 - 2019)\n"
            "=======================================================\n"
            "1. View by year (sorted ASCENDING by year)\n"
            "2. View by province (sorted DESCENDING by totals)\n"
            "3. View by taxon (sorted ASCENDING by totals)\n"
            "4. View by province and taxon\n"
            "-------------------------------------------------------\n"
            "0. Exit\n"
            "-------------------------------------------------------\n");
        break;

        // custom (4) part 1
    case 2:
        printf("Choose a Province\n"
            "----------------------------------\n"
            " 1) AB (Alberta)\n"
            " 2) BC (British Columbia)\n"
            " 3) MB (Manitoba)\n"
            " 4) NB (New Brunswick)\n"
            " 5) NL (Newfoundland)\n"
            " 6) NS (Nova Scotia)\n"
            " 7) NT (Northwest Territories)\n"
            " 8) NU (Nunavut)\n"
            " 9) ON (Ontario)\n"
            "10) PE (Prince Edward Island)\n"
            "11) QC (Quebec)\n"
            "12) SK (Saskatchewan)\n"
            "13) YT (Yukon Territory)\n");
        break;

        // custom (4) part 2
    case 3:
		printf("Choose a Taxon\n"
			"---------------\n"
			" 1) Mammals\n"
			" 2) Birds\n"
			" 3) Reptiles\n"
			" 4) Amphibians\n"
			" 5) Fishes\n"
			" 6) Arthropods\n"
			" 7) Molluscs\n"
			" 8) Vascular Plants\n"
			" 9) Mosses\n"
			"10) Lichens\n");
        break;

    default:
        break;

    }
}


//just print labels 1-4 : year, prov, taxon, custom prov+taxon
void printHeader(int type)
{
    switch (type)
    {

        //yearly
    case 1:
        printf("YEAR EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n"
            "---- ------- ---------- ---------- ---------- ------- ---------\n");
        break;

        //by prov
    case 2:
		printf("PROVINCE             EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n"
			"-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
        break;

        //by taxon
    case 3:
        printf("TAXON           EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n"
            "--------------- ------- ---------- ---------- ---------- ------- ---------\n");
        break;

        // prov and taxon
    case 4:
        printf("EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n"
            "------- ---------- ---------- ---------- ------- ---------\n");
        break;

    default:
        break;
    }

    return;
}


//just print lines 1-4 : year, prov, taxon, custom prov+taxon
void printFooter(int type)
{
    switch (type)
    {

        //yearly
    case 1:
        printf("---- ------- ---------- ---------- ---------- ------- ---------\n");
        break;

        //by prov
    case 2:
        printf("-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
        break;

        //by taxon
    case 3:
        printf("--------------- ------- ---------- ---------- ---------- ------- ---------\n");
        break;

        // prov and taxon
    case 4:
        printf("------- ---------- ---------- ---------- ------- ---------\n");
        break;

    default:
        break;
    }

    return;
}


//print formatted entries 1-4 : year, prov, taxon, custom prov+taxon
void printEntry(int type, struct Analysis entry)
{
    switch (type)
    {

        //yearly
    case 1:
        printf("%-4s %7d %10d %10d %10d %7d %9d\n"
        , entry.label, entry.extinct, entry.extirpated, entry.endangered, entry.threatened, entry.concern, entry.total);
        break;

        //by prov
    case 2:
        printf("%-20s %7d %10d %10d %10d %7d %9d\n"
            , entry.label, entry.extinct, entry.extirpated, entry.endangered, entry.threatened, entry.concern, entry.total);
        break;

        //by taxon
    case 3:
        printf("%-16s %7d %10d %10d %10d %7d %9d\n"
            , entry.label, entry.extinct, entry.extirpated, entry.endangered, entry.threatened, entry.concern, entry.total);
        break;

        // prov and taxon
    case 4:
        printf("%7d %10d %10d %10d %7d %9d\n"
            , entry.extinct, entry.extirpated, entry.endangered, entry.threatened, entry.concern, entry.total);
        break;

    default:
        break;
    }

    return;
}


//get datafile and populate data array
int loadData(char* datafile, struct FileData* data, int max)
{
    FILE* fp = NULL;

    fp = fopen(datafile, "r");


    // specs for this data
    char delimiter = ',';
    int entries = 5;

    //track progress
    int entryCount = 0;
    int lineCount = 0;


    // we will build a buffer one ch at a time, copy data and clear at delimiters
    char buffer[STRINGLEN] = { 0 };

    char ch;

    //strcat requires a string with a \0 terminator
    char chString[2];
    chString[1] = '\0';



    if (fp) // not null
    {

        do //This part skips the first line
        {
            ch = getc(fp);
        } while (ch != '\n');
        /////////////////////////

        do //while not eof or reached max entries
        {

            ch = getc(fp); //read file one ch at a time

            if (ch != EOF)
            {

                if (ch == '\n' || ch == delimiter) // done building this entry
                {
                    // copy data
                    
                        switch (entryCount)
                        {

                        case 0: // year
                            //data[lineCount].year = atoi(buffer);
                            strcpy(data[lineCount].year, buffer);
                            break;

                        case 1: // taxon
                            strcpy(data[lineCount].taxon, buffer);
                            break;

                        case 2: // status
                            strcpy(data[lineCount].status, buffer);
                            break;

                        case 3: // count
                            data[lineCount].count = atoi(buffer);
                            break;

                        case 4: // province
                            strcpy(data[lineCount].province, buffer);
                            break;

                        }
                                        

                    // done with this entry, set up for the next
                    strcpy(buffer, ""); //clear buffer
                    entryCount++; // next entry
                    entryCount %= entries; // only x number of entries per line
                    
                    if (ch == '\n') // next line
                    {
                            lineCount++;
                    }

                }
                else // continue building this entry
                {

                    chString[0] = ch; //turn ch into string
                    strcat(buffer, chString); //continue building

                }

            }

        } while (ch != EOF && lineCount < max);



        fclose(fp);

    }
    else //is null
    {
        printf("Failed to open file\n");
    }

    return lineCount;

}


//main menu
void mainLogic(struct FileData* data, int records)
{
    int input;
    do
    {
        printMenu(0);

        input = inputSelectRange(0, 4);

        switch (input)
        {

        case 0:
            printf("Application Terminated!\n");
            break;

        case 1:
            viewYear(data, records);
            break;

        case 2:
            viewProvince(data, records);
            break;

        case 3:
            viewTaxon(data, records);
            break;

        case 4:
            viewCustom(data, records);

            break;

        default:
            break;
        }

    } while (input);
    
}


// 1
void viewYear(struct FileData * data, int records)
{
    int i, validEntries;
    struct Analysis years[TABLE_ENTRIES] = { 0 };

    struct Analysis total = { 0 };

    performAnalysisYear(data, records, years, TABLE_ENTRIES);// populate the table
        
    validEntries = getEmptyEntry(years, TABLE_ENTRIES) - 1;// how many entries we made


    quickSortAnalysis(years, 0, validEntries);// sort the table

    //print the contents of analysis table
    printHeader(1);
    for (i = 0; i <= validEntries; i++)
    {
        if (strcmp(years[i].label, ""))// don't print blank entries
        {
            printEntry(1, years[i]);
        }
    }

    printFooter(1);
    getAnalysisTotal(years, TABLE_ENTRIES, &total);
    printEntry(1, total);


    putchar('\n');
    return;
}


// 2
void viewProvince(struct FileData* data, int records)
{
    int i, validEntries;
    struct Analysis prov[TABLE_ENTRIES] = { 0 };

    struct Analysis total = { 0 };


    performAnalysisProv(data, records, prov, TABLE_ENTRIES);// populate the table

    validEntries = getEmptyEntry(prov, TABLE_ENTRIES) - 1;// how many entries we made
    

    quickSortAnalysis(prov, 0, validEntries);// sort the table



    printHeader(2);

    // just print it backwards
    for (i = validEntries; i >= 0; i--)
    {
        if (strcmp(prov[i].label, ""))// don't print blank entries
        {
            expandProvinceLabel(prov[i].label); // use full names on output
            printEntry(2, prov[i]);
        }
    }

    printFooter(2);
    getAnalysisTotal(prov, TABLE_ENTRIES, &total);
    printEntry(2, total);


    putchar('\n');
    return;
}


// 3
void viewTaxon(struct FileData* data, int records)
{
    int i, validEntries;

    struct Analysis taxon[TABLE_ENTRIES] = { 0 };

    struct Analysis total = { 0 };


    performAnalysisTaxon(data, records, taxon, TABLE_ENTRIES); // populate the table

    validEntries = getEmptyEntry(taxon, TABLE_ENTRIES) - 1; // how many entries we made

    quickSortAnalysis(taxon, 0, validEntries); // sort the table

    //print the data
    printHeader(3);
    for (i = 0; i <= validEntries; i++)
    {
        if (strcmp(taxon[i].label, ""))// don't print blank entries
        {
            printEntry(3, taxon[i]);
        }
    }

    printFooter(3);
    getAnalysisTotal(taxon, TABLE_ENTRIES, &total);
    printEntry(3, total);


    putchar('\n');
    return;
}


// 4
void viewCustom(struct FileData* data, int records)
{
    struct Analysis custom = { 0 };

    int i; 

    char queryProv[STRINGLEN] = { 0 };
    char queryTaxon[STRINGLEN] = { 0 };


    int input;

    // big menu stuff
    do
    {
        printMenu(2);

        input = inputSelectRange(1, 13);

		/*Choose a Province
----------------------------------
 1) AB (Alberta)
 2) BC (British Columbia)
 3) MB (Manitoba)
 4) NB (New Brunswick)
 5) NL (Newfoundland)
 6) NS (Nova Scotia)
 7) NT (Northwest Territories)
 8) NU (Nunavut)
 9) ON (Ontario)
10) PE (Prince Edward Island)
11) QC (Quebec)
12) SK (Saskatchewan)
13) YT (Yukon Territory)*/

        switch (input)
        {

        case 1:
            strcpy(queryProv, "AB");
            break;

        case 2:
            strcpy(queryProv, "BC");
            break;

        case 3:
            strcpy(queryProv, "MB");
            break;

        case 4:
            strcpy(queryProv, "NB");
            break;

        case 5:
            strcpy(queryProv, "NL");
            break;

        case 6:
            strcpy(queryProv, "NS");
            break;

        case 7:
            strcpy(queryProv, "NT");
            break;

        case 8:
            strcpy(queryProv, "NU");
            break;

        case 9:
            strcpy(queryProv, "ON");
            break;

        case 10:
            strcpy(queryProv, "PE");
            break;

        case 11:
            strcpy(queryProv, "QC");
            break;

        case 12:
            strcpy(queryProv, "SK");
            break;

        case 13:
            strcpy(queryProv, "YT");
            break;

        default:
            break;
        }

    } while (input == -1);

    //more menu
    do
    {
        printMenu(3);

        input = inputSelectRange(1, 10);

        /*Choose a Taxon
---------------
 1) Mammals
 2) Birds
 3) Reptiles
 4) Amphibians
 5) Fishes
 6) Arthropods
 7) Molluscs
 8) Vascular Plants
 9) Mosses
10) Lichens*/

        switch (input)
        {

        case 1:
            strcpy(queryTaxon, "Mammals");
            break;

        case 2:
            strcpy(queryTaxon, "Birds");
            break;

        case 3:
            strcpy(queryTaxon, "Reptiles");
            break;

        case 4:
            strcpy(queryTaxon, "Amphibians");
            break;

        case 5:
            strcpy(queryTaxon, "Fishes");
            break;

        case 6:
            strcpy(queryTaxon, "Arthropods");
            break;

        case 7:
            strcpy(queryTaxon, "Molluscs");
            break;

        case 8:
            strcpy(queryTaxon, "Vascular Plants");
            break;

        case 9:
            strcpy(queryTaxon, "Mosses");
            break;

        case 10:
            strcpy(queryTaxon, "Lichens");
            break;

        default:
            break;
        }

    } while (input == -1);

    
    // iterate through all data
    for (i = 0; i < records; i++)
    {
        //narrow by spec province AND taxon
        if (!strcmp(data[i].province, queryProv) && !strcmp(data[i].taxon, queryTaxon))
        {

            //build the custom dataset
            switch (getStatus(data[i]))
            {
                //EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN

            case 0:
                custom.extinct += data[i].count;
                break;

            case 1:
                custom.extirpated += data[i].count;
                break;

            case 2:
                custom.endangered += data[i].count;
                break;

            case 3:
                custom.threatened += data[i].count;
                break;

            case 4:
                custom.concern += data[i].count;
                break;

            default:
                break;
            }


        }
    }
    
    //done gathering data, get totals 

    custom.total += custom.extinct;
    custom.total += custom.extirpated;
    custom.total += custom.endangered;
    custom.total += custom.threatened;
    custom.total += custom.concern;
    

    printf("*** Data filtered by PROVINCE and TAXON ***\n");

    putchar('\n');

    expandProvinceLabel(queryProv); // full name of province on the output

    printf("    Province: %s\n"
        "    Taxon   : %s\n\n", 
        queryProv , queryTaxon);


    printHeader(4);

    printEntry(4, custom);

    putchar('\n');


    return;
}


//helper function to know if given entry exists in analysis table
int getEntryExists(struct Analysis* table, char * query, int entries)
{
    int i, retVal = -1;

    if (table)
    {

        for (i = 0; i < entries; i++)
        {

            if (!strcmp(table[i].label, query))
            {
                retVal = i;
            }
        }
    }

    return retVal;
}


//make an entry to analysis table under specified label
void addEntry(struct Analysis* table, int entries, char* label, int status, int value)
{
    int targetIndex;
    if (table)
    {

        //where to put the data?

        //it already exists, add here
        targetIndex = getEntryExists(table, label, entries);

        if (targetIndex == -1) // need to make one
        {
            targetIndex = getEmptyEntry(table, entries);

            strcpy(table[targetIndex].label, label); //further finds of "label" will be added to this
        }
        
        //add the data
        //always added to total
        table[targetIndex].total += value;
        
        //specific
        switch (status)
        {
            //EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN

        case 0:
            table[targetIndex].extinct += value;
            break;

        case 1:
            table[targetIndex].extirpated += value;
            break;

        case 2:
            table[targetIndex].endangered += value;
            break;

        case 3:
            table[targetIndex].threatened += value;
            break;

        case 4:
            table[targetIndex].concern += value;
            break;

        default:
            break;
        }

    }


    return;
}


//swap two entries of an analysis struct
void swapEntry(struct Analysis* entry1, struct Analysis* entry2)
{
    struct Analysis temp = { 0 };

    temp = *entry1;
    *entry1 = *entry2;
    *entry2 = temp;
}


// this is an implementation of quicksort, from pseudocode found at
//https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
// attributed to Nico Lomuto
// Sorts an analysis table, divides it into partitions, then sorts those
//
int partitionAnalysis(struct Analysis * table, int min, int max)
{
    int i, j, pivot, sortByYear;
    
    sortByYear = (atoi(table[max].label) && atoi(table[min].label)); // if both these are true then we're likely sorting the year table
   

    // Choose the last element as the pivot
    if (sortByYear) // we are sorting by years
    {
        pivot = atoi(table[max].label);
    }
    else // we are sorting by totals
    {
        pivot = table[max].total;
    }


    // Temporary pivot index
    i = (min - 1);  

        for (j = min; j <= (max - 1); j++) 
        {
            if (sortByYear)
			{
                // If the current element is less than or equal to the pivot
                if (atoi(table[j].label) < pivot)
                {
                    // Move the temporary pivot index forward
                    i++;

                    // Swap the current element with the element at the temporary pivot index
                    swapEntry(&table[i], &table[j]);
                }
			}
			else // sort by totals
			{
				// If the current element is less than or equal to the pivot
				if (table[j].total < pivot)
				{
					// Move the temporary pivot index forward
					i++;

					// Swap the current element with the element at the temporary pivot index
					swapEntry(&table[i], &table[j]);
				}
			}

		}

        // Move the pivot element to the correct pivot position (between the smaller and larger elements)
        i++;
        swapEntry(&table[i], &table[max]);
        
        return i; // the pivot index
}


// this is an implementation of quicksort, from pseudocode found at
//https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
// attributed to Nico Lomuto
// Sorts an analysis table, divides it into partitions, then sorts those
//
void quickSortAnalysis(struct Analysis* table, int min, int max) 
{
    int pivInd;

    // Ensure indices are in correct order
    if (min < max) 
    {

        // Partition array and get the pivot index

        pivInd = partitionAnalysis(table, min, max);

        // Sort the two partitions
        quickSortAnalysis(table, min, pivInd - 1);  // Left side of pivot

        quickSortAnalysis(table, pivInd + 1, max); // Right side of pivot

    }

}


//populate an analysis table from the given data - by year
void performAnalysisYear(struct FileData* data, int records, struct Analysis* table, int entries)
{

    int i;

    for (i = 0; i < records; i++)
    {
        addEntry(table, entries, data[i].year, getStatus(data[i]), data[i].count);
    }

    return;
}


//populate an analysis table from the given data - by province
void performAnalysisProv(struct FileData* data, int records, struct Analysis* table, int entries)
{

    int i;

    for (i = 0; i < records; i++)
    {
        addEntry(table, entries, data[i].province, getStatus(data[i]), data[i].count);
    }

    return;
}


//populate an analysis table from the given data - by taxon
void performAnalysisTaxon(struct FileData* data, int records, struct Analysis* table, int entries)
{

    int i;

    for (i = 0; i < records; i++)
    {
        addEntry(table, entries, data[i].taxon, getStatus(data[i]), data[i].count);
    }

    return;
}


//helper function to find the earliest empty slot in the analysis table
int getEmptyEntry(struct Analysis* table, int entries)
{
	int i, retVal = -1;
	if (table)
	{
        
        for (i = 0; i < entries; i++)
		{

            if (!strcmp(table[i].label, "") && retVal == -1)
            {
                retVal = i;
            }
		}
	}

    return retVal;
}


//helper function to simplify determining where to put the data 
int getStatus(struct FileData entry)
{
    int retVal;

    // 0 to 4 EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN

    if (!strcmp(entry.status, "EXTINCT"))
    {
        retVal = 0;
    }
    else if (!strcmp(entry.status, "EXTIRPATED"))
    {
        retVal = 1;
    }
    else if (!strcmp(entry.status, "ENDANGERED"))
    {
        retVal = 2;
    }
    else if (!strcmp(entry.status, "THREATENED"))
    {
        retVal = 3;
    }
    else if (!strcmp(entry.status, "SPECIAL CONCERN"))
    {
        retVal = 4;
    }
    else
    {
        retVal = -1;
    }


    return retVal;
}


//from a table of analysis entries collect totals and save to result
void getAnalysisTotal(struct Analysis* table, int entries, struct Analysis * result)
{
    int i;

    if (table && result)
    {
        for (i = 0; i < entries; i++)
        {
            
            result->concern += table[i].concern;
            result->endangered += table[i].endangered;
            result->extinct += table[i].extinct;
            result->extirpated += table[i].extirpated;
            result->threatened += table[i].threatened;
            result->total += table[i].total;
            
        }

    }

    return;
}


//turn ON into Ontario etc.
void expandProvinceLabel(char* string)
{

	/*AB
	BC
	MB
	NB
	NL
	NS
	NT
	NU
	ON
	PE
	QC
	SK
	YT */

    if (!strcmp(string, "AB"))
    {
        strcpy(string, "Alberta");
    }
    else if (!strcmp(string, "BC"))
    {
        strcpy(string, "British Columbia");
    }
    else if (!strcmp(string, "MB"))
    {
        strcpy(string, "Manitoba");
    }
    else if (!strcmp(string, "NB"))
    {
        strcpy(string, "New Brunswick");
    }
    else if (!strcmp(string, "NL"))
    {
        strcpy(string, "Newfoundland");
    }
    else if (!strcmp(string, "NS"))
    {
        strcpy(string, "Nova Scotia");
    }
    else if (!strcmp(string, "NT"))
    {
        strcpy(string, "Northwest Territory");
    }
    else if (!strcmp(string, "NU"))
    {
        strcpy(string, "Nunavut");
    }
    else if (!strcmp(string, "ON"))
    {
        strcpy(string, "Ontario");
    }
    else if (!strcmp(string, "PE"))
    {
        strcpy(string, "Prince Edward Island");
    }
    else if (!strcmp(string, "QC"))
    {
        strcpy(string, "Quebec");
    }
    else if (!strcmp(string, "SK"))
    {
        strcpy(string, "Saskatchewan");
    }
    else if (!strcmp(string, "YT"))
    {
        strcpy(string, "Yukon Territory");
    }
    
    return;

}


// given two bounds returns integer value from a successful user prompt
int inputSelectRange(int lowerBound, int upperBound)
{
	int value = -1;

    printf("Selection: ");
	scanf(" %d", &value);
    putchar('\n');

	if ((value < lowerBound) || (value > upperBound))
	{
		value = -1;
		printf("Invalid menu selection!\n\n");
	}

	return value;
}