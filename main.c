#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

 #define TRUE 1
#define wall_row 20//width of boundary
#define  wall_column 40//height  of boundary

    int i,j,Box[wall_row][wall_column],snake_xcoordinate,snake_ycoordinate,snake_head,snake_tail,snake_temp,game_over,food,food_xcoordinate,food_ycoordinate,user_input,direction,score,high_score,Speed;//global variables that are used in function
    FILE *f,*f1;//we are creating file handler
    int snake2_xcoordinate,snake2_ycoordinate,snake2_temp,snake2_head,snake2_tail,direction2,user2_input,score1,score2;
    char name[20];

  COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left corner of the screen
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
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


void game_level()//function for selecting game level
{
    bold_red();
     gotoxy(50,12);
    printf("SELECT YOUR LEVEL");
        gotoxy(50,13);
        printf("1)EASY");
        gotoxy(50,14);
        printf("2)MEDIUM");
        gotoxy(50,15);
        printf("3)HARD");


        gotoxy(50,16);
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


                SetConsoleTextAttribute(hConsole, 480);
                bold_red();
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
             default:
    {
              gotoxy(50,16);
            printf("WRONG INPUT");
            gotoxy(50,17);
            printf("PRESS ENTER TO GO BACK");
            while(1)
    {
        user_input = input_keyboard();//taking input
        if(user_input == 13)//if user press enter the game will run again
            {
               game_details();
               game_level();
                break;
            }
        else if(user_input == 27)//if user press escape the game will end
                {

                    break;
                }
    }

    }
}
}

void snakemulti_body()//it will define all the property of snake like movement position etc
 {


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


                     snake2_xcoordinate=wall_row/4;//starting postion of snake in the middle of the box
                    snake2_ycoordinate=wall_column/4;//snake position is set to middle with  snake_xcoordinate =5 &snake_ycoordinate =10
                    snake2_temp=snake2_ycoordinate;
                    snake2_head=5;
                    snake2_tail=1;
                    direction2=UP;

    for(i=0;i<snake_head;i++)
        {
            snake_temp++;
            Box[snake_xcoordinate][snake_temp-snake_head] = i+1;//setting coordinate for tail and head to appear
        }
        for(i=0;i<snake2_head;i++)
        {
            snake2_temp++;
            Box[snake2_xcoordinate][snake2_temp-snake2_head] = i+1;//setting coordinate for tail and head to appear
        }

}

void printmulti()//it will print boundary ,food and score
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
            printf("PLAYER1:%d   PLAYER2:%d    \t ",score1,score2);
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


                if(Box[i+4][j+4]>0 && Box[i+4][j+4]!=snake2_head)
                    bold_red();
                         printf("%c",176);//print tail of the snake

                    if(Box[i+4][j+4]==snake2_head)
                        printf("%c",178);//prints head of the snake


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
                Speed= Speed - 15;//in this we are decreasing it so that our halt time is less
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

