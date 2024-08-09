
#include "MatamStory.h"

#include "Utilities.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


    this->m_turnIndex = 1;
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

    shared_ptr<Event> eventToPlay = m_events.back();
    m_events.pop_back();

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
                getSolarEclipseMessage(player , solarEclipse -> getForceBuff());
            }
            else
            {
                player.alterForce(solarEclipse -> getForceNerf());
                getSolarEclipseMessage(player , solarEclipse -> getForceNerf());
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
            getPotionsPurchaseMessage(player , numOfPotions);
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
        if(!snail)
        {
            //SNAIL WIN:
            if(snail -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(snail -> getDamage());
                getEncounterLostMessage(player , snail -> getDamage());
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(snail -> getLoot());
                getEncounterWonMessage(player , snail -> getLoot());
            }
        }
        //SLIME:
        else if(!slime)
        {
            //SLIME WIN:
            if(slime -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(slime -> getDamage());
                getEncounterLostMessage(player , slime -> getDamage());
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(slime -> getLoot());
                getEncounterWonMessage(player , slime -> getLoot());
            }
        }
        //BALROG:
        else if(!balrog)
        {
            //BALROG WIN:
            if(balrog -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(balrog -> getDamage());
                getEncounterLostMessage(player , balrog -> getDamage());
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(balrog -> getLoot());
                getEncounterWonMessage(player , balrog -> getLoot());
            }
        }
        //PACK:
        else if(!pack)
        {
            //PACK WIN:
            if(pack -> getCombatPower() >= player.getCombatPower())
            {
                player.takeDamage(pack -> getDamage());
                getEncounterLostMessage(player , pack -> getDamage());
            }
            //PLAYER WIN:
            else
            {
                if(player.isWarrior())
                {
                    player.takeDamage(DAMAGE_TAKEN_ON_PLAYER_WIN);
                }
                player.takeLoot(pack -> getLoot());
                getEncounterWonMessage(player , pack -> getLoot());
            }
        }
    }
    m_events.push_back(eventToPlay);
    m_turnIndex++;
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
    int winners = 0;
    int losers = 0;
    for(const shared_ptr<Player>& player : m_players)
    {
        if(player -> getLevel() == MAX_LEVEL)
        {
            winners++;
        }
        if(player -> getHealthPoints() == MIN_HP)
        {
            losers++;
        }
    }
    if(winners || losers == m_players.size())
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
        }
    }
    printNoWinners();
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
