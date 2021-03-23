#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "my_jedi_manager.h"

/*In this function we create a char pointer to a variable  which we get by using the getline function*/
char* read_string(){
    	char *b=NULL;
   	size_t bufsize = 0;
    	getline(&b,&bufsize,stdin);
	return b;
}
/*In this function we get an int variable by using the read_string function and converting it to a int vaule using the strol  c library function*/
int getint(){
	char *str=NULL;
	int num;
	str=read_string();
	num=strtol(str,NULL,0);
	free(str);
	return num;
}
/*This is just a function of prints to show the menu to screen*/
void menu(){
        printf("[*] [2018] [SAUCEM APPS] [JediManager]\n");
        printf("[1] Exit\n");
        printf("[2] Inserting a Jedi\n");
        printf("[3] Show Jedis\n");
        printf("[4] Show a Jedi with ID\n");
        printf("[5] Modify a Jedi with ID\n");
        printf("[6] Remove a Jedi with ID\n");
        printf("[7] Export Jedi's to a binary file\n");
        printf("[8] Import a Jedi from a binary file\n");
        printf("[9] Jedi combat simulator\n");
        printf("[10] Sort Jedis with hit points\n");
        printf("[11] Jedi autosaving \n");
}
*///In this function we create a switch to give the user the option to exit the program, if the user chooses says yes, the program closes, if they choose no, we come back to the program right were it was left of. In both cases we free the ‘option’ variable*/
void exitm(struct jedi * new_jedi, struct list * list){
	char *exitmenu;
        printf("Are you sure you want to exit the manager? [y/n]");
	exitmenu=read_string();
        if ( *exitmenu=='y'|| *exitmenu=='Y'|| *exitmenu=='n'|| *exitmenu=='N'){
		switch(*exitmenu) {
                	case 'y': case 'Y':
                        if (list->head == NULL){ 
                            free(list);
                       	}
                        else{
                           struct jedi * current ;
                        	while (list->head->next_jedi != NULL){
                           		current=list->head;
					list->head = list->head->next_jedi;
                            		free(current->ptr_points);
					free(current->s_full_name);
                            		free (current); 
					  
                                }
				free(exitmenu);
                       	 }   
                        exit(-1);
                        break;
                    	case 'n': case 'N':
			free(exitmenu);
                        return;
                        break;
                  }
         }
	else {
                printf("Character not valid");
                exitm(new_jedi, list);

            }
}


/*Here we are going to introduce the jedi we created in the info() function in the end of the list,
using a while loop to move through the created jedis.*/

void insertjedi(struct jedi * new_jedi, struct list * list) {
	struct jedi * current2=list->head;
	if (current2==NULL){
		printf("List is empty we start filling head.\n");
		list->head=new_jedi;
	
	}
	else{	
		while(current2->next_jedi!=NULL){
		current2=current2->next_jedi;
		}
		current2->next_jedi=new_jedi; 
	}

}

/*In this function first we do dynamic memory allocations with malloc to reserve memory for the jedi we are about to create.Then we get the values of the jedi with the getint() and read_string functions, saving the variables in the corresponding pointer. We also take into account if the jedi is a master or apprentice to save the values accordingly */

struct jedi * info(struct jedi * new_jedi) {
	int z;
	struct jedi * current = new_jedi;

		current = (struct jedi *)malloc(sizeof(struct jedi));
		current->ptr_points = (struct points *)malloc(sizeof(struct points));
		printf("Inserting a Jedi\n");
		printf("Give the ID of the Jedi:\n");
		current-> id = getint();
		
