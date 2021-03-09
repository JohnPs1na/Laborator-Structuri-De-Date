#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <ctime>
using namespace std;

//Utility functions here

int max(int a[], int len) {
    int maxi = a[0];
    for (int i = 0; i < len; i++)
        if (maxi < a[i])
            maxi = a[i];
    return maxi;
}

void copy_list(int a[], int b[], int st, int dr)
{
    for (int i = st; i < dr; i++)
        b[i] = a[i];
}
bool test_sort(int a[], int len)
{
    for (int i = 1; i < len; i++)
        if (a[i] < a[i - 1])
            return false;
    return true;
}
void print_Array(int a[], int len)
{
    for (int i = 0; i < len; i++)
        cout << a[i] << ' ';
    cout << '\n';
}

//TEMA se incepe de aici

// bubble sort
void bubble_sort(int a[], int len)
{
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

// Count sort
void count_sort(int a[], int len)
{
    int maxi = max(a, len);
    vector<int> cnt(maxi+1,0);

    for (int i = 0; i < len; i++)
        cnt[a[i]] += 1;

    int idx = 0;
    for (int i = 0; i < maxi + 1; i++)
        for (int j = 0; j < cnt[i]; j++)
            a[idx++] = i;

}

// insert sort
void insert_sort(int a[], int len)
{
    for (int i = 1; i < len; i++) {
        int k = i;
        while (k > 0 and a[k] < a[k - 1]) {
            swap(a[k], a[k - 1]);
            k--;
        }
    }
}

// Merge Sort
void merge_sort(int a[], int len)
{
    if (len <= 1)
        return;
    int mid = len / 2;
    int* l = a;
    int* r = a + mid;
    int len1 = mid;
    int len2 = len - len1;

    merge_sort(l, len1);
    merge_sort(r, len2);

    int *aux = new int[len];
    int poz1, poz2, idx;
    poz1 = poz2 = idx = 0;
    while (poz1 < len1 && poz2 < len2)
        if (l[poz1] <= r[poz2])
            aux[idx++] = l[poz1++];
        else
            aux[idx++] = r[poz2++];

    while (poz1 < len1)
        aux[idx++] = l[poz1++];
    while (poz2 < len2)
        aux[idx++] = r[poz2++];

    for (int i = 0; i < len; i++)
        a[i] = aux[i];

    delete[] aux;
}

//Radix Sort pe biti
void radix_sort(int a[], int len) {
    int m = max(a, len);

    int* a1 = new int[len];
    int* a2 = new int[len];

    int put = 0;

    while (pow(2, put) < m) {

        int idx1 = 0, idx2 = 0;

        for (int i = 0; i < len; i++) {
            if ((a[i] & (1 << put)) == 0)
                a1[idx1++] = a[i];
            else
                a2[idx2++] = a[i];
        }
        int k = 0;
        for (int i = 0; i < idx1; i++)
            a[k++] = a1[i];
        for (int i = 0; i < idx2; i++)
            a[k++] = a2[i];
        put += 1;
    }

    delete[] a1;
    delete[] a2;
}


//varianta slaba de quicksort cu pivot elementar luat ca primul element din array, va da eroare de stack overflow
//pentru listele sortate, aproape sortate, si sortate descrescator cu un nr de elemente mai mare decat 10^5

//Aici e varianta mai buna cu pivotul ales ca fiind elementul din mijloc
void quick_sort(int a[], int st,int dr)
{
    if(st<dr){
        int i = st;
        int j = dr;
        int pivot = a[(st+dr)/2];

        while(i<j){
            while(a[i]<pivot)
                i++;
            while(a[j]>pivot)
                j--;
            if(i<=j){
                if(a[i]>a[j]){
                    swap(a[i],a[j]);
                }
                i++;
                j--;
            }
        }
        quick_sort(a,st,j);
        quick_sort(a,i,dr);
    }
}

int medOf3(int a[],int st,int dr)
{
    int mij = a[(st+dr)/2];
    if((st>mij) xor (st>dr))
        return st;
    else if((dr>mij) xor (dr>st))
        return dr;
    else
        return mij;
}

//Aici e varianta cu pivotul ales ca fiind mediana din 3

void quick_sortMED3(int a[], int st, int dr) {

    int i = st;
    int j = dr;
    int pivot = medOf3(a,st,dr);

    while (i <= j) {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j) {
            if(a[i]>a[j])
                swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (st<j)
        quick_sort(a, st, j);
    if (i<dr)
        quick_sort(a, i, dr);
}

//Aici se termina functiile care apartin Temei
//Alte Functii pentru utilitate
unsigned long long llrand() //functie pentru generarea unui array cu elemente random luata de pe internet.
{
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

void generate_random_array(int A[], int N, int M)
{
    for (int i = 0; i < N; i++)
        A[i] = llrand() % M;
}
void generate_almost_sorted_array(int A[], int N, int M)
{
    A[0] = (rand() % (M-N+1)) + 1;
    for (int i = 1; i < N; i++) {
        A[i] = A[i - 1] + rand() % 12 - 2;
    }
}

void generate_sorted_array(int A[], int N, int M)
{
    generate_random_array(A,N,M);
    sort(A,A+N);
}

void generate_sorted_decreasing(int A[],int N,int M)
{
    generate_random_array(A,N,M);
    sort(A,A+N,greater<int>());
}

void generate_constant(int A[],int N, int M)
{
    int x = rand() % M+1;
    for(int i = 0;i<N;i++)
    {
        A[i] = x;
    }
}
void runBubble(int l[], int len) {
    if(len>=100000)
    {
        cout<<"Bubble: Prea Mult Timp\n";
        return;
    }
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Bubble Sort: ";
    auto start = chrono::high_resolution_clock::now();
    bubble_sort(copie, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT! " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;


}
void runInsert(int l[], int len) {
    if(len>=100000)
    {
        cout<<"Insert: Prea Mult Timp\n";
        return;
    }
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Insert Sort: ";
    auto start = chrono::high_resolution_clock::now();
    insert_sort(copie, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;

}
void runCount(int l[], int len) {
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Count Sort: ";
    auto start = chrono::high_resolution_clock::now();
    count_sort(copie, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT! " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;

}
void runMerge(int l[], int len) {
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Merge Sort: ";
    auto start = chrono::high_resolution_clock::now();
    merge_sort(copie, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;

}
void runRadix(int l[], int len)
{
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Radix Sort: ";
    auto start = chrono::high_resolution_clock::now();
    radix_sort(copie, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT! " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;

}
void runQuick(int l[], int len) {


    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Quick Sort: ";
    auto start = chrono::high_resolution_clock::now();
    quick_sort(copie, 0, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT! " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;

}

void runQuickMED3(int l[], int len)
{
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "Quick Sort Med 3: ";
    auto start = chrono::high_resolution_clock::now();
    quick_sortMED3(copie, 0, len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT! " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;

}

void runSTL(int l[],int len)
{
    int* copie = new int[len];
    copy_list(l, copie, 0, len);
    cout << "STL Sort: ";
    auto start = chrono::high_resolution_clock::now();
    sort(copie,copie+len);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stop - start;
    if (test_sort(copie, len))
        cout << "SORTAT! " << duration.count() << " secunde\n";
    else
        cout << "lista nu a fost sortata\n";
    delete[] copie;
    cout << endl;
}
void sorteaza_tot(int l[],int len) {
    runBubble(l, len);
    runInsert(l, len);
    runCount(l, len);
    runMerge(l, len);
    runRadix(l, len);
    runQuick(l, len);
    runQuickMED3(l,len);
    runSTL(l,len);
}


int main()
{
    srand(time(NULL));

    int testNumber;

    cout << "introduceti numarul de teste pe care doriti sa il efectuati: ";
    cin >> testNumber;
    cout << '\n';

    for (int i = 0; i < testNumber; i++)
    {
        int n, m;
        cout << "introduceti numarul de elemente pentru testul " << i + 1 << " :";
        cin >> n;
        cout << "introduceti numarul maxim din lista pe care o sa o generam : ";
        cin >> m;

        cout << "\nAcum generam liste\n";

        int* test = new int[n];
        cout << "RANDOM:\n";
        generate_random_array(test, n, m);
        sorteaza_tot(test,n);

        cout << "ALMOST SORTED:\n";
        generate_almost_sorted_array(test, n, m);
        sorteaza_tot(test, n);

        cout << "SORTED:\n";
        generate_sorted_array(test, n, m);
        sorteaza_tot(test, n);

        cout<< "SORTED DECREASING:\n";
        generate_sorted_decreasing(test,n,m);
        sorteaza_tot(test,n);

        cout<<"CONSTANT:\n";
        generate_constant(test,n,m);
        sorteaza_tot(test,n);

        delete[] test;
    }
    return 0;
}


