#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

class Position
{
public:
	Coordinate current;
	Coordinate before;

	Position(Coordinate*);

	void Read_Position(Coordinate*);
};

Position::Position(Coordinate *_current)
{
	now = *_current;
}

void Position::Read_Position(Coordinate *_current)
{
	before = current;
	current = *_current;
}

class Rotation
{
public:
	Coordinate current;
	Coordinate before;

	Rotation(Coordinate*);

	void Read_Rotation(Coordinate*);
};

Rotation::Rotation(Coordinate *_current)
{
	current = *_current;
}

void Rotation::Read_Rotation(Coordinate *_current)
{
	before = current;
	current = *_current;
}

class Transform
{
public:
	Position position;
	Rotation rotation;
};

Transform::Transform(Position *_position, Rotation *_rotation)
{
	position = *_position;
	rotation = *_rotation;
}

#endif