		int size;
		do{
		printf("Give the name of the Jedi:");
		current->s_full_name= strtok(read_string(), "\n");
		size = strlen(current->s_full_name);
		current->size_name = size;
			if(size>10){
				printf("The name overcomes the maximun length, 10 digits limit. Try again\n");
			} 
		}while(size>10);
		printf("Give hit points:\n");
		current->ptr_points->hit_points = getint();
		printf("Give the attack of an apprentice:\n");
		current->ptr_points->attack_array[0] = getint();
		printf("Give the defense of an apprentice:\n");
		current->ptr_points->defense_array[0]= getint();
		printf("Give the speed of an apprentice:\n");
		current->ptr_points->speed_array[0]= getint();
		printf("Give the attack of an master:\n");
		current->ptr_points->attack_array[1] = getint();
		printf("Give the defense of an master:\n");
		current->ptr_points->defense_array[1]= getint();
		printf("Give the speed of an master:\n");
		current->ptr_points->speed_array[1]= getint();
	do{
		z=1;
		printf("Is a Master? (y/n)\n");
		char *master = read_string();
		if ( *master=='y'|| *master=='Y'||*master=='n'||*master=='N'){
                	switch(*master) {
				case 'y': case 'Y':
                        	current->ptr_points->level = 1;
				break;
                    		case 'n': case 'N':
              			current->ptr_points->level = 0;	
                       		 break;
                        }
		free(master);
            	}
           	else {
                  printf("Character not valid. Please try again.\n");
                  z=2;
             	}
		current->next_jedi=NULL;


	}while(z!=1);
		//printf("The information has been saved \n");
		return current;
}
/*function created to check if the list is empty or not before using any other functions that requires the list not to be empty*/
int isEmpty(struct list * list){
	if (list->head==NULL){
		return 1;
	}
	else{
		return 0;
	}
}
/*function created to search for a specific jedi in order to show its full information, remove it from the list or modify its information
In this function we move through the list of jedis looking for the id the user gave us. If it is found the position that it has is returned.*/
int searchid (struct list * list, int idd){
	int count =1;
	struct jedi * current = list->head;
		do{
			if(current->id==idd){
				printf("Find in the position %d \n", count);
				return count;
			}
			count++;
			current=current->next_jedi;
		}while(current!=NULL);
	printf("No encontrado \n");
	return 0;
}

/*in this function we first check if the list is empty, if not we first move through the list to find the jedi with the id the user wants and then using the searchid we get the position the jedi occupies and we free that memory.*/
void remove_jedi(struct list * list,int idd){
	if(isEmpty(list)==1){
		printf("The list is empty \n");
		return;
	}
	struct jedi * temp = list->head;
	struct jedi * prev;
	if((temp != NULL) & (temp->id == idd)){
		list->head = temp->next_jedi;
		free(temp);
		return;
	}
	int numnode=searchid(list,idd);
	if(numnode==0){		
		return;
	}
	for(int i=1; i<numnode;i++){
		printf("The key being deleted is %d", temp->id);
		prev=temp;
		temp=temp->next_jedi;
	}
	prev->next_jedi=temp->next_jedi;
	free(temp);

}

