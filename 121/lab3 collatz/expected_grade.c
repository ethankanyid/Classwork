/** Programmer: Ethan Kanyid
  * Class: CptS 121, Fall 2019
  * Programming lab: Lab_03
  * Date: (9/8/2023)
  * Description: expected_grade
  */

#include <stdio.h>
#include <math.h>

int main(void)
{

    double score1, score2, score3,score4;
    char expected_letter_grade;

    printf("Please enter 3 scores (#,#,#):");
      scanf("%lf,%lf,%lf",&score1,&score2,&score3);
    printf("Please enter expected letter grade:");
      scanf(" %c",&expected_letter_grade);

      if (expected_letter_grade == 'A') {
        score4 = 90*4 - score1 - score2 - score3;
        printf("%.2lf\n",score4);
      }
      else if (expected_letter_grade == 'B')
      {
        score4 = 80*4 - score1 - score2 - score3;
        printf("%.2lf\n",score4);
      }
      else if (expected_letter_grade == 'C')
      {
        score4 = 70*4 - score1 - score2 - score3;
        printf("%.2lf\n",score4);
      }
      else if (expected_letter_grade == 'D')
      {
      score4 = 60*4 - score1 - score2 - score3;
        printf("%.2lf\n",score4);
      }
      else
      {
        printf("You will fail this class\n");
      }




return 0;
}