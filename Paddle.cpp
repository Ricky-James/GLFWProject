#include "Headers/Paddle.h"

void Paddle::draw()
{

	b2Vec2 center = body->GetPosition();
	float32 angle = body->GetAngle();

	glMatrixMode(GL_MODELVIEW);
	glColor3f(colour[0], colour[1], colour[2]);

	glPushMatrix();             // save the current GL_MODELVIEW matrix 
	{
		glTranslatef(center.x, center.y, 0.0f);
		glRotatef(((GLfloat)angle) * RAD2DEG, 0, 0, 1);  // rotate object
		glTranslatef(-center.x, -center.y, 0.0f);

	}


	float points[8] = {
		(center.x - width / 2), (center.y + height / 2),
		(center.x + width / 2), (center.y + height / 2),
		(center.x + width / 2), (center.y - height / 2),
		(center.x - width / 2), (center.y - height / 2)
	};

	glBegin(GL_QUADS); //Top left, clockwise
	{


		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(points[i], points[i + 1]);
		}
	}
	glEnd();

	glPopMatrix();              // restore the GL_MODELVIEW matrix



}

void Paddle::updateRotation()
{
	//X range is -1 to 1
	//Rotation should be between maxRotate range (-maxRotate to maxRotate linearly)
	rotation = (body->GetPosition().x * maxRotate) * DEG2RAD;

}

double Paddle::getRotation()
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
	body->SetTransform(b2Vec2(x, y), (float32)(rotation));
	
		

	

	
}




