// Deze code bestaat uit 3 classes en een main functie.
#include <SFML/Graphics.hpp>// deze libary dient voor het omgaan van graphics
#include <Windows.h>// deze libary wordt gebruik voor specifieke windows API functies
#include <vector>// heeft vector containers uit de STL
#include <string>// gebruik van de stringklasse in STL (gebruiken voor tekst manupilatie)
#include <iostream>// input en output libary
#include <algorithm>// verzameling algoritmen idg wordt het gebruikt voor soorten zoeken
#include <random>// deze dient om de kaarten te randomizen
#include <ctime>// tijdfuncties die worden gebruikt voor getallengenerator


using namespace std;

class Player {
public:
    Player(const string& playerName) : name(playerName), score(0) {}
    // constructor met parameters
    string getName() const { return name; }//de naam van de spelers zonder iets te veranderen van het object
    int getScore() const { return score; }//score van de speler
    void updateScore() { score++; }//  player score verhogen met 1
    void switchPlayer(Player*& currentPlayer, Player& player1, Player& player2) {//currentplayer is een pointer
        // wissel van de spelers, player 1 en 2 zijn referenties 
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }// zorgt voor het roteren van de ene naar de andere speler

private:
    string name;//naam van de speler
    int score;// score van de speler
};

class Card {
public:
    Card(float width, float height) : shape(sf::Vector2f(width, height)), flipped(false), frontTexture(nullptr) {}
    // constructor met parameters, shape van de kaart, de kaart is niet omgedraait en fronttexture is nog niet ingesteld.
    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }// positie van de kaarten instellen
    bool contains(sf::Vector2f point) const {
        return shape.getGlobalBounds().contains(point);
    }//controleert of de gegeven punt binnen de grenzen van de kaart ligt.
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }// tekenen van de kaart in  de venster. 
    void flip() {
        flipped = !flipped;
        shape.setTexture(flipped ? frontTexture : backTexture);
    } // dient voor het draaien van de kaart. indien het gedraait is zal het fronttexture weergegeven worden
    bool isFlipped() const {
        return flipped;
    }// dient voor het terugkeren van de kaart
    void setFrontTexture(const sf::Texture& texture) {
        frontTexture = &texture;
        if (flipped) shape.setTexture(frontTexture);
    }// dient voor het stellen van de voorzijde (fronttexture)
    void setBackTexture(const sf::Texture& texture) {
        backTexture = &texture;
        if (!flipped) shape.setTexture(backTexture);
    }// dient voor het stellen van de achterzijde (backtexture)
    static void loadTextures(const vector<string>& filenames, vector<sf::Texture>& frontTextures, vector<int>& cardIndices) {
        for (const auto& filename : filenames) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                cerr << "Error loading texture: " << filename << endl;
                return;
            }
            frontTextures.push_back(texture);
        }
        cardIndices = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8 };
        shuffle(cardIndices.begin(), cardIndices.end(), default_random_engine(static_cast<unsigned int>(time(0))));
    }//Deze methode laadt een reeks afbeeldingen (textures) voor de voorkant van de kaarten,
    //en shufflet vervolgens de indices om de kaarten willekeurig te verdelen.
    static void setCardPositions(vector<Card>& cards, float cardWidth, float cardHeight, float spacing) {
        for (int i = 0; i < cards.size(); ++i) {
            int row = i / 6;
            int col = i % 6;
            cards[i].setPosition(col * (spacing + cardWidth + spacing), row * (spacing + cardHeight + spacing));
        }
    }// deze functie dient voor het positie van de kaarten in de venster

private:
    sf::RectangleShape shape;// grafische representie van de kaart. hoe de kaart eruit zal zien
    bool flipped;// geeft aan of de kaart is omgedraaid
    const sf::Texture* frontTexture; //pointer naar de voorkant van de kaart
    const sf::Texture* backTexture;// pointer naar de achterkant van de kaart
};

class MemoryGame {
public:
    MemoryGame();//constructor, initialiseert het venster met de daaropbestemde functies
    void run();//Start de hoofdgameloop waar het spel wordt uitgevoerd

private:
    void draw();//Tekent alle kaarten en bijgewerkte scores
    void handleEvents();// verwerkt de handelingen van de gebruiker(muisklick)
    void checkMatch();//controleren van de omgedraaide kaarten (gelijksoorten)
    void resetGame();// restart de game na 1 ronde

