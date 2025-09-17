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
    while True:
        airportName = input("Введите имя аэропорта: ")
        if airportName.strip():
            break
        print("Ошибка! Введите корректное имя аэропорта.")

    while True:
        try:
            ticketPrice = int(input("Введите цену билета: "))
            if ticketPrice > 0:
                break
            else:
                print("Ошибка! Введите корректную цену билета.")
        except ValueError:
            print("Ошибка! Введите корректную цену билета.")

    while True:
        try:
            numberOfSeats = int(input("Введите количество мест: "))
            if numberOfSeats > 0:
                break
            else:
                print("Ошибка! Введите корректное количество мест.")
        except ValueError:
            print("Ошибка! Введите корректное количество мест.")

    while True:
        try:
            ticketsSold = int(input("Введите количество проданных билетов: "))
            if 0 <= ticketsSold <= numberOfSeats:
                break
            else:
                print("Ошибка! Введите корректное количество проданных билетов.")
        except ValueError:
            print("Ошибка! Введите корректное количество проданных билетов.")  

    airport = Airport(airportName=airportName, ticketPrice=ticketPrice, numberOfSeats=numberOfSeats, ticketsSold=ticketsSold)
    print("------------------------")
    print("Имя аэропорта:", airport.getAirportName())
    print("Цена билета:", airport.getTicketPrice())
    print("Количество мест:", airport.getNumberOfSeats())
    print("Количество проданных билетов:", airport.getTicketsSold())
    print("------------------------")
    print("Цена проданных билетов:", airport.priceOfSoldTickets())


if __name__ == "__main__":
    main()