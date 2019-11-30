#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct dataPoint
{
    double time;
    double x;
};

int meanCalculated = 0;
int medianCalculated = 0;
int rangeCalculated = 0;
int stdvCalculated = 0;
int bestFitCalculated = 0;

double Mean;
double Median;
double Range;
double StandardDeviation;
double tangent;
double cutoff;

typedef struct dataPoint coord;

double calculateMean(coord arr[], int length)
{
    double mean = 0;
    int i = 0;
    for (; i < length; i++)
    {
        mean += arr[i].x;
    }

    mean /= length;

    return mean;
}

double calculateMedian(coord arr[], int length)
{
    coord tem;

    int i = 0;
    int j = i + 1;
    //sorting the dataset O(n2) algorithm
    for (; i < length - 1; i++)
    {
        for (; j < length; j++)
        {
            if (arr[i].x > arr[j].x)
            {
                tem = arr[i];
                arr[i] = arr[j];
                arr[j] = tem;
            }
        }
    }

    //calculating median
    if (length % 2 == 1)
    {
        return arr[length / 2].x;
    }
    else
    {
        return 0.5 * (arr[(length / 2) - 1].x + arr[length / 2].x);
    }
}

double calculateRange(coord arr[], int length)
{
    coord tem;
    int i = 0;
    int j = i + 1;
    //sorting the dataset O(n2) algorithm
    for (; i < length - 1; i++)
    {
        for (; j < length; j++)
        {
            if (arr[i].x > arr[j].x)
            {
                tem = arr[i];
                arr[i] = arr[j];
                arr[j] = tem;
            }
        }
    }

    return arr[length - 1].x - arr[0].x;
}

double calculateStandardDeviation(coord arr[], int length)
{
    if (meanCalculated == 1)
    {
        //do nothing as it is already calculated
    }
    else
    {
        Mean = calculateMean(arr, length);
        meanCalculated = 1;
    }

    double variance = 0;

    int i = 0;

    for (; i < length; i++)
    {
        variance += pow((arr[i].x - Mean), 2);
    }

    variance = variance / length;

    return sqrt(variance);
}

void calculateBestFit(coord arr[], int len)
{
    double x_average = 0;
    double y_average = 0;
    double xy_average = 0;
    double x_squared_average = 0;
    int i = 0;
    for (; i < len; i++)
    {
        x_average += arr[i].time;
        y_average += arr[i].x;
        xy_average += arr[i].time * arr[i].x;
        x_squared_average += arr[i].time * arr[i].time;
    }

    x_average /= len;
    y_average /= len;
    xy_average /= len;
    x_squared_average /= len;

    double m = ((x_average * y_average) - xy_average) / ((x_average * x_average) - x_squared_average);
    double c = y_average - m * x_average;
    tangent = m;
    cutoff = c;
}

double getPredictedValue(double x)
{
    return tangent * x + cutoff;
}

