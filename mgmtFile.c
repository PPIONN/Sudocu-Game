

char *readline(FILE *fp){
	char c;int i=0;
	char *str = (char *)malloc(20*sizeof(char));
	while ((c=getc(fp)) != '\n' && c != EOF){
		str[i] = c;i++;
	}
	return str;
}
/*Specifier = 1 ; for print the original sudocu puzzle;
specifier = 2 ; for print the original puzzle for the second time to solve ;
specifier = 3 ; for print the solved puzzle;
*/
void printSudocuPuzzle(FILE *fp,int *a,int size,int specifier){
	if (specifier == 1) fprintf(fp, "\nOriginal Sudocu Puzzle\n*****Do not change this******\n\n");
	else if (specifier == 2)fprintf(fp, "\nSolve this Puzzle and save it to the file\n\n");
	else if (specifier == 3) fprintf(fp, "\nSolution for the above puzzle is this\n\n");
	for (int i=0;i<=size*(size-1);i=i+size){
		fprintf(fp,"\t");
		if (i == 27 || i == 54) fprintf(fp, "----------------------\n\t");
		for (int j=0;j<size;j++){
			if (j % 3 == 0 && j != 0) fprintf(fp," | ");
			else fprintf(fp, " ");
			if (*((a+i)+j) == 0) fprintf(fp,"_");
			else fprintf(fp,"%d",*((a+i)+j));

		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}
int dtoi(char a){
	if (a == '0') return 0;
	if (a == '1') return 1;
	if (a == '2') return 2;
	if (a == '3') return 3;
	if (a == '4') return 4;
	if (a == '5') return 5;
	if (a == '6') return 6;
	if (a == '7') return 7;
	if (a == '8') return 8;
	if (a == '9') return 9;
}
//This function returns zero if this array does not get full.else return 1;
int getArrayFromFile(char *fileName,int *getArray,int size){
	int row=0,col=0;
	FILE *fp = fopen(fileName,"r");
	fseek(fp,0,2);
	double endPosition = ftell(fp);
	fseek(fp,363,0);
	do{
		char *str = readline(fp);
		for (int i = 0;i<strlen(str);i++){
			if (str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9'){
				int val = dtoi(str[i]);
				*((getArray+size*row)+col) = val;
				col++;
				if (col>size-1){col = 0;row ++;}
			}
		}
	}while(ftell(fp) != endPosition);
	fclose(fp);
	printArray(getArray,9);
	if (row == size && col == 0) return 1;
	else return 0;
}
