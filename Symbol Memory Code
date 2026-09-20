#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

#define TOTAL_LEVELS 30
#define MAX_SYMBOLS 7
#define MAX_INPUT 100

void clearScreen(void);
void pauseProgram(void);
void waitMilliseconds(int ms);
void printLine(char ch, int n);
void printTitle(void);
void printLevelHeader(int level);
void generateSymbols(char symbols[], int count);
void shuffleArray(char symbols[], int count);
double calculateScore(int correct, int total, double answerTime, double targetTime);
void displayResults(int completedLevels, double totalScore, double totalTime, int totalCorrect, int totalSymbols);
void showInstructions(void);

void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseProgram(void)
{
    printf("\nPress ENTER to continue...");
    getchar();
}

void waitMilliseconds(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    clock_t start = clock();
    clock_t delay = (clock_t)((double)ms * CLOCKS_PER_SEC / 1000.0);
    while (clock() - start < delay)
    {
    }
#endif
}

void printLine(char ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
    printf("\n");
}

void printTitle(void)
{
    clearScreen();

    printf("\n");
    printLine('=', 70);
    printf("                 SYMBOL MEMORY GAME\n");
    printLine('=', 70);
    printf("             30-LEVEL MEMORY CHALLENGE\n");
    printLine('-', 70);
    printf("              Recall • Accuracy • Speed\n");
    printLine('=', 70);
    printf("\n");
}

void printLevelHeader(int level)
{
    printf("\n");
    printLine('-', 70);
    printf("                         LEVEL %02d / %02d\n", level, TOTAL_LEVELS);
    printLine('-', 70);
}

void generateSymbols(char symbols[], int count)
{
    const char available[] =
        "@#$%%&*+=!?ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int length = (int)strlen(available);
    int i;
    int j;
    int duplicate;

    for (i = 0; i < count; i++)
    {
        do
        {
            duplicate = 0;
            symbols[i] = available[rand() % length];

            for (j = 0; j < i; j++)
            {
                if (symbols[j] == symbols[i])
                {
                    duplicate = 1;
                    break;
                }
            }
        } while (duplicate);
    }

    symbols[count] = '\0';
}

void shuffleArray(char symbols[], int count)
{
    int i;
    int j;
    char temp;

    for (i = count - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = symbols[i];
        symbols[i] = symbols[j];
        symbols[j] = temp;
    }
}

double calculateScore(int correct, int total, double answerTime, double targetTime)
{
    double accuracy;
    double score;
    double errorDeduction;
    double timePenalty = 0.0;

    if (total <= 0)
        return 0.0;

    accuracy = ((double)correct / (double)total) * 100.0;

    errorDeduction = (double)(total - correct) * 10.0;

    score = accuracy - errorDeduction;

    if (answerTime > targetTime)
    {
        timePenalty = (answerTime - targetTime) * 2.0;
        score -= timePenalty;
    }

    if (score < 0.0)
        score = 0.0;

    if (score > 100.0)
        score = 100.0;

    return score;
}

void showInstructions(void)
{
    printTitle();

    printf("HOW TO PLAY\n\n");
    printf("1. You will see a sequence of symbols.\n");
    printf("2. Memorize the symbols and their exact order.\n");
    printf("3. The symbols will disappear after a short time.\n");
    printf("4. Type the sequence exactly as you remember it.\n");
    printf("5. Your score depends on accuracy and response time.\n");
    printf("6. Every symbol error reduces your score.\n");
    printf("7. Taking longer than the target time causes a time penalty.\n");
    printf("8. Before each level, press ENTER to play.\n");
    printf("9. Press 2 before a level to exit the game.\n");
    printf("10. The final average uses only completed levels.\n");

    printf("\n");
    printLine('-', 70);
    printf("Press ENTER to start the game.\n");
    printLine('-', 70);

    getchar();
}

void displayResults(int completedLevels, double totalScore, double totalTime, int totalCorrect, int totalSymbols)
{
    double averageScore = 0.0;
    double accuracy = 0.0;

    if (completedLevels > 0)
        averageScore = totalScore / (double)completedLevels;

    if (totalSymbols > 0)
        accuracy = ((double)totalCorrect / (double)totalSymbols) * 100.0;

    clearScreen();

    printf("\n");
    printLine('=', 70);
    printf("                       FINAL RESULTS\n");
    printLine('=', 70);

    if (completedLevels == 0)
    {
        printf("\nNo levels were completed.\n");
        printf("No performance score can be calculated.\n");
    }
    else
    {
        printf("\nCompleted Levels       : %d / %d\n", completedLevels, TOTAL_LEVELS);
        printf("Total Time Taken      : %.2f seconds\n", totalTime);
        printf("Overall Accuracy      : %.2f%%\n", accuracy);
        printf("Total Correct Symbols : %d / %d\n", totalCorrect, totalSymbols);
        printf("Total Score           : %.2f\n", totalScore);
        printf("Average Score         : %.2f / 100.00\n", averageScore);

        printf("\n");
        printLine('-', 70);

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

        printLine('-', 70);
    }

    printf("\n");
    printf("Thank you for playing the Symbol Memory Game!\n");
    printLine('=', 70);
}

