#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <string>
#include <cctype>

//Global Array length variable
int LEN = 0;

/* creates random integer */
int randomInt()
{
	return rand() % 1000;
}

///////////////////////////////////////////////
/// 					Array Methods   							///
///////////////////////////////////////////////

/* sorts array in ascending order */
void sortAscending(int arr[])
{
	int i;
	for(i = 0; i < LEN; i++)
	{
		arr[i] = i +1;
	}
}

/* sorts array in descending order */
void sortDescending(int arr[])
{
	int i;
	int count = 0;
	for(i = LEN; i > 0; i--)
	{
		arr[count] = i;
		count++;
	}
}

/* gives entire array identical values */
void identical(int arr[])
{
	int value = randomInt();
	int i;
	for(i = 0; i < LEN; i++)
	{
		arr[i] = value;
	}
}

/* randomly generated array */
void random(int arr[])
{
	int i;
	for(i = 0; i < LEN; i++)
	{
		arr[i] = randomInt();
	}
}

/* Validates that the correct type is entered */
template <typename T>
T checkInput(T test, std::string  msg) {
    while(!(std::cin >> test)){
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize> :: max(),'\n'); // Flush out the buffer
		std::cout << msg; // Display the error message
	}
    std::cin.clear(); // Clears buffer in case user enters more variables
    std::cin.ignore(std::numeric_limits <std::streamsize> :: max(),'\n'); // Flush out the buffer
    return test; // Returns the correct type
}
///////////////////////////////////////////////
/// 					Sorting Methods   					  ///
///////////////////////////////////////////////


/* class  consists of all of the sorting algorithms */
template <class T>
class Sort
{
	private:

		int length;
		int partition(T arr[], int left, int right);
		int medianOfThree(T arr[], int start, int end);
		void insertionSortQS(T arr[], int start, int end);
		void merge(T arr[], int first, int mid, int last);
		void heapify(T arr[],int length, T root);
		void swap(T* a, T* b);

	public:
		//Constd::string uctor & Destd::string uctor
		Sort();
		~Sort();
		void setLength(int n);
		int getLength();


		void InsertionSort(T arr[]);
		void QuickSortRight(T arr[], int left, int right);
		void QuickSortMedian(T arr[], int left, int right);
		void QuickSortInsertion(T arr[], int start, int end);
		void MergeSort(T arr[], int first, int last);
		void HeapSort(T arr[], int length);

};

//Constd::string uctor & Deconstd::string uctor
template <class T>
Sort<T> :: Sort(){}

template <class T>
Sort<T> :: ~Sort(){}

/* sets legngth of array */
template <class T>
void Sort<T> :: setLength(int n)
{
	length = n;
}
/* sets legngth of array */
template <class T>
int Sort<T> :: getLength()
{
	return length;
}

/* swap numbers */
template <class T>
void Sort<T> :: swap(T* a, T* b)
		{
			T temp = *a;
			*a = *b;
			*b = temp;
		}
///////////////////////////////////////////////
/// 					Intsertion Sort  							///
///////////////////////////////////////////////

template <class T>
void Sort<T> :: InsertionSort(T arr[])
{
	int i, key, j;
	for(i = 1; i < length; i++)
	{
		/* Checks to see if all elements before j to
		see if they are in the correct order */
		key = arr[i];
		j = i-1;

		while(j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j -= 1;
		}
		arr[j+1] = key;
	}
}

// InsertionSort operation for quicSort
template <class T>
void Sort<T> :: insertionSortQS(T arr[], int start, int end)
{
	int i, key, j;
	for(i = start + 1; i < end; i++)
	{
		key = arr[i];
		j = i-1;

		while(j > 0 && arr[j-1] > key)
		{
			arr[j+1] = arr[j];
			j -= 1;

		}
		arr[j+1] = key;
	}
}


///////////////////////////////////////////////
/// 					Quick Sort       							///
///////////////////////////////////////////////

/* pivot on right most element */
template <class T>
int Sort<T> :: partition(T arr[], int left, int right)
{
	int pivot = arr[right];
	int i = (left - 1);
	int j;

	/* If the array item is less than pivot it goes left else stays
	 right */
	for(j = left; j <= right-1; j++)
	{
			if(arr[j] <= pivot)
			{
				i++;
				swap(&arr[i], &arr[j]);
			}
	}

	swap(&arr[i + 1], &arr[right]);
	return (i + 1);
}

/* pivot on the median of three elements */
template <class T>
int Sort <T> :: medianOfThree(T arr[], int left, int right)
{
	int mid = (left + right) / 2;

	// finds an array of 3 items that compose median and sorts them

	if(arr[right] < arr[left])
	{
		swap(&left, &right);
	}
	if(arr[mid] < arr[left])
	{
		swap(&mid, &left);
	}
	if(arr[right] < arr[mid])
	{
		swap(&right, &mid);
	}
	swap(&arr[mid], &arr[left]);
	return partition(arr, left, right);
}

