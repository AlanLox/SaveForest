#include "Characters.h"


#include <QDir>
#include <QFrame>
#include <QString>


using namespace std;


//
//
//    KILL
//
//


Kill::Kill(QGraphicsScene* scene) : _scene(scene) {
	_stage = 0;
	_attackCount = 0;

	Kill_pics.insert(pair<string, QPixmap>("normal", QPixmap("resources/Kill/normal.png")));
	Kill_pics.insert(pair<string, QPixmap>("up", QPixmap("resources/Kill/up.png")));
	Kill_pics.insert(pair<string, QPixmap>("down", QPixmap("resources/Kill/down.png")));
	Kill_pics.insert(pair<string, QPixmap>("extend", QPixmap("resources/Kill/extend.png")));

	auto normal = new QGraphicsPixmapItem(Kill_pics.find("normal")->second);
	normal->setZValue(-0.4);
	Kill_items.insert(pair<string, QGraphicsPixmapItem*>("normal", normal));
	Kill_items.insert(pair<string, QGraphicsPixmapItem*>("up", new QGraphicsPixmapItem(Kill_pics.find("up")->second)));
	Kill_items.insert(pair<string, QGraphicsPixmapItem*>("down", new QGraphicsPixmapItem(Kill_pics.find("down")->second)));
	Kill_items.insert(pair<string, QGraphicsPixmapItem*>("extend", new QGraphicsPixmapItem(Kill_pics.find("extend")->second)));

	//создание атак

	attack_pics.insert(pair<string, QPixmap>("k1", QPixmap("resources/attacks/k1.png")));
	attack_pics.insert(pair<string, QPixmap>("k2", QPixmap("resources/attacks/k2.png")));
	attack_pics.insert(pair<string, QPixmap>("k3", QPixmap("resources/attacks/k3.png")));
	attack_pics.insert(pair<string, QPixmap>("kh", QPixmap("resources/attacks/kh.png")));
	attack_pics.insert(pair<string, QPixmap>("ksm1", QPixmap("resources/attacks/ksm1.png")));
	attack_pics.insert(pair<string, QPixmap>("ksm2", QPixmap("resources/attacks/ksm2.png")));

	_scene->addItem(Kill_items.find("normal")->second);


	_attackTimer = unique_ptr<QTimer>(new QTimer(this));
}


void Kill::setNormal(string poseName) {
	_scene->removeItem(Kill_items.find(poseName)->second);
	Kill_items.erase(poseName);

	auto normal = new QGraphicsPixmapItem(Kill_pics.find("normal")->second);
	normal->setZValue(-0.4);
	Kill_items.insert(pair<string, QGraphicsPixmapItem*>("normal", normal));
	_scene->addItem(Kill_items.find("normal")->second);
}


//extend up down
void Kill::setPose(string poseName) {
	_scene->removeItem(Kill_items.find("normal")->second);
	Kill_items.erase("normal");
	auto pose = new QGraphicsPixmapItem(Kill_pics.find(poseName)->second);
	pose->setZValue(-0.4);
	Kill_items.insert(pair<string, QGraphicsPixmapItem*>(poseName, pose));
	_scene->addItem(Kill_items.find(poseName)->second);
}


void Kill::Attack1() {
	setPose("extend");

	_attackCount = 0;
	//update attack1
	connect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateAttack1);
	_attackTimer->start(1);
}


void Kill::Attack2() {
	setPose("extend");

	_attackCount = 0;
	//update attack2

	connect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateAttack2);
	_attackTimer->start(1);
}


void Kill::Attack3() {
	setPose("up");

	_attackCount = 0;
	//update attack3

	connect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateAttack3);
	_attackTimer->start(1);
}

void Kill::Heal() {
	setPose("up");

	_attackCount = 0;
	//update 

	connect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateHeal);
	_attackTimer->start(1);
}

void Kill::SpecialAttack() {
	setPose("up");

	_attackCount = 0;

	_stage = 1;


	auto dark = new QGraphicsRectItem;
	dark->setBrush(QBrush("#000022"));
	dark->setRect(0, 0, 1150, 690);
	dark->setOpacity(0.0);
	attack_items.push_front(dark);
	_scene->addItem(attack_items[0]);

	//update sp attack

	connect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateSpecialAttack);
	_attackTimer->start(1);
}