/*In this function we give the user the option to change all of the information inside a jedi except for the ID, which is optional, once the values are changed, we store the jedi in the same position that it was before*/
void modify_jedi(struct list * list, int modid) {
	struct jedi * current = retujedi(list, modid);
	char *newmaster = NULL;
	char *newid = NULL;
	int z;
	do{
	z=1;	
   	if(current!=NULL) {
    		printf("Enter the new parameters for the jedi:\n");
    		printf("Do you want to change the jedi's ID? (y/n)\n");
    		newid =read_string();
    	if(*newid=='y' || *newid=='Y'){
    		printf("Enter the new ID of the jedi:\n");
    		current->id=getint();
    	}
	int size;
		do{
		printf("New name of the Jedi:");
		current->s_full_name= strtok(read_string(), "\n");
		size = strlen(current->s_full_name);
		current->size_name = size;
			if(size>10){
				printf("The name overcomes the maximun length, 10 digits limit. Try again\n");
			} 
		}while(size>10);
	printf("Give new hit points:\n");
	current->ptr_points->hit_points = getint();
        printf("Give the new attack of an apprentice:\n");
        current->ptr_points->attack_array[T_APPRENTICE] = getint();
        printf("Give the new defense of an apprentice:\n");
        current->ptr_points->defense_array[T_APPRENTICE]= getint();
        printf("Give the new speed of an apprentice:\n");
        current->ptr_points->speed_array[T_APPRENTICE]= getint();
	printf("Give the new attack of a master:\n");
        current->ptr_points->attack_array[T_MASTER] = getint();
        printf("Give the new defense of a master:\n");
        current->ptr_points->defense_array[T_MASTER]= getint();
        printf("Give the new speed of a master:\n");
        current->ptr_points->speed_array[T_MASTER]= getint();
	printf("Is the jedi a master?  [y/n] \n");
	newmaster=read_string();
	if ( *newmaster=='y'|| *newmaster=='Y'||*newmaster=='n'||*newmaster=='N'){
                switch(*newmaster) {
                case 'y': case 'Y':
                	current->ptr_points->level=T_MASTER;
                        break;
                case 'n': case 'N':
                        current->ptr_points->level=T_APPRENTICE;
                        break;
                }
        }
        else {
                  printf("Character not valid. Please try again.\n");
                  z=2;
            }
        }
	else{	
	}
	free(newid);
	free(newmaster);
	}while(z!=1);
	
}
/*In this function we move through the jedi list and we compare the id of each jedi to the one the user supplied in the option 4 and if they are the same we return the jedi (using the searchid function). if not we throw an exception*/
struct jedi * retujedi (struct list * list, int idd){
	if(isEmpty(list)==1){
		printf("The list is empty \n");
		return NULL;
	}
	struct jedi * current = list->head;
	if(current->id == idd){
		return current;
	}
	else{
		int numnode=searchid(list,idd);
		if(numnode==0){	
			return NULL;
		}
		else{
			for(int i=1; i<numnode;i++){
				current=current->next_jedi;	
			}
			return current;
		}
		
	}
}

/*in this function we make a call to the retujedi function which gives us the jedi with the id the user was looking for and we print it to screen.*/
void fullinfo(int idd, struct list * list){
	struct jedi * current = retujedi(list,idd);
	if(current!=NULL){
		printf("Full info of the Jedi.\n");
		printf("ID : %d\n", current->id); 
		printf("NAME: %s\n", current->s_full_name);
		printf("HP: %d\n", current->ptr_points->hit_points);
		printf("Attack of apprentice:  %d \n", current->ptr_points->attack_array[0]);
		printf("Defense of apprentice:  %d \n", current->ptr_points->defense_array[0] );
 		printf("Speed of apprentice:  %f \n", current->ptr_points->speed_array[0]);
		printf("Attack of master:  %d \n", current->ptr_points->attack_array[1]);
		printf("Defense of master:  %d \n", current->ptr_points->defense_array[1] );
 		printf("Speed of master:  %f \n", current->ptr_points->speed_array[1]);   
 	}
	else{
	return;
	}
}


