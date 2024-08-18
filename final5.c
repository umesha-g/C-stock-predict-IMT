#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "pbPlots.h"
#include "supportLib.h"
#include <unistd.h>

//Function declaration
void drift_calculation (double a_1[], int n, double* Dr, double* Vr);
double random_calculation (double var);
double Final_formula (double drift, double random_change);
void Graph_creation (double a_1[], int n_2 , double tsp);

//main Function
int main()
{

    int i,n_1;
    double a[1000], temp, drift_1, rand_1, var_1;
    char verif, verify, run_1 ,run_2;

start_1:
        //obtaining number of days
            printf("Please Enter number of days - ");
            scanf("%d",&n_1);

        //loop for scanning daily stock price values
            printf("\n\n            ---Please Enter Stock Value For Each Previous Day---\n\n");
            for(i=n_1; i>0;)
            {
                printf("Enter stock value for %d day(s) before today - Rs.  ",n_1-i+1);
                scanf("%lf",&temp);
                

            //Chacking for minus numbers
                if(temp > 0.00)
                {
                    a[i-1] = temp;
                    temp=0;
                    i--;
                }
                else
                {
                    printf("\n !!!!!! Please enter a valid value !!!!!!\n");
                    temp=0;
                }

            }
        //loop for printing the daily stock price values
            printf("\n\n            --- Please check Your values---\n\n");
            for(i=n_1; i>0; i--)
            {
                printf("Stock Price Value %d Day(s) Before Today - Rs. %.2f\n",n_1-i+1,a[i-1]);
            }


start_2:

        //Verification
            printf("\n\nAre your values correct ? (Y for continue and N for restart program) --> ");
            scanf(" %c",&verify);

            if(verify=='Y')
            {
                goto verified;
            }
            else
            {
                if(verify=='N')
                {
                    printf("\n\n            --- Programme Restarted---\n\n");
                    goto start_1;
                }
                else
                {
                    goto start_2;
                    
                }

            }

verified:

            printf("\n\n                                                        ----- Values Verified -----\n\n");
           
        //Calling Function for calculate drift part
            drift_calculation (a,n_1, &drift_1, &var_1);

            printf("--> drift value=%.4lf\n\n",drift_1);

        //Calling Function for calculate Random part
            rand_1 = random_calculation (var_1);

            printf("\n\n-->Random change of Stock price = %.4lf\n\n",rand_1);

        // Calling function to final part
            double today_stock_price = Final_formula(drift_1,rand_1);

        // Printing Final result
            printf(" \n\n\n\n                               ----- ||||  Today's Stock Price is %.2lf  |||| -----\n\n\n\n",today_stock_price);
            
        // Calling function to create Graph
            Graph_creation (a,n_1,today_stock_price);

start_3:

        // ASk to run again
            printf("\n\n Do you want to Run Programme again? ( Y or N )");

            scanf(" %c",&run_1);

        // check for answer
            if(run_1=='Y')
            {
                printf("\n\n                                                 --- Program Restarted---\n\n");
                goto start_1;
                
            }
            else
            {
                if(run_1=='N')
                {
                    printf("\n\n                                               --- Thank You ---\n\n");
                    goto end;
                }
                else
                {
                    goto start_3;
                        
                }

            }

            
end:

return 0;

}


// Defining function for drift part calculation
void drift_calculation (double a_1[],int n,double* Dr,double* Vr)
{
            int i;
            double b[1000],c[1000],k[1000],m[1000],sum,ave,vars,temp;
            double drift,var;

            printf("\n                                    ====       Calculations For Drift Part Of Formula       ====\n\n\n");

        //loop for calculating periodic daily return
            for(i=0; i<n; )
            {
	      b[i]=a_1[i]/a_1[i-1];
	      c[i]=logf(b[i]);
               ++i;
                
            }

        //loop for printing average daily return values
            printf("\n\n            ---periodic daily return---\n\n");
            for(i=1; i<n; i++) 
            {
                printf("periodic daily return %d =%f\n",i,c[i]);
            }
            printf("\n\n");

        //summation of periodic daily return values
            for(i=1; i<n; i++)
            {
                sum=sum+c[i];
            }
            printf("--> Sum of periodic daily return values= %f\n",sum);
            printf("\n\n");

        //average daily return
            ave=sum/(n-1);
            printf("--> Average daily return value=%f\n",ave);
            printf("\n\n");

        //calculating variance
            for(i=1; i<n; i++)
            {
                k[i]=c[i]-ave;
            }

        //square of elements
            for(i=1; i<n; i++)
            {
                m[i]=pow(k[i],2);
            }

        //printing square of variance elements
            printf("\n\n            ---square values of variance elements---\n\n");
            for(i=1; i<n; i++)
            {
                printf("square values of variance elements %d is=%f\n",i,m[i]);
            }

        //summation of matrix elements
            for(i=1; i<n; i++)
            {
                vars=vars+m[i];
            }

        //sum of square elements
            printf("\n\n--> variance sum=%f\n\n",vars);

        //variance
            var=vars/(n-1);
            printf("--> variance=%.4lf\n\n",var);

        //calculating drift
            drift=ave-(var/2);
            *Dr= drift;
            *Vr = var;

        return;    
}