//в этой и других первый раз добавляется во внешней(?) функции, к которой коннектится и в которой меняется флажок
void Kill::updateAttack1() {
	++_attackCount;

	if (attack_items.size() < 5 && _attackCount % 30 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("k1")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setX(attack_items[i]->x() + 5);
	}

	if (attack_items.size() == 5 && attack_items[0]->x() >= 1000) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal("extend");
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateAttack1);
		_attackTimer->stop();
		emit attackComplete();
	}
}



void Kill::updateAttack2() {
	++_attackCount;

	if (attack_items.size() < 3 && _attackCount % 40 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("k2")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setX(attack_items[i]->x() + 5);
	}

	if (attack_items.size() == 3 && attack_items[0]->x() >= 1000) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal("extend");
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateAttack2);
		_attackTimer->stop();
		emit attackComplete();
	}
}


void Kill::updateAttack3() {
	++_attackCount;

	if (attack_items.size() < 5 && _attackCount % 30 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("k3")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setY(attack_items[i]->y() - 5);
	}

	if (attack_items.size() == 5 && attack_items[0]->y() <= -700) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal("up");
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateAttack3);
		_attackTimer->stop();
		emit attackComplete();
	}
}



void Kill::updateHeal() {
	++_attackCount;

	if (attack_items.size() < 3 && _attackCount % 30 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("kh")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setY(attack_items[i]->y() - 5);
	}

	if (attack_items.size() == 3 && attack_items[0]->y() <= -700) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal("up");
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateHeal);
		_attackTimer->stop();
		emit attackComplete();
	}
}


void Kill::updateSpecialAttack() {
	if (_stage == 1) {
		attack_items[0]->setOpacity(attack_items[0]->opacity() + 0.002);
		if (attack_items[0]->opacity() >= 0.5) _stage = 2;
	}
	if (_stage == 2) {

		int c1 = 50, c2 = 70, c3 = 90;

		++_attackCount;
		if (attack_items.size() == 1 && _attackCount <= c1) {
			attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("ksm1")->second));
			_scene->addItem(attack_items[0]);
		}
		if (_attackCount >= c1 && _attackCount <= c2 && attack_items.size() == 2) {
			_scene->removeItem(attack_items[0]);
			attack_items.pop_front();
		}
		if (attack_items.size() == 1 && _attackCount >= c1 && _attackCount <= c2) {
			attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("ksm2")->second));
			_scene->addItem(attack_items[0]);
		}
		if (_attackCount >= c2 && _attackCount <= c3 && attack_items.size() == 2) {
			_scene->removeItem(attack_items[0]);
			attack_items.pop_front();
		}
		if (attack_items.size() == 1 && _attackCount >= c2 && _attackCount <= c3) {
			attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("ksm1")->second));
			_scene->addItem(attack_items[0]);
		}
		if (_attackCount >= c3 && attack_items.size() == 2) {
			_scene->removeItem(attack_items[0]);
			attack_items.pop_front();
			_stage = 3;
		}
	}
	if (_stage == 3) {
		attack_items[0]->setOpacity(attack_items[0]->opacity() - 0.002);
		if (attack_items[0]->opacity() <= 0.002) {
			_scene->removeItem(attack_items[0]);
			attack_items.clear();
			setNormal("up");
			disconnect(_attackTimer.get(), &QTimer::timeout, this, &Kill::updateSpecialAttack);
			_attackTimer->stop();
			emit attackComplete();
		}
	}
}





//
//
//      MONSTER
//
//


