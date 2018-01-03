#include <stdint.h>
#include <stdio.h>

#define PHI 0x9e3779b9

static uint32_t Q[4096], c = 362436;

void init_rand(uint32_t x)
{
    int i;

    Q[0] = x;
    Q[1] = x + PHI;
    Q[2] = x + PHI + PHI;
    for (i = 3; i < 4096; i++)
	Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

uint32_t rand_cmwc(void)
{
    uint64_t t, a = 18782LL;
    static uint32_t i = 4095;
    uint32_t x, r = 0xfffffffe;

    i = (i + 1) & 4095;
    t = a * Q[i] + c;
    c = (t >> 32);
    x = t + c;
    if (x < c) 
    {
       x++;
       c++;
    }
    return (Q[i] = r - x);
}

void main (void)
{
    uint32_t x, i = 1024*1024*100; // i bytes to generate
    init_rand(69);
    while (i > 0)
	{
	x = rand_cmwc();
	fwrite(&x, sizeof(x), 1, stdout);
	i--;
	}

}
