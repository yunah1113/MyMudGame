#include <iostream>
#include <string>
#include <cstdlib> 
#include <iomanip>
#include <vector>
#include <ctime>

#include "Battle.h"
#include "Monster.h"
#include "Player.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    system("cls");

    string uName, cClass;
    int cChoice;
    char hcIn;
    bool isHC = false;

    cout << "================================================\n";
    cout << "       [ 텍스트 에디션 : 심연의 광산 ]          \n";
    cout << "================================================\n";
    cout << " >> 이름을 입력하세요 : ";
    cin >> uName;

    system("cls");
    cout << "------------------------------------------------\n";
    cout << "           시작 도구를 선택하세요               \n";
    cout << "------------------------------------------------\n";
    cout << "  1. 전사  2. 마법사  3. 야만인  4. 성기사      \n";
    cout << "------------------------------------------------\n";
    cout << " >> 선택: ";
    cin >> cChoice;

    if (cChoice == 1) cClass = "전사";
    else if (cChoice == 2) cClass = "마법사";
    else if (cChoice == 3) cClass = "야만인";
    else if (cChoice == 4) cClass = "성기사";
    else cClass = "농부";

    cout << "\n >> 하드코어 모드? (1:예 / 0:아니오) : ";
    cin >> hcIn;
    isHC = (hcIn == '1');

    system("cls");
    Player player(uName, cClass, isHC);

    vector<Monster> monsters;
    monsters.push_back(Monster("초록 슬라임", 40, 10, 15, 10, 50));
    monsters.push_back(Monster("먼지 요정", 50, 15, 20, 10, 80));
    monsters.push_back(Monster("바위 게", 70, 20, 30, 10, 120));
    monsters.push_back(Monster("그림자 브루트", 150, 40, 50, 20, 300));

    for (size_t i = 0; i < monsters.size(); i++) {
        if (!player.isAlive()) break;
        system("cls");
        cout << "------------------------------------------------\n";
        cout << "  [!] " << monsters[i].GetName() << " 등장!\n";
        cout << "------------------------------------------------\n\n";
        system("pause");

        Battle battle(player, monsters[i]);
        if (!battle.Run()) {
            cout << "\n당신은 쓰러졌습니다...\n";
            break;
        } else {
            cout << "\n승리했습니다!\n";
            player.GainExp(monsters[i].GetExpReward());
            player.Loot(2);
            system("pause");
        }
    }

    if (player.isAlive()) cout << "\n광산을 정복했습니다!\n";
    system("pause");
    return 0;
}