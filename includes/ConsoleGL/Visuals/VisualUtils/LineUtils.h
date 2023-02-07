#ifndef LINE_UTILS_H
#define LINE_UTILS_H

size_t line_width = 1;

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

void destroyLine(line* ln)
{
	destroyPoint(ln->a);
	destroyPoint(ln->b);
	
	*ln = EMPTY_LINE;
}

#ifdef _cplusplus
}
#endif

#endif