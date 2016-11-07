//  ANALYSIS OF ALGORITHMS I - HOMEWORK 2
//  CAN YILMAZ ALTINİĞNE - 150130132

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <ctime>

using namespace std;

//  ******************  NUMBER CLASS  ********************

class Number {

    long int number;                                // FOR 3RD QUESTION IN QUICK SORT SECTION

public:

    void set_number(long int number){
        this->number = number;
    }

    long int get_order(){
        return number;
    }

    bool operator < (long int order){
        return number < order;
    }
};

//  ******************  WORD CLASS  ********************

class Word {

    int word_order;                                         // FOR WORDS IN LINES
    string word;

public:

    string get_word(){
        return word;
    }

    void set_word(string word){
        this->word = word;
    }

    int get_order(){
        return word_order;
    }

    void set_order(int order){
        word_order = order;
    }

    bool operator < (long int order){
        return word_order < order;
    }
};

//  ****************************************************

//  ******************  LINE CLASS  ********************

class Line {                                    // LINES IN MOBY DICK

    int original_line_number;
    vector<Word> words;                         // WORDS IN THAT LINE

public:

    bool operator < (long int order){
        return original_line_number < order;
    }

    int get_order(){
        return original_line_number;
    }

    vector<Word>& get_words() {
        return words;
    }

    void set_words(vector<Word> words){
        this->words = words;
    }

    void set_original_line_number(int line_number){
        this->original_line_number = line_number;
    }
};

// ******************************************************

// QUICK SORT ALGORITHM

// PARTITION FUNCTION FOR QUICK SORT

template <typename T>
long int partition(vector<T> & A, long int start, long int end, bool is_Randomized){

    T temp;

    if (is_Randomized) {            // IF IT IS RANDOMIZED QUICK SORT THEN PIVOT ELEMENT IS RANDOMLY SELECTED
        srand(255);
        long int random_pivot_index = start + (rand() % (end-start+1));         // RANDOM INDEX NUMBER BETWEEN END & START OF PARTITION
        temp = A[random_pivot_index];
        A[random_pivot_index] = A[end];                                       // AFTER DETERMINE THE PIVOT ELEMENT SWAP IT WITH END ELEMENT
        A[end] = temp;                                                        // OF PARTITION BECAUSE IN LECTURE SLIDES WE CHOOSE LAST ELEMENT AS PIVOT
    }

    T pivot_element = A[end];                         // THEN END ELEMENT IS PIVOT ELEMENT IF IT IS RANDOMIZED THE PIVOT ELEMENT IS ALREADY ASSIGNED AS END ELEMENT

    long int pivot_number = pivot_element.get_order();  // GET THE ORDER FOR LINE IT RETURNS LINE NUMBER, FOR WORD IT RETURNS WORD ORDER IN LINE,
                                                        // FOR NUMBER IT RETURNS THAT NUMBER
    long int i = start-1;

    for (long int j = start; j < end; j++) {         // ORDER THE SMALLER ONES TO THE LEFT OF THE PIVOT
        if (A[j] < pivot_number ) {
            i += 1;

            temp = A[i];
            A[i] = A[j];
            A[j] = temp;

        }
    }

    temp = A[i+1];                                        // FINALLY FIRST BIGGER ELEMENT THAN PIVOT AND PIVOT ELEMENT (WHICH IS END OF PARTITION) IS SWAPPED
    A[i+1] = pivot_element;
    A[end] = temp;

    return i+1;

}

int quicksort_counter = 0;

// QUICK SORT

template <typename T>
void quick_sort(vector<T> & A, long int start, long int end, int M, int N, bool is_Randomized){

    quicksort_counter++;

    if (quicksort_counter == M) cout << A[N].get_order() << endl;

    long int q;

    if (start < end) {
        q = partition(A, start, end, is_Randomized);            // FIND THE PARTITION POINT
        quick_sort(A, start, q-1, M, N, is_Randomized);         // QUICK SORT THE LEFT OF PIVOT
        quick_sort(A, q+1, end, M, N, is_Randomized);           // QUICK SORT THE RIGHT OF PIVOT
    }
}

