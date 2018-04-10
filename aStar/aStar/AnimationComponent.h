#pragma once
#include <iostream>
#include <map>
#include "ECS.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"

using namespace std;

/// <class> Animation Component
/// <summary>
/// A component to handle the animation
/// variables and available states for
/// each entity. It will work as a FSM.
/// </summary>
/// <author>Jack Keogh</author>

enum class AnimTypes
{
	Idle,
	Walking,
	Firing,
	Dead
};

struct AnimVar
{
	int Frames;
	int CurrentFrame;
	int Height;
	int widthDiff;
	int MaxWidth;
};

class AnimationComponent : public Component
{
private:
	class State * CurrentState;
	AnimTypes m_current;
	map<AnimTypes, AnimVar> m_animInfo;
	SpriteComponent * m_sprite;
	MovementComponent * m_movement;
	float timer;

public:
	/// <summary>
	/// Overload Animation component constructor that defaults params to 0.
	/// </summary>
	/// <param name="f">int defining number of frames.</param>
	/// <param name="x">int defining the start frame.</param>
	/// <param name="d">int defining the difference of width of each frame.</param>
	/// <param name="width">int defining total width of animation.</param>
	/// <param name="t">AnimTypes defining the animation type.</param>
	AnimationComponent(int f = 0, int x = 0, int d = 0, int width = 0, AnimTypes t = AnimTypes::Idle);

	/// <summary>
	/// Default destructor of the animation component.
	/// </summary>
	~AnimationComponent();

	/// <summary>
	/// Override init method inherited from component class.
	/// </summary>
	void init() override;

	/// <summary>
	/// Override update method inherited from component class.
	/// </summary>
	void update() override;

	/// <summary>
	/// These methods handle the current animation.
	/// </summary>
	void idle();
	void walk();
	void fire();
	void dead();

	/// <summary>
	/// This allows an animation to be added to the map
	/// storage of animations.
	/// </summary>
	/// <param name="T">Animation Type.</param>
	/// <param name="F">Number of frames in animation.</param>
	/// <param name="W">Total width of animation sheet.</param>
	/// <param name="D">The Difference of each frame.</param>
	/// <param name="H">The Height value on the animation sheet.</param>
	void addAnimation(AnimTypes T, int F, int W, int D, int H);

	/// <summary>
	/// This method is used to set the animation type.
	/// </summary>
	/// <param name="value">AnimTypes to define the animation type.</param>
	void setAnim(AnimTypes value);

	/// <summary>
	/// This method is used to get the current animation.
	/// </summary>
	/// <returns>m_current.</returns>
	AnimTypes getAnim();

	/// <summary>
	/// sets the current animation state.
	/// </summary>
	/// <param name="value">state to set current animation too </param>
	void setCurrent(State * value);
};

class State
{
public:
	virtual void idle(AnimationComponent* A)
	{

	};
	virtual void walk(AnimationComponent* A)
	{

	};
	virtual void fire(AnimationComponent* A)
	{

	};
	virtual void dead(AnimationComponent* A)
	{

	};

	virtual void Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent* A)
	{

	};
};

class Idle : public State
{
public:
	Idle() {};
	~Idle() {};

	void Walking(AnimationComponent* A);
	void fire(AnimationComponent* A);
	void Dead(AnimationComponent* A);
	void Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent* A);
};

class Fire : public State
{
public:
	Fire() {};
	~Fire() {};

	void idle(AnimationComponent* A);
	void Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent* A);
};

class Walk : public State
{
public:
	Walk() {};
	~Walk() {};

	void idle(AnimationComponent * A);
	void Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent* A);
};

class Dead : public State
{
public:
	Dead() {};
	~Dead() {};

	void Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent* A);
};