/*In this function we choose two jedis (using the searchID and retujedi functions), and after computing the damage points of each of the jedis, they start to battle with one another. We also did a switch with several cases and different senteces to make the battle more dynamic. If one of the jedis die, we stop the battle. If it was a master and loses the battle, the jedi becomes and apprentice, on the other hand, if an apprentice wins to a master, it becomes a master.*/
void battle(struct list * list){
	int jedia;
	int jedib;
	int x;
	int y;
	struct jedi * temp = list->head;
	struct jedi * temp2 = list->head;
	printf("Inserte el ID del jedi 1\n");
	jedia = getint();
	x = searchid(list, jedia);
		if(x==0){		
			printf("Not found\n");		
			return;
		}
		for(int i=1; i<x;i++){
			temp=temp->next_jedi;
		}
	printf("%.10s, I choose you! \n", temp->s_full_name);

	printf("Inserte el ID del jedi 2\n");
	jedib = getint();
	y = searchid(list, jedib);
	if(y==0){		
		printf("Not found\n");		
		return;
		}
	for(int i=1; i<y;i++){
		temp2=temp2->next_jedi;
	}
	printf("%.10s, I choose you! \n", temp2->s_full_name);

	if(temp->ptr_points->hit_points == 0 || temp2->ptr_points->hit_points == 0){

	printf("One of the jedis has died. Combat cannot continue\n");
	return;
	}
	else{
		printf("\nLET THE BATTLE START \n");
		sleep(3);
		int damage;
		while(temp->ptr_points->hit_points > 0 && temp2->ptr_points->hit_points > 0){
		damage= (temp->ptr_points->speed_array[temp->ptr_points->level]/temp2->ptr_points->speed_array[temp2->ptr_points->level])*(((86+rand()%15)*temp->ptr_points->attack_array[temp->ptr_points->level])/(temp2->ptr_points->defense_array[temp2->ptr_points->level])/10); 

	int z = (int)rand()%9;
		switch(z) {
			case 0:
				printf("%.10s stabs several times %.10s causing %d points of damage \n", temp->s_full_name, temp2->s_full_name, damage);
				sleep(2);
				break;
			case 1:
				printf("%.10s throws his sword directly to %.10s 's head dealing %d points of damage \n", temp->s_full_name, temp2->s_full_name, damage);
				sleep(2);
				break;
			case 2:
				printf("%.10s parry perfctly, and his counter-attack deals %d points of damage to %.10s \n", temp->s_full_name, damage, temp2->s_full_name);
				sleep(2);
				break;
			case 3:
				printf("%.10s attack was very effective! %.10s looses %d HP \n", temp->s_full_name, temp2->s_full_name, damage);
				sleep(2);
				break;
 			case 4:
				printf("%.10s has nothing to do against %.10s's imparable COMBO. Looses %d HP \n", temp2->s_full_name, temp->s_full_name, damage);
				sleep(2);
				break;
			case 5:
				printf("%.10s fails his attack, but he's lucky enought to deal %d damage to %.10s \n", temp->s_full_name, damage, temp2->s_full_name);
				sleep(2);
				break;
			case 6:
				printf("%.10s said something very ugly to %.10s. %.10s feels sad. %.10s looses %d HP \n", temp->s_full_name, temp2->s_full_name, temp2->s_full_name , temp2->s_full_name , damage);
				sleep(2);
				break;
			case 7:
				printf("%.10s calls the Force, and push %.10s against the wall! %d of damage dealt! \n", temp->s_full_name, temp2->s_full_name, damage);
				sleep(2);
				break;
			case 8:
				printf("%.10s gave %.10s an amazing compliment. %.10s is so confused, and hurts himself %d with damage! \n", temp->s_full_name, temp2->s_full_name, temp2->s_full_name, damage);
				sleep(2);
				break;


}

	temp2->ptr_points->hit_points= temp2->ptr_points->hit_points - damage;

	damage= (temp2->ptr_points->speed_array[temp2->ptr_points->level]/temp->ptr_points->speed_array[temp->ptr_points->level])*(((86+rand()%15)*temp2->ptr_points->attack_array[temp2->ptr_points->level])/(temp->ptr_points->defense_array[temp->ptr_points->level])/10);
 
	z = (int)rand()%9;
		switch(z) {
			case 0:
				printf("%.10s stabs several times %.10s causing %d points of damage \n", temp2->s_full_name, temp->s_full_name, damage);
				sleep(2);
				break;
			case 1:
				printf("%.10s throws his sword directly to %.10s 's head dealing %d points of damage \n", temp2->s_full_name, temp->s_full_name, damage);
				sleep(2);
				break;
			case 2:
				printf("%.10s parry perfctly, and his counter-attack deals %d points of damage to %.10s \n", temp2->s_full_name, damage, temp->s_full_name);
				sleep(2);
				break;
			case 3:
				printf("%.10s attack was very effective! %.10s looses %d HP \n", temp2->s_full_name, temp->s_full_name, damage);
				sleep(2);
				break;
 			case 4:
				printf("%.10s has nothing to do against %.10s's imparable COMBO. Looses %d HP \n", temp->s_full_name, temp2->s_full_name, damage);
				sleep(2);
				break;
			case 5:
				printf("%.10s fails his attack, but he's lucky enought to deal %d damage to %.10s \n", temp2->s_full_name, damage, temp->s_full_name);
				sleep(2);
				break;
			case 6:
				printf("%.10s said something very ugly to %.10s. %.10s feels sad. %.10s looses %d HP \n", temp2->s_full_name, temp->s_full_name, temp->s_full_name , temp->s_full_name , damage);
				sleep(2);
				break;
			case 7:
				printf("%.10s calls the Force, and push %.10s against the wall! %d of damage dealt! \n", temp2->s_full_name, temp->s_full_name, damage);
				sleep(2);
				break;
			case 8:
				printf("%.10s gave %.10s an amazing compliment. %.10s is so confused, and hurts himself %d with damage! \n", temp2->s_full_name, temp->s_full_name, temp->s_full_name, damage);
				sleep(2);
				break;			
			}

	temp->ptr_points->hit_points= temp->ptr_points->hit_points - damage;

	printf("\n\n\t\tCURRENT LIFE %.10s : \t %d \n\t\tCURRENT LIFE %.10s : \t %d\n\n",temp->s_full_name, temp->ptr_points->hit_points, temp2->s_full_name, temp2->ptr_points->hit_points);
	sleep(2.5);

}
	if(temp->ptr_points->hit_points <= 0){ 
	printf("\n\n\n\n\n\n\t\t\t\t\t\t\t%.10s has won the battle! \n\n\n\n\n\n", temp2->s_full_name);
	temp->ptr_points->hit_points=0;
	if(temp->ptr_points->level == 1 && temp2->ptr_points->level == 0){
	temp->ptr_points->level = 0;
	temp2->ptr_points->level = 1;
	}
	}
	else if(temp2->ptr_points->hit_points <= 0){
	printf("\n\n\n\n\n\n\t\t\t\t\t\t\t%.10s has won the battle! \n\n\n\n\n\n", temp->s_full_name);
	temp2->ptr_points->hit_points=0;
	if(temp->ptr_points->level == 0 && temp2->ptr_points->level == 1){
	temp->ptr_points->level = 1;
	temp2->ptr_points->level = 0;
	}
	}



}



}


