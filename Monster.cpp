#include "Monster.h"
#include <iostream>

Monster::Monster(const string& name, int str, int dex, int vit, int eng, int expReward, int lv) 
: Character(str, dex, vit, eng, lv), name(name), expReward(expReward)
{
}