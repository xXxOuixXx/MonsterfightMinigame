#include <iostream>
#include <string>

class Monster {
public:
    Monster(std::string name, std::string race, int hp, int ad, int dp, int s)
        : name(name), race(race), hp(hp), ad(ad), dp(dp), s(s) {}

    int attack(Monster& other_monster) {
        int damage = ad - other_monster.dp;
        damage = (damage > 0) ? damage : 0;
        other_monster.hp -= damage;
        return damage;
    }

    void parry() {
        dp += 10;
    }

    void heal() {
        hp += 5;
    }

    bool isAlive() {
        return hp > 0;
    }

    std::string getName() {
        return name;
    }

    std::string getRace() {
        return race;
    }

    int getHP() {
        return hp;
    }

    int getAD() {
        return ad;
    }

    int getDP() {
        return dp;
    }

    int getSpeed() {
        return s;
    }

private:
    std::string name;
    std::string race;
    int hp;
    int ad;
    int dp;
    int s;
};

Monster selectMonsterProfile() {
    std::cout << "Select a monster profile to fight:" << std::endl;
    std::cout << "1. Monster1 (orc)" << std::endl;
    std::cout << "2. Monster2 (troll)" << std::endl;
    std::cout << "3. Monster3 (goblin)" << std::endl;

    int choice;
    while (true) {
        std::cout << "Enter the number of the first monster profile: ";
        if (std::cin >> choice && choice >= 1 && choice <= 3) {
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
        }
    }

    if (choice == 1) {
        return Monster("Monster1", "orc", 80, 20, 10, 5);
    }
    else if (choice == 2) {
        return Monster("Monster2", "troll", 50, 18, 15, 4);
    }
    else {
        return Monster("Monster3", "goblin", 30, 25, 5, 6);
    }
}

int main() {
    Monster monster1 = selectMonsterProfile();
    Monster monster2 = selectMonsterProfile();

    if (monster1.getRace() == monster2.getRace()) {
        std::cout << "Monsters of the same race cannot fight." << std::endl;
        return 0;
    }

    int roundCount = 0;
    while (monster1.isAlive() && monster2.isAlive()) {
        roundCount++;

        if (monster1.getSpeed() > monster2.getSpeed()) {
            int damage = monster1.attack(monster2);
            std::cout << monster1.getName() << " attacks " << monster2.getName() << " for " << damage << " damage." << std::endl;
            if (!monster2.isAlive()) {
                break;
            }

            monster2.heal();
            std::cout << monster2.getName() << " heals and gains 5 HP." << std::endl;

            damage = monster2.attack(monster1);
            std::cout << monster2.getName() << " attacks " << monster1.getName() << " for " << damage << " damage." << std::endl;
            if (!monster1.isAlive()) {
                break;
            }

            monster1.heal();
            std::cout << monster1.getName() << " heals and gains 5 HP." << std::endl;
        }
        else {
            int damage = monster2.attack(monster1);
            std::cout << monster2.getName() << " attacks " << monster1.getName() << " for " << damage << " damage." << std::endl;
            if (!monster1.isAlive()) {
                break;
            }

            monster1.heal();
            std::cout << monster1.getName() << " heals and gains 5 HP." << std::endl;

            damage = monster1.attack(monster2);
            std::cout << monster1.getName() << " attacks " << monster2.getName() << " for " << damage << " damage." << std::endl;
            if (!monster2.isAlive()) {
                break;
            }

            monster2.heal();
            std::cout << monster2.getName() << " heals and gains 5 HP." << std::endl;
        }
    }

    if (monster1.isAlive()) {
        std::cout << monster1.getName() << " (Race: " << monster1.getRace() << ") wins in " << roundCount << " rounds!" << std::endl;
    }
    else {
        std::cout << monster2.getName() << " (Race: " << monster2.getRace() << ") wins in " << roundCount << " rounds!" << std::endl;
    }

    return 0;
}