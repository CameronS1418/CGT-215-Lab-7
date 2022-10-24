#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{

	int hitCount(1);
	int BangCount(1);

	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(150, 100));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	window.draw(ball);

	// Middle Rectangle
	PhysicsRectangle square;
	square.setCenter(Vector2f(400, 300));
	square.setSize(Vector2f(100, 100));
	square.setStatic(true);
	world.AddPhysicsBody(square);

	square.onCollision = [&BangCount](PhysicsBodyCollisionResult) {
		cout << "Bang " << BangCount << endl;
		BangCount++;
	};


	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	floor.onCollision = [&hitCount](PhysicsBodyCollisionResult result) {
		cout << "Hit " << hitCount << endl;
		hitCount++;

	};

	// Left Wall
	PhysicsRectangle wall1;
	wall1.setSize(Vector2f(20, 560));
	wall1.setCenter(Vector2f(0, 300));
	wall1.setStatic(true);
	world.AddPhysicsBody(wall1);
	window.draw(wall1);
	wall1.onCollision = [&hitCount](PhysicsBodyCollisionResult result) {
		cout << "Hit " << hitCount << endl;
		hitCount++;
	};

	// Roof
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	window.draw(ceiling);
	ceiling.onCollision = [&hitCount](PhysicsBodyCollisionResult result) {
		cout << "Hit " << hitCount << endl;
		hitCount++;

	};

	// Right Wall
	PhysicsRectangle wall2;
	wall2.setSize(Vector2f(20, 560));
	wall2.setCenter(Vector2f(800, 300));
	wall2.setStatic(true);
	world.AddPhysicsBody(wall2);
	window.draw(wall2);
	wall2.onCollision = [&hitCount](PhysicsBodyCollisionResult result) {
		cout << "Hit " << hitCount << endl;
		hitCount++;
	};
	ball.applyImpulse(Vector2f(0.50, 0));

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(square);
		window.draw(wall1);
		window.draw(ceiling);
		window.draw(wall2);
		window.display();
		if (BangCount == 4) {
			exit(0);
		}
	}
}
