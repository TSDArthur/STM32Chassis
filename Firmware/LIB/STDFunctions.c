#include <sys.h>
#include <STDFunctions.h>

int Str2Int(const char *str, int st, int ed)
{
    int num = 0;
    u8 negative = 0;
    for (int i = st; i <= ed; i++)
    {
        if (str[i] == '-')
        {
            negative = 1;
            continue;
        }
        num += str[i] - '0';
        num *= 10;
    }
    num /= 10;
    if (negative)
    {
        num *= -1;
    }
    return num;
}

float Str2Float(const char *str, int st, int ed)
{
    float num = 0;
    int pointPos = 0;
    for (int i = st; i <= ed; i++)
    {
        if (str[i] == '.')
        {
            pointPos = i;
            break;
        }
    }
    if (pointPos == 0)
    {
        return (float)Str2Int(str, st, ed);
    }
    for (int i = ed; i > pointPos; i--)
    {
        num += str[i] - '0';
        num /= 10;
    }
    num += (float)Str2Int(str, st, pointPos - 1);
    return num;
}
