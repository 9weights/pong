#include <iostream>
#include "raylib.h"
#include <vector>
//class entity{
//private:
//
//public:
//    entity(float x, float y, float width, float height)
//        : m_player{x,y,width,height}
//    {}
//    Rectangle m_player;
//};
//

const float g_deltaT{1};


void calcHorzImpulse(Vector2& ballVelocity, Vector2 paddleVelocity)
{
    ballVelocity.y = (paddleVelocity.y - ballVelocity.y) / 2 + ballVelocity.y;
    ballVelocity.x = -ballVelocity.x;
}
void calcVertImpulse(Vector2& ballVelocity, Vector2 velocity)
{
    ballVelocity.y = -ballVelocity.y;
}
void calcPosition(Rectangle& entity, Vector2 velocity)
{
    double deltaT{1.0};
    entity.x = entity.x + velocity.x * g_deltaT;
    entity.y = entity.y + velocity.y * g_deltaT;
}

void runNpcTurn(Rectangle& npc, const Rectangle& ball, Vector2& npcVelocity)
{
    float y2 {ball.y};
    y2 = ball.y - (npc.height - ball.height)/2;
    npcVelocity.y = {(y2 - npc.y) / g_deltaT};
    npc.y = y2;
}

 int main(){
    const int screenWidth{1000};
    const int screenHeight{800};
    InitWindow(screenWidth, screenHeight, "Pong GUI");
    Camera2D camera{};
    camera.zoom = 1;
    camera.offset = Vector2{0,0};
    camera.target = Vector2{0,0};
    camera.rotation = 0;
    
    float ballWidth{10};
    Vector2 startPos {screenWidth/2 - ballWidth/2,screenHeight/2 - ballWidth/2};
    Vector2 startVel {1,0};

    Rectangle player = {0, screenHeight/2 - 50,10,100};
    Rectangle npc = {screenWidth - 10, screenHeight/2 - 50, 10, 100};
    Rectangle ball = {startPos.x, startPos.y, ballWidth, ballWidth};
    Rectangle halfPitchLine = {screenWidth/2 - 5, 0, 10, screenHeight};

    std::vector<Rectangle> walls{{0,0,screenWidth,1},
        {screenWidth,0,1,screenHeight},
        {0,screenHeight,screenWidth,1},
        {0,0,1,screenHeight}
    };
    
    
    Vector2 ballVelocity {startVel.x,startVel.y};
    Vector2 playerPaddleVelocity {0,0};
    Vector2 npcPaddleVelocity {0,0};
    int playerScore {0};
    int npcScore{0};
    bool isReset{};
    std::string nScore{};
    std::string pScore{};
    bool playerWin{false};
    bool npcWin{false};


    while (!WindowShouldClose())
    {
        if (isReset)
        {

        }


        if (IsKeyDown(KEY_DOWN)){playerPaddleVelocity.y = 2;}
        else if (IsKeyDown(KEY_UP)){playerPaddleVelocity.y = -2;}
        else {playerPaddleVelocity.y = 0;}
        if (CheckCollisionRecs(player, walls[0]))
        {
            if (playerPaddleVelocity.y < 0){playerPaddleVelocity.y = 0;}
        }

        else if (CheckCollisionRecs(player, walls[2]))
        {
            if (playerPaddleVelocity.y > 0){playerPaddleVelocity.y = 0;}
        }

        calcPosition(player, playerPaddleVelocity);

        runNpcTurn(npc, ball, npcPaddleVelocity);



        
        if (CheckCollisionRecs(player, ball)){calcHorzImpulse(ballVelocity, playerPaddleVelocity);}
        else if (CheckCollisionRecs(npc, ball)){calcHorzImpulse(ballVelocity, npcPaddleVelocity);}
        for (auto idx{0}; idx < 4; ++idx)
        {
            if (CheckCollisionRecs(walls[idx], ball))
            {
                if (idx == 0 || idx == 2){calcVertImpulse(ballVelocity, Vector2 {0,0});}
                else 
                {
                    if (idx == 1)
                    {
                        ++playerScore;
                    }
                    if (idx == 3)
                    {
                        ++npcScore;
                    }

                    ball.x = startPos.x;
                    ball.y = startPos.y;
                    ballVelocity.x = startVel.x;
                    ballVelocity.y = 0;

                    isReset = true;
                }
                
            }
        }
        calcPosition(ball, ballVelocity);
        if (playerScore > 3)
        {
            playerWin = true;
        }
        else if (npcScore > 3)
        {
            npcWin = true;
        } 
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                DrawRectangleRec(halfPitchLine, LIGHTGRAY);
                DrawRectangleRec(player, GRAY);
                DrawRectangleRec(npc, GRAY);
                DrawRectangleRec(ball, WHITE);
                for (Rectangle wall : walls)
                {
                    DrawRectangleRec(wall, WHITE);
                }
            EndMode2D();
            pScore = "Player score: " + std::to_string(playerScore);
            nScore = "Npc score: " + std::to_string(npcScore);
            DrawText(pScore.c_str(), screenWidth/4, 10, 20 ,RED);
            DrawText(nScore.c_str(), screenWidth * 3.0/4.0, 10, 20 ,RED);
        EndDrawing();
    if (playerWin || npcWin)
    {
        while(!WindowShouldClose())
        {
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
            if (playerWin){DrawText("You win", screenWidth/3, 50, 100, RED);};
            if (npcWin){DrawText("You lose", screenWidth/3, 50, 100, RED);}
        EndDrawing();
        }
        break;
    }
    }
    CloseWindow();
    //Rectangle npc =
    // createGUI()
    // createUserPaddle
    // createCPUPaddle
    // createBall
    // if press enter
    // startGame
    // if press ctrl c
    // quit


    return 0;
}
