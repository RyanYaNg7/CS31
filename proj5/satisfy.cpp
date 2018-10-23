//
//  main.cpp
//  proj5
//
//  Created by 杨子鸣 on 11/14/16.
//  Copyright © 2016 杨子鸣. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
//func1
int notHaveSamerule(char word1[][MAX_WORD_LENGTH+1],
                    char word2[][MAX_WORD_LENGTH+1],
                    int distance[],
                    int n);

void lowerized(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int nRules);

int isValidRule(char word1[][MAX_WORD_LENGTH+1],
                char word2[][MAX_WORD_LENGTH+1],
                int distance[],
                int n);

int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[],
                   int nRules);




//func2
int singleSatisfy(char sim[][200],
                  char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int distance[],
                  int nRules,
                  int i, int s);

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[],
                          int nRules,
                          const char document[]);











int main()
{
    char word1[20][MAX_WORD_LENGTH + 1] = { "FI","VE" };
    	    char word2[20][MAX_WORD_LENGTH + 1] = { "SX","SIX" };
    	    int distance[20] = { 0,-1 };
    	    assert(normalizeRules(word1, word2, distance, 2) == 0);
    //IF THE DISTANCE IS LESS THAN ZERO
    	    char word3[20][MAX_WORD_LENGTH + 1] = { "QWe","JIJIji","WhatI" };
    	    char word4[20][MAX_WORD_LENGTH + 1] = { "MUN","Is","Me" };
    	    int distance1[20] = { 1,2,3 };
    	    assert(normalizeRules(word3, word4, distance1, 3) == 3);
    	assert(strcmp(word3[0], "qwe") == 0);
    	assert(strcmp(word3[1], "jijiji") == 0);
    	assert(strcmp(word3[2], "whati") == 0);
    	assert(strcmp(word4[0], "mun") == 0);
    	assert(strcmp(word4[1], "is") == 0);
    	assert(strcmp(word4[2], "me") == 0);
    //IF THE DISTANCE IS LESS THAN ZERO
    
    
    	    char word5[20][MAX_WORD_LENGTH + 1] = { "341","","cheM","math","physics***","","!!finance" };
    	    char word6[20][MAX_WORD_LENGTH + 1] = { "Ryan&" ,"oi io xxee909","omg this is har","weird","evil","","paper" };
    	    int distance2[20] = { 2,4,63,6,43,2,5,65,4,3 };
    	    assert(normalizeRules(word5, word6, distance2, 6) == 1);
    	assert(strcmp(word5[0], "math") == 0);
    	assert(strcmp(word6[0], "weird") == 0);
    //INVALID RULE WITH NON-LETTER CHARACTER
    	    char word7[20][MAX_WORD_LENGTH + 1] = { "WHat","Man","man","shittY","JuMpy","man" ,"WhaT","mAn","whAt","what","shitty" };
    	    char word8[20][MAX_WORD_LENGTH + 1] = { "mAN","Venture","venture","what","wHat","what","jumpY","venTUre","jUmpy" ,"man","what" };
    	    int distance3[20] = { 5,4,2,4,7,9,3,2,3,4 };
    	    assert(normalizeRules(word7, word8, distance3,11) == 4);
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "one", "one", "three", "six"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "two", "four", "one", "two"
    };
    int test1dist[TEST1_NRULES] = {
        3,           4,          1,           13
    };
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
                                 "one two Three foUr five Six seven EIGHT nine ten eleven twelve.") == 3);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
                                 "one two Three foUr     five Six.") == 3);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
                                 "------ 9324 ------") == 0);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
                                 "    one two : three FOUR!!!!") == 2);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
                                 "one two one TWO three three Four!") == 2);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
                                 "one&two&three&four&five&six is equal to 0000000") == 0);
    cout << "All tests succeeded" << endl;
    
    const int TEST2_NRULES = -2;
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST2_NRULES,
                                 "one two one TWO three three Four!") == 0);
}







//func1





//see if there is a conterpart of the just normalized rule, if there is, replace it with the greater distance one
int notHaveSamerule(char word1[][MAX_WORD_LENGTH+1],
                    char word2[][MAX_WORD_LENGTH+1],
                    int distance[],
                    int n)
{
    for (int m = 0; m < n; m++)
    {
        if (strcmp(word1[n],word1[m]) == 0 && strcmp(word2[n],word2[m]) == 0)
        {
            cerr << "n ortho same is " << n <<endl;
            distance[m] = max(distance[m], distance[n]);
            return 0;
        }
        
        else if (strcmp(word1[n],word2[m]) == 0 && strcmp(word2[n],word1[m]) == 0)
        {
            cerr << "n cross same is " << n <<endl;
            distance[m] = max(distance[m], distance[n]);
            return 0;
        }
    }
    return 1;
}

void lowerized(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int nRules)
{
    for (int n = 0; n < nRules; n++)                        // change all rules to lower case
    {
        for (int m = 0; m < strlen(word1[n]); m++)
        {
            word1[n][m] = tolower(word1[n][m]);
        }
        for (int m = 0; m < strlen(word2[n]); m++)
        {
            word2[n][m] = tolower(word2[n][m]);
        }
    }
}

