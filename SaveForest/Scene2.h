#pragma once

#include <QGraphicsScene>
#include <unordered_map>
#include <QPushButton>
#include <QBoxLayout>

class Scene2 : public QGraphicsScene {
	std::unique_ptr<QPushButton> _nextScene;
	std::unique_ptr<QPushButton> _next;
	std::unordered_map<std::string, QGraphicsPixmapItem*> _items;
	std::unordered_map<std::string, QGraphicsTextItem*> _texts;

	void setFont(QGraphicsTextItem*);

	Q_OBJECT
private slots:
	void next2();
	void next3();
	void next4();
	void next5();
public:
	Scene2();

	QPushButton* getNextScene() const;

	//добавить кнопочку
};

