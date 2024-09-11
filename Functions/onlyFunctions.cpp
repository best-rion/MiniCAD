#include "../firstHeader.h"

using namespace sf; using namespace std;


VertexPoint points[150];
unsigned int points_count = 0;
unsigned int m_points_count = 50;
unsigned int c_points_count = 100;



// d_line Variables
short selected_point[2];
short next_point_to_select = 0;
short selected_count = 0;

clock_t starting, ending;
//



float dist(Vector2f p1, Vector2f p2){ return sqrt( pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2) ); }


void cursor_text(Vector2i position, Text &text){
    string position_x = to_string(position.x);
    string position_y = to_string(position.y);
    string position_string = "(" + position_x + "," + position_y + ")";

    text.setString(position_string);
    text.setPosition(Vector2f(position.x+15,position.y+20));
}



void set_font(Text &cursor_pos_text, Font &font){

    font.loadFromFile("arial.ttf");
    cursor_pos_text.setCharacterSize(12);
    cursor_pos_text.setFont(font);
}




// line Variables

unsigned int num_of_lines = 0;// used as extern
Line line[50];
MouseOnce mouse_line;
EscKeyOnce esc_key_line;
Vertex temp_line[2]; // Sticky Line


unsigned int closest_circle;

bool first_endpoint_has_been_clicked = false,
     second_endpoint_has_been_clicked = false;
void set_line_to_default(){
    first_endpoint_has_been_clicked = false;
    second_endpoint_has_been_clicked = false;
}


void making_line(){

    Vector2f line_position = cursor_position;

    if ( mouse_line.isPressed() && icon_active[1] )
    {


        // ORTHOGONAL LINE
        for(int i=0; i<selected_count; i++){

            if( abs(cursor_position.x - points[ selected_point[i] ].position.x) <= 50 ){
                line_position.x = points[ selected_point[i] ].position.x;
            }
            if( abs(cursor_position.y - points[ selected_point[i] ].position.y) <= 50 ){
                line_position.y = points[ selected_point[i] ].position.y;
            }

        }//


        if( first_endpoint_has_been_clicked  ){

            line[num_of_lines].endPoint[0].position = temp_line[0].position;

            // Tangent point HERE
            TanReturn tan_point;
            tan_point = tangent_point( line[num_of_lines].endPoint[0].position, closest_circle );
            if(tan_point.is_close){
                line_position = tan_point.point;
            }   //

            line[num_of_lines].endPoint[1].position = line_position;

            // Adding Middle point
            points[m_points_count].position.x =
                            (line[num_of_lines].endPoint[0].position.x
                           + line[num_of_lines].endPoint[1].position.x) / 2;

            points[m_points_count].position.y =
                            (line[num_of_lines].endPoint[0].position.y
                           + line[num_of_lines].endPoint[1].position.y) / 2;

            points[m_points_count].change_fillColor(Color(0,255,0));
            m_points_count++;     //

            num_of_lines++;

            second_endpoint_has_been_clicked = true;
        }

        temp_line[0].position = line_position;
        first_endpoint_has_been_clicked = true;

        // Always select the first point

            selected_point[next_point_to_select] = points_count;

            next_point_to_select++;
            if(next_point_to_select==2){next_point_to_select=0;}

            selected_count++;
            if(selected_count>2){selected_count=2;}
        //
        // Adding end-point to show the VertexPoint
        points[points_count].position = line_position;
        points_count++;
                //
    }

}


void reset_line(){
    if( esc_key_line.isPressed() ){

        if(!second_endpoint_has_been_clicked){
            points_count--;
        }
        set_line_to_default();

        // Reset d_line
        next_point_to_select = 0;
        selected_count = 0;
        //
    }
}

void drawing_line(RenderWindow &window){

    if(first_endpoint_has_been_clicked){ // Drawing Sticky Line
        temp_line[1].position = cursor_position;
        window.draw(temp_line,2,Lines);
    }

    for(int i=0; i<num_of_lines; i++){
        line[i].draw_me(window);
    }
}



