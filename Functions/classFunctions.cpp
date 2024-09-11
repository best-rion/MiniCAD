#include "../classHeader.h"


bool MouseOnce::isPressed()
{
    if( Mouse::isButtonPressed(Mouse::Left) && is_not_pressed){
        is_not_pressed = false;
        return true;
    }else if(!Mouse::isButtonPressed(Mouse::Left)){
        is_not_pressed = true;
        return false;
    }
    else{
        return false;
    }
}


bool EscKeyOnce::isPressed()
{
    if( Keyboard::isKeyPressed(Keyboard::Escape) && is_not_pressed){
        is_not_pressed = false;
        return true;
    }else if(!Keyboard::isKeyPressed(Keyboard::Escape)){
        is_not_pressed = true;
        return false;
    }
    else{
        return false;
    }
}



VertexPoint::VertexPoint()
{
    VertexPoint::setFillColor(Color(100,255,255));
    VertexPoint::setRadius(radius);
    VertexPoint::setPointCount(4);
}

void VertexPoint::change_fillColor(Color color){
    this->setFillColor(color);
}

void VertexPoint::draw_me(RenderWindow &window)
{
    this->setPosition( position - Vector2f(radius,radius) );
    window.draw(*this);
}


void Line::draw_me(RenderWindow &window)
{
    // Drawing line
    window.draw(endPoint,2,Lines);
}




void DottedLine::draw_me(RenderWindow &window)
{

    float d = dist(p1,p2);

    float xd = (p2.x-p1.x)*dot_size/d;
    float yd = (p2.y-p1.y)*dot_size/d;

    float fnum = d/dot_size; // Number of lines and spaces in float

    int inum = (int) fnum; // Number of lines and spaces in integer

    line[0].color = Color(Color(255,255,255,180));
    line[1].color = Color(Color(255,255,255,180));


    if(inum%2==1){

        for(int i=0; i<inum; i++){

            if(i%2==0){

                line[0].position.x = p1.x + xd *  i    ;
                line[0].position.y = p1.y + yd *  i    ;

                line[1].position.x = p1.x + xd * (i+1) ;
                line[1].position.y = p1.y + yd * (i+1) ;

                window.draw(line,2,Lines);
            }
        }

    }else{

        for(int i=0; i<inum+1; i++){

            if(i%2==0){

                line[0].position.x = p1.x + xd *  i    ;
                line[0].position.y = p1.y + yd *  i    ;

                line[1].position.x = p1.x + xd * (i+1) ;
                line[1].position.y = p1.y + yd * (i+1) ;

                if(i==inum){
                    line[1].position.x = p2.x;
                    line[1].position.y = p2.y;
                }

                window.draw(line,2,Lines);
            }
        }
    }
}


// class Icon

    void Icon::set_bg(){
        bg.setSize(Vector2f(rect_size,rect_size));
        bg.setPosition( position - Vector2f(rect_size/2,rect_size/2) );
        bg.setOutlineColor(Color(50,50,50));
        bg.setOutlineThickness(1);
    }

    Icon::Icon(Vector2f pos, string filename, int icon_num){


        position = pos;
        icon_number = icon_num;



        // Setting Image
        Image image;
        image.loadFromFile(filename);

        texture.loadFromImage(image);

        Vector2f scale;

        scale.x = icon_size / image.getSize().x;
        scale.y = icon_size / image.getSize().y;

        this->setTexture(texture);
        this->setPosition( position - Vector2f(icon_size/2,icon_size/2) );
        this->setScale(scale);

        // Setting background

        set_bg();
    }


    void Icon::check_cursor(){
        if( abs( cursor_position.x - position.x) < rect_size/2 && abs( cursor_position.y - position.y) < rect_size/2 ){

            // Changing "Capture" icon color when clicked
            if( icon_number == 2){

                if( Mouse::isButtonPressed(Mouse::Left) ){
                    bg.setOutlineColor( Color(255,255,255) );
                }else{
                    bg.setOutlineColor( Color(0,0,0) );
                }
            }


            if( mouse.isPressed() ){

                if(!pressedAlready){

                    for(int i=0; i<3; i++){

                        if(i!=icon_number){

                            icon_active[i] = false;

                        }else{

                            icon_active[icon_number] = true;
                            pressedAlready = true;
                        }
                    }
                }else{

                    icon_active[icon_number] = false;
                    pressedAlready = false;
                }
            }

        }
    }
    void Icon::draw_me(RenderWindow &window){

        if( icon_active[icon_number] ){
            bg.setFillColor(Color(100,100,100));
        }else{
            this->pressedAlready = false; // If it is not active, it means it is not pressed anymore
            bg.setFillColor(Color(255,255,255));
        }

        check_cursor();
        window.draw(bg);
        window.draw(*this);
    }





// class MyCircle

    MyCircle::MyCircle(){

        MyCircle::setFillColor(Color(0,0,0,0));
        MyCircle::setOutlineColor(Color::White);
        MyCircle::setOutlineThickness(1.f);
    }

    void MyCircle::draw_me(RenderWindow &window){

        // Drawing central plus

        line1[0].position.x = center.x - 10;
        line1[0].position.y = center.y;
        line1[1].position.x = center.x + 10;
        line1[1].position.y = center.y;

        line2[0].position.x = center.x;
        line2[0].position.y = center.y - 10;
        line2[1].position.x = center.x;
        line2[1].position.y = center.y + 10;

        window.draw(line1,2,Lines);
        window.draw(line2,2,Lines);

        // Drawing circle

        this->setPosition( center - Vector2f( this->getRadius(), this->getRadius() ) );
        window.draw(*this);
    }




