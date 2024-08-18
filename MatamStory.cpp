#include "MatamStory.h"

#include "Utilities.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IsValidCard{
public:
    IsValidCard() = default;
    explicit IsValidCard(const string& word):card(word){}
    bool operator()(){
        for(const auto& it : vaidCards){
            if(card == it) {
                return true;
            }
        }
        return false;
    }
private:
    string card;
    string vaidCards[5] = {"Snail","Slime","Balrog","PotionMerchant","SolarEclipse"};
};
class InvalidCardInput : public std::runtime_error {
public:
    InvalidCardInput() : std::runtime_error("Invalid Cards File") {}
};

bool MatamStory::isNumber(const string& number) {
    for(auto& it : number){
        if(!isdigit(it)){
            return false;
        }
    }
    return true;
}
void MatamStory::add_card(const string& cardName){
    if(cardName == "Snail"){
        m_Cards.push_back(make_shared<Snail>());
    }
    else if(cardName == "Slime") {
        m_Cards.push_back(make_shared<Slime>());
    }
    else if(cardName == "Balrog"){
        m_Cards.push_back(make_shared<Balrog>());
    }
    else if( cardName == "PotionsMerchant"){
        m_Cards.push_back(make_shared<PotionsMerchant>());
    }
    else if (cardName == "SolarEclipse"){
        m_Cards.push_back(make_shared<SolarEclipse>());
    }
}
vector<shared_ptr<Event>> MatamStory::pack_input(const vector<string>& cardsVector,
                                                 vector<shared_ptr<Event>>& packVector,
                                                 int* start_index,int packSize)
{
    while (packSize > 0 && *start_index < cardsVector.size()) {
        const std::string& card = cardsVector[*start_index];
        if (card == "Snail") {
            packVector.push_back(std::make_shared<Snail>());
            packSize--;
        } else if (card == "Slime") {
            packVector.push_back(std::make_shared<Slime>());
            packSize--;
        } else if (card == "Balrog") {
            packVector.push_back(std::make_shared<Balrog>());
            packSize--;
        } else if (card == "Pack") {
            if (*start_index + 1 >= cardsVector.size() || !isNumber(cardsVector[*start_index + 1])) {
                throw InvalidCardInput();
            }
            int new_pack_size = stoi(cardsVector[++(*start_index)]);
            *start_index += 1;
            std::vector<std::shared_ptr<Event>> other_pack_vec;
            pack_input(cardsVector, other_pack_vec, start_index, new_pack_size);
            packSize--;
            packVector.push_back(std::make_shared<Pack>(other_pack_vec));
            (*start_index)--;
        } else {
            throw InvalidCardInput();
        }
        *start_index += 1;
    }
    if (packSize > 0) {
        throw InvalidCardInput();
    }
    return packVector;
}

