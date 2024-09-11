/*
struct point{
    VertexPoint vp;
    point *next = NULL;
};

point* head_point;


void append_point(Vector2f cordinate){

    point *new_point = new point();
    new_point->vp.position = cordinate;

    point *last_point = head_point;

    while(true){

        if(last_point->next == NULL){
            last_point->next = new_point;
            break;
        }
        last_point = last_point->next;
    }
}


void remove_point(unsigned int position){

    point* current_point = head_point;

    point* previous_point;

    for(int i=0; i<position; i++){

        if(i==position-1){
            previous_point = current;
        }

        current_point = current_point->next;
    }
    previous_point->next = current_point->next;
    delete current_point;
}



void pop_point(){

    point *last_point = head_point;

    point *sec_last_point;

    while(true){
        if(last_point->next == NULL){
            second_last_point->next = NULL;
            delete last_point;
            break;
        }
        sec_last_point = last_point;

        last_point = last_point->next;
    }
}



void delete_points(point *current_point){ // Pass "head_point" here

    if(current_point->next != NULL){
        delete_points(current_point->next); // Recursion here
        delete current_point;
    }else{
        delete current point;
    }
}

*/

