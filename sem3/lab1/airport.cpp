#include <iostream>
#include <string>


using namespace std;

class Airport {
    private:
    string airportName = "";
    int ticketPrice = 0;
    int numberOfSeats = 0;
    int ticketsSold = 0;

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

int main(){
    Airport Airport;
    Airport.setAirportName("NJC");
    Airport.setTicketPrice(5000);
    Airport.setNumberOfSeats(500); 
    Airport.setTicketsSold(150);
    cout << "Airport Name: " << Airport.getAirportName() << endl;
    cout << "Ticket Price: " << Airport.getTicketsPrice() << endl;
    cout << "Number of Seats: " << Airport.getNumberOfSeats() << endl;
    cout << "Tickets Sold: " << Airport.getTicketsSold() << endl;
    cout << "------------------------" << endl;
    cout << "Price of Sold Tickets: " << Airport.priceOfSoldTitckes() << endl;
    return 0;
}
