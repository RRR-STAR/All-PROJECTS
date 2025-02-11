
/**
 * A game like candy crush made using C++11 & SFML-2.4.2
*/

#include <SFML/Graphics.hpp>
#include <random>
#include <fstream>

class piece {  
    private : 
    sf::FloatRect pieceGlobalBounds;
    
    public : 
    short int x, y, row, col, type, match, alpha;
    /*
     * (x, y)     : pixel position of the gems
     * (row, col) : logical position in the grid
     * (type)     : the type of the tile
     * (match)    : track that the gem is a any part of a match
     * (alpha)    : for transparency effect on the gems
     */
    piece() noexcept { // default values
        x = y = row = col = type = -1;
        match = false;  alpha = 255;
    } 
    virtual ~piece() noexcept {}
    
    void setGlobalBounds(sf::FloatRect gemGlobalBound){ // pass by value for copy
        pieceGlobalBounds = gemGlobalBound; 
    }
    sf::FloatRect& getGlobalBounds(){ return pieceGlobalBounds; }
};


constexpr void swapGems(piece, piece, auto &);
void loadInitialImage(sf::Texture &, sf::RenderWindow &);
std::string getGameScore(std::string &&);
void setGameScores(std::string &&curScore, std::string &&);
void gameMessage(sf::String &&, short int &&, sf::Texture &, sf::RenderWindow &);
bool initialMessagePrinted = false;


