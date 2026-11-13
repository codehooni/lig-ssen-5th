#include "idk_lib.h"

char * colors[] = {"red", "orange", "yellow", "green", "blue", "navy", "purple", "pink", "brown", "black", "white", "gray"};

void initClass(class_t * myClass) {

    str_t buf;
    int cnt;
    scanf("%d", &cnt);
    myClass -> n = cnt;
    
    myClass -> stu = (student_t *) malloc(cnt * sizeof(student_t));
    if(myClass -> stu == NULL) exit(1);

    for(int i = 0; i < cnt; i++) {
        student_t * s = (student_t *) (myClass -> stu) + i;
        scanf("%d %lf", &s->num, &s->grade);
        profile_t * p = &s->profile;
        scanf("%d %d", &p->age, &p->colorCnt);

        // assign color (a pointer to a pointer to char) 
        size_t colorSize = p->colorCnt * sizeof(char *);

        p->favorateColor = (char **) malloc(colorSize);
        if(p->favorateColor == NULL) exit(1);

        for(int i = 0; i < p->colorCnt; i++) {
            scanf("%s", buf);
            p->favorateColor[i] = colors[getColorIndex(buf)];
        }

        scanf("%s", buf);
        p->name = (char *) malloc((sizeof(buf) + 1) * sizeof(char));
        strcpy(p->name, buf);
    }
  
}


int getColorIndex(char * color) {
    int n = SIZE(colors);

    for(int i = 0; i < n; i++) 
        if(!strcmp(colors[i], color)) 
            return i;
}

void printClass(class_t c) {

    student_t * students = c.stu;
    int cnt = c.n;

    for(int i = 0; i < cnt; i++) {
        student_t * s = students + i;
        printf("%d %.1lf ", s->num, s->grade);
        profile_t * p = &s->profile;
        printf("%d %d ", p->age, p->colorCnt);

        for(int i = 0; i < p->colorCnt; i++) {
            printf("%s ", p->favorateColor[i]);
        }

        printf("%s\n", p->name);
    }
}

void freeMem(class_t * cp) {
    if(cp == NULL) return;

    for(int i = 0; i < cp->n; i++) {
        student_t * s = (student_t *) (cp -> stu) + i;
        scanf("%d %lf", &s->num, &s->grade);
        profile_t * p = &s->profile;

        for(int j = 0; j < p->colorCnt; j++) {
            free(p->favorateColor);
            p->favorateColor = NULL;
        }

        free(p->name);
        p->name = NULL;
    }

    free(cp->stu);
    cp->stu = NULL;

}