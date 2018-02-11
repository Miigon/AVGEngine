#include "Label.h"
#include "../Application.h"

void Label::draw()
{
	const auto windowWidth = Application::getInstance()->windowWidth;
	const auto windowHeight = Application::getInstance()->windowHeight;

	const auto poxX = getDouble("pos.x");
	const auto poxY = getDouble("pos.y");

	const auto height = getDouble("size.height");
	const auto width = getDouble("size.width");

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d(poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d(poxX / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1);
	
	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d((poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d((poxX + width) / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1);

	glEnd();
}
