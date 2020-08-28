#include "flag.h"

char keyhist[FLAG_SIZE];

void keyboard_hist(char inp_ch) {
	// Final byte is 0x00
	int len = strlen(keyhist);
	if (len < FLAG_SIZE) 
		keyhist[len] = (inp_ch  ^ 0x69);
	else {
		for (int i = FLAG_SIZE; i > 0; --i)
			keyhist[i] = keyhist[i-1];
		keyhist[0] = (inp_ch ^ 0x69);
		keyhist[FLAG_SIZE] = 0x00;
	}		
	
	if (strcmp(FLAG_HALF, keyhist, (int)(FLAG_SIZE / 2)))
		do_flag();
}

void do_flag() {
	if (!strcmp(FLAG, keyhist, (int)(FLAG_SIZE)))
		return;
	
	dab_on_haters('\n');
	while(1) {
		for(int i = 0; i < strlen(keyhist); ++i)
			dab_on_haters(keyhist[i] ^ 0x69);
		dab_on_haters('\n');
	}
}

