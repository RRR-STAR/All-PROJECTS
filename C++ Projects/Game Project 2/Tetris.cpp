/**
 * Tetris Game using C++11 and SFML-2.4.2
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

bool startUpsLoaded = false, initialMessagePrinted = false; // a global var to share messages between functions

void loadInitialImage(sf::Texture &image, sf::RenderWindow &window){
    
    sf::Sprite startupImage(image);
    startupImage.setPosition(0, 0);
    sf::Event e;  sf::Clock c; // vars for transition effect
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


// this func used to fet the current  and highest score of the player
std::string getGameScore(std::string &&scoreType){
    
    std::ifstream fileToRead("TetrisScore.txt", std::ios::in);
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
    
    std::ofstream fileToWrite("TetrisScore.txt");
    fileToWrite << std::string(curScore) << "\n" << std::string(highScore);
    fileToWrite.close();
}


void gameMessage(sf::String &&m, short int &&mszDuration, sf::Texture &backImage, sf::RenderWindow &window){
    using namespace sf;
    
    Text txt;  Font f;  bool pgExit = false;
    f.loadFromFile("Fonts/cambria-math.ttf");
    
    if (m == "gameOver"){ 
        txt.setString("GAME OVER !"); 
        txt.setFillColor(Color::Red);
    }
    else if (m == "gameFinish"){
        txt.setString(" Greetings...\n -- YOU WIN !"); 
        txt.setFillColor(Color::Green);
        pgExit = true;
    }
    else if (m == "gameNewScore"){
        txt.setString("HIGH SCORE !"); 
        txt.setFillColor(Color::Green);
    }
    else if (m == "gamePause"){
        txt.setString("TAP < SPACE >\nTO CONTINUE ..."); 
        txt.setFillColor(Color::Yellow);
        txt.setFont(f);
        txt.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 45);
        window.draw(txt);
        return;
    }
    else if (m == "gameScore"){
        txt.setString(" Score : " + std::to_string(mszDuration));
        txt.setFillColor(Color::Blue);
        txt.setFont(f);
        txt.setPosition(backImage.getSize().x / 2 - 110, backImage.getSize().y / 2 + 170);
        window.draw(txt);
        return;
    }
    else if (m == "gameInitialMessage"){
        txt.setString(" NEW GAME \n"); 
        txt.setFont(f);
        Text txt2("SCORE BOARD ", f);
        txt.setFillColor(Color::Yellow);
        txt2.setFillColor(Color::Yellow);
        txt.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 75);
        txt2.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 15);
        
        // LOGIC FOR MOUSE HOVERING AND TAPPING
        // get the positions of mouse and texts
        Vector2i mousePosInWindow = Mouse::getPosition(window);
        Vector2f mousePos = window.mapPixelToCoords(mousePosInWindow);
        FloatRect txt1Pos = txt.getGlobalBounds();
        FloatRect txt2Pos = txt2.getGlobalBounds();
        
        // checks that if the mouse cursor pos is on the text
        if (txt1Pos.contains(mousePos)){
            txt.setFillColor(Color::Cyan); // on hover color change
            
            // by doing this the game will start executing
            if (Mouse::isButtonPressed(Mouse::Button::Left)){ initialMessagePrinted = true; }
        }
        else if (txt2Pos.contains(mousePos)){
            txt2.setFillColor(Color::Cyan);
            
            // by doing this the score board will be shown
            if (Mouse::isButtonPressed(Mouse::Button::Left)){
                String message =
                    " LastScore: " + getGameScore("CurrentScore")
                    + "\n\n" + 
                    " HighScore: " + getGameScore("HighestScore")
                ;
                gameMessage(std::move(message), 3, backImage, window);
            }
            
        }
        else { // return to previous color when mouse cursor is not hovered
            txt.setFillColor(Color::Yellow);  
            txt2.setFillColor(Color::Yellow);
            
            // or if Enter key is pressed then also the game starts
            if (Keyboard::isKeyPressed(Keyboard::Return)){ initialMessagePrinted = true; }
        }
        // ----- draw the initial texts -----
        window.draw(txt);   window.draw(txt2);
        return;
    }
    else { // for default strings
        txt.setString(m); 
        txt.setFillColor(Color::Yellow);
    }
    txt.setFont(f);
    txt.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 45);
    window.clear();
    window.draw(txt);
    window.display();
    sleep(seconds(mszDuration));// sleep to pause the pg. for the required time
    if (pgExit){ exit(EXIT_FAILURE); };
}


// This function is use to check that the tiles(pieces) location is in the game window or not
constexpr bool anyTilesCoordinateGoOutofWindow(auto &tiles, auto &gameGrid){
    for (auto &anyTile : tiles){
        
        // for check out of bound for tiles
        if (anyTile.x < 0  or  anyTile.x >= 10  or  anyTile.y >= 20){
            return true;
        }
        // for check collision (overlapping with an existing block)
        if (gameGrid[anyTile.y][anyTile.x]){ 
            return true; // enters if the grid position is non-zero
        }
    }
    return false;
}


main(){
    using namespace sf;
    /*
    *        0     1
    *     -------------   this is for understanding purpose
    *     |     |     |   
    *  0  |  0  |  1  |   ---------- it represents the figures or shapes ----------
    *     |     |     |   where the mentioned blocks are filled with some colors
    *     -------------   and the blocks which are not mentioned are not filled with colors
    *     |     |     |   therefore 1,3,5,7 or 0,2,4,6 represents a single line colored shape(I-shape)
    *  1  |  2  |  3  |   and in the same way 0,1,2,3 or 2,3,4,5 or 4,5,6,7 represents a square shape     
    *     |     |     |   and 0,2,3,5 or 2,4,5,7 represents a Z-type shape
    *     -------------   and 1,2,3,5 or 3,4,5,7 represents a T-type shape
    *     |     |     |   and 0,2,4,5 or 2,4,6,7 represents a L-typr shape
    *  2  |  4  |  5  |   and 1,3,5,7 or 3,5,7,6 represents a J-type shape
    *     |     |     |   
    *     -------------   
    *     |     |     |   
    *  3  |  6  |  7  |   
    *     |     |     |   
    *     -------------   
    */
    // this is for creating shapes
    constexpr std::array<std::array<int, 4>, 7> shapes = {
        1, 3, 5, 7,     // I shape
        2, 4, 5, 7,     // Z shape
        3, 5, 4, 6,     // S shape
        3, 5, 4, 7,     // T shape
        2, 4, 6, 7,     // L shape
        3, 5, 7, 6,     // J shape
        4, 5, 6, 7,     // O shape
    };
    
    // load the images and icons in textures first
    Image icon;  icon.loadFromFile("Images/Tetris/icon2.png");
    Texture imgStarting, imgBack, imgTiles, imgFrame;
    imgStarting.loadFromFile("Images/Tetris/startingimage.png");
    imgBack.loadFromFile("Images/Tetris/background.png");
    imgTiles.loadFromFile("Images/Tetris/tiles.png");
    imgFrame.loadFromFile("Images/Tetris/frame.png");
    
    // create the game window
    RenderWindow window(VideoMode(imgBack.getSize().x, imgBack.getSize().y), "Tetris...");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    View windowView = window.getDefaultView(); // to handle the window resizing
    
    gameRestart : // label for the goto statement(memory safe implementation)
    try {
        // reset the flag because when game will restarted
        initialMessagePrinted = false;
        
        // represents a grid inside the game where the shapes are placed
        // gameGrid.size()       -->  no of rows in gameGrid 2D array
        // gameGrid.at().size()  -->  no of cols in gameGrid 2D array
        std::array<std::array<int, 10>, 20> gameGrid = {0}; // default all elem '0' 
        
        // a 2x4 grid shape that's why pair array of 4
        // which describe at previously with diagram
        struct coordinates { int x, y; };
        std::array<coordinates, 4>  points = {0}, copyP = {0};
        
        bool  gamePause = false, tileRotate = false;
        unsigned int playersScore = 0, tileColorNo = 1, dx = 0; // dx : tile movement in X axis
        
        float timer = 0.0, delay = 0.5, copyofDelay = delay; // for speed mechanishm
        Clock timerClock;
        
        Sprite background(imgBack), tiles(imgTiles), frame(imgFrame);
        tiles.setTextureRect(IntRect(0, 0, 18, 18)); // each tile is 18px
        
        ////////////////////////// @c FOR-SELECTING-THE-INITIAL-SHAPE //////////////////////////
        
        // select the row randomly which selects the shape randomly & (i % 7) for in bound ranges
        short int n = rand() % 7;
        short int i = 0;
        
        // [[ 2x4 ]] grid matrix coordinates automatically created from the shapes by using the formula,
        // which represents previously in the diagram
        // arr[i][j] / 2 = elem row number
        // arr[i][j] % 2 = elem col number
        for (auto &eachPoint : points){
            eachPoint.x = shapes[n][i] % 2; // provides col no.
            eachPoint.y = shapes[n][i] / 2; // provides row no.
            ++i;
        }
        
        //////////////////////////// @c GAME-LOOPING-STARTS ////////////////////////////
        
        Event e;
        while (window.isOpen()){
            while (window.pollEvent(e)){
                
                if (e.type == Event::Closed){ window.close(); }
                if (e.type == Event::LostFocus){ gamePause = true; }
                if (e.type == Event::GainedFocus){ gamePause = false; }
                if (e.type == Event::KeyPressed){
                    
                    if (e.key.code == Keyboard::Space){ gamePause = !(gamePause); }
                    if (e.key.code == Keyboard::Up){ tileRotate = true; }  // rotate tiles
                    if (e.key.code == Keyboard::Left){ dx = -1; }          // move tiles left
                    if (e.key.code == Keyboard::Right){ dx = 1; }          // move tiles right
                    // if (e.key.code == Keyboard::Down){ delay = 0.1; }   // move tiles down faster
                }
                if (e.type == Event::Resized){
                    window.setSize(Vector2u(imgBack.getSize().x * 2, imgBack.getSize().y * 2));
                    windowView = window.getView(); // get the current view for clickable texts
                    window.setView(windowView);    // set the current view to remain the logic as it is
                }
            }
            if (not startUpsLoaded){
                // ensure that image and instruction load only once
                loadInitialImage(imgStarting, window);
                gameMessage("Instructions...",                              2, imgBack, window);
                gameMessage("1. Arrow  ^ \n    To Rotate\n    The Shapes",  2, imgBack, window);
                gameMessage("2. Arrow <|>\n    for Tiles\n    Movement", 2, imgBack, window);
                gameMessage("4. [SPACE]  \n    To Pause \n    The Game",    2, imgBack, window);
                startUpsLoaded = true;
            }
            if (not gamePause and initialMessagePrinted){
                timer += timerClock.restart().asSeconds();  // game speed increases as it played
                
                ////////////////////////// @c FOR-MOVE-THE-TILES /////////////////////////////
                
                copyP = points; // store a back-up for-if tiles go out-of-range
                
                for (auto &eachPoint : points){ eachPoint.x += dx; } // move the tiles
                // if the new moved position of tiles is invalid then revert the poistions of tiles
                if (anyTilesCoordinateGoOutofWindow(points, gameGrid)){ points = copyP; }
                
                ////////////////////////// @c FOR-ROTATE-THE-TILES /////////////////////////////
                
                if (tileRotate){
                    // poivot tile which is the center of rotation and not change it's position
                    coordinates pivotTile = points[1]; 
                    for (auto &eachPoint : points){
                        
                        int tempX = eachPoint.x - pivotTile.x;  // calculate relative horizontal position
                        int tempY = eachPoint.y - pivotTile.y;  // calculate relative vertical position
                        // perform rotation 90 degree clockwise
                        eachPoint.x = pivotTile.x - tempY;      // inverts vertical to horizontal  
                        eachPoint.y = pivotTile.y + tempX;      // use the horizontal as new vertical
                    }
                    // if new rotation coordinates are invalid then revert the positions
                    if (anyTilesCoordinateGoOutofWindow(points, gameGrid)){ points = copyP; }
                }
                
                ////////////////////////// @c MOVE-TILES-DOWN-AND-CREATE-NEW-SHAPES //////////////////////////
                
                if (timer >= delay){
                    copyP = points;                                     // store back-up of positions
                    for (auto &eachPoint : points){ eachPoint.y += 1; } // move the tile down with one step
                    
                    if (anyTilesCoordinateGoOutofWindow(points, gameGrid)){
                        // when the tile can't move furthur down, it will be locked in the game grid
                        // where ever the tile is drop in the game grid, 
                        // that block's value in game grid will be replaced by the tile colour no.
                        /*
                        Grid Row 16 :   [0,0,0,0,0,0,0,0,0]   before any |   [0,0,0,0,0,0,0,0,0] 
                        Grid Row 17 :   [0,0,0,0,0,0,0,0,0]   tile  place|   [2,0,0,0,0,0,0,0,0] -> I shape
                        Grid Row 18 :   [0,0,0,0,0,0,0,0,0]   -----------    [2,0,0,0,0,0,3,0,0] -> L shape
                        Grid Row 19 :   [0,0,0,0,0,0,0,0,0]   |after any     [2,0,0,1,0,0,3,0,0] -> T shape reverse
                        Grid Row 20 :   [0,0,0,0,0,0,0,0,0]   |tile place    [2,0,1,1,1,0,3,3,0]
                        */
                        // used copy of point bcz points co-ordinates become invalid 
                        for (auto &eachPoint : copyP){ gameGrid[eachPoint.y][eachPoint.x] = tileColorNo; }
                        
                        tileColorNo = 1 + (rand() % 7); // random colors of tiles
                        n = rand() % 7;  i = 0;         // random shapes of tiles
                        
                        for (auto &eachPoint : points){         // for creating new shapes durng gameplay
                            eachPoint.x = shapes[n][i] % 2;     // provides col no.
                            eachPoint.y = shapes[n][i] / 2;     // provides row no.
                            ++i;
                        }
                        // if the newly created piece overloaps(cross) the game grid
                        // [ GAME-OVER LOGIC ]
                        if (anyTilesCoordinateGoOutofWindow(points, gameGrid)){ 
                            " ----------- Game over, restart the Game ------------ ";
                            gameMessage("gameOver", 2, imgBack, window);
                            // throw the obtained score by the player
                            throw  playersScore;
                        }
                    }
                    timer = 0; // for reset after each 1 step drop
                    // otherwise the tile drops immidiately at the bottom and game over logic executed unconditionally
                }
                
                /////////////////////////////////// @c CHECK-LINES ////////////////////////////////////
                
                // start checking the game grid in a reverse order( from the bottom )
                for (short int i = gameGrid.size() - 1, k = i;  i > 0;  i--){
                    
                    short int nonEmptyBlocks = 0; // count the non-empty blocks
                    for (auto &anyBlock : gameGrid[i]){ if (anyBlock != 0){ ++nonEmptyBlocks; } }
                    /*
                    * now the full lines logic are checked in a beautiful and efficient way
                    * if (row is not full) : 
                    *       copy done in one by one means, no change in rows just copy as it is
                    *       { row(k) } = { row(i) } where, [k == i] 
                    *       constant flow because (--k),(--i)
                    * but if (row is full with non empty blocks) : 
                    *       copy done, no change in row
                    *       still [k == i], but now after this iteration [k != i] because only (--i)
                    *       so when in next iteration, { row(k) } = { row(i) } here, [k == i-1]
                    *       hence, the row which is full is just substitute by it's just upper row and,
                    *       from here all current rows are substitute by it's upper rows [currentRow(k) = upperRow(i - 1)]
                    */
                    gameGrid[k] = gameGrid[i]; // whole row copy
                    
                    if (nonEmptyBlocks < gameGrid.at(i).size()){ --k; }
                    else { // nonEmptyBlocks == gameGrid.at(i).size()
                        ++playersScore; // if a line cleared then users Score should be a plus
                        
                        // after clearing each and every step the game speed increases
                        delay -= 0.02; // less value speed more
                        
                        // after a particular score, player won the game
                        if (playersScore >= 99){ throw "Game Finish"; }
                    }
                }
                
                //////////////////////////// @c RESET-VALUES-FOR-TICK-DROP /////////////////////////////
                
                // reset all the flags in each iteration, so that tiles can be moved or rotate in every iteration
                // otherwise the tiles moved from one corner to another in just one click and also automatically rotated 
                dx = 0;  tileRotate = false;
                if (delay <= 0){ delay = copyofDelay; } // reset the delay if reach 0
            }
            
            ////////////////////////////////// @c WINDOW-DRAW /////////////////////////////////
            
            window.clear();
            window.draw(background); // print background first otherwise it overlaps the tiles
            
            for (auto &eachPoint : points){
                // change the color of tiles according to the tile color no
                tiles.setTextureRect(IntRect(tileColorNo * 18, 0, 18, 18));
                tiles.setPosition(eachPoint.x * 18, eachPoint.y * 18);
                tiles.move(28, 30); // for move the tiles to the right while moving
                window.draw(tiles);
            }
            // display the game grid with placed tiles
            for (short int i = 0; i < gameGrid.size(); ++i){
                for (short int j = 0; j < gameGrid.at(i).size(); ++j){
                    
                    if (gameGrid[i][j] == 0){ continue; } // means grid block is still not occoupied by any tile
                    tiles.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                    tiles.setPosition(j * 18, i * 18);
                    tiles.move(28, 32); // move tiles 'X','Y' axis after tile placed
                    window.draw(tiles);
                }
            }
            window.draw(frame); // print the frame after tiles placed so that tiles doesn't overlaps the frame
            
            // game initial message and hold the game
            if (not initialMessagePrinted){ gameMessage("gameInitialMessage", 0, imgBack, window); }
            else { // when game starts then print the score update it in real time
                gameMessage("gameScore", playersScore, imgBack, window); 
            }
            // game pause message
            if (gamePause and  initialMessagePrinted){ gameMessage("gamePause", 0, imgBack, window); }
            
            window.display();
        }
    }
    catch (unsigned int curScore){
        /*
        When control(pg. flow) reches here it means,
        all the objects get destroyed automatically and we can simply restart the pg.
        with no memory leaks
        */
        unsigned int highScore = std::stoi(getGameScore("HighestScore"));
        
        // if current score is greater than the existing high score then, update both the scores
        if (curScore >= highScore){ 
            gameMessage("gameNewScore", 1, imgBack, window);
            setGameScores(std::to_string(curScore), std::to_string(curScore)); 
        }
        else { // otherwise only update the current score
            setGameScores(std::to_string(curScore), std::to_string(highScore)); 
        }
        
        goto gameRestart; // then restart the game
    }
    catch (const char *){ // if player cross score 99 then game finish
        gameMessage("gameFinish", 3, imgBack, window);
    }
    return 0;
}

