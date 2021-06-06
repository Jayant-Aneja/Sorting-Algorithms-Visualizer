#include <stdio.h>
#include <stdlib.h>
#include<unordered_map>
#include <time.h>
#include <iostream>
#include <deque>
#include <queue>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
using namespace std;
#define SORT_NO 7// Number of sorting algorithms
#define MAX 45    // Number of values in the array
#define COLORS 90 // Max Color Length

/*~~Global Variables~~*/
int a[MAX];        // Sorting Array
double cc[COLORS]; // Color Array
char text1[5];
char text2[5];
int ans;
int swapflag = 0; // Flag to check if swapping has occured
int i = 0, j = 0; // To iterate through the array
int flag = 0;     // For Insertion Sort
int dirflag = 0;  // For Ripple Sort, to change direction at the ends
int count1 = 1;    // For Ripple Sort, to keep count1 of how many are sorted at the end
int sorting = 0;  // 1 if Sorted
const char* sort_string[] = { "Bubble Sort", "Selection Sort", "Insertion Sort", "Ripple Sort", "Comb Sort","heap Sort","Merge Sort" };
int sort_count1 = 0; // To cycle through the string
int speed = 10;     // Speed of sorting
int arrayFlag = 1;
int backFlag = 1;
int fastslow = 0;
int vertical_index;
int heap_insert = MAX- 1;
priority_queue<int> gquiz;
/*{~~Function Declarations~~*/
void merge_fun(int l, int m, int r);
double randomFlaot();
void bitmap_output(int, int, const char*, void*);
void makedelay(int);
void display_text();
void Initialize();
void display();
void int_str(int rad, char r[]);
int notsorted();
void keyboard(unsigned char key, int x, int y);
void ripplesort();
void bubblesort();
void selectionsort();
void insertionsort();
char* whichmode(char k);
void quickSort(int low, int high);
int partition(int low, int high);
void swap(int* a, int* b);
void combSort();
void mergeSort();
queue<pair<int,int>>q;
void shellSort();
void heapify(int n, int i);
void heapSort();

// Function Definaions
char* whichmode(const int d)
{
    char* z;
    if (d == 1)
    {
        char ai[17] = {'I','N','t','e','r','a','c','t','i','v','e',' ','m','o','d','e','/0'};
        z = ai;
        return z; /* code */
    }
    char ai[17] = { 'O','u','t','s','t','a','n','d','i','n','g',' ','m','o','d','e','/0' };
    z = ai;
    return z;
}

