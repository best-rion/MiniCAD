#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#define WIDTH  1200
#define HEIGHT 800

using namespace sf;using namespace std;


extern Vector2f cursor_position;
extern bool icon_active[3];

float dist(Vector2f p1, Vector2f p2);


class MouseOnce{
public:
    bool is_not_pressed = true;
    bool isPressed();
};


class EscKeyOnce{
public:
    bool is_not_pressed = true;
    bool isPressed();
};



class VertexPoint: public CircleShape{
private:
    float radius = 4;
public:
    Vector2f position;
    bool hovering = false;

    VertexPoint();
    void change_fillColor(Color color);
    void draw_me(RenderWindow &window);

};


class Line{
public:

    Vertex endPoint[2];

    void draw_me(RenderWindow &window);
};



class DottedLine{

private:

    float dot_size = 5;

    Vertex line[2];

public:

    Vector2f p1,p2;

    bool exists = false;

    void draw_me(RenderWindow &window);
};




class Icon: public Sprite{

private:

    float icon_size = 30;
    float padding = 5;
    float rect_size = icon_size+2*padding;
    Texture texture;
    RectangleShape bg;
    bool pressedAlready = false;
    MouseOnce mouse;

public:

    Vector2f position = Vector2f(0,0);

    int icon_number;

    void set_bg();

    Icon(Vector2f pos, string filename, int icon_num);

    void check_cursor();

    void draw_me(RenderWindow &window);
};


class MyCircle: public CircleShape{

private:

    Vertex line1[2];
    Vertex line2[2];

public:

    Vector2f center;

    MyCircle();

    void draw_me(RenderWindow &window);

};