int main(int argc, char *argv[])
{
    coord arr[1000]; //here 1000 is maximum number of data point that we can work with
    char filename[40];
    if (argc < 2)
    {
        printf("Provide Input Filename: ");
        scanf("%s", filename);
    }
    else
    {
        strcpy(filename, argv[1]);
    }

    FILE *fptr, *fout;
    fptr = fopen(filename, "r");
    char line[256];
    double time, x;
    fgets(line, sizeof(line), fptr);

    int index = 0;
    while (fscanf(fptr, "%lf %lf", &time, &x) != EOF)
    {
        arr[index].time = time;
        arr[index].x = x;
        index++;
    }

    int len = index;

    /*int i = 0 ;
    for(;i<len;i++){
        printf("%lf %lf\n",arr[i].time,arr[i].x);
    }*/
    int option;
    int menuOption;

    while (1)
    {
        printf("Perform Operation\n1. Perform Analysis\n2. Print Analysis to File\n3. Display Graph of Input Data\n4. Exit\nChoose your Option: ");
        scanf("%d", &option);

        if (option == 1)
        {
            while (1)
            {
                printf("\nPerform Analysis:\n");
                printf("1. Mean\n");
                printf("2. Median\n");
                printf("3. Range\n");
                printf("4. Standard Deviation\n");
                printf("5. Best Fit Line\n");
                printf("6. Differenciation of Best Fit Line\n");
                printf("7. Integration of Best Fit Line\n");
                printf("8. All\n");
                printf("9. Go to Main Menu\nSelect Operation: ");

                scanf("%d", &menuOption);

                if (menuOption == 1)
                {
                    if (meanCalculated == 0)
                    {
                        Mean = calculateMean(arr, len);
                        meanCalculated = 1;
                    }

                    printf("\nMean: %lf\n", Mean);
                    fout = fopen("output.txt", "a");
                    fprintf(fout, "Mean: %lf\n", Mean);
                    fclose(fout);
                }

                else if (menuOption == 2)
                {
                    if (medianCalculated == 0)
                    {
                        Median = calculateMedian(arr, len);
                        medianCalculated = 1;
                    }

                    printf("\nMedian: %lf\n", Median);
                    fout = fopen("output.txt", "a");
                    fprintf(fout, "Median: %lf\n", Median);
                    fclose(fout);
                }

                else if (menuOption == 3)
                {
                    if (rangeCalculated == 0)
                    {
                        Range = calculateRange(arr, len);
                        rangeCalculated = 1;
                    }

                    printf("\nRange: %lf\n", Range);

                    fout = fopen("output.txt", "a");
                    fprintf(fout, "Range: %lf\n", Range);
                    fclose(fout);
                }

                else if (menuOption == 4)
                {
                    if (stdvCalculated == 0)
                    {
                        StandardDeviation = calculateStandardDeviation(arr, len);
                        stdvCalculated = 1;
                    }

                    printf("\nStandardDeviation: %lf\n", StandardDeviation);
                    fout = fopen("output.txt", "a");
                    fprintf(fout, "Standard Deviation: %lf\n", StandardDeviation);
                    fclose(fout);
                }

                else if (menuOption == 5)
                {
                    //best fit linear regression using numerical method
                    if (bestFitCalculated == 0)
                    {
                        calculateBestFit(arr, len);
                        bestFitCalculated = 1;
                    }
                    printf("\nBest fit line : y = %lf x + %lf\n", tangent, cutoff);
                    fout = fopen("output.txt", "a");
                    fprintf(fout, "\nBest fit line : y = %lf x + %lf\n", tangent, cutoff);
                    fclose(fout);
                }

                else if (menuOption == 6)
                {
                    if (bestFitCalculated)
                    {
                        //do nothing
                    }
                    else
                    {
                        calculateBestFit(arr, len);
                    }

                    printf("\nDifferenciation of fit line : %lf \n", tangent);
                    fout = fopen("output.txt", "a");
                    fprintf(fout, "\nDifferenciation of fit line : %lf \n", tangent);
                    fclose(fout);
                }

                if (menuOption == 7)
                {
                    if (bestFitCalculated)
                    {
                        //do nothing
                    }
                    else
                    {
                        calculateBestFit(arr, len);
                    }

                    printf("\nIntegration of best fit line : y = %lf x2 + x*%lf\n", tangent * 0.5, cutoff);
                    fout = fopen("output.txt", "a");
                    fprintf(fout, "Integration of best fit line : y = %lf x2 + x*%lf \n", tangent * 0.5, cutoff);
                    fclose(fout);
                }

                else if (menuOption == 8)
                {
                    if (meanCalculated == 0)
                    {
                        Mean = calculateMean(arr, len);
                        meanCalculated = 1;
                    }

                    printf("--------------------------------------\n");
                    printf("Mean: %lf\n", Mean);
                    if (medianCalculated == 0)
                    {
                        Median = calculateMedian(arr, len);
                        medianCalculated = 1;
                    }
                    printf("Median: %lf\n", Median);
                    if (rangeCalculated == 0)
                    {
                        Range = calculateRange(arr, len);
                        rangeCalculated = 1;
                    }
                    printf("Range: %lf\n", Range);
                    if (stdvCalculated == 0)
                    {
                        StandardDeviation = calculateStandardDeviation(arr, len);
                        stdvCalculated = 1;
                    }
                    printf("StandardDeviation: %lf\n", StandardDeviation);
                    if (bestFitCalculated == 0)
                    {
                        calculateBestFit(arr, len);
                        bestFitCalculated = 1;
                    }
                    printf("Best fit line : y = %lf x + %lf\n", tangent, cutoff);
                    printf("Differenciation of fit line : %lf \n", tangent);
                    printf("Integration of best fit line : y = %lf x2 + x*%lf \n", tangent * 0.5, cutoff);
                    printf("\n--------------------------------------\n");
                    fout = fopen("output.txt", "w");
                    fprintf(fout, "Mean: %lf\n", Mean);
                    fprintf(fout, "Median: %lf\n", Median);
                    fprintf(fout, "Range: %lf\n", Range);
                    fprintf(fout, "Standard Deviation: %lf\n", StandardDeviation);
                    fprintf(fout, "Best fit line : y = %lf x + %lf\n", tangent, cutoff);
                    fprintf(fout, "Differenciation of fit line : %lf\n", tangent);
                    fprintf(fout, "Integration of best fit line : y = %lf x2 + x*%lf\n", tangent * 0.5, cutoff);
                    fclose(fout);
                }

                else if (menuOption == 9)
                {
                    printf("\n");
                    break;
                }
            }
        }

        else if (option == 2)
        {
            if (meanCalculated == 0)
            {
                Mean = calculateMean(arr, len);
                meanCalculated = 1;
            }

            printf("\n--------------------------------------\n\n");

            if (medianCalculated == 0)
            {
                Median = calculateMedian(arr, len);
                medianCalculated = 1;
            }
            if (rangeCalculated == 0)
            {
                Range = calculateRange(arr, len);
                rangeCalculated = 1;
            }
            if (stdvCalculated == 0)
            {
                StandardDeviation = calculateStandardDeviation(arr, len);
                stdvCalculated = 1;
            }
            if (bestFitCalculated == 0)
            {
                calculateBestFit(arr, len);
                bestFitCalculated = 1;
            }

            fout = fopen("output.txt", "w");
            fprintf(fout, "Mean: %lf\n", Mean);
            fprintf(fout, "Median: %lf\n", Median);
            fprintf(fout, "Range: %lf\n", Range);
            fprintf(fout, "Standard Deviation: %lf\n", StandardDeviation);
            fprintf(fout, "Best fit line : y = %lf x + %lf\n", tangent, cutoff);
            fprintf(fout, "Differenciation of fit line : %lf\n", tangent);
            fprintf(fout, "Integration of best fit line : y = %lf x2 + x*%lf\n", tangent * 0.5, cutoff);
            fclose(fout);

            printf("All analysis has been printed to output.txt \n\n--------------------------------------\n");
        }

        else if (option == 3)
        {
            calculateBestFit(arr, len);
            FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
            FILE *dataset = fopen("dataset.dat", "w");
            FILE *bestfit = fopen("bestfit.dat", "w");

            for (int i = 0; i < len; i++)
            {
                fprintf(dataset, "%lf %lf \n", arr[i].time, arr[i].x);
                fprintf(bestfit, "%lf %lf \n", arr[i].time, getPredictedValue(arr[i].time));
            }

            fclose(dataset);
            fclose(bestfit);

            fprintf(gnuplotPipe, "set terminal jpeg\n");
            fprintf(gnuplotPipe, "set output 'output.jpeg'\n");
            fprintf(gnuplotPipe, "plot 'bestfit.dat' pointsize 1.3 linecolor 4 with linespoint,'dataset.dat' pointsize 1.5 linecolor 1 with linespoint\n");

            fclose(gnuplotPipe);
        }

        else if (option == 4)
        {
            break;
        }
        else
        {
            break;
        }
    }
    fclose(fout);
    fclose(fptr);

    return 0;
}