/*In this function we export the list of jedis up to that point into a binary document in the same folder that the project is stored in. If there is an error in this process, we print out a message telling the user what went wrong, if everything goes well, a message is printed confirming that the file was created and the jedis were correctly stored*/

void exportfile(struct list * list){
    struct jedi *current = list -> head;
    printf("Please insert the name of the file: ");
    char *namefile=NULL;
    namefile = read_string();
    FILE *file; 
    file = fopen(namefile, "ab");
    if (file==NULL){
       printf("The file could not be open");
       return;
    }   
    if (current==NULL){
       printf("The list is empty. There is nothing to export");
       return;
    } 
	while(current!=NULL){
        
    fwrite(current,sizeof(struct jedi),1, file);
	
    
    current=current->next_jedi;

    }
	int a= fclose(file);

     if (a==0){
            printf("The file was closed correctly\n");
            printf("The file was created and saved\n");
            return;
        }
    if (a!=0){
            printf("The file could not be closed\n");
            return;
        }
	if(ferror(file)!=0){
		printf("There was an error in the file\n");
        return;
		
	}

}

/*In this function we are going to introduce the jedi we imported for the file in import_file() and we are going to set it in the start of the jedi list by setting the jedi head as its next_jedi*/


void insertimport (struct jedi * new_jedi, struct list * start) {
	if ( start->head == NULL){
		printf("List is empty, we start filling head jedi. \n");
		start->head = new_jedi;
 
	
	}
	else{	
    		new_jedi->next_jedi = start->head; 
    		start->head = new_jedi; 
		
	}


}
 
