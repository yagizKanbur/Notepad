#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

char fileName[25];
char openFileName[25];

struct sentence {
    struct sentence *next;
    struct sentence *prev;
    char letter;
};

struct sentence *currentLetter;
struct sentence *headCut = NULL;
struct sentence *lastCut = NULL;
struct sentence *currentCut = NULL;
struct sentence *headEnter = NULL;
struct sentence *currentEnter = NULL;
struct sentence *lastEnter = NULL;

struct line{
    struct line *next;
    struct line *prev;
    struct sentence *headLetter;
    struct sentence *lastLetter;
    int whereLine;
};

struct line *headLine;
struct line *lastLine;
struct line *currentLine;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

void goX(int x)
{
    currentLetter = currentLine->headLetter;

    for (int i=1; i<x; i++)
    {
        currentLetter = currentLetter->next;
    }
}

int lengthOfLine ()
{
    int length = 0;
    struct line *spec;
    if (headLine == currentLine && headLine->next != NULL)
    {
        length = 0;
    }
    else
    {
        for (spec = headLine; spec!=currentLine; spec = spec->next)
        {
            length++;
        }
    }
    return length;
}

int lengthOfSentence()
{
    int length = 0;
    struct sentence *spec;
    if (currentLine->headLetter == NULL)
    {
        length = 0;
    }
    else
    {
        length = 1;
        for (spec = currentLine->headLetter; spec != currentLetter; spec = spec->next)
        {
            length++;
        }
        if(currentLetter->letter =='\n')
            length --;
    }
    return length;
}

