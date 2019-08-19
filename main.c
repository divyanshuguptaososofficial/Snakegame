#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define wall_row 20//width of boundary
#define  wall_column 40//height  of boundary
    int i,j,Box[wall_row][wall_column],snake_xcoordinate,snake_ycoordinate,snake_head,snake_tail,snake_temp,game_over,food,food_xcoordinate,food_ycoordinate,user_input,direction,score,high_score,Speed;//global variables that are used in function
    FILE *f;//we are creating file handler

void snake_body()//it will define all the property of snake like movement position etc
 {
        f=fopen("highscore.txt","r");//we are opening highscore file in snake body so that we want to open/print the highscore file/data in the starting of the game
        fscanf(f,"%d",&high_score);//we are taking the value from the file and storing it in high_score variable
        fclose(f);

     for(i=0;i<wall_row;i++)
        {
            for(j=0;j<wall_column;j++)//nested for loop
                {
                    Box[i][j]=0; // we are setting all the values of box field to zero
                }
        }
                    snake_xcoordinate=wall_row/2;//starting postion of snake in the middle of the box
                    snake_ycoordinate=wall_column/2;//snake position is set to middle with  snake_xcoordinate =10 &snake_ycoordinate =20
                    snake_temp=snake_ycoordinate;
                    snake_head=5;
                    snake_tail=1;
                    game_over=0;
                    food=0;
                    direction='d';//we are intializing the dirction so that whenever our game starts the snake is moving in some direction
                    score=0;
                    Speed=100;

    for(i=0;i<snake_head;i++)
        {
            snake_temp++;
            Box[snake_xcoordinate][snake_temp-snake_head] = i+1;//setting coordinate for tail and head to appear
        }

}

void print()//it will print boundary ,food and score
{
    for(i=0;i<=wall_column+1;i++)//top vertical line of the box
        {
            if(i==0)
                printf("%c",201);//top left corner
            else if(i==wall_column+1)
                printf("%c",187);//top right corner
            else
                printf("%c",205);//vertical line joining top left corner and top right corner
        }
            printf("CURRENT SCORE:%d    \t HIGHSCORE:%d ",score,high_score);
            printf("\n");

    for(i=0;i<wall_row;i++)//will draw two horizontal line from top left corner and top right corner joining bottom left corner and bottom right corner respectively
        {
            printf("%c",186);
                for(j=0;j<wall_column;j++)//NESTED FOR LOOP
                {
                    if(Box[i][j]==0)
                        printf(" ");//print blank space where ever we have set the value of box fiwld to 0

                    if(Box[i][j]>0 && Box[i][j]!=snake_head)
                        printf("%c",176);//print tail of the snake

                    if(Box[i][j]==snake_head)
                        printf("%c",178);//prints head of the snake

                    if(Box[i][j]==-1)
                        printf("%c",15);

                    if(j==wall_column-1)
                        printf("%c\n",186);//horizontal line

                }
        }
            for(i=0;i<=wall_column+1;i++)//bottom  vertical line of the box
                {
                    if(i==0)
                        printf("%c",200);//bottom left corner
                    else if(i==wall_column+1)
                        printf("%c",188);//bottom right corner
                    else
                        printf("%c",205);//vertival line joining bottom left corner and bottom right corner
                }
}

void Food_creation()//code for food creation
{
    srand(time(0));//as we run our program again and again we have the same random food location(that make our predictable) to over come this situation we will use srand(value) so that it generate food at different locatin
    food_xcoordinate = 1+ rand() % 18; //x coordinate of food and we are adding(1) ,we are doing modulus by 18 so that food doesnot come on the boundary
    food_ycoordinate = 1 + rand() % 38;//y coordinate of food and we are adding(1) ,we are doing modulus by 38 so that food doesnot come on the boundary

    if(food == 0 && Box[food_xcoordinate][food_ycoordinate]==0)//checking if  there is  food or not and as well as there is empty space in the boc
        {
            Box[food_xcoordinate][food_ycoordinate]= -1;//we are setting special value to this coordinate so that we can use this while printing the food
            food = 1;//it tells the food is already on the screen

        if(Speed>10 && score!=0)//as the snake eats the food the speed of snake increases
            {
                Speed= Speed - 5;//in this we are decreasing it so that our halt time is less
            }
        }
}