//PLEASE READ THIS

/*In this function first we open the file the user selected and while the end of file is not reached we reserve memory for the new jedi that is being created we extract the information from the file with fread and then we save the jedi in the list by using the insertimport() function. However as much as we tried our code was not working so when doing this point it doiesn't work properly. It looses all the information except for the ID, and it reads more jedis than there are in the file*/
void importfile(struct list * list){
        
    printf("Please insert the name of the file where you want the information from: ");
    char *namefile= read_string();
    FILE *file; 
    file = fopen(namefile, "rb");
	if (file==NULL){
            printf("The file could not be open");
            return;
        }
    	
	if(ferror(file)!=0){
		printf("There was an error in the file\n");	
		
	}
       if(feof(file)) { 
        	
		int a=fclose(file);

   			  if (a==0){
            			printf("The file was closed correctly\n");
           			return;
        			}
   			  if (a!=0){
            			printf("The file could not be closed\n");
            			return;
        			}

      }

    while(feof(file)==0){
	struct jedi * jedi1 = (struct jedi*)malloc(sizeof(struct jedi));
	jedi1->ptr_points = (struct points*)malloc(sizeof(struct points));
        size_t result= fread(jedi1, sizeof(jedi1), 1, file);
        if(result!=1){
		printf("No information was read. \n");
		free(jedi1->ptr_points);  
		free(jedi1);
            break; 
        }else{
 		printf("Read jedi. \n");
		printf("ID : %d\n", jedi1->id); 
		printf("NAME: %s\n", jedi1->s_full_name);
		printf("HP: %d\n", jedi1->ptr_points->hit_points);
		insertimport(jedi1, list);
	}
	

    } 
	
	free(namefile);

}

    
/*in this function we are going to order the jedi list by the life points of the jedis. For this we use the sort function that moves through the jedi list comparing the points of the jedis and swapping their places accordingly using the swap function*/

void sort(struct list *start) 
{ 
    int status; 
    struct jedi *current; 
    struct jedi *base = NULL; 
  
    /* Checking for empty list */
    if (start->head == NULL) {
	printf("List is empty\n");
        return; }
  
    do
    { 
        status = 0; 
        current = start->head; 
  
        while (current->next_jedi != base) 
        { 
            if (current->ptr_points->hit_points < current->next_jedi->ptr_points->hit_points) 
            {  
		printf("We are about to perfom a swap\n");
                swap(current, current->next_jedi); 
                status = 1; 
            } 
            current = current->next_jedi; 
        } 
        base = current; 
    } 
    while (status); 
} 
  
/* Function to swap data of two nodes a and b. In this function we swap the data of two jedis given by the sort function by using pointers to reference the variables to their new values and using a temporary variable to store the values while they were being changed.*/

void swap(struct jedi *a, struct jedi *b) { 
	printf("swapping\n");
	int temp_id = a->id; 
	a->id = b->id; 
	b->id = temp_id; 

	char *temp_name = a->s_full_name;	
	a->s_full_name = b->s_full_name; 
	b->s_full_name = temp_name; 
	
	int temp_size = a->size_name; 
	a->size_name = b->size_name; 
	b->size_name = temp_size; 

	int temp_hp = a->ptr_points->hit_points; 
	a->ptr_points->hit_points = b->ptr_points->hit_points; 
	b->ptr_points->hit_points = temp_hp; 
	
	int temp_aatt = a->ptr_points->attack_array[0]; 
	a->ptr_points->attack_array[0] = b->ptr_points->attack_array[0]; 
	b->ptr_points->attack_array[0] = temp_aatt; 

	int temp_adef = a->ptr_points->defense_array[0]; 
	a->ptr_points->defense_array[0] = b->ptr_points->defense_array[0]; 
	b->ptr_points->defense_array[0] = temp_adef; 
	
	double temp_aspd = a->ptr_points->speed_array[0]; 
	a->ptr_points->speed_array[0] = b->ptr_points->speed_array[0]; 
	b->ptr_points->speed_array[0] = temp_aspd; 

	int temp_matt = a->ptr_points->attack_array[1]; 
	a->ptr_points->attack_array[1] = b->ptr_points->attack_array[1]; 
	b->ptr_points->attack_array[1] = temp_matt; 

	int temp_mdef = a->ptr_points->defense_array[1]; 
	a->ptr_points->defense_array[1] = b->ptr_points->defense_array[1]; 
	b->ptr_points->defense_array[1] = temp_mdef; 

	double temp_mspd = a->ptr_points->speed_array[1]; 
	a->ptr_points->speed_array[1] = b->ptr_points->speed_array[1]; 
	b->ptr_points->speed_array[1] = temp_mspd; 

	int temp_lvl = a->ptr_points->level; 
	a->ptr_points->level = b->ptr_points->level; 
	b->ptr_points->level = temp_lvl;
} 

