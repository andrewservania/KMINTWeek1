#include "FWApplication.h"
#include "Config.h"
#include "IGameObject.h"
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

FWApplication * FWApplication::mInstance;

FWApplication::FWApplication(int offsetX, int offsetY, int width, int height)
	: mTargetDelayMS(1000 / 60),
	mStartCycleTimeMS(0),
	mDeltaTimeMS(0),
	mTimeMS(0),
	mIsRunning(true),
	mFontSize(12),
	mFontName("")
	//mTextBackgroundColor(0xFF,0xFF,0xFF,0xFF)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		LOG("SDL init failed");
		return;
	}

	mWindow = SDL_CreateWindow("KMint framework", offsetX, offsetY, width, height, SDL_WINDOW_SHOWN);
	if (!mWindow)
	{
		LOG(SDL_GetError());
		return;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		LOG(SDL_GetError());
		SDL_DestroyWindow(mWindow);
		return;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!IMG_Init(imgFlags) & imgFlags)
	{
		LOG(IMG_GetError());
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		return;
	}

	if (TTF_Init() < 0)
	{
		LOG(TTF_GetError());
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		return;
	}

	//mFont = TTF_OpenFont(GetRelativePath("Resources/OpenSans-Regular.ttf").c_str(), mFontSize);
	SetFontSize(12);
	SetFont("OpenSans-Regular.ttf");


	mInstance = this;
	mGameObjects.reserve(32);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

