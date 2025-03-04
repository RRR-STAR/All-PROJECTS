

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <memory>
#include <random>
#include <vector>
#include <cmath>
#include <list>


namespace Asteroid { 
    
    sf::Texture imgBack;
    short int fireType = 1, ith_background = 0;
    bool inHomePage = true, spaceshipBoost = false;
    constexpr auto DEG_TO_RAD = 0.017453F;
    
    // for generate random number
    std::mt19937 randGen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<> randNo(0, 1000);
    void loadInitialImage(sf::Texture &, sf::RenderWindow &);
    void gameMessage(sf::String &&, short int, sf::RenderWindow &);
    std::string getGameScore(std::string &&);
    void setGameScores(std::string &&, std::string &&);
    
    
    /////////////////////////////// @c ANIMATION-CLASS //////////////////////////////
    
    
    class Animation { // use to create animation for the objects
        
        private : 
        
        short int curFrame;  float frameRate;
        std::vector<sf::IntRect> frames; // this just stores the cords of frames
        sf::Sprite sprite;               // to display the frame on screen
        /*
        imgTobeAnimate : image which contains different view frames in a linear row
        cordX, cordY   : the inital co-ordinates for the frames
        frameW, frameH : each frame size
        frameCount     : total how many frames possible in the image
        frameRate      : determines the speed of frame changing
        */
        public : 
        
        Animation(sf::Texture &imgTobeAnimate, int cordX, int cordY, 
                int frameW, int frameH, int frameCount, float frameSpeed) noexcept {
            
            curFrame = 0;           // start from the first most frame
            frameRate = frameSpeed; // set the frame changing speed
            
            for (short int i = 0; i < frameCount; ++i){
                frames.push_back(sf::IntRect(cordX + i*frameW, cordY, frameW, frameH));
                // cordX + frameW * i = goto the next frame(frame cordX = frame size * frame no.)
            }
            sprite.setTexture(imgTobeAnimate);
            sprite.setOrigin(frameW / 2, frameH / 2); // set orgin for smooth rotations for rotable objects
            sprite.setTextureRect(frames[0]);         // set the initial frame to the sprite obj
        }
        Animation() noexcept { curFrame = frameRate = 0; }
        ~Animation() noexcept {}
        
        void update(){
            curFrame += frameRate; // increment the frames in timely manner
            // if the current frame reach to the last then restart
            if (curFrame >= frames.size()){ curFrame -= frames.size(); }
            // set the currrent frame to the sprite obj 
            if (frames.size() > 0){ sprite.setTextureRect(frames[curFrame]); }
        }
        // checks if the animations is over or not
        // if the current frame reached the last frame then animation over
        inline bool isEnd(){ return (curFrame + frameRate  >=  frames.size()); }
        inline sf::Sprite& getSprite(){ return sprite; }
    };
    
    
    //////////////////////////////////// @c GAME-OBJECTS //////////////////////////////////
    
    
    class GameObject { // a base class for all movable game objects
        friend void Main();
        friend bool isCollided(const std::shared_ptr<GameObject>&, const std::shared_ptr<GameObject>&);
        
        protected : 
        
        bool life;
        sf::String name;
        float x, y, dx, dy, angle, R;
        Animation animation;
        /*
        name         : a particular name that defines the object
        life         : that defines the object is collided and alive or not
        x , y        : current co-ordinates of the object
        dx , dy      : future co-ordinates of the object
        angle        : a angle in which direction the object is moving
        animation    : to define the animations of the objects
        R            : a optional value for visualizing collisions
        */
        GameObject(sf::String &&objName) noexcept { 
            name = objName;  life = true;  x = y = dx = dy = angle = R = 0.0F; 
        }
        public : 
        
        virtual ~GameObject() noexcept {};
        virtual void update(){};
        