// Defining function for random part calculation
double random_calculation (double var)
{

            printf("\n\n\n                                   ====       Calculations For Random Part Of Formula       ====\n\n\n");

            double x,j,o,l,t;                                      // x - x for random probability | j - c part of formula | o - b part of formula | l - square root of log natural | t - time
            double ran,sqr,nat_log,inv_sqr,stnd_dev,random_change; // ran - random number | sqr - Square of random number | natlog - Natural log | stnd_dev - Standard deviation | random_change - final random change

        // generating random number
            srand(time(0));
            t = rand() % 100;
            ran = t/100;
        // print random number
            printf("\n\n-->Computer generated random Number = %.4lf",ran);

        // Square of random number
            sqr = ran*ran;
            //printf("\n y is %.4lf",sqr );

        // reciprocal of square of random number
            inv_sqr = 1/sqr;
            //printf("\n g is %.4lf",invsqr );

        // log natural of reciprocal of square of random number
            nat_log = log(inv_sqr);
            //printf("\n l is %.4lf",natlog );

        // square root of log natural of reciprocal of square of random number
            l = sqrt(nat_log);
            //printf("\n p is %.4lf",a );

        // c part of formula
            j = 2.515517 + (0.802853*l) + (0.010328*(l*l));
            //printf("\n c is %.4lf",c );

        // b part of formula
            o = 1 + (1.432788*l) + (0.189269*(l*l)) + (0.001308*(l*l*l));
            //printf("\n b is %.4lf",b );

        // calculate x
            x = (j/o)-l;

        // print x
            printf("\n\n--> x = %.4lf",x );

        // calculating standard deviation
            stnd_dev = sqrt(var);

        // calculating random change
            random_change = stnd_dev * x;

        // return random change
        
            return random_change ;
}

// Defining fuction for Final Formula
double Final_formula (double drift,double random_change)
{
     double yest_stock_price,p,q,tsp;

        // addition
            p = drift + random_change;
        // printf("\n p is %.4lf",p );

        // calculating exponential
            q = exp(p);
        // printf("\n q is %.4lf",q );

        // obtaining yesterday stock price
            printf("\n\n\nPlease enter yesterday Stock price - Rs. " );
            scanf("%lf",&yest_stock_price);
            //printf("\n yest is %.4lf",yest_stock_price );

        // calculating today stock price
            tsp= yest_stock_price * q;

            return tsp;
}
       
// Defining function for Create Graph
void Graph_creation (double a_1[],int n_2 ,double tsp)
{
            int  x_range, y_range,i ;
            double x_r[1000];
            
        // Loop for elements of x-axis  
            for (i=0; i<=n_2; i++)
            {
                
                x_r[i]=i+1;
            }

        // Adding calculated stockprice as last element of the array    
            a_1[n_2] = tsp;

        // assigning element number in arrays
            x_range = n_2+1;

            y_range = n_2+1;
        
        // Image creating function
            RGBABitmapImageReference *imageref = CreateRGBABitmapImageReference();

        // Plot (function, image width , image height , x array , number of elements in x array , y array , number of elements in y array)
            DrawScatterPlot(imageref, 2400, 1400, x_r, x_range, a_1, y_range);
            
        //
            size_t length;
            double *pngData = ConvertToPNG(&length, imageref->image);

        // Create Graph .png File
            WriteToFile(pngData, length, "plot.png");

            printf("\n The Graph is Created in Your Programme Folder as a Image file ");

            return ;

}
