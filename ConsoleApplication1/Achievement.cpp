#include "Achievement.h"
#include "Giocatore.h"
#include "EntityManager.h"
bool CombactAchievementTrigger::CheckCondition()
{
    Giocatore* giocatore = context.entityManager->GetGiocatore();
    unsigned int mobskilledbyplayer = giocatore->GetMobsKilled();
    if (numbermobs <= mobskilledbyplayer)
        return true;

    return false;
}