        void settings(Animation &anim, int X, int Y, float degree = 1, int radious = 0){
            animation = anim;  x = X;  y = Y;  angle = degree;  R = radious;
        }
        void draw(sf::RenderWindow &window){    // draw the obj to the window
            this->animation.getSprite().setPosition(x, y);
            this->animation.getSprite().setRotation(angle + 90.0F);
            window.draw(animation.getSprite()); // draw a particular frame to the window
            
            sf::CircleShape circle(R);
            circle.setPosition(x, y);
            circle.setOrigin(R, R);
            // ------ optional part for debugging collison detections -------
            // circle.setFillColor(sf::Color::Cyan);
            // window.draw(circle);
        }
    };
    
    
    ////////////////////////////////// @c SPACESHIP-CLASS //////////////////////////////////
    
    
    class SpaceShip : public GameObject {
        
        public  :
        
        SpaceShip() noexcept : GameObject("spaceship"){}
        ~SpaceShip() noexcept {}
        
        void update(){
            if (spaceshipBoost){ // if user boosted the ship by up-arraow then increase speed
                dx += std::cos(angle * DEG_TO_RAD) * 0.2F;
                dy += std::sin(angle * DEG_TO_RAD) * 0.2F;
            }
            else { dx *= 0.99F;  dy *= 0.99F; } // otherwise decrease the speed gradually
            
            // prevent the ship speed to become too much fast
            float maxSpeed = 5.0F, speed = std::sqrt(dx * dx  +  dy * dy);
            if (speed > maxSpeed){ dx *= maxSpeed / speed;  dy *= maxSpeed / speed; }
            
            x += dx;  y += dy;
            
            // screen wrapping 
            // if the ship moves off one side of the screen then it reappears on other side
            if (x < 0.0F){ x = imgBack.getSize().x; }
            if (y < 0.0F){ y = imgBack.getSize().y; }
            if (x > imgBack.getSize().x){ x = 0.0F; }
            if (y > imgBack.getSize().y){ y = 0.0F; }
        }
    };
    
    
    ////////////////////////////////// @c BULLET-CLASS //////////////////////////////////
    
    
    class Bullet : public GameObject {
        
        public : 
        
        Bullet() noexcept : GameObject("bullet"){}
        ~Bullet() noexcept {}
        
        void update(){
            dx += std::cos(angle * DEG_TO_RAD) * 1.0F; // calculate the velocity horizontal
            dy += std::sin(angle * DEG_TO_RAD) * 1.0F; // calculate the velocity vertically
            x += dx;   y += dy;                        // updae to the actual co-ordinates
            // change the fire types but not effect the single fire type 
            if (fireType == 2  and  R == 11){ angle += randNo(randGen) % 7 - 3; }
            if (fireType == 3  and  R == 11){ angle += randNo(randGen); }
            // if go out of bound then remove that bullet obj
            if (x < 0  or  x > imgBack.getSize().x){ life = false; }
            if (y < 0  or  y > imgBack.getSize().y){ life = false; }
        }
    };
    
    
    ////////////////////////////////// @c ASTEROID-CLASS //////////////////////////////////
    
    
    class Asteroid : public GameObject {
        
        public :
        
        Asteroid() noexcept : GameObject("asteroid"){ 
            dx = randNo(randGen) % 3; // spawn a asteroid with random values
            dy = randNo(randGen) % 3; // (%5) to limit the asteroids movement speed
        }
        ~Asteroid() noexcept {}
        
        void update(){
            x += dx;   y += dy; // update the actual co-ordinates
            // screen wrapping (same like the spaceship)
            if (x < 0.0F){ x = imgBack.getSize().x; }
            if (y < 0.0F){ y = imgBack.getSize().y; }
            if (x > imgBack.getSize().x){ x = 0.0F; }
            if (y > imgBack.getSize().y){ y = 0.0F; }
        }
    };
    
    
    ////////////////////////////////// @c EXPLOSION-CLASS //////////////////////////////////
    
    
    class Explosion : public GameObject {  public :
        