// TO SPLIT WORDS AND WORD ORDERS IN LINE

vector<Word> split(string str, string str2) {

    vector<Word> words;

    stringstream ss_word(str); // Turn the string into a stream.
    stringstream ss_word_order(str2);

    string tok_one, tok_two;
    Word temp;

    while(getline(ss_word, tok_one, '_') && getline(ss_word_order, tok_two, '_')) {     // WORD ORDERS AND WORDS ARE SPLITTED BY "_"
        temp.set_word(tok_one);                                                         // WORD IS PUSHED TO WORD VECTOR
        temp.set_order(atoi(tok_two.c_str()));
        words.push_back(temp);
    }

    return words;                       // THAT VECTOR IS RETURNED TO ASSIGN THAT LINE'S CLASS VARIABLE "WORDS"
}

// --------------------------------------------

int main(int argc, const char * argv[]) {

    ifstream moby_dick_file;
    ifstream numbers_file;
    ofstream novel;
    ofstream numbers;
    int M,N,K;

    vector<Line> line_array;
    vector<Word> word_array;
    vector<Number> numbers_array;

    Line temp;
    int order;
    string words, word_order;

    if (atoi(argv[1]) == 1) {
        moby_dick_file.open("mobydick.txt");
        novel.open("novel.txt");
        M = atoi(argv[2]);
        N = atoi(argv[3]);

        // ****************** TAKING LINE INPUTS ***************************

        while (moby_dick_file >> order >> words >> word_order) {

            words.erase(0,1);                               // { AND } IS DELETED FROM WORDS AND WORD ORDER
            word_order.erase(0,1);
            words.erase(words.size()-1,1);
            word_order.erase(word_order.size()-1,1);

            temp.set_original_line_number(order);
            temp.set_words(split(words, word_order));           // SPLIT FUNCTION IS CALLED TO HAVE WORD VECTOR FOR THAT LINE WORD CAN HOLD A WORD AND THAT WORD'S ORDER
            line_array.push_back(temp);
        }

        // ****************     PART 1: SORTING LINES    *******************

        quick_sort(line_array, 0, line_array.size()-1, M, N, false);

        // ***********   PART 2: SORTING WORDS IN SORTED LINES   ***********

        for (int i = 0; i < line_array.size(); i++) {
            quick_sort(line_array[i].get_words(), 0, line_array[i].get_words().size()-1, 0, 0, true);
        }

        // ******   PRINT SORTED LINES AND WORDS IN NOVEL TEXT FILE  *****

        for (int k = 0; k < line_array.size(); k++) {
            for (int l = 0; l < line_array[k].get_words().size(); l++) {
                novel << line_array[k].get_words()[l].get_word() << " ";
            }
            novel << endl;
        }

        novel.close();
        moby_dick_file.close();

    } else if (atoi(argv[1]) == 2){

        numbers_file.open("numbers_to_sort.txt");
        numbers.open("numbers.txt");
        clock_t t = 0;

        // * SORT K NUMBERS IN TEXT FILE AND PRINT THEM IN NUMBERS TEXT FILE *

        K = atoi(argv[2]);

        long int added;
        Number temp;

        for (int a = 0; a < K; a++) {               // NUMBER OBJECTS PUSHED TO VECTOR
            numbers_file >> added;
            temp.set_number(added);
            numbers_array.push_back(temp);
        }

        //  *************** SORTING K NUMBERS *******************

        t = clock();

        quick_sort(numbers_array, 0, numbers_array.size()-1, 0, 0, false);

        t = clock() - t;

        //  ******************************************************

        for (int a = 0; a < numbers_array.size(); a++) numbers << numbers_array[a].get_order() << endl;
        cout << endl <<"Wow ! It only took " << float(t) / CLOCKS_PER_SEC << " seconds." << endl;


        numbers_file.close();
        numbers.close();

    }

    return 0;
}
