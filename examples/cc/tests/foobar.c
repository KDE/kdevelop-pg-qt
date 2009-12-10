int foo(int x, int y, int z, int a, int b, int c);

int foo(int x, int y)
{
	return x * x - y * y * y;
}

float bar(int x)
{
	return 1.f;
}

int read_int(int x) {}
int read_float();


int main(int argc, char* argv)
{
	return foo(read_int(), read_float() * read_int());
}

