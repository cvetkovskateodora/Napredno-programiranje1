#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

enum CardValue{ // inicijaliziranje na broevi
    As = 1, Dva, Tri, Chetiri,
    Pet, Shest, Sedum, Osum,
    Devet, Deset, Dzandar, Chupa, Pop
};

static const std::string CardValues[] = { // string za broevite na kartite
    "As","Dvojka", "Trojka", "Chetvorka",
    "Petka", "Shestka", "Sedumka", "Osumka",
    "Devetka", "Desetka", "Dzandar", "Chupa", "Pop"
};

enum CardColor{ // inicijaliziranje na formi
    List, Srce, Baklava, Spato
};

static const std::string CardColors[] = { // string za formite
	"List", "Srce", "Baklava", "Spato"
};

class Card{ // izbiranje na broj i boja (forma)
    CardValue val_;
    CardColor color_;
public:
    Card(const CardValue &val, const CardColor &color){
        val_ = val; color_ = color;
    }
    const std::string &getValue() const {
		return CardValues[val_ - 1];
	}
    const std::string &getColor() const {
		return CardColors[color_];
	}
};

class Deck{ // inicijaliziranje na shpil od 52 karti, kade broevi ima 13, a formi 4
private:
    const int size_ = 52;
    std::vector<Card> Cards;
    static Deck *deckIn;
    Deck(){
        std::srand (unsigned (std::time(0))); // sluchajno izvlekuvanje
        for(int i=0; i<size_; i++){
            Cards.push_back(Card(CardValue((i+1)%13), CardColor(i%4)));
        }
        shuffle(); // meshanje
    }
public:
    ~Deck() { Cards.clear(); }

    static Deck &getInstance(){
        if(deckIn == NULL){
            deckIn = new Deck();
        }
        return *deckIn;
    }

    void shuffle(){
        std::random_shuffle (Cards.begin(), Cards.end()); // sluchajno izvlekuvanje na karti
    }

    Card getCard(){ // brishenje na vekje izvlechenata kombinacija
        int position = rand()%size_;
        Card choosen = Cards[position];
        Cards.erase(Cards.begin() + position);
        return choosen;
    }
};
Deck *Deck::deckIn = NULL;

int main() {
    Deck &deck = Deck::getInstance();
    for(int i=0; i<5; ++i){ // izvlekuvanje na 5 karti
        Card myCard = deck.getCard();
        std::cout<<myCard.getValue()<<" "<<myCard.getColor()<<"\n";
    }
    return 0;

}