main(){
    using namespace sf;
    
    // for generate random numbers in each run
    std::mt19937 randGen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<> randNo(7, 777);
    
    // load all the images from files into textures
    Texture imgStarting, imgBack, imgCursor, imgGems;    Image icon;
    imgStarting.loadFromFile("Images/Match-3-Gems/startupimage.png");
    imgBack.loadFromFile("Images/Match-3-Gems/background.png");
    imgCursor.loadFromFile("Images/Match-3-Gems/cursor.png");
    imgGems.loadFromFile("Images/Match-3-Gems/gems.png");
    icon.loadFromFile("Images/Match-3-Gems/icon.png");
    
    RenderWindow window(VideoMode(imgBack.getSize().x, imgBack.getSize().y), "Match Gems 3...");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // explicitly mentioned the frame rate so that the window resized doesn't effect the animations
    window.setFramerateLimit(120);
    
    unsigned short int playersScore = 0;
    
    try {
        
        short int oneGemSize = 54; // determines each tile size in width
        std::array<std::array<piece, 8>, 8> gameGrid; // represents the game grid 
        
        // initialize the game grid with random gems
        // we can use the modern for-each based loop but ,
        // here we nedd the indecies for calculateion
        for (short int row = 0; row < gameGrid.size(); ++row){
            for (short int col = 0; col < gameGrid[row].size(); ++col){
                
                gameGrid[row][col].type = randNo(randGen) % 7;
                gameGrid[row][col].row  = row;
                gameGrid[row][col].col  = col;
                gameGrid[row][col].y    = row * oneGemSize;
                gameGrid[row][col].x    = col * oneGemSize;
            }
        }
        
        bool isSwapping = false, isMoving = false, gamePause = false;
        short int g1row, g1col, g2row, g2col, gemClickCount = 0;
        g1row = g1col = g2row = g2col = -1; 
        piece clickedGem;
        Sprite background(imgBack), gems(imgGems), cursor(imgCursor);
        Event e;
        
        // load the game initial image first the start the game
        loadInitialImage(imgStarting, window);
        
        ////////////////////////// @c GAME-LOOPING-STARTS //////////////////////////
        
        while (window.isOpen()){
            while (window.pollEvent(e)){
                if (e.type == Event::Closed){ window.close(); }
                if (e.type == Event::LostFocus){ gamePause = true; }
                if (e.type == Event::GainedFocus){ gamePause = false; }
            }
            
            ////////////////////////////// @c MOUSE-CLICK-LOGIC ///////////////////////////
            
            if (initialMessagePrinted  and  not gamePause){
                
                if (Mouse::isButtonPressed(Mouse::Left)  &&  not isSwapping  &&  not isMoving){
                    
                    Vector2i mousePosInWindow = Mouse::getPosition(window);
                    Vector2f mousePos = window.mapPixelToCoords(mousePosInWindow);
                    
                    for (auto &eachBlock : gameGrid){
                        for (auto &eachPiece : eachBlock){
                            
                            // mouse clicks on the pieces are captured here
                            if (eachPiece.getGlobalBounds().contains(mousePos)){
                                gemClickCount++;
                                clickedGem = eachPiece;
                                
                                // set the cursor image on any clicked gem
                                cursor.setPosition(eachPiece.x + 47, eachPiece.y + 25);
                            }
                        }
                    }
                    
                }
                
                ////////////////////////////// @c SWAPPING-LOGIC-ON-CLICK ///////////////////////////
                
                // ----------- [+1] for to not start from array index --------
                // ----------- with [0] adjancecy check can't be done --------
                if (gemClickCount == 1){
                    g1row = (clickedGem.y / oneGemSize) + 1; // gives: (row no. + 1) for first gem
                    g1col = (clickedGem.x / oneGemSize) + 1; 
                }
                else if (gemClickCount == 2){
                    g2row = (clickedGem.y / oneGemSize) + 1;
                    g2col = (clickedGem.x / oneGemSize) + 1; // gives: (col no. + 1) for second gem
                    
                    // adjacency check (the gems are just besides with each other or not: 'vertically'/'hotrizontally')
                    if ((abs(g1row - g2row) == 1 && g1col == g2col) or (g1row == g2row && abs(g1col - g2col) == 1)){
                        
                        // [-1] for again get the actual array index
                        swapGems(gameGrid[g1row-1][g1col-1] , gameGrid[g2row-1][g2col-1] , gameGrid);
                        
                        cursor.setPosition(0, 0); // hide the cursor after second click
                        gemClickCount = 0;        // reset is two clicks done for again two taps
                        isSwapping = true;        // during swapping no more mouse clicks allowed
                    }
                    else { gemClickCount = 1; }   // give the chance to player for re-choose
                }
                
                ////////////////////////////// @c MOVING-ANIMATION-LOGIC ///////////////////////////
                
                for (auto &eachBlock : gameGrid){
                    for (auto &eachPiece : eachBlock){
                        /* 
                        /// this logic works fine but it depands on the system FPS ///
                        int dx = eachPiece.x - eachPiece.col * oneGemSize;
                        int dy = eachPiece.y - eachPiece.row * oneGemSize;
                        if (dx != 0){ eachPiece.x -= dx /abs(dx);  isMoving = true; }
                        if (dy != 0){ eachPiece.y -= dy /abs(dy);  isMoving = true; }
                        */
                        // another logic where a loop is explicitly declered 
                        // to handle the swapping animation, so that it doesn't relay on system FPS
                        short int dx = 0, dy = 0;
                        for(short int speed = 0; speed < 3; ++speed){
                            
                            dx = eachPiece.x - eachPiece.col * oneGemSize;
                            dy = eachPiece.y - eachPiece.row * oneGemSize;
                            
                            // gradually move the piece to it's targeted grid position
                            if (dx != 0){ eachPiece.x -= dx / abs(dx);  isMoving = true; }
                            if (dy != 0){ eachPiece.y -= dy / abs(dy);  isMoving = true; }
                        }
                    }
                }
                
                ////////////////////////////// @c MATCH-FINDING ///////////////////////////
                
                // this part is just for marking the matches
                
                for (short int row = 0; row < gameGrid.size(); ++row){
                    for (short int col = 0; col < gameGrid[row].size(); ++col){
                        
                        // first checking vertically(row wise checking) of match gems 
                        if (col > 0  and  col < gameGrid[row].size()-1){ // condition for preventing out-of-bound accesses
                            if (gameGrid[row][col].type == gameGrid[row][col - 1].type 
                            &&  gameGrid[row][col].type == gameGrid[row][col + 1].type){
                                
                                gameGrid[row][col].match     = true;
                                gameGrid[row][col - 1].match = true;
                                gameGrid[row][col + 1].match = true;
                            }
                        }
                        // now checking horizontally(col wise checking) of match gems 
                        if (row > 0  and  row < gameGrid.size()-1){ // condition for preventing out-of-bound accesses
                            if (gameGrid[row][col].type == gameGrid[row - 1][col].type
                            &&  gameGrid[row][col].type == gameGrid[row + 1][col].type){
                                
                                gameGrid[row][col].match     = true;
                                gameGrid[row - 1][col].match = true;
                                gameGrid[row + 1][col].match = true;
                            }
                        }
                        
                    }
                }
                
                ////////////////////////////// @c DELETING-ANIMATION ///////////////////////////
                
                // after finding the mathces those gems are removed from the grid 
                // with an animated fadeing effect
                if (not isMoving){
                    for (auto &eachBlock : gameGrid){
                        for (auto &eachPiece : eachBlock){
                            
                            // if the piece is part of match and still not toally faded(un-visible)
                            if (eachPiece.match  and  eachPiece.alpha > 0){
                                eachPiece.alpha -= 5; // slowly decrease the transparency of the gem
                                isMoving = true;
                            }
                        }
                    }
                }
                
                //////////////////////////////// @c CALCULATE-SCORE //////////////////////////////
                
                // calculate the score in each frame
                short int curScore = 0;
                for (auto &eachBlock : gameGrid){
                    for (auto &eachPiece : eachBlock){
                        if (eachPiece.match){ curScore += 1; }
                    }
                }
                // now update the score only once, when no moving is going on
                if (not isMoving  and  curScore){ playersScore += curScore; }
                // if player's score reach 99 the finish the game
                if (playersScore > 99){ throw "GAME OVER !"; }
                
                ////////////////////////////// @c SWAP-BUT-NOT-MTACHED ///////////////////////////
                
                // now if the pieces are swapped but not matched then reverse the swap
                if (isSwapping && not isMoving){ // swapped but not moved, then re-swap
                    
                    swapGems(gameGrid[g1row-1][g1col-1] , gameGrid[g2row-1][g2col-1] , gameGrid);
                    isSwapping = false; // again provide the chance for swapping
                }
                
                /*** important ***/
                ///////////////// @c UPDATE-GRID-:-MOVING-PIECES-DOWN-&-GENERATE-NEW-PIECES /////////////////
                
                if (not isMoving){
                    
                    // this section handles the gems down after match and delete animation 
                    // iterate through the grid in a reverse order, from [7,7]->[7,0]->...->[0,7]->[0,0]
                    for (short int col = gameGrid[0].size()-1; col >= 0; --col){
                        
                        /// @_logic: itearte from last, for each column, each element, if found `piece.match == true`,
                        // then count the empty spaces and move down the non-matched- pieces by swapping with them
                        // ------ current non-matched-piece + empty space  ==  matched-piece(empty cell) ------
                        short int emptySpaces = 0;
                        for (short int row = gameGrid.size()-1; row >= 0; --row){
                            
                            // count the empty sapces in the selected col
                            if (gameGrid[row][col].match){ ++emptySpaces;  continue; }
                            if (emptySpaces > 0){ // if there is empty space in the col
                                
                                swapGems(gameGrid[row + emptySpaces][col] , gameGrid[row][col] , gameGrid);
                                isMoving = true;
                            }
                        }
                    }
                    // this section re-spawn new pieces(new gems)
                    for (short int col = gameGrid[0].size()-1; col >= 0; --col){
                        for (short int row = gameGrid.size()-1, pos = 0; row >= 0; --row){
                            
                            if (gameGrid[row][col].match){
                                
                                // set the 'y' co-ordinate at -minus explicitly for creating an animation effect
                                gameGrid[row][col].y = -oneGemSize * ++pos;
                                gameGrid[row][col].type  = randNo(randGen) % 7;
                                gameGrid[row][col].match = false;
                                gameGrid[row][col].alpha = 255;
                                
                            }
                            isMoving = true;
                        }
                    }
                }
                
                isMoving = false; // reset the flag for the next FRAME
            }
            
            ////////////////////////////// @c WINDOW-DRAW ///////////////////////////
            
            window.clear();
            window.draw(background);
            
            if (initialMessagePrinted){
                // draw the gems
                for (auto &eachBlock : gameGrid){
                    for (auto &eachPiece : eachBlock){
                        
                        gems.setTextureRect(IntRect(eachPiece.type * 49, 0, 49, 49));
                        gems.setColor(Color(255, 255, 255, eachPiece.alpha));
                        gems.setPosition(eachPiece.x, eachPiece.y);
                        gems.move(48, 25); // for padding
                        // helps in finding mouse taps on the gems
                        eachPiece.setGlobalBounds(gems.getGlobalBounds());
                        window.draw(gems);
                    }
                }
                // draw the player's real time score
                gameMessage("gameScore", playersScore, imgBack, window);
            }
            else {
                gameMessage("gameInitialMessage", 0, imgBack, window);
            }
            // if the cursor is placed at 0,0 then no need to print it
            if (cursor.getPosition() != Vector2f(0, 0)){ window.draw(cursor); }
            window.display();
        }
    }
    catch (...){ // when control reaches here all the objs get destroyed except the window and textures
        gameMessage("gameFinish", 2, imgBack, window);
        setGameScores("99", "99"); 
    }
    
    /////////////////////////////////////// @c UPDATE-SCORE /////////////////////////////////////
    
    unsigned short int highScore = std::stoi(getGameScore("HighestScore"));
    // if current score is greater than the existing high score then, update both the scores
    if (playersScore >= highScore){ 
        gameMessage("gameNewScore", 1, imgBack, window);
        setGameScores(std::to_string(playersScore), std::to_string(playersScore)); 
    }
    else { // otherwise only update the current score
        setGameScores(std::to_string(playersScore), std::to_string(highScore)); 
    }
    return 0;
}


