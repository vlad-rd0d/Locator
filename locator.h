#ifndef LOCATOR_H
#define LOCATOR_H

#include <iostream>
#include <cmath>
#include <regex>

#define _USE_MATH_DEFINES

using namespace std;

class Locator
{
private:
    /* Диаметр Земли */
    double dz = 6365.0;
    /* Радиан */
    double rad = M_PI / 180.0;
    string myloc;
    string hisloc;
    double azimut;
    double dist;
    double my_lon;
    double my_lat;
    double his_lon;
    double his_lat;
    /* Проверка локатора на соответсвие шаблону */
    bool islocator(string locator);
    /* Перевод символов локатора в верхний регистр */
    string loc_to_upper(string locator);
    /* Широта */
    double latitude(string locator);
    /* Долгота */
    double longitude(string locator);
    /* Расстояние */
    double qrb();
    /* Азимут */
    double direction();
public:
    Locator();
    ~Locator();    
    void set_myloc();
    void set_myloc(string locator);
    void set_hisloc();
    void set_hisloc(string locator);
    void calc_azdist();
    string get_myloc();
    string get_hisloc();
    double get_mylong();
    double get_mylat();
    double get_hislong();
    double get_hislat();
    double get_azimut();
    double get_distance();
    void show_myloc();
    void show_hisloc();
};

#endif // LOCATOR_H
