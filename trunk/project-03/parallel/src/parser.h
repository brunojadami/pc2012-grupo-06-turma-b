#ifndef PARSER_H
#define PARSER_H

void openFile();
void closeFile();
void readInput(int&, int&, double&, int&);
double* createM(int);
double* readM(int);
double* cloneM(double*, int);
void copyM(double*, double*, int n);

#endif
