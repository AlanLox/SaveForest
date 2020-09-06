#include <random>
#include "GameLogic.h"

Battle::Battle(int KillHP, int monsterHP, int KillMana, int specialAttackCount): 
	KillHP(KillHP), monsterHP(monsterHP), KillMana(KillMana), specialAttackCount(specialAttackCount) {
	for (int i = 0; i < 4; ++i)
		availableAttacks.push_back(true);
}

bool Battle::win() {
	return (monsterHP <= 0);
}

bool Battle::gameOver() {
	return (KillHP <= 0);
}


bool Battle::can_Attack2() {
	return (availableAttacks[0] == true);
}
bool Battle::can_Attack3() {
	return (availableAttacks[1] == true);
}
bool Battle::can_Heal() {
	return (availableAttacks[2] == true);
}
bool Battle::can_SpecialAttack() {
	return (availableAttacks[3] == true);
}


int Battle::getKillHP() const {
	return KillHP;
}
int Battle::getKillMana() const {
	return KillMana;
}
int Battle::getMonsterHP() const {
	return monsterHP;
}

//Kill
//без магии
int Battle::killAttack1() {
	int attack = KILL_MIN_ATTACK_1 + rand() % KILL_ATTACK_1_RANGE;
	monsterHP -= attack;
	return attack;
}

//магия
int Battle::killAttack2() {
	KillMana -= KILL_MANA_ATTACK_2;
	int attack = KILL_MIN_ATTACK_2 + rand() % KILL_ATTACK_2_RANGE;
	monsterHP -= attack;
	if (KillMana < KILL_MANA_ATTACK_2) availableAttacks[0] = false;
	return attack;
}

//магия
int Battle::killAttack3() {
	KillMana -= KILL_MANA_ATTACK_3;
	int attack = KILL_MIN_ATTACK_3 + rand() % KILL_ATTACK_3_RANGE;
	monsterHP -= attack;
	if (KillMana < KILL_MANA_ATTACK_3) availableAttacks[1] = false;
	return attack;
}

//магия
int Battle::killHeal() {
	KillMana -= KILL_MANA_HEAL;
	int HP = KILL_MIN_HEAL + rand() % KILL_HEAL_RANGE;
	if (KillHP + HP > KILL_HP)
		HP = KILL_HP - KillHP;
	KillHP += HP;
	if (KillHP > KILL_HP) KillHP = KILL_HP;
	if (KillMana < KILL_MANA_HEAL) availableAttacks[2] = false;
	return HP;
}

//ограниченное кол-во раз? от урона от противника?
int Battle::killSpecial() {
	specialAttackCount -= 1;
	int attack = KILL_MIN_SPESIAL_ATTACK + rand() % KILL_SPECIAL_ATTACK_RANGE;
	monsterHP -= attack;
	if (specialAttackCount == 0) availableAttacks[3] = false;
	return attack;
}

//monster
int Battle::monsterAttack1() {
	int attack = MONSTER_MIN_ATTACK_1 + rand() % MONSTER_ATTACK_RANGE;
	KillHP -= attack;
	return attack;
}

int Battle::monsterAttack2() {
	int attack = MONSTER_MIN_ATTACK_2 + rand() % MONSTER_ATTACK_RANGE;
	KillHP -= attack;
	return attack;
}

int Battle::monsterAttack3() {
	int attack = MONSTER_MIN_ATTACK_3 + rand() % MONSTER_ATTACK_RANGE;
	KillHP -= attack;
	return attack;
}
