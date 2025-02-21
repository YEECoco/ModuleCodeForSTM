#include "rgb.h"

/* 
 * Turn on the right or left searclight
 * light: right or left 
 * color: choose the color you want to display
 * 
 */
void Set_RGB(car_RGB light, RGB_Color color){
    uint8_t Light_RGB = light;
    switch (Light_RGB){
        case RGB_R:
            Set_color_R(color);
            break;
        case RGB_L:
            Set_color_L(color);
            break;
        case RGB_Max:
            Set_color_R(color);
            Set_color_L(color);
            break;
        default:
            ALL_RGB_OFF;
    }
}

/*
 * Turn on the right searchlight and show the color
 * color: the color you want to display
 * 
*/
void Set_color_R(RGB_Color color){
    switch (color){
        case red:
            RRGB_SET(set, reset, reset);
		    break;
        case green: 
            RRGB_SET(reset, set, reset);
		    break;
        case blue:
            RRGB_SET(reset, reset, set);
		    break;
        case yellow:
		    RRGB_SET(set, set, reset);
		    break;
	    case purple:
		    RRGB_SET(set, reset, set);
		    break;
	    case lake:
		    RRGB_SET(reset, set, set);
		    break;
	    case write:
		    RRGB_SET(set, set, set);
		    break;
        default:
            R_RGB_OFF;
    }
}

/*
 * Turn on the left searchlight and show the color
 * color: the color you want to display
*/
void Set_color_L(RGB_Color color){
	switch (color){
        case red:
            LRGB_SET(set, reset, reset);
            break;
        case green:
            LRGB_SET(reset, set, reset);
            break;
        case blue:
            LRGB_SET(reset, reset, set);
            break;
        case yellow:
            LRGB_SET(set, set, reset);
            break;
        case purple:
            LRGB_SET(set, reset, set);
            break;
        case lake:
            LRGB_SET(reset, set, set);
            break;
        case write:
            LRGB_SET(set, set, set);
            break;
        default:
            L_RGB_OFF;
	}
}
