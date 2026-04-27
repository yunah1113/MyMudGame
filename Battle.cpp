#include "Battle.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster), combatMessage("[시스템] " + monster.GetName() + "와(과) 전투를 시작합니다!") {}

bool Battle::Run() {
    int action;
    while (monster.isAlive() && player.isAlive()) {
        int mHp = monster.GetHp(), pHp = player.GetHp();
        int mBarCnt = (mHp * 20) / monster.GetMaxHp();
        int pBarCnt = (pHp * 20) / player.GetMaxHp();

        string mBar = string(mBarCnt, '=') + string(20 - mBarCnt, '-');
        string pBar = string(pBarCnt, '=') + string(20 - pBarCnt, '-');

        cout << "==================================================\n";
        cout << " [ " << left << setw(14) << monster.GetName() << " ] [" << mBar << "] " << mHp << " HP\n";
        cout << " [ " << left << setw(14) << "당신" << " ] [" << pBar << "] " << pHp << " HP\n";
        cout << "==================================================\n";
        cout << " " << combatMessage << "\n";
        cout << "--------------------------------------------------\n";
        cout << " 1. 일반 공격 \n 2. 강력한 일격 (배쉬) \n 3. 상태 확인\n";
        cout << "--------------------------------------------------\n";
        cout << " >> 행동 선택 : ";
        cin >> action;

        if (action == 1) {
            int dmg = player.Attack();
            monster.TakeDamage(dmg);
            combatMessage = "=> " + monster.GetName() + "에게 검을 휘둘렀습니다! (-" + to_string(dmg) + " HP)";
        } else if (action == 2) {
            int dmg = player.CriticalAttack();
            monster.TakeDamage(dmg);
            combatMessage = "=> [강타!] " + monster.GetName() + "에게 치명상을 입혔습니다! (-" + to_string(dmg) + " HP)";
        } else if (action == 3) {
            player.PreviewCritical();
            system("pause");
            system("cls");
            continue;
        } else {
            cin.clear(); cin.ignore(100, '\n');
            combatMessage = "=> 당신은 머뭇거렸고, 공격 기회를 놓쳤습니다!";
        }

        if (monster.isAlive() && action != 3) {
            int mDmg = monster.Attack();
            player.TakeDamage(mDmg);
            combatMessage += "\n=> " + monster.GetName() + "의 반격! (-" + to_string(mDmg) + " HP)";
        }
        system("cls");
    }
    return player.isAlive();
}