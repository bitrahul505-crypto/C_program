#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define TOTAL_LEVELS 30

void clearScreen(void);
void waitMilliseconds(int milliseconds);
void printLine(char symbol, int length);
void printTitle(void);
void printLevelHeader(int level);
void showInstructions(void);
void displayFinalResults(int completedLevels, double totalScore,
                         double totalTime, int totalQuestions,
                         int totalCorrect);

void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitMilliseconds(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    clock_t start;
    clock_t delay;

    start = clock();
    delay = (clock_t)((double)milliseconds *
                      (double)CLOCKS_PER_SEC / 1000.0);

    while ((clock() - start) < delay)
    {
    }
#endif
}

void printLine(char symbol, int length)
{
    int i;

    for (i = 0; i < length; i++)
        printf("%c", symbol);

    printf("\n");
}

void printTitle(void)
{
    clearScreen();

    printf("\n");
    printLine('=', 72);
    printf("                 QUICK MATH CHALLENGE\n");
    printLine('=', 72);
    printf("             ATTENTION & PROCESSING GAME\n");
    printLine('-', 72);
    printf("              30 LEVELS  |  SCORE / 100\n");
    printLine('=', 72);
    printf("\n");
}

void printLevelHeader(int level)
{
    printf("\n");
    printLine('-', 72);
    printf("                         LEVEL %02d / %02d\n",
           level, TOTAL_LEVELS);
    printLine('-', 72);
}

void showInstructions(void)
{
    printTitle();

    printf("HOW TO PLAY\n");
    printLine('-', 72);

    printf("1. Each level contains a mathematical question.\n");
    printf("2. Solve the question as quickly and accurately as possible.\n");
    printf("3. Difficulty increases as the levels progress.\n");
    printf("4. Later levels use larger numbers and harder operations.\n");
    printf("5. Taking longer than the target time causes a time penalty.\n");
    printf("6. An incorrect answer receives an accuracy deduction.\n");
    printf("7. Each completed level is scored out of 100.00.\n");
    printf("8. Before each level, press ENTER to play.\n");
    printf("9. Press 2 and ENTER to exit before starting that level.\n");
    printf("10. Final statistics use only completed levels.\n");

    printLine('-', 72);

    printf("\nPress ENTER to start the game...");
    getchar();
}

int main(void)
{
    int level;
    int completedLevels;
    int totalQuestions;
    int totalCorrect;

    int operation;
    int maxNumber;
    int answer;
    int correctAnswer;

    int choice;
    int displayDelay;

    double levelScore;
    double totalScore;
    double totalTime;
    double answerTime;
    double targetTime;

    double accuracy;
    double timePenalty;
    double errorPenalty;

    double userAnswer;

    char input[100];

    clock_t gameStart;
    clock_t gameEnd;
    clock_t answerStart;
    clock_t answerEnd;

    srand((unsigned int)time(NULL));

    completedLevels = 0;
    totalQuestions = 0;
    totalCorrect = 0;
    totalScore = 0.0;

    printTitle();

    printf("Press ENTER to view instructions...");
    getchar();

    showInstructions();

    gameStart = clock();

    for (level = 1; level <= TOTAL_LEVELS; level++)
    {
        printTitle();
        printLevelHeader(level);

        printf("\n");
        printf("Press ENTER to start Level %02d\n", level);
        printf("Press 2 and ENTER to exit the game\n");
        printf("\nChoice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        if (input[0] == '2')
            break;

        if (level <= 5)
        {
            maxNumber = 10;
            targetTime = 5.00;
            displayDelay = 800;
        }
        else if (level <= 10)
        {
            maxNumber = 20;
            targetTime = 4.50;
            displayDelay = 750;
        }
        else if (level <= 15)
        {
            maxNumber = 40;
            targetTime = 4.00;
            displayDelay = 700;
        }
        else if (level <= 20)
        {
            maxNumber = 60;
            targetTime = 3.50;
            displayDelay = 650;
        }
        else if (level <= 25)
        {
            maxNumber = 100;
            targetTime = 3.00;
            displayDelay = 600;
        }
        else
        {
            maxNumber = 150;
            targetTime = 2.50;
            displayDelay = 550;
        }

        operation = rand() % 4;

        if (operation == 0)
        {
            int a;
            int b;

            a = 1 + rand() % maxNumber;
            b = 1 + rand() % maxNumber;

            correctAnswer = a + b;

            clearScreen();

            printf("\n");
            printLine('=', 72);
            printf("                         SOLVE!\n");
            printLine('=', 72);

            printf("\n");
            printf("Level             : %02d\n", level);
            printf("Target Time       : %.2f seconds\n", targetTime);

            printf("\n");
            printf("                       %d + %d = ?\n", a, b);

            printf("\n");
            printLine('-', 72);

            waitMilliseconds(displayDelay);
        }
        else if (operation == 1)
        {
            int a;
            int b;

            a = 1 + rand() % maxNumber;
            b = 1 + rand() % maxNumber;

            if (b > a)
            {
                int temp;
                temp = a;
                a = b;
                b = temp;
            }

            correctAnswer = a - b;

            clearScreen();

            printf("\n");
            printLine('=', 72);
            printf("                         SOLVE!\n");
            printLine('=', 72);

            printf("\n");
            printf("Level             : %02d\n", level);
            printf("Target Time       : %.2f seconds\n", targetTime);

            printf("\n");
            printf("                       %d - %d = ?\n", a, b);

            printf("\n");
            printLine('-', 72);

            waitMilliseconds(displayDelay);
        }
        else if (operation == 2)
        {
            int a;
            int b;

            if (level <= 10)
            {
                a = 1 + rand() % 10;
                b = 1 + rand() % 10;
            }
            else if (level <= 20)
            {
                a = 1 + rand() % 15;
                b = 1 + rand() % 12;
            }
            else
            {
                a = 1 + rand() % 20;
                b = 1 + rand() % 15;
            }

            correctAnswer = a * b;

            clearScreen();

            printf("\n");
            printLine('=', 72);
            printf("                         SOLVE!\n");
            printLine('=', 72);

            printf("\n");
            printf("Level             : %02d\n", level);
            printf("Target Time       : %.2f seconds\n", targetTime);

            printf("\n");
            printf("                       %d x %d = ?\n", a, b);

            printf("\n");
            printLine('-', 72);

            waitMilliseconds(displayDelay);
        }
        else
        {
            int divisor;
            int multiplier;

            divisor = 1 + rand() % 12;
            multiplier = 1 + rand() % 12;

            correctAnswer = multiplier;

            clearScreen();

            printf("\n");
            printLine('=', 72);
            printf("                         SOLVE!\n");
            printLine('=', 72);

            printf("\n");
            printf("Level             : %02d\n", level);
            printf("Target Time       : %.2f seconds\n", targetTime);

            printf("\n");
            printf("                       %d / %d = ?\n",
                   divisor * multiplier, divisor);

            printf("\n");
            printLine('-', 72);

            waitMilliseconds(displayDelay);
        }

        clearScreen();

        printf("\n");
        printLine('=', 72);
        printf("                         ANSWER\n");
        printLine('=', 72);

        printf("\n");
        printf("Level             : %02d\n", level);
        printf("Target Time       : %.2f seconds\n", targetTime);

        printf("\n");
        printf("Your answer: ");

        answerStart = clock();

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        answerEnd = clock();

        answerTime =
            (double)(answerEnd - answerStart) /
            (double)CLOCKS_PER_SEC;

        userAnswer = atof(input);

        answer = (int)round(userAnswer);

        if (answer == correctAnswer)
            totalCorrect++;
        
        totalQuestions++;

        if (answer == correctAnswer)
        {
            accuracy = 100.0;
            errorPenalty = 0.0;
        }
        else
        {
            accuracy = 0.0;
            errorPenalty = 40.0;
        }

        timePenalty = 0.0;

        if (answerTime > targetTime)
        {
            timePenalty =
                (answerTime - targetTime) * 8.0;
        }

        levelScore = accuracy - errorPenalty + 100.0 - accuracy;

        if (answer == correctAnswer)
            levelScore = 100.0;
        else
            levelScore = 0.0;

        if (answer == correctAnswer && answerTime > targetTime)
            levelScore -= timePenalty;

        if (answer != correctAnswer)
        {
            double partialTimeScore;

            partialTimeScore = 0.0;

            if (answerTime < targetTime)
            {
                partialTimeScore =
                    (targetTime - answerTime) * 2.0;

                if (partialTimeScore > 10.0)
                    partialTimeScore = 10.0;
            }

            levelScore = partialTimeScore;
        }

        if (levelScore < 0.0)
            levelScore = 0.0;

        if (levelScore > 100.0)
            levelScore = 100.0;

        totalScore += levelScore;
        completedLevels++;

        clearScreen();

        printf("\n");
        printLine('=', 72);
        printf("                       LEVEL RESULT\n");
        printLine('=', 72);

        printf("\n");
        printf("Level                 : %02d\n", level);
        printf("Correct Answer        : %d\n", correctAnswer);
        printf("Your Answer           : %d\n", answer);
        printf("Answer Time           : %.2f seconds\n", answerTime);
        printf("Target Time           : %.2f seconds\n", targetTime);

        printf("\n");

        if (answer == correctAnswer)
            printf("Accuracy              : 100.00%%\n");
        else
            printf("Accuracy              : 0.00%%\n");

        printf("Time Penalty          : %.2f points\n", timePenalty);
        printf("Error Deduction       : %.2f points\n", errorPenalty);

        printf("\n");
        printLine('-', 72);
        printf("LEVEL SCORE           : %.2f / 100.00\n",
               levelScore);
        printLine('-', 72);

        if (level < TOTAL_LEVELS)
        {
            printf("\nPress ENTER to continue...");
            getchar();
        }
    }

    gameEnd = clock();

    totalTime =
        (double)(gameEnd - gameStart) /
        (double)CLOCKS_PER_SEC;

    displayFinalResults(
        completedLevels,
        totalScore,
        totalTime,
        totalQuestions,
        totalCorrect
    );

    return 0;
}

void displayFinalResults(int completedLevels,
                         double totalScore,
                         double totalTime,
                         int totalQuestions,
                         int totalCorrect)
{
    double averageScore;
    double overallAccuracy;

    averageScore = 0.0;
    overallAccuracy = 0.0;

    if (completedLevels > 0)
    {
        averageScore =
            totalScore / (double)completedLevels;
    }

    if (totalQuestions > 0)
    {
        overallAccuracy =
            ((double)totalCorrect /
             (double)totalQuestions) * 100.0;
    }

    clearScreen();

    printf("\n");
    printLine('=', 72);
    printf("                       FINAL RESULTS\n");
    printLine('=', 72);

    printf("\n");

    if (completedLevels == 0)
    {
        printf("No levels were completed.\n");
    }
    else
    {
        printf("Completed Levels       : %d / %d\n",
               completedLevels, TOTAL_LEVELS);

        printf("Total Questions        : %d\n",
               totalQuestions);

        printf("Correct Answers        : %d\n",
               totalCorrect);

        printf("Overall Accuracy       : %.2f%%\n",
               overallAccuracy);

        printf("Total Time Taken       : %.2f seconds\n",
               totalTime);

        printf("Total Score            : %.2f\n",
               totalScore);

        printf("Average Score          : %.2f / 100.00\n",
               averageScore);

        printf("\n");
        printLine('-', 72);

        if (averageScore >= 90.0)
            printf("                 PERFORMANCE: EXCELLENT\n");
        else if (averageScore >= 75.0)
            printf("                 PERFORMANCE: VERY GOOD\n");
        else if (averageScore >= 60.0)
            printf("                 PERFORMANCE: GOOD\n");
        else if (averageScore >= 40.0)
            printf("                 PERFORMANCE: MODERATE\n");
        else
            printf("                 PERFORMANCE: NEEDS PRACTICE\n");

        printLine('-', 72);

        printf("\n");
        printf("Average response time is included in the\n");
        printf("level-by-level timing and scoring calculations.\n");
    }

    printf("\n");
    printLine('=', 72);
    printf("                    GAME COMPLETED\n");
    printLine('=', 72);

    printf("\nThank you for playing!\n\n");
}
