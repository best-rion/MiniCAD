#include "classHeader.h"
#define cursor_x 100
#define cursor_y 100
#define cursor_t 1

extern unsigned int points_count;
extern unsigned int m_points_count;
extern unsigned int c_points_count;

extern float scale;

extern const unsigned int trh;

extern VertexPoint tangent_vertex; // tangent point is a property of circle

void cursor_text(Vector2i position, Text &text);

void set_font(Text &cursor_pos_text, Font &font);




void set_line_to_default();

void making_line();

void reset_line();

void drawing_line(RenderWindow &window);


void making_d_line_template(unsigned short low, unsigned short high);
void making_d_line();

void drawing_d_line_template(RenderWindow &window, unsigned short low, unsigned short high);
void drawing_d_line(RenderWindow &window);



void making_circle();

void reset_circle();

void drawing_circle(RenderWindow &window);



struct TanReturn{
    Vector2f point;     // The closest tangent point
    bool is_close; // Is the cursor close to it?
};
TanReturn tangent_point(Vector2f p, int circle_index);

void check_closest_tan_point(RenderWindow &window);




void save_drawing(RenderWindow &window);


void zoom_point( unsigned short, unsigned short,Vector2f);
void zoom_line(Vector2f);
void zoom_circle(Vector2f);

void zoom_temp_line(Vector2f);
void zoom_temp_circle(Vector2f);

void close_point();

void draw_points(RenderWindow &window);

void set_cursor_pixels(Uint8 *myCursorPixels);