void making_d_line_template(unsigned short low, unsigned short high){

    for(int i=low; i<high; i++){ // HIGH is Points count

        if(  dist(cursor_position ,points[i].position) <= 20  && !points[i].hovering /* so that it doesn't restart clock with every frame */ ){

            points[i].hovering = true;

            starting = clock();
        }

        if( dist(cursor_position ,points[i].position) > 20 && points[i].hovering){

            points[i].hovering = false;

            ending = clock();
            double time_taken = (double)(ending - starting)/ double(CLOCKS_PER_SEC);


            bool already_selected=false; // Checking if already selected
            for( unsigned short j=0; j<selected_count; j++){
                if(selected_point[j] == i ){
                    already_selected = true;
                }
            }

            if( time_taken > 1 && !already_selected ){

                selected_point[next_point_to_select] = i;

                next_point_to_select++;
                if(next_point_to_select==2){next_point_to_select=0;}

                selected_count++;
                if(selected_count>2){selected_count=2;}

            }

        }

    }
}


void making_d_line(){

    making_d_line_template(0,points_count);

    // Middle_point

    making_d_line_template(50,m_points_count);

    // Circles_point

    making_d_line_template(100,c_points_count);
}

DottedLine d_line[2][2];

void drawing_d_line_template(RenderWindow &window, unsigned short low, unsigned short high){

    for(int i=0; i<selected_count; i++){

        if( abs(cursor_position.x - points[ selected_point[i] ].position.x) < 50 ){

            d_line[i][0].p1 = points[ selected_point[i] ].position;
            d_line[i][1].p1 = points[ selected_point[i] ].position;

            d_line[i][0].p2.x = points[ selected_point[i] ].position.x;

            d_line[i][0].p2.y = cursor_position.y;
            d_line[i][0].draw_me(window);
        }

        if( abs(cursor_position.y - points[ selected_point[i] ].position.y) < 50 ){

            d_line[i][0].p1 = points[ selected_point[i] ].position;
            d_line[i][1].p1 = points[ selected_point[i] ].position;

            d_line[i][1].p2.y = points[ selected_point[i] ].position.y;

            d_line[i][1].p2.x = cursor_position.x;
            d_line[i][1].draw_me(window);
        }

    }
}

void drawing_d_line(RenderWindow &window){

    drawing_d_line_template(window,0,points_count);

    // Middle points

    drawing_d_line_template(window,50,m_points_count);

    // Circle points

    drawing_d_line_template(window,100,c_points_count);

}



// Making Circle


unsigned int num_of_circles = 0;
MyCircle circle[50];
MouseOnce mouse_circle;
EscKeyOnce esc_key_circle;
MyCircle temp_circle;


bool  temp_circle_has_been_clicked = false;

void set_circle_to_default(){

    temp_circle_has_been_clicked = false;

}

void making_circle(){
    if ( mouse_circle.isPressed() && icon_active[0]  )
    {
        Vector2f circle_position = cursor_position;

        if( !temp_circle_has_been_clicked ){

            // ORTHOGONAL LINE

            for(int i=0; i<selected_count; i++){
                if( abs(cursor_position.x - points[ selected_point[i] ].position.x) <= 50 ){
                    circle_position.x = points[ selected_point[i] ].position.x;
                }
                if( abs(cursor_position.y - points[ selected_point[i] ].position.y) <= 50 ){
                    circle_position.y = points[ selected_point[i] ].position.y;
                }

            }

            temp_circle.center = circle_position;

            temp_circle_has_been_clicked = true;

        }else{

            float perm_radius = dist(cursor_position, temp_circle.center);

            // Adding center-point to show the VertexPoint
            points[points_count].position = temp_circle.center;
            points_count++;
            //

            // Adding top-point to show the VertexPoint
            points[c_points_count].position =
                            Vector2f(temp_circle.center.x,temp_circle.center.y - perm_radius) ;
            points[c_points_count].change_fillColor(Color(250, 35, 35));
            c_points_count++;
            //

            // Adding right-point to show the VertexPoint
            points[c_points_count].position =
                            Vector2f(temp_circle.center.x + perm_radius,temp_circle.center.y) ;
            points[c_points_count].change_fillColor(Color(250, 35, 35));
            c_points_count++;
            //

            // Adding bottom-point to show the VertexPoint
            points[c_points_count].position =
                            Vector2f(temp_circle.center.x,temp_circle.center.y + perm_radius) ;
            points[c_points_count].change_fillColor(Color(250, 35, 35));
            c_points_count++;
            //

            // Adding left-point to show the VertexPoint
            points[c_points_count].position =
                            Vector2f(temp_circle.center.x - perm_radius,temp_circle.center.y) ;
            points[c_points_count].change_fillColor(Color(250, 35, 35));
            c_points_count++;
            //


            circle[num_of_circles].center = temp_circle.center;
            circle[num_of_circles].setRadius( perm_radius );
            num_of_circles++;

            temp_circle_has_been_clicked = false;
        }

    }

}


