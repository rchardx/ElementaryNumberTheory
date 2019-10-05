#include <stdio.h>
#include <math.h>

const __int64 MAX = 47000;

__int64 prime[MAX];

__int64 number[MAX];

__int64 find ( __int64 n )
{
    
    
    number[0] = number[1] = 1;
    for ( __int64 i=2; i<=n; i++ )
    {
        number[i] = 0;
    }
    
    for ( __int64 j=2; j<=n; j++ )
    {
        for ( __int64 z=j+j; z<=n; z+=j )
        {
            if ( ! number[z] )
            {
                number[z] = 1;
            }
        }
    }
    
    __int64 p = 0;
    for ( i=0; i<=n; i++ )
    {
        if ( !number[i] )
        {
            prime[p++] = i;
        }
    }
    
    return p;
}

__int64 num[MAX];
__int64 pre;

__int64 f ( __int64 n, __int64 len )
{
    
    __int64 l, r, mid;
    __int64 flag = 1;
    
    __int64 n2 = ( __int64 )( sqrt ( (double)n ) ) + 1;
    
    l = 0;
    r = len - 1;
    while ( l<=r )
    {
        mid = ( l + r ) / 2;
        if ( prime[mid] > n2 )
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    
    for ( __int64 i=r; i>=0; i-- )
    {
        if ( ! ( n % prime[i] ) )
        {
            flag = 0;
            while ( ! ( n % prime[i] ) )
            {
                num[pre++] = prime[i];
                n /= prime[i];
            }
            break;
        }
    }
    if ( flag )
    {
        num[pre++] = n;
        n = 1;
    }
    
    return n;
}

__int64 power ( __int64 a, __int64 n )/*计算幂的函数*/
{
    
    __int64 sum = 1;
    __int64 count = a;
    
    while ( n )
    {
        if ( n & 1 )
        {
            sum *= count;
        }
        n >>= 1;
        count *= count;
    }
    return sum;
}


struct
{
    __int64 num;
    __int64 count;
}p[MAX];
__int64 next;

__int64 stack[MAX];

__int64 total_sum;

void find ( __int64 no, __int64 val, __int64 n )//传递进去的是第几个因数，这个因数的大小，和原来的数的大小
{
    if ( no == next )
    {
        __int64 sum = 1;
        for ( __int64 i=0; i<no; i++ )
        {
            if ( stack[i] )
            {
                sum *= ( p[i].num - 1 ) * power ( p[i].num, stack[i]-1 );
            }
        }
        total_sum += sum*(n/val);
        return;
    }
    for ( __int64 i=p[no].count; i>=0; i-- )
    {
        stack[no] = i;
        find ( no+1, val*power ( p[no].num, i ), n );
    }
}

int main ()
{
    
    __int64 n;
    
    __int64 len = find ( MAX );
    while ( scanf ( "%I64d", &n ) != EOF )
    {
        pre = 0;
        __int64 temp = n;
        while ( temp > 1 )
        {
            temp = f ( temp, len );
        }
        
        next = 0;
        p[next].num = num[0];
        p[next].count = 1;
        next ++;
        for ( __int64 i=1; i<pre; i++ )
        {
            if ( num[i] != num[i-1] )
            {
                p[next].num = num[i];
                p[next].count = 1;
                next ++;
            }
            else
            {
                p[next-1].count ++;
            }
        }
        
        total_sum = 0;
        
        find ( 0, 1, n );
        
        printf ( "%I64d\n", total_sum );
        
    }
    return 0;
}
