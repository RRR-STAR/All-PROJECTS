/**
 * An Arkanoid Game made using C++11 and SFML-2.4.2
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
using namespace sf;

bool startupsLoaded = false; // a global var to load the startup items only once

void loadInitialImage(Texture &image, RenderWindow &window){
    
    Sprite startupImage(image);
    startupImage.setPosition(0, 20);
    Event e;  Clock c; // vars for transition effect
    float transparency = 0.0f; // range (0 - 255)
    
    while (true){
        // update the transparency
        float dt = c.restart().asSeconds();
        if (transparency < 270.0f){ 
            transparency += 100.0f * dt;
            // means image loaded successfully and return to main pg.
            if (transparency > 270.0f){ return; }
        }
        // set this transparency to the image sprite
        Color startupImageColor = startupImage.getColor();
        startupImage.setColor(
            Color(
                startupImageColor.r, startupImageColor.g, startupImageColor.b,
                static_cast<Uint8>(transparency)
            )
        );
        window.clear();
        window.draw(startupImage);
        window.display();
    }
}


// template <typename message = String>
void gameMessage(String &&m, short int &&mszDuration, Texture &backImage, RenderWindow &window){
    
    Text txt;  Font f;  bool pgExit = false;
    f.loadFromFile("Fonts/algerian-regular.ttf");
    
    if (m == "gameOver"){ 
        txt.setString("GAME OVER !"); 
        txt.setFillColor(sf::Color::Red);
    }
    else if (m == "gameFinish"){
        txt.setString("Greetings..\n  YOU WON !"); 
        txt.setFillColor(sf::Color::Green);
        pgExit = true;
    }
    else if (m == "gamePause"){
        txt.setString("TAP < SPACE >\nTO CONTINUE ..."); 
        txt.setFillColor(sf::Color::Blue);
        txt.setFont(f);
        txt.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 45);
        window.draw(txt);
        return;
    }
    else {
        txt.setString(m); 
        txt.setFillColor(sf::Color::Yellow);
    }
    txt.setFont(f);
    txt.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 45);
    window.clear();
    window.draw(txt);
    window.display();
    sleep(seconds(mszDuration));// sleep for pause the pg. for the required time
    if (pgExit){ exit(1); };
}


int main(){
    
    // for generate random numbers in each run
    std::mt19937 randGen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<> randNo(7, 777);
    
    // first load all reqired images because if image loading failed then game not run
    // load all images into memory through textures
    Texture imageInitial, imageBall, imageBack, imagePaddle, imageColourBlocks[5];
    
    imageInitial.loadFromFile("Images/Arkanoid/startingimage.png");
    imageBack.loadFromFile("Images/Arkanoid/background.jpg");
    imageBall.loadFromFile("Images/Arkanoid/ball.png");
    imagePaddle.loadFromFile("Images/Arkanoid/paddle.png");
    imageColourBlocks[0].loadFromFile("Images/Arkanoid/blueblock.png"); // 3 block BLUE
    imageColourBlocks[1].loadFromFile("Images/Arkanoid/redblock.png"); // 1 block RED
    imageColourBlocks[2].loadFromFile("Images/Arkanoid/greenblock.png"); // 2 block GREEN
    imageColourBlocks[3].loadFromFile("Images/Arkanoid/skyblueblock.png"); // 4 block SKY-BLUE
    imageColourBlocks[4].loadFromFile("Images/Arkanoid/whiteblock.png"); // 5 block WHITE
    
    // image for the icon of the window
    Image icon;  icon.loadFromFile("Images/Arkanoid/icon.png");
    
    // a window for the game
    // the render window size must be same with the background image size
    RenderWindow gameWindow(VideoMode(imageBack.getSize().x, imageBack.getSize().y), "  Arkanoid...");
    gameWindow.setFramerateLimit(120); // set the game max. FPS
    gameWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    gameRestart : // a goto lebel to restart the game (memory safe implementation)
    try {
        // load the images into the window through sprites
        Sprite background(imageBack), ball(imageBall), paddle(imagePaddle), eachBlock;
        
        // initial position of the paddle
        paddle.setPosition(imageBack.getSize().x / 2, imageBack.getSize().y - 20);
        // ball position should be in the middle of the paddle
        // initial position of the ball
        float bx = paddle.getPosition().x + imagePaddle.getSize().x / 2;
        float by = paddle.getPosition().y - 15;
        ball.setPosition(bx, by);
        // for ball movement to X and Y axis
        float dx = 3, dy = 3; // also decides balls velocity(if value incresed, speed increased)
        
        short int totalBlocksInARow = (imageBack.getSize().x / imageColourBlocks[0].getSize().x) - 2,
        blockHeight = imageColourBlocks[0].getSize().y, 
        blockWidth = imageColourBlocks[0].getSize().x;
        
        std::vector<Sprite> blocks; // dynamic array for total no of blocks
        // set the block positions separated by 3 pixels
        for (short int i = 1, x = 0; i < totalBlocksInARow; i++){ // columns
            // float f = 0;
            for (short int j = 1, f = 0; j <= 5; j++){ // defines the no. of rows
                
                // eachBlock.setTexture(imageColourBlocks[static_cast<int>(f)]); // print each color brick 2 times
                eachBlock.setTexture(imageColourBlocks[f]);
                blocks.push_back(eachBlock);
                blocks.at(x).setPosition(i * (blockWidth + 3), j * (blockHeight + 3));
                ++x;  ++f;
            }
        }
        if (not startupsLoaded){ // ensure that image and instruction load only once
            loadInitialImage(imageInitial, gameWindow);
            gameMessage("  USE  <- | ->\n TO CONTROL\n THE PADDLE", 4, imageBack, gameWindow);
            startupsLoaded = true;
        }
        Event event;  bool gamePaused = true;
        
        while (gameWindow.isOpen()){
            while (gameWindow.pollEvent(event)){
                if (event.type == Event::Closed){
                    gameWindow.close();
                }
                if (event.type == Event::KeyPressed  &&  event.key.code == Keyboard::Space){
                    gamePaused = !(gamePaused); // for toggle the logic
                }
            }
            if (not gamePaused){ // all he game logic execute if game not paused
                /*
                we can also do "if (gamePaused){ continue; }"
                it also works same but it have problems with window re-sizing
                if we do that the window can't be resized until game resume
                */
                // bx += dx;  by += dy; // moving the ball to the X and Y axis
                
                bx += dx;
                for (short int i = 0; i < blocks.size(); i++){
                    if (FloatRect(bx+3, by+3, 3, 3).intersects(blocks.at(i).getGlobalBounds())){
                        // if the ball collide with any block
                        blocks.at(i).setPosition(-100, 0); // remove that block from the screen
                        dx = -(dx); // for reverse 90^ the ball on hitting a block
                    }
                }
                by += dy;
                for (short int i = 0; i < blocks.size(); i++){
                    if (FloatRect(bx+3, by+3, 3, 3).intersects(blocks.at(i).getGlobalBounds())){
                        // if the ball collide with any block
                        blocks.at(i).setPosition(-100, 0); // remove that block from the screen
                        dy = -(dy); // for reverse 90^ the ball on hitting a block
                    }
                }
                // bounds the ball into the window (if this bounds are not provided ball doesn't seen on the screen 
                // because it goes out of bound like block(-100, 0) or some value)
                if (bx < 0  or  bx > imageBack.getSize().x){ dx = (-dx); } 
                if (by < 0){ dy = (-dy); }
                // if (by < 0 or by > imageBack.getSize().y){ dy = (-dy); }
                
                if (by > imageBack.getSize().y + 15){ // game Over logic
                    gameMessage("gameOver", 2, imageBack, gameWindow);
                    throw "RESTART THE GAME";
                }
                // game Finish logic
                bool gameFinish = true;
                for (auto &eachBlock : blocks){ 
                    if (eachBlock.getPosition().x != -100){ gameFinish = false; }
                }
                if (gameFinish){ gameMessage("gameFinish", 4, imageBack, gameWindow); }
                
                // paddle movement and paddle bounds - in left
                if (Keyboard::isKeyPressed(Keyboard::Left)  and  paddle.getPosition().x > 0){
                    paddle.move(-7, 0);
                }
                // right side paddle movement and bound - in right
                if (Keyboard::isKeyPressed(Keyboard::Right)  and  paddle.getPosition().x + paddle.getGlobalBounds().width < imageBack.getSize().x){
                    paddle.move(7, 0);
                }
                if (FloatRect(bx+3, by+3, 6, 6).intersects(paddle.getGlobalBounds())){
                    dy = -(randNo(randGen) % 5 + 2); // when the ball hits the paddle change ball speed randomly
                }
            }
            gameWindow.clear();
            gameWindow.draw(background); // default position is (0, 0)
            ball.setPosition(bx, by); // move the ball in each frame
            gameWindow.draw(ball);
            gameWindow.draw(paddle);
            for (auto &eachBlock : blocks){ gameWindow.draw(eachBlock); } // display all the blocks
            // if game paused then draw the mesage
            if (gamePaused){ gameMessage("gamePause", 0, imageBack, gameWindow); }
            gameWindow.display();
            
        }
    }
    catch (...){
        /*
        When control(pg. flow) reches here it means,
        all the objects get destroyed automatically and we can simply restart the pg.
        with no memory leaks
        */
        goto gameRestart;
    }
}