bool isEmptySentence ()
{
    if (currentLine->headLetter == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void display ()
{
    system("CLS");
    struct line *i;
    struct sentence *j;

    for (i = headLine; i!=NULL; i = i->next)
    {
        for (j = i->headLetter; j!=NULL; j = j->next)
        {
            printf("%c",j->letter);
        }

    }
}

void deleteEnter (char data)
{
    struct sentence *link = malloc(sizeof(struct sentence));
    link->letter = data;

    if (headEnter == NULL)
    {
        headEnter = lastEnter = link;
        link->next = NULL;
        link->prev = NULL;

    }
    else if (headEnter != NULL)
    {
        link->next = NULL;
        lastEnter->next = link;
        link->prev = lastEnter;
        lastEnter = link;
    }
}

void insertFirstLine ()
{
    struct line *link = malloc(sizeof(struct line));

    headLine = currentLine = lastLine = link;
    link->next = NULL;
    link->prev = NULL;
    link->headLetter = NULL;
    link->lastLetter = NULL;
    currentLetter = currentLine->lastLetter = currentLine->headLetter;
}

void insertLine ()
{
    struct line *link = malloc(sizeof(struct line));
    if (currentLetter==currentLine->lastLetter)
    {
        if (currentLine != lastLine)
        {
            link->next = currentLine->next;
            link->prev = currentLine;
            currentLine->next->prev = link;
            currentLine->next = link;
            currentLine = link;
            link->headLetter = NULL;
            link->lastLetter = NULL;
            currentLetter = link->lastLetter = link->headLetter;
        }
        else
        {
            lastLine->next = link;
            link->next = NULL;
            link->prev = lastLine;
            link->headLetter = NULL;
            link->lastLetter = NULL;
            lastLine = currentLine = link;
            currentLetter = link->lastLetter = link->headLetter;
        }
    }
    else
    {
        if (currentLine != lastLine)
        {
        }
        else
        {
        }
    }
}

void deleteLine ()
{
    if (currentLine!=lastLine)
    {
        /// ortadaki satiri silme islemi
        currentLine->next->prev = currentLine->prev;
        currentLine->prev->next = currentLine->next;
        currentLine = currentLine->prev;
        currentLetter = currentLine->lastLetter;
    }
    else if(currentLine==headLine && headLine->next == NULL)
    {
        headLine=NULL;
        lastLine=NULL;
        currentLine=headLine=lastLine;
        currentLetter=NULL;
    }
    else
    {
        lastLine->prev->next = NULL;
        lastLine = lastLine->prev;
        currentLine = lastLine;
        currentLetter = currentLine->lastLetter;
    }
}

void insertLetter (char data)
{
    struct sentence *link = malloc(sizeof(struct sentence));
    link->letter = data;

    /// basa harf ekleme
    if (isEmptySentence())
    {
        /// Ilk harf ekleme
        currentLine->headLetter = link;
        currentLine->lastLetter = link;
        currentLetter = link;
        link->next = NULL;
        link->prev = NULL;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
    else if (currentLetter != currentLine->lastLetter && currentLetter != currentLine->headLetter)
    {
        /// araya ekleme
        link->next = currentLetter->next;
        link->prev = currentLetter;
        link->next->prev = link;
        currentLetter->next = link;
        currentLetter = link;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
    else if (currentLetter == currentLine->lastLetter && currentLetter->letter != '\n')
    {
        /// sona ekleme
        link->next = NULL;
        currentLine->lastLetter->next = link;
        link->prev = currentLine->lastLetter;
        currentLine->lastLetter = link;
        currentLetter = link;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
    else if (currentLetter == currentLine->lastLetter && currentLetter->letter == '\n')
    {
        /// sonda \ n varsa sona ekleme
        link->next = currentLetter->next;
        link->prev = currentLetter;
        link->next->prev = link;
        currentLetter->next = link;
        currentLetter = link;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
    else if (currentLetter != NULL && currentLetter == currentLine->headLetter)
        {
            /// Ikinci harf varsa basa harf ekleme
            currentLine->headLetter->prev = link;
            link->next = currentLine->headLetter;
            link->prev = NULL;
            currentLine->headLetter = link;
            currentLetter = link;
            gotoxy(lengthOfSentence(),lengthOfLine());
        }
}

void deleteLetter ()
{
    if (currentLetter == currentLine->lastLetter)
    {
        if (currentLine->headLetter == NULL)
        {
            gotoxy(0,0);
        }
        else if(currentLetter == currentLine->headLetter && currentLine == headLine)
        {
            currentLine->headLetter = NULL;
            currentLine->lastLetter = NULL;
        }
        else if (currentLetter == currentLine->headLetter && currentLine != headLine)
        {
            currentLine->headLetter = NULL;
            currentLine->lastLetter = NULL;
            deleteLine();
            currentLetter = currentLine->lastLetter;
        }
        else
        {
            currentLetter->prev->next = NULL;
            currentLetter = currentLetter->prev;
            currentLine->lastLetter = currentLetter;
        }
    }
    else if (currentLetter != currentLine->lastLetter && currentLetter != currentLine->headLetter)
    {
        if (currentLetter->prev == currentLine->headLetter)
        {
            currentLetter->next->prev = currentLetter->prev;
            currentLetter->prev->next = currentLetter->next;
            currentLetter->next = NULL;
            currentLetter = currentLetter->prev;
            currentLine->headLetter = currentLetter;
        }
        else
        {
            currentLetter->next->prev = currentLine->prev;
            currentLetter->prev->next = currentLetter->next;
            currentLetter->next = NULL;
            currentLetter = currentLetter->prev;
        }
    }
    else if (currentLetter != currentLine->lastLetter && currentLetter == currentLine->headLetter)
    {
        if (currentLine == headLine)
        {
            if (currentLetter->next == currentLine->lastLetter)
            {
                currentLetter->next->prev = NULL;
                currentLetter = currentLetter->next;
                currentLine->headLetter = currentLetter;
                currentLine->lastLetter = currentLetter;
            }
            else
            {
                currentLetter->next->prev = NULL;
                currentLetter = currentLetter->next;
                currentLine->headLetter = currentLetter;
            }
        }
        else if (currentLine->headLetter == NULL || currentLine->headLetter == '\n' || currentLine->lastLetter == NULL)
        {
            deleteLine();
            deleteLetter();
            currentLetter = currentLine->lastLetter;
        }
    }
}

void newFile ()
{
    int VKcontrol = 0;
    int control;
    while (1)
    {

        if (_kbhit())
        {
        VKcontrol = 0;
        control = _getch();
        if(control == 224)
        {
            continue;
        }
        if (control == 13)
        {
            insertLetter('\n');
            insertLine();
            display();
        }
        else if (control == 8)
        {
            deleteLetter();
            display();
            gotoxy(lengthOfSentence(),lengthOfLine());
        }
        else if (control == 27)
        {
            menu_interface();
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            goLeft();
            Sleep(200);
            VKcontrol = 1;
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            goUp();
            Sleep(200);
            VKcontrol = 1;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            goRight();
            Sleep(200);
            VKcontrol = 1;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            goDown();
            Sleep(200);
            VKcontrol = 1;
        }
        else // if (VKcontrol != 1)
        {
            insertLetter(control);
            display();
            gotoxy(lengthOfSentence(),lengthOfLine());
        }
        }
    }
}

void goLeft ()
{
    if (currentLetter == currentLine->headLetter && currentLine == headLine)
    {
        gotoxy(0,0);
    }
    else if (currentLetter == currentLine->headLetter && currentLine != headLine)
    {
        currentLine = currentLine->prev;
        currentLetter = currentLine->lastLetter;
        gotoxy(0,lengthOfLine()+1);
    }
    else if (currentLetter == '\n')
    {
        currentLetter = currentLetter->prev;
    }
    else
    {
        currentLetter = currentLetter->prev;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
}

void goRight ()
{
    if (currentLetter == currentLine->lastLetter && currentLine != lastLine)
    {
        currentLine = currentLine->next;
        currentLetter = currentLine->lastLetter;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
    else if (currentLetter != currentLine->lastLetter)
    {
        currentLetter = currentLetter->next;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
}

void goUp ()
{
    if (currentLine == headLine)
    {
        currentLetter = currentLine->headLetter;
        gotoxy(0,lengthOfLine());
    }
    else
    {
        currentLine = currentLine->prev;
        currentLetter = currentLine->lastLetter;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
}

void goDown ()
{
    if (currentLine == lastLine)
    {
        currentLetter = currentLine->lastLetter;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
    else
    {
        currentLine=currentLine->next;
        currentLetter = currentLine->lastLetter;
        gotoxy(lengthOfSentence(),lengthOfLine());
    }
}


void menu_interface ()
{
    system("CLS");
    int selection;
    printf ("1- Continue on Last File\n");
    printf ("2- New File\n");
    printf ("3- Save File\n");
    printf ("4- Open File\n");
    int select = selection_warning();
    menu(select);
}

int selection_warning ()
{
    int selection;
    printf("What Do You Want To Do:");
    scanf("%d",&selection);
    if (selection>4 || selection<1)
    {
        system("CLS");
        printf("Warning: You need to enter valid numbers\n");
        menu_interface();
    }
    return selection;
}

void menu (int selection)
{
    switch (selection)
    {
    case 1:
        continueOnFile();
        break;
    case 2:
        system("CLS");
        insertFirstLine ();
        newFile ();
        break;
    case 3:
        saveInterface();
        saveFile();
        break;
    case 4:
        openInterface();
        openFile();
        break;
    }
}

void continueOnFile()
{
    display();
    newFile();
}

void saveInterface ()
{
    printf("Dosya ismi giriniz: ");
    scanf("%s",fileName);
}

void openInterface ()
{
    printf("Dosya ismi giriniz: ");
    scanf("%s",openFileName);
}

void saveFile()
{
    FILE *fForSave;
    fForSave = fopen(fileName,"w+");
    struct line *v1;
    struct sentence *v2;
    for (v1 = headLine; v1 != NULL ; v1 = v1->next)
    {
        for (v2 = v1->headLetter; v2 != NULL; v2 = v2->next)
        {
            fputc(v2->letter,fForSave);
        }
    }
    fputc('\0',fForSave);
    fclose(fForSave);
    menu_interface();
}

void openFile()
{
    FILE *fForOpen;

    char data;

    fForOpen = fopen(openFileName,"r+");
    insertFirstLine();
    while (1)
    {
        data = fgetc(fForOpen);
        if (data == '\n')
        {
            insertLetter(data);
            insertLine();
            display();
        }
        else if (data == '\0')
        {
            goto endWhile;
        }
        else
        {
            insertLetter(data);
            display();
        }
    }
    endWhile :
    fclose(fForOpen);

    display();

    gotoxy(lengthOfSentence(),lengthOfLine());
    newFile();
}

int main ()
{
    menu_interface();
    return 0;
}
