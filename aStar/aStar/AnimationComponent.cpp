#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(int f, int x, int d, int width, AnimTypes t)
{
	m_current = t;
	CurrentState = new Idle;
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::init()
{
	m_sprite = &m_owner->getComponent<SpriteComponent>();
	m_movement = &m_owner->getComponent<MovementComponent>();
}

void AnimationComponent::update()
{
	timer += 1.0f / 60.0f;
	if (timer >= 0.2f)
	{
		CurrentState->Animate(m_sprite, m_movement, m_animInfo[m_current].Frames, m_animInfo[m_current].CurrentFrame,
			m_animInfo[m_current].MaxWidth, this);
		timer = 0.0f;
	}
}

void AnimationComponent::idle()
{
	CurrentState->idle(this);
	m_current = AnimTypes::Idle;
	m_sprite->setSheetPosition(m_sprite->getSpriteDimensions().x, m_animInfo[m_current].Height);
}

void AnimationComponent::walk()
{
	CurrentState->walk(this);
	m_current = AnimTypes::Walking;
	m_sprite->setSheetPosition(m_sprite->getSpriteDimensions().x, m_animInfo[m_current].Height);
}

void AnimationComponent::fire()
{
	CurrentState->fire(this);
	m_current = AnimTypes::Firing;
	m_sprite->setSheetPosition(m_sprite->getSpriteDimensions().x, m_animInfo[m_current].Height);
}

void AnimationComponent::dead()
{
	CurrentState->dead(this);
	m_current = AnimTypes::Dead;
	m_sprite->setSheetPosition(m_sprite->getSpriteDimensions().x, m_animInfo[m_current].Height);
}

void AnimationComponent::addAnimation(AnimTypes T, int F, int W, int D, int H)
{
	m_animInfo[T].CurrentFrame = 0;
	m_animInfo[T].Frames = F;
	m_animInfo[T].Height = H;
	m_animInfo[T].MaxWidth = W;
	m_animInfo[T].widthDiff = D;
}

void AnimationComponent::setAnim(AnimTypes value)
{
	m_current = value;
}

AnimTypes AnimationComponent::getAnim()
{
	return m_current;
}

void AnimationComponent::setCurrent(State * value)
{
	CurrentState = value;
}

//////////////////////////////////////////////////////////////////////////

void Idle::Walking(AnimationComponent * A)
{
}

void Idle::fire(AnimationComponent * A)
{
	A->setCurrent(new Fire);

	delete this;
}

void Idle::Dead(AnimationComponent * A)
{
}

void Idle::Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent * A)
{
	float x = Sprite->getSpriteDimensions().x;
	float y = Sprite->getSpriteDimensions().y;

	if (CurrentFrame == Frames)
	{
		CurrentFrame = 0;
		Sprite->setSheetPosition(0, y);
	}
	else
	{
		Sprite->setSheetPosition(x + Width, y);
		CurrentFrame++;
	}
}

//////////////////////////////////////////////////////////////////////////

void Fire::idle(AnimationComponent* A)
{
	A->setCurrent(new Idle);
	A->idle();

	delete this;
}

void Fire::Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent * A)
{
	float x = Sprite->getSpriteDimensions().x;
	float y = Sprite->getSpriteDimensions().y;

	if (CurrentFrame == Frames)
	{
		CurrentFrame = 0;
		Sprite->setSheetPosition(0, y);
		idle(A);
	}
	else
	{
		Sprite->setSheetPosition(x + Width, y);
		CurrentFrame++;
	}
}

//////////////////////////////////////////////////////////////////////////

void Walk::idle(AnimationComponent * A)
{
	A->setCurrent(new Idle);
	A->idle();

	delete this;
}

void Walk::Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent * A)
{
	float x = Sprite->getSpriteDimensions().x;
	float y = Sprite->getSpriteDimensions().y;

	if (CurrentFrame == Frames)
	{
		CurrentFrame = 0;
		Sprite->setSheetPosition(0, y);
	}
	else
	{
		Sprite->setSheetPosition(x + Width, y);
		CurrentFrame++;
	}

	if (Movement->getVelocity().Length() > 0)
	{
		CurrentFrame = 0;
		Sprite->setSheetPosition(0, y);
		idle(A);
	}
}

//////////////////////////////////////////////////////////////////////////

void Dead::Animate(SpriteComponent * Sprite, MovementComponent * Movement, int & Frames, int & CurrentFrame, int Width, AnimationComponent * A)
{
	float x = Sprite->getSpriteDimensions().x;
	float y = Sprite->getSpriteDimensions().y;

	if (CurrentFrame != Frames)
	{
		Sprite->setSheetPosition(x + Width, y);
		CurrentFrame++;
	}
}