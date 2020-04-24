#include"Grid.h"
int jjj = 0;
Grid::Grid()
{
	this->app = NULL;
	this->sizeX = 0;
	this->sizeY = 0;
	this->posX = 0;
	this->posY = 0;
	this->texture_id = 0;
	this->LeftPreBehRel = false;
	this->RightPreBehRel = false;
	this->isMineSetted = false;
	this->isClickOnce = false;
	this->isPressLR = false;
	this->isReadyToShow = false;
	this->sta = REV;
}

void Grid::Init_texture(Texture t)
{
	this->t = t;
	this->s.setTexture(t);
	this->s.setTextureRect(IntRect(0, 0, this->sizeX, this->sizeY));
}

void Grid::setPosition(int x, int y)
{
	this->s.setPosition(x, y);
}

void Grid::show()
{
	switch (this->sta)
	{
	case REV:
		this->s.setTexture(t);
		this->s.setTextureRect(IntRect(this->sizeX, 0, this->sizeX, this->sizeY));
		break;
	case FRO:
		this->s.setTexture(t);
		if (this->texture_id == 0)
			this->s.setTextureRect(IntRect(0, 0, this->sizeX, this->sizeY));
		else if(this->texture_id == 9)
			this->s.setTextureRect(IntRect(2 * this->sizeX, 0, this->sizeX, this->sizeY));
		else
			this->s.setTextureRect(IntRect((this->texture_id + 2) * this->sizeX, 0, this->sizeX, this->sizeY));
		break;
	case FLA:
		this->s.setTexture(t);
		this->s.setTextureRect(IntRect(11 * this->sizeX, 0, this->sizeX, this->sizeY));
		break;
	case WEN:
		this->s.setTexture(t);
		this->s.setTextureRect(IntRect(12 * this->sizeX, 0, this->sizeX, this->sizeY));
		break;
	default:
		break;
	}
	if (this->isReadyToShow)
	{
		this->s.setTexture(t);
		this->s.setTextureRect(IntRect(13 * this->sizeX, 0, this->sizeX, this->sizeY));
	}
	(*this->app).draw(this->s);
}

void Grid::setTextureID(int id)
{
	this->texture_id = id;
}

bool Grid::onClickRight(Event& e)
{
	FloatRect box = s.getGlobalBounds();
	if (Mouse::getPosition(*app).x >= box.left && Mouse::getPosition(*app).x <= (box.left + box.width) && Mouse::getPosition(*app).y >= box.top && Mouse::getPosition(*app).y <= (box.top + box.height))
	{
		if (isPressLR)
		{
			this->RightPreBehRel = false;
			return false;
		}
		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Right)
			this->RightPreBehRel = true;
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Right && this->RightPreBehRel)
		{
			this->RightPreBehRel = false;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool Grid::onClickLeft(Event& e)
{
	FloatRect box = s.getGlobalBounds();
	if (Mouse::getPosition(*app).x >= box.left && Mouse::getPosition(*app).x <= (box.left + box.width) && Mouse::getPosition(*app).y >= box.top && Mouse::getPosition(*app).y <= (box.top + box.height))
	{
		if (isPressLR)
		{
			this->LeftPreBehRel = false;
			return false;
		}
		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
			this->LeftPreBehRel = true;
		if (e.type == Event::MouseButtonReleased&& e.mouseButton.button == Mouse::Left && this->LeftPreBehRel)
		{
			this->LeftPreBehRel = false;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool Grid::onClickDouble(Event& e)
{
	if (isPressLR)
		return false;
	FloatRect box = s.getGlobalBounds();
	if (Mouse::getPosition(*app).x >= box.left && Mouse::getPosition(*app).x <= (box.left + box.width) && Mouse::getPosition(*app).y >= box.top && Mouse::getPosition(*app).y <= (box.top + box.height))
	{
		if (e.type==Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Grid::onCLickLR(Event& e)
{
	bool flag = false;
	FloatRect box = s.getGlobalBounds();
	if (Mouse::getPosition(*app).x >= box.left && Mouse::getPosition(*app).x <= (box.left + box.width) && Mouse::getPosition(*app).y >= box.top && Mouse::getPosition(*app).y <= (box.top + box.height))
	{
		if (Mouse::isButtonPressed(Mouse::Left) && Mouse::isButtonPressed(Mouse::Right))
		{
			isPressLR = true;
			flag = true;
		}
		else
		{
			if (isPressLR)
				flag = true;
			isPressLR = false;
		}
	}
	else
	{
		isPressLR = false;
		flag = false;
	}
	return flag;
}