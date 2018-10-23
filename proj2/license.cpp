//
//  license.cpp
//  proj2
//
//  Created by 杨子鸣 on 10/7/16.
//  Copyright © 2016 杨子鸣. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string Identification , Country;                // some basic settings
    double exptRvn, lcFee;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);
    
    cout << "Identification: ";                                 // input part
    getline(cin, Identification);
    if (Identification == "")
    {
        cout << "---" << endl;
        cout << "You must enter a property identification." << endl;
        return 1;
    }
    
    cout << "Expected revenue (in millions): ";
    cin >> exptRvn;
    cin.ignore(10000, '\n');
    if (exptRvn < 0)
    {
        cout << "---" << endl;
        cout << "The expected revenue must be nonnegetive." << endl;
        return 1;
    }
    
    cout << "Country: ";
    getline(cin, Country);
    if (Country == "")
    {
        cout << "---" << endl;
        cout << "You must enter a country." << endl;
        return 1;
    }
    
    
    
    
    if (Country == "UAE" || Country == "Turkey")                            //calculation part
    {
        if (exptRvn <= 20)
            lcFee = 18.1 / 100 * exptRvn;
        
        else if (exptRvn <= 50)
            lcFee = 18.1 / 100 * 20 + 21.7 / 100 * (exptRvn - 20);
        
        else
            lcFee = 18.1 / 100 * 20 + 21.7 / 100 * 30 + (exptRvn - 50) * 23 / 100;
                                                    // why i cannot but ()at the end???
    }
    
    else
    {
        if (exptRvn <= 20)
            lcFee = 18.1 / 100 * exptRvn;
        
        else if (exptRvn <= 50)
            lcFee = 18.1 / 100 * 20 + 20.3 / 100 * (exptRvn - 20);
        
        else
            lcFee = 18.1 / 100 * 20 + 20.3 / 100 * 30 + (exptRvn - 50) * 23 / 100;
    }
    
    
    
    
    cout << "---" << endl;                                                     //output part
    cout << "The license fee for " << Identification << " is $" << lcFee << " million." << endl;
    
}