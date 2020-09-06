#pragma once


#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QSize>
#include <QFont>

#include <QTabWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QPainter>

#include <unordered_map>
#include <string>

#include <list>
#include <vector>
#include <random>
#include <memory>


class Kill : public QObject {
	std::unordered_map<std::string, QPixmap> Kill_pics;
	std::unordered_map<std::string, QGraphicsPixmapItem*> Kill_items;

	QGraphicsScene* _scene;

	std::unordered_map<std::string, QPixmap> attack_pics;
	QList<QGraphicsItem*> attack_items;

	int _attackCount;
	int _stage; //0 1 2 3

	std::unique_ptr<QTimer> _attackTimer;

	Q_OBJECT

signals:

	void attackComplete();

private slots:

	void updateAttack1();
	void updateAttack2();
	void updateAttack3();
	void updateHeal();
	void updateSpecialAttack();

public:

	Kill(QGraphicsScene* scene);

	Kill(const Kill&) = delete;

	Kill operator=(const Kill&) = delete;


	void setNormal(std::string poseName);

	//extend up down
	void setPose(std::string poseName);

	void Attack1();
	void Attack2();
	void Attack3();
	void Heal();
	void SpecialAttack();

};




class monster : public QObject {
	std::unordered_map<std::string, QPixmap> monster_pics;
	std::unordered_map<std::string, QGraphicsPixmapItem*> monster_items;

	QGraphicsScene* _scene;

	std::unordered_map<std::string, QPixmap> attack_pics;
	QList<QGraphicsPixmapItem*> attack_items;

	std::unique_ptr<QTimer> _attackTimer;

	int _attackCount;


	Q_OBJECT

signals:

	void attackComplete();

private slots:

	void updateAttack1();
	void updateAttack2();
	void updateAttack3();

public:



	monster(QGraphicsScene* scene);

	monster(const monster&) = delete;

	monster operator=(const monster&) = delete;

	void setNormal();

	//up
	void setUp();

	void Attacks();

	void Attack1();
	void Attack2();
	void Attack3();

};

//отрисовка карточек во время атак должна быть поверх фона, поэтому для них отдельный метод??
class background {
	QSize _backgroundSize = QSize(1150, 690);
	QSize _maxCloudSize = QSize(360, 120);
	std::unordered_map<std::string, QPixmap> _objectsPics;
	std::unordered_map<std::string, QGraphicsPixmapItem*> _backgroundObjects;

	const int _cloudSpeed = 50;
	const int _cloudCount = 5;

	std::vector<QPixmap> _clouds;
	std::list<QGraphicsPixmapItem*> _sceneClouds;
	std::mt19937 _random;

	QGraphicsScene* _scene;

public:

	background(QGraphicsScene* scene);


	void updateClouds(int timerInterval);

};



class buttons {
	std::unique_ptr <QTabWidget> _attacks;
	QGraphicsScene* _scene;
	std::unordered_map<std::string, QGraphicsRectItem*> _stats;
	std::unordered_map<std::string, QGraphicsTextItem*> _names;

	int _KillHP;
	int _KillMana;
	int _monsterHP;
	int _KillSP;

public:
	std::vector<QPushButton*> _buttons;
	//0:a1, 1:a2, 2:a3, 3:h, 4:s
public:
	buttons(QGraphicsScene* scene);

	void updateKillHP(int);
	void updateKillMana(int);
	void updateMonsterHP(int);
	void updateSP();
};