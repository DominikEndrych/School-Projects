#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>
#include <pthread.h>
#include <vector>
#include <iostream>

#define TYPE int

using namespace std;

// class for one part of task
class TaskPart
{
public:
    int m_id;                 // user thread identification
    int m_from, m_length;     // data range
    TYPE *m_data;             // array
    TYPE m_max;               // result

	TaskPart(){m_id = 0; m_from = 0; m_length = 0; m_data = nullptr; m_max = 0;}

    TaskPart( int t_myid, int t_from, int t_length, TYPE *t_data ) :
        m_id( t_myid ), m_from( t_from ), m_length( t_length ), m_data( t_data ) {}

    TYPE get_result() { return m_max; }

    // function search_max search the largest number in part of array
    // from the left (included) up to the right element
    TYPE search_max()
    {
        TYPE l_max = m_data[ m_from ];
        for ( int i = 1; i < m_length; i++ )
            if ( l_max < m_data[ m_from + i ] )
                l_max = m_data[ m_from + i ];
        return l_max;
    }

    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void insertionSort()
    {
        //iStart - index pro zacatek trizeni
        //iStop - index pro konec trizeni

        int i, key, j;
        for (i = m_from + 1 ; i < m_from + m_length /*iStop + 1*/ ; i++)
        {
            key = m_data[i];
            j = i - 1;

            /* Move elements of arr[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
            while (j >= m_from && m_data[j] > key)
            {
                m_data[j + 1] = m_data[j];
                j = j - 1;
            }
            m_data[j + 1] = key;
        }
    }

    void selectionSort()
    {
        //iStart - od ktereho indexu tridit
        //iStop - po ktery index tridit

        int i, j, min_idx;

        // One by one move boundary of unsorted subarray
        for (i = m_from; i < m_from + m_length /*iStop*/; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i+1; j < m_from + m_length /*iStop+1*/; j++)
            if (m_data[j] < m_data[min_idx])
                min_idx = j;

            // Swap the found minimum element with the first element
            this->swap(&m_data[min_idx], &m_data[i]);
        }
    }

    void bubbleSort(int arr[], int iStart, int iStop)
    {
        for(int i = 0; i < m_length; i++){
            for(int j = m_from; j < m_from + m_length-i-1; j++)
                if(m_data[j] > m_data[j+1])
                    this->swap(&m_data[j], &m_data[j+1]);
        }
    }


};

// Thread will search the largest element in array
// from element arg->m_from with length of arg->m_length.
// Result will be stored to arg->m_max.
void *my_thread( void *t_void_arg )
{
    TaskPart *lp_task = ( TaskPart * ) t_void_arg;

    printf( "Thread %d started from %d with length %d...\n",
        lp_task->m_id, lp_task->m_from, lp_task->m_length );

    lp_task->m_max = lp_task->search_max();

    printf( "Found maximum in thread %d is %d\n", lp_task->m_id, lp_task->m_max );

    return NULL;
}

void *sortArray( void *t_void_arg )
{
    TaskPart *lp_task = ( TaskPart * ) t_void_arg;

    lp_task->insertionSort();

    return NULL;
}

// Time interval between two measurements converted to ms
int timeval_diff_to_ms( timeval *t_before, timeval *t_after )
{
    timeval l_res;
    timersub( t_after, t_before, &l_res );
    return 1000 * l_res.tv_sec + l_res.tv_usec / 1000;
}



void mergeTwoArrays(vector<int> arr1, /*int n1,*/  vector<int> arr2, /*int n2,*/ vector<int> &result){

    int i = 0;  //index for arr1
    int j = 0;  //index for arr2
    int k = 0;  //index for result

    int n1 = arr1.size();
    int n2 = arr2.size();

    //vysledkovy vektor musime promazat
    result.clear();

    while(i < n1 && j < n2){
        if(arr1[i] < arr2[j]){
            result.push_back(arr1[i]);
            //result = arr1[i];
            i++;
            k++;
        }
        else{
            result.push_back(arr2[j]);
            //result[k] = arr2[j];
            j++;
            k++;
        }
    }
    while(i < n1)
        result.push_back(arr1[i++]);
    while(j < n2)
        result.push_back(arr2[j++]);
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void printVector(vector <int> vec)
{
    for(unsigned int i = 0; i < vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

#define LENGTH_LIMIT 10000000

int main( int t_na, char **t_arg )
{
    printf( "\nSorted array:\n" );

    int n = 10;
    int l_my_array[] = {1,5,4,7,2,10,8,3,6,9};

    int vlaken = atoi( t_arg[ 1 ] );
    int part, lastPart;

    if(n%vlaken == 0){
        part = n/vlaken;
        lastPart = part;
    }
    else{
        part = n/vlaken;
        lastPart = n - (part * (vlaken-1));
    }

    //rozdeleni intervalu
    TaskPart parts[vlaken];
    for(int i = 0; i < vlaken; i++){
        if(i+1 == vlaken){
            parts[i] = TaskPart(i+1, i*part, lastPart, l_my_array);
        }
        else{
            parts[i] = TaskPart(i+1, i*part, part, l_my_array);
        }
    }

    pthread_t threads[vlaken];
    for(int i = 0; i < vlaken; i++){
        pthread_create(&threads[i], NULL, sortArray, &parts[i]);
    }
    for(int i = 0; i < vlaken; i++){
        pthread_join(threads[i], NULL);
    }

	printArray(l_my_array, n);

    vector<int> pom[vlaken];
    vector<int> finalVector;

    for(int t = 0; t < vlaken; t++){

        //posledni interval
        if(t + 1 == vlaken){
            for(int j = 0; j < lastPart; j++){
                pom[t].push_back(l_my_array[ (t*part) + j]);
            }
        }
        //vsechny intervaly krome posledniho
        else{
            for(int i = 0; i < part; i++){
                pom[t].push_back(l_my_array[ (t*part) + i]);
            }
        }

    }

    for(int i = 0; i < vlaken; i++){
        //finalVector se preda nejprve jako spojovane pole a pak jako pole vysledku
        //ve funkci se prepisuje jenom posledni parametr, ostatni jsou kopie
        mergeTwoArrays(finalVector, pom[i], finalVector);
    }

    printVector(finalVector);

}
