#pragma once
#include "FWApplication.h"
#include <SDL_rect.h>


class IGameObject
{
public:
	IGameObject() : mIsActive(true) { mApplication = FWApplication::GetInstance(); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Abstract draw method </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Draw()
	{
		if (!mIsActive)
			return;

		if (mWidth == 0 || mHeight == 0)
			mApplication->DrawTexture(mTexture, mX, mY);
		else
			mApplication->DrawTexture(mTexture, mX, mY, mWidth, mHeight);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Abstract update method </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="deltaTime">	The delta time. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Update(float deltaTime) = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Abstract onCollision method </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="collidedObject">	[in,out] If non-null, the collided object. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void OnCollision(IGameObject * collidedObject){ }


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Set the offset of this object (translation) </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="x">	The uint32_t to process. </param>
	/// <param name="y">	The uint32_t to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetOffset(uint32_t x, uint32_t y) { this->mX = x; this->mY = y; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the offset of this object (translation) </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="x">	[in,out] The uint32_t &amp; to process. </param>
	/// <param name="y">	[in,out] The uint32_t &amp; to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void GetOffset(uint32_t & x, uint32_t & y) const { x = this->mX; y = this->mY; };


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Set the bounding box of this object. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetSize(uint32_t width, uint32_t height) { this->mWidth = width; this->mHeight = height; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the bounding box of this object. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="width"> 	[in,out] The width. </param>
	/// <param name="height">	[in,out] The height. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void GetSize(uint32_t & width, uint32_t & height) const { width = this->mWidth; height = this->mHeight; }


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Move this object by a given amount. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="x">	The uint32_t to process. </param>
	/// <param name="y">	The uint32_t to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Translate(uint32_t x, uint32_t y) { this->mX += x; this->mY += y; }

	////************************************
	//// Method:    SetColor
	//// FullName:  IGameObject::SetColor
	//// Access:    virtual public 
	//// Returns:   void
	//// Qualifier:
	//// Parameter: const Color & color
	//// Description: 
	////************************************
	//virtual void SetColor(const Color & color) { this->mColor = color; }
	////************************************
	//// Method:    GetColor
	//// FullName:  IGameObject::GetColor
	//// Access:    virtual public 
	//// Returns:   Color
	//// Qualifier: const
	////************************************
	//virtual Color GetColor() const { return mColor; }


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Set the texture of this object. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="texture">	[in,out] If non-null, the texture. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetTexture(SDL_Texture * texture) { mTexture = texture; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the texture of this object. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <returns>	The texture. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual SDL_Texture * GetTexture() const { return mTexture; }


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the distance to another object </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="obj">	[in,out] If non-null, the object. </param>
	///
	/// <returns>	Distance to object. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual float DistanceTo(IGameObject * obj)
	{
		return sqrt(pow((float)obj->GetBoundingBox().x - mX, 2) + pow((float)obj->GetBoundingBox().y - mY, 2));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the distance to a given position </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="x">	The x coordinate. </param>
	/// <param name="y">	The y coordinate. </param>
	///
	/// <returns>	Distance to object. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual float DistanceTo(int x, int y)
	{
		return sqrt(pow((float)x - mX, 2) + pow((float)y - mY, 2));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the rect of this object. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <returns>	The bounding box. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual SDL_Rect GetBoundingBox() const
	{
		SDL_Rect rect;
		rect.x = mX;
		rect.y = mY;
		rect.w = mWidth;
		rect.h = mHeight;

		return rect;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Check if an object is currently colliding with another object. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="o">	[in,out] If non-null, the IGameObject * to process. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool CheckCollision(IGameObject * o)
	{
		SDL_Rect collisionRect = Intersection(GetBoundingBox(), o->GetBoundingBox());

		if (collisionRect.w == 0 && collisionRect.h == 0)
			return false;

		return true;
	}

	virtual void SetActive(bool isActive) { mIsActive = isActive;  };

protected:
	FWApplication * mApplication;
	SDL_Texture * mTexture;
	
	uint32_t mX, mY;
	uint32_t mWidth, mHeight;
	bool mIsActive;
	//Color mColor;

private:

	SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
	{
		int x1 = Max(boundsA.x, boundsB.x);
		int y1 = Max(boundsA.y, boundsB.y);
		int x2 = Min(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
		int y2 = Min(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

		int width = x2 - x1;
		int height = y2 - y1;

		if (width > 0 && height > 0)
		{
			SDL_Rect intersect = { x1, y1, width, height };
			return intersect;
		}
		else
		{
			SDL_Rect intersect = { 0, 0, 0, 0 };
			return intersect;
		}
	}

	int Max(int a, int b)
	{
		if (a > b)
			return a;

		return b;
	}
	int Min(int a, int b)
	{
		if (a < b)
			return a;

		return b;
	}
};