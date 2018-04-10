////Author: John McGrath
//#include "BulletHandler.h"
//
///// <summary>
///// Constructor for the Bullet Handler
///// </summary>
//BulletHandler::BulletHandler()
//{
//	m_rofTimer = SDL_GetTicks();
//	//tempEnt.addComponent<RenderComponet>
//
//	for (size_t i = 0; i < 100; i++)
//	{
//		//m_bullets.push_back(new Bullet());
//	}
//}
//
///// <summary>
///// Update loop for the bullet handler
///// </summary>
///// <param name="pos">Position the bullets are coming from</param>
///// <param name="targetPos">Position of the target</param>
//void BulletHandler::Update(SDL_Point pos, SDL_Point targetPos)
//{
//	calculateBulletAngle(pos, targetPos);
//
//	//Get the current time
//	m_rofTimer = SDL_GetTicks();
//
//	//If the m_rofCap (ms) amount of time has passed since last time
//	if (m_rofTimer > m_previousTime + m_rofCap)
//	{
//		if (m_isFiring)
//		{
//			//Check to make sure you've not exited the vector
//			if (m_bulletCounter < m_bullets.size())
//			{
//				m_previousTime = SDL_GetTicks();
//
//				//Fire the current bullet
//				ResetBullet(m_bulletCounter);
//
//				//Repeating loop of 0 to 100
//				if (m_bulletCounter < 100)
//				{
//					m_bulletCounter++;
//				}
//
//				else
//				{
//					m_bulletCounter = 0;
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < m_bullets.size(); i++)
//	{
//		//The the update loop returns that the bullet has traveled it's max distance
//		//if (m_bullets[i]->Update() == -1)
//		//{
//		//	//if the bullet is out of range, make it the next bullet to be used 
//		//	m_bulletCounter = i;
//		//}
//	}
//}
//
///// <summary>
///// Update loop for the bullet handler
///// </summary>
///// <param name="pos">Position the bullets are coming from</param>
///// <param name="targetPos">Position of the target</param>
////void BulletHandler::UpdateWithComponent(SDL_Point pos, SDL_Point targetPos, WeaponComponent gun)
////{
////	calculateBulletAngle(pos, targetPos);
////
////	//Get the current time
////	m_rofTimer = SDL_GetTicks();
////
////	//If the m_rofCap (ms) amount of time has passed since last time
////	if (m_rofTimer > m_previousTime + gun.getTimeBetweenShots())
////	{
////		if (m_isFiring)
////		{
////			//Check to make sure you've not exited the vector
////			if (m_bulletCounter < m_bullets.size())
////			{
////				m_previousTime = SDL_GetTicks();
////				//cout << "Bullet: " << m_bulletCounter << endl;
////
////				//Sets the bullet with the guns values
////				m_bullets[m_bulletCounter]->setValuesFromComponent(gun);
////
////				//Fire the current bullet
////				ResetBullet(m_bulletCounter);
////			
////
////				//Repeating loop of 0 to 100
////				if (m_bulletCounter < 100)
////				{
////					m_bulletCounter++;
////				}
////
////				else
////				{
////					m_bulletCounter = 0;
////				}
////			}
////		}
////	}
////
////	for (int i = 0; i < m_bullets.size(); i++)
////	{
////		//The the update loop returns that the bullet has traveled it's max distance
////		if (m_bullets[i]->Update() == -1)
////		{
////			//if the bullet is out of range, make it the next bullet to be used 
////			m_bulletCounter = i;
////		}
////	}
////}
//
///// <summary>
///// Calculate the angle between two vectors
///// </summary>
///// <param name="pos">First vector</param>
///// <param name="targetPos">Second vector</param>
//void BulletHandler::calculateBulletAngle(SDL_Point pos, SDL_Point targetPos)
//{
//	m_firingPos = pos;
//	m_cursorPos = targetPos;
//
//	//Get the vector from one point to the other
//	m_aimDirX = m_cursorPos.x - m_firingPos.x;
//	m_aimDirY = m_cursorPos.y - m_firingPos.y;
//
//	//Normalise it
//	norm = Normalise(m_aimDirX, m_aimDirY);
//
//	//Increase it by max speed
//	//m_normalisedAimDirX = norm.x * m_bullets[m_bulletCounter]->getMaxSpeed();
//	//m_normalisedAimDirY = norm.y * m_bullets[m_bulletCounter]->getMaxSpeed();
//}
//
///// <summary>
///// Normalise a vector as a Point2D
///// </summary>
///// <param name="v">The Vector to be normalised</param>
//CD_Vector BulletHandler::Normalise(SDL_Point v)
//{
//	float mag;
//
//	mag = sqrt((v.x * v.x) + (v.y * v.y));
//	norm.x = v.x / mag;
//	norm.y = v.y / mag;
//
//	return norm;
//}
//
///// <summary>
///// Normalise a vector as two Float values
///// </summary>
///// <param name="x">The x componant to be normalised</param>
///// <param name="y">The y componant to be normalised</param>
//CD_Vector BulletHandler::Normalise(float x, float y)
//{
//	float mag;
//
//	mag = sqrt((x * x) + (y * y));
//	norm.x = x / mag;
//	norm.y = y / mag;
//
//	return norm;
//}
//
///// <summary>
///// Reset the bullet and fire it using the current aiming vector
///// </summary>
///// <param name="i">The position of the bullet to be reset</param>
//void BulletHandler::ResetBullet(int i)
//{
//	if (i < 100)
//	{
//		//m_bullets[i]->m_dst.x = m_firingPos.x;
//		//m_bullets[i]->m_dst.y = m_firingPos.y;
//		//m_bullets[i]->setStartingPoint(m_firingPos);
//		//m_bullets[i]->m_velocity.x = m_normalisedAimDirX;
//		//m_bullets[i]->m_velocity.y = m_normalisedAimDirY;
//	}
//}
//
///// <summary>
///// Render function for the bullets
///// </summary>
///// <param name="Renderer">The renderer we want to copy to</param>
//void BulletHandler::Render(SDL_Renderer * Renderer)
//{
//	for (int i = 0; i < m_bullets.size(); i++)
//	{
//		//SDL_RenderCopy(Renderer, m_bullets[i]->m_sprite, &m_bullets[i]->m_src, &m_bullets[i]->m_dst);
//	}
//}
//
///// <summary>
///// Makes the bullet disappear
///// </summary>
///// <param name="i">The position of the bullet to disappear</param>
//void BulletHandler::RemoveBullet(int i)
//{
//	if (i < 100)
//	{
//		/*m_bullets[i]->m_dst.x = -100;
//		m_bullets[i]->m_dst.y = -100;
//		SDL_Point temp;
//		temp.x = -100;
//		temp.y = -100;
//		m_bullets[i]->setStartingPoint(temp);
//		m_bullets[i]->m_velocity.x = 0;
//		m_bullets[i]->m_velocity.y = 0;
//		m_bulletCounter = i;*/
//	}
//}