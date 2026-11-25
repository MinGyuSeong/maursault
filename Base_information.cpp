#include "Base_information.h"

bool Draw_Collider = false;

bool Get_Draw_Collider(){
	return Draw_Collider;
}
void change_collider() {
	Draw_Collider = !Draw_Collider;
}