/* right pivot quicksort */
template <class T>
void Sort<T> :: QuickSortRight(T arr[], int start, int end)
{
	if(start < end)
	{
		int pivot = partition(arr, start, end);
		QuickSortRight(arr, start, pivot - 1);
		QuickSortRight(arr, pivot + 1, end);
	}
}

/* right pivot quicksort with insertion sort combined together */
template <class T>
void Sort<T> :: QuickSortInsertion(T arr[], int start, int end)
{
	if(start < end)
	{
		if((end - start) <= 16)
		{
			QuickSortInsertion(arr, start, end + 1);
		}
		else
		{
			int pivot = partition(arr, start, end);
			QuickSortRight(arr, start, pivot - 1);
			QuickSortRight(arr, pivot + 1, end);
		}
	}
}

/* quicksort with median of three elements as pivot */
template <class T>
void Sort<T> :: QuickSortMedian(T arr[], int start, int end)
{
	if(start < end)
	{
		int pivot = medianOfThree(arr, start, end);
		QuickSortRight(arr, start, pivot - 1);
		QuickSortRight(arr, pivot + 1, end);
	}
}


///////////////////////////////////////////////
/// 					Merge Sort       							///
///////////////////////////////////////////////

/* merges arrays */
template <class T>
void Sort<T> :: merge(T arr[], int first, int mid, int last)
{
	int i;
	int leftL = mid - first + 1;
	int rightL = last - mid;

	T leftArray[leftL]; // Creates the left array
	T rightArray[rightL]; // Creates the right array

	for(i = 0; i < leftL; i++)
	{
		leftArray[i] = arr[first + i];
	}
	for(i = 0; i < rightL; i++)
	{
		rightArray[i] = arr[mid + i + 1];
	}

	int cnt;
	int left = 0;
	int right = 0;


	/* Merge the temp arrays back into the original array */
	for(cnt = first; left < leftL && right < rightL; cnt++)
	{
		if(leftArray[left] <= rightArray[right])
		{
			arr[cnt] = leftArray[left];
			left++;
		}
		else
		{
			arr[cnt] = rightArray[right];
			right++;
		}
	}
	/* Copying elemets from left[] to array[] */
	for(i = left; i < leftL; i++)
	{
		arr[cnt] = leftArray[i];
		cnt++;
	}
	/* Copying elemets from right[] to array[] */
	for(i = right; i < rightL; i++)
	{
		arr[cnt] = rightArray[i];
		cnt++;
	}
}

/* Merge Sort */
template <class T>
void Sort<T> :: MergeSort(T arr[], int first, int last)
{
	if(first < last)
	{
		int mid = first + (last - first) / 2;

		/* Split and sort the array into two halves using the midpoint */
		MergeSort(arr, mid+1, last);
		merge(arr, first, mid, last);
	}
}

///////////////////////////////////////////////
/// 					Heap Sort       							///
///////////////////////////////////////////////

/* converts array into heap */
template <class T>
void Sort<T> :: heapify(T arr[], int length, T root)
{
	T largest = root;
	T leftChild = 2 * root + 1;
	T rightChild = 2 * root + 2;

	/*  Tests if left child is the potential largest node  */

	if (leftChild < length && arr[leftChild] > arr[largest])
	{
		largest = leftChild;
	}
	/*  Tests if right child is the potential largest node  */
	if(rightChild < LEN && arr[rightChild] > arr[largest])
	{
		largest = rightChild;
	}

	if(largest != root)
	{
		swap(&arr[root], &arr[largest]);
		heapify(arr, length, largest);
	}
}

