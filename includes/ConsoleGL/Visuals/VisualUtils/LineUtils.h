#ifndef LINE_UTILS_H
#define LINE_UTILS_H

static volatile size_t line_width = 1;

#ifdef _cplusplus
extern "C"
{
#endif

size_t getLineWidth(void) {return line_width;}

void setLineWidth(const size_t size) {line_width = size;}

void initLine(line* ln, const point a, const point b)
{
	ln->a = a;
	ln->b = b;
}

void destroyLine(line** ln)
{
	line* ptr = *ln;
	point* a = &(ptr->a), *b = &(ptr->b);
	
	destroyPoint(&a);
	destroyPoint(&b);
	
	*ln = null_line;
}

#ifdef _cplusplus
}
#endif

#endif