    sf::RenderWindow window;//sfml venster plaatsen op de scherm
    vector<Card> cards;// dient voor de kaarten in het spel
    vector<sf::Texture> frontTextures;//textures voorkant van de kaarten
    sf::Texture backTexture;// textures achterkant van de kaarten
    vector<int> cardIndices;//een geshuffel lijst van indices om de kaarten willekeurig te verdelen
    const vector<string> filenames = {
       "C:/Users/User/Desktop/Images/Card_0.jfif",
        "C:/Users/User/Desktop/Images/Card_1.jfif",
        "C:/Users/User/Desktop/Images/Card_2.jfif",
        "C:/Users/User/Desktop/Images/Card_3.jfif",
        "C:/Users/User/Desktop/Images/Card_4.jfif",
        "C:/Users/User/Desktop/Images/Card_5.jfif",
        "C:/Users/User/Desktop/Images/Card_6.jfif",
        "C:/Users/User/Desktop/Images/Card_7.jfif",
        "C:/Users/User/Desktop/Images/Card_8.jfif"//dient voor de textures van de verschillende kaarten
    };
    const std::string backFilename ="C:/Users/User/Desktop/Images/Background.jfif" ;
    //dient voor de texture van de achterkant van de kaarten
    const float cardWidth = 100.0f;
    const float cardHeight = 150.0f;
    const float spacing = 20.0f;
    // lengte, breedte en verte van de kaarten
    int firstCardIndex;// dient voor de omgedraaide kaarten
    int secondCardIndex;
    bool checkingMatch;//aangeeft of het spel wacht op matchcontrole
    sf::Clock clock;// dient voor de tijd tussen het beurt van de volgende speler

    Player player1;//Objecten en pointer voor spelersbeheer
    Player player2;
    Player* currentPlayer;

    sf::Font font;//dient voor het behouden van de score (scoreboard)
    sf::Text scoreText;
    sf::Text turnText;
};

MemoryGame::MemoryGame()
    : window(sf::VideoMode(800, 600), "Memory Game"), firstCardIndex(-1), secondCardIndex(-1), checkingMatch(false),
    player1("Player 1"), player2("Player 2"), currentPlayer(&player1) {
    Card::loadTextures(filenames, frontTextures, cardIndices);
    //window en dient voor het bijhouden van de geselecteerde kaarten
    if (!backTexture.loadFromFile(backFilename)) {
        cerr << "Error loading back texture: " << backFilename << endl;
    }//dient voor de backtexture. indien het mislukt het functie verder

    for (int i = 0; i < 18; ++i) {
        cards.emplace_back(cardWidth, cardHeight);
        cards[i].setFrontTexture(frontTextures[cardIndices[i]]);
        cards[i].setBackTexture(backTexture);
    }//instelling 18 kaarten, back en front texture 
    Card::setCardPositions(cards, cardWidth, cardHeight, spacing);
    // nadat alles wordt ingesteld worden de kaarten in de posities gezet
    if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
        cerr << "Error loading font!" << endl;
    }// deze file dient voor de lettertype van de tekst

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 550);
    // instelling scoretext
    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(550, 550);
}//instelling wie de volgende spelers beurt is text

void MemoryGame::run() {
    while (window.isOpen()) {//game blijft draaien zolang het venster open is
        handleEvents();// verwerking van de gebruikers invoering
        if (checkingMatch) {// controleren van de kaarten en tijdsvertraging
            if (clock.getElapsedTime().asSeconds() > 1.0f) {
                checkMatch();
            }
        }
        window.clear();// wissen van de window om een nieuw game te starten
        draw();// opnieuw de kaarten en gegevens plaatsen in de window
        window.display();// het inhoud plaatesen
    }
}

void MemoryGame::draw() {
    for (const auto& card : cards) {//&auto(constante referentie)
        card.draw(window);
    }

    scoreText.setString(player1.getName() + ": " + to_string(player1.getScore()) + "  " +
        player2.getName() + ": " + to_string(player2.getScore()));//namen en scores van beide spelers op te nemen
    turnText.setString(currentPlayer->getName() + "'s Turn");//dit wordt gedaan door getname en getScore
    //aangeving beurt
    window.draw(scoreText);// tekent het scoreTekst op de venster(window)
    window.draw(turnText);//tekent het scoreTekst op de venster(window)
}