void ResetScreenPosition()//resetting screen
{
    HANDLE hOut;//handle allows us to handle the console of the program
    COORD Position;//it gives post coordinate of the console screen
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);//hout variable(we have created) is used to handle the standard input of the program
    Position.X = 0;//assiging top most corner of the output screen to the variable position
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);//just setting the cursor position
}

int input_keyboard()//creating this function to get the character when keyboard is hit
{
    if(_kbhit())//when button is press it returns the character
       {
           return _getch();
       }
    else
        {
            return -1;
        }
}

void snake_movementeasy()//in this function the snake can go from all the 4 side of the wall and can come from all the opposite side
{
    user_input = input_keyboard();//getting the input from the user and storing it
    user_input = tolower(user_input);//converting the input in lower so that we donot worry about whether capslock is on or not

    if(((user_input=='w'||user_input=='a')||(user_input=='s'||user_input=='d')) && (abs(direction-user_input)>5))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
    direction = user_input;

    if(direction=='w')//up
    {
        snake_xcoordinate--;
       if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        {
            GameOver();
        }
        if(snake_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
            snake_xcoordinate=wall_row-1;
          if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
               score+=5;//increasing the score when snake eats the food
               snake_tail -= 1;//for increasing snake length

           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

         if(direction=='a')//left
    {
        snake_ycoordinate--;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
            snake_ycoordinate=wall_column-1;

        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
           {

           food = 0;//for creating new food when snake surpasses the food
        score+=5;//increasing the score when snake eats the food
        snake_tail -= 1;//for increasing snake length


           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }


        if(direction=='s')//down
    {
        snake_xcoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
            snake_xcoordinate=0;
        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
        {

        food = 0;//for creating new food when snake surpasses the food
       score+=5;//increasing the score when snake eats the food
       snake_tail -= 1;//for increasing snake length



           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

    if(direction=='d')//right
    {
        snake_ycoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
           snake_ycoordinate=0;

           if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
                score+=5;//increasing the score when snake eats the food
                   snake_tail -= 1;//for increasing snake length


           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }
}

void snake_movementmoderate()//in this function the snake can go from  2 side of the wall and can come from only 2  opposite side(when snake touches upper and bottom wall the game gets over)
{
    user_input = input_keyboard();//getting the input from the user and storing it
    user_input = tolower(user_input);//converting the input in lower so that we donot worry about whether capslock is on or not

    if(((user_input=='w'||user_input=='a')||(user_input=='s'||user_input=='d')) && (abs(direction-user_input)>5))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
    direction = user_input;

    if(direction=='w')//up
    {
        snake_xcoordinate--;
       if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
            {
               game_over=1;
                GameOver();
           }
          if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
               score+=5;//increasing the score when snake eats the food
               snake_tail -= 1;//for increasing snake length

           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

         if(direction=='a')//left
    {
        snake_ycoordinate--;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
            snake_ycoordinate=wall_column-1;

        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
           {

           food = 0;//for creating new food when snake surpasses the food
        score+=5;//increasing the score when snake eats the food
        snake_tail -= 1;//for increasing snake length


           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }


        if(direction=='s')//down
    {
        snake_xcoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
           {
               game_over=1;
                GameOver();
           }
        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
        {

        food = 0;//for creating new food when snake surpasses the food
       score+=5;//increasing the score when snake eats the food
       snake_tail -= 1;//for increasing snake length



           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

    if(direction=='d')//right
    {
        snake_ycoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOver();

        if(snake_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
           snake_ycoordinate=0;

           if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
                score+=5;//increasing the score when snake eats the food
                   snake_tail -= 1;//for increasing snake length


           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }
}

void snake_movementhard()//in this function snakes dies by hitting all the four wall
{
    user_input = input_keyboard();//getting the input from the user and storing it
    user_input = tolower(user_input);//converting the input in lower so that we donot worry about whether capslock is on or not

    if(((user_input=='w'||user_input=='a')||(user_input=='s'||user_input=='d')) && (abs(direction-user_input)>5))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
        {
        direction = user_input;
        }
    if(direction=='w')//up
        {
            snake_xcoordinate--;
            if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOver();
                }
            if(snake_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
                {
                    GameOver();
                }
            if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score+=5;//increasing the score when snake eats the food
                    snake_tail -= 1;//for increasing snake length
                }
                    snake_head++;
                    Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
        }

    if(direction=='a')//left
        {
            snake_ycoordinate--;
            if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOver();
                }
            if(snake_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
                {
                  GameOver();
                }
            if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score+=5;//increasing the score when snake eats the food
                    snake_tail -= 1;//for increasing snake length
                }
                    snake_head++;
                    Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
        }

    if(direction=='s')//down
        {
            snake_xcoordinate++;
            if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOver();
                }
            if(snake_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
                {
                    GameOver();
                }
            if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score+=5;//increasing the score when snake eats the food
                    snake_tail -= 1;//for increasing snake length
                }
                    snake_head++;
                    Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
        }

    if(direction=='d')//right
        {
            snake_ycoordinate++;
            if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOver();
                }
            if(snake_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
                {
                    GameOver();
                }
           if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score+=5;//increasing the score when snake eats the food
                    snake_tail -= 1;//for increasing snake length
                }
                    snake_head++;
                    Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
        }
}//end of snake_movementhard function

void snaketail_movement()//start of snaketail_movementfunction
{
    for(i=0;i<wall_row;i++)
        {
            for(j=0;j<wall_column;j++)
            {
                if(Box[i][j]==snake_tail)//we are checking where the value is non zero and then e=we are setting it to 0
                    {
                        Box[i][j] = 0;
                    }
            }
        }
                        snake_tail++;//we are incrementing the tail so that when snaketail_movemnt function is called it check for different value
}//end of snaketail_movementfunction

void GameOver()//some material that should occur when our game gets over
{
    printf("\a");//it will produce a beep sound indicating that our game is over
    Sleep(200);
    system("Cls");

    if(score>high_score)//comparing the score from the high score if  score is more than high score than we will update the value in the highscore file
        {
        printf("  New HighScore %d!!!!!!\n\n",score);
        system("pause");//halting the system
        f=fopen("highscore.txt","w");//writing new value in the file
        fprintf(f,"%d",score);//printing score value
        fclose(f);
        }
    system("Cls");

    printf("\n\n         GAME OVER !!!!!!\n");
    printf("             Score : %d \n\n",score);
    printf("             Press ENTER to play again or ESC to exit ... \n");

    while(1)
    {
        user_input = input_keyboard();//taking input
        if(user_input == 13)//if user press enter the game will run again
            {
                game_over=0;
                system("Cls");
                game_level();
                break;
            }
        else if(user_input == 27)//if user press escape the game will end
                {
                    game_over=1;
                    break;
                }
    }
        system("Cls");
}

void game_level()//function for selecting game level
{
    printf("\nSELECT YOUR LEVEL  \n  1)EASY \n 2)MODERATE \n 3)HARD");
    scanf("%d",&user_input);

    switch(user_input)
    {
        case 1:
            {//case 1 starts
                system("Cls");
                snake_body();
    while(game_over==0)
    {
        print();
        ResetScreenPosition();
        Food_creation();
        snake_movementeasy();
        snaketail_movement();
        Sleep(Speed); //this will increase this speed of snake
    }
            break;
            }//case 1 ends

         case 2:
            {//case 2 satarts
                system("Cls");
                snake_body();
     while(game_over==0)
    {
        print();
        ResetScreenPosition();
        Food_creation();
        snake_movementmoderate();
        snaketail_movement();
        Sleep(Speed); //this will increase this speed of snake

    }
            break;
            }//case 2 ends

   case 3:
            {//case 3 satarts
                system("Cls");
                snake_body();
     while(game_over==0)
    {
        print();
        ResetScreenPosition();
        Food_creation();
        snake_movementhard();
        snaketail_movement();
        Sleep(Speed); //this will increase this speed of snake

    }
            break;
            }//case 3 ends
}
}
void game_details()//function for about the game
{
    printf("Welcome to our snake game !!!!!!!!!!!!!!!!!!!   \n  CONTROLS : \n W->UP \n A->LEFT \n S->DOWN \n D->RIGHT  \n THE GAME HAS THREE LEVEL SELCTION \n EASY MODE: IN THIS YOU DONOT DIE BY HITTING ALL THE FOUR WALL AND THE ONLY WAY TO GET KILLED IS BY EATING YOUR OWN TAIL \n MODERATE:IN THIS YOU  DIE BY HITTING THE UPPER ,BOTTOM WALL AND BY EATING YOUR OWN TAIL \nHARD MODE: IN THIS YOU  DIE BY HITTING ALL THE 4 WALL AND  BY EATING YOUR OWN TAIL");
}
int main()//main function
{
    game_details();
    game_level();

}

