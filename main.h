#include<chrono>
#include "raylib.h"
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<string>
using namespace std;
#include<iostream>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


class player
{
private:
    float xAxis;
    float yAxis;
public:
  player( float xcoordinate = 0,float ycoordinate=0){
    if (xAxis<=0 && yAxis<=0){
        xAxis = xcoordinate;
        yAxis = ycoordinate;}
  };
  
  player shoot(float velocity, float angle, float time,player initialP );
  void drawTank(int x, int y);
  

    friend std::ostream& operator<<(std::ostream& os, const player& player) {
      os << "(" + to_string(player.xAxis) + ", " + to_string(player.yAxis) + ")";
      return os;
    }

    void hitPlayerCheck(float deltaTime, player target);
    //void drawTankBarrel(int x, int y);
    void drawTankBarrel(Vector2 position, float angleDegrees);
    bool operator<(const player& other) const {
        return (xAxis < other.xAxis) || (xAxis == other.xAxis && yAxis < other.yAxis);
    }
    bool operator>(const player& other) const {
        return (xAxis > other.xAxis) || (xAxis == other.xAxis && yAxis > other.yAxis);
    }
    float getXAxis(){return xAxis;};
    float getYAxis(){return yAxis;};
    
    
   
};
static inline float Dist2(Vector2 a, Vector2 b) {
    float dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}
struct Projectile{
  Vector2 pos{0,0};
  Vector2 vel{0,0};
  bool alive = false;
};

static inline Vector2 Rotate(Vector2 v, float rads){
  return{v.x * cosf(rads) - v.y * sinf(rads), v.x * sinf(rads) + v.y * cosf(rads)};
}

struct Target{
  float radius = 30.0f;
  int x = 0;
  int y = 0;
  void drawtarget(){
    DrawCircle(x,y,radius,RED);
    DrawCircle(x,y,radius - 5,WHITE);
    DrawCircle(x,y,radius - 10,RED);
    DrawCircle(x,y,radius - 15,WHITE);
    DrawCircle(x,y,radius - 20, RED);
    DrawCircle(x,y,radius - 22,WHITE);
    DrawCircle(x,y, radius - 23, RED);
  }

  
};

void drawLandScape(){
  ClearBackground(BLUE);
  DrawRectangle(0,500,1200,100,ORANGE);
  DrawCircle(0,0,75,YELLOW);
  
  
}

void player::drawTank(int xVertice, int yVertice){

DrawRectangle(xVertice,yVertice,120,50,DARKGREEN);
DrawRectangle(xVertice + 10,yVertice - 20,50,40,DARKGREEN);
Vector2 vertex1 = {xVertice + 60, yVertice - 20};
Vector2 vertex2 = {xVertice + 60,yVertice + 20};
Vector2 vertex3 = {xVertice + 120,yVertice + 20};
DrawTriangle(vertex1,vertex2,vertex3,DARKGREEN);
DrawCircle(xVertice + 20,yVertice + 50,20,BLACK);
DrawCircle(xVertice + 60,yVertice + 50,20,BLACK);
DrawCircle(xVertice + 100,yVertice + 50,20,BLACK);
}

/*void drawTankBarrel(int x, int y){
  DrawRectangle(x + 65,y-10,20,DARKGREEN);
}*/

void player:: drawTankBarrel(Vector2 position, float angleDegrees) {
    // Barrel dimensions
    Vector2 size = {120, 20};               // width x height
    Vector2 origin = {0, size.y / 2};       // hinge on left-center

    // Draw the rotated barrel
    DrawRectanglePro({position.x, position.y, size.x, size.y}, origin, angleDegrees, DARKGREEN);
}
int changeTargetPositionX(target& target){

int xMin = 425;
int xMax = 1175;

int xRandomNumber = (rand() % (xMax - xMin + 1 )) + xMin;
return xRandomNumber;
}

static int RandRangeInt(int lo, int hiInclusive) {
    return lo + (std::rand() % (hiInclusive - lo + 1));
}











