// Only this line of comment is provided 
#include <stdio.h>
    int main()
    {
        
        double x;
        double total = 0;
        double count = 0;
        while (scanf("%lf", &x) == 1) { // pay attention to %lf
            total += x;
            count++;
            double average = (count > 0) ? total / count : 0;
            printf("Total=%f Average=%f\n", total, average); // pay attention to %f
            
        };
        
    
    }
