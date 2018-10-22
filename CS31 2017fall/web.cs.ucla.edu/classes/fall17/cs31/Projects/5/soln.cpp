// Project 5

#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

   //*********************
   //***  Replace the "Z:/words.txt" in the initialization of WORDNAMEFILE below
   //***  with a path to the file you want to use as your word file.
   //***
   //***  On a Windows system, if you provide a path for the wordfilename,
   //***  use / in the string instead of the \ that Windows usually uses
   //***  (e.g., "Z:CS31/P5/mywordfile.txt").
   //
   //***  On a Mac, it's probably easiest to use the complete pathname to
   //***  the words file, e.g. "/Users/yourUsername/words.txt" or
   //***  "/Users/yourUsername/CS31/P5/words.txt".
   //
   //***  On a SEASnet Linux server, if you put the words.txt file in the
   //***  same directory as your .cpp file, you can use "words.txt" as the
   //***  file name string.

const char WORDFILENAME[] = "Z:/words.txt";

const int MAXPROBELEN = 100;
const int MAXWORDS = 9000;

int runOneRound(const char words[][MAXWORDLEN+1], int num, int wordnum);
bool contains(const char words[][MAXWORDLEN+1], int num, const char str[]);
void countMatches(const char s1[], const char s2[], int& nStars, int& nPlanets);

int main()
{
      // Get word list

    char wordList[MAXWORDS][MAXWORDLEN+1];

    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME);
    if (nWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }

    cout.setf(ios::fixed);
    cout.precision(2);

    cout << "How many rounds do you want to play? ";
    int nRounds;
    cin >> nRounds;
    cin.ignore(10000, '\n');
    if (nRounds <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return 1;
    }

    int totalProbes = 0;
    int minProbes;
    int maxProbes;

      // Play rounds

    for (int round = 1; round <= nRounds; round++)
    {
        cout << endl << "Round " << round << endl;

          // Select random word as secret word

        int wordnum = randInt(0, nWords-1);
        cout << "The secret word is " << strlen(wordList[wordnum])
             << " letters long." << endl;

          // Play a round with that word

        int nProbes = runOneRound(wordList, nWords, wordnum);
        if (nProbes == -1)
        {
            cout << "**** Internal program error:  runOneRound returned -1!"
                 << endl;
            return 1;
        }
        cout << "You got it in " << nProbes;
        if (nProbes == 1)
            cout << " try";
        else
            cout << " tries";
        cout << "." << endl;

          // Update and print statistics

        totalProbes += nProbes;
        if (round == 1)
        {
            minProbes = nProbes;
            maxProbes = nProbes;
        }
        else if (nProbes < minProbes)
            minProbes = nProbes;
        else if (nProbes > maxProbes)
            maxProbes = nProbes;
        cout << "Average: " << static_cast<double>(totalProbes)/round
             << ", minimum: " << minProbes
             << ", maximum: " << maxProbes << endl;
    }
}

int runOneRound(const char words[][MAXWORDLEN+1], int num, int wordnum)
{
      // If impossible to play a round, return failure

    if (wordnum < 0  ||  wordnum >= num)
        return -1;

      // Repeatedly get probe words until word is guessed

    for (int probeNum = 1; ;)
    {
          // Get probe word

        cout << "Probe word: ";
        char probe[MAXPROBELEN+1];
        cin.getline(probe, MAXPROBELEN+1);

          // If it's the secret word, return

        if (strcmp(probe, words[wordnum]) == 0)
            return probeNum;

          // See if probe word has a valid number of lower case letters...

        int k;
        for (k = 0; islower(probe[k]); k++)
            ;
        if (probe[k] != '\0'  ||  k < MINWORDLEN  ||  k > MAXWORDLEN)
            cout << "Your probe word must be a word of " << MINWORDLEN
                 << " to " << MAXWORDLEN << " lower case letters." << endl;

          // ... and is in the word list ...

        else if (! contains(words, num, probe) )
            cout << "I don't know that word." << endl;

          // ... and if so, report number of stars and planets
        else
        {
            int nStars;
            int nPlanets;
            countMatches(probe, words[wordnum], nStars, nPlanets);
            cout << "Stars: " << nStars << ", Planets: " << nPlanets << endl;
            probeNum++;
        }
    }
}

  // Return true if str is in list
bool contains(const char words[][MAXWORDLEN+1], int num, const char str[])
{
    for (int k = 0; k < num; k++)
        if (strcmp(words[k], str) == 0)
            return true;
    return false;
}

  // Determine numbers of stars and planets between s1 and s2
void countMatches(const char s1[], const char s2[], int& nStars, int& nPlanets)
{
    const char STAR_BLOT   = '#';  // any nonword character will do
    const char PLANET_BLOT = '@';  // any nonword character will do

    char s1copy[MAXWORDLEN+1];
    strcpy(s1copy, s1);
 
      // First, count and blot out the stars so they won't be matched later.
      // Check every position for a star, stopping at the end of the
      // shorter string

    nStars = 0;
    int k;
    for (k = 0; s1copy[k] != '\0'  &&  s2[k] != '\0'; k++)
    {
        if (s1copy[k] == s2[k])
        {
            nStars++;
            s1copy[k] = STAR_BLOT;
        }
    }
    int shorterLen = k;

      // Now count the planets.  For every character in s2

    nPlanets = 0;
    for (int k2 = 0; s2[k2] != '\0'; k2++)
    {
          // Don't count stars

        if (k2 < shorterLen  &&  s1copy[k2] == STAR_BLOT)
            continue;

          // For every character in the copy of s1

        for (int k1 = 0; s1copy[k1] != '\0'; k1++)
        {
              // If they match, blot it out of the copy of s1
              // so it won't be matched again

            if (s1copy[k1] == s2[k2])
            {
                nPlanets++;
                s1copy[k1] = PLANET_BLOT;
                break;
            }
        }
    }
}
