
#include <iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
using namespace std;

void insertionSort(int ar[], int size, double accumulator,double swaps,double compares, double *a,double*s,double*c) {
    int cur,pre;

    clock_t start, end;
    start = clock();
    for (int i = 1; i < size; i++) {
        cur = ar[i];//saves number at current
        pre = i - 1;
       
        while (pre >= 0 && ar[pre] > cur) {
            compares++;
            
            
            ar[pre + 1] = ar[pre];//puts a[0]<->a[1]
            
            --pre;
            ar[pre + 1] = cur;
            swaps++;
        }
        
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     accumulator+= time_taken;
   
     *a = accumulator;
     *s = swaps;
     *c = compares;
     
}

void maxHeap(int ar[], int size)
{
    for (int i = 1; i < size; i++){
        if (ar[i] > ar[(i - 1) / 2]){
            int cur = i;//currrent array index we are looking at

            while (ar[cur] > ar[(cur - 1) / 2]){

                swap(ar[cur], ar[(cur - 1) / 2]);
                //swap counter
                cur = (cur - 1) / 2;
            }
        }
    }
}

void heapSort(int ar[], int size, double swaps, double compares, double* s, double* c){
    //build max heap from array
    maxHeap(ar, size);

    for (int i = size - 1; i > 0; i--) {
        
        //delete the first elemenet
        swap(ar[0], ar[i]);
        swaps++;

        int next = 0;
        int current;

        do{
            current = (2 * next + 1);

             if (ar[current] < ar[current + 1] && current < (i - 1)) {
                compares++;
                  current++;
            }
           
            if (ar[next] < ar[current] && current < i) {
                swap(ar[next], ar[current]);
            }
            swaps++;
         next = current;

        } while (current < i);
    }
    *s = swaps;
    *c = compares;

}
void merge(int* arr, int first, int size, int mid,double swapCounter,double compareCounter,double* sc,double* cc){
    
    int j, k,i;;
    int Aux[10000];
    i = first;
    k = first;
    j = mid + 1;

    while (i <= mid && j <= size) {
        if (arr[i] < arr[j]) {
            compareCounter++;
            Aux[k] = arr[i];
            swapCounter++;
            k++;
            i++;
        }
        else {
            Aux[k] = arr[j];
            swapCounter++;
            k++;
            j++;
        }
    }
    while (i <= mid) {
        compareCounter++;
        Aux[k] = arr[i];
        swapCounter++;
        k++;
        i++;
    }
    while (j <= size) {
        compareCounter++;
        Aux[k] = arr[j];
        swapCounter++;
        k++;
        j++;
    }
    for (i = first; i < k; i++) {
        arr[i] = Aux[i];
        swapCounter++;
    }
    *sc += swapCounter;
    *cc += compareCounter;
}

void mergeSort(int* arr, int first, int size, double accumulator, double swaps, double compares, double numTempArrays, double* a, double* s, double* c, double* t)
{
    
    double swapCounter=0, compareCounter=0,sc,cc, storeSC=0,storeCC=0;
    int mid;
    clock_t start, end;
    start = clock();
    if (first < size) {
        
        mid = (first + size) / 2;
        //counter temp
        numTempArrays++;
        mergeSort(arr, first, mid,accumulator, swaps, compares, numTempArrays, a, s, c,t);
        mergeSort(arr, mid + 1, size, accumulator, swaps, compares, numTempArrays, a, s, c, t);

        merge(arr, first, size, mid,swapCounter, compareCounter, &sc, &cc);
        storeSC += sc;
        storeCC +=cc;
    }
    end = clock();
    double time = double(end-start) / double(CLOCKS_PER_SEC);
    accumulator += time;
    *a = accumulator;
    *s = storeSC;
    *c = storeCC;
    *t = numTempArrays;
       
}

int partition(int ar4[], int first, int size){

    int pivot = ar4[first];
    int e = size;
    for (int i = size; i > first; i--) {
        if (ar4[i] > pivot)
            swap(ar4[i], ar4[e--]);
        //swaps on condition
    }
     swap(ar4[first], ar4[e]);
   
     return e;
}

void quickSort(int ar4[], int first, int size ,double accumulator,double swaps,double compares, double* a, double* s,double*c)
{
    chrono::time_point<chrono::system_clock>go, stop;

    go = chrono::system_clock::now();
    int sort;
    if (first < size) {
        
        sort = partition(ar4,first,size);
        swaps++;
        compares++;
        
        quickSort(ar4, first, sort - 1,accumulator,swaps,compares,a,s,c);
        quickSort(ar4, sort + 1,size,accumulator,swaps,compares,a,s,c);
    } 
    double time = 0; 
    stop = chrono::system_clock::now();
    time=chrono::duration_cast<chrono::nanoseconds>(stop - go).count();

    accumulator += time;
    *a += accumulator;
    *s+= swaps;
    *c+= compares;
}




int main()
{
   
    int size = 10000;//10000;
    int ar[10000] = {};//original array
    int ar1[10000] = {};//array for insertion sort
    int ar2[10000] = {};//heapsort
    int ar3[10000] = {};//mergesort
    int ar4[10000] = {};//quicksort

    srand(time(NULL));

    for (int i = 0; i < size; i++) {//generates an array of rand nums
        ar[i] = (rand() % 1000000)+1;//1to1000000
        ar1[i] = ar[i];
        ar2[i] = ar[i];
        ar3[i] = ar[i];
        ar4[i] = ar[i];
    }
   
    double accumulator = 0, averageTime, swaps=0,compares=0,aveSwap,aveComps;
    double a,s,c,t,save=0, saveS=0,saveC=0,saveT=0;
    double numTempArrays=0;
   
    for (int i = 1; i <=100; i++) {
        //need to reset the array
        for (int i = 0; i < size; i++) {
            ar1[i] = ar[i];
        }
        insertionSort(ar1, size, accumulator, swaps,compares,&a,&s,&c);
       
        save += a;
        saveS+= s;
        saveC += c;
        
    }
    cout << "Insertion analysis of array size 10,000\n";
    cout << "total time it took for insert: " << save << endl;
    averageTime = save / 100.0;
    aveSwap = saveS / 100;
    aveComps = saveC / 100;
    cout << "Average time for Insertion Sort (100 times): " << averageTime<<" seconds" << endl;
    cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
    cout << "Average number swaps for Insertion Sort: " << aveSwap << endl;
   
    cout << "from insert" << ar1[23] << endl;

    //reset values for counters
    accumulator = 0;
    averageTime = 0;
    swaps = 0;
    compares = 0;
    aveSwap = 0;
    aveComps = 0;
    a = 0;
    s = 0;
    c = 0;
    save = 0;
    saveS = 0;
    saveC = 0;

    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < size; i++) {
            ar2[i] = ar[i];
        }
        clock_t start, end;
        start = clock();
        heapSort(ar2,size,swaps,compares,&s,&c);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        accumulator += time_taken;
        saveS += s;
        saveC += c;
        
    }
    cout << "-------------------------------------------------------" << endl;
    cout << "Heap Sort analysis of array size 10,000\n";
    cout << "total time it took for heap: " << accumulator << endl;
    averageTime = accumulator / 100.0;
    aveSwap = saveS / 100;
    aveComps = saveC / 100;
    cout << "Average time for Heap Sort (100 times): " << averageTime<<" seconds" << endl;
    cout << "Average number of comparisons for Heap Sort: " << aveComps << endl;
    cout << "Average number swaps for Heap Sort: " << aveSwap << endl;

    //reset values for counters
    accumulator = 0;
    averageTime = 0;
    swaps = 0;
    compares = 0;
    aveSwap = 0;
    aveComps = 0;
    a = 0;
    s = 0;
    c = 0;
    save = 0;
    saveS = 0;
    saveC = 0;
    //double t, temp=0;

    for (int i = 0; i < 100; i++) {
        //need to reset the array
        for (int i = 0; i < size; i++) {
            ar3[i] = ar[i];
        }

        
        mergeSort(ar3, 0, size - 1, accumulator, swaps, compares,numTempArrays, &a, &s, &c,&t);
        save += a;
        saveS += s;
        saveC += c;
        saveT += t;
        

        //cout << "here2" << endl;
        
    }

    cout << "-------------------------------------------------------" << endl;
    cout << "Merge Sort analysis of array size 10,000\n";
    cout << "total time it took for merge: " << save << endl;
    averageTime = save / 100.0;
    aveSwap = saveS / 100;
    aveComps = saveC / 100;
    cout << "Average time for Merge Sort (100 times): " << averageTime <<" Seconds" << endl;
    cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
    cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
    cout << "Number of ""temparary"" arrays:" << saveT << endl;

    //reset values for counters
    accumulator = 0;
    averageTime = 0;
    swaps = 0;
    compares = 0;
    aveSwap = 0;
    aveComps = 0;
    a = 0;
    s = 0;
    c = 0;
    save = 0;
    saveS = 0;
    saveC = 0;
    

    for (int i = 0; i < 100; i++) {
        //need to reset the array
        for (int i = 0; i < size; i++) {
            ar4[i] = ar[i];
        }
     
        quickSort(ar4, 0, size - 1,accumulator,swaps,compares,&a,&s,&c);
        save += a;
        saveS += s;
        saveC += c;
        
    }

    cout << "-------------------------------------------------------" << endl;
    cout << "Quick Sort analysis of array size 10,000\n";
    cout << "total time it took for quick sort: " << save << endl;
    averageTime = save / 100.0;
    aveSwap = saveS / 100;
    aveComps = saveC / 100;
    cout << "Average time for quick Sort (100 times): " << averageTime <<" nanoseconds" << endl;
    cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
    cout << "Average number swaps for quick Sort: " << aveSwap << endl;

    cout <<"from quicksort "<< ar4[23] << endl;

    
    //===========================================16=====================================
        
        int q2[16] = {};
        int q2IS[16] = {};
        int q2HS[16] = {};
        int q2MS[16] = {};
        int q2QS[16] = {};

        size = 16;
        for (int i = 0; i < size; i++) {
            q2[i] = (rand() % 1000) + 1;
            q2IS[i] = q2[i];
            q2HS[i] = q2[i];
            q2MS[i] = q2[i];
            q2QS[i] = q2[i];
        }

            for (int i = 1; i <= 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2IS[i] = q2[i];
                }
                insertionSort(q2IS, size, accumulator, swaps, compares, &a, &s, &c);

                save += a;
                saveS += s;
                saveC += c;
                
            }
            cout << "---------------------------------------------------------------" << endl;
            cout << "Insertion analysis of array size 16\n";
            cout << "total time it took for insert: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Insertion Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
            cout << "Average number swaps for Insertion Sort: " << aveSwap << endl; 

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                for (int i = 0; i < size; i++) {
                    q2HS[i] = q2[i];
                }
                clock_t start, end;
                start = clock();
                heapSort(q2HS, size, swaps, compares, &s, &c);
                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                accumulator += time_taken;
                saveS += s;
                saveC += c;

            }
            cout << "-------------------------------------------------------" << endl;
            cout << "Heap Sort analysis of array size 16\n";
            cout << "total time it took for heap: " << accumulator << endl;
            averageTime = accumulator / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Heap Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Heap Sort: " << aveComps << endl;
            cout << "Average number swaps for Heap Sort: " << aveSwap << endl;     

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;
            

            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2MS[i] = q2[i];
                }


                mergeSort(q2MS, 0, size - 1, accumulator, swaps, compares, numTempArrays, &a, &s, &c, &t);
                save += a;
                saveS += s;
                saveC += c;
                saveT += t;    

            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Merge Sort analysis of array size 16\n";
            cout << "total time it took for merge: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Merge Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
            cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
            cout << "Number of ""temparary"" arrays:" << saveT << endl;


            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;


            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2QS[i] = q2[i];
                }

                quickSort(q2QS, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
                save += a;
                saveS += s;
                saveC += c;

            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Quick Sort analysis of array size 16\n";
            cout << "total time it took for quick sort: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for quick Sort (100 times): " << averageTime<<" Nanoseconds" << endl;
            cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
            cout << "Average number swaps for quick Sort: " << aveSwap << endl;

           

        //==============================32===================================================
            int q232[32] = {};
            int q2IS32[32] = {};
            int q2HS32[32] = {};
            int q2MS32[32] = {};
            int q2QS32[32] = {};

            size = 32;
            for (int i = 0; i < size; i++) {
                q232[i] = (rand() % 1000) + 1;
                q2IS32[i] = q232[i];
                q2HS32[i] = q232[i];
                q2MS32[i] = q232[i];
                q2QS32[i] = q232[i];

            }

            for (int i = 1; i <= 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2IS32[i] = q232[i];
                }
                insertionSort(q2IS32, size, accumulator, swaps, compares, &a, &s, &c);

                save += a;
                saveS += s;
                saveC += c;
                
            }
            cout << "---------------------------------------------------------------" << endl;
            cout << "Insertion analysis of array size 32\n";
            cout << "total time it took for insert: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Insertion Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
            cout << "Average number swaps for Insertion Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                for (int i = 0; i < size; i++) {
                    q2HS32[i] = q232[i];
                }
                clock_t start, end;
                start = clock();
                heapSort(q2HS32, size, swaps, compares, &s, &c);
                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                accumulator += time_taken;
                saveS += s;
                saveC += c;

            }
            cout << "-------------------------------------------------------" << endl;
            cout << "Heap Sort analysis of array size 32\n";
            cout << "total time it took for heap: " << accumulator << endl;
            averageTime = accumulator / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Heap Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Heap Sort: " << aveComps << endl;
            cout << "Average number swaps for Heap Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2MS32[i] = q232[i];
                }


                mergeSort(q2MS32, 0, size - 1, accumulator, swaps, compares, numTempArrays, &a, &s, &c, &t);
                save += a;
                saveS += s;
                saveC += c;
                saveT += t;
            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Merge Sort analysis of array size 32\n";
            cout << "total time it took for merge: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Merge Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
            cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
            cout << "Number of ""temparary"" arrays:" << saveT << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;


            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2QS32[i] = q232[i];
                }

                quickSort(ar4, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
                save += a;
                saveS += s;
                saveC += c;

            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Quick Sort analysis of array size 32\n";
            cout << "total time it took for quick sort: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for quick Sort (100 times): " << averageTime << " Nanoseconds" << endl;
            cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
            cout << "Average number swaps for quick Sort: " << aveSwap << endl;

        //=============================64===============================
            int q264[64] = {};
            int q2IS64[64] = {};
            int q2HS64[64] = {};
            int q2MS64[64] = {};
            int q2QS64[64] = {};

            size = 64;
            for (int i = 0; i < size; i++) {
                q264[i] = (rand() % 1000) + 1;
                q2IS64[i] = q264[i];
                q2HS64[i] = q264[i];
                q2MS64[i] = q264[i];
                q2QS64[i] = q264[i];

            }

            for (int i = 1; i <= 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2IS64[i] = q264[i];
                }
                insertionSort(q2IS64, size, accumulator, swaps, compares, &a, &s, &c);

                save += a;
                saveS += s;
                saveC += c;
             
            }
            cout << "---------------------------------------------------------------" << endl;
            cout << "Insertion analysis of array size 64\n";
            cout << "total time it took for insert: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Insertion Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
            cout << "Average number swaps for Insertion Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                for (int i = 0; i < size; i++) {
                    q2HS64[i] = q264[i];
                }
                clock_t start, end;
                start = clock();
                heapSort(q2HS64, size, swaps, compares, &s, &c);
                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                accumulator += time_taken;
                saveS += s;
                saveC += c;

            }
            cout << "-------------------------------------------------------" << endl;
            cout << "Heap Sort analysis of array size 64\n";
            cout << "total time it took for heap: " << accumulator << endl;
            averageTime = accumulator / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Heap Sort (100 times): " << averageTime  << endl;
            cout << "Average number of comparisons for Heap Sort: " << aveComps << endl;
            cout << "Average number swaps for Heap Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;
            //double t, temp=0;

            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2MS64[i] = q264[i];
                }


                mergeSort(q2MS64, 0, size - 1, accumulator, swaps, compares, numTempArrays, &a, &s, &c, &t);
                save += a;
                saveS += s;
                saveC += c;
                saveT += t;

            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Merge Sort analysis of array size 64\n";
            cout << "total time it took for merge: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Merge Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
            cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
            cout << "Number of ""temparary"" arrays:" << saveT << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;


            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2QS64[i] = q264[i];
                }

                quickSort(q2QS64, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
                save += a;
                saveS += s;
                saveC += c;

            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Quick Sort analysis of array size 64\n";
            cout << "total time it took for quick sort: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for quick Sort (100 times): " << averageTime << " Nanoseconds" << endl;
            cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
            cout << "Average number swaps for quick Sort: " << aveSwap << endl;

            //=======================128=======================================================
            int q2128[128] = {};
            int q2IS128[128] = {};
            int q2HS128[128] = {};
            int q2MS128[128] = {};
            int q2QS128[128] = {};

            size = 128;
            for (int i = 0; i < size; i++) {
                q2128[i] = (rand() % 1000) + 1;
                q2IS128[i] = q2128[i];
                q2HS128[i] = q2128[i];
                q2MS128[i] = q2128[i];
                q2QS128[i] = q2128[i];

            }

            for (int i = 1; i <= 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2IS128[i] = q2128[i];
                }
                insertionSort(q2IS128, size, accumulator, swaps, compares, &a, &s, &c);

                save += a;
                saveS += s;
                saveC += c;
                //cout << c << endl;
            }
            cout << "---------------------------------------------------------------" << endl;
            cout << "Insertion analysis of array size 128\n";
            cout << "total time it took for insert: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Insertion Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
            cout << "Average number swaps for Insertion Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                for (int i = 0; i < size; i++) {
                    q2HS128[i] = q2128[i];
                }
                clock_t start, end;
                start = clock();
                heapSort(q2HS128, size, swaps, compares, &s, &c);
                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                accumulator += time_taken;
                saveS += s;
                saveC += c;

            }
            cout << "-------------------------------------------------------" << endl;
            cout << "Heap Sort analysis of array size 128\n";
            cout << "total time it took for heap: " << accumulator << endl;
            averageTime = accumulator / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Heap Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Heap Sort: " << aveComps << endl;
            cout << "Average number swaps for Heap Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2MS128[i] = q2128[i];
                }


                mergeSort(q2MS128, 0, size - 1, accumulator, swaps, compares, numTempArrays, &a, &s, &c, &t);
                save += a;
                saveS += s;
                saveC += c;
                saveT += t;
            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Merge Sort analysis of array size 128\n";
            cout << "total time it took for merge: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Merge Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
            cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
            cout << "Number of ""temparary"" arrays:" << saveT << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;


            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2QS128[i] = q2128[i];
                }

                quickSort(q2128, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
                save += a;
                saveS += s;
                saveC += c;

            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Quick Sort analysis of array size 128\n";
            cout << "total time it took for quick sort: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for quick Sort (100 times): " << averageTime << " Nanoseconds" << endl;
            cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
            cout << "Average number swaps for quick Sort: " << aveSwap << endl;

            //==========================256=======================================
            int q2256[256] = {};
            int q2IS256[256] = {};
            int q2HS256[256] = {};
            int q2MS256[256] = {};
            int q2QS256[256] = {};

            size = 256;
            for (int i = 0; i < size; i++) {
                q2256[i] = (rand() % 1000) + 1;
                q2IS256[i] = q2256[i];
                q2HS256[i] = q2256[i];
                q2MS256[i] = q2256[i];
                q2QS256[i] = q2256[i];

            }

            for (int i = 1; i <= 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2IS256[i] = q2256[i];
                }
                insertionSort(q2IS256, size, accumulator, swaps, compares, &a, &s, &c);

                save += a;
                saveS += s;
                saveC += c;
              
            }
            cout << "---------------------------------------------------------------" << endl;
            cout << "Insertion analysis of array size 256\n";
            cout << "total time it took for insert: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Insertion Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
            cout << "Average number swaps for Insertion Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                for (int i = 0; i < size; i++) {
                    q2HS256[i] = q2HS256[i];
                }
                clock_t start, end;
                start = clock();
                heapSort(q2HS256, size, swaps, compares, &s, &c);
                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                accumulator += time_taken;
                saveS += s;
                saveC += c;

            }
            cout << "-------------------------------------------------------" << endl;
            cout << "Heap Sort analysis of array size 256\n";
            cout << "total time it took for heap: " << accumulator << endl;
            averageTime = accumulator / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Heap Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Heap Sort: " << aveComps << endl;
            cout << "Average number swaps for Heap Sort: " << aveSwap << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;
 
            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2MS256[i] = q2256[i];
                }

                mergeSort(q2MS256, 0, size - 1, accumulator, swaps, compares, numTempArrays, &a, &s, &c, &t);
                save += a;
                saveS += s;
                saveC += c;
                saveT += t;
            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Merge Sort analysis of array size 256\n";
            cout << "total time it took for merge: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Merge Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
            cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
            cout << "Number of ""temparary"" arrays:" << saveT << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

            for (int i = 0; i < 100; i++) {
                //need to reset the array
                for (int i = 0; i < size; i++) {
                    q2QS256[i] = q2256[i];
                }

                quickSort(q2QS256, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
                save += a;
                saveS += s;
                saveC += c;
            }

            cout << "-------------------------------------------------------" << endl;
            cout << "Quick Sort analysis of array size 256\n";
            cout << "total time it took for quick sort: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for quick Sort (100 times): " << averageTime << " Nanoseconds" << endl;
            cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
            cout << "Average number swaps for quick Sort: " << aveSwap << endl;

            //=================================================final array===========================================
            //run insert then run quick and merge sort
            size = 10000;
            int finAr[10000] = {};

            for (int i = 0; i < size; i++) {
                finAr[i] = ar[i];
             }
                //need to reset the array
                
                insertionSort(finAr, size, accumulator, swaps, compares, &a, &s, &c);

                save += a;
                saveS += s;
                saveC += c;

         
            cout << "---------------------------------------------------------------" << endl;
            cout << "Insertion analysis of array size finAR\n";
            cout << "total time it took for insert: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Insertion Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Insertion Sort: " << aveComps << endl;
            cout << "Average number swaps for Insertion Sort: " << aveSwap << endl;

           

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

           
                //need to reset the array
                
                mergeSort(finAr, 0, size - 1, accumulator, swaps, compares, numTempArrays, &a, &s, &c, &t);
                save += a;
                saveS += s;
                saveC += c;
                saveT += t;
            

            cout << "-------------------------------------------------------" << endl;
            cout << "Merge Sort analysis of array size finAr\n";
            cout << "total time it took for merge: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for Merge Sort (100 times): " << averageTime << endl;
            cout << "Average number of comparisons for Merge Sort: " << aveComps << endl;
            cout << "Average number swaps for Merge Sort: " << aveSwap << endl;
            cout << "Number of ""temparary"" arrays:" << saveT << endl;
            cout << "passes merge sort" << endl;

            //reset values for counters
            accumulator = 0;
            averageTime = 0;
            swaps = 0;
            compares = 0;
            aveSwap = 0;
            aveComps = 0;
            a = 0;
            s = 0;
            c = 0;
            save = 0;
            saveS = 0;
            saveC = 0;

                //quickSort(finAr, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
                
            try {
               // quickSort(finAr, 0, size - 1, accumulator, swaps, compares, &a, &s, &c);
            }
            catch (invalid_argument& err) {

                abort();
                throw invalid_argument("didn't pass quick sort");
            }
           // cout << "passes quick sort " << endl;

               
                cout << "passes quick sort " << endl;
                save += a;
                saveS += s;
                saveC += c;
            

            cout << "-------------------------------------------------------" << endl;
            cout << "Quick Sort analysis of array size finAr\n";
            cout << "total time it took for quick sort: " << save << endl;
            averageTime = save / 100.0;
            aveSwap = saveS / 100;
            aveComps = saveC / 100;
            cout << "Average time for quick Sort (100 times): " << averageTime << " Nanoseconds" << endl;
            cout << "Average number of comparisons for quick Sort: " << aveComps << endl;
            cout << "Average number swaps for quick Sort: " << aveSwap << endl;

           

            //run insert
            /*for (int i = 0; i < size; i++) {
                finAr[i] = ar[i];
            }
            insertionSort(finAr, size, accumulator, swaps, compares, &a, &s, &c);
            cout << "passes insertion " << endl;
           /* for (int i = 0; i < size; i++) {
                finAr[i] = ar[i];
            }
            */
           
            /*for (int i = 0; i < size; i++) {
                finAr[i] = ar[i];
            }
            */
           

    return 0;
}


