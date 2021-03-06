#include <SFML/Window.hpp>
#include <complex> // for simple polar -> cartesian convertion
#include "ship.hpp"

using namespace sf;


float Entity::getGravity() {
	return gravity;
}

Ship::Ship(const int initx, const int inity, const int sizex, const int sizey)
{
	shape.setSize(Vector2f(sizex, sizey));
	shape.setFillColor(Color::Blue);
	shape.setOrigin(sizex / 2.0f, sizey / 2.0f);
	shape.setPosition(initx, inity);
}

RectangleShape Ship::getShape()
{
	return shape;
}

Vector2f Ship::getVelocity()
{
	return velocity;
}

Vector2f Ship::getPosition() {
	return shape.getPosition();
}

float Ship::getThrusterRotation() {
	return thrusterRotationImpulse;
}

float Ship::getThrusterPropulsion() {
	return thrusterPropulsionImpulse;
}

void Ship::followMouse(Vector2i mpos){
	if (mpos.x > shape.getPosition().x) {
		velocity.x += shipAccel;
	} else {
		velocity.x -= shipAccel;
	}
	if (mpos.y > shape.getPosition().y) {
		velocity.y += shipAccel;
	} else {
		velocity.y -= shipAccel;
	}
}

void Ship::followMouseLine(Vector2i mpos)
{
	//Vector2f spos = shape.getPosition();
	Vector2f spos = shape.getPosition();
	float xdiff = static_cast<float>(mpos.x) - spos.x;
	float ydiff = static_cast<float>(mpos.y) - spos.y;
	velocity.x = xdiff / 20;
	velocity.y = ydiff / 20;
}

void Ship::followMouseThrusters(Vector2i mpos) {
	Vector2f spos = shape.getPosition();
	float ydiff = static_cast<float>(mpos.y) - spos.y;
	if (ydiff < -100) {
		//shape.rotate(1);
		fireLeftThruster(100);
		fireRightThruster(100);
	}
	else if (ydiff > -100 && ydiff <= -50) {
		fireLeftThruster(50);
		fireRightThruster(50);
	}
	else if (ydiff > -50 && ydiff <= 0) {
		fireLeftThruster(25);
		fireRightThruster(25);
	}

	// limit velocity
	// if (velocity.y < -0.02) {
	// 	velocity.y = 0.01;
	// }
	// else if (velocity.y > 0.02) {
	// 	velocity.y = 0.01;
	// }
}

void Ship::applyGravity(){
	velocity.y += getGravity() / 5;
}

void Ship::update()
{
	if(Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		velocity.x -= keyPressAccel;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		velocity.x += keyPressAccel;
	}
	if(Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		velocity.y -= keyPressAccel;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		velocity.y += keyPressAccel;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		velocity.x *= .95f;
		velocity.y *= .95f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		fireLeftThruster(100);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::T)) {
		fireRightThruster(100);
	}
	//shape.rotate(1.0f);
	shape.move(velocity);
	// apply rotation
	shape.setRotation(rotation);
}

void Ship::fireLeftThruster(unsigned int percent) {
	// limit percentage
	if (percent > 100) {
		percent = 100;
	}
	// apply rotation
	rotation += getThrusterRotation();
	//shape.rotate(getThrusterRotation());
	// apply thrust
	const float thrust = static_cast<float>(percent) / 100.0f * getThrusterPropulsion();
	std::complex<float> thrustPointer = std::polar(thrust, shape.getRotation() * static_cast<float>(M_PI) / 180.0f);
	velocity.y -= real(thrustPointer);
	velocity.x += imag(thrustPointer);
}

void Ship::fireRightThruster(unsigned int percent) {
	// limit percentage
	if (percent > 100) {
		percent = 100;
	}
		// apply rotation
	rotation -= getThrusterRotation();
	//shape.rotate(-getThrusterRotation());
	// apply thrust
	const float thrust = static_cast<float>(percent) / 100.0f * getThrusterPropulsion();
	std::complex<float> thrustPointer = std::polar(thrust, shape.getRotation() * static_cast<float>(M_PI) / 180.0f);
	velocity.y -= real(thrustPointer);
	velocity.x += imag(thrustPointer);	
}

void Ship::inputUp() {
	velocity.y -= 0.1f;
}