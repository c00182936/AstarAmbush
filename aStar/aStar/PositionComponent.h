#pragma once
#include "ECS.h"
#include "SDL.h"
#include "CD_Vector2f.h"

class PositionComponent : public Component
{
public:
	/// <summary>
	/// Default Position Component constructor.
	/// Able to take in to floating point
	/// params to assign the x and y position.
	/// </summary>
	PositionComponent(float X = 0, float Y = 0)
	{
		m_position = CD_Vector(X, Y);
	}

	/// <summary>
	/// Default Initialiser. Creates a 0x0 box at position (0,0)
	/// </summary>
	void init() override
	{
		m_centre = CD_Vector(0, 0);
		m_width = 0;
		m_height = 0;
		m_radius = 0;
		m_rotation = 0;
		m_isCircle = false;
	}

	/// <summary>
	/// Box Initialiser, sets the isCircle variable to false
	/// </summary>
	/// <param name="position">Position of top left most point of box</param>
	/// <param name="height">Height of Box</param>
	/// <param name="width">Width of box</param>
	/// <param name="rotation">Rotation of box</param>
	void setBoxDimensions(CD_Vector position, float height, float width, float rotation)
	{
		m_position = position;
		m_height = height;
		m_width = width;
		m_isCircle = false;
		m_rotation = rotation;
		m_radius = 0; //no radius for quadrilatials. This can be altered if needed
		m_centre = m_position + CD_Vector(m_width / 2, m_height / 2);
	}

	/// <summary>
	/// Circle Initialiser. Sets isCricle to true
	/// </summary>
	/// <param name="centre">The centre point of the circle</param>
	/// <param name="radius">The radius length of the circle</param>
	/// <param name="rotation">The angle of rotation</param>
	void setCircleDimensions(CD_Vector centre, float radius, float rotation)
	{
		m_centre = centre;
		//m_position is always the top corner
		m_position = m_centre - CD_Vector(m_radius, m_radius);;
		m_height = radius * 2;
		m_width = radius * 2;
		m_isCircle = true;
		m_rotation = rotation;
		m_radius = radius;
	}

	/// <summary>
	/// This function adds the passed vector to the position member variable
	/// This also moves the centre point
	/// </summary>
	/// <param name="moveVec">The vector that the position will be moved by</param>
	void move(CD_Vector moveVec)
	{
		//move the position
		m_position = m_position + moveVec;

		//also move the centre point
		m_centre = m_centre + moveVec;
	}

#pragma region basicSetFunctions
	/// <summary>
	/// Sets the position (i.e. the top left point), also moves the centre point accordingly
	/// </summary>
	/// <param name="position">Position to move to</param>
	void setPosition(CD_Vector position)
	{
		m_position = position;

		//also move the centre point to its new position
		if (m_isCircle)
		{
			//if it is a circle
			m_centre = m_position + CD_Vector(m_radius, m_radius);
		}
		else
		{
			//if it is a square
			m_centre = m_position + CD_Vector(m_width / 2, m_height / 2);
		}
	}

	/// <summary>
	/// Changes the height of the box. Does not change radius
	/// </summary>
	/// <param name="height">New height value</param>
	void setHeight(float height)
	{
		m_height = height;
	}

	/// <summary>
	/// Changes the Width of the box. Does not change radius
	/// </summary>
	/// <param name="width">New width value</param>
	void setWidth(float width)
	{
		m_width = width;
	}

	/// <summary>
	/// Changes the radius of the circle. Changes the width and height accordingly
	/// New width and height will be radius * 2
	/// </summary>
	/// <param name="radius">New Radius value</param>
	void setRadius(float radius)
	{
		m_radius = radius;
		m_width = radius * 2;
		m_height = radius * 2;
	}

	/// <summary>
	/// Changes the rotation variable
	/// </summary>
	/// <param name="rotation">New rotation value</param>
	void setRotation(float rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// Changes whether the object will be treated as a box or a circle
	/// </summary>
	/// <param name="circle">True for circle, False for box</param>
	void setIsCircle(bool isCircle)
	{
		m_isCircle = isCircle;
	}
#pragma endregion basicSetFunctions

#pragma region getFunctions
	/// <summary>
	/// Returns the position
	/// </summary>
	/// <returns>Returns a CD_Vector containing the co-ords of the top left point</returns>
	CD_Vector GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// Returns the centre position
	/// </summary>
	/// <returns>Returns a CD_Vector containing the co-ords of the centre point</returns>
	CD_Vector GetCentre()
	{
		return m_centre;
	}

	/// <summary>
	/// Returns the width
	/// </summary>
	/// <returns>Width value as float</returns>
	float GetWidth()
	{
		return m_width;
	}

	/// <summary>
	/// Returns the height
	/// </summary>
	/// <returns>Height value as float</returns>
	float GetHeight()
	{
		return m_height;
	}

	/// <summary>
	/// Returns the radius
	/// </summary>
	/// <returns>Radius value as float</returns>
	float GetRadius()
	{
		return m_radius;
	}

	/// <summary>
	/// Returns the rotation value
	/// </summary>
	/// <returns>Rotation value as float</returns>
	float GetRotation()
	{
		return m_rotation;
	}

	/// <summary>
	/// Returns true if the object is a circle, and false if the onject is a box
	/// </summary>
	/// <returns>Is the object a circle</returns>
	bool GetIsCircle() 
	{
		return m_isCircle; 
	}


	/// <summary>
	/// Returns the y position of the top left point cast as an int
	/// </summary>
	/// <returns>Y Position as int</returns>
	int GetYPosition()
	{
		return m_position.y;
	}

	/// <summary>
	/// Returns the x position of the top left point cast as an int
	/// </summary>
	/// <returns>X Position as int</returns>
	int GetXPosition()
	{
		return m_position.x;
	}
#pragma endregion getFunctions


private:
	CD_Vector m_position;
	CD_Vector m_centre;
	float m_width;
	float m_height;

	//not used as of this moment
	float m_rotation;
	//m_isCircle a bool to decide whether or not to use circle collision detection
	bool m_isCircle;
	//m_radius is needed for circle collisions, set to 0 by default for quadrilaterals
	float m_radius;
};