#include "Headers/Paddle.h"

void Paddle::updateRotation()
{
	//X range is -1 to 1
	//Rotation should be between maxRotate range (-maxRotate to maxRotate linearly)
	rotation = (body->GetPosition().x * maxRotate) * DEG2RAD;

}

float Paddle::getRotation()
{
	return rotation;
}

void Paddle::updatePosition(float x) //Takes in mouse input
{
	//Clamp paddle to screen
	x = b2Clamp(x, -1.0f, 1.0f);

	//Idea here is to raise the paddle slightly on the Y axis the further left or right it goes
	float y = (pos.y + x / 5); //Simply adds a small portion of the X value
	
	if (x < 0) //X is negative if on the left side
	{
		y = (pos.y + (x * -1) / 5); //Changes x to positive
	}
	body->SetTransform(b2Vec2(x, y), rotation);
	
		

	

	
}




