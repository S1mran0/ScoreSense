#include <stdio.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define MAX_TERMS    4

struct Subject {
    char name[30];
    int  grades[MAX_TERMS];
};
//predictt
float predict(struct Subject s, int terms)
{
    return (s.grades[terms - 1] + s.grades[terms - 2]) / 2.0f;
}
//bar
void print_bar(int grade)
{
    int i;
    for (i = 0; i < grade / 10; i++)
        printf("*");
    printf("\n");
}

int main()
{
    struct Subject s[MAX_SUBJECTS];
    int subjects, terms;
    int i, j;
//intro
    printf("     >Grade Quest - CHAPTER 1<\n\n");
    printf("A new hero enters the academy...\n\n");
   
    printf("How many enemies (subjects): ");
    scanf("%d", &subjects);

    printf("How many rounds (terms)   : ");
    scanf("%d", &terms);
//input
    for (i = 0; i < subjects; i++) {
        printf("\nEnter %d Enemy (Subject) name: ", i + 1);
        scanf("%s", s[i].name);

        for (j = 0; j < terms; j++) {
            printf("  Round %d score: ", j + 1);
            scanf("%d", &s[i].grades[j]);
        }
    }
//battle
    printf("\n     >Battle Report<\n");

    for (i = 0; i < subjects; i++) {
        int first = s[i].grades[0];
        int last  = s[i].grades[terms - 1];
        float pred = predict(s[i], terms);

        char trend[20];
        if      (last > first) strcpy(trend, "Leveling Up!");
        else if (last < first) strcpy(trend, "Taking Damage..");
        else                   strcpy(trend, "Holding Ground");

        int hours;
        if      (last >= 85) hours = 1;
        else if (last >= 70) hours = 2;
        else                 hours = 3;

        printf("\n[Enemy] %s\n", s[i].name);
        printf(" Status        : %s\n", trend);
        printf(" Next Attack   : %.1f\n", pred);
        printf(" Trainig Needed: %d hr/day\n", hours);

        printf(" Power chart:\n");
        for (j = 0; j < terms; j++) {
            printf("     Term %d [%3d] ", j + 1, s[i].grades[j]);
            print_bar(s[i].grades[j]);
        }
    }

//final boss
    float total = 0;
    int k;
    for (k = 0; k < subjects; k++)
        total += s[k].grades[terms - 1];

    float avg = total / subjects;

    printf("\n     FINAL BOSS\n");
    printf("Your Power Level: %.1f\n", avg);

    if (avg >= 85) {
        printf("*** YOU DEFEATED THE FINAL BOSS! ***\n");
        printf("The academy bows before you, champion!\n");
    } else if (avg >= 70) {
        printf(">> You damaged the boss but he survives!\n");
        printf("Train harder and challenge him again.\n");
    } else {
        printf("!! The boss overwhelmed you this time.\n");
        printf("Rest, train, and return stronger!\n");
    }

    printf("\n     >GAME OVER<\n");

    return 0;
}