// just we need to change the swap logic for targeted rows and cols 
// rest of the work done by moving animation
constexpr void swapGems(piece gem1, piece gem2, auto &gameGrid){
    
    // swap the targeted row and col only and not used explicit swap() calls
    auto 
    tempRow  = gem1.row,  tempCol  = gem1.col;
    gem1.row = gem2.row;  gem1.col = gem2.col;
    gem2.row = tempRow;   gem2.col = tempCol;
    
    // directly update the grid
    gameGrid[gem1.row][gem1.col] = gem1;
    gameGrid[gem2.row][gem2.col] = gem2;
}


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
    
    std::ifstream fileToRead("MatchGemsScore.txt", std::ios::in);
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
    
    std::ofstream fileToWrite("MatchGemsScore.txt");
    fileToWrite << std::string(curScore) << "\n" << std::string(highScore);
    fileToWrite.close();
}


void gameMessage(sf::String &&m, short int &&mszDuration, sf::Texture &backImage, sf::RenderWindow &window){
    using namespace sf;
    
    Text txt;  Font f;  bool pgExit = false;
    f.loadFromFile("Fonts/algerian-regular.ttf");
    
    if (m == "gameFinish"){
        txt.setString(" -> Greetings ... \n -- YOU MATCH 99 !"); 
        txt.setFillColor(Color::Green);
        pgExit = true;
    }
    else if (m == "gameScore"){
        txt.setString(" Score : " + std::to_string(mszDuration));
        txt.setFillColor(Color::Red);
        txt.setFont(f);
        txt.setPosition(backImage.getSize().x / 2 + 130, backImage.getSize().y / 2 + 171);
        window.draw(txt);
        return;
    }
    else if (m == "gameInitialMessage"){
        txt.setString(" NEW GAME \n"); 
        txt.setFont(f);
        Text txt2("SCORE BOARD ", f);
        txt.setFillColor(Color::Blue);
        txt2.setFillColor(Color::Blue);
        txt.setPosition(backImage.getSize().x / 2 - 90, backImage.getSize().y / 2 - 49);
        txt2.setPosition(backImage.getSize().x / 2 - 95, backImage.getSize().y / 2 + 5);
        
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
            if (Mouse::isButtonPressed(Mouse::Left)){ initialMessagePrinted = true; }
        }
        else if (txt2Pos.contains(mousePos)){
            txt2.setFillColor(Color::Cyan);
            
            // by doing this the score board will be shown
            if (Mouse::isButtonPressed(Mouse::Left)){
                String message =
                    " Last Score : " + getGameScore("CurrentScore")
                    + "\n\n" + 
                    " High Score : " + getGameScore("HighestScore");
                gameMessage(std::move(message), 3, backImage, window);
            }
            
        }
        else { // return to previous color when mouse cursor is not hovered
            txt.setFillColor(Color::Blue);  
            txt2.setFillColor(Color::Blue);
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
    txt.setPosition(backImage.getSize().x / 2 - 115, backImage.getSize().y / 2 - 65);
    window.clear();
    window.draw(txt);
    window.display();
    sleep(seconds(mszDuration));// sleep to pause the pg. for the required time
    if (pgExit){ exit(EXIT_FAILURE); };
}