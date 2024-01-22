#ifndef COSEWIC_H
#define COSEWIC_H

//memory for all strings used
#define STRINGLEN 32

//the size of the analysis tables
#define TABLE_ENTRIES 15

//////////////////////////////////////
// Structures
//////////////////////////////////////


struct FileData
{
    //YEAR,TAXON,STATUS,COUNT,PROVINCE
    //2012,Lichens,THREATENED,3,BC

    char year[STRINGLEN];

    char taxon[STRINGLEN];

    char status[STRINGLEN];

    int count;

    char province[STRINGLEN];


};


// will use this to display tables of analyzed data
struct Analysis
{
    char label[STRINGLEN];

    int extinct;
    int extirpated;
    int endangered;
    int threatened;
    int concern;
    int total;
};


//////////////////////////////////////
// Functions
//////////////////////////////////////


//just print instructions to screen for main and 4
void printMenu(int type);


//just print labels 1-4 : year, prov, taxon, custom prov+taxon
void printHeader(int type);


//just print lines 1-4 : year, prov, taxon, custom prov+taxon
void printFooter(int type);


//print formatted entries 1-4 : year, prov, taxon, custom prov+taxon
void printEntry(int type, struct Analysis entry);


//get datafile and populate data array
int loadData(char * datafile, struct FileData * data, int max);


//main menu
void mainLogic(struct FileData* data, int records);


// 1
void viewYear(struct FileData* data, int records);


// 2
void viewProvince(struct FileData* data, int records);


// 3
void viewTaxon(struct FileData* data, int records);


// 4
void viewCustom(struct FileData* data, int records);


//helper function to know if given entry exists in analysis table
int getEntryExists(struct Analysis* table, char* query, int entries);


//make an entry to analysis table under specified label
void addEntry(struct Analysis* table, int entries, char* label, int status, int value);


//helper function to find the earliest empty slot in the analysis table
int getEmptyEntry(struct Analysis* table, int entries);


//swap two entries of an analysis struct
void swapEntry(struct Analysis* entry1, struct Analysis* entry2);


//this is an implementation of quicksort, from pseudocode found at
//https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
//
//Sorts an analysis table, divides it into partitions, then sorts those
//
int partitionAnalysis(struct Analysis* table, int min, int max);


//this is an implementation of quicksort, from pseudocode found at
//https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
//
//Sorts an analysis table, divides it into partitions, then sorts those
//
void quickSortAnalysis(struct Analysis* table, int min, int max);


//populate an analysis table from the given data - by year
void performAnalysisYear(struct FileData* data, int records, struct Analysis* table, int entries);


//populate an analysis table from the given data - by province
void performAnalysisProv(struct FileData* data, int records, struct Analysis* table, int entries);


//populate an analysis table from the given data - by taxon
void performAnalysisTaxon(struct FileData* data, int records, struct Analysis* table, int entries);


//helper function to simplify determining where to put the data 
int getStatus(struct FileData entry);


//from a table of analysis entries collect totals and save to result
void getAnalysisTotal(struct Analysis * table, int entries, struct Analysis * result);


//turn ON into Ontario etc.
void expandProvinceLabel(char* string);


// given two bounds returns integer value from a successful user prompt
int inputSelectRange(int lowerBound, int upperBound);


#endif // !COSEWIC_H