        Explosion() noexcept : GameObject("explosion"){}
        ~Explosion() noexcept {}
    };
    
    
    ////////////////////////////////// @c COLLISION-DETECTION-FUNCTION //////////////////////////////////
    
    
    bool isCollided(const std::shared_ptr<GameObject> &obj1, const std::shared_ptr<GameObject> &obj2){
        
        // collision check between two objs using maths ---circle distance formula---
        auto distanceSquareX = (obj1->x - obj2->x) * (obj1->x - obj2->x);
        auto distanceSquareY = (obj1->y - obj2->y) * (obj1->y - obj2->y);
        auto distanceSquareR = (obj1->R + obj2->R) * (obj1->R + obj2->R); // R -> radious
        
        return (distanceSquareX + distanceSquareY  <  distanceSquareR);
    }
    
    
    void Main(){
        using namespace sf;
        
        Image       icon;  
        Texture     imgStartUp, imgBack2, imgBack3, imgBack4, imgSpaceship, imgSpaceshipBoost, imgBlueFire, imgRedFire, 
                    imgBigAsteroids, imgSmallAsteroids, imgExplosion1, imgExplosion2, imgExplosion3, imgHealth;
        SoundBuffer explosion1SBuffer, shipBoostSBuffer, singleFireSBuffer, specialFireSBuffer1, specialFireSBuffer2;
        
        imgStartUp.loadFromFile         ("Images/Asteroid/startupimage.png");
        icon.loadFromFile               ("Images/Asteroid/icon.png");
        imgBack.loadFromFile            ("Images/Asteroid/background.jpg");
        imgBack2.loadFromFile           ("Images/Asteroid/background2.jpg");
        imgBack3.loadFromFile           ("Images/Asteroid/background3.jpg");
        imgBack4.loadFromFile           ("Images/Asteroid/background4.jpg");
        imgSpaceship.loadFromFile       ("Images/Asteroid/spaceship2.png");
        imgSpaceshipBoost.loadFromFile  ("Images/Asteroid/spaceship2_.png");
        imgBlueFire.loadFromFile        ("Images/Asteroid/bluefire.png");
        imgRedFire.loadFromFile         ("Images/Asteroid/redfire.png");
        imgBigAsteroids.loadFromFile    ("Images/Asteroid/bigrocks.png");
        imgSmallAsteroids.loadFromFile  ("Images/Asteroid/smallrocks.png");
        imgExplosion1.loadFromFile      ("Images/Asteroid/explosion1.png");
        imgExplosion2.loadFromFile      ("Images/Asteroid/explosion2.png");
        imgExplosion3.loadFromFile      ("Images/Asteroid/explosion3.png");
        imgHealth.loadFromFile          ("Images/Asteroid/heartimage.png");
        explosion1SBuffer.loadFromFile  ("Sounds/Asteroid/explosionsound1.wav");
        shipBoostSBuffer.loadFromFile   ("Sounds/Asteroid/thrustsound.wav");
        singleFireSBuffer.loadFromFile  ("Sounds/Asteroid/weaponsound3.wav");
        specialFireSBuffer1.loadFromFile("Sounds/Asteroid/weaponsound1.wav");
        specialFireSBuffer2.loadFromFile("Sounds/Asteroid/weaponsound2.wav");
        
        imgBack.setSmooth     (true);    imgBack2.setSmooth(true);
        imgBack3.setSmooth    (true);    imgBack4.setSmooth(true);
        imgSpaceship.setSmooth(true);
        
        // ------------------- creating the main game window -------------------
        RenderWindow window(VideoMode(imgBack.getSize().x, imgBack.getSize().y), "Asteroid !...");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        window.setFramerateLimit(120);
        loadInitialImage(imgStartUp, window); // load the initial image for the game
        
        std::array<Sprite, 4>       background;
        background[0].setTexture    (imgBack);
        background[1].setTexture    (imgBack2);
        background[2].setTexture    (imgBack3);
        background[3].setTexture    (imgBack4);
        Sprite playerHealth         (imgHealth);
        
        Animation spaceShipAnim     (imgSpaceship,      0, 0,  45,  50,  1, 1);
        Animation spaceShipBoostAnim(imgSpaceshipBoost, 0, 0,  45,  70,  1, 1);
        Animation blueBulletAnim    (imgBlueFire,       0, 0,  32,  64, 16, 1);
        Animation redBulletAnim     (imgRedFire,        0, 0,  32,  64, 16, 0);
        Animation bigAsteroidAnim   (imgBigAsteroids,   0, 0,  64,  64, 16, 0);
        Animation smallAsteroidAnim (imgSmallAsteroids, 0, 0,  64,  64, 16, 0);
        Animation explosionAnim_1   (imgExplosion1,     0, 0,  50,  50, 20, 1);
        Animation explosionAnim_2   (imgExplosion2,     0, 0, 192, 192, 64, 1);
        Animation explosionAnim_3   (imgExplosion3,     0, 0, 256, 256, 48, 1);
        
        Sound explosionSound1  (explosion1SBuffer);
        Sound shipBoostSound   (shipBoostSBuffer);
        Sound singleFireSound  (singleFireSBuffer);
        Sound specialFireSound1(specialFireSBuffer1);
        Sound specialFireSound2(specialFireSBuffer2);
        
        singleFireSound.setPitch  (2.0F);    singleFireSound.setVolume  (10.0F);
        specialFireSound1.setPitch(2.0F);    specialFireSound1.setVolume(10.0F);
        specialFireSound2.setPitch(2.0F);    specialFireSound2.setVolume(10.0F);
        shipBoostSound.setPitch   (2.0F);    shipBoostSound.setVolume   (12.5F);
        
        // std::list<GameObject*> gameObjs;
        std::list<std::shared_ptr<GameObject>> gameObjs;
        
        // GameObject *spaceshipObj = new SpaceShip(); // space ship obj
        std::shared_ptr<GameObject> spaceshipObj = std::make_shared<SpaceShip>();
        spaceshipObj->settings(spaceShipAnim, 400, 400, 0, 20);
        gameObjs.push_back(spaceshipObj);
        
        ///////////////////////////////// @c MAIN-LOOP /////////////////////////////////
        
        // if the players high score not set, then it means player plays the game for the first time
        bool gamePause = false, startUpInstructionsLoaded = (getGameScore("HighestScore")=="0")? false:true;
        short int playerHealthCount = 5,  playerScore = 0, waveLength = 0, waveNo = 0;
        Clock inputClock, fireClock, fireHoldClock;                            // timer clocks for hold inputs and 
        bool inputBlocked = false, continiousFireOn = false, holdFire = false; // flags for timers
        
        Event e;
        while (window.isOpen()){
            while (window.pollEvent(e)){
                if (e.type == Event::Closed){ window.close(); }
                if (e.type == Event::LostFocus){ gamePause = true; }
                if (e.type == Event::GainedFocus){ gamePause = false; }
                
                
                ////////////////////////// @c DIFFERENT-TYPE-BULLET-SHOOT-LOGIC /////////////////////////
                
                
                if (e.type == Event::KeyPressed){
                    if (e.key.code == Keyboard::Space  and  not inputBlocked){ 
                        
                        // create a new single bullet obj on space key input
                        std::shared_ptr<GameObject> bulletObj = std::make_shared<Bullet>();
                        bulletObj->settings(blueBulletAnim, spaceshipObj->x, spaceshipObj->y, spaceshipObj->angle, 10);
                        gameObjs.push_back(bulletObj);
                        // play the single bullet fire sound
                        // only play the sound if it is not the sound is currently playing 
                        // (it actually maintain the sound effect properly)
                        if (singleFireSound.getStatus() != Sound::Playing){ singleFireSound.play(); }
                        else { singleFireSound.stop(); }
                    }
                    // changes the fire type upon keyboard down key press
                    else if (e.key.code == Keyboard::Down){ ++fireType;  if (fireType >= 4) fireType = 1; }
                    
                    else if (e.key.code == Keyboard::LShift  and  not continiousFireOn){
                        fireClock.restart();  continiousFireOn = true; // shift hold for continious fire
                    }
                }
                if (e.type == Event::KeyReleased){ // shift released continious fire off
                    if (e.key.code == Keyboard::LShift){ continiousFireOn = false; }
                }
            }
            if (not startUpInstructionsLoaded){
                gameMessage("gameInstructions", 20, window);  startUpInstructionsLoaded = true;
            }
            "----------------------------------- start game logic and calculations ---------------------------------";
            
            if (not gamePause  and  not inHomePage){
                
                if (not inputBlocked  and  continiousFireOn  and  not holdFire){ 
                    
                    // create a new continious bullet obj
                    std::shared_ptr<GameObject> bulletObj = std::make_shared<Bullet>();
                    bulletObj->settings((fireType == 1)? blueBulletAnim : redBulletAnim, 
                                        spaceshipObj->x, spaceshipObj->y, spaceshipObj->angle, 11);
                    gameObjs.push_back(bulletObj);
                    
                    switch (fireType){ // play the continious fire sound based on the fire type
                        case 1 :    if (specialFireSound1.getStatus() != Sound::Playing){ 
                                        specialFireSound1.play(); 
                                    } break;
                        case 2 :    if (specialFireSound2.getStatus() != Sound::Playing){ 
                                        specialFireSound2.play(); 
                                    } break;
                        case 3 :    if (specialFireSound2.getStatus() != Sound::Playing){ 
                                        specialFireSound2.play(); 
                                    } break;
                    }
                    // continue the continious fire upto 3 seonds then block it for recharge
                    if (fireClock.getElapsedTime() >= seconds(3)){ 
                        holdFire = true;  fireHoldClock.restart(); 
                    }
                }
                else { // restart the continious fire after recharged for 10 seconds
                    if (fireHoldClock.getElapsedTime() >= seconds(10)){ holdFire = false; }
                }
                
                /////////////////////////// @c SHIP-MOVEMENT-LOGIC //////////////////////////
                
                
                if (not inputBlocked  and  Keyboard::isKeyPressed(Keyboard::Right)){ spaceshipObj->angle += 2.9F; }
                if (not inputBlocked  and  Keyboard::isKeyPressed(Keyboard::Left)){  spaceshipObj->angle -= 2.9F; }
                // cahnging the space ship image based on enable/disable boost of the space ship
                if (not inputBlocked  and  Keyboard::isKeyPressed(Keyboard::Up)){ 
                    spaceshipBoost = true;  
                    spaceshipObj->animation = spaceShipBoostAnim;
                    // play the spaceship boost sound
                    if (shipBoostSound.getStatus() != Sound::Playing){ shipBoostSound.play(); }
                }
                else { spaceshipBoost = false;  spaceshipObj->animation = spaceShipAnim;  shipBoostSound.stop(); }
                
                
                ///////////////////////// @c COLLISION-DETECTION-LOGIC-AND-INPUT-HOLD ////////////////////////
                
                
                for (auto &obj1 : gameObjs){
                    for (auto &obj2 : gameObjs){
                        
                        if (obj1->name == "bullet"  and  obj2->name == "asteroid"){
                            if ( isCollided(obj1, obj2) ){
                                
                                obj1->life = obj2->life = false; 
                                // if R = 10, means it is already a small asteroid, so not break it furthur
                                if (obj2->R != 10){ // this refer to big asteroids
                                    obj2->name = "break_this_asteroid"; 
                                    ++playerScore; // increment the if only a big asteroid destroyed
                                }
                                // create a explosion effect based on the asteroid type
                                std::shared_ptr<GameObject> explosionObj = std::make_shared<Explosion>();
                                explosionObj->settings((obj2->R == 10)? explosionAnim_1 : explosionAnim_2, obj2->x, obj2->y);
                                gameObjs.push_back(explosionObj);
                            }
                        }
                        else if (obj1->name == "spaceship"  and  obj2->name == "asteroid"){
                            if ( isCollided(obj1, obj2) ){
                                
                                // upon collision between player and asteroid
                                obj2->life = false;       --playerHealthCount; 
                                // create a different explosion effect for the spaceship colliding
                                std::shared_ptr<GameObject> explosionObj = std::make_shared<Explosion>();
                                explosionObj->settings(explosionAnim_3, obj1->x, obj1->y);
                                gameObjs.push_back(explosionObj);
                                
                                // play the sound when  player collided with an  asteroid
                                if (explosionSound1.getStatus() != Sound::Playing){ explosionSound1.play(); }
                                else { explosionSound1.stop(); }
                                
                                // block the ship movements after the collsion for some times by holding keyboard inputs
                                inputBlocked = true;  inputClock.restart();
                                spaceshipObj->dx = spaceshipObj->dy = 0;
                                
                                "------------------ Game Over Logic -----------------";
                                if (playerHealthCount <= 0){ 
                                    gameMessage("gameOver", 2, window);  
                                    if (playerScore > std::stoi(getGameScore("HighestScore"))){
                                        gameMessage("gameHighScore", 2, window);  
                                    }
                                    throw playerScore;
                                }
                            }
                        }
                    }
                }
                // released the input flag and again allow keyboard inputs after holding for 1/2 seconds
                if (inputBlocked  and  inputClock.getElapsedTime() >= seconds(0.5)){ inputBlocked = false; }
                
                
                ////// @c REMOVE-THE-EXPLOSION-OBJ'S-AFTER-ANIMATION,-AND-SPAWN-NEW-SMALL-ASTEROIDS ///////
                
                
                for (auto &obj : gameObjs){
                    if (obj->name == "explosion"){
                        if (obj->animation.isEnd()){ obj->life = false; }
                    }
                    if (obj->name == "break_this_asteroid"){
                        for (short int i = 0; i < 4; ++i){
                            std::shared_ptr<GameObject> smallAsteroidObj = std::make_shared<Asteroid>();
                            smallAsteroidObj->settings(smallAsteroidAnim, obj->x, obj->y, randNo(randGen)%360, 10);
                            gameObjs.push_back(smallAsteroidObj);
                        }
                    }
                }
                
                ///////////////////////// @c ALL-OBJECTS-UPDATE-LOGIC-FOR-EACH-FRAME ////////////////////////
                
                
                // update the game objects one by one and remove if not needed
                for (auto it = gameObjs.begin(); it != gameObjs.end(); ){
                    auto eachObj = *it;
                    
                    eachObj->update();
                    eachObj->animation.update();
                    // erase current and points to the next element
                    if (not eachObj->life){ it = gameObjs.erase(it); }
                    else { ++it; } // manually increment the iterator, if obj life is true
                }
                
                //////////////////////////// @c CREATE-A-NEW-WAVE /////////////////////////
                
                
                // create asteroid objects randomly based on wave format
                if (gameObjs.size() == 1){ // when only one obj is left which is spaceship
                    waveLength += 5;       // increase the wave length whenever player clears a wave successfully
                    waveNo++;              // track the wave no.
                    
                    // draw the background so that the window can be cleared.
                    window.clear();  window.draw(background[ith_background]);
                    gameMessage("gameWave", waveNo, window);
                    
                    for (short int i = 0; i < waveLength; ++i){
                        std::shared_ptr<GameObject> bigAsteroidObj = std::make_shared<Asteroid>();
                        bigAsteroidObj->settings(bigAsteroidAnim, randNo(randGen) % imgBack.getSize().x, 
                                                randNo(randGen) % imgBack.getSize().y, randNo(randGen) % 360, 20);
                        gameObjs.push_back(bigAsteroidObj);
                    }
                }
            }
            
            //////////////////////////// @c WINDOW-DRAW /////////////////////////
            
            
            window.clear(); 
            window.draw(background[ith_background]); // draw the the chosen background
            if (inHomePage){ gameMessage("gameHomePage", 0, window); }
            else { 
                for (auto &obj : gameObjs){ obj->draw(window); }            // draw game objs
                gameMessage("gameScore", playerScore, window);              // draw score
                
                for (short int i = 0; i < playerHealthCount; ++i){             // draw health
                    playerHealth.setPosition(1050 + i*imgHealth.getSize().x, 20);
                    window.draw(playerHealth);
                }
                if (holdFire){                                                 // draw hold fire msz if recharging
                    short int rechargingCounter = static_cast<int>(fireHoldClock.getElapsedTime().asSeconds());
                    gameMessage("gameFireRecharge", (9 - rechargingCounter), window);
                }
            }
            window.display();
        }
        
    }
    
    
    void loadInitialImage(sf::Texture &image, sf::RenderWindow &window){
        
        sf::Sprite startupImage(image);
        startupImage.setPosition(0, 0);
        sf::Event e;  sf::Clock c; // vars for transition effect
        float transparency = 0.0F; // range (0 - 255)
        
        while (true){
            // update the transparency
            float dt = c.restart().asSeconds();
            if (transparency < 270.0F){ 
                transparency += 75.0F * dt;
                // means image loaded successfully and return to main pg.
                if (transparency > 270.0F){ return; }
            }
            // set this transparency to the image sprite
            sf::Color startupImageColor = startupImage.getColor();
            startupImage.setColor(
                sf::Color(
                    startupImageColor.r, startupImageColor.g, startupImageColor.b,
                    static_cast<sf::Uint8>(transparency)
                )
            );
            window.clear();
            window.draw(startupImage);
            window.display();
        }
    }
    
    
    void gameMessage(sf::String &&m, short int mszDuration, sf::RenderWindow &window){
        using namespace sf;
        
        Text txt;  Font f1,f2;
        f1.loadFromFile("Fonts/algerian-regular.ttf");
        f2.loadFromFile("Fonts/cambria-math.ttf");
        
        if (m == "gameInstructions"){
            txt.setString("\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Instructions .....\n\
                \n\n\t\t\t\t\t\t\t\t\t\t\t(These are one time instructions so read it carefully)\
                \n\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t 1. UP-ARROW to move forward.\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t 2. LEFT-ARROW to rotate left.\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t 3. RIGHT-ARROW to rotate right.\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t 4. SPACE to fire single bullet.\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t 5. LEFT-SHIFT hold for special fire.\
                \n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t 6. DOWN-ARROW to change special fire type.\
            ");
            txt.setFillColor(Color::Yellow);  
            txt.setPosition(0, 0);
            txt.setFont(f2);  
            window.clear();
        }
        else if (m == "gameHomePage"){
            Text txt1(" NEW GAME \n",      f1);
            Text txt2("SCORE BOARD",       f1);
            Text txt3("Change Background", f2);
            
            txt1.setFillColor(Color::Cyan);
            txt2.setFillColor(Color::Cyan);
            txt3.setFillColor(Color::Cyan);
            txt1.setPosition(imgBack.getSize().x / 2 - 90,                imgBack.getSize().y / 2 - 60);
            txt2.setPosition(imgBack.getSize().x / 2 - 95,                imgBack.getSize().y / 2 -  0);
            txt3.setPosition(imgBack.getSize().x / 2 - 125/*155 for f1*/, imgBack.getSize().y / 2 + 60);
            
            // LOGIC FOR MOUSE HOVERING AND TAPPING
            // get the positions of mouse and texts
            Vector2i mousePosInWindow = Mouse::getPosition(window);
            Vector2f mousePos = window.mapPixelToCoords(mousePosInWindow);
            FloatRect txt1Pos = txt1.getGlobalBounds();
            FloatRect txt2Pos = txt2.getGlobalBounds();
            FloatRect txt3Pos = txt3.getGlobalBounds();
            
            if (txt1Pos.contains(mousePos)){       // checks that if the mouse cursor pos is on the text
                txt1.setFillColor(Color::Magenta); // on hover color change
                // by doing this the game will move from the home page to the playing page
                if (Mouse::isButtonPressed(Mouse::Left)){ inHomePage = false; }
            }
            else if (txt2Pos.contains(mousePos)){
                txt2.setFillColor(Color::Magenta);
                // by doing this the score board will be shown
                if (Mouse::isButtonPressed(Mouse::Left)){
                    String message= " Last Score : " + getGameScore("CurrentScore")
                                    + "\n\n" + 
                                    " High Score : " + getGameScore("HighestScore");
                    gameMessage(std::move(message), 3, window);
                }
            }
            else if (txt3Pos.contains(mousePos)){
                txt3.setFillColor(Color::Magenta);
                // by doing this background picture will be switched between different themes
                if (Mouse::isButtonPressed(Mouse::Left)){ 
                    ++ith_background;  if (ith_background >= 4){ ith_background = 0; }  
                    sleep(seconds(0.3)); // sleep for small amount of time to take effects for changes
                }
            }
            else { // return to previous color when mouse cursor is not hovered
                txt1.setFillColor (Color::Cyan);
                txt2.setFillColor(Color::Cyan);
                txt3.setFillColor(Color::Cyan);
                // also the game starts based on the enter key pressed
                if (Keyboard::isKeyPressed(Keyboard::Return)){ inHomePage = false; }
            }
            // ----- draw the home page texts -----
            window.draw(txt1);  window.draw(txt2);  window.draw(txt3);
            return;
        }
        else if (m == "gameOver"){ 
            txt.setString("GAME OVER !"); 
            txt.setFont(f1);
            txt.setFillColor(Color::Red);
            txt.setPosition(imgBack.getSize().x / 2 - 80, imgBack.getSize().y / 2 - 45);
            window.clear();
        }
        else if (m == "gameHighScore"){ 
            txt.setString("HIGH SCORE !"); 
            txt.setFont(f1);
            txt.setFillColor(Color::Green);
            txt.setPosition(imgBack.getSize().x / 2 - 80, imgBack.getSize().y / 2 - 45);
            window.clear();
        }
        else if (m == "gameScore"){
            txt.setString(" Score : " + std::to_string(mszDuration));
            txt.setFont(f1);
            txt.setPosition(1080, 50);
            txt.setFillColor(Color::Cyan);
            window.draw(txt);
            return;
        }
        else if (m == "gameWave"){
            txt.setString(" Wave : " + std::to_string(mszDuration));
            txt.setFont(f1);
            txt.setCharacterSize(60);
            txt.setFillColor(Color::Cyan);
            txt.setPosition(imgBack.getSize().x / 2 - 125, imgBack.getSize().y / 2 - 45);
            mszDuration = 2;
        }
        else if (m == "gameFireRecharge"){
            txt.setString("Special Fire Recharging... " + std::to_string(mszDuration));
            txt.setFont(f2);
            txt.setPosition(10, 10);
            txt.setCharacterSize(20);
            txt.setFillColor(Color::Cyan);
            window.draw(txt);
            return;
        }
        else { // for default strings
            txt.setString(m); 
            txt.setFillColor(Color::Yellow);
            txt.setFont(f2);
            txt.setPosition(imgBack.getSize().x / 2 - 110, imgBack.getSize().y / 2 - 60);
            window.clear();
        }
        window.draw(txt);  window.display();
        sleep(seconds(mszDuration)); // sleep to pause the pg. and display the message
    }
    
    
    // this func used to get the current or highest score of the player
    std::string getGameScore(std::string &&scoreType){
        
        std::ifstream fileToRead("AsteroidScore.txt", std::ios::in);
        if (not fileToRead){ return std::string("0"); } // if file opens fails then return 0 as score
        
        std::string curScore, highScore;  
        std::getline(fileToRead, curScore);  // 1 Line: last played score
        std::getline(fileToRead, highScore); // 2 Line: highest score
        fileToRead.close();
        
        if (scoreType == "CurrentScore"){ return curScore; }
        else if (scoreType == "HighestScore"){ return highScore;  }
        else { return std::string("0"); }
    }
    // this func is used to set the current or highest score of the player
    void setGameScores(std::string &&curScore, std::string &&highScore){
        
        std::ofstream fileToWrite("AsteroidScore.txt");
        fileToWrite << std::string(curScore) <<"\n"<< std::string(highScore);
        fileToWrite.close();
    }
}


main(){
    try { 
        Asteroid::Main(); 
    }
    catch (short int score){ // score catches correctly
        unsigned short int highScore = std::stoi(Asteroid::getGameScore("HighestScore"));
        // if current score is greater than the existing high score then, update both the scores
        if (score >= highScore){ 
            Asteroid::setGameScores(std::to_string(score), std::to_string(score)); 
        }
        else { // otherwise only update the current score
            Asteroid::setGameScores(std::to_string(score), std::to_string(highScore)); 
        }
    }
    return 0;
}
