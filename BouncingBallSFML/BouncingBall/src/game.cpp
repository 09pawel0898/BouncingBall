#include "game.hpp"

void Game::initTextures(void)
{
    /* loading all essential textures and setting smooth*/
    this->bgtexture.loadFromFile("img/bgpattern.png"); this->bgtexture.setSmooth(true);
    this->balltexture.loadFromFile("img/ball.png"); this->balltexture.setSmooth(true);
    this->dark_theme_texture.loadFromFile("img/opacity_cover2.png");
    this->backbuttontexture.loadFromFile("img/buttonback.png"); this->backbuttontexture.setSmooth(true);
    this->playbuttontexture.loadFromFile("img/playbutton.png"); this->playbuttontexture.setSmooth(true);
    this->logotexture.loadFromFile("img/logoball.png"); this->logotexture.setSmooth(true);
    this->tiletexture.loadFromFile("img/tile.png"); this->tiletexture.setSmooth(true);
    this->ballicontexture.loadFromFile("img/ballicon.png"); this->ballicontexture.setSmooth(true);

    /* loading the transition animation frames*/
    for (unsigned int i = 0; i < 6; i++)
    {
        std::string type, path;
        type = std::to_string(i + 1);
        path = "img/" + type + ".png";
        //std::cout << path << std::endl;
        this->animt[i].loadFromFile(path);
        this->animt[i].setSmooth(true);
    }
}

void Game::initSprites(void)
{
    /* setting up sprites' textures, initial positions, scales etc */
    this->background.setTexture(this->bgtexture);
    this->ball.setTexture(this->balltexture); this->ball.setPosition(sf::Vector2f(this->window->getSize().x/2.0f, 150)); this->ball.setOrigin(43, 43);
    this->darktheme.setTexture(this->dark_theme_texture);
    this->backbutton.setTexture(this->backbuttontexture); this->backbutton.setOrigin(48, 48); this->backbutton.setScale(0.6f, 0.6f); this->backbutton.setPosition(400, 50);
    this->playbutton.setTexture(this->playbuttontexture);  this-> playbutton.setOrigin(150 / 2.0f, 150 / 2.0f); this->playbutton.setPosition(window->getSize().x / 2.0f, 420);
    this->logo.setTexture(this->logotexture); this->logo.setPosition(25, 5); this->logo.setScale(0.9f, 0.9f);
    this->tile.setTexture(this->tiletexture); this->tile.setPosition(0, 600);
    this->floor = sf::RectangleShape(sf:: Vector2f(450, 2)); this->floor.setPosition(0, 598);
    this->wall1 = sf::RectangleShape(sf::Vector2f(2, 600)); this->wall1.setPosition(0, 0);
    this->wall2 = sf::RectangleShape(sf::Vector2f(2, 600)); this->wall2.setPosition(448, 0);

    for (unsigned int i = 0; i < 2; i++)
    {
        this->ballicon[i].setTexture(this->ballicontexture); 
        this->ballicon[i].setOrigin(42, 42); 
        this->ballicon[i].setScale(0.5f, 0.5f);
    }
    for (unsigned int i = 0; i < 6; i++)
        anim[i].setTexture(animt[i]);
 
}

void Game::initFont(void)
{
    /* fonts and text type initialization */
    this->font.loadFromFile("font/OpenSans-Bold.ttf");
    this->font2.loadFromFile("font/OpenSans-Regular.ttf");
    this->lose.setFont(this->font2); this->lose.setCharacterSize(30); this->lose.setFillColor(sf::Color(255, 255, 255)); this->lose.setString("Restart"); this->lose.setPosition(this->window->getSize().x / 2.0f - 52, 605);
    this->COUNTER.setFont(font); this->COUNTER.setCharacterSize(80); this->COUNTER.setFillColor(sf::Color(56, 47, 123));
}


Game::Game(void)
{
    /* creating window and calling init functions */
	this->window = new sf::RenderWindow(sf::VideoMode(450, 600), "Bouncing ball");
    this->window->setFramerateLimit(120);
    this->initTextures();
    this->initSprites();
    this->initFont();
}