FWApplication::~FWApplication()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_CloseFont(mFont);
	TTF_Quit();
	SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the window. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <returns>	null if it fails, else the window. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Window * FWApplication::GetWindow() const
{
	return mWindow;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the instance. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <returns>	null if it fails, else the instance. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

FWApplication * FWApplication::GetInstance()
{
	if (!mInstance)
	{
		new FWApplication();
	}

	return mInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Query if this object is running. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <returns>	true if running, false if not. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool FWApplication::IsRunning()
{
	return mIsRunning;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets relative path. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="path">	Full pathname of the file. </param>
///
/// <returns>	The relative path. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

std::string FWApplication::GetRelativePath(const std::string & path) const
{
	std::string basePath = SDL_GetBasePath();
	return basePath + ".." + PATH_SEP + path; //  + PATH_SEP
	//size_t pos = basePath.rfind("Debug");
	//return basePath.substr(0, basePath.rfind("Debug")) + path + PATH_SEP; //  + "resources" + PATH_SEP
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Loads a texture. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="fileName">	Filename of the file. </param>
///
/// <returns>	null if it fails, else the texture. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Texture * FWApplication::LoadTexture(const std::string & fileName)
{
	const std::string path = GetRelativePath("Resources" PATH_SEP + fileName);
	SDL_Surface * surface = IMG_Load(path.c_str());
	if (surface)
	{
		SDL_Texture * texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		if (!texture)
		{
			LOG("Couldn't load texture: " + path);
		}
		return texture;
	}

	LOG("SDL Error, couldn't load BMP: " + path);
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw texture. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="texture">	[in,out] If non-null, the texture. </param>
/// <param name="xOffset">	The offset. </param>
/// <param name="yOffset">	The offset. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::DrawTexture(SDL_Texture * texture, int xOffset, int yOffset)
{
	SDL_Rect rect = { xOffset, yOffset };

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(mRenderer, texture, &rect, &rect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw texture. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="texture">	[in,out] If non-null, the texture. </param>
/// <param name="xOffset">	The offset. </param>
/// <param name="yOffset">	The offset. </param>
/// <param name="width">  	The width. </param>
/// <param name="height"> 	The height. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::DrawTexture(SDL_Texture * texture, int xOffset, int yOffset, int width, int height)
{
	SDL_Rect rect = { xOffset - (width / 2), yOffset - (height / 2), width, height };

	//SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(mRenderer, texture, NULL, &rect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Starts a tick. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::StartTick()
{
	SDL_RenderClear(mRenderer);
	mStartCycleTimeMS = SDL_GetTicks();

	//SDL_Event ev;
	//while (SDL_PollEvent(&ev) != 0)
	//{
	//	if (ev.type == SDL_QUIT)
	//	{
	//		mIsRunning = false;
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Ends a tick. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::EndTick()
{
	SDL_RenderPresent(mRenderer);
	//SDL_UpdateWindowSurface(mWindow);

	mTimeMS = SDL_GetTicks();
	mDeltaTimeMS = mTimeMS - mStartCycleTimeMS;
	if (((int32_t)mTargetDelayMS - (int32_t)mDeltaTimeMS) > 0)
	{
		SDL_Delay(mTargetDelayMS - mDeltaTimeMS);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the game objects. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::UpdateGameObjects()
{
	for (IGameObject * obj : mGameObjects)
	{
		for (IGameObject * o : mGameObjects)
		{
			if (o != obj)
			{
				// Check collision
				bool collided = obj->CheckCollision(o);
				if (collided)
				{
					obj->OnCollision(o);
					o->OnCollision(obj);
				}
			}
		}
		obj->Update((float)mDeltaTimeMS / 1000.0f);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Renders the game objects. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::RenderGameObjects()
{
	for (IGameObject * obj : mGameObjects)
	{
		obj->Draw();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets target FPS. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="target">	Target for the. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::SetTargetFPS(unsigned short target)
{
	mTargetDelayMS = 1000 / target;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Removes the texture described by texture. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="texture">	[in,out] If non-null, the texture. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::RemoveTexture(SDL_Texture * texture)
{
	SDL_DestroyTexture(texture);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw line. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="startPosX">	The start position x coordinate. </param>
/// <param name="startPosY">	The start position y coordinate. </param>
/// <param name="endPosX">  	The end position x coordinate. </param>
/// <param name="endPosY">  	The end position y coordinate. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::DrawLine(int startPosX, int startPosY, int endPosX, int endPosY)
{
	SDL_RenderDrawLine(mRenderer, startPosX, startPosY, endPosX, endPosY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets a color. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="color">	The color. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::SetColor(const Color & color)
{
	mColor = color;
	SDL_SetRenderDrawColor(mRenderer, mColor.r, mColor.g, mColor.b, mColor.a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw rectangle. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="startPosX">	The start position x coordinate. </param>
/// <param name="startPosY">	The start position y coordinate. </param>
/// <param name="width">		The width. </param>
/// <param name="height">   	The height. </param>
/// <param name="fill">			true to fill. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::DrawRect(int startPosX, int startPosY, int width, int height, bool fill)
{
	SDL_Rect rect = { startPosX, startPosY, width, height };

	if (fill)
	{
		SDL_RenderFillRect(mRenderer, &rect);
	}
	else
	{
		SDL_RenderDrawRect(mRenderer, &rect);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Adds a renderable. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="renderable">	[in,out] If non-null, the renderable. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::AddRenderable(IGameObject * renderable)
{
	mGameObjects.push_back(renderable);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets time since started milliseconds. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <returns>	The time since started milliseconds. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t FWApplication::GetTimeSinceStartedMS() const
{
	return mTimeMS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw text. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="message">	The message. </param>
/// <param name="offsetX">	The offset x coordinate. </param>
/// <param name="offsetY">	The offset y coordinate. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::DrawText(const std::string & message, uint32_t offsetX, uint32_t offsetY)
{
	SDL_Color color = { mColor.r, mColor.g, mColor.b, mColor.a };
	//SDL_Color bgColor = { mTextBackgroundColor.r, mTextBackgroundColor.g, mTextBackgroundColor.b, mTextBackgroundColor.a };

	SDL_Surface * surface = TTF_RenderText_Blended(mFont, message.c_str(), color);
	if (surface)
	{
		SDL_Texture * texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (texture)
		{
			DrawTexture(texture, offsetX, offsetY, surface->w, surface->h);
		}
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets font size. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="ptSize">	Size of the point. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::SetFontSize(int ptSize)
{
	mFontSize = ptSize;

	if (mFontName != "")
	{
		SetFont(mFontName);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets a font. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="filename">	Filename of the file. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::SetFont(const std::string & filename)
{
	if (mFont)
	{
		TTF_CloseFont(mFont);
	}

	mFontName = filename;
	mFont = TTF_OpenFont(GetRelativePath("Resources/" + filename).c_str(), mFontSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Quits this object. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FWApplication::Quit()
{
	mIsRunning = false;
}