monster::monster(QGraphicsScene* scene) : _scene(scene) {
	_attackCount = 0;

	monster_pics.insert(pair<string, QPixmap>("normal", QPixmap("resources/monster/normal.png")));
	monster_pics.insert(pair<string, QPixmap>("up", QPixmap("resources/monster/up.png")));

	auto normal = new QGraphicsPixmapItem(monster_pics.find("normal")->second);
	normal->setZValue(-0.4);
	auto up = new QGraphicsPixmapItem(monster_pics.find("up")->second);
	up->setZValue(-0.4);
	monster_items.insert(pair<string, QGraphicsPixmapItem*>("normal", normal));
	monster_items.insert(pair<string, QGraphicsPixmapItem*>("up", up));


	//создание атак
	attack_pics.insert(pair<string, QPixmap>("m1", QPixmap("resources/attacks/m1.png")));
	attack_pics.insert(pair<string, QPixmap>("m2", QPixmap("resources/attacks/m2.png")));
	attack_pics.insert(pair<string, QPixmap>("m3", QPixmap("resources/attacks/m3.png")));



	_scene->addItem(monster_items.find("normal")->second);


	_attackTimer = unique_ptr<QTimer>(new QTimer(this));
}



void monster::setNormal() {
	_scene->removeItem(monster_items.find("up")->second);
	monster_items.erase("up");
	auto pose = new QGraphicsPixmapItem(monster_pics.find("normal")->second);
	pose->setZValue(-0.4);
	monster_items.insert(pair<string, QGraphicsPixmapItem*>("normal", pose));
	_scene->addItem(monster_items.find("normal")->second);

}


//up
void monster::setUp() {
	_scene->removeItem(monster_items.find("normal")->second);
	monster_items.erase("normal");
	auto pose = new QGraphicsPixmapItem(monster_pics.find("up")->second);
	pose->setZValue(-0.4);
	monster_items.insert(pair<string, QGraphicsPixmapItem*>("up", pose));
	_scene->addItem(monster_items.find("up")->second);
}



//временно
void monster::Attack1() {
	setUp();

	_attackCount = 0;
	//update attack1

	connect(_attackTimer.get(), &QTimer::timeout, this, &monster::updateAttack1);
	_attackTimer->start(1);
}

void monster::Attack2() {
	setUp();

	_attackCount = 0;
	//update attack2

	connect(_attackTimer.get(), &QTimer::timeout, this, &monster::updateAttack2);
	_attackTimer->start(1);
}

void monster::Attack3() {
	setUp();

	_attackCount = 0;
	//update attack3

	connect(_attackTimer.get(), &QTimer::timeout, this, &monster::updateAttack3);
	_attackTimer->start(1);
}

//меняет координаты
void monster::updateAttack1() {
	++_attackCount;

	if (attack_items.size() < 3 && _attackCount % 30 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("m1")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setX(attack_items[i]->x() - 5);
	}

	if (attack_items.size() == 3 && attack_items[0]->x() <= -1000) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal();
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &monster::updateAttack1);
		_attackTimer->stop();
		emit attackComplete();
	}
}
void monster::updateAttack2() {
	++_attackCount;

	if (attack_items.size() < 3 && _attackCount % 35 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("m2")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setX(attack_items[i]->x() - 5);
	}

	if (attack_items.size() == 3 && attack_items[0]->x() <= -1000) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal();
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &monster::updateAttack2);
		_attackTimer->stop();
		emit attackComplete();
	}
}
void monster::updateAttack3() {
	++_attackCount;

	if (attack_items.size() < 3 && _attackCount % 40 == 0) {
		attack_items.push_front(new QGraphicsPixmapItem(attack_pics.find("m3")->second));
		_scene->addItem(attack_items[0]);
	}

	for (int i = 0; i < attack_items.size(); ++i) {
		attack_items[i]->setX(attack_items[i]->x() - 5);
	}

	if (attack_items.size() == 3 && attack_items[0]->x() <= -1000) {
		for (int i = 0; i < attack_items.size(); ++i) {
			_scene->removeItem(attack_items[i]);
		}
		attack_items.clear();
		setNormal();
		disconnect(_attackTimer.get(), &QTimer::timeout, this, &monster::updateAttack3);
		_attackTimer->stop();
		emit attackComplete();
	}
}



//
//
//    BACKGROUND
//
//



