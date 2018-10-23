//
//  main.cpp
//  dis1
//
//  Created by 杨子鸣 on 9/30/16.
//  Copyright © 2016 杨子鸣. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    cout << "How many hours did you work? ";
    double Hoursworked;
    cin >> Hoursworked;
    cout << "What is your hourly rate of pay? " << endl;
    double payRate;
    cin >> payRate;
    double atmEarned = Hoursworked * payRate;
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "You earned $" << atmEarned << endl;
    cout << "$" << (0.1 * atmEarned) << "will be withheld" <<endl;
    
}