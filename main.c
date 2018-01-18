/*
-------------------------------------------------------------------------------------------------------------------------------------------------
						Project Name - Sudocu Puzzle Game

						CODED BY - Mr.ari

						Date - 6th jan,2018
----------------------------------------------------------------------------------------------------------------------------------------------
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<malloc.h>
#include"random.c"
#include"swaping.c"
#include"mgmtFile.c"
#define LEVEL_ONE 40
#define LEVEL_TWO 35
#define LEVEL_THREE 30
#define LEVEL_FOUR 25
#define LEVEL_FIVE 20
#define MAX_SWAP_SIDE 4

//function Prototypes
int levelDefine(int tnum); //Return the number of knowns to show in sudocu according to level
void printSudocuInFile(FILE *fp,int *originArray,int *sudocuPuz,int size,int tnum); //Print a sudocu Puzzle in the file
void generateSudocu(int *a,int size); //Generate a sudocu by means of 2D array
void generateSudocuPuz(int *a,int *b,int size,int levelNum); //Generates the sudocu puzzle
void generateSudocuAgain(int *originArray,int size); //if user press "continue game" then generates sudocu puzzle again

int main(){
  //variables declarations;
  int tnum=0,firstChoice,secondChoice,thirdChoice,flag=1,checkForZero;
  FILE *fp;
  int arrayNine[9][9] = {{1,5,4,8,7,3,2,9,6},{3,8,6,5,9,2,7,1,4},{7,2,9,6,4,1,8,3,5},
                          {8,6,3,7,2,5,1,4,9},{9,7,5,3,1,4,6,2,8},{4,1,2,9,6,8,3,5,7},
                           {6,3,1,4,5,7,9,8,2},{5,9,8,2,3,6,4,7,1},{2,4,7,1,8,9,5,6,3}};
  int puzzle[9][9] = {0};int checkPuzzle[9][9] = {0};
  int *originArray = &arrayNine[0][0];
  int *sudocuPuz = &puzzle[0][0];
  printf("\t\t\tWelcome\n\n");
  while (1){
  printf("Enter your choice:\n\t1.New Game\n\t2.Continue\n\t3.Exit\n");
  scanf("%d",&firstChoice);
  switch (firstChoice) {
    case 1://for New game
      fp = fopen("sudocuPuzz.txt","w");
      while (tnum < 1 || tnum >5){
      printf("Choose Level:\n\t1.Level One\n\t2.Level Two\n\t3.Level Three\n\t4.Level Four\n\t5.Level Five\n");
      scanf("%d",&tnum);
      }
      tnum = levelDefine(tnum);
      printSudocuInFile(fp,originArray,sudocuPuz,9,tnum);
      flag = 0;
      fclose(fp);
    case 2://for continue;
      if (flag) generateSudocuAgain(originArray,9);
      printf("Open the file SudocuPuzzle.txt and Solve the Puzzle and save it by pressing ctrl+s\n");
      secondChoice = 1;
      while(secondChoice){
      printf("Enter your choice :\n\t1.Check Puzzle\n\t2.Show the solution\n\t3.Back to Main menu\n\t4.exit\n");
      scanf("%d",&secondChoice);
      switch(secondChoice){
        case 1:
        checkForZero = getArrayFromFile("sudocuPuzz.txt",&checkPuzzle[0][0],9);
        if(!checkForZero){
          printf("Your Puzzle is not completed...\nPress 1 to start a New Game\npress 2 to Solve the same Puzzle\npress 3 to save and exit\n");
          scanf("%d",&thirdChoice);
          if (thirdChoice == 1) {firstChoice = 1;secondChoice = 0;}
          else if (thirdChoice == 2) {firstChoice =2;secondChoice = 0;}
          if (thirdChoice == 3) exit(0);
        }
        else{
          if (compareArray(&checkPuzzle[0][0],originArray,9)) printf("SORRY ! Better Luck Next time....\n");
          else printf("WOW!!You are a Genius\n");
        }
        break;
        case 2:
        fp = fopen("sudocuPuzz.txt","a");
        printSudocuPuzzle(fp,originArray,9,3);
        printf("Check the file sudocuPuzz.txt\n");
        fclose(fp);
        fp = fopen("temp.txt","w");
        fclose(fp);
        exit(0);
        case 3:secondChoice = 0;break;
        case 4:exit(0);
        default:printf("Wrong Key Pressed\n");
      }
    }
      break;
      case 3:
      exit(0);
      default:
      printf("Wrong Key Pressed\n");
    }

  }
  return 0;
}

// Function Definitions

int levelDefine(int tnum){
  if (tnum == 1) tnum = LEVEL_ONE;
  else if (tnum == 2) tnum = LEVEL_TWO;
  else if (tnum == 3) tnum = LEVEL_THREE;
  else if (tnum == 4) tnum = LEVEL_FOUR;
  else tnum = LEVEL_FIVE;
  return tnum;
}

void generateSudocu(int *a,int size){
  int specifier;FILE *ftemp = fopen("temp.txt","w");
  srand(time(0));
  for (int i=1;i<=MAX_SWAP_SIDE;i++){
    for (int j=0;j<=6;j=j+3){
      int randomNumOne = rand()%3 + j;
      int randomNumTwo = rand()%3 + j;
    if(i % 2 == 0) specifier = 2;
    else specifier = 1;
    fprintf(ftemp,"%d%d\n",randomNumOne,randomNumTwo);
    rowColExchange(a,size,randomNumOne,randomNumTwo,specifier);
  }
}
  fclose (ftemp);
}

void generateSudocuPuz(int *a,int *b,int size,int levelNum){
  int randomNumOne,randomNumTwo,i=0;
  srand(time(0));
  while (i<levelNum){
      randomNumOne = rand()%9;
      randomNumTwo = rand()%9;
      if (*((b+size*randomNumOne)+randomNumTwo) == 0) {
        *((b+size*randomNumOne)+randomNumTwo) = *((a+size*randomNumOne)+randomNumTwo);
        i++;
      }
    }
}

void printSudocuInFile(FILE *fp,int *originArray,int *sudocuPuz,int size,int tnum){
  generateSudocu(originArray,size);
  generateSudocuPuz(originArray,sudocuPuz,size,tnum);
  printSudocuPuzzle(fp,sudocuPuz,size,1);
  printSudocuPuzzle(fp,sudocuPuz,size,2);
}

void generateSudocuAgain(int *originArray,int size){
  int randomNumOne,randomNumTwo,specifier;FILE *ftemp = fopen("temp.txt","r");
  for (int i=1;i<=MAX_SWAP_SIDE*3;i++){
    if ((i%6)>0 && (i%6)<4) specifier=1;
    else specifier =2;
    char *str = readline(ftemp);
    if (strlen(str) == 0){
      printf("\nSORRY!!No Saved Game Found\n");
      exit(0);
    }
    int x = atoi(str);
    randomNumOne = x/10;
    randomNumTwo = x%10;
    rowColExchange(originArray,size,randomNumOne,randomNumTwo,specifier);
  }
  fclose (ftemp);
}