background::background(QGraphicsScene* scene) : _scene(scene) {

	// Загрузка _clouds
	QDir dir("resources/clouds"); //!!!
	for (const auto& File : dir.entryInfoList(QDir::Files)) {
		QPixmap cloud(File.absoluteFilePath());
		if (!cloud.isNull()) {
			_clouds.push_back(cloud);
		}
	}

	_objectsPics.insert(pair<string, QPixmap>("sky", QPixmap("resources/background/sky.png")));
	_objectsPics.insert(pair<string, QPixmap>("ground", QPixmap("resources/background/ground.png")));
	_objectsPics.insert(pair<string, QPixmap>("icons", QPixmap("resources/background/icons.png")));


	auto sky = new QGraphicsPixmapItem(_objectsPics.find("sky")->second);
	sky->setZValue(-1.0);
	_backgroundObjects.insert(pair<string, QGraphicsPixmapItem*>("sky", sky));
	_scene->addItem(_backgroundObjects.find("sky")->second);
	auto ground = new QGraphicsPixmapItem(_objectsPics.find("ground")->second);
	ground->setZValue(-0.8);
	_backgroundObjects.insert(pair<string, QGraphicsPixmapItem*>("ground", ground));
	_scene->addItem(_backgroundObjects.find("ground")->second);
	auto icons = new QGraphicsPixmapItem(_objectsPics.find("icons")->second);
	icons->setZValue(-0.5);
	_backgroundObjects.insert(pair<string, QGraphicsPixmapItem*>("icons", icons));
	_scene->addItem(_backgroundObjects.find("icons")->second);


}




void background::updateClouds(int timerInterval) {
	// Обновление координат каждого облака на сцене и удаление при необходимости
	auto it = _sceneClouds.begin();
	while (it != _sceneClouds.end()) {
		auto sceneCloud = *it;
		auto p = sceneCloud->pos();
		p.setX(p.x() + static_cast<qreal>(_cloudSpeed) / timerInterval);
		if (p.x() > _backgroundSize.width() + _maxCloudSize.width() / 2) {
			it = _sceneClouds.erase(it);
			_scene->removeItem(sceneCloud);
			delete sceneCloud;
		}
		else {
			sceneCloud->setPos(p);
			++it;
		}
	}

	// Добавление новых облаков при необходимости
	if (_clouds.empty())
		return;
	const auto firstUpdate = _sceneClouds.empty();
	uniform_int_distribution<int> cloudDist(0, static_cast<int>(_clouds.size()) - 1);
	uniform_int_distribution<int> yDist(0, _backgroundSize.height() / 3 - 1);

	int i = 0;
	while (static_cast<int>(_sceneClouds.size()) < _cloudCount) {
		const auto cloud = _clouds[cloudDist(_random)];
		const auto sceneCloud = new QGraphicsPixmapItem(cloud);
		int x = 0;
		if (firstUpdate) {
			x = _backgroundSize.width() / _cloudCount * i;
			++i;
		}
		else x = -cloud.width();
		const auto y = yDist(_random);
		sceneCloud->setPos(x, y);
		sceneCloud->setZValue(-0.9);
		_scene->addItem(sceneCloud);
		_sceneClouds.push_back(sceneCloud);
	}

}










//
//
//      BUTTONS
//
//


