#include "firstHeader.h"

const unsigned int trh = 80; // Top Rectangle Height
bool icon_active[3] = {false,false,false}; // Used as extern
float zoom = 0.1;
Vector2f cursor_position; // Used as extern


int main()
{   tangent_vertex.setFillColor(Color::Yellow);

    Font font;
    Text cursor_pos_text;
    set_font(cursor_pos_text, font);

    // Creating window and setting logo
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "MiniCAD");
    Image logo;
    logo.loadFromFile("logo.png");
    window.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
    //



    // CURSOR PLUS PLUS

    Cursor myCursor;
    Vector2u cursorSize(cursor_x,cursor_y);
    Uint8 myCursorPixels[cursor_x*cursor_y*4];
    set_cursor_pixels(myCursorPixels);
    myCursor.loadFromPixels(myCursorPixels, cursorSize, {cursor_x/2, cursor_y/2});

    Cursor default_cursor;
    default_cursor.loadFromSystem(Cursor::Arrow);
    //



    // Setting Top Background with Gradient

    Color top(75,90,105);
    Color bottom(40,45,50);
    Vertex top_rectangle[] =
    {
        Vertex( Vector2f(0,0) , top ),
        Vertex( Vector2f(WIDTH,0) , top ),
        Vertex( Vector2f(WIDTH,trh) , bottom ),
        Vertex( Vector2f(0,trh) , bottom )
    };

    // Setting Icons

    Icon icon1(Vector2f(50,trh/2), "Icons/circle.png", 0),
         icon2(Vector2f(120,trh/2), "Icons/line.png", 1),
         icon3(Vector2f(190,trh/2), "Icons/camera.png", 2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseWheelScrolled)
            {
                float sign =  event.mouseWheelScroll.delta ;
                scale = pow(2,sign*zoom);
                Vector2f cursor = Vector2f(event.mouseWheelScroll.x,event.mouseWheelScroll.y);

                zoom_point(0,   points_count,   cursor);
                zoom_point(50,  m_points_count, cursor);
                zoom_point(100, c_points_count, cursor);

                zoom_line( cursor );

                zoom_circle( cursor );

                zoom_temp_line( cursor );

                zoom_temp_circle( cursor );
            }
        }


        // Getting cursor's position
        cursor_position = Vector2f( Mouse::getPosition(window) );

        reset_line();

        reset_circle();

        // Click should only affect region inside window
        if(    (cursor_position.x>0 && cursor_position.x<WIDTH)
            && (cursor_position.y>trh && cursor_position.y<HEIGHT)
        )
        {


            // Cursor Plus
                window.setMouseCursor(myCursor);
            //


            cursor_text( Vector2i(cursor_position) , cursor_pos_text );

            // BRINGING cursor closer to point
            close_point();

            making_d_line();
            making_line();

            making_circle();
        }else{
            window.setMouseCursor(default_cursor);
        }




        window.clear(Color(20,25,30));

        // Show cursor coordinates if on the drawing portion of the window

        if( (cursor_position.x>0 && cursor_position.x<WIDTH) && (cursor_position.y>trh && cursor_position.y<HEIGHT) )
            window.draw(cursor_pos_text);

        drawing_line(window);
        drawing_d_line(window);

        drawing_circle(window);


        draw_points(window);

        window.draw(top_rectangle, 4, Quads);
        icon1.draw_me(window);
        icon2.draw_me(window);
        icon3.draw_me(window);

        window.display();

        // Saving the drawing as image
        save_drawing(window);

    }

    return 0;
}
