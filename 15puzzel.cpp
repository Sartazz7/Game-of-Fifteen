#include<Fl/Fl.H>
#include<Fl/Fl_Window.H>
#include<Fl/Fl_Button.H>
#include<FL/Fl_Radio_Button.H>
#include<FL/Fl_Light_Button.H>
#include<cstdlib>
#include<stdlib.h>
#include<iostream>

using namespace std;

char *int2charstar(int v){
	char *s=new char[sizeof(int)];
	sprintf(s,"%d",v);
	return s;
}

Fl_Button *button[4][4];

class MyButton : public Fl_Button {
	int my_x, my_y;
	int *bl_x;
	int *bl_y;
	public :
		MyButton(int x, int y, int w, int h, const char *l, int *bx, int *by);
		int handle(int e);
};

MyButton :: MyButton (int x, int y, int w, int h, const char *l, int *bx , int *by) : Fl_Button(x,y,w,h,l){
	my_x=x;
	my_y=y;
	bl_x=bx;
	bl_y=by;
}

int MyButton :: handle (int e) {
	if (e==FL_PUSH) {
		if(my_x-100 == *bl_x || my_x+100 == *bl_x){
			if(my_y == *bl_y){
				button[*bl_x/100-1][*bl_y/100-1]->label(this->label());
				*bl_x = my_x;
				label("");
				return 1;
			}
		}
		if(my_y-100 == *bl_y || my_y+100 == *bl_y){
			if(my_x == *bl_x){
				button[*bl_x/100-1][*bl_y/100-1]->label(this->label());
				*bl_y = my_y;
				label("");
				return 1;
			}
		}
	}
	return -1;
}

int main () {
	Fl_Window *window;
	int x=400, y=400;
	
	window = new Fl_Window (600,600,"15 Puzzel Game");
    	for(int i=0; i<4; i++){
    		for(int j=0; j<4; j++){
    			button[j][i]= new MyButton (100+j*100,100+i*100,100,100, "", &x, &y);
    			if(i==3 && j==3)continue;
    			button[j][i]->label( int2charstar(i*4+j+1));
    		}
    	}
    	srand(time(0));
    	for(int i=0; i<20; i++){
    		int ac = rand()%15;
    		int bc = rand()%15; 
    		const char *a = button[ac/4][ac%4]->label();
    		const char *b = button[bc/4][bc%4]->label();
    		button[ac/4][ac%4]->label(b);
    		button[bc/4][bc%4]->label(a);
    	}
	window->end();
    	window->show();
    	return (Fl::run());
    	
    	
}
