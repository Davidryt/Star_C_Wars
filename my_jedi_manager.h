#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
enum level_jedi { T_APPRENTICE = 0 , T_MASTER = 1};
struct points{
	int hit_points;
	int attack_array[2];
	int defense_array[2];
	double speed_array[2];
	enum level_jedi level;
	
};
struct jedi{
	int id;
	int size_name;
	char *s_full_name;
	struct points *ptr_points;
	struct jedi *next_jedi;
	
};

struct list{
	struct jedi *head;
	
};

/*
struct thread_args {
    struct list *list_jedi;
    struct jedi *head_jedi;
    pthread_mutex_t  mutex;
};*/

extern void *autosave();

extern char* read_string();
extern int getint();
extern void menu();
extern void exitm();
extern void insertjedi();
extern int searchid();
extern int isEmpty();
extern void remove_jedi();
extern struct jedi * info();
extern void showjedi();
extern void fullinfo();
extern struct jedi * retujedi ();
extern void modify_jedi();
extern void battle ();
extern void exportfile();
extern void importfile();
extern void sort();
extern void swap();



