#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;


class Tariff {
    public:
        string name;
        int cost;
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

    
        const vector<Client>& getClients() const {
            return clients;
        }

        const vector<Tariff>& getTariffs() const {
            return tariffs;
        }

        const vector<Ticket>& getTickets() const {
            return tickets;
        }
};

int getIntInput(string prompt, string errorMessage, int minValue = numeric_limits<int>::min(), int maxValue = numeric_limits<int>::max()) {
    int value;
    string input;
    cout << prompt << endl;
    while (true) {
        cin >> input;
        bool isValid = !input.empty() && (input[0] == '-' ? input.size() > 1 : true);
        for (size_t i = (input[0] == '-' ? 1 : 0); i < input.size(); ++i) {
            if (!isdigit(input[i])) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            try {
                size_t pos;
                value = stoi(input, &pos);
                if (pos == input.size() && value >= minValue && value <= maxValue) {
                    break;
                }
            } catch (...) {}
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
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

enum MenuAction {
    ADD_TARIFF = 1,
    ADD_CLIENT,
    BUY_TICKET,
    CLIENT_SUM,
    TOTAL_SUM,
    SHOW_TARIFFS,
    SHOW_CLIENTS,
    SHOW_TICKETS,
    EXIT = 0
};

int main() {
    Till till;
    while (true) {
        cout << endl << "Меню:" << endl;
        cout << "1) Добавить тариф" << endl;
        cout << "2) Ввести данные пассажира" << endl;
        cout << "3) Зарегистрировать покупку билета" << endl;
        cout << "4) Рассчитать стоимость купленных билетов конкретным пассажиром" << endl;
        cout << "5) Рассчитать стоимость всех проданных билетов" << endl;
        cout << "6) Показать все тарифы" << endl;
        cout << "7) Показать всех пассажиров" << endl;
        cout << "8) Показать все билеты" << endl;
        cout << "0) Выход" << endl;
        int choice = getIntInput("Выберите пункт меню: ", "Ошибка ввода!", 0, 8);
        cout << endl;

        if (choice == EXIT) break;

        if (choice == ADD_TARIFF) {
            Tariff tariff;
            tariff.name = getStringInput("Введите название тарифа: ", "Ошибка ввода!");
            tariff.cost = getIntInput("Введите стоимость тарифа: ", "Ошибка ввода!", 1);
            till.addTariff(tariff);
            cout << "Тариф добавлен." << endl;
        } else if (choice == ADD_CLIENT) {
            Client client;
            client.name = getStringInput("Введите имя клиента: ", "Ошибка ввода!");
            client.passport = getStringInput("Введите паспорт клиента: ", "Ошибка ввода!");
            till.addClient(client);
            cout << "Клиент добавлен." << endl;
        } else if (choice == BUY_TICKET) {
            if (till.getClients().empty() || till.getTariffs().empty()) {
                cout << "Нет клиентов или тарифов для покупки билета." << endl;
                continue;
            }
            cout << "Выберите клиента:" << endl;
            const auto& clients = till.getClients();
            for (size_t i = 0; i < clients.size(); ++i) {
                cout << i + 1 << ") " << clients[i].name << " (" << clients[i].passport << ")" << endl;
            }
            int clientIdx = getIntInput("Введите номер клиента: ", "Ошибка ввода!", 1, clients.size()) - 1;

            cout << "Выберите тариф:" << endl;
            const auto& tariffs = till.getTariffs();
            for (size_t i = 0; i < tariffs.size(); ++i) {
                cout << i + 1 << ") " << tariffs[i].name << " (" << tariffs[i].cost << ")" << endl;
            }
            int tariffIdx = getIntInput("Введите номер тарифа: ", "Ошибка ввода!", 1, tariffs.size()) - 1;

            till.buyTicket(clients[clientIdx], tariffs[tariffIdx]);
            cout << "Билет куплен." << endl;
        } else if (choice == CLIENT_SUM) {
            if (till.getClients().empty()) {
                cout << "Нет клиентов." << endl;
                continue;
            }
            cout << "Выберите клиента:" << endl;
            const auto& clients = till.getClients();
            for (size_t i = 0; i < clients.size(); ++i) {
                cout << i + 1 << ") " << clients[i].name << " (" << clients[i].passport << ")" << endl;
            }
            int clientIdx = getIntInput("Введите номер клиента: ", "Ошибка ввода!", 1, clients.size()) - 1;
            int sum = till.summaryOfSoldTicketsByName(clients[clientIdx].name);
            cout << "Сумма купленных билетов для " << clients[clientIdx].name << ": " << sum << endl;
        } else if (choice == TOTAL_SUM) {
            int sum = till.summaryOfSoldTickets();
            cout << "Общая сумма проданных билетов: " << sum << endl;
        } else if (choice == SHOW_TARIFFS) {
            const auto& tariffs = till.getTariffs();
            if (tariffs.empty()) {
                cout << "Нет тарифов." << endl;
            } else {
                cout << "Тарифы:" << endl;
                for (size_t i = 0; i < tariffs.size(); ++i) {
                    cout << i + 1 << ") " << tariffs[i].name << " (Стоимость: " << tariffs[i].cost << ")" << endl;
                }
            }
        } else if (choice == SHOW_CLIENTS) {
            const auto& clients = till.getClients();
            if (clients.empty()) {
                cout << "Нет пассажиров." << endl;
            } else {
                cout << "Пассажиры:" << endl;
                for (size_t i = 0; i < clients.size(); ++i) {
                    cout << i + 1 << ") " << clients[i].name << " (Паспорт: " << clients[i].passport << ")" << endl;
                }
            }
        } else if (choice == SHOW_TICKETS) {
            const auto& tickets = till.getTickets();
            if (tickets.empty()) {
                cout << "Нет билетов." << endl;
            } else {
                cout << "Билеты:" << endl;
                for (size_t i = 0; i < tickets.size(); ++i) {
                    cout << i + 1 << ") "
                         << "Пассажир: " << tickets[i].client.name << " (Паспорт: " << tickets[i].client.passport << "), "
                         << "Тариф: " << tickets[i].tariff.name << " (Стоимость: " << tickets[i].tariff.cost << ")" << endl;
                }
            }
        }
    }
    till.~Till();
    return 0;
}