#include <stdio.h>
#include <stdlib.h>
#include "my_jedi_manager.h"


int main(){
	struct jedi *head_jedi = NULL;
	struct list *list_jedi = (struct list *)malloc(sizeof(struct list)); 
	list_jedi->head=NULL;
	int counter = 0;
/*
	pthread_mutex_t mutex;
    struct thread_args *structthr1;
    structthr1=(struct thread_args *)calloc(50, sizeof(struct thread_args));
    structthr1->list_jedi=list_jedi;
    structthr1->head_jedi=head_jedi;
    structthr1->mutex=mutex;
     if(pthread_mutex_init(&mutex,NULL)!=0){
        printf("The mutex could not be initialized.\n");
    
        */
        

    
	do{
   		menu();
		printf("       #INFO:  %i times shown this menu\n", counter);
    		printf("Type an option:\n");
    		int optionmenu=2;
		optionmenu=getint();
    		switch(optionmenu) {
			case 1:
				exitm(head_jedi, list_jedi);
				break;
			case 2:
			/*In this option we have to introduce a jedi. To do this first we create the jedi to be inserted in the function info and in insert_jedi we place it in the jedi list*/
				head_jedi=info(head_jedi,list_jedi);
				insertjedi(head_jedi,list_jedi);
				break;
			case 3:
				showjedi(list_jedi);
				break;
			case 4:
				/*In this case we are going to print to screen a jedi that the user chooses by their id, 
				so after getting the corresponding id, with the fullinfo function we display the info of the chosen jedi. */
				printf("Insert the ID\n");
				int seeid = getint();
				fullinfo(seeid, list_jedi);
				break;

 			case 5:
				printf("Insert the ID\n");
				int numid2 = getint();
				modify_jedi(list_jedi, numid2);
				break;

			case 6:
				/*In this option we are going to erase the jedi that contains the id that the user supplied so by using the removejedi function we delete it.*/
				printf("Insert the ID\n");
				int numid = getint();
				remove_jedi(list_jedi, numid);
				break;

			case 7:
				exportfile(list_jedi);
				break;
			case 8:
				/*in this option we are going to import the jedi from a binary file into the list*/
				importfile(list_jedi);
				break;

			case 9:
				battle(list_jedi);
				break;

			case 10:
				/*In this function we are going to move through the jedi list reading each jedi ‘s hit points and swapping them if the hit points of any given jedi are bigger than of the 					later jedi.*/
				sort(list_jedi);
				break;

			case 11:
                //autosave(list_jedi,structthr1);
				break;
     			 }
		counter++;

	}while(1==1);

	/*
pthread_t tjedi;
    pthread_create(&tjedi, NULL, NULL, (void *) &structthr1);
    pthread_join(tjedi, NULL);
    pthread_t tsave;
    pthread_create(&tsave, NULL, &autosave, (void *) &structthr1);
    pthread_join(tsave, NULL);
*/
	return 0;
}