/*In this function we print out the whole list of jedis inside a table. We don’t show the full information of the jedi, only the points corresponding to either a master or an apprentice, according to what the user already chose on previous options*/
void showjedi(struct list * list){	
	struct jedi * current=list->head;
	if (current ==NULL){
		printf("There are no jedis created \n");
	}
	else{
		printf("=====================================================================\n");
		printf(" |%8s|%20s|%8s|%8s|%8s| \n", "ID", "NAME", "HP", "Attack", "Defense");
		printf("=====================================================================\n");
		while( current!=NULL){
			printf(" |%8d|%20.10s|%8d|%8d|%8d| \n",
			current->id,
			current->s_full_name,
			current->ptr_points->hit_points,
			current->ptr_points->attack_array[current->ptr_points->level],
			current->ptr_points->defense_array[current->ptr_points->level]);
		printf("=====================================================================\n");
		current=current->next_jedi;
		}
	}
}





//PLEASE READ THIS 




/*Here we tried to make the autosave work as best as possible, unfortunately, we couldn’t finish it. Our initial approach was to make two different functions to put into two different threads: the first one was a globalswitch function, which was the switch of the program and it was there to control the list of jedis and all of its modifications, then, we created the autosave function which was put into the second thread, which is the one that actually saves the program into the file. Then, we realised that the globalswitch function wasn’t necessary and we put the mutex lock and lock at the beggining and end of the switch (inside the main), but after deleting the globalswitch we didn’t know which function pass to the creation of the thread that controlled the list. However, after all, we still decide to put it in the file commented so it could be taken into account our efforts while making it, even though it still didn't work properly and we were getting out of options and ideas. */







/*
void *autosave(struct list * list, void *b) {
    struct thread_args *args=(struct thread_args *)b;
    //struct list *list_jedi=args2->list_jedi;
    //struct jedi *head_jedi=args2->head_jedi;
    pthread_mutex_t  mutex=args->mutex;
    printf("ee");
    pthread_mutex_lock(&mutex);
    struct jedi *current = list -> head;
    char *namefile="##auto_jedi_save.dat";
    FILE *file; 
    file = fopen(namefile, "ab");
    if (file==NULL){
       printf("The file could not be open");
       return 0;
    }   
    if (current==NULL){
       printf("The list is empty. There is nothing to export");
       return 0;
    } 
	while(current!=NULL){
        
    fwrite(current,sizeof(struct jedi),1, file);
	
    current=current->next_jedi;

    }
    pthread_mutex_unlock(&mutex);
	int a= fclose(file);

     if (a==0){
            printf("The file was closed correctly\n");
            printf("The file was created and saved\n");
            return 0;
        }
    else if (a!=0){
            printf("The file could not be closed\n");
            return 0;
        }
	else if(ferror(file)!=0){
		printf("There was an error in the file\n");
        return 0;
		
	}
	 
    return 0;
}
*/
