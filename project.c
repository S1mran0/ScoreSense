#include <stdio.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define MAX_TERMS 10

struct Subject {
    char name[30];
    int grades[MAX_TERMS];
    float predictedGrade;
};

// Function to calculate trend
void analyzeTrend(struct Subject s, int terms, char *trend) {
    int improving = 0, declining = 0;
    for(int i=1; i<terms; i++) {
        if(s.grades[i] > s.grades[i-1]) improving++;
        else if(s.grades[i] < s.grades[i-1]) declining++;
    }
    if(improving == terms-1) strcpy(trend, "Improving");
    else if(declining == terms-1) strcpy(trend, "Declining");
    else strcpy(trend, "Fluctuating");
}

// Function to predict next term grade
float predictNext(struct Subject s, int terms) {
    if(terms < 2) return s.grades[terms-1]; // Not enough data
    return (s.grades[terms-1] + s.grades[terms-2]) / 2.0;
}

/*// Function to print ASCII bar graph
void printBar(int grade) {
    int bars = grade / 2; // 50 bars max for 100%
    for(int i=0;i<bars;i++) printf("█");
    printf("\n");
}*/

// Function to give study plan based on grade
float studyHours(int grade) {
    if(grade >= 85) return 0.5;   // Excellent
    else if(grade >= 70) return 1; // Good
    else return 2;                 // Weak
}

int main() {
    int subjectsCount, termsCount;
    printf("Welcome to Super Smart Grade Improver!\n\n");
    
    printf("Enter number of subjects: ");
    scanf("%d", &subjectsCount);
    printf("Enter number of terms/exams completed: ");
    scanf("%d", &termsCount);

    struct Subject subjects[MAX_SUBJECTS];
    
    // Input grades
    for(int i=0;i<subjectsCount;i++){
        printf("\nEnter subject %d name: ", i+1);
        scanf("%s", subjects[i].name);
        printf("Enter grades for %d terms: ", termsCount);
        for(int j=0;j<termsCount;j++){
            scanf("%d", &subjects[i].grades[j]);
        }
        subjects[i].predictedGrade = predictNext(subjects[i], termsCount);
    }
    
    // Analyze trends, calculate overall improvement
    int totalStart = 0, totalEnd = 0;
    printf("\n--- Grade Summary ---\n");
    for(int i=0;i<subjectsCount;i++){
        char trend[20];
        analyzeTrend(subjects[i], termsCount, trend);
        printf("%s: %s, predicted next term: %.1f\n", subjects[i].name, trend, subjects[i].predictedGrade);
        totalStart += subjects[i].grades[0];
        totalEnd += subjects[i].grades[termsCount-1];
    }
    
    // Study Plan
    printf("\n--- Study Plan ---\n");
    for(int i=0;i<subjectsCount;i++){
        float hours = studyHours(subjects[i].grades[termsCount-1]);
        printf("%s: %.1f hr/day\n", subjects[i].name, hours);
    }
    
   /* // Trend Graph
    printf("\n--- Trend Graph ---\n");
    for(int i=0;i<subjectsCount;i++){
        printf("%s: ", subjects[i].name);
        for(int j=0;j<termsCount;j++){
            printBar(subjects[i].grades[j]);
            printf("0000");
        }
        printf("\n");
    }
    */

    // Motivation Messages
    printf("\nMotivation:\n");
    for(int i=0;i<subjectsCount;i++){
        char trend[20];
        analyzeTrend(subjects[i], termsCount, trend);
        printf("- %s: ", subjects[i].name);
        if(strcmp(trend,"Improving")==0) printf("Great job! Keep going!\n");
        else if(strcmp(trend,"Declining")==0) printf("Don't give up, focus on weak chapters.\n");
        else printf("Mixed trend; try to stay consistent.\n");
    }
    
    float overallPredicted = 0;
    for(int i=0;i<subjectsCount;i++) overallPredicted += subjects[i].predictedGrade;
    overallPredicted /= subjectsCount;
    float overallImprovement = ((float)(totalEnd - totalStart)/totalStart)*100;
    
    printf("\nOverall predicted next term average: %.1f\n", overallPredicted);
    printf("Overall improvement: %.1f%%\n", overallImprovement);
    
    // What-if scenario
    printf("\n--- What-If Scenario ---\n");
    int simGrades[MAX_SUBJECTS];
    printf("Enter simulated next term grades (one by one): ");
    for(int i=0;i<subjectsCount;i++) scanf("%d", &simGrades[i]);
    
   /* float newAverage = 0;
    for(int i=0;i<subjectsCount;i++) newAverage += simGrades[i];
    newAverage /= subjectsCount;
    printf("New overall average: %.1f\n", newAverage);
    */
   
    float overallPercentage = 0;
    for(int i=0;i<subjectsCount;i++){
    overallPercentage += simGrades[i];
    overallPercentage /= subjectsCount;}
    printf("New overall percentage: %.1f%%\n", overallPercentage);

    return 0;
}