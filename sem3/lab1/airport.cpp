#include <iostream>
#include <string>
#include <limits>
#include <locale>    
#include <codecvt> 


using namespace std;

class Airport {
    private:
        string airportName;
        int ticketPrice;
        int numberOfSeats;
        int ticketsSold;

    public:
        int priceOfSoldTitckes() {
            return ticketPrice * ticketsSold;
        }

        int getTicketsPrice() {
            return ticketPrice;
        }

        int getTicketsSold() {
            return ticketsSold;
        }   

        int getNumberOfSeats() {
            return numberOfSeats;
        }

        string getAirportName() {
            return airportName;
        }

        void setTicketsSold(int sold) {
            ticketsSold = sold;
        }

        void setTicketPrice(int price) {
            ticketPrice = price;
        }

        void setNumberOfSeats(int seats) {
            numberOfSeats = seats;
        }

        void setAirportName(string name) {
            airportName = name;
        }

};

int getIntInput(string prompt, string errorMessage,int minValue = numeric_limits<int>::min() , int maxValue = numeric_limits<int>::max()) {
    int value;
    cout << prompt;
    cin >> value;
    while(cin.fail() || maxValue < value || value < minValue) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
        cin >> value;
    }
    
    return value;
}

string getStringInput(string prompt, string errorMessage) {
    string value;
    cout << prompt;
    cin >> value;
    while(value.empty() || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
        cin >> value;
    }
    
    return value;
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Airport Airport;
    Airport.setAirportName(getStringInput("Введите имя аэропорта: ", "Ошибка! Введите корректное имя аэропорта: "));
    Airport.setTicketPrice(getIntInput("Введите цену билета: ", "Ошибка! Введите корректную цену билета: ", 1));
    Airport.setNumberOfSeats(getIntInput("Введите количество мест: ", "Ошибка! Введите корректное количество мест: ", 1)); 
    Airport.setTicketsSold(getIntInput("Введите количество проданных билетов: ", "Ошибка! Введите корректное количество проданных билетов: ", 0, Airport.getNumberOfSeats()));
    cout << "------------------------" << endl;
    cout << "Имя аэропорта: " << Airport.getAirportName() << endl;
    cout << "Цена билета: " << Airport.getTicketsPrice() << endl;
    cout << "Количество мест: " << Airport.getNumberOfSeats() << endl;
    cout << "Количество проданных билетов: " << Airport.getTicketsSold() << endl;
    cout << "------------------------" << endl;
    cout << "Цена проданных билетов: " << Airport.priceOfSoldTitckes() << endl;
    return 0;
}