void MemoryGame::handleEvents() {
    sf::Event event;//wordt aangemaakt om individuele gebeurtenissen op te slaan
    //die door het venster worden gegenereerd
    while (window.pollEvent(event)) {//alle gebeurtenissen uit de gebeurteniswachtrij
        //en verwerkt ze een voor een totdat er geen meer zijn
        if (event.type == sf::Event::Closed)
            window.close();//venster gesloten indien de gebruiker dat doet
        if (event.type == sf::Event::MouseButtonPressed && !checkingMatch) {//uisklik is gedetecteerd en er geen controle op een match wordt uitgevoerd
            //wordt verder gekeken naar het type muisklik.
            if (event.mouseButton.button == sf::Mouse::Left) {//controleert linkermuisknop
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);//huidige positie van de muis in venstercoördinaten.
                for (int i = 0; i < 18; ++i) {//reageert op de klikken van de muis
                    if (cards[i].contains(static_cast<sf::Vector2f>(mousePos)) && !cards[i].isFlipped()) {
                        // de muispositie zich binnen de grenzen van de kaart
                            //bevindt en of de kaart niet al omgedraaid is
                        if (firstCardIndex == -1) {// controleert of index is ingesteld, indien niet wordt het wel ingesteld
                            firstCardIndex = i;
                        }
                        else if (secondCardIndex == -1) {
                            secondCardIndex = i;
                            checkingMatch = true;
                            clock.restart();//vlag wordt geactiveerd, en de klok wordt gereset
                        }
                        cards[i].flip();//roept de functie flip aan
                        break;//beeindiging van de forloop
                    }
                }
            }
        }
    }
}

void MemoryGame::checkMatch() {
    if (cardIndices[firstCardIndex] == cardIndices[secondCardIndex]) {// dient voor het checken of
        //de kaarten hetzelfde zijn
        currentPlayer->updateScore();//update van de score indien de kaarten overeenkomen
    }
    else {// indien ze niet overeenkomen zullen de kaarten weer omgedraaid worden
        cards[firstCardIndex].flip();
        cards[secondCardIndex].flip();
        currentPlayer->switchPlayer(currentPlayer, player1, player2);//player wordt dan verwisselt
    }
    firstCardIndex = -1;
    secondCardIndex = -1;//deze functies worden gereset
    checkingMatch = false;

    bool allFlipped = all_of(cards.begin(), cards.end(), [](const Card& card) { return card.isFlipped(); });
    if (allFlipped) {//controle of alle kaarten omgedraaid zijn
        cout << "Game over! " << (player1.getScore() > player2.getScore() ? player1.getName() : player2.getName()) << " wins!" << endl;
        resetGame();// reset wordt aangeroepen 
    }
}

void MemoryGame::resetGame() {
    shuffle(cardIndices.begin(), cardIndices.end(), default_random_engine(static_cast<unsigned int>(time(0))));
    //shuffelen van de kaarten
    for (int i = 0; i < cards.size(); ++i) {//herstellen van de kaarten
        cards[i].setFrontTexture(frontTextures[cardIndices[i]]);
        if (cards[i].isFlipped()) cards[i].flip();// indien alle kaarten omgedraaid zijn zal het game eindigen
    }
    player1 = Player("Player 1");// opnieuw intitialiseren van de players
    player2 = Player("Player 2");
    currentPlayer = &player1;// player 1 zal dan opnieuw moeten spelen
}

int main() {
    system("COLOR 7D");
    system("cls");
    printf("\Memory Card game");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\n\t\t\t\t\tWELCOME";
    //cout << "\n\n\n\n\t\t\t\tschool project";
    cout << "\n\n\n\t\t\t\t";

    for (int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(150);
    }

    cout << "\n\t\t\t\t" << (char)1 << "!";
    system("Pause");
    MemoryGame game; // Creëert een instantie van de MemoryGame klasse
    game.run();      // Start de hoofdgame
    return 0;        // Beëindigt het programma succesvol
}
