
/*This above program generates random numbers between 0-10
but the problem is every time we run the program the output
will be same.because the seed is set to 1.
'''
so if we modify the seed every time the problem seems to be solved*/

int randomNum(int bound){
return (rand()%bound);
}