void reset_circle(){
    if( esc_key_circle.isPressed() ){

        if( temp_circle_has_been_clicked ){
            set_circle_to_default();
        }

    }
}


void drawing_circle(RenderWindow &window){

    if(temp_circle_has_been_clicked){
        temp_circle.setRadius( dist(cursor_position, temp_circle.center) );
        temp_circle.draw_me(window);
    }

    for(int i=0; i<num_of_circles; i++){
        circle[i].draw_me(window);
    }
}


TanReturn tangent_point(Vector2f p, int circle_index){

    float x1 = p.x;
    float y1 = p.y;
    float h  = circle[circle_index].center.x;
    float k  = circle[circle_index].center.y;
    float r  = circle[circle_index].getRadius();
    float X1  = x1-h;
    float Y1  = y1-k;


    Vector2f tp[2]; // 2 tangent points

    float C0 = X1*X1+Y1*Y1;
    float C1 = sqrt(C0-r*r);


    tp[0].x = ( X1*r*r + Y1*r*C1) / C0 + h;
    tp[0].y = ( Y1*r*r - X1*r*C1) / C0 + k;

    // Tangent point number 2

    tp[1].x = ( X1*r*r - Y1*r*C1) / C0 + h;
    tp[1].y = ( Y1*r*r + X1*r*C1) / C0 + k;

    TanReturn tr;

    bool not_close = true;

    for(int i=0; i<2; i++){
        if( dist( cursor_position , tp[i] ) < 30 ){
            tr.point =  tp[i];
            not_close = false; // The cursor is indeed close
        }
    }

    tr.is_close = !not_close;

    return tr;
}


TanReturn ctp; // It is a property of line
VertexPoint tangent_vertex;


void check_closest_tan_point(RenderWindow &window){

    if( !temp_circle_has_been_clicked ){

        closest_circle = 0;

        ctp = tangent_point(temp_line[0].position , closest_circle);

        for(int j=1; j<num_of_circles; j++){

            TanReturn ttp = tangent_point(temp_line[0].position , j); // Temporary Tangent Point

            if( ttp.is_close && !ctp.is_close ){ // Cursor is close to another circle

                    closest_circle = j;
                    ctp = ttp;
            }

            else if(ttp.is_close && ctp.is_close){ // Cursor is close to both

                if( dist(cursor_position , ttp.point) < dist(cursor_position , ctp.point)){ // Which is closer

                    closest_circle = j;
                    ctp = ttp;
                }
            }
        }

        if(ctp.is_close){
            tangent_vertex.position = ctp.point;
            tangent_vertex.draw_me(window);
        }

    }

}



void save_drawing(RenderWindow &window){

    if(icon_active[2]){

        icon_active[2] = false;

        Texture drawing_texture;

        drawing_texture.create(WIDTH, HEIGHT);

        drawing_texture.update(window);

        Image drawing_image = drawing_texture.copyToImage();

        drawing_texture.loadFromImage(drawing_image,IntRect(0,trh,WIDTH,HEIGHT-trh)); // To crop the upper section

        drawing_image = drawing_texture.copyToImage();

        drawing_image.saveToFile("Drawings/Drawing.jpg");
    }
}

float scale;

void zoom_point(unsigned short low, unsigned short high, Vector2f cursor){

        for(int j=low; j<high; j++){

            Vector2f del;

            del.x = points[j].position.x - cursor.x;
            del.y = points[j].position.y - cursor.y;

            del.x *= scale;
            del.y *= scale;

            points[j].position.x = cursor.x + del.x;
            points[j].position.y = cursor.y + del.y;
        }
}



