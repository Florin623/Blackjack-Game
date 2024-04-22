#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_set>

class Carte {
    uint16_t nr{};
    std::string stema;

public:
    Carte(const uint16_t& nr, std::string stema): nr(nr), stema(std::move(stema)) {}

    [[nodiscard]] uint16_t getnr() const {
        return nr;
    }

    [[nodiscard]] std::string getstema() const {
        return stema;
    }
};

class Jucator {
    std::string nume;
    double suma{};
    std::vector<Carte> carti;

public:
    explicit Jucator(std::string nume, const double& suma): nume(std::move(nume)), suma(suma) {}

    explicit Jucator(std::string nume): nume(std::move(nume)) {} //Dealer

    void add(const Carte& carte) {
        carti.emplace_back(carte);
    }

    void win(const double& malai) {
        suma += malai;
    }

    void lose(const double& malai) {
        suma -= malai;
    }

    [[nodiscard]] uint16_t calcPuncte() const {
        uint16_t s = 0;
        for (const auto& it : carti)
            if (it.getnr() > 10)
                s += 10;
            else
                s += it.getnr();
        return s;
    }

    [[nodiscard]] std::string getnume() const {
        return nume;
    }

    [[nodiscard]] double getsuma() const {
        return suma;
    }

    void resetcarti() {
        carti.clear();
    }
};

class Pachet {
    std::vector<Carte> carti;

public:
    Pachet() = default;

    void add(const Carte& carte) {
        carti.emplace_back(carte);
    }

    [[nodiscard]] Carte getCarte(const uint16_t& poz) const {
        return carti[poz];
    }

    uint16_t check_carti() {
        bool cond = false;
        for (const auto& it : carti) {
            cond = false;
            if (it.getnr() >= 2 && it.getnr() <= 14) {
                if (it.getstema() == "rosu" || it.getstema() == "negru" || it.getstema() == "romb" || it.getstema() == "trefla")
                    cond = true;
                if (!cond) {
                    std::cout << "Pachet masluit\n";
                    return 0;
                }
            }
            else {
                std::cout << "Pachet masluit\n";
                return 0;
            }
        }

        cond = true;
        if (carti.size() == 52) {
            for (uint16_t i = 0; i < carti.size() - 1; ++i)
                for (uint16_t j = i + 1; j < carti.size(); ++j)
                    if (carti[i].getnr() == carti[j].getnr() && carti[i].getstema() == carti[j].getstema())
                        cond = false;
            if (cond) {
                std::cout << "Pachet OK\n";
                return 1;
            }
        }
        else
            std::cout << "Pregatit pentru Blackjack\n";
        return 1;
    }

    void shuffle_Pachet(const uint16_t& a, uint16_t& x0, const uint16_t& c, const uint16_t& a1, uint16_t& x01, const uint16_t& c1) {
        for (uint16_t i = 0; i < 50; ++i) {
            x0 = (a * x0 + c) % carti.size();
            x01 = (a1 * x01 + c1) % carti.size();
            std::swap(carti[x0], carti[x01]);
        }
    }

    void print() const {
        for (const auto& it : carti)
            std::cout << it.getnr() << ',' << it.getstema() << '\n';
    }
};

int main() {
    Pachet Pachet;
    std::string command;
    std::cin >> command;
    if (command == "check_cards") {
        uint16_t nr;
        char v;
        std::string stema;
        while (std::cin >> nr >> v >> stema)
            Pachet.add(Carte(nr, stema));
        Pachet.check_carti();
    }
    else if (command == "shuffle_cards") {
        uint16_t a, c, x0, a1, c1, x01, nr;
        std::cin >> a >> c >> x0 >> a1 >> c1 >> x01;
        char v;
        std::string stema;
        while (std::cin >> nr >> v >> stema)
            Pachet.add(Carte(nr, stema));
        Pachet.shuffle_Pachet(a, x0, c, a1, x01, c1);
        Pachet.print();
    }
    else if (command == "play_game") {
        std::vector<Jucator> jucatori;
        uint16_t nr_jucatori;
        std::cin >> nr_jucatori;
        for (uint16_t i = 0; i < nr_jucatori; ++i) {
            std::string nume_jucator;
            double suma_jucator;
            std::cin >> nume_jucator >> suma_jucator;
            Jucator newJucator(nume_jucator, suma_jucator);
            jucatori.emplace_back(newJucator);
        }

        for (uint16_t i = 0; i < 4; ++i)
            for (uint16_t j = 2; j <= 14; ++j) {
                if (j != 11) {
                    uint16_t nr;
                    std::string stema;
                    switch (nr) {
                        case 0:
                            stema = "rosu";
                            break;
                        case 1:
                            stema = "negru";
                            break;
                        case 2:
                            stema = "romb";
                            break;
                        case 3:
                            stema = "trefla";
                            break;
                    }
                    nr = j;
                    Carte newCarte(nr, stema);
                    Pachet.add(newCarte);
                }
            }
        uint16_t a, c, x0, a1, c1, x01;
        Jucator Dealer("Dealer");
        while (std::cin >> a) {
            std::cin >> c >> x0 >> a1 >> c1 >> x01;
            Pachet.shuffle_Pachet(a, x0, c, a1, x01, c1);
            uint16_t poz_cur_carte = 0;
            bool gata_runda = false;
            std::unordered_set<std::string> jucatori_out;

            Dealer.resetcarti();
            for (auto& it : jucatori) {
                it.resetcarti();
                for (uint16_t j = 0; j < 2; ++j) {
                    Carte newCarte = Pachet.getCarte(poz_cur_carte++);
                    it.add(newCarte);
                }
            }

            for (uint16_t i = 0; i < 2; ++i) {
                Carte newCarte = Pachet.getCarte(poz_cur_carte++);
                Dealer.add(newCarte);
            }

            for (auto& it : jucatori)
                while (it.calcPuncte() <= 16) {
                    Carte newCarte = Pachet.getCarte(poz_cur_carte++);
                    it.add(newCarte);
                }
            while (Dealer.calcPuncte() <= 16) {
                Carte newCarte = Pachet.getCarte(poz_cur_carte++);
                Dealer.add(newCarte);
            }

            if (Dealer.calcPuncte() > 21) {
                for (auto& it : jucatori)
                    if (it.calcPuncte() <= 21)
                        it.win(10);
                    else {
                        it.lose(10);
                        if (it.getsuma() < 10)
                            jucatori_out.insert(it.getnume());
                    }
                gata_runda = true;
            }

            if (!gata_runda)
                for (auto& it : jucatori) {
                    if (it.calcPuncte() > Dealer.calcPuncte())
                        if (it.calcPuncte() > 21) {
                            it.lose(10);
                            if (it.getsuma() < 10)
                                jucatori_out.insert(it.getnume());
                        }
                        else
                            it.win(10);
                    else if (it.calcPuncte() < Dealer.calcPuncte()) {
                        it.lose(10);
                        if (it.getsuma() < 10)
                            jucatori_out.insert(it.getnume());
                    }
                }

            for (const auto& it : jucatori_out)
                for (uint16_t j = 0; j < jucatori.size(); ++j)
                    if (it == jucatori[j].getnume()) {
                        jucatori.erase(jucatori.begin() + j);
                        break;
                    }
        }
        for (const auto& it : jucatori)
            std::cout << it.getnume() << ": " << it.getsuma() << "\n";
    }
    return 0;
}