buttons::buttons(QGraphicsScene* scene) : _scene(scene) {
	_attacks = unique_ptr <QTabWidget>(new QTabWidget);
	_attacks->setFixedSize(200, 190);
	_attacks->move(0, 500);
	/*_attacks->setStyleSheet("QTabWidget{" "color: #000000;"
		"background-color: #FF6347;"
		"border: 2px solid #800000;"
		"}");*/

	_buttons.push_back(new QPushButton(u8"Wind"));
	_buttons.push_back(new QPushButton(u8"Shine"));
	_buttons.push_back(new QPushButton(u8"Vortex"));
	_buttons.push_back(new QPushButton(u8"Heal"));
	_buttons.push_back(new QPushButton(u8"Special Attack"));

	for (int i = 0; i < 5; ++i) {
		_buttons[i]->setBaseSize(170, 50);
		_buttons[i]->setFont(QFont("Times", 20, QFont::Bold));
		_buttons[i]->setStyleSheet("QPushButton{" "color: #0d1821;"
			"background-color: #669e85;"
			"border: 2px solid #005222;"
			"}");
	}

	QVBoxLayout* b1 = new QVBoxLayout();
	b1->addWidget(_buttons[0]);
	b1->addWidget(_buttons[1]);
	b1->addWidget(_buttons[2]);

	QVBoxLayout* b2 = new QVBoxLayout();
	b2->addWidget(_buttons[3]);
	b2->addWidget(_buttons[4]);

	auto tab1 = new QFrame();
	tab1->setFrameStyle(QFrame::Panel + QFrame::Raised);
	tab1->setLineWidth(4);
	tab1->setLayout(b1);
	tab1->setStyleSheet("QFrame{" "background-color: #669e85;"
		"border: 2px solid #800000;"
		"}");



	auto tab2 = new QFrame();
	tab2->setFrameStyle(QFrame::Panel + QFrame::Raised);
	tab2->setLineWidth(4);
	tab2->setLayout(b2);
	tab2->setStyleSheet("QFrame{" "background-color: #669e85;"
		"border: 2px solid #800000;"
		"}");

	_attacks->addTab(tab1, "attacks");
	_attacks->addTab(tab2, "special");


	_scene->addWidget(_attacks.get());





	//HP, mana

	_KillHP = 500;
	_KillMana = 400;
	_monsterHP = 500;
	_KillSP = 3;

	auto KillHP = new QGraphicsRectItem;

	KillHP->setBrush(QBrush("#539e47"));
	KillHP->setRect(380, 570, _KillHP, 30);


	auto KillMana = new QGraphicsRectItem;
	KillMana->setBrush(QBrush("#004fc5"));
	KillMana->setRect(380, 610, _KillMana, 20);

	auto monsterHP = new QGraphicsRectItem;
	monsterHP->setBrush(QBrush("#c50024"));
	monsterHP->setRect(460, 60, _monsterHP, 30);

	_stats.insert(pair<string, QGraphicsRectItem*>("KillHP", KillHP));
	_stats.insert(pair<string, QGraphicsRectItem*>("KillMana", KillMana));
	_stats.insert(pair<string, QGraphicsRectItem*>("monsterHP", monsterHP));

	_scene->addItem(_stats.find("KillHP")->second);
	_scene->addItem(_stats.find("KillMana")->second);
	_scene->addItem(_stats.find("monsterHP")->second);


	//names


	auto KillName = new QGraphicsTextItem(u8"Хранитель леса");
	KillName->setFont(QFont("Times", 30, QFont::Bold));
	KillName->setPos(380, 520);


	auto monsterName = new QGraphicsTextItem(u8"Демон пустоши");
	monsterName->setFont(QFont("Times", 30, QFont::Bold));
	monsterName->setPos(680, 10);


	auto SP = new QGraphicsTextItem(u8"SP: 3");
	SP->setFont(QFont("Times", 24, QFont::Bold));
	SP->setPos(380, 640);


	_names.insert(pair<string, QGraphicsTextItem*>("KillName", KillName));
	_names.insert(pair<string, QGraphicsTextItem*>("monsterName", monsterName));
	_names.insert(pair<string, QGraphicsTextItem*>("SP", SP));

	_scene->addItem(_names.find("KillName")->second);
	_scene->addItem(_names.find("monsterName")->second);
	_scene->addItem(_names.find("SP")->second);

}


void buttons::updateKillHP(int HP) {
	_KillHP += HP;
	if (_KillHP <= 0) _KillHP = 1;
	_stats.find("KillHP")->second->setRect(380, 570, _KillHP, 30);
}

void buttons::updateKillMana(int mana) {
	_KillMana -= mana;
	if (_KillMana <= 0) _KillMana = 1;
	_stats.find("KillMana")->second->setRect(380, 610, _KillMana, 20);
}
void buttons::updateMonsterHP(int HP) {
	_monsterHP -= HP;
	if (_monsterHP <= 0) _monsterHP = 1;
	_stats.find("monsterHP")->second->setRect(460 + (500 - _monsterHP), 60, _monsterHP, 30);
}


void buttons::updateSP() {
	_scene->removeItem(_names.find("SP")->second);
	_names.erase("SP");

	QString s(--_KillSP + 48);

	auto SP = new QGraphicsTextItem(u8"SP: " + s);
	SP->setFont(QFont("Times", 24, QFont::Bold));
	SP->setPos(380, 640);

	_names.insert(pair<string, QGraphicsTextItem*>("SP", SP));

	_scene->addItem(_names.find("SP")->second);
}