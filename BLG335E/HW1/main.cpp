/*
 * Analysis of Algorithms I - Homework I
 * Student Name: Can Yılmaz Altıniğne
 * Student ID : 150130132
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// WAREHOUSES
// COORDINATES, ID AND DISTANCE FROM CENTER IN THIS CLASS

class Warehouse {
public:
    long int id, xCoor, yCoor;
    double distance_to_center;
    
    bool operator < (Warehouse& other){
        return distance_to_center < other.distance_to_center;
    }
    
    bool operator > (Warehouse& other){
        return distance_to_center > other.distance_to_center;
    }
};

// --------------------------------------------------------------


// CENTER POINT
// COORDINATES AND FUNCTION THAT CALCULATES A WAREHOUSE'S DISTANCE FROM THIS POINT

class Center_Point {
public:
    long int xCoor, yCoor;
    
    double calculate_distance(Warehouse& x){
        return std::sqrt(std::pow((xCoor-x.xCoor), 2) + std::pow((yCoor-x.yCoor), 2));
    }
};

// --------------------------------------------------------------------------------------

// SORTING ALGORITHMS CLASS

class Algorithms {
    
    void merge(Warehouse * arr, long int p, long int q, long int r){
        long int n1 = q-p+1;
        long int n2 = r-q;
        
        Warehouse * array_left = new Warehouse[n1+1];           // LEFT PART
        Warehouse * array_right = new Warehouse[n2+1];          // RIGHT PART
        Warehouse temp;
        temp.distance_to_center = 250000;                       // NO DISTANCE WOULD BE HIGHER THAN THIS VALUE CONSIDER THIS AS INFINITE
        
        for (long int i = 0; i < n1; i++) {         // APPENDING THE LEFT SIDE
            array_left[i] = arr[p+i];
        }
        
        array_left[n1] = temp;
        
        for (long int i = 0; i < n1; i++) {                 // APPENDING THE RIGHT SIDE
            array_right[i] = arr[q+i+1];
        }
        
        array_right[n2] = temp;
        
        int x = 0, y = 0;
        
        for (long int i = p; i < r+1; i++) {                                // FORM LEFT AND RIGHT MERGING HAPPENS HERE
            if(array_left[x] < array_right[y]) arr[i] = array_left[x++];
            else arr[i] = array_right[y++];
        }
        
        delete [] array_left;
        delete [] array_right;
    }
    
public:
    
    void insertion_sort(Warehouse * arr, long int length){
        
        Warehouse temp;
        int j;
        
        if (length == 1) return;
        
        for (int i = 1; i < length; i++) {                  // TRAVERSE ALL ELEMENTS EXCEPT FIRST BECAUSE THE FIRST ELEMENT ALREADY SORTED
            
            temp = arr[i];
            j = i;
            
            while (arr[j-1] > temp && j > 0) {              // BIGGER NUMBERS THAN CURRENT ELEMENT SHIFTS RIGHT
                arr[j] = arr[j-1];
                j -= 1;
            }
            
            arr[j] = temp;                                  // UNTIL THERE ARE NO BIGGER ELEMENTS THAN CURRENT ELEMENT
        }
    }
    
    void merge_sort(Warehouse * arr, long int p, long int r){       // DIVIDE THE ARRAY BY TWO UNTIL THERE ARE N TIMES 1 ELEMENTS
        long int q;
        
        if (p < r) {
            q = (p+r) / 2;                                          // MERGE THEM SEQUENTIALLY (1'S 2'S 4'S 8'S ........ N'S)
            merge_sort(arr, p, q);
            merge_sort(arr, q+1, r);
            merge(arr, p, q, r);
        }
    }
    
    void linear_search(Warehouse * arr, long int length){
        
        static int where_to_put = 0;                    // FROM 0 TO K NUMBERS WILL BE SORTED
        Warehouse temp = arr[where_to_put];             // START FROM 0
        int temp_order = where_to_put;
        
        for (int i = where_to_put + 1; i < length; i++) {       // START FROM UNSORTED ELEMENT
            if (arr[i] < temp) {
                temp = arr[i];
                temp_order = i;                         // TRAVERSE ALL ARRAY
            }
        }
        
        arr[temp_order] = arr[where_to_put];                // SWAP THE SMALLEST ELEMENT AND FIRST ELEMENT OF ARRAY
        arr[where_to_put++] = temp;                         // THEN REPEAT THESE STEPS FOR SECOND, THIRD, FOURTH .... KTH
    }
};

// -----------------------------------------------------------

int main(int argc, const char * argv[]) {
    
    Center_Point center;
    Algorithms algorithms;
    std::ifstream input_file;
    std::ofstream output_file;
    std::clock_t t = 0;
    
    input_file.open("warehouselocations.txt");
    output_file.open("output.txt");
    
    long int N = atol(argv[1]);
    long int K = atol(argv[2]);
    std::string algorithm_type = argv[3];
    center.xCoor = atol(argv[4]);
    center.yCoor = atol(argv[5]);
    
    Warehouse * warehouse_list = new Warehouse[N];              // NTH SIZED ARRAY
    
    for (int z = 0; z < N; z++) {
        input_file >> warehouse_list[z].id  >> warehouse_list[z].xCoor  >> warehouse_list[z].yCoor;         // GET N WAREHOUSES
        warehouse_list[z].distance_to_center = center.calculate_distance(warehouse_list[z]);                // CALCULATE THEIR DISTANCE TO CENTER
    }
    
    if (algorithm_type == "MS" || algorithm_type == "ms") {                 // ALGORITHMS WORK HERE
        t = clock();
        algorithms.merge_sort(warehouse_list, 0, N-1);
        t = clock() - t;
        
    } else if (algorithm_type == "IS" || algorithm_type == "is"){
        t = clock();
        algorithms.insertion_sort(warehouse_list, N);
        t = clock() - t;
        
    } else if (algorithm_type == "LS" || algorithm_type == "ls"){
        t = clock();
        for (int q = 0; q < K; q++) {
            algorithms.linear_search(warehouse_list, N);
        }
        t = clock() - t;
        
    } else {
        std::cout << "No algorithm provided !";
    }
    
    for (int w = 0; w < K; w++) {               // PRINT THEM IN FILE
        output_file << warehouse_list[w].id << "\t" << warehouse_list[w].xCoor << "\t" << warehouse_list[w].yCoor << "\t" << warehouse_list[w].distance_to_center << std::endl;
    }
    
    std::cout << std::endl <<"Wow ! It only took " << float(t) / CLOCKS_PER_SEC << " seconds." << std::endl;
    
    input_file.close();
    output_file.close();
    delete [] warehouse_list;
    
    return 0;
}