void zoom_line( Vector2f cursor){

    for(int j=0; j<num_of_lines; j++){
        for(int i=0; i<2; i++){

            Vector2f del;

            del.x = line[j].endPoint[i].position.x - cursor.x;
            del.y = line[j].endPoint[i].position.y - cursor.y;

            del.x *= scale;
            del.y *= scale;

            line[j].endPoint[i].position.x = cursor.x + del.x;
            line[j].endPoint[i].position.y = cursor.y + del.y;
        }
    }

}


void zoom_circle( Vector2f cursor){

    for(int j=0; j<num_of_circles; j++){

        Vector2f del;

        del.x = circle[j].center.x - cursor.x;
        del.y = circle[j].center.y - cursor.y;

        del.x *= scale;
        del.y *= scale;

        circle[j].center = cursor + del;
        circle[j].setRadius(circle[j].getRadius() * scale);
    }
}




void zoom_temp_line( Vector2f cursor){

    if (first_endpoint_has_been_clicked )
    {
        Vector2f del;

        del.x = temp_line[0].position.x - cursor.x;
        del.y = temp_line[0].position.y - cursor.y;

        del.x *= scale;
        del.y *= scale;

        temp_line[0].position.x = cursor.x + del.x;
        temp_line[0].position.y = cursor.y + del.y;
    }
}

void zoom_temp_circle( Vector2f cursor){
    if ( temp_circle_has_been_clicked )
    {
        Vector2f del;

        del.x = temp_circle.center.x - cursor.x;
        del.y = temp_circle.center.y - cursor.y;

        del.x *= scale;
        del.y *= scale;

        temp_circle.center = cursor + del;
        temp_circle.setRadius(temp_circle.getRadius() * scale );
    }
}


void close_point(){
    // BRINGING cursor closer to point
    for(int i=0; i<points_count; i++){
        if( dist(cursor_position ,points[i].position) <= 10 ){
            cursor_position = points[i].position;
        }
    }
    // BRINGING cursor closer to m_point
    for(int i=50; i<m_points_count; i++){
        if( dist(cursor_position ,points[i].position) <= 10 ){
            cursor_position = points[i].position;
        }
    }

    // BRINGING cursor closer to c_point
    for(int i=100; i<c_points_count; i++){
        if( dist(cursor_position ,points[i].position) <= 10 ){
            cursor_position = points[i].position;
        }
    }
}


void draw_points(RenderWindow &window){

    for(int i=50; i<m_points_count; i++){
        if(dist(cursor_position,points[i].position)<50)
            points[i].draw_me(window);
    }

    for(int i=100; i<c_points_count; i++){
        if(dist(cursor_position,points[i].position)<50)
            points[i].draw_me(window);
    }

    for(int i=0; i<points_count; i++){
        if(dist(cursor_position,points[i].position)<50)
            points[i].draw_me(window);
    }


    if(first_endpoint_has_been_clicked)
        check_closest_tan_point(window);
}



void set_cursor_pixels(Uint8 *myCursorPixels){

    Uint8 temp_pixels[cursor_x][cursor_y][4];

    for(unsigned short i=0; i<cursor_x; i++){
        for(unsigned short j=0; j<cursor_y; j++){
            if( (i>cursor_x/2-cursor_t && i<cursor_x/2+cursor_t)
             || (j>cursor_y/2-cursor_t && j<cursor_y/2+cursor_t) )
            {
                temp_pixels[i][j][0] = 255;
                temp_pixels[i][j][1] = 255;
                temp_pixels[i][j][2] = 255;
                temp_pixels[i][j][3] = 255;
            }else{
                temp_pixels[i][j][0] = 0;
                temp_pixels[i][j][1] = 0;
                temp_pixels[i][j][2] = 0;
                temp_pixels[i][j][3] = 0;
            }
        }
    }

    for(unsigned short i=0; i<cursor_x; i++){
        for(unsigned short j=0; j<cursor_y; j++){
            for(unsigned short k=0; k<4; k++){
                *(myCursorPixels + cursor_y*4*i + 4*j + k) = temp_pixels[i][j][k];
            }
        }
    }
}

