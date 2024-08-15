#include "MatamStory.h"

#include "Utilities.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isValidPackMembersAmount(const string& word)
{
    for(const char letter : word)
    {
        if(!isdigit(letter))
        {
            return false;
        }
    }
    if(stoi(word) < MIN_PACK_MEMBER_NUMBER)
    {
        return false;
    }
    return true;
}

void MatamStory :: addCard(const string& cardName)
{
    if(cardName == "Snail")
    {
        m_events.push_back(make_shared<Snail>());
    }
    else if(cardName == "Slime")
    {
        m_events.push_back(make_shared<Slime>());
    }
    else if(cardName == "Balrog")
    {
        m_events.push_back(make_shared<Balrog>());
    }
    else if( cardName == "PotionsMerchant")
    {
        m_events.push_back(make_shared<PotionsMerchant>());
    }
    else if (cardName == "SolarEclipse")
    {
        m_events.push_back(make_shared<SolarEclipse>());
    }
}

//vector<shared_ptr<Encounter>> packInput(const vector<string>& cardsVector,
//                                                 vector<shared_ptr<Encounter>>& packVector,
//                                                 int* start_index,int packSize)
//{
//    while (packSize > 0 && *start_index < cardsVector.size()) {
//        const std::string& card = cardsVector[*start_index];
//        if (card == "Snail") {
//            packVector.push_back(std::make_shared<Snail>());
//        } else if (card == "Slime") {
//            packVector.push_back(std::make_shared<Slime>());
//        } else if (card == "Barlog") {
//            packVector.push_back(std::make_shared<Balrog>());
//        } else if (card == "Pack") {
//            if (*start_index + 1 >= cardsVector.size() || !isValidPackMembersAmount(cardsVector[*start_index + 1])) {
//                throw runtime_error("Invalid Events File");
//            }
//            int new_pack_size = stoi(cardsVector[++(*start_index)]);
//            *start_index += 1;
//            std::vector<std::shared_ptr<Encounter>> other_pack_vec;
//            packInput(cardsVector, other_pack_vec, start_index, new_pack_size);
//            shared_ptr<Pack> otherPack;
//            otherPack ->insertNewMembers(other_pack_vec);
//            packVector.push_back(std::make_shared<Pack>());
//            (*start_index)--;
//        } else {
//            throw runtime_error("Invalid Events File");
//        }
//        packSize -= 1;
//        *start_index += 1;
//
//    }
//    if (packSize > 0) {
//        throw runtime_error("Invalid Events File");
//    }
//    return packVector;
//}

vector<shared_ptr<Encounter>> packInput(const vector<string>& eventsVector , vector<shared_ptr<Encounter>>& packVector,
                                        int* startIndex, int packSize)
{
    while (packSize > 0 && *startIndex < static_cast<int>(eventsVector.size()))
    {
        const string& event = eventsVector[*startIndex];

        if (event == "Snail")
        {
            packVector.push_back(std::make_shared<Snail>());
        }
        else if (event == "Slime")
        {
            packVector.push_back(std::make_shared<Slime>());
        }
        else if (event == "Balrog")
        {
            packVector.push_back(std::make_shared<Balrog>());
        }
        else if (event == "Pack")
        {
            if (*startIndex + 1 >= static_cast<int> (eventsVector.size()) || !isValidPackMembersAmount(eventsVector[*startIndex + 1]))
            {
                throw runtime_error("Invalid Events File");
            }

            int newPackSize = stoi(eventsVector[++(*startIndex)]);
            *startIndex += 1;

            std::vector<std::shared_ptr<Encounter>> otherPackVec;
            packInput(eventsVector , otherPackVec, startIndex, newPackSize);

            shared_ptr<Pack> otherPack = make_shared<Pack>();
            otherPack -> insertNewMembers(otherPackVec);
            packVector.push_back(otherPack);

        }
        else
        {
            throw runtime_error("Invalid Events File");
        }

        packSize -= 1;
        *startIndex += 1;
    }

    if (packSize > 0)
    {
        throw runtime_error("Invalid Events File");
    }

    return packVector;
}


//void MatamStory :: putCards(const vector<string>& cardsVector, int* start_index) {
//    for(auto& it : cardsVector){
//        cout << it << endl;
//    }
//    for (int i = *start_index; i < cardsVector.size() ; i++)
//    {
//        if (cardsVector[i] == "Pack" && i + 1 < cardsVector.size())
//        {
//            if (!isValidPackMembersAmount(cardsVector[i + 1]))
//            {
//                throw runtime_error("Invalid Events File");
//            }
//            else
//            {
//                int packSize = stoi(cardsVector[i + 1]);
//                vector<shared_ptr<Encounter>> pack_vector;
//                *start_index = i + 2;
//                shared_ptr<Pack> pack = std::make_shared<Pack>();
//                pack->insertNewMembers(packInput(cardsVector, pack_vector, start_index, packSize));
//                m_events.push_back(pack);
//                putCards(cardsVector, start_index);
//                i = *start_index;
//            }
//        }
//        else
//        {
//            addCard(cardsVector[i]);
//        }
//    }
//}

void MatamStory :: putCards(const vector<string>& eventsVector, int* startIndex)
{
    for (int i = *startIndex; i < static_cast<int> (eventsVector.size()) ; i++)
    {
        if (eventsVector[i] == "Pack" && i + 1 < static_cast<int>(eventsVector.size()))
        {
            if (!isValidPackMembersAmount(eventsVector[i + 1]))
            {
                throw runtime_error("Invalid Events File");
            }
            else
            {
                int packSize = stoi(eventsVector[i + 1]);
                vector<shared_ptr<Encounter>> packVector;
                *startIndex = i + 2;

                shared_ptr<Pack> pack = std::make_shared<Pack>();
                pack -> insertNewMembers(packInput(eventsVector, packVector, startIndex, packSize));
                m_events.push_back(pack);

                i = *startIndex - 1;
            }
        }
        else
        {
            addCard(eventsVector[i]);
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
        if (word != "Snail" && word != "Slime" && word != "Balrog" && word != "Pack" && !isValidPackMembersAmount(word)
            && word != "PotionsMerchant" && word != "SolarEclipse") {
            throw runtime_error("Invalid Events File");
        }
        tempEventVector.push_back(word);
    }
    if (static_cast<int>(tempEventVector.size()) < 2) {
        throw runtime_error("Invalid Events File");
    }
    putCards(tempEventVector, &start_index);


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
        m_leaderboard.insert(player);
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


    shared_ptr<Event> eventToPlay = m_events.front();
    m_events.pop_front();

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

            vector<shared_ptr<Encounter>> packMembers = pack -> getPackMembers();
            for(shared_ptr<Encounter> member : packMembers)
            {
                if(dynamic_pointer_cast<Balrog>(member))
                {
                    pack -> addCombatPower();
                }
            }
        }
    }
    m_events.push_back(eventToPlay);
    m_turnIndex++;
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for(shared_ptr<Player> player : m_players)
    {
        playTurn(*player);
    }

    updateLeaderboard();
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    int playerIndex = 1;
    for(const shared_ptr<Player>& player : m_leaderboard)
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
    for(const shared_ptr<Player>& player : m_leaderboard)
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

    toUpdate.reserve(m_leaderboard.size());

for (const auto& player : m_leaderboard)
    {
        toUpdate.push_back(player);
    }

    m_leaderboard.clear();

    for (const auto& player : toUpdate)
    {
        m_leaderboard.insert(player);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