void MatamStory::put_cards(const vector<string>& cardsVector, int* start_index) {
    for (int i = *start_index; i < cardsVector.size() ; i++) {
        IsValidCard isValidCard(cardsVector[i]);
        if (isValidCard()) {
            add_card(cardsVector[i]);
            (*start_index)++;
        }
        else if (cardsVector[i] == "Pack" && i + 1 < cardsVector.size()) {
            if(!isNumber(cardsVector[i + 1])) throw InvalidCardInput();
            int packSize = stoi(cardsVector[i + 1]);
            vector<shared_ptr<Event>> pack_vector;
            *start_index = i + 2;
            Pack pack = Pack(pack_input(cardsVector, pack_vector, start_index, packSize));
            m_Cards.push_back(make_shared<Pack>(pack));
            i = *start_index;
        }
        else {
            throw InvalidCardInput();
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    if (!eventsStream) {
        throw runtime_error("Invalid Events File");
    }

    if (!playersStream) {
        throw runtime_error("Invalid Players File");
    }

    string word;
    vector<string> tempEventVector;
    int start_index = 0;
    //WE TURN THE EVENTS STREAM FILE INTO A VECTOR SO WE CAN EASILY NAVIGATE THROUGH IT'S INFO:
    while (eventsStream >> word) {
        tempEventVector.push_back(word);
    }
    if (static_cast<int>(tempEventVector.size()) < 2) {
        throw runtime_error("Invalid Events File");
    }
    put_cards(tempEventVector, &start_index);

    string playerInfo, name, job, character;
    vector<string> tempPlayersVector;
    int numOfPlayersInFile = 0;
    while (playersStream >> playerInfo) {
        tempPlayersVector.push_back(playerInfo);
    }

    if (static_cast<int>(tempPlayersVector.size()) % NUMBER_OF_PLAYER_PARAMETERS != 0) {
        throw runtime_error("Invalid Players File");
    }
    string playerToInsert[3];

    int playerIndex = 0;
    while (playerIndex <= static_cast<int>(tempPlayersVector.size() - 2))
    {
        int i = 0;
        while (i < NUMBER_OF_PLAYER_PARAMETERS) {
            playerToInsert[i] = tempPlayersVector[i + playerIndex];
            i++;
        }
        name = playerToInsert[0];
        job = playerToInsert[1];
        character = playerToInsert[2];
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //NAME CHECK:
        if (name.size() > MAX_NAME_LENGTH || name.size() < MIN_NAME_LENGTH) {
            throw runtime_error("Invalid Players File");
        }
        for (char letter: name) {
            if (letter == ' ' || !isalpha(static_cast<unsigned char>(letter))) {
                throw runtime_error("Invalid Players File");
            }
        }
        //JOB CHECK:
        if (job != "Warrior" && job != "Magician" && job != "Archer") {
            throw runtime_error("Invalid Players File");
        }
        //CHARACTER CHECK:
        if (character != "RiskTaking" && character != "Responsible") {
            throw runtime_error("Invalid Players File");
        }
        numOfPlayersInFile++;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //INSERTING THE PLAYERS:
        if (job == "Warrior") {
            if (character == "RiskTaking") {
                m_players.push_back(make_shared<Player>(name, make_unique<Warrior>(), make_unique<RiskTaking>()));
            } else {
                m_players.push_back(make_shared<Player>(name, make_unique<Warrior>(), make_unique<Responsible>()));
            }
        } else if (job == "Archer") {
            if (character == "RiskTaking") {
                m_players.push_back(make_shared<Player>(name, make_unique<Archer>(), make_unique<RiskTaking>()));
            } else {
                m_players.push_back(make_shared<Player>(name, make_unique<Archer>(), make_unique<Responsible>()));
            }
        } else if (job == "Magician") {
            if (character == "RiskTaking") {
                m_players.push_back(make_shared<Player>(name, make_unique<Magician>(), make_unique<RiskTaking>()));
            } else {
                m_players.push_back(make_shared<Player>(name, make_unique<Magician>(), make_unique<Responsible>()));
            }
        }
        playerIndex += NUMBER_OF_PLAYER_PARAMETERS;
    }
    if(numOfPlayersInFile < MIN_NUMBER_OF_PLAYERS || numOfPlayersInFile > MAX_NUMBER_OF_PLAYERS)
    {
        throw runtime_error("Invalid Players File");
    }

    for(const shared_ptr<Player>& player : m_players)
    {
        leaderBoardSet.insert(player);
    }

    this -> m_turnIndex = 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatamStory::playTurn(Player& player) {
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    if(player.getHealthPoints() == MIN_HP || player.getLevel() == MAX_LEVEL)
    {
        return;
    }
    auto cardSize = m_Cards.size();

    shared_ptr<Event> eventToPlay = m_Cards[(m_turnIndex - 1) % cardSize];

    printTurnDetails(m_turnIndex , player , *eventToPlay);
    //SPECIAL EVENT:
    if(dynamic_pointer_cast<SpecialEvent>(eventToPlay))
    {
        shared_ptr<SpecialEvent> specialEvent = dynamic_pointer_cast<SpecialEvent>(eventToPlay);

        //SOLAR ECLIPSE:
        if(dynamic_pointer_cast<SolarEclipse>(specialEvent))
        {
            shared_ptr<SolarEclipse> solarEclipse = dynamic_pointer_cast<SolarEclipse>(specialEvent);
            if(player.getJob() == "Magician")
            {
                player.alterForce(solarEclipse -> getForceBuff());
                cout << getSolarEclipseMessage(player , solarEclipse -> getForceBuff()) << endl;
            }
            else
            {
                player.alterForce(solarEclipse -> getForceNerf());
                cout << getSolarEclipseMessage(player , solarEclipse -> getForceNerf()) << endl;
            }
        }

        //POTIONS MERCHANT:
        else
        {
            shared_ptr<PotionsMerchant> potionsMerchant = dynamic_pointer_cast<PotionsMerchant>(specialEvent);
            //RISK TAKING:
            int numOfPotions = 0;
            if(player.getCharacter() == "RiskTaking")
            {
                if(player.getHealthPoints() < MAXIMAL_HP && player.pay(potionsMerchant -> getPotionCost()))
                {
                    player.addHealth(potionsMerchant -> getPotionEffect());
                    numOfPotions++;
                }
            }
            //RESPONSIBLE:
            else
            {
                while(player.getHealthPoints() < player.getMaxHP() && player.pay(potionsMerchant -> getPotionCost()))
                {
                    player.addHealth(potionsMerchant -> getPotionEffect());
                    numOfPotions++;
                }
            }
            cout << getPotionsPurchaseMessage(player , numOfPotions) << endl;
        }
    }

    //ENCOUNTER:
    else
    {
        shared_ptr<Encounter> encounter = dynamic_pointer_cast<Encounter>(eventToPlay);

        shared_ptr<Snail> snail = dynamic_pointer_cast<Snail>(encounter);
        shared_ptr<Slime> slime = dynamic_pointer_cast<Slime>(encounter);
        shared_ptr<Balrog> balrog = dynamic_pointer_cast<Balrog>(encounter);
        shared_ptr<Pack> pack = dynamic_pointer_cast<Pack>(encounter);

        //SNAIL:
        if(snail != nullptr)
        {
            //SNAIL WIN:
            if(snail -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(snail -> getDamage());
                cout << getEncounterLostMessage(player , snail -> getDamage()) << endl;
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(snail -> getLoot());
                player.addLevel();
                cout << getEncounterWonMessage(player , snail -> getLoot()) << endl;
            }
        }
        //SLIME:
        else if(slime != nullptr)
        {
            //SLIME WIN:
            if(slime -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(slime -> getDamage());
                cout << getEncounterLostMessage(player , slime -> getDamage()) << endl;
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(slime -> getLoot());
                player.addLevel();
                cout << getEncounterWonMessage(player , slime -> getLoot()) << endl;
            }
        }
        //BALROG:
        else if(balrog != nullptr)
        {
            //BALROG WIN:
            if(balrog -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(balrog -> getDamage());
                cout << getEncounterLostMessage(player , balrog -> getDamage()) << endl;
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(balrog -> getLoot());
                player.addLevel();
                cout << getEncounterWonMessage(player , balrog -> getLoot()) << endl;
            }
            balrog -> balrogCombatPowerIncrease();
        }
        //PACK:
        else if(pack != nullptr)
        {
            //PACK WIN:
            if(pack -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(pack -> getDamage());
                cout << getEncounterLostMessage(player , pack -> getDamage()) << endl;
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(pack -> getLoot());
                player.addLevel();
                cout << getEncounterWonMessage(player , pack -> getLoot()) << endl;
            }

            vector<shared_ptr<Event>> packMembers = pack -> getPackMembers();
            for(shared_ptr<Event>& member : packMembers)
            {
                if(dynamic_pointer_cast<Balrog>(member))
                {
                    pack -> addCombatPower();
                }
            }
        }
    }
    m_turnIndex++;
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for(shared_ptr<Player>& player : m_players)
    {
        playTurn(*player);
    }

    updateLeaderboard();
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    int playerIndex = 1;
    for(const shared_ptr<Player>& player : leaderBoardSet)
    {
        printLeaderBoardEntry(playerIndex , *player);
        playerIndex ++;
    }
    /*=======================================================================================*/

    printBarrier();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MatamStory::isGameOver() const {
    int losers = 0;
    for(const shared_ptr<Player>& player : m_players)
    {
        if(player -> getLevel() == MAX_LEVEL)
        {
            return true;
        }
        if(player -> getHealthPoints() == MIN_HP)
        {
            losers++;
        }
    }
    if(losers == static_cast<int>(m_players.size()))
    {
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    int playerIndex = 1;

    for(const shared_ptr<Player>& player : m_players)
    {
        printStartPlayerEntry(playerIndex , *player);
        playerIndex++;
    }

    /*=========================================================================================*/
    printBarrier();


    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    for(const shared_ptr<Player>& player : leaderBoardSet)
    {
        if(player -> getLevel() == MAX_LEVEL)
        {
            printWinner(*player);
            break;
        }
        else if(player -> getHealthPoints() == MIN_HP)
        {
            printNoWinners();
            break;
        }
    }
    /*========================================================================*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatamStory::updateLeaderboard()
{
    vector<shared_ptr<Player>> toUpdate;

    toUpdate.reserve(leaderBoardSet.size());

for (const auto& player : leaderBoardSet)
    {
        toUpdate.push_back(player);
    }

    leaderBoardSet.clear();

    for (const auto& player : toUpdate)
    {
        leaderBoardSet.insert(player);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
