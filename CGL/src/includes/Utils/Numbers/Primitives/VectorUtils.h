#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

/*
	Get the maximum bounds of two vectors.
*/
vector3 getVector3Max(const vector3 a, const vector3 b) {return ((vector3) {.x = (a.x >= b.x) ? a.x : b.x, .y = (a.y >= b.y) ? a.y : b.y, .z = (a.z >= b.z) ? a.z : b.z});}
/*
	Get the minimum bounds of two vectors.
*/
vector3 getVector3Min (const vector3 a, const vector3 b) {return ((vector3) {.x = (a.x >= b.x) ? b.x : a.x, .y = (a.y >= b.y) ? b.y : a.y, .z = (a.z >= b.z) ? b.z : a.z});}

/*
	Some Vector conversion functions
*/
vector3 vector2ToVector3(const vector2 vect) {return ((vector3) {vect.x, 0, vect.z});}
vector3i vector2iToVector3i(const vector2i vect) {return ((vector3i) {vect.x, 0, vect.z});}
vector3l vector2lToVector3l(const vector2l vect) {return ((vector3l) {vect.x, 0, vect.z});}
vector3s vector2sToVector3s(const vector2s vect) {return ((vector3s) {vect.x, 0, vect.z});}
vector3f vector2fToVector3f(const vector2f vect) {return ((vector3f) {vect.x, 0, vect.z});}
vector2 vector2lToVector2(const vector2l vect) {return ((vector2) {(size_t) vect.x, (size_t) vect.z});}
vector2 vector2sToVector2(const vector2s vect) {return ((vector2) {(size_t) vect.x, (size_t) vect.z});}
vector2 vector2iToVector2(const vector2i vect) {return ((vector2) {(size_t) vect.x, (size_t) vect.z});}

/*
	Check if 'vect' is positive.
*/
bool isPositiveVector2l(const vector2l vect) {return (vect.x >= 0 && vect.z >= 0);}

/*
	Return the absolute values of 'vect'.
*/
vector2l vector2Absl(vector2l vect)
{
	vect.x = longAbs(vect.x);
	vect.z = longAbs(vect.z);
	
	return vect;
}

vector2l vector2ToVector2l(const vector2 vect)
{
	vector2l ret = ((vector2l) {0, 0});

	ret.x = ((int64_t) vect.x);
	ret.z = ((int64_t) vect.z);
	
	return ret;
}

/*
	Get the total value represented by 'vect'.
*/
size_t vector2Total(const vector2 vect) {return (vect.x + vect.z);}

/*
	Get the total value represented by 'vect'.
*/
size_t vector2Totall(const vector2l vect) {return vector2Total(vector2lToVector2(vect));}

/*
	Get the difference between 'a' and 'b'.
*/
size_t getVctor2Difference(const vector2 a, const vector2 b)
{
	vector2 diff;
	
	diff.x = ulongDifference(a.x, b.x);
	diff.z = ulongDifference(a.z, b.z);
	
	return vector2Total(diff);
}

/*
	Get the difference between 'a' and 'b'.
*/
size_t getVector2Differencel(vector2l a, vector2l b) {return (longDifference(a.x, b.x) + longDifference(a.z, b.z));}

/*
	Check if 'vect' is positive.
*/
bool isPositiveVector3l(const vector3l vect) {return (vect.x >= 0 && vect.y >= 0 && vect.x >= 0);}

/*
	Get the absolute value of 'vect'.
*/
vector3l vector3Absl(vector3l vect)
{
	vect.x *= 1;
	vect.y *= 1;
	vect.z *= 1;
	
	return vect;
}

/*
	Convert 'vect' from vector3l to vector3.
*/
vector3 vector3lToVector3(vector3l vect)
{
	vector3 ret = {0, 0, 0};
	if(!isPositiveVector3l(vect)) return ret;
	
	ret.x = ((size_t) vect.x);
	ret.y = ((size_t) vect.y);
	ret.z = ((size_t) vect.z);
	
	return ret;
}

/*
	Convert 'vect' from vector3 to vector3l
*/
vector3l vector3ToVector3l(const vector3 vect)
{
	vector3l ret = {0, 0, 0};
	
	ret.x = ((int64_t) vect.x);
	ret.y = ((int64_t) vect.y);
	ret.z = ((int64_t) vect.z);
	
	return ret;
}

/*
	Get the total represented by the sum of 'vect's members.
*/
size_t getVector3Total(const vector3 vect) {return (vect.x + vect.y + vect.z);}

/*
	Get the total represented by the sum of 'vect's members.
*/
int64_t getVector3Totall(const vector3l vect) 
{
	int64_t ret = 0;
	
	ret += ((int64_t) vect.x);
	ret += ((int64_t) vect.y);
	ret += ((int64_t) vect.z);
	
	return ret;
}

/*
	Get the total difference between all members and 'a' and 'b'.
*/
size_t getVector3Difference(const vector3 a, const vector3 b)
{
	size_t a_total = getVector3Total(a), b_total = getVector3Total(b);
	
	if(a_total > b_total) return (a_total - b_total);
	return (b_total - a_total);
}

/*
	Get the total difference between all members and 'a' and 'b'.
*/
size_t getVector3Differencel(const vector3l a, const vector3l b)
{
	size_t a_total = getVector3Totall(a), b_total = getVector3Totall(b);
	
	if(a_total > b_total) return (a_total - b_total);
	return (b_total - a_total);
}

/*
	Return the sum of adding corresponding members of 'a' and 'b'.
*/
vector3 vector3Add(const vector3 a, const vector3 b)
{
	vector3 ret = a;
	
	ret.x += b.x;
	ret.y += b.y;
	ret.z += b.z;
	
	return ret;
}

/*
	Return the sum of adding corresponding members of 'a' and 'b'.
*/
vector3l vector3Addl(const vector3l a, const vector3l b)
{
	vector3l ret = a;
	
	ret.x += b.x;
	ret.y += b.y;
	ret.z += b.z;
	
	return ret;
}

#ifdef _cplusplus
}
#endif

#endif