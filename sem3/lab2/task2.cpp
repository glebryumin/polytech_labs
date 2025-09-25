#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Добавляем enum для типа тарифа
enum class TariffType {
    Economy,
    Business,
    Unknown
};

class Tariff {
    public:
        string name;
        int cost;
        TariffType type;

        Tariff(string n, int c, TariffType t = TariffType::Unknown)
            : name(n), cost(c), type(t) {}
};

class Client {
    public:
        string name;
        string passport;
};

class Ticket {
    public:
        Client client;
        Tariff tariff;
        Ticket() : client(), tariff("", 0, TariffType::Unknown) {}
};

class Till {
    private:
        vector<Ticket> tickets;
        vector<Tariff> tariffs;
        vector<Client> clients;
    public:
        void buyTicket(const Client& client, const Tariff& tariff) {
            Ticket ticket;
            ticket.client = client;
            ticket.tariff = tariff;
            tickets.push_back(ticket);
        }
        void addClient(const Client& client) {
            clients.push_back(client);
        }
        void addTariff(const Tariff& tariff) {
            tariffs.push_back(tariff);  
        }
        ~Till() {
            tickets.clear();
            tariffs.clear();
            clients.clear();
        }

        int summaryOfSoldTickets() const {
            int sum = 0;
            for (const auto& ticket : tickets) {
                sum += ticket.tariff.cost;
            }
            return sum;
        }

        int summaryOfSoldTicketsByName(const string& name) {
            int sum = 0;
            for (const auto& ticket : tickets) {
                if (ticket.client.name == name) {
                    sum += ticket.tariff.cost;
                }
            }
            return sum;
        }
};

int main() {
    Till Till;
    Client client1 = {"Иван Иванов", "1234 567890"};
    Client client2 = {"Петр Петров", "0987 654321"};
    Tariff tariff1 = {"Эконом", 100, TariffType::Economy};
    Tariff tariff2 = {"Бизнес", 200, TariffType::Business};
    Till.addClient(client1);
    Till.addClient(client2);
    Till.addTariff(tariff1);
    Till.addTariff(tariff2);
    Till.buyTicket(client1, tariff1);
    Till.buyTicket(client2, tariff2);
    Till.buyTicket(client1, tariff2);
    cout << "Общая сумма проданных билетов: " << Till.summaryOfSoldTickets() << endl;
    cout << "Сумма проданных билетов клиенту Иван Иванов: " << Till.summaryOfSoldTicketsByName("Иван Иванов") << endl;  

    return 0;
}