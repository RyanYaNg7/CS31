//
//  main.cpp
//  proj4
//
//  Created by 杨子鸣 on 11/2/16.
//  Copyright © 2016 杨子鸣. All rights reserved.
//no function (other than main) may read anything from cin or write anything to cout
//all functions that return an int must return −1 if they are passed any bad arguments(e.g. a negative array size, or a position that would require looking at the contents of an element past the last element we're interested in). Unless otherwise noted, passing 0 to the function as the array size is not itself an error; it merely indicates the function should examine no elements of the array.
//

#include <iostream>
#include <cstring>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);


#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    string h[7] = { "jill", "hillary", "donald", "tim", "", "evan", "evan" };
    assert(lookup(h, 7, "evan") == 5);      //two "evan" in the array
    assert(lookup(h, 7, "donald") == 2);    //regular test
    assert(lookup(h, 2, "donald") == -1);   //no such element
    assert(positionOfMax(h, 7) == 3);       //normal test
    assert(positionOfMax(h, 0) == -1);      //no elements in the array
    string g[4] = { "jill", "hillary", "gary", "mindy" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?"); //for n = size of array
    assert(appendToAll(g, 2, "!") == 2 && g[0] == "jill?!" && g[3] == "mindy?");  //for n < size of array
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "gary?" && g[3] == "hillary?!");    //regular
    assert(rotateLeft(g, 4, 3) == 3 && g[0] == "jill?!" && g[3] == "hillary?!");     //the end
    
    string e[4] = { "donald", "tim", "", "evan" };
    assert(subsequence(h, 7, e, 4) == 2);   //regular
    assert(subsequence(h,7,e,0)  == 0); //no element in a2
    assert(subsequence(h,3,e,4) == -1);  //no such sequence because n1 < n2
    assert(subsequence(h,4,e,4) == -1); // no such sequence
    
    string d[5] = { "hillary", "hillary", "hillary", "tim", "tim" };
    assert(countRuns(d, 5) == 2);   //regular
    assert(countRuns(h, 1) == 1);   //n < size

    string m[4] = {"hillary", "hillary", "hillary", "timm"};
    assert(differ(d,5,m,4) == 3);   //regular
    assert(differ(d,3,m,3) == 3);   //both run out
    assert(differ(d,4,m,3) == 3);   //one runs out
    
    string f[3] = { "gary", "donald", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2); //regular
    assert(lookupAny(h,2,f,3) == -1); //none
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "gary");    //odd number
    assert(flip(h, 6) == 6 && h[5] == "jill" && h[0] == "evan" && h[2] == "tim" && h[6] == "evan"); //even number, partial flip
    
    string cand[6] = { "donald", "jill", "hillary", "tim", "evan", "bill" };
    assert(separate(cand, 6, "gary") == 3); //regular
    string cand2[6] = { "donald", "jill", "hillary", "tim", "evan", "bill" };
    assert(separate(cand2, 5, "bill") == 0 && cand2[5] == "bill" && cand2[0] == "donald");    //n < size
    
    
    cout << "All tests succeeded" << endl;
}



int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    
    for(int k = 0; k < n; k++)
        a[k] += value;
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    for (int k = 0; k < n; k++)
    {
        if (a[k] == target)
            return k;
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    int pos = 0;
    if (n <= 0)
        return -1;
    string tmpM = a[0];
    for (int k = 1; k < n; k++)
    {
        if (a[k] > tmpM)
        {
            tmpM = a[k];
            pos = k;
        }
    }
    return pos;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0)
        return -1;
    if (pos >= n)
        return -1;
    if (pos < 0)
        return -1;
    string posedOne = a[pos];       //store the original value
    for (int k = pos; k < (n-1); k++)              //scoot the array
    {
        a[k] = a[k+1];
    }
    a[n-1] = posedOne;              //set the last element
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    
    int m = 1;
    
    for (int k = 0; k < (n-1); k++)
    {
        if (a[k+1] != a[k])
            m += 1;
    }
    return m;
}

int flip(string a[], int n)
{
    if (n<0)
        return -1;
    for (int m=0; m != (n/2); m++)
    {
        string mid = a[n-1-m];
        a[n-1-m] = a[m];
        a[m] = mid;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    
    int lim = min(n1, n2);                  //set the limit for n below
    
    for (int n = 0; n != lim; n++)
    {
        if (a1[n] != a2[n])
            return n;
    }
    return lim;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)       // super hard for me
{
    if (n1 < 0 || n2 < 0)
    {
        cerr << "1";
        return -1;
    }
    if (n1 < n2)                //if n1 < n2, there is no such subsequence
    {
        cerr << "2";
        return -1;
    }
    
    if (n2 == 0)
    {
        cerr << "3";
        return 0;
    }
    
    int m = 0;
    int n = 0;
    int k = 0;
    while (n != n2)
    {
        if (a2[n] == a1[m])
        {
            k++;                //time of match in a round
            m++;                //count the position of a1
            n++;                //count the position of a2
        }
        else                    //start over from a new m
        {
            k = 0;
            m++;
        }
        
        if (k == n2)            //all the elements in a2 match
        {
            cerr << "6  " << m << "  ";
            return (m-n2);
        }
        
        if (m == n1)            //no match
        {
            cerr << "4" ;
            return -1;
        }
    }
    cerr << "5  ";
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    
    
    for (int n = 0; n < n1; n++)                    //bubble
    {
        for (int m = 0; m < n2; m++)
        {
            if (a1[n] == a2[m])
                return n;
        }
    }
    return -1;
}
/*                                              creating an array in function separate.
 int separate(string a[], int n, string separator)
 {
 if (n < 0)
 return -1;
 
 string smaller[100000];
 int m = 0;
 int j = 1;
 int i = n-1;
 for (int k = 0; k < n; k++)
 {
 
 if (a[k] < separator)
 {
 smaller[m] = a[k];
 m++;
 }
 if (a[k] > separator)
 {
 smaller[i] = a[k];
 i--;
 }
 if (a[k] == separator)
 {
 smaller[m+j] = a[k];
 j++;
 }
 }
 
 
 for (int k = 0; k < n; k++)
 {
 if (!(smaller[k] < separator))
 return k;
 }
 return n;
 
 }
 
 */

int separate(string a[], int n, string separator)
{
    if (n < 0)
        return -1;
    
    string mid;
    int m = 0;
    int i = n-1;
    for (int k=0; k < n; k++)   //move all the smaller ones to the front
    {
        if (a[k] < separator)
        {
            mid = a[m];
            a[m] = a[k];                //m=0
            a[k] = mid;
            m++;                        //m=1
        }
    }
    //m is not the number of smaller ones
    for (int k=(n-1); k >= m; k--)   //move all the greater ones to the back
    {
        if (a[k] > separator)
        {
            mid = a[i];
            a[i] = a[k];
            a[k] = mid;
            i--;
        }
    }
    
    for (int k=0; k < n; k++)
        cerr << a[k] << "   ";
    
    for (int k=0; k < n; k++)
    {
        if (!(a[k] < separator))
            return k;
    }
    return n;
}