int isValidRule(char word1[][MAX_WORD_LENGTH+1],
                char word2[][MAX_WORD_LENGTH+1],
                int distance[],
                int n)
{
    if (distance[n] <= 0)       //distance is not positive
    {
        return 0;
    }
    
    if (strlen(word1[n]) == 0 || strlen(word2[n]) == 0)     //a word in the rule contains no character
    {
        return 0;
    }
    
    for (int m = 0; m < strlen(word1[n]); m++)          //a word in the word1 contains non-letter character
        if (!isalpha(word1[n][m]))
        {
            return 0;
        }
    
    for (int m = 0; m < strlen(word2[n]); m++)          // a word in word2 that contains non-letter character
        if (!isalpha(word2[n][m]))
        {
            return 0;
        }
    return 1;
}


int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[],
                   int nRules)
{
    if (nRules <= 0)     //if nRule is less than zero
    {
        nRules = 0;
        return 0;
    }
    
    lowerized(word1,word2,nRules);
    
    int n = 0;
    int rt = 0;
    int wr = 0;
    int ppp = 0;
    while ((n+wr) < nRules)
    {
        if ((isValidRule(word1, word2, distance, n)==0)|| (notHaveSamerule(word1, word2, distance, n)==0))
        {
            char tmp[MAX_WORD_LENGTH+1];
            strcpy(tmp, word1[n]);
            int m1;
            for (m1 = n; m1 < nRules-1; m1++)
                strcpy(word1[m1], word1[m1+1]);
            strcpy(word1[m1], tmp);
            
            strcpy(tmp, word2[n]);
            int m2;
            for (m2 = n; m2 < nRules-1; m2++)
                strcpy(word2[m2], word2[m2+1]);
            strcpy(word2[m2], tmp);
            
            int tmp_;
            tmp_ = distance[n];
            int m3;
            for (m3 = n; m3 < nRules-1; m3++)
                distance[m3] = distance[m3+1];
            distance[m3] = tmp_;
            wr++;
            ppp++;
        }
        else
        {
            ppp++;
            rt++;
            n++;
        }
        cerr <<"wtf is this "<<  ppp <<endl;
    }
    
    cerr << "rt is " << rt <<endl;
    return rt;
    
    
    
}








//func2
int singleSatisfy(const char sim[][200],
                  const char word1[][MAX_WORD_LENGTH+1],
                  const char word2[][MAX_WORD_LENGTH+1],
                  const int distance[],
                  const int nRules,
                  const int i,
                  const int s,
                  int& k)
{
    if (!strcmp(word1[i],sim[k]))
    {
        int mlim = k-distance[i];
        int ulim = k+distance[i];
        if (mlim < 0)
            mlim = 0;
        if (ulim > s)
            ulim = s;
        for (int n = mlim; n <= ulim; n++) //search all sim in distance
        {
                if (!strcmp(sim[n],word2[i]))
                {
                    
                    return 1;
                }
        }
        
        return 0;
    }
    else
    {

        return 0;
    }
}

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[],
                          int nRules,
                          const char document[])
{
    if (nRules <= 0)     //if nRule is less than zero
    {
        nRules = 0;
        return 0;
    }
    
    //treat the document as its simplest version
    char doc[200];
    char sim[200][200];
    cerr << "the length of document is " << strlen(document) <<endl;
    int i = 0;
    for (i; i < strlen(document); i++)
    {
        doc[i] = tolower(document[i]);
    }
    doc[i] = '\0';
    
    
    
    int n = 0;
    int s = 0;
    int m = 0;
    if (doc[n] == ' ')
    {
        for (n; n < strlen(doc); n++)
        {   if (doc[n] == ' ')
            continue;
            else if (islower(doc[n]))
                break;
        }
    }
    while (n < strlen(doc))
    {
        for (n; n < strlen(doc); n++)
        {
            if (islower(doc[n]))
            {
                sim[s][m] = doc[n];
                m++;
                continue;
            }
            else if (doc[n] == ' ')
            {
                sim[s][m]='\0';
                m=0;
                for (n; n < strlen(doc); n++)
                {   if (doc[n] == ' ')
                        continue;
                    else if (islower(doc[n]))
                    {
                        s++;
                        sim[s][m]=doc[n];
                        m++;
                        break;
                    }
                }
            }
            else
                continue;
        }
        sim[s][m]='\0';
    }

    
    
    /*
    for (int n = 0; n <= s;n++)
    {
        cerr << "the " << n << " row is";
        for(int m = 0; m < strlen(sim[n]); m++)
        {
            cerr << sim[n][m];
        }
        cerr <<endl;
    }
    */
    
    //see if the simplified document satisfy the rules
    cerr << " for test reason, the 's' here is " << s << "; and 'doc' here is '" << doc <<
    "'"<<endl;
    
    int nnn = 0;
            cerr<< s << "   this is s"<<endl;
    for (int i = 0; i < nRules; i++)    // all w1
    {
        for (int k = 0; k <= s; k++)    //all sim with w2 comparison
        {
            if (singleSatisfy(sim, word1, word2, distance, nRules, i, s, k))//rule i correct
            {
                nnn ++;
                cerr << "this time, i is " << i << ";   k is " << k <<  " and nnn is " << nnn << endl;
                break;
            }
        }
        
    }
    cerr << " the result returned by this function is " << nnn << endl;
    return nnn;
}
