class Airport:

    def __init__(self, airportName: str, ticketPrice: int, numberOfSeats: int, ticketsSold: int):
        self.airportName = airportName
        self.ticketPrice = ticketPrice
        self.numberOfSeats = numberOfSeats
        self.ticketsSold = ticketsSold

    def getAirportName(self) -> str:
        return self.airportName

    def getTicketPrice(self) -> int:
        return self.ticketPrice

    def getNumberOfSeats(self) -> int:
        return self.numberOfSeats

    def getTicketsSold(self) -> int:
        return self.ticketsSold
    
    def setAirportName(self, airportName: str):
        self.airportName = airportName
    
    def setTicketPrice(self, ticketPrice: int):
        self.ticketPrice = ticketPrice  
    
    def setNumberOfSeats(self, numberOfSeats: int):
        self.numberOfSeats = numberOfSeats
    
    def setTicketsSold(self, ticketsSold: int):
        self.ticketsSold = ticketsSold  
    
    def priceOfSoldTickets(self) -> int:
        return self.ticketPrice * self.ticketsSold


def main():
    airport = Airport(airportName="NJC", ticketPrice=500, numberOfSeats=500, ticketsSold=150)
    print("Airport Name:", airport.getAirportName())
    print("Ticket Price:", airport.getTicketPrice())
    print("Number of Seats:", airport.getNumberOfSeats())
    print("Tickets Sold:", airport.getTicketsSold())
    print("------------------------")
    print("Total Price of Sold Tickets:", airport.priceOfSoldTickets())


if __name__ == "__main__":
    main()