#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unicode/uchar.h"
#include "unicode/ustring.h"
#include "unicode/utypes.h"
#include "unicode/ustdio.h"

/*
--------------------
 printU();
--------------------
*/

bool printU(UChar *str)
{

    int32_t len;
    UErrorCode errorCode = U_ZERO_ERROR;
    char *s;

    u_strToUTF8(NULL, 0, &len, str, -1, &errorCode);

    if(len < 1)
    {
        printf("Error: the length less than 1.\n");
        return false;
    }

    if(errorCode != U_ZERO_ERROR && errorCode != U_BUFFER_OVERFLOW_ERROR)
    {
        printf("Error: (ICU) %s\n", u_errorName(errorCode) );
        return false;
    }

    errorCode = U_ZERO_ERROR;

    s = malloc(len+1);

    if(!s)
    {
        printf("Error: unable to allocate memory (4)\n");
        return false;
    }

    u_strToUTF8(s, len+1, &len, str, -1, &errorCode);

    if(errorCode != U_ZERO_ERROR)
    {
        printf("Error: u_strToUTF8(): %s\n", u_errorName(errorCode) );
        free(s);
        return false;
    }

    printf("UTF8 string: %s\n", s);

    free(s);

    return true;
}

/*
--------------------
 main();
--------------------
*/

int main()
{

    char testStr[]="Šešios žąsys su šešiais žąsyčiais.";
    const char locale[] = "lt_LT";

    UChar *uStr;
    UChar *lowerStr;
    UChar *upperStr;

    int32_t length;
    int32_t retLength;
    UErrorCode errorCode = U_ZERO_ERROR;

    printf("%s\n", testStr);
    printf("strlen: %ld\n", strlen(testStr));

    u_strFromUTF8(NULL, 0, &length, testStr, -1, &errorCode);

    if(errorCode!=U_ZERO_ERROR && errorCode != U_BUFFER_OVERFLOW_ERROR)
    {
        printf("Error: (ICU) %s\n", u_errorName(errorCode));
        return 1;
    }

    errorCode = U_ZERO_ERROR;

    printf("length: %d\n", length);

    if(length < 1)
    {
        printf("Error: the length less than 1.\n");
        return 1;
    }

    uStr = malloc((length + 1) * sizeof *uStr);

    if(!uStr)
    {
        printf("Error: unable to allocate memory (1).\n");
        return 1;
    }

    u_strFromUTF8(uStr, (length + 1) * sizeof *uStr, &retLength, testStr, strlen(testStr), &errorCode);

    if(errorCode != U_ZERO_ERROR)
    {
        printf("Error: (ICU) %s\n", u_errorName(errorCode) );
        free(uStr);
        return 1;
    }

    printf("retLength: %d\n", retLength);

    if(!printU(uStr))
    {
        printf("Error: printU.\n");
        free(uStr);
        return 1;
    }



    // to lower

    length = u_strToLower(NULL, 0, uStr, -1, locale, &errorCode);

    if(errorCode != U_ZERO_ERROR && errorCode != U_BUFFER_OVERFLOW_ERROR)
    {
        printf("Error: (ICU) %s\n", u_errorName(errorCode) );
        free(uStr);
        return 1;
    }

    errorCode = U_ZERO_ERROR;

    printf("length: %d\n", length);

    if(length<1)
    {
        printf("Error: length less than 1.\n");
        free(uStr);
        return 1;
    }

    lowerStr = malloc((length + 1) * sizeof *lowerStr);

    if(!lowerStr)
    {
        printf("Error: unable to allocate memory (2).\n");
        free(uStr);
        return 1;
    }

    length = u_strToLower(lowerStr, (length + 1) * sizeof *lowerStr, uStr, -1, locale, &errorCode);

    if(errorCode != U_ZERO_ERROR)
    {
        printf("Error: (ICU) %s\n", u_errorName(errorCode) );
        free(lowerStr);
        free(uStr);
        return 1;
    }

    if(!printU(lowerStr))
    {
        printf("Error: printU.\n");
        free(lowerStr);
        free(uStr);
        return 1;
    }

    free(lowerStr);



    // to upper

    length = u_strToUpper(NULL, 0, uStr, -1, locale, &errorCode);

    if(errorCode != U_ZERO_ERROR && errorCode != U_BUFFER_OVERFLOW_ERROR)
    {
        printf("ICU error: %s\n", u_errorName(errorCode) );
        free(uStr);
        return 1;
    }

    errorCode = U_ZERO_ERROR;

    printf("length: %d\n", length);

    if(length<1)
    {
        printf("Error: length less than 1.\n");
        free(uStr);
        return 1;
    }

    upperStr = malloc((length + 1) * sizeof *upperStr);

    if(!upperStr)
    {
        printf("Error: unable to allocate memory (3).\n");
        free(uStr);
        return 1;
    }

    length = u_strToUpper(upperStr, (length + 1) * sizeof *upperStr, uStr, -1, locale, &errorCode);

    if(errorCode != U_ZERO_ERROR)
    {
        printf("ICU error: %s\n", u_errorName(errorCode) );
        free(upperStr);
        free(uStr);
        return 1;
    }

    if(!printU(upperStr))
    {
        printf("Error: printU.\n");
        free(upperStr);
        free(uStr);
        return 1;
    }

    free(upperStr);



    free(uStr);

    return 0;
}