Game::~Game(void)
{
	delete this->window;
}

void Game::run(void)
{
    /* main application loop */
	while(this->window->isOpen())
	{
        /* menu state when game is not started yet or has been canceled(back button was pressed) */
        if (!this->game_started)
        {
            this->updateMenuState();
            this->renderMenuState();
        }
        else
        {
            /* frame counter >= 6 because of letting show the transition animation in the first 6 frames :) and lasts till the game_losts turns true */
            if (frame_counter >= 6 && !this->game_lost)
            {
                this->updateGameState();
                this->renderGameState();
            }
            else if (this->game_lost) /* when ball fall down, the lost game state is active*/
            {
                this->updateLostState();
                this->renderLostState();
            }
            else /* here i reserved the first 6 frames for the animation to show */
            {
                this->window->clear();
                this->window->draw(this->background);
                this->window->draw(this->anim[this->frame_counter]);
                this->window->display();
            }
            /* every loop frame incrementation */
            this->frame_counter++;
        }
	}
}

/*renders entities in menu state*/
void Game::renderMenuState(void)
{
    this->window->clear();
    this->window->draw(this->background);
    this->window->draw(this->floor);
    this->window->draw(this->darktheme);
    this->window->draw(this->logo);
    this->window->draw(this->playbutton);
    this->window->display();
}

/*renders entities in game state*/
void Game::renderGameState(void)
{
    this->window->clear();

    this->window->draw(this->background);
    this->window->draw(this->COUNTER);
    this->window->draw(this->ball);
    this->window->draw(this->floor);
    this->window->draw(this->backbutton);

    this->window->display();
}

/*renders entities in lost game state*/
void Game::renderLostState(void)
{
    this->window->clear();
    this->window->draw(this->background);
    this->window->draw(this->COUNTER);
    this->window->draw(this->floor);
    this->window->draw(this->tile);
    this->window->draw(this->lose);
    this->window->draw(this->ballicon[0]);
    this->window->draw(this->ballicon[1]);
    this->window->draw(this->backbutton);
    this->window->display();
}

/* menu state update*/
void Game::updateMenuState(void)
{
    this->mouseposition = sf::Mouse::getPosition(*window);
    
    /* checking for events*/
    this->hangleMenuStateEvents();

    /* zooming in and out the button icon after covering by cursor*/
    if (buttonCover(this->playbutton, 72, this->mouseposition, "circle"))
        this->playbutton.setScale(0.89f, 0.89f);
    else 
        this->playbutton.setScale(0.8f, 0.8f);
}

/* game state update*/
void Game::updateGameState(void)
{

    this->mouseposition = sf::Mouse::getPosition(*window);

    /* checking for events*/
    this->handleGameStateEvents();

    /* zooming in and out the button icon after covering by cursor*/
    if (this->buttonCover(this->backbutton, 30, this->mouseposition, "circle"))
        this->backbutton.setScale(0.64f, 0.64f);
    else
        this->backbutton.setScale(0.55f, 0.55f);
    
    if (this->ball.is_jumping && (actual_frame == frame_counter - 30))
        this->ball.is_jumping = false;
    
    /* converts integer counter to string*/
    this->jc = std::to_string(this->ball.jump_counter);
    
    /* setting up shift accordingly to the lenght of the string*/
    if (this->jc.size() == 1)
        this->shift = 25;
    else if (this->jc.size() > 1)
    {
        if (this->jc.size() == 2)
            this->shift = 47;
        else this->shift = 69;
    }

    /* if the ball occurs below the bottom line of the window the game is lost */
    if (this->ball.getPosition().y - 1000 > this->window->getSize().y)
        this->game_lost = true;

    /* updating the counter */
    this->COUNTER.setPosition(this->window->getSize().x / 2.0f - this->shift, 138);
    this->COUNTER.setString(this->jc);
    
    /* updating the ball */
    this->ball.update(this->floor, this->wall1, this->wall2);

}

