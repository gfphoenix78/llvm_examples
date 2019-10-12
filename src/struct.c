
struct bar {
int id;
char name[32];
};

struct foo {
int a;
struct bar bar;
struct foo *next;
};


void setfoo(struct foo *f, int x)
{
	f->a += x;
	f->bar.id = x;
	f->next->a += x;
	f->next->bar.id = x;

	f->a += x + f->bar.id;
	f->next->a += x + f->a;
}

