#include "locator.h"

using namespace std;

Locator::Locator()
{
    myloc = "XX00XX";
    hisloc = "XX00XX";
    azimut = 0.0;
    dist = 0.0;
    my_lon = 0.0;
    my_lat = 0.0;
    his_lon = 0.0;
    his_lat = 0.0;
}

Locator::~Locator()
{
    //
}

bool Locator::islocator(string locator)
{
    regex re("[A-Ra-r]{2}[0-9]{2}[A-Za-z]{2}");
    bool result = regex_match(locator, re);
    return result;
}

void Locator::set_myloc(string locator)
{
    if(this->islocator(locator))
    {
        this->myloc = loc_to_upper(locator);
        this->my_lat = latitude(this->myloc);
        this->my_lon = longitude(this->myloc);
    }
}

void Locator::set_hisloc(string locator)
{
   if(this->islocator(locator))
   {
       this->hisloc = loc_to_upper(locator);
       this->his_lat = latitude(this->hisloc);
       this->his_lon = longitude(this->hisloc);
   }
}

void Locator::set_myloc()
{
    cout << "Enter your locator: "; cin >>this->myloc;
    this->myloc = loc_to_upper(this->myloc);
}

void Locator::set_hisloc()
{
    cout << "Enter his locator: "; cin >> this->hisloc;
    this->hisloc = loc_to_upper(this->hisloc);
}

void Locator::show_myloc()
{
     cout << "My locator: " << this->myloc << endl;
}

void Locator::show_hisloc()
{
    cout << "His locator: " << this->hisloc << endl;
}

string Locator::get_myloc()
{
    return this->myloc;
}

string Locator::get_hisloc()
{
    return this->hisloc;
}

double Locator::get_mylong()
{
    return this->my_lon;// * 180.0 / M_PI;
}

double Locator::get_mylat()
{
    return this->my_lat;// * 180.0 / M_PI;
}

double Locator::get_hislong()
{
    return this->his_lon;// * 180.0 / M_PI;
}

double Locator::get_hislat()
{
    return this->his_lat;// * 180.0 / M_PI;
}

 /* Перевод символов локатора в верхний регистр */
string Locator::loc_to_upper(string locator)
{
    int i = 0;
    while (locator[i])
    {
        locator[i] = toupper(locator[i]);
        i++;
    }
    return locator;
}

/* Широта */
double Locator::latitude(string locator)
{
    double deg = 0.0;
    deg += 10.0 * ((int) locator[1] - (int) 'A');
    deg += (int) locator[3] - (int) '0';
    deg += ((int) locator[5] - (int) 'A') / 24.0 + 1/48.0;
    deg -= 90.0;
    return deg;
}

/* Долгота */
double Locator::longitude(string locator)
{
    double deg = 0.0;
    deg += 20.0 * ((int) locator[0] - (int) 'A');
    deg += 2.0 * ((int) locator[2] - (int) '0');
    deg += ((int) locator[4] - (int) 'A') / 12.0 + 1/24.0;
    deg -= 180.0;
    return deg;
}

/* Расстояние */
double Locator::qrb()
{
    double mylat = this->my_lat * rad;
    double mylon = this->my_lon * rad;
    double hislat = this->his_lat * rad;
    double hislon = this->his_lon * rad;
    return dz * acos(sin(mylat) * sin(hislat) + cos(mylat) * cos(hislat) * cos(mylon - hislon));
}

/* Азимут */
double Locator::direction()
{
    double mylat = this->my_lat * rad;
    double mylon = this->my_lon * rad;
    double hislat = this->his_lat * rad;
    double hislon = this->his_lon * rad;
    double ss = mylon - hislon;
    double dx = sin(mylat) * tan(hislat - M_PI / 2.0) + cos(mylat) * cos(ss);
    double az = -180.0 / M_PI * atan(sin(ss)/dx);
    if (dx < 0)
    {
        az += 180.0;
    }
    if (az > 360)
    {
        az -= 360.0;
    }
    if (az < 0)
    {
        az += 360.0;
    }
    return az;
}

void Locator::calc_azdist()
{
    this->azimut = this->direction();
    this->dist = this->qrb();
}

double Locator::get_azimut()
{
    return this->azimut;
}

double Locator::get_distance()
{
    return this->dist;
}