// To get random number between 0.0 to 1.0
double randomFlaot()
{
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

// Function to display text on screen char by char
void bitmap_output(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// Function to integer to string
void int_str(int rad, char r[])
{
    snprintf(r, 10, "%d", rad);
}

// Home Screen Static Texts
void display_text()
{
    glColor3d(cc[36], cc[37], cc[38]);
    bitmap_output(250, 750, "SORTING ALGORITHM VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
    // glBegin(GL_LINE_LOOP);
    // glVertex2f(145, 700);
    // glVertex2f(520, 700);
    // glEnd();
    char text[20]; // other text small font
    glColor3d(cc[39], cc[40], cc[41]);
    bitmap_output(15, 700, "This code sorts a random set of integers in ascending order by displaying them graphically", GLUT_BITMAP_HELVETICA_18);
    bitmap_output(15, 680, "as bars with varying height", GLUT_BITMAP_HELVETICA_18);

     glColor3f(0.5, 0.5, 0.5);
    glColor3d(cc[42], cc[43], cc[44]);
    int_str(speed, text);
    strcat(text, "ms");
    bitmap_output(620, 510, "Speed:", GLUT_BITMAP_HELVETICA_18);
    //strcat(mode, "Mode");
    bitmap_output(600, 510, whichmode(fastslow), GLUT_BITMAP_HELVETICA_18);
    bitmap_output(650, 510, text, GLUT_BITMAP_HELVETICA_18);
    char iff[50] = "swapping ";
    // strcat(texts, " swapping ");
    strcat(iff, text1);
    strcat(iff, " and ");
    strcat(iff, text2);

    glBegin(GL_LINE_LOOP);
    glColor3d(cc[42], cc[43], cc[44]);
    glVertex3f(10.0f, 740.0f, 0.0f);
    glColor3d(cc[45], cc[46], cc[47]);
    glVertex3f(690.0f, 740.0f, 0.0f);
    glColor3d(cc[48], cc[49], cc[50]);
    glVertex3f(690.0f, 500.0f, 0.0f);
    glColor3d(cc[51], cc[52], cc[53]);
    glVertex3f(10.0f, 500.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(cc[47], cc[52], cc[10]);
    glVertex2f(450.0, 740.0);
    glColor3d(cc[42], cc[17], cc[74]);
    glVertex2f(450.0, 500.0);
    glEnd();
    glColor3d(cc[56], cc[77], cc[36]);
    bitmap_output(550.0, 700.0, "STEP", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3d(cc[34], cc[58], cc[28]);
    // bitmap_output(470, 650, texts, GLUT_BITMAP_HELVETICA_18);
    bitmap_output(470, 600, iff, GLUT_BITMAP_HELVETICA_18);

    glColor3d(cc[54], cc[55], cc[56]);
    if (sorting == 0) // if not sorting display menu
    {
        bitmap_output(15, 645, "MENU", GLUT_BITMAP_TIMES_ROMAN_24);
        bitmap_output(15, 625, "Press s to SORT", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 605, "Press c to SELECT the sort algorithm", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 585, "Press r to RANDOMISE", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 565, "Esc to QUIT", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 545, "Selected sort: ", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(80, 545, *(sort_string + sort_count1), GLUT_BITMAP_HELVETICA_18);
    }
    else if (sorting == 1) // while sorting
    {
        glColor3d(cc[57], cc[58], cc[59]);
        bitmap_output(55, 555, "Sorting in progress...", GLUT_BITMAP_HELVETICA_18);
        glColor3d(cc[60], cc[61], cc[62]);
        bitmap_output(55, 535, "Press p to PAUSE", GLUT_BITMAP_HELVETICA_18);
    }
}

// Initailization of values also call whenever r key is pressed
void Initialize()
{
    heap_insert = MAX - 1;
    srand(time(0)); // Use current time as seed for random generator
    int temp1;
    
    int curr_size;  //
    int left_start; 
    while (!q.empty())
    {
        q.pop();
    }
    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size = 1; curr_size <= MAX - 1; curr_size = 2 * curr_size)
    {
        // Pick starting point of different subarrays of current size
        for (left_start = 0; left_start < MAX - 1; left_start += 2 * curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting
            // point of right
            int mid = min(left_start + curr_size - 1, MAX - 1);

            int right_end = min(left_start + 2 * curr_size - 1, MAX - 1);
            q.push(make_pair(left_start,curr_size));
            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            
        }
    }
    if (arrayFlag == 1)
    {
        // Reset the array
        for (temp1 = 0; temp1 < MAX; temp1++)
        {
            a[temp1] = rand() % 100 + 1;
            // printf("%d ", a[temp1]);
        }
        arrayFlag = 0;
    }

    if (backFlag == 1)
    {
        for (int i = 0; i < COLORS; i++)
        {
            cc[i] = randomFlaot();
        }

        // Reset all values
        i = j = 0;
        dirflag = 0;
        count1 = 1;
        flag = 0;
        glClearColor(randomFlaot(), randomFlaot(), randomFlaot(), randomFlaot());
        backFlag = 0;
    }
    
    // Build heap (rearrange array)

    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 699, 0, 799);
}

// check elements before calling sorting functions
int notsorted()
{
    int q;
    for (q = 0; q < MAX - 1; q++)
    {
        if (a[q] > a[q + 1])
            return 1; // Return 1 if not sorted
    }
    return 0;
}

// Main function for display
void display()
{
    int ix, temp;
    glClear(GL_COLOR_BUFFER_BIT);


    display_text();
    char text[10];

    for (ix = 0; ix < MAX; ix++)
    {
        // glColor4d(1, 0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glColor3d(cc[63], cc[64], cc[65]);
        glVertex2f(10 + (700 / (MAX + 1)) * ix, 50);
        glColor3d(cc[66], cc[67], cc[68]);
        glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50);
        glColor3d(cc[69], cc[70], cc[71]);
        glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 4);
        glColor3d(cc[72], cc[73], cc[74]);
        glVertex2f(10 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 4);
        glEnd();

        int_str(a[ix], text);
        // printf("\n%s", text);
        glColor3d(cc[75], cc[76], cc[77]);
        bitmap_output(12 + (700 / (MAX + 1)) * ix, 30, text, GLUT_BITMAP_HELVETICA_18);
    }

    if (swapflag == 1 || sorting == 0)
    {
        glBegin(GL_POLYGON);
        glColor3d(cc[75], cc[76], cc[77]);
        glColor3d(cc[78], cc[79], cc[80]);
        glVertex2f(10 + (700 / (MAX + 1)) * vertical_index, 50);
        glColor3d(cc[81], cc[82], cc[83]);
        glVertex2f(10 + (700 / (MAX + 1)) * (vertical_index + 1), 50);
        glColor3d(cc[84], cc[85], cc[86]);
        glVertex2f(10 + (700 / (MAX + 1)) * (vertical_index + 1), 50 + a[vertical_index] * 4);
        glColor3d(cc[87], cc[88], cc[89]);
        glVertex2f(10 + (700 / (MAX + 1)) * vertical_index, 50 + a[vertical_index] * 4);
        glEnd();
        swapflag = 0;
    }
    glFlush();
}

// Timer Function, takes care of sort selection
void makedelay(int)
{
    if (sorting)
    {
        switch (sort_count1)
        {
        case 0:
            bubblesort();
            break;
        case 1:
            selectionsort();
            break;
        case 2:
            insertionsort();
            break;
        case 3:
            ripplesort();
            break;
        case 4:
            combSort();
            break;
        case 5:
            heapSort();
            break;
        case 6:
            mergeSort();
            break;
        }
    }
    if (fastslow == 1)
    {
        sorting = 0;
    }
    speed = 100;
    glutPostRedisplay();
    glutTimerFunc(speed, makedelay, 100);
}

// Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'k')
    {
        speed = 50;
    }
    else if (sorting != 1)
    {
        switch (key)
        {
        case 27:
            exit(0); // 27 is the ascii code for the ESC key
        case 's':
            sorting = 1;
            break;
        case 'i':
            fastslow = 1;
            break;
        case 'o':
            fastslow = 0;
            break;
        case 'r':
            arrayFlag = 1;
            Initialize();
            break;
        case 'x':
            backFlag = 1;
            arrayFlag = 0;
            Initialize();
        case 'z':
            arrayFlag = 1;
            backFlag = 1;
            Initialize();
            break;
        case 'c':
            sort_count1 = (sort_count1 + 1) % SORT_NO;
            break;
        }
    }
    else if (sorting == 1)
    {
        if (key == 'p')
            sorting = 0;
        speed = 1000;
    }
    else
        Initialize();
}

// Insertion Sort
void insertionsort()
{
    int temp;

    while (i < MAX)
    {
        if (flag == 0)
        {
            j = i;
            flag = 1;
        }
        while (j < MAX - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                printf("inside while if ");
                a[j] = a[j + 1];
                a[j + 1] = temp;
                vertical_index = j;

                goto A;
            }
            j++;
            if (j == MAX - 1)
            {
                flag = 0;
            }
            int_str(a[j], text1);
            int_str(a[j + 1], text2);
            printf("swap %d and %d\n", a[j], a[j + 1]);
        }
        i++;
    }
    sorting = 0;
A:
    i = j = 0;
}

