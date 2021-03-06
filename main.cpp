#include <iostream>
#include <conio.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
int a1, a2;
struct challandata
{
    string chno;
    string date;
    float mtl;
};

struct billdata
{
    string bno;
    string date;
    float mtl;
};
challandata c[200];
billdata b[200];
void readch(string filename)
{
    fstream file;
    file.open(filename.c_str());
    for (int i = 0; i < a1; i++)
    {
        file >> c[i].chno;
        file >> c[i].date;
        file >> c[i].mtl;
    }
    file.close();
}
void readb(string filename)
{
    fstream file;
    file.open(filename.c_str());
    for (int i = 0; i < a2; i++)
    {
        file >> b[i].bno;
        file >> b[i].date;
        file >> b[i].mtl;
    }
    file.close();
}

int main()
{
    cout << "Enter No of Challan: ";
    cin >> a1;
    cout << "Enter No of Bill: ";
    cin >> a2;
    string file1 = "challan.txt";
    string file2 = "bill.txt";
    readch(file1);
    readb(file2);
    ofstream myfile;
    myfile.open("final.txt");
    myfile << "BILL NO;DATE;MATERIAL SENT;CHALLAN NO;DATE;MATERIAL RECIEVED;OPENING BALANCE;MATERIAL SENT;BALANCE";
    float bal;
    int l = 1;
    int m = 0;
    float tempbal = 0;
    bal = c[0].mtl;
    for (int k = 0; k < a2; k++)
    {
        m = l;
        tempbal = bal;
        while (b[k].mtl > bal)
        {
            bal = bal + c[l].mtl;
            l++;
        }

        myfile << fixed << setprecision(3) << endl
               << b[k].bno << ";" << b[k].date << ";" << b[k].mtl;
        if (b[k].mtl > tempbal)
            myfile << fixed << setprecision(3) << ";" << c[m - 1].chno << ";" << c[m - 1].date << ";;" << tempbal << ";" << tempbal << ";0.000" << endl;
        else
            myfile << fixed << setprecision(3) << ";" << c[m - 1].chno << ";" << c[m - 1].date << ";;" << tempbal << ";" << b[k].mtl << ";" << tempbal - b[k].mtl << endl;
        bal = bal - b[k].mtl;
        for (int a = m; a < l - 1; a++)
        {
            myfile << fixed << setprecision(3) << ";;;" << c[a].chno << ";" << c[a].date << ";" << c[a].mtl << ";;" << c[a].mtl << ";0.000" << endl;
        }
        if (m < l)
        {
            myfile << fixed << setprecision(3) << ";;;" << c[l - 1].chno << ";" << c[l - 1].date << ";" << c[l - 1].mtl << ";;" << c[l - 1].mtl - bal << ";" << bal << endl;
        }
        myfile << fixed << setprecision(3) << ";;;;;;TOTAL;" << b[k].mtl << endl;
    }
    myfile.close();
    cout << "DONE!" << endl;
    return 0;
}
