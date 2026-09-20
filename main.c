#include<raylib.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

const int SCREENWIDTH = 1200;
const int SCREENHEIGHT = 950;
int speedFactor =3;
int bulletspeedFactor=4;
Vector2 shipPosition = {(float)((SCREENWIDTH/2)-80), (float)((SCREENHEIGHT/2)-120)};
float rotation=0.0f;

Rectangle sourceRec = {0.0f, 0.0f, 800.0f, 600.0f};   
Vector2 origin = {40.0f, 30.0f};
Vector2 shipVelocity;

int randomInt(int min,int max);
void moveShip(void);
void bulletLogic(void);
float getRotation(void);
Vector2 asteroidSpawnLogic(void);
void asteroidGenerator(void);


typedef enum{
    large,
    mid,
    small
    
}asteroidSize;

typedef struct{
    Vector2 position;
    Vector2 velocity;
    float bulletRotation;
    bool active;
    
}Bullet;

typedef struct{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    bool active;
    asteroidSize size;
}Asteroid;



Bullet bullets[10000];
Asteroid asteroids[1000];
int bulletIndex=0;
int asteroidIndex=0;

int main(void) {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib test");
    Texture2D spaceship = LoadTexture("resources/spaceship.png");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        Rectangle destRec = {shipPosition.x, shipPosition.y, 80.0f, 60.0f};
        // Rectangle bulletRec={bulletPosition.x, bulletPosition.y, 10.0f, 10.0f};

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(spaceship, sourceRec, destRec, origin, rotation, WHITE);
            // DrawRectanglePro(destRec, YELLOW);
            if (bulletIndex>=1){
                for(int i=0;i<=bulletIndex;i++){
                    Rectangle rectBullet={bullets[i].position.x,bullets[i].position.y,10,6};
                    Vector2 originBullet={5,3};
                    DrawRectanglePro(rectBullet,originBullet,bullets[i].bulletRotation,RED);
                    printf("%d",bulletIndex);
                }
            }
        EndDrawing();
        //update
 
        moveShip();
        rotation = getRotation();
        shipPosition.x = cos(rotation * DEG2RAD) * speedFactor + shipPosition.x;
        shipPosition.y = (sin(rotation * DEG2RAD) * speedFactor) + shipPosition.y;
        for(int i=0;i<=bulletIndex;i++){
                // Vector2 bulletPosition = {shipPosition.x + (sourceRec.width/2)*cos(rotation * DEG2RAD),shipPosition.y + (sourceRec.height/2)*(sin(rotation * DEG2RAD))};
                // Vector2 bulletDirection={(cos(rotation * DEG2RAD)),(sin(rotation * DEG2RAD))};
                bullets[i].position.x+= bulletspeedFactor*bullets[i].velocity.x;
                bullets[i].position.y+= bulletspeedFactor*bullets[i].velocity.y;

        }


        // printf("x: %f, y: %f, rotation: %f,     %f ,     %F \n", shipPosition.x, shipPosition.y, rotation,cos(rotation * DEG2RAD) , sin(rotation * DEG2RAD) );
        

        
        
        //draw

    }
    UnloadTexture(spaceship);
    CloseWindow();
    return 0;
}

void moveShip(void){

        if(IsKeyDown(KEY_Q)) {
            rotation -= speedFactor;
        }
        if(IsKeyDown(KEY_E)) {
            rotation += speedFactor;
        }
       

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            printf("hi");
            bulletLogic();
        }

}

float getRotation(void) {
    if (rotation > 360.0f) {
        rotation -= 360.0f;
    } else if (rotation < 0.0f) {
        rotation += 360.0f;
    }
    return rotation;
}

void bulletLogic(){
    //bullet will spawn at the tip of the ship and move in the direction the ship is facing
    //get the position of the tip of the ship
    Vector2 bulletPosition = {shipPosition.x + (120/2)*cos(rotation * DEG2RAD),shipPosition.y + (90/2)*(sin(rotation * DEG2RAD)) };
    Vector2 bulletDirection={(cos(rotation * DEG2RAD)),(sin(rotation * DEG2RAD))};
    bullets[bulletIndex].position=bulletPosition;
    bullets[bulletIndex].active=true;
    bullets[bulletIndex].bulletRotation=rotation;
    bullets[bulletIndex].velocity=bulletDirection;
    bulletIndex+=1;
    printf("Bullet Index : %d",bulletIndex);
}



int randomInt(int min, int max){
    srand(time(NULL));
    int min = 1;
    int max = 100;
    int random = (rand() % (max - min + 1)) + min; 
    return random;



}

// Vector2 asteroidGenerator()
Vector2 asteroidSpawnLogic(void){

    //posiiton
    int x=shipPosition.x;
    int y=shipPosition.y;

    int randX = randomInt(80,SCREENWIDTH-80);
    int randY = randomInt(80,SCREENHEIGHT-80);
    
    bool end=true;
    while (end){
        int distance=sqrt((x-randX)*(x-randX) + (y-randY)*(y-randY));
        int max2;
        if (distance<180){
            if (randY-100 >=50){
                int max2=-50;
                
            }
            else{
                int max2=+50;
            }
            randY=randomInt(1,randY+max2);
        }
        else{
            end=false;
        }
    }

    

    return (Vector2){randX,randY};
}

void asteroidGenerator(){
    
    Vector2 asteroidPosition=asteroidSpawnLogic();
    asteroids[asteroidIndex].rotation=randomInt(0,360) ;
    Vector2 asteroidDirection= {(cos(asteroids[asteroidIndex].rotation) * DEG2RAD),(sin(asteroids[asteroidIndex].rotation))};
    asteroids[asteroidIndex].position=asteroidPosition;
    asteroids[asteroidIndex].velocity=asteroidDirection;
    asteroids[asteroidIndex].size=randomInt(0,2);
    asteroids[asteroidIndex].active=true;
    asteroidIndex+=1;
    printf("Asteroid Index : %d",asteroidIndex);


}
