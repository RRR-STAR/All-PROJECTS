
#include <istream>
#include <conio.h>
using namespace std;

namespace WordGuesser {
    
    namespace functions {
        
        void header(){ // header outlet
            printf("\n\n\n\t\t-----------------------------------------\
                        \n\t\t|        Welcome to Word Guesser        |\
                        \n\t\t-----------------------------------------\
            \n\n");
        }
        
        void printTable(char **table, short int &rows, short int &columns){
            // i = -2 to print two extra lines(1.column values, 2.underscore) except the table
            for (short int i = -2; i < rows; i++){ // display the table
                
                if (i == -2){ printf("\n\t\t  "); }
                else if (i == -1){ printf("\n\t\t_"); }
                else { printf("\n\t\t| "); }
                
                for (short int j = 0; j < columns; j++){
                    
                    if (i == -2){ printf("%d   ", j + 1); }
                    else if (i == -1){ printf("____"); }
                    else { printf("%c | ", table[i][j]); }
                }
            }
            printf("\n\n");
        }
        
        void footer(char *ans, short int &ansLength){
            printf("\n\n\t\t-----------------------------------------\
                    \n\n\t\t  Your Word is  < ");
            for (short int i = 0; i < ansLength; i++){ printf("%c ", ans[i]); }
            printf(">\n\n\n\n\n\n");
        }
    }
    
    void main(){
        system("cls");   functions::header();
        printf("\n\t[ WordGuesser ] : Think about a word of any length.");
        _sleep(3000); // for pause the pg. for a certain amount of time
        printf("\n\t[ WordGuesser ] : Hope you are done !\
                \n\t[ WordGuesser ] : How many letters are there in your word ? \
                \n\t => ");
        short int wordLength = 0;   scanf("%hd", &wordLength);
        printf("\n\t( Me )         : My word contains %d letters.", wordLength);
        
        if (wordLength <= 0){
            printf("\n\t[ WordGuesser ] : Your word must contain at least two letters !");
            exit(0);
        }
        printf("\n\t[ WordGusser ] : OK! That's Fine.\
                \n\t[ WordGusser ] : Now you should have to provide me some hints for guessing your word.\
                \n\n\t  Press... any button... to continue...");
        getche();   system("cls");   functions::header();
        printf("\n\t[ WordGuesser ] : Select the columns in which your letters are located.\n\n");
        
        short int rows = 26 / wordLength + 1, letter = 65;
        char *firstTable[rows]; // matrix of first table
        
        for (short int i = 0; i < rows; i++){
            firstTable[i] = new char[wordLength](); // allocate memory for columns
            
            for (short int j = 0; j < wordLength; j++){
                // only takes upto 'Z' & rest are spaces 
                if (letter > 90){ firstTable[i][j] = ' '; }
                else {
                    firstTable[i][j] = static_cast<char>(letter);
                    ++letter; // increment the letters
                }
            }
        }
        functions::printTable(firstTable, rows, wordLength);
        char *secondTable[wordLength]; // seconed table
        short int letterPos = 0;
        
        for (short int i = 0; i < wordLength; i++){
            printf("\n\t[ WordGuesser ] : Enter %d letter column position : ", i + 1);
            scanf("%hd", &letterPos);
            
            if (letterPos <= 0 or letterPos > wordLength){
                printf("\t[ WordGuesser ] : InputError! enter valid column positions");
                delete []firstTable;   delete []secondTable;
                exit(1);
            }
            printf("\t( Me )          : My %d letter is in %d column.", i + 1, letterPos);
            
            secondTable[i] = new char[rows](); // memory for second table
            for (short int j = 0; j < rows; j++){ // create each row from column
                secondTable[i][j] = firstTable[j][letterPos - 1]; // -1 to match array index
            }
        }
        system("cls");   functions::header();
        printf("\n\t[ WordGuesser ] : Re-select the columns in which your letters are located.\n\n");
        functions::printTable(secondTable, wordLength, rows);
        
        // after constructing the second table the first table is not needed more
        for (short int i = 0; i < rows; i++){ 
            delete firstTable[i];   firstTable[i] = nullptr; 
        }
        char WORD[wordLength]; // finding the actual user's word
        for (short int i = 0; i < wordLength; i++){ 
            printf("\n\t[ WordGuesser ] : Enter %d letter column position : ", i + 1);
            scanf("%hd", &letterPos);
            
            if (letterPos <= 0 or letterPos > rows){
                printf("\t[ WordGuesser ] : InputError! enter valid column positions");
                delete []secondTable;
                exit(1);
            }
            printf("\t( Me )          : My %d letter is in %d column.", i + 1, letterPos);
            
            WORD[i] = secondTable[i][letterPos - 1];
            delete secondTable[i];   secondTable[i] = nullptr; 
        }
        system("cls");   functions::header();   functions::footer(WORD, wordLength);
    }
}
main(){ WordGuesser::main(); getch(); }
// main ends