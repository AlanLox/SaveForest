#pragma once

#include <QGraphicsScene>
#include <QPushButton>
#include <memory>

class Scene1 : public QGraphicsScene {
	std::unique_ptr<QPushButton> _nextScene;


	//Q_OBJECT
//public slots:

public:
	Scene1();

	QPushButton* getNextScene() const;
	//добавить кнопочку
};


class Scene4 : public QGraphicsScene {

	std::unique_ptr<QPushButton> _end;
public:
	Scene4(bool end);

	//добавить кнопочку
	QPushButton* endScene() const;
};