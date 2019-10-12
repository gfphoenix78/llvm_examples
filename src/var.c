 int a;
 extern int b;
 int *ap;
 extern int *bp;
 struct foo {
 int id;
 char name[16];
 };
 struct foo f1 = {
 .id = 12,
 .name = "justing",
 };
extern struct foo f2;
extern struct foo *f3;

int func_b()
{
return b;
}

int * func_bp()
{
return bp;
}

struct foo func_f2()
{
return f2;
}

struct foo *func_f3()
{
return f3;
}

