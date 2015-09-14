#pragma once

#include <functional>
#include <cstdint>
#include <vector>

class IGameObject;
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;
//struct SDL_Event;

//#define SDL_DRAW_PUTPIXEL_BPP(A, B, C)  \
//*(A(B(Uint8*)super->pixels + (y0+y)*super->pitch +               \
//                                          (x0+x)*SDL_DRAW_BPP)) = C; \
//*(A(B(Uint8*)super->pixels + (y0-y)*super->pitch +               \
//                                          (x0+x)*SDL_DRAW_BPP)) = C; \
//*(A(B(Uint8*)super->pixels + (y0+y)*super->pitch +               \
//                                          (x0-x)*SDL_DRAW_BPP)) = C; \
//*(A(B(Uint8*)super->pixels + (y0-y)*super->pitch +               \
//                                          (x0-x)*SDL_DRAW_BPP)) = C;
//
//
//#define SDL_DRAW_PUTPIXEL \
//  SDL_DRAW_PUTPIXEL_BPP(0+,1+,colorbyte1)   \
//  if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {   \
//    SDL_DRAW_PUTPIXEL_BPP(0+,0+,colorbyte2)   \
//    SDL_DRAW_PUTPIXEL_BPP(0+,2+,colorbyte0) \
//          }else{                                   \
//    SDL_DRAW_PUTPIXEL_BPP(0+,0+,colorbyte0)   \
//    SDL_DRAW_PUTPIXEL_BPP(0+,2+,colorbyte2) \
//          }

struct Color
{
	uint32_t r, g, b, a;

	Color() {}
	Color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) : r(red), g(green), b(blue), a(alpha) { }
};


class FWApplication
{
public:


	FWApplication(int offsetX = 50, int offsetY = 50, int width = 1200, int height = 600);
	~FWApplication();

	void SetTargetFPS(unsigned short target);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the window. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <returns>	The SDL window. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	SDL_Window * GetWindow() const;
	static FWApplication * GetInstance();

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is the game running, returns false when window is closed. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <returns>	true if running, false if not. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool IsRunning();


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Returns a relative path at the binary location </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="path">	(Optional) full pathname of the file. </param>
	///
	/// <returns>	The relative path. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string GetRelativePath(const std::string & path = "") const;


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads a texture and returns it's pointer. Note you have to cleanup yourself </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="fileName">	Filename of the file. </param>
	///
	/// <returns>	null if it fails, else the texture. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	SDL_Texture * LoadTexture(const std::string & fileName);



	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draw a texture to the screen at a given position </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="texture">	[in,out] If non-null, the texture. </param>
	/// <param name="xOffset">	The offset. </param>
	/// <param name="yOffset">	The offset. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawTexture(SDL_Texture * texture, int xOffset, int yOffset);


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draw a texture to the screen at a given position </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="texture">	[in,out] If non-null, the texture. </param>
	/// <param name="xOffset">	The offset. </param>
	/// <param name="yOffset">	The offset. </param>
	/// <param name="width">  	The width. </param>
	/// <param name="height"> 	The height. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawTexture(SDL_Texture * texture, int xOffset, int yOffset, int width, int height);
	


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draws a line from position to position </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="startPosX">	The start position x coordinate. </param>
	/// <param name="startPosY">	The start position y coordinate. </param>
	/// <param name="endPosX">  	The end position x coordinate. </param>
	/// <param name="endPosY">  	The end position y coordinate. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY);


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draws a rect from start position to end position </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="startPosX">	The start position x coordinate. </param>
	/// <param name="startPosY">	The start position y coordinate. </param>
	/// <param name="width">		The width. </param>
	/// <param name="height">   	The height. </param>
	/// <param name="fill">			true to fill. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawRect(int startPosX, int startPosY, int width, int height, bool fill);


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draws text on the screen at a given location </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="message">	The message. </param>
	/// <param name="offsetX">	The offset x coordinate. </param>
	/// <param name="offsetY">	The offset y coordinate. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawText(const std::string & message, uint32_t offsetX, uint32_t offsetY);



	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Start of the cycle, catches input, etc. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void StartTick();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	End of the cycle, swaps buffers </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void EndTick();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destroy a texture resource, and frees memory </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="texture">	[in,out] If non-null, the texture. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void RemoveTexture(SDL_Texture * texture);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Set the color (as a state), all future draws are done with this color. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="color">	The color. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetColor(const Color & color);


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the font as a state, all future font rendering is done with this font. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="fileName">	Filename of the file. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetFont(const std::string & fileName);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the fontsize as a state, all future font rendering is done in this size. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="ptSize">	Size of the point. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetFontSize(int ptSize);



	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Add a renderable object, update and render will be called when ticks are handled by the application. </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	///
	/// <param name="renderable">	[in,out] If non-null, the renderable. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void AddRenderable(IGameObject * renderable);

	uint32_t GetTimeSinceStartedMS() const;


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates all gameObjects </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void UpdateGameObjects();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Renders all gameObjects </summary>
	///
	/// <remarks>	Joris, 21-10-2014. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void RenderGameObjects();
	void Quit();
	//void AddOnEvent(std::function<void(SDL_Event*)> func);

private:
	std::vector<IGameObject *> mGameObjects;
	static FWApplication * mInstance;

	SDL_Window * mWindow;
	SDL_Renderer * mRenderer;

	uint32_t mTimeMS;
	uint32_t mTargetDelayMS;
	uint32_t mStartCycleTimeMS;
	uint32_t mDeltaTimeMS; // The actual loop cycle time

	bool mIsRunning;

	Color mColor;
	//Color mTextBackgroundColor;
	TTF_Font * mFont;
	std::string mFontName;
	uint32_t mFontSize;
	//uint32_t mColor;

};