/* lost game state update*/
void Game::updateLostState(void)
{
    this->mouseposition = sf::Mouse::getPosition(*window);

    /* checking for events*/
    this->handleLostStateEvents();

    /* checking for buttons cover */
    if (this->buttonCover(this->tile, 72, this->mouseposition, "rectangle") && this->tile.getPosition().y == 400)
    {
        this->ballicon[0].setPosition(130, 427);
        this->ballicon[1].setPosition(320, 427);
        this->ballicon[0].rotate(1);
        this->ballicon[1].rotate(-1);
    }
    else
    {
        this->ballicon[0].setPosition(700, 700);
        this->ballicon[1].setPosition(700, 700);
    }
    if (this->buttonCover(this->backbutton, 30, this->mouseposition, "circle"))
    {
        this->backbutton.setScale(0.64f, 0.64f);

    }
    else
        this->backbutton.setScale(0.55f, 0.55f);

    /* moving tile 10px every frame to the final position and creating nice animation this way*/
    if (this->tile.getPosition().y > 400)
    {
        this->tile.move(0, -10);
        this->lose.move(0, -10);
    }
}

/* checks for events in menu state */
void Game::hangleMenuStateEvents(void)
{
	while (this->window->pollEvent(this->event))
	{
        /* window closed */
		if (this->event.type == sf::Event::Closed) this->window->close(); 

        /* start button clicked */
        if (this->buttonCover(this->playbutton, 72, this->mouseposition, "circle") && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->game_started = true;
            this->frame_counter = 0;
        }
	}
}

/* checks for events in game state */
void Game::handleGameStateEvents(void)
{
	while (this->window->pollEvent(this->event))
	{
        /* window closed */
		if (this->event.type == sf::Event::Closed)
            this->window->close();

        /* clicked on ball */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (this->ball.checkIfOnClicked(this->ball, this->mouseposition)))
        {
            if (!this->ball.is_jumping)
            {
                this->ball.jump_counter++;
                this->ball.jump();
                this->actual_frame = this->frame_counter;
                this->ball.is_jumping = true;
            }
        }

        /* back to menu button click */
        if (this->buttonCover(this->backbutton, 48, this->mouseposition, "circle") && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->game_lost = false;
            this->ball.reset();
            this->ball.jump_counter = 0;
            this->tile.setPosition(0, 600);
            this->lose.setPosition(this->window->getSize().x / 2.0f - 52, 605);
            this->game_started = false;
        }
        /* reset ball under space key*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            this->ball.reset();
            this->ball.jump_counter = 0;
        }
	}
}

/* checks for events in game lost state */
void Game::handleLostStateEvents(void)
{
	while (this->window->pollEvent(this->event))
	{
        /* window closed */
		if (this->event.type == sf::Event::Closed) this->window->close();

        /* onclick on reset game or back to the menu button*/
        if ((this->buttonCover(this->tile, 72, this->mouseposition, "rectangle") || this->buttonCover(this->backbutton, 48, this->mouseposition, "circle"))&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            /* same actions for both */
            this->game_lost = false;
            this->ball.reset();
            this->ball.jump_counter = 0;
            this->tile.setPosition(0, 600);
            this->lose.setPosition(this->window->getSize().x / 2.0f - 52, 605);
            /* except this one, when the back menu button was chosen, game_started needs to be set to false*/
            if (this->buttonCover(this->backbutton, 48, this->mouseposition, "circle"))
                this->game_started = false;
        }
	}
}



bool Game::buttonCover(const sf::Sprite& button, int radius, const sf::Vector2i& mouseposition, const std::string& buttontype)
{
    double mx, my, bx, by;
    mx = mouseposition.x;
    my = mouseposition.y;
    bx = button.getPosition().x;
    by = button.getPosition().y;

    if (buttontype == "circle")  // if the type of button is equal to "circle" 
    {

        double d = 0; //distance between the cursor and the center of the button 
        double X, Y;

        X = abs(bx - mx);
        Y = abs(by - my);
        d = sqrt(X * X + Y * Y);
        if (d > radius)
            return false;
        if (d <= radius)
            return true;
    }
    else if (buttontype == "rectangle")  // if rectangle represents the button
    {
        if (my > by && my < by + 54)
            return true;
        else
            return false;
    }
    return false;
}