template <class T>
void Sort<T> :: HeapSort(T arr[], int length)
{
	int i;
	for(i = length / 2 - 1; i >= 0; i--)
	{
		heapify(arr, length, i);
	}
// Swap the largest with the root
	for(i = length - 1; i >= 0; i--)
	{
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

///////////////////////////////////////////////
/// 					User Interface       					///
///////////////////////////////////////////////

template <class T>
class Interface : public Sort<T>
{
public:

	//calls methods

	inline void insertionSort(T arr[])
	{
		this->InsertionSort(arr);
	}

	inline void quickSortRight(T arr[])
	{
		int length = this->getLength();
		this->QuickSortRight(arr, 0, length-1);
	}

	inline void quickSortInsertion(T arr[])
	{
		int length = this->getLength();
		this->QuickSortInsertion(arr, 0, length-1);
	}

	inline void quickSortMedian(T arr[])
	{
		int length = this->getLength();
		this->QuickSortMedian(arr, 0, length-1);
	}

	inline void mergeSort(T arr[])
	{
		int length = this->getLength();
		this->MergeSort(arr, 0, length-1);
	}

	inline void heapSort(T arr[])
	{
		int length = this->getLength();
		this->HeapSort(arr, length);
	}

};

///////////////////////////////////////////////
/// 					Main      										///
///////////////////////////////////////////////

using std::cout;
using std::cin;
using std::cerr;

int main() {
    srand(time(0)); // Seeds the random number generator

    /* Delclaring and initializing main variables */
    Interface<int> object;
    clock_t stopwatch;
    int OPTION = 0, SORT = 0, test = 0;
    float runTime  = 0.00f;
    bool isRunning = true;
    char loopContinue  = ' ';
    std::string loop       = "";

    /* std::string ings used for user input */
    std::string  lengthError  = "Please enter an integer next time!: ";
    std::string  arrayInputError = "Integer must be between 1-4: ";
		std::string  sortingInputError = "Sort  must be between 1-4: ";
    std::string  sortedOrderSelectMessage =


										 "\n-- Array Options --"
                     "\n(1) Sorted - ascending"
                     "\n(2) Sorted - descending"
                     "\n(3) All the same value"
                     "\n(4) Random\n";

    std::string sortingSelectMsg    = "\n-- Sorting Options --"
                     "\n(1) Insertion sort"
                     "\n(2)Quicksort1: pivot is the right-most element"
                     "\n(3)Quicksort2: pivot is the right-most element, switches to Insertion Sort dependent on length of array"
                     "\n(4)Quicksort, pivot: median of three"
                     "\n(5)Mergesort"
                     "\n(6)Heapsort"
                     "\n(7)Suprise me : \n\n";

	  while (isRunning)
		{
			 /* Gets the LEN of the array */
			 cout << "\nEnter array length: \t"; // Asks the user to enter the desired length
			 LEN = checkInput(test, lengthError); // Checks for the correct type and stores user value
			 while (LEN < 0 || LEN == 0 || LEN >= INT_MAX)
			 {
			 	cerr << "That is not a valid length, enter a new length: "; //  error message
			  LEN = checkInput(test,lengthError);
			 }


		 		 /* Gets the  array Ordering option */
		 		 cout << sortedOrderSelectMessage;
		 		 OPTION = checkInput(test, arrayInputError);
		 		 while (OPTION < 0 || OPTION == 0 || OPTION >= INT_MAX)
		 		 {
					 cerr << "That is not a valid sorting option, enter a new one: \n";
					 LEN = checkInput(test,arrayInputError);
		 		 }
        /* Gets the sorting method that will be used */
        cout << sortingSelectMsg;
        SORT = checkInput(test, sortingInputError);
        while (SORT < 1 || SORT > 6)
				{
            cerr << "That is not a valid sorting option, please pick another: \n"; // Error message
            SORT = checkInput(test, sortingInputError); // Checks for the correct type and gets user value
        }

        object.setLength(LEN); // Sets the LEN inside the Sort class
        int arr[LEN]; // Creates the array

        /* Populates the array with the option chosen */
        switch (OPTION)
				 {
            case 1: sortAscending(arr);  break;
            case 2: sortDescending(arr); break;
            case 3: identical(arr);        break;
            case 4: random(arr);      break;
            default:
                cerr << "\nERROR!\n";
                exit(EXIT_FAILURE); // Exit out the program
            break;
        }

        /* Runs the sorting algorithm and times how long it takes */
        cout << "\nLOADING...\n";
        stopwatch = clock(); // Starts the timer
        switch (SORT)
				 {
            case 1: object.insertionSort(arr); break;
            case 2: object.quickSortRight(arr);    break;
            case 3: object.quickSortInsertion(arr);    break;
            case 4: object.quickSortMedian(arr);    break;
            case 5: object.mergeSort(arr);     break;
            case 6: object.heapSort(arr);      break;
            default:
                cerr << "\nAn error occurred\n"; // Error message
                exit(EXIT_FAILURE);
            break;
        }
        stopwatch = clock() - stopwatch; // Ends the timer
        runTime = ((float)stopwatch)/CLOCKS_PER_SEC; // Converts the time to seconds
        cout << "RUN TIME: " << runTime << "\n";

        cout << "would you like to go again??(y/n): ";
        cin >> loop;
				loopContinue = toupper(loop[0]);


        /* Ends or keeps the program running */
        switch (loopContinue) {
            case 'Y': cout << "\n\n"; break;
            default:
                cout << "\nExiting.\n";
                isRunning = false; // Break out of the loop
            break;
        }
    }
    return EXIT_SUCCESS;
}
