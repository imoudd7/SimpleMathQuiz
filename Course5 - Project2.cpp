#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   
using namespace std;


enum enOperationType
{
    Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5
};
enum enQuestionsLevel
{
    Easy = 1, Med = 2, Hard = 3, Mix = 4
};
struct stQuestion
{
    int number1 = 0;
    int number2 = 0;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
    enOperationType OpertaionType;
    enQuestionsLevel QuestionsLevel;
};
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enOperationType OpType;
    enQuestionsLevel QueLevel;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};


short ReadHowManyQuestoins()
{
    short NumberOfQuestions = 0;

    do
    {
        cout << "How Many Questions do you want to answer? " << endl;
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}
short RandomNumber(int from, int to)
{
    short RandNum = rand() % (to - from + 1) + from;
    return RandNum;
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}



enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionsLevel;

    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?";
        cin >> QuestionsLevel;

    } while (QuestionsLevel < 1 || QuestionsLevel > 4);
    return enQuestionsLevel(QuestionsLevel);
}
enOperationType ReadOpType()
{
    short OpType;

    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
        cin >> OpType;

    } while (OpType < 1 || OpType > 5);
    return enOperationType(OpType);
}



int SimpleCalculator(int Num1, int Num2, enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return Num1 + Num2;
    case Sub:
        return Num1 - Num2;
    case Mult:
        return Num1 * Num2;
    case Div:
        return Num1 / Num2;
    default:
        return Num1 + Num2;
    }
}

string GetOpTypeText(enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mult:
        return "*";
    case Div:
        return "/";
    default:
        return "Mix";
    }
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    switch (QuestionLevel)
    {
    case Easy:
        return "Easy";
    case Med:
        return "Med";
    case Hard:
        return "Hard";
    default:
        return "Mix";
    }
}




stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = (enOperationType)RandomNumber(1, 4);
    }

    Question.OpertaionType = OpType;



    switch (QuestionLevel)
    {
    case Easy:
        Question.number1 = RandomNumber(1, 10);
        Question.number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.number1, Question.number2, Question.OpertaionType);
        Question.QuestionsLevel = enQuestionsLevel::Easy;
        return Question;

    case Med:
        Question.number1 = RandomNumber(10, 50);
        Question.number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.number1, Question.number2, Question.OpertaionType);
        Question.QuestionsLevel = enQuestionsLevel::Med;
        return Question;

    case Hard:
        Question.number1 = RandomNumber(50, 100);
        Question.number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.number1, Question.number2, Question.OpertaionType);
        Question.QuestionsLevel = enQuestionsLevel::Hard;
        return Question;
    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Qustion = 0; Qustion < Quizz.NumberOfQuestions; Qustion++)
    {
        Quizz.QuestionList[Qustion] = GenerateQuestion(Quizz.QueLevel, Quizz.OpType);
    }
}

void PrintQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << endl;
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]" << endl << endl;
    cout << Quizz.QuestionList[QuestionNumber].number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].number2 << endl;
    cout << " " << GetOpTypeText(Quizz.QuestionList[QuestionNumber].OpertaionType);
    cout << endl << "_________" << endl;
}

int ReadQustionAnswer()
{
    int answer;
    cin >> answer;
    return answer;
}


void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
        system("color 4F");
}



void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :(" << endl;
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :)" << endl;
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}



void AskAndCorrectQuestionsListAnswer(stQuizz& Quizz)
{
    for (short QuistionNumber = 0; QuistionNumber < Quizz.NumberOfQuestions; QuistionNumber++)
    {
        PrintQuestion(Quizz, QuistionNumber);
        Quizz.QuestionList[QuistionNumber].PlayerAnswer = ReadQustionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuistionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsTest(bool Pass)
{
    if (Pass)
    {
        return "Pass :)";
    }
    else
    {
        return "Fail :(";
    }
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << endl;
    cout << "____________________________________" << endl << endl;
    cout << "Final Results is " << GetFinalResultsTest(Quizz.isPass);
    cout << endl;

    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QueLevel) << endl;
    cout << "Op Type            : " << GetOpTypeText(Quizz.OpType) << endl;
    cout << "Number of right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "____________________________________" << endl << endl;
}




void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestoins();
    Quizz.QueLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionsListAnswer(Quizz);
    PrintQuizzResults(Quizz);
}
void StartGame()
{
    char PlayAgain = 'y';

    do
    {

        ResetScreen();
        PlayMathGame();

        cout << endl << "\t\t\tDo you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}




int main()
{
    srand((unsigned)time(NULL));

    StartGame();
}