// Selection Sort
void selectionsort()
{
    int temp, j, min, pos;

    while (notsorted())
    {

        while (i < MAX - 1)
        {
            min = a[i + 1];
            pos = i + 1;
            if (i != MAX - 1)
            {
                for (j = i + 2; j < MAX; j++)
                {
                    if (min > a[j])
                    {
                        min = a[j];
                        vertical_index = i;
                        pos = j;
                    }
                }
            }
            printf("\ni=%d min=%d at %d", i, min, pos);
            printf("\nchecking %d and %d", min, a[i]);
            if (min < a[i])
            {

                //j=pos;
                int_str(min, text1);
                int_str(a[i], text2);
                printf("\nswapping %d and %d", min, a[i]);
                temp = a[pos];
                a[pos] = a[i];
                a[i] = temp;
                // vertical_index = min;
                swapflag = 1; //change
                goto A;
            }
            i++;
        }
    }
    sorting = 0;
    i = j = 0;
A:
    printf("");
}

//Bubble Sort
void bubblesort()
{
    int temp;
    while (notsorted())
    {
        while (j < MAX - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                vertical_index = j + 1;

                int_str(a[j], text1);
                int_str(a[j + 1], text2);
                goto A;
            }
            j++;
            if (j == MAX - 1)
                j = 0;
            printf("swap %d and %d\n", a[j], a[j + 1]);
        }
    }
    sorting = 0;
