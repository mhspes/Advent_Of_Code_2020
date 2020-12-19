#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *fp;

/*  DAY 4  */
// Validate passports
char const *fields[] = {
        "byr", "iyr", "eyr", "hgt",
        "hcl", "ecl", "pid", NULL
};
char const *fields_ecl[] = {
        "amb", "blu", "brn", "gry", "grn", "hzl", "oth", NULL
};

int is_valid_number(char * dfield, int len, int min, int max)
{
    int i, ret;
    ret = 0;
    for(i=0; i < len; i++)
    {
        if(!isdigit(dfield[i])){
            return 0;
        }
        ret = ret*10 + dfield[i]-'0';
    }
    if(!(min && max)) return ret; // no bounds set
    if(ret < min || max < ret ) return 0;

    return ret;
}
int isalphanumeric(char * dfield, int len)
{
    int i;
    for(i=0; i < len; i++)
    {
        if(isdigit(dfield[i]))
        {
            continue;
        } else if (isalpha(dfield[i]))
        {
            if(!('a' <= dfield[i] && dfield[i] <= 'f')) return 0; // not a-f
        } else {
            return 0; // Not integer nor char
        }
    }
    return 1; // return 1 on success
}

int aoc4(void) {

    char c, testv[3], dfield[15];
    char const **kp;
    int i,j, valids, linebr, n_fields;
    valids = n_fields = 0;
   if(NULL == ( fp = fopen("inputs/aoc4.txt", "r")))
   {
       printf("File not found.\n");
       exit(0);
   }

   i = linebr = 0;
   while(EOF != (c = getc(fp))){

       if(c == '\n' && ++linebr == 2)
       {
           // a single passport read, check
           if(n_fields == 7)valids++;
           n_fields = linebr = 0;
       }
       else if (isalpha(c)){
           linebr = 0;
           testv[i++] = c;
           if(i == 3)
           {
               // 3 chars read, process
               for(kp = fields, j=0; *kp != NULL; kp++, j++)
               {
                   if(strcmp(&testv[0], *kp) == 0)
                   {
                       break;
                   }
               }
               i=0;
               //Inspect the datafield
               while(EOF != (c = getc(fp)))
               {
                   if(c == ' ') break;
                   if(c == '\n')
                   {
                       linebr++;
                       break;
                   }
                   if(!(c == ':')) dfield[i++] = c; // i = length of the datafield arr
               }

               switch (j){
                   case 0:
                       if(4 == i && is_valid_number(dfield, i, 1920, 2002)) n_fields++;
                       break;
                   case 1:
                       if(4 == i && is_valid_number(dfield, i, 2010, 2020)) n_fields++;
                       break;
                   case 2:
                       if(4 == i && is_valid_number(dfield, i, 2020, 2030)) n_fields++;
                       break;
                   case 3:
                       if(i==5)
                       {
                           if(dfield[3] == 'c' && dfield[4] == 'm')
                           {
                               if(is_valid_number(dfield, 3, 150, 193)) n_fields++;
                           }
                       } else if (i==4)
                       {
                           if(dfield[2] == 'i' && dfield[3] == 'n')
                           {
                               if(is_valid_number(dfield, 2, 59, 76)) n_fields++;
                           }
                       }
                       break;
                   case 4:
                       if(i == 7 && dfield[0] == '#' && isalphanumeric(dfield+1, 6)) n_fields++;
                       break;
                   case 5:
                       if(i == 3)
                       {
                           memcpy(testv, dfield, 3);
                           for(kp = fields_ecl, j=0; *kp != NULL; kp++, j++)
                           {
                               if(strcmp(&testv[0], *kp) == 0)
                               {
                                   n_fields++;
                                   break;
                               }
                           }
                       }
                       break;
                   case 6:
                       if(i == 9){
                           if(is_valid_number(dfield, i, 0, 0)) n_fields++;
                       }
                       break;
                   default:
                       break;
               }
               i = 0;
           }
       }
   }

   fclose(fp);

   printf("Valid passports: %d\n", valids);
   return 0;
}
