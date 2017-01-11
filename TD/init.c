extern char _bend,_bstart;

//Initialisation du bss
void init_bss(){
	char *dst;
	for (dst = &_bstart; dst < &_bend; dst++)
		 *dst = 0;
}

