#include "Car.h"

/*
Constructor & Destructor
*/

Car::Car(float _x, float _y, float a, float s) : x(_x), y(_y), angle(a), speed(s)
{
	m_currentLap = 1;
	m_nextLap = false;
}

/*
Getter & Setter
*/
float Car::getX()
{
	return x;
}

float Car::getSpeed()
{
	return speed;
}

float Car::getY()
{
	return y;
}

float Car::getAngle()
{
	return angle;
}

float Car::getLap()
{
	return m_currentLap;
}

/*
Others
*/

void Car::move(sf::Image& maskRace)
{
	
	m_nextX = x + cos(angle * M_PI / 180) *  speed;
	m_nextY = y + sin(angle * M_PI / 180) * speed;

	if (calculateMaskCollision(maskRace))
	{
		x += cos(angle * M_PI / 180) * speed;
		y += sin(angle * M_PI / 180) * speed;
	}		
}

bool Car::calculateMaskCollision(sf::Image& raceMask)
{
	sf::Color nextPos = raceMask.getPixel(m_nextX, m_nextY);

	if (nextPos == sf::Color::Black)
	{
		speedDownFast();
		return false;
	}

	if (nextPos == sf::Color(255, 255, 0))
	{
		m_nextLap = true;
	}

	if (nextPos == sf::Color(0, 0, 128))
	{
		if (m_nextLap)
		{
			m_currentLap++;
			m_nextLap = false;
		}
	}

	if (nextPos == sf::Color::White)
		speedDownFast();

	return true;
}

void Car::turnLeft()
{
	angle -= 2.f;
} 

void Car::turnRight()
{
	angle += 2.f;
}

void Car::speedUp()
{
	if (speed <= m_speedMax)
		speed += m_speedValue;
	else
		speed = 6.1;
}

void Car::speedDown()
{
	if (speed >= m_speedMin)
		speed -= m_speedValue;

	if (speed < 0)
		speed = 0;

}

void Car::speedDownFast()
{
	if (speed - (m_speedValue + 0.05) >= m_limit)
		speed -= (m_speedValue + 0.05) ;
	else
		speed = m_limit;
}