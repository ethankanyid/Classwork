#include "rational.h"
#include <stdlib.h>
#include <stdio.h>

static Rational rtnl_simplify(Rational rtnl);

Rational rtnl_simplify(Rational rtnl)
{
    int a = 0;
    int b = 0;
    int tmp = 0;

    a = abs(rtnl.num);
    b = abs(rtnl.denom);

    if(b == 0)
        return rtnl;

    while (b != 0)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    if (rtnl.denom < 0)
    {
        rtnl.num = -rtnl.num;
        rtnl.denom = -rtnl.denom;
    }

    rtnl.num = rtnl.num / a;
    rtnl.denom = rtnl.denom / a;

    return rtnl;
}
Rational rtnl_add(Rational rtnl0, Rational rtnl1)
{
    Rational rtnl;
    rtnl.num = (rtnl0.num * rtnl1.denom) + (rtnl1.num * rtnl0.denom);
    rtnl.denom = rtnl0.denom * rtnl1.denom;

    return rtnl_simplify(rtnl);
}
Rational rtnl_sub(Rational rtnl0, Rational rtnl1)
{
    Rational rtnl;
    rtnl.num = (rtnl0.num * rtnl1.denom) - (rtnl1.num * rtnl0.denom);
    rtnl.denom = rtnl0.denom * rtnl1.denom;

    return rtnl_simplify(rtnl);
}
Rational rtnl_mul(Rational rtnl0, Rational rtnl1)
{
    Rational rtnl;
    rtnl.num = rtnl0.num * rtnl1.num;
    rtnl.denom = rtnl0.denom * rtnl1.denom;

    return rtnl_simplify(rtnl);
}
Rational rtnl_div(Rational rtnl0, Rational rtnl1)
{
    Rational rtnl;
    rtnl.num = rtnl0.num * rtnl1.denom;
    rtnl.denom = rtnl0.denom * rtnl1.num;

    return rtnl_simplify(rtnl);
}
Rational rtnl_init(int num, int denom)
{
    Rational rtnl;
    rtnl.num = num;
    rtnl.denom = denom;
    return rtnl_simplify(rtnl);
}
Rational rtnl_ipow(Rational rtnl, int ipow)
{
    if (ipow == 0)
    {
        rtnl.num = 1;
        rtnl.denom = 1;

        return rtnl;
    }

    int power =  abs(ipow);
    int num = rtnl.num;
    int denom = rtnl.denom;

    for (int i = 2; i <= power; i++)
    {
        rtnl.num = rtnl.num * num;
        rtnl.denom = rtnl.denom * denom;
    }

    num = rtnl.num;
    denom = rtnl.denom;

    if (ipow < 0)
    {
        rtnl.num = denom;
        rtnl.denom = num;
    }

    return rtnl;
}

char *rtnl_asStr(Rational rtnl, char buf[RTNL_BUF_SIZE])
{
    /*int character = 0;
    int num = rtnl.num;
    int denom = rtnl.denom;
    int i = 0;
    int x = 0;
    int y = 0;

    buf[i] = '(';
    printf("%d", rtnl.num);

    for (y = 0; x < rtnl.num; x = x * 10)
    {
    }
    x = x / 10;
    char bufn[y];
    int z = 0;

    while (num != 0)
    {
        character = num / x;
        num = num % (x * character);
        bufn[z] = character + '0';
        x = x / 10;
        printf("%c", bufn[z++]);
    }


    while (num != 0)
    {
        character = num / x;
        num = num % (x * character);
        buf[++i] = character + '0';
        x = x / 10;
        printf("%c", buf[i]);
    }

    buf[++i] = '/';
    printf("%c", buf[i]);
    for (x = 10; x < rtnl.denom; x *= 10)
    {}
    x = x / 10;

    while (denom != 0)
    {
        character = denom / x;
        denom = denom % (character * denom);
        buf[++i] = character + '0';
        x = x / 10;
        printf("%c", buf[i]);
    }

    buf[++i] = ')';
    buf[++i] = 0;
    printf("%c", buf[i]);*/

    snprintf(buf, RTNL_BUF_SIZE, "(%d/%d)", rtnl.num, rtnl.denom);
    return buf;
}
