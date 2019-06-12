#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gsl/gsl_fit.h>

int main()
{
	//读取csv文件中的数据
    char tar[10000];
    double cur_lib[1000];
    char *ch;
	int cur_count = 0;
    FILE * fp = fopen("./data/spring_data.csv", "r");
    while(fgets(tar, 10000, fp)!=NULL)
	{
        ch = strtok(tar, ",");  
        while(ch!=NULL)
		{
            cur_lib[cur_count] = atof(ch);
            ch = strtok(NULL, ",");
            cur_count++;
        }
    }
    fclose(fp);

	//将数据放到x[],y[]数组中
	int n=cur_count/2-1;
	double x[n];
	double y[n];
	for (int i=0;i<n;i++)
	{
		y[i]=cur_lib[i*2+2];
		x[i]=cur_lib[i*2+3]*9.81;
	}

	//gsl拟合
	double c0, c1, cov00, cov01, cov11, sumsq;

  	gsl_fit_linear (x, 1, y, 1, n,
                   &c0, &c1, &cov00, &cov01, &cov11,
                   &sumsq);

  	printf ("best fit: Y = %g + %g X\n", c0, c1);
  	printf ("covariance matrix:\n");
  	printf ("[ %g, %g\n  %g, %g]\n",
          	cov00, cov01, cov01, cov11);
  	printf ("sumsq = %g\n", sumsq);

  	printf ("\n");

	// plot
    FILE *pipe = popen("gnuplot -persist", "w"); // Open a pipe to gnuplot
    if (pipe) // If gnuplot is found
    { 
        fprintf(pipe, "set term wx\n");         // set the terminal
        fprintf(pipe, "set xlabel '|Force| (Newtons)'\n");
        fprintf(pipe, "set ylabel 'Distance (meters)'\n");
        fprintf(pipe, "set xrange [0:10]\n");
        fprintf(pipe, "set yrange [0.05:0.6]\n");
        fprintf(pipe, "set title 'Measured Displacement of Spring'\n");
        fprintf(pipe, "linear fit:y=%.4f*x+%.4f\n",c1,c0);

        // 1 sending gnuplot the plot '-' command
        fprintf(pipe, "plot '-' title '(Force,Distance)' with points  pt 7 lc rgb 'blue',\
                            '-' title 'Distance=f(Force)' with  linespoints  pt  6 lc rgb 'red'\n");
        
        // 2 followed by data points: <x,y>
        for (int i = 0; i < n; i++)
        {
            fprintf(pipe, "%lf %lf\n", x[i], y[i]);
        }
        // 3 followed by the letter "e" 
        fprintf(pipe, "e");
        
        // linear fit
        fprintf(pipe,"\n"); // start a new draw item
        fprintf(pipe, "%lf %lf\n", 0.0, c0+c1*0.0);
        for (int i = 0; i < n; i++)
        {
            fprintf(pipe, "%lf %lf\n", x[i], c0+c1*x[i]);
        }
        fprintf(pipe, "%lf %lf\n", 20.0,c0+c1*20.0);
        fprintf(pipe, "e");
        
        fflush(pipe);
        fprintf(pipe, "exit \n"); // exit gnuplot
        pclose(pipe);             //close pipe
    }

    return 0;
}