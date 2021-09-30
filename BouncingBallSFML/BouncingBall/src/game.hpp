#ifndef GAME_H
#define GAME_H


#include "ball.hpp"


/* Main Game Class*/
class Game
{
	private:
		sf::RenderWindow* window; // sfml window
		sf::Event event; // sfml event 
		sf::Texture bgtexture, balltexture, dark_theme_texture, backbuttontexture, playbuttontexture, logotexture, tiletexture, ballicontexture, animt[6]; // textures
		sf::Sprite background, darktheme, backbutton, playbutton, logo, tile, ballicon[2], anim[6]; // sprites
		sf::RectangleShape floor, wall1, wall2; // rectangleshapes
		sf::Font font, font2; //fonts
		sf::Text COUNTER, lose; //text
		sf::Vector2i mouseposition; // mouseposition vector

		Ball ball; // ball

		std::string jc; //jump(score) counter converted from int
		unsigned int frame_counter = 0, actual_frame = 0; 
		unsigned int shift = 25; // informs about amount of pixels needed to shift the COUNTER (to stay in the center of the window)
		bool game_started = false; // ntc
		bool game_lost = false;	// informs about ball's fall

		/* Initialization */
		void initTextures(void); 
		void initSprites(void);
		void initFont(void);

	public:
		/* Constructor / Destructor */
		Game(void);
		~Game(void);

		/* Functions */
		void run(void);

		//Menu State
		void renderMenuState(void);
		void updateMenuState(void);
		void hangleMenuStateEvents(void);

		//Game State
		void renderGameState(void);
		void updateGameState(void);
		void handleGameStateEvents(void);

		//Lost Game State
		void renderLostState(void);
		void updateLostState(void);
		void handleLostStateEvents(void);

		//return true if cursor is covering the button, false otherwise
		bool buttonCover(const sf::Sprite& button, int radius, const sf::Vector2i& mouseposition, const std::string& buttontype);
};

#endif