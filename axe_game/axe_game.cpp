      #include "raylib.h"

      int main(){
        //Window dimensions
        int width{800};
        int height{450};
        //Score variable
        float score = 0.0;

        //Circle coordinates
        int circle_x{200};
        int circle_y{200};
        int circle_radius{25};
        //Circle edges
        int l_circle_x{circle_x - circle_radius};
        int r_circle_x{circle_x + circle_radius};
        int u_circle_y{circle_y - circle_radius};
        int b_circle_y{circle_y + circle_radius};


        //Axe coordinates
        int axe_x{400};
        int axe_y{0};
        int axe_length{50};
        //Axe edges
        int l_axe_x{axe_x};
        int r_axe_x{axe_x + axe_length};
        int u_axe_y{axe_y};
        int b_axe_y{axe_y + axe_length};


        int directions{10};
        bool collision_with_axe = 
                                  (b_axe_y >= u_circle_y) &&
                                  (u_axe_y <= b_circle_y) &&
                                  (r_axe_x >= l_circle_x) &&
                                  (l_axe_x <= r_circle_x);

        
        InitWindow(width,height,"Axe Game");
        SetTargetFPS(60);
        while(WindowShouldClose() == false)
        {
          BeginDrawing();
          ClearBackground(WHITE);
          

          if(collision_with_axe)
          {
            const char* gameOverText = "Game Over!";
            int fontSize = 40;

            //Checking how wide is the text
            int textWidth = MeasureText(gameOverText, fontSize);

            //Center the text both horizontally and vertically on the screen
            int centerWidth = (width / 2) - (textWidth / 2);
            int centerHeight = height / 2 - fontSize / 2;

            DrawText(gameOverText, centerWidth, centerHeight, fontSize, RED);
            DrawText(TextFormat("Score: %.2f", score), 10, 10, 20, DARKGRAY);

            //Checking if the player wants to restart
            if (IsKeyPressed(KEY_R)) 
            {
            // Reset all game state
            score = 0;
            circle_x = 200;
            axe_y = 0;
            collision_with_axe = false;
            }
            DrawText("Press R to Restart", centerWidth, centerHeight + 50, 20, DARKGRAY);
          }
          else
          {
          //Game logic begins

          //Implementing score
              score += GetFrameTime();
              DrawText(TextFormat("Score: %.2f", score), 10, 10, 20, DARKGRAY);
          
          //Update the edges every frame
          l_circle_x = circle_x - circle_radius;
          r_circle_x = circle_x + circle_radius;
          u_circle_y = circle_y - circle_radius;
          b_circle_y = circle_y + circle_radius;
          l_axe_x = axe_x;
          r_axe_x = axe_x + axe_length;
          u_axe_y = axe_y;
          b_axe_y = axe_y + axe_length;
          //Update collision with axe every frame
          collision_with_axe = 
                                  (b_axe_y >= u_circle_y) &&
                                  (u_axe_y <= b_circle_y) &&
                                  (r_axe_x >= l_circle_x) &&
                                  (l_axe_x <= r_circle_x);

          DrawCircle(circle_x, circle_y, circle_radius, BLUE);
          DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

          //Movement of the axe
          axe_y += directions;
          if(axe_y > height || axe_y < 0)
          {
            directions = -directions;
          }

          //Movement of the circle
          if(IsKeyDown(KEY_D) && circle_x < width - circle_radius)
          {
            circle_x += 10;
          }
          if(IsKeyDown(KEY_A) && circle_x > circle_radius)
          {
            circle_x -= 10;
          }
          //game logic ends
          }
          EndDrawing();
        }

      }
