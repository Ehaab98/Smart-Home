#define CLR_BIT(x,n) x=x&(~(1<<n))
#define SET_BIT(x,n) x=x|(1<<n)
#define GET_BIT(x,n) (x>>n)&1
#define TOGGLE_BIT(x,n) x=x^((1<<n))