#include<stdio.h>
#include<math.h>

float f(float x){
    return(x*x*x+x*x-3*x-3);
}

int main(){
    float x1, x2, xm=0, acc=0.001, temp;
    int i=1;
    do{
        printf("Enter x1 & x2:");
        scanf("%f %f",&x1, &x2);
    }while (f(x1)*f(x2)>=0);
    printf("Iteration\tx1\tx2\txm\tf(x1)\t\tf(x2)\tf(xm)\n");
    do{
        temp=xm;
        printf("%d\t\t",i);
        printf("%.4f\t %.4f\t", x1, x2);
        xm=(x1+x2)/2.0;
        printf("%.4f\t %.4f\t %.4f\t %.4f\t\n",xm, f(x1), f(x2),f(xm));
        if(f(x1)*f(xm)<0){
            x2=xm;
        }
        else{
            x1=xm;
        }
        i++;
    }while(fabs(temp-xm)>=acc);

printf("The root is %.4f",xm);
return 0;
}
