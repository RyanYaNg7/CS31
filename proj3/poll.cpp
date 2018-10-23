//
//  main.cpp
//  proj3
//
//  Created by 杨子鸣 on 10/28/16.
//  Copyright © 2016 杨子鸣. All rights reserved.
//


#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
#include <cassert>
using namespace std;
bool isValidUppercaseStateCode(string stateCode);
bool hasCorrectSyntax(string pollData);
int countVotes(string pollData, char party, int& voteCount);


int main()

{
    
    
    
    assert(!hasCorrectSyntax("TX5555555555D"));
    
    
    
    
    
    
    
    int votes = -999;
    
    votes = -999;    // so we can detect whether countVotes sets votes
    
    assert(countVotes("TX38RCA55DMs6rnY29dUT06L", 'd', votes) == 0 && votes == 84);
    
    
    
    votes = -999;
    
    assert(countVotes("AK32ACA76A", 'A', votes) == 0 && votes == 108);
    
    
    
    votes = -999;
    
    assert(!(countVotes("CA06A", 'A', votes) == 2) && votes == 6);
    
    
    
    votes = -999;
    
    assert(!(countVotes("CA60A", 'A', votes) == 2) && votes == 60);
    
    
    
    votes = -999;    // so we can detect whether countVotes sets votes
    
    assert(countVotes("TX38RCA55DMs6rnY29dUT06L", 'd', votes) == 0  &&  votes == 84);
    
    
    
    votes = -999;
    
    assert(countVotes("AK32ACA76A", 'A', votes) == 0  &&  votes == 108);
    
    
    
    votes = -999;
    
    assert(!(countVotes("CA06A", 'A', votes) == 2)  &&  votes == 6);
    
    
    
    votes = -999;
    
    assert(!(countVotes("CA60A", 'A', votes) == 2)  &&  votes == 60);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int count = -99;
    
    assert(countVotes("Ca233dtX33m", 'd', count) == 1 && count == -99);// vote is three digits
    
    
    
    assert(countVotes("Ca60aTx00b", 'a', count) == 2 && count == -99);
    
    
    
    
    
    
    
    assert(countVotes("Ca06a", 'a', count) == 0 && count == 6);
    
    assert(countVotes("Ca60a", 'a', count) == 0 && count == 60);
    
    
    
    
    
    assert(countVotes("Tx23rCa05fDC1dMi50ral32g", 'r', count) == 0 && count == 73);//calculate votes for R
    
    
    
    assert(countVotes("Tx23rCa05fDC1dMi50ral32g", 'G', count) == 0 && count == 32);//calculate votes for G
    
    
    

    
    cout << "All tests succeeded" << endl;
    
}


int countVotes(string pollData, char party, int& voteCount)
{
    if (!hasCorrectSyntax(pollData))
        return 1;
    
    if (!isalpha(party))
        return 3;
    int vc = 0;
    int pos = 0;
    
    while (pos !=pollData.size())
    {
        pos +=2;          //the first electoral vote
        
        string num = "";
        while (isdigit(pollData[pos]))
        {
            num += pollData[pos];
            pos++;          //after the loop ends, pos == party code
        }
        
        if (num.size() > 2)
            return false;
        
        int aug = 0;
        
        for(int q=0; q != num.size(); q++)
        {
            int amt = (num[q]-48) * pow(10,(num.size()-q-1));
            aug += amt;
        }
        
        
        if (toupper(pollData[pos]) == toupper(party))
            vc += aug;
        
        if (aug == 0)
            return 2;
        
        pos++;              //pos == first character of state code.
    }
    
    voteCount = vc;
    
    return 0;
}


bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
    "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
    "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool hasCorrectSyntax(string pollData)
{
    //zero forecast
    
    if (pollData.size() == 0)                       //no forecast
        return true;
    
    //there exists at least one forecast
    
    if (pollData.size()<4)                      //minimum number of blocks of first forecast
    {
        cerr << "mini" <<endl;
        return false;
    }
    
    
    //multiple forecast
    
    int pos = 0;
    while (pos !=pollData.size())
    {
        if ((pos+1)==pollData.size())                           //for the exsitance of the last forecast
        {
            cerr << "extra one alphabet" <<endl;
            return false;
        }
        
        if (!isalpha(pollData[pos]) || !isalpha(pollData[pos+1]))     //state code part
        {
            cerr << "state code not a alphabet" <<endl;
            return false;
        }
        
        pollData[pos] = toupper(pollData[pos]);
        pollData[pos+1] = toupper(pollData[pos+1]);
        string state = pollData.substr(pos,2);                  //set the state code
        
        if(!isValidUppercaseStateCode(state))
        {
            cerr << "state code" <<endl;
            return false;
        }
        
        pos +=2;
        if (pos == pollData.size())                         //for the existance of vote count
        {
            cerr << "vote count non-exsitant"<< endl;
            return false;
        }
        
        
        if (!isdigit(pollData[pos]))               //vote counts
        {
            cerr << "first character of vote is not a digit " <<endl;
            return false;
        }
        
        string num = "";                        //
        while (isdigit(pollData[pos]))
        {
            num += pollData[pos];             //
            pos++;
        }
        
        if (num == "" || pos == pollData.size() || num.size() > 2)        //for the existance of party code
        {
            cerr << "wrong number or no party code" << endl;
            return false;
        }
        
        if (!isalpha(pollData[pos]))              //party code
        {
            cerr << "party code" <<endl;
            return false;
        }
        
        pos++;
        
        
    }
    return true;
}