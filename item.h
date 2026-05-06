#pragma once
#include <iostream>
#include <string>

class Player; // 전방 선언

class Item {
public:
    Item(std::string name, int grade) : name(name), grade(grade) { 
        std::cout << "[생성] " << name << " (등급: " << grade << ")" << std::endl;
    }

    ~Item() {
        std::cout << "[소멸] " << name << std::endl;
    }

    std::string GetName() const { return name; }
    
    int GetGrade() const { return grade; }

private:
    std::string name;
    int grade;
    std::weak_ptr<Player> owner; // 주인을 가리키는 약한 참조 (순환 참조 방지)
};