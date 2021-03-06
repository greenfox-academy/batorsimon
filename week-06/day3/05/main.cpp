#include <iostream>

using namespace std;

// Create a Car class.
// Create the following private variables : age, kms_runed, manufacturer, number_of_seats
// use proper variable types.
// Implement a method which has one parameter, and increases the kms_runed variable by its parameter value.
// Implement a method which can add a person to a car, if the number of persons in the car reached
// the value of number of seats in the car it should tell you that 'The car is full!' or something like that.
// Inherite at least two car models and try out the methods you have created.

class Car{
    public:
        void set_age(int age){
            this->age = age;
        }
        void set_km_runed(int km_runed){
            this->km_runed = km_runed;
        }
        void set_manufacturer(string manufacturer){
            this->manufacturer = manufacturer;
        }
        void set_number_of_seats(int number_of_seats){
            this->number_of_seats = number_of_seats;
        }
        void set_number_of_people_in_car(int number_of_people_in_car){
            this->number_of_people_in_car = number_of_people_in_car;
        }

        void get_age(){
            cout << "Age of the car: " << age <<endl;
        }
        void get_km_runed(){
            cout << "Km-s the car have run: " << km_runed <<endl;
            }
        void get_manufacturer(){
            cout << "Manufacturer of the car: " << manufacturer <<endl;
        }
        void get_number_of_seats(){
            cout << "Number of seats in the car: " << number_of_seats <<endl;
        }
        void get_number_of_people_in_car(){
            if(number_of_people_in_car < number_of_seats){
                cout << "The number of people in the car: " << number_of_people_in_car <<endl;
            } else{
                cout << "Too much people in the car! " <<endl;
            }
        }

    private:
        int age;
        int km_runed;
        string manufacturer;
        int number_of_seats;
        int number_of_people_in_car;
};

class Audi: public Car{

};

class Peugeut: public Car{

};


int main()
{
    cout << "Peugeut: " << endl;
    Peugeut p;
    p.set_age(11);
    p.get_age();
    p.set_km_runed(192500);
    p.get_km_runed();
    p.set_manufacturer("Peugeut");
    p.get_manufacturer();
    p.set_number_of_seats(5);
    p.get_number_of_seats();
    p.set_number_of_people_in_car(6);
    p.get_number_of_people_in_car();

    cout << endl << "Audi: " << endl;
    Audi a;
    a.set_age(6);
    a.get_age();
    a.set_km_runed(2500);
    a.get_km_runed();
    a.set_manufacturer("Audi");
    a.get_manufacturer();
    a.set_number_of_seats(4);
    a.get_number_of_seats();
    a.set_number_of_people_in_car(2);
    a.get_number_of_people_in_car();

    return 0;
}
