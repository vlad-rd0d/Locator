//*****************************************************************
// File:		main.cpp
// Created:		QtCreator
// Author:		Vlad Shchekunov aka RD0D
// Description:
//*****************************************************************
#include <iostream>
#include "locator.h"

using namespace std;

int main(int argc, char* argv[])
{
    Locator *loc;
    string my_loc, his_loc;
    int qrb, azimut;
    try
    {
        if(argc < 3) throw "Error! Few arguments!\nUsage: locator my_locator his_locator";
        loc = new Locator();            // конструктор
        loc->set_myloc(argv[1]);        // передаём аргументы командной строки: argv[1] - my locator
        loc->set_hisloc(argv[2]);       // argv[2] - his locator
        my_loc = loc->get_myloc();
        his_loc = loc->get_hisloc();
        loc->calc_azdist();              // рассчитываем азимут и расстояние
        qrb = (int)loc->get_distance();
        azimut = (int)loc->get_azimut();
        /* Вывод результатов раблты программы */
        cout << "=========================" << endl;
        cout << my_loc << "  ----->  " << his_loc << endl;
        cout << "-------------------------" << endl;
        cout << "My latitude:\t" << loc->get_mylat() << endl;
        cout << "My longitude:\t" << loc->get_mylong() << endl;
        cout <<  "-------------------------" <<endl;
        cout << "His latitude:\t" << loc->get_hislat() << endl;
        cout << "His longitude:\t" << loc->get_hislong() << endl;
        cout <<  "-------------------------" <<endl;
        cout << "Distance:\t" << qrb << " km." << endl;
//        cout << "Azimut:\t\t" << azimut << "°" << endl;
        cout << "Azimut:\t\t" << azimut << "\xC2\xB0" << endl;
        cout << "=========================" << endl;
    }
    catch (const char* err)
    {
        cerr << err << endl;
    }
    delete loc;

    return 0;
}
