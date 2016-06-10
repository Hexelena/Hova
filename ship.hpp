#ifndef HOVA_SHIP_H
#define HOVA_SHIP_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
protected:
	// gravity factor in g | [g] = m/s^2
	const float gravity = 1.0f;
public:
	float getGravity();

	virtual void applyGravity() = 0;
	virtual void update() = 0;
};

class Ship : public Entity{
private:
	const float keyPressAccel = .4f;
	const float shipAccel = .96f;
	const float thrusterRotationImpulse = 4.0f;
	const float thrusterPropulsionImpulse = 1.0f;
	Vector2f velocity{0.0f, 0.1f};
	RectangleShape shape;

public:
	Ship(const int initx, const int inity, const int sizex, const int sizey);
	float getX();
	float getY();
	float getThrusterRotation();
	float getThrusterPropulsion();
	Vector2f getPosition();
	RectangleShape getShape();
	Vector2f getVelocity();

	void followMouse(Vector2i mpos);
	void followMouseLine(Vector2i mpos);

	void inputUp();

	void applyGravity() override;
	void update() override;
};


#endif // HOVA_SHIP_H