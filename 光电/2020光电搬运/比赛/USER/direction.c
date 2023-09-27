#include "direction.h"
#include "speed.h"
#include "delay.h"
void Direction(u8 left,u8 right)
{
 	PBout(11)=left;                      
	PBout(10)=right; 				  
} 

