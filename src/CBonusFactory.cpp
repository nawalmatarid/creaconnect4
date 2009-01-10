#include "../include/CBonusFactory.h"

#include "../include/CSFMLManager.h"

#include "../include/CDoubleBonus.h"
#include "../include/CBombBonus.h"
#include "../include/CSwapBonus.h"

//**************************
//Description : Create a bonus
//Parameters : The type of bonus
//Return value : The bonus newly created
//Note : None
//**************************
IBonus * CBonusFactory::CreateBonus(int _iTypeBonus)
{
    CSFMLManager * Manager = CSFMLManager::GetInstance();

    switch(_iTypeBonus)
    {
        case DOUBLE :
        {
            return new CDoubleBonus(Manager->GetAnimation(DOUBLE), Manager->GetRenderWindow());
            break;
        }
        case BOMB :
        {
            return new CBombBonus(Manager->GetAnimation(BOMB), Manager->GetRenderWindow());
            break;
        }
        case SWAP :
        {
            return new CSwapBonus(Manager->GetAnimation(SWAP), Manager->GetRenderWindow());
            break;
        }
        default:
        {
            return new CDoubleBonus(Manager->GetAnimation(DOUBLE), Manager->GetRenderWindow());
            break;
        }
    }
}