void snakemulti_movementeasy()//in this function the snake can go from all the 4 side of the wall and can come from all the opposite side
{
    user_input = input_keyboard();//getting the input from the user and storing it
    //user_input = tolower(user_input);//converting the input in lower so that we donot worry about whether capslock is on or not


    if(((user_input=='w'||user_input=='a')||(user_input=='s'||user_input=='d')) && (abs(direction-user_input)>5))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)

    direction = user_input;

   if(((user_input== UP||user_input==DOWN)||(user_input==RIGHT||user_input==LEFT)) && ((abs(direction2-user_input)!=2) && (abs(direction2-user_input)!=8) ))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
   direction2 = user_input;



    if(direction=='w')//up
    {
        snake_xcoordinate--;
       if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        {
            GameOvermulti();
        }
        if(snake_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
            snake_xcoordinate=wall_row-1;
          if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
               score1+=5;//increasing the score when snake eats the food
               snake_tail -= 1;//for increasing snake length

           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

         if(direction=='a')//left
    {
        snake_ycoordinate--;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
            snake_ycoordinate=wall_column-1;

        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
           {

           food = 0;//for creating new food when snake surpasses the food
        score1+=5;//increasing the score when snake eats the food
        snake_tail -= 1;//for increasing snake length


           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }


        if(direction=='s')//down
    {
        snake_xcoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
            snake_xcoordinate=0;
        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
        {

        food = 0;//for creating new food when snake surpasses the food
       score1+=5;//increasing the score when snake eats the food
       snake_tail -= 1;//for increasing snake length



           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

    if(direction=='d')//right
    {
        snake_ycoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
           snake_ycoordinate=0;

           if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
                score1+=5;//increasing the score when snake eats the food
                   snake_tail -= 1;//for increasing snake length


           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }


     if(direction2==UP)//up
    {
        snake2_xcoordinate--;
       if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        {
            GameOvermulti();
        }
        if(snake2_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
            snake2_xcoordinate=wall_row-1;
          if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
               score2+=5;//increasing the score when snake eats the food
               snake2_tail -= 1;//for increasing snake length

           }
        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }


         if(direction2==LEFT)//left
    {
        snake2_ycoordinate--;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
            snake2_ycoordinate=wall_column-1;

        if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
           {

           food = 0;//for creating new food when snake surpasses the food
        score2+=5;//increasing the score when snake eats the food
        snake2_tail -= 1;//for increasing snake length


           }
        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;

    }

        if(direction2==DOWN)//down
    {
        snake2_xcoordinate++;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
            snake2_xcoordinate=0;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
        {

        food = 0;//for creating new food when snake surpasses the food
       score2+=5;//increasing the score when snake eats the food
       snake2_tail -= 1;//for increasing snake length



           }

        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }

    if(direction2==RIGHT)//right
    {
        snake2_ycoordinate++;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
           snake2_ycoordinate=0;

           if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
                score2+=5;//increasing the score when snake eats the food
                   snake2_tail -= 1;//for increasing snake length


           }

        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }
}





void snakemulti_movementmoderate()//in this function the snake can go from  2 side of the wall and can come from only 2  opposite side(when snake touches upper and bottom wall the game gets over)
{
    user_input = input_keyboard();//getting the input from the user and storing it
    //user_input = tolower(user_input);//converting the input in lower so that we donot worry about whether capslock is on or not

    if(((user_input=='w'||user_input=='a')||(user_input=='s'||user_input=='d')) && (abs(direction-user_input)>5))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
    direction = user_input;


  if(((user_input== UP||user_input==DOWN)||(user_input==RIGHT||user_input==LEFT)) && ((abs(direction2-user_input)!=2) && (abs(direction2-user_input)!=8) ))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
   direction2 = user_input;


    if(direction=='w')//up
    {
        snake_xcoordinate--;
       if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
            {
               game_over=1;
                GameOvermulti();
           }
          if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
               score1+=5;//increasing the score when snake eats the food
               snake_tail -= 1;//for increasing snake length

           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

         if(direction=='a')//left
    {
        snake_ycoordinate--;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
            snake_ycoordinate=wall_column-1;

        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
           {

           food = 0;//for creating new food when snake surpasses the food
        score1+=5;//increasing the score when snake eats the food
        snake_tail -= 1;//for increasing snake length


           }
        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }


        if(direction=='s')//down
    {
        snake_xcoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
           {
               game_over=1;
                GameOvermulti();
           }
        if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
        {

        food = 0;//for creating new food when snake surpasses the food
       score1+=5;//increasing the score when snake eats the food
       snake_tail -= 1;//for increasing snake length



           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

    if(direction=='d')//right
    {
        snake_ycoordinate++;
        if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
           snake_ycoordinate=0;

           if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
                score1+=5;//increasing the score when snake eats the food
                   snake_tail -= 1;//for increasing snake length


           }

        snake_head++;
        Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
    }

 if(direction2==UP)//up
    {
        snake2_xcoordinate--;
       if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
            {
               game_over=1;
                GameOvermulti();
           }
          if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
               score2+=5;//increasing the score when snake eats the food
               snake2_tail -= 1;//for increasing snake length

           }
        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }

         if(direction2==LEFT)//left
    {
        snake2_ycoordinate--;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
            snake2_ycoordinate=wall_column-1;

        if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
           {

           food = 0;//for creating new food when snake surpasses the food
        score2+=5;//increasing the score when snake eats the food
        snake2_tail -= 1;//for increasing snake length


           }
        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }


        if(direction2==DOWN)//down
    {
        snake2_xcoordinate++;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
           {
               game_over=1;
                GameOvermulti();
           }
        if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
        {

        food = 0;//for creating new food when snake surpasses the food
       score2+=5;//increasing the score when snake eats the food
       snake2_tail -= 1;//for increasing snake length



           }

        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }

    if(direction2==RIGHT)//right
    {
        snake2_ycoordinate++;
        if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
        GameOvermulti();

        if(snake2_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
           snake2_ycoordinate=0;

           if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
            {
                food = 0;//for creating new food when snake surpasses the food
                score2+=5;//increasing the score when snake eats the food
                   snake2_tail -= 1;//for increasing snake length


           }

        snake2_head++;
        Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
    }

}

void snakemulti_movementhard()//in this function snakes dies by hitting all the four wall
{
    user_input = input_keyboard();//getting the input from the user and storing it
    //user_input = tolower(user_input);//converting the input in lower so that we donot worry about whether capslock is on or not


    if(((user_input=='w'||user_input=='a')||(user_input=='s'||user_input=='d')) && (abs(direction-user_input)>5))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
        {
        direction = user_input;
        }

   if(((user_input== UP||user_input==DOWN)||(user_input==RIGHT||user_input==LEFT)) && ((abs(direction2-user_input)!=2) && (abs(direction2-user_input)!=8) ))//we are using abs so that snake cannot go onto itself when user press the key(THAT IS If it is running in left direction it cannot move in right direction in the same line and vice versa)
   direction2 = user_input;


    if(direction=='w')//up
        {
            snake_xcoordinate--;
            if(Box[snake_xcoordinate][snake_ycoordinate]!=0 && Box[snake_xcoordinate][snake_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOvermulti();
                }
            if(snake_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
                {
                    GameOvermulti();
                }
            if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score1+=5;//increasing the score when snake eats the food
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
                    GameOvermulti();
                }
            if(snake_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
                {
                  GameOvermulti();
                }
            if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score1+=5;//increasing the score when snake eats the food
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
                    GameOvermulti();
                }
            if(snake_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
                {
                    GameOvermulti();
                }
            if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score1+=5;//increasing the score when snake eats the food
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
                    GameOvermulti();
                }
            if(snake_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
                {
                    GameOvermulti();
                }
           if(Box[snake_xcoordinate][snake_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score1+=5;//increasing the score when snake eats the food
                    snake_tail -= 1;//for increasing snake length
                }
                    snake_head++;
                    Box[snake_xcoordinate][snake_ycoordinate]= snake_head;
        }

        if(direction2==UP)//up
        {
            snake2_xcoordinate--;
            if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOvermulti();
                }
            if(snake2_xcoordinate==0)//if snake goes from the up side of the wall it comes from the down side of the wall
                {
                    GameOvermulti();
                }
            if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score2+=5;//increasing the score when snake eats the food
                    snake2_tail -= 1;//for increasing snake length
                }
                    snake2_head++;
                    Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
        }

    if(direction2==LEFT)//left
        {
            snake2_ycoordinate--;
            if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOvermulti();
                }
            if(snake2_ycoordinate==0)//if snake goes from the left side of the wall it comes from the right side of the wall
                {
                  GameOvermulti();
                }
            if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score2+=5;//increasing the score when snake eats the food
                    snake2_tail -= 1;//for increasing snake length
                }
                    snake2_head++;
                    Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
        }

    if(direction2==DOWN)//down
        {
            snake2_xcoordinate++;
            if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOvermulti();
                }
            if(snake2_xcoordinate==wall_row-1)//if snake goes from the down side of the wall it comes from the up side of the wall
                {
                    GameOvermulti();
                }
            if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score2+=5;//increasing the score when snake eats the food
                    snake2_tail -= 1;//for increasing snake length
                }
                    snake2_head++;
                    Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
        }

    if(direction2==RIGHT)//right
        {
            snake2_ycoordinate++;
            if(Box[snake2_xcoordinate][snake2_ycoordinate]!=0 && Box[snake2_xcoordinate][snake2_ycoordinate]!=-1) //in this we are checking that snake is on the food or not and or it is not on an empty space.if this satisfies the game should end because that means snake has eaten itself
                {
                    GameOvermulti();
                }
            if(snake2_ycoordinate==wall_column-1)//if snake goes from the right side of the wall it comes from the left side of the wall
                {
                    GameOvermulti();
                }
           if(Box[snake2_xcoordinate][snake2_ycoordinate]==-1)
                {
                    food = 0;//for creating new food when snake surpasses the food
                    score2+=5;//increasing the score when snake eats the food
                    snake2_tail -= 1;//for increasing snake length
                }
                    snake2_head++;
                    Box[snake2_xcoordinate][snake2_ycoordinate]= snake2_head;
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
void snaketailmulti_movement()//start of snaketail_movementfunction
{
    for(i=0;i<wall_row;i++)
        {
            for(j=0;j<wall_column;j++)
            {
                if(Box[i][j]==snake2_tail)//we are checking where the value is non zero and then e=we are setting it to 0
                    {
                        Box[i][j] = 0;
                    }
            }
        }
                        snake2_tail++;//we are incrementing the tail so that when snaketail_movemnt function is called it check for different value
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

gotoxy(50,1);
    printf("   GAME OVER !!!!!!");

    gotoxy(50,3);
    printf("   PLAYER SCORE : %d ",score);


    gotoxy(50,5);
    printf("   Press ENTER to play again or ESC to exit ... ");

    gotoxy(50,7);

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

void GameOvermulti()//some material that should occur when our game gets over
{
    printf("\a");//it will produce a beep sound indicating that our game is over
   Sleep(200);
    system("Cls");

    gotoxy(50,0);
    if(score1>score2)//comparing the score from the high score if  score is more than high score than we will update the value in the highscore file
        {
        printf(" PLAYER 1 WINS!!!!!!\n\n");
        }
    else if(score1<score2)
    {
     printf("PLAYER 2 WINS");
    }
    else if (score1==score2)
    {
     printf("MATCH DRAW");
    }


    gotoxy(50,1);
    printf("   GAME OVER !!!!!!");

    gotoxy(50,3);
    printf("   PLAYER 1 SCORE : %d ",score1);
    gotoxy(50,4);
    printf("   PLAYER 2 SCORE : %d ",score2);

    gotoxy(50,6);
    printf("   Press ENTER to play again or ESC to exit ... ");

    gotoxy(50,7);

    while(1)
    {
        user_input = input_keyboard();//taking input
        if(user_input == 13)//if user press enter the game will run again
            {
                score1=0;
                score2=0;
                game_over=0;
                system("Cls");
                gamemulti_level();
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

void gamemulti_level()//function for selecting game level
{
bold_red();
   gotoxy(50,12);
    printf("SELECT YOUR LEVEL");
        gotoxy(50,13);
        printf("1)EASY");
        gotoxy(50,14);
        printf("2)MEDIUM");
        gotoxy(50,15);
        printf("3)HARD");

         HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


                SetConsoleTextAttribute(hConsole, 480);
                bold_red();
        gotoxy(50,16);
    scanf("%d",&user_input);

    switch(user_input)
    {
        case 1:
            {//case 1 starts
                system("Cls");
                snakemulti_body();
    while(game_over==0)
    {
        printmulti();
        ResetScreenPosition();
        Food_creation();
        snakemulti_movementeasy();
        snaketail_movement();
        snaketailmulti_movement();
        Sleep(Speed); //this will increase this speed of snake
    }
            break;
            }//case 1 ends

         case 2:
            {//case 2 satarts
                system("Cls");
                snakemulti_body();
     while(game_over==0)
    {
        printmulti();
        ResetScreenPosition();
        Food_creation();
        snakemulti_movementmoderate();
        snaketailmulti_movement();
        Sleep(Speed); //this will increase this speed of snake

    }
            break;
            }//case 2 ends

   case 3:
            {//case 3 satarts
                system("Cls");
                snakemulti_body();
     while(game_over==0)
    {
        printmulti();
        ResetScreenPosition();
        Food_creation();
        snakemulti_movementhard();
        snaketailmulti_movement();
        Sleep(Speed); //this will increase this speed of snake

    }
            break;
            }//case 3 ends

   default:
    {
              gotoxy(50,16);
            printf("WRONG INPUT");
            gotoxy(50,17);
            printf("PRESS ENTER TO GO BACK");
            while(1)
    {
        user_input = input_keyboard();//taking input
        if(user_input == 13)//if user press enter the game will run again
            {
               gamemulti_details();
               gamemulti_level();
                break;
            }
        else if(user_input == 27)//if user press escape the game will end
                {

                    break;
                }
    }

    }
}
}
void game_details()//function for about the game
{

    system("Cls");

    gotoxy(30,1);
      bold_cyan();
        printf("Welcome to our snake game !!!!!!!!!!!!!!!!!!!\n");

        bold_green();
        gotoxy(50,2);
        printf("PLAYER 1");
         gotoxy(50,3);
         printf("CONTROLS : ");
          gotoxy(50,4);
          printf("W->UP");
              gotoxy(50,5);
          printf("A->LEFT");
              gotoxy(50,6);
          printf("S->DOWN");
              gotoxy(50,7);
          printf("D->RIGHT");
}
void gamemulti_details()//function for about the game
{
    system("Cls");
    gotoxy(30,1);
    bold_cyan();
        printf("Welcome to our snake game !!!!!!!!!!!!!!!!!!!\n");

    bold_green();
        gotoxy(50,2);
        printf("PLAYER 1");
         gotoxy(50,3);
         printf("CONTROLS : ");
          gotoxy(50,4);
          printf("W->UP");
              gotoxy(50,5);
          printf("A->LEFT");
              gotoxy(50,6);
          printf("S->DOWN");
              gotoxy(50,7);
          printf("D->RIGHT");

                gotoxy(70,2);
        printf("PLAYER 2");
         gotoxy(70,3);
         printf("CONTROLS : ");
          gotoxy(70,4);
          printf("ARROW UP->UP");
              gotoxy(70,5);
          printf("ARROW LEFT->LEFT");
              gotoxy(70,6);
          printf("ARROW DOWN->DOWN");
              gotoxy(70,7);
          printf("ARROW RIGHT->RIGHT");


}
void starting_screen(){
    system("Cls");
     red();
    gotoxy(50,10);
    printf("1)SINGLE PLAYER");
    gotoxy(50,11);
    printf("2)MULTIPLAYER");
    gotoxy(50,12);
    printf("3)HIGHSCORE TABLE");
    gotoxy(50,13);
    printf("4)QUIT");

    gotoxy(50,15);

    scanf("%d",&user_input);

    switch(user_input)
    {
    case 1:
       {
        game_details();
        game_level();
        break;
    }
    case 2:
    {
        gamemulti_details();
        gamemulti_level();
        break;
    }
    case 3:
        {
            printTableShape();
            gotoxy(60,30);
            printf("PRESS ENTER TO GOTO MAIN MENU");
            while(1)
    {
        user_input = input_keyboard();//taking input
        if(user_input == 13)//if user press enter the game will run again
            {
               main();
                break;
            }
        else if(user_input == 27)//if user press escape the game will end
                {

                    break;
                }
    }
            break;
        }
    case 4:
        {
            system("Cls");
            gotoxy(50,15);
            printf("THANK YOU FOR PLAYING");
            break;
        }
    default:
        {
            system("Cls");
            gotoxy(50,15);
            printf("WRONG INPUT");
            gotoxy(50,16);
            printf("PRESS ENTER TO GOTO MAIN MENU");
            while(1)
    {
        user_input = input_keyboard();//taking input
        if(user_input == 13)//if user press enter the game will run again
            {
               main();
                break;
            }
        else if(user_input == 27)//if user press escape the game will end
                {

                    break;
                }
    }

            break;
        }
        }
        }

void loading_screen(){
        int r,q;

        gotoxy(50,10);

        //red();
        printf("LOADING.............");
        gotoxy(50,12);
        for(r=1;r<=20;r++)
        {
            for(q=0;q<=100000000;q++);

            printf("%c",177);
        }
        }

void timer(){
int hour=0,min=0,sec=0;

while(TRUE)
{
    printf("\rTIME: %2d:%2d:%2d",hour,min,sec);
   sec++;
    Sleep(1000);
    if(sec==59){
        min++;
        sec=0;
    }
    if(min==59)
    {
        hour++;
        min=0;
        sec=0;
    }
    if(hour==24)
    {
        hour=0;
        sec=0;
        min=0;
    }

    }
    return 0;
}

void red () {
  printf("\033[1;31m");
}
void bold_yellow() {
  printf("\033[1;33m");
}
void bold_red() {
  printf("\033[1;31m");
}
void green() {
  printf("\033[0;32m");
}
void bold_green() {
  printf("\033[1;32m");
}
void yellow() {
  printf("\033[0;33m");
}
void blue() {
  printf("\033[0;34m");
}
void bold_blue() {
  printf("\033[1;34m");
}
void magenta() {
  printf("\033[0;35m");
}
void bold_magenta() {
  printf("\033[1;35m");
}
void cyan() {
  printf("\033[0;36m");
}
void bold_cyan() {
  printf("\033[1;36m");
}


void printTableShape() {




                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  system("cls");
                  SetConsoleTextAttribute(hConsole, 480);        //Yellow Color Code=480
                  gotoxy(25,0);
                  printf("   High Score Table   ");
                  printf("\n");
                  SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
                  gotoxy(21,1);
                  printf("      Top Fifteen Scores      ");
                  SetConsoleTextAttribute(hConsole, 47);             //Gray Color Code=8
                  gotoxy(15,4);
                  printf("\xDA");
                  for (int i=16; i<57; i++) {                //First Line 15
                      gotoxy(i,4);                           //Middle Line 39
                     printf("\xC4");                          //Last Line 57
                  }                                          //Second Line 20
                  printf("\xBF");
                  gotoxy(20,4); printf("\xC2");
                  gotoxy(39,4); printf("\xC2");
                  gotoxy(15,5); printf("\xB3");
                  gotoxy(20,5); printf("\xB3");
                  gotoxy(39,5); printf("\xB3");
                  gotoxy(57,5); printf("\xB3");
                  gotoxy(15,6); printf("\xC3");
                  for (int i=16; i<57; i++) {
                      gotoxy(i,6);
                      printf("\xC4");
                  }
                  gotoxy(39,6); printf("\xC5");
                  gotoxy(20,6); printf("\xC5");
                  gotoxy(57,6); printf("\xB4");
                  for (int i=7; i<23; i++) {
                      gotoxy(15,i); printf("\xB3");
                      gotoxy(20,i); printf("\xB3");
                      gotoxy(39,i); printf("\xB3");
                      gotoxy(57,i); printf("\xB3");
                  }
                  gotoxy(15,22); printf("\xC0");
                  for (int i=16; i<57; i++) {
                      gotoxy(i,22);
                     printf("\xC4");
                  }
                  gotoxy(39,22); printf("\xC1");
                  gotoxy(20,22); printf("\xC1");
                  gotoxy(57,22); printf("\xD9");
                  SetConsoleTextAttribute(hConsole, 14);    //Yellow Color Code=14
                  gotoxy(28,5); printf("Name");
                  gotoxy(46,5); printf("Score");
                  gotoxy(17,5); printf("S.NO");
             }
int main()//main function
{

              HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
               system("cls");

                SetConsoleTextAttribute(hConsole, 480);

   loading_screen();
    starting_screen();

}
