#include "Entity.h"
#include "Level.h"
#include "Player.h"
#include "Bullet.h"

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Tower Defense Game");

	view.reset(FloatRect(0, 0, 1280, 720));
	view.zoom(0.5);

	Level level;
	level.LoadFromFile("map.tmx");

	Image cat;
	cat.loadFromFile("images/cat.png");
	cat.createMaskFromColor(Color(255,255,255));

	Object p = level.GetObject("player");

	Player player(cat, "player", level, p.rect.left, p.rect.top, 15, 13);

	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;//второй итератор.для взаимодействия между объектами списка

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) //а именно левая, то стреляем 
				{ //и тут же снимаем координаты мыши в этом месте
					Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
					Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
					entities.push_back(new Bullet(BulletImage, "bullet", level, player.getX(), player.getY(), 16, 16, pos.x, pos.y)); //и передаем в конструктор пули. создается пуля
					//shoot.play();//играем звук пули
				}
		}
		player.update(time);
		window.setView(view);
		window.clear(Color(65, 140, 180));
		level.Draw(window);
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}