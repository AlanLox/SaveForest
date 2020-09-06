#pragma once

#include <vector>

class Battle {
	int KillHP;
	int monsterHP;

	int KillMana;
	int specialAttackCount;

	std::vector<bool> availableAttacks; //2, 3, heal, special

public:

	const static int SPECIAL_ATTACK_COUNT = 3;

	const static int KILL_HP = 3000;
	const static int MONSTER_HP = 30000;
	const static int KILL_MANA = 500;

	const static int KILL_MIN_ATTACK_1 = 1000;
	const static int KILL_MIN_ATTACK_2 = 2000;
	const static int KILL_MIN_ATTACK_3 = 2500;
	const static int KILL_MIN_HEAL = 1200;
	const static int KILL_MIN_SPESIAL_ATTACK = 5000;

	const static int KILL_MANA_ATTACK_2 = 30;
	const static int KILL_MANA_ATTACK_3 = 40;
	const static int KILL_MANA_HEAL = 40;

	const static int MONSTER_MIN_ATTACK_1 = 500;
	const static int MONSTER_MIN_ATTACK_2 = 600;
	const static int MONSTER_MIN_ATTACK_3 = 700;

	const static int KILL_ATTACK_1_RANGE = 200;
	const static int KILL_ATTACK_2_RANGE = 300;
	const static int KILL_ATTACK_3_RANGE = 300;

	const static int KILL_SPECIAL_ATTACK_RANGE = 1000;
	const static int KILL_HEAL_RANGE = 300;

	const static int MONSTER_ATTACK_RANGE = 100;


public:
	Battle(int KillHP = KILL_HP, int monsterHP = MONSTER_HP, int KillMana = KILL_MANA, int specialAttackCount = SPECIAL_ATTACK_COUNT);

	bool win();
	bool gameOver();

	int getKillHP() const;
	int getKillMana() const;
	int getMonsterHP() const;

	bool can_Attack2();
	bool can_Attack3();
	bool can_Heal();
	bool can_SpecialAttack();


	//Kill
	int killAttack1(); //без магии
	int killAttack2(); //магия
	int killAttack3(); //магия

	int killHeal(); //магия
	int killSpecial(); //ограниченное кол-во раз? от урона от противника?

	//monster
	int monsterAttack1();
	int monsterAttack2();
	int monsterAttack3();

};