A:
    printf("");
}

//Ripple Sort
void ripplesort()
{
    int temp;
    while (notsorted() && sorting)
    {
        if (dirflag == 0)
        {
            while (j < MAX - 1)
            {
                if (a[j] > a[j + 1])
                {
                    swapflag = 1;
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    vertical_index = j + 1;
                    goto A;
                }
                j++;
                if (j == MAX - 1)
                {
                    count1++;
                    j = MAX - count1;
                    dirflag = 1 - dirflag;
                }

                printf("j=%d forward swap %d and %d\n", j, a[j], a[j + 1]);
                int_str(a[j], text1);
                int_str(a[j + 1], text2);
            }
        }
        else
        {
            while (j >= 0)
            {
                if (a[j] > a[j + 1])
                {
                    swapflag = 1;
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    vertical_index = j + 1;
                    goto A;
                }
                j--;
                if (j == 0)
                {
                    dirflag = 1 - dirflag;
                }

                printf("j=%d backward swap %d and %d\n", j, a[j], a[j + 1]);
                int_str(a[j], text1);
                int_str(a[j + 1], text2);
            }
        }
    }
    sorting = 0;
A:
    printf("");
}
// heap sort


// main function to do heap sort
void heapSort()
{
    if (heap_insert<0)
        sorting = 0;
    for (int x = 0; x <= heap_insert; x++)
    {
        gquiz.push(a[x]);
    }
    if(!gquiz.empty())
    {
        int  i;
        
        for ( i = 0; i <= heap_insert; i++)
        {
            if (a[i] == gquiz.top())
                break;
        }

        if (i != heap_insert)
        {
            swapflag = 1;
            a[i] = a[heap_insert];
            a[heap_insert] = gquiz.top();
        }
        cout << gquiz.top()<<" ";
        cout << a[heap_insert] << " ";
        gquiz.pop();
        heap_insert -= 1;
        while (!gquiz.empty())
            gquiz.pop();
    }
}
void mergeSort()
{
    if (q.empty())
        sorting = 0;
    if (!q.empty())
    {
        
        pair<int, int> x = q.front();
        int left_start = x.first;
        int curr_size = x.second;
        int mid = min(left_start + curr_size - 1, MAX - 1);
        int right = min(left_start + 2 * curr_size - 1, MAX - 1);
        merge_fun(left_start, mid ,right );
        swapflag = 1;
        q.pop();
    }
}
void merge_fun( int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int* L = new int[n1];
    int* R=new int[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}



int getNextGap(int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap * 10) / 13;

    if (gap < 1)
        return 1;
    return gap;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to sort a[0..n-1] using Comb Sort
void combSort()
{
    // Initialize gap
    int gap = MAX;

    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (notsorted())
    {
        printf("not done");
        while (gap != 1 || swapped == true)
        {
            // Find next gap
            gap = getNextGap(gap);

            // Initialize swapped as false so that we can
            // check if swap happened or not
            swapped = false;

            // Compare all elements with current gap
            for (int j = 0; j < MAX - gap; j++)
            {
                if (a[j] > a[j + gap])
                {
                    swap(&a[j], &a[j + gap]);
                    swapflag = 1;
                    swapped = true;
                    vertical_index = j + gap;

                    int_str(a[j], text1);
                    int_str(a[j + gap], text2);

                    goto A;
                }
            }
        }
    }
    sorting = 0;

A:
    printf("");
}


// Main Function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(2000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("SORTING ALGORITHM VISUALIZER");
    Initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, makedelay, 1);
    glutMainLoop();
}