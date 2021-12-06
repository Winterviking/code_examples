// защиты нет, потому что файл используется в "метапрограммировании"
//#ifndef __ATOI_CORE_H_INCLUDED__
//#define __ATOI_CORE_H_INCLUDED__

_itoa2__
{
    BYTE i = 0;
    //BYTE i = base;
    //BYTE shift = 0;

    //do {
    //    shift++;
    //} while ((i >>= 1) > 1);
    //i = 0;

    bool negative = false;

    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    //if (num < 0 && base == 10)
    //{
    //    negative = true;
    //    num = -num;
    //}
    if (num < 0) {
        negative = true;
        num = -num;
    }


    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num = num >> shift;
    }

    switch (base)
    {
    case 8:
        str[i++] = '0';
        break;
    case 16:
        str[i++] = 'x';
        str[i++] = '0';
        break;
    };

    // If number is negative, append '-'
    if (negative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);
    convert_strlen = i;

    return str;
}

//#endif /* __ATOI_CORE_H_INCLUDED__ */
