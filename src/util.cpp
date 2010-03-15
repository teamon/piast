#include "piast.h"

bool key_pressed(int n){
	if(KEY_DOWN(n)){
		while(KEY_DOWN(n));
		return true;
	} else {
		return false;
	}
}
