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
		x[i]=cur_lib[i*2+2];
		y[i]=cur_lib[i*2+3];
	}

	//拟合
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

    return 0;
}