int main(void)
{
    int level;
    int completedLevels = 0;
    int symbolCount;
    int displayTime;
    int correct;
    int i;
    int choice;
    int errorCount;
    int totalCorrect = 0;
    int totalSymbols = 0;

    double totalScore = 0.0;
    double levelScore;
    double answerTime;
    double targetTime;

    char symbols[MAX_SYMBOLS + 1];
    char answer[MAX_INPUT];
    char levelChoice[10];

    clock_t gameStart;
    clock_t answerStart;
    clock_t answerEnd;

    srand((unsigned int)time(NULL));

    printTitle();

    printf("Press ENTER to view instructions...");
    getchar();

    showInstructions();

    gameStart = clock();

    for (level = 1; level <= TOTAL_LEVELS; level++)
    {
        printTitle();
        printLevelHeader(level);

        printf("\nPress ENTER to continue to Level %d\n", level);
        printf("Press 2 and ENTER to exit the game\n");
        printf("\nYour choice: ");

        if (fgets(levelChoice, sizeof(levelChoice), stdin) == NULL)
            break;

        if (levelChoice[0] == '2')
            break;

        symbolCount = 3 + (level - 1) / 7;

        if (symbolCount > MAX_SYMBOLS)
            symbolCount = MAX_SYMBOLS;

        displayTime = 3000 - ((level - 1) * 70);

        if (displayTime < 1000)
            displayTime = 1000;

        targetTime = 4.0 + ((double)symbolCount * 0.7);

        generateSymbols(symbols, symbolCount);

        clearScreen();

        printf("\n");
        printLine('=', 70);
        printf("                         MEMORIZE!\n");
        printLine('=', 70);

        printf("\n");
        printf("Level          : %02d\n", level);
        printf("Symbols        : %d\n", symbolCount);
        printf("Display Time   : %.2f seconds\n", (double)displayTime / 1000.0);

        printf("\n");
        printf("                    ");

        for (i = 0; i < symbolCount; i++)
        {
            printf("[%c] ", symbols[i]);
        }

        printf("\n\n");
        printLine('-', 70);

        waitMilliseconds(displayTime);

        clearScreen();

        printf("\n");
        printLine('=', 70);
        printf("                         RECALL!\n");
        printLine('=', 70);

        printf("\n");
        printf("Level %02d\n", level);
        printf("Enter the %d symbols in the EXACT order.\n", symbolCount);
        printf("\nYour answer: ");

        answerStart = clock();

        if (fgets(answer, sizeof(answer), stdin) == NULL)
            break;

        answerEnd = clock();

        answer[strcspn(answer, "\n")] = '\0';

        answerTime =
            (double)(answerEnd - answerStart) / (double)CLOCKS_PER_SEC;

        correct = 0;

        for (i = 0; i < symbolCount; i++)
        {
            if (answer[i] != '\0')
            {
                if (answer[i] == symbols[i])
                    correct++;
            }
        }

        errorCount = symbolCount - correct;

        levelScore = calculateScore(
            correct,
            symbolCount,
            answerTime,
            targetTime
        );

        completedLevels++;

        totalScore += levelScore;
        totalCorrect += correct;
        totalSymbols += symbolCount;

        clearScreen();

        printf("\n");
        printLine('=', 70);
        printf("                       LEVEL RESULT\n");
        printLine('=', 70);

        printf("\n");
        printf("Level                 : %02d\n", level);
        printf("Symbols               : %d\n", symbolCount);
        printf("Correct Symbols       : %d\n", correct);
        printf("Symbol Errors         : %d\n", errorCount);
        printf("Target Answer Time    : %.2f seconds\n", targetTime);
        printf("Actual Answer Time    : %.2f seconds\n", answerTime);
        printf("Time Difference       : %.2f seconds\n", answerTime - targetTime);

        printf("\n");
        printLine('-', 70);

        printf("LEVEL SCORE            : %.2f / 100.00\n", levelScore);

        printLine('-', 70);

        if (level < TOTAL_LEVELS)
        {
            printf("\nPress ENTER to continue to the next level...");
            getchar();
        }
    }

    {
        clock_t gameEnd = clock();
        double totalGameTime =
            (double)(gameEnd - gameStart) / (double)CLOCKS_PER_SEC;

        totalScore = totalScore;

        displayResults(
            completedLevels,
            totalScore,
            totalGameTime,
            totalCorrect,
            totalSymbols
        );
    }

    return 0;
}
