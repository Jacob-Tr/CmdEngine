#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#define initVect(vect, type) (vect) = ((vector##type) empty_vector##type)
#define destroyVect(vect, type) initVect(vect, type)

#ifdef _cplusplus
extern "C"
{
#endif

vector3 vector2ToVector3(const vector2 vect) {return ((vector3) {vect.x, 0, vect.z});}

vector3i vector2iToVector3i(const vector2i vect) {return ((vector3i) {vect.x, 0, vect.z});}

vector3l vector2lToVector3l(const vector2l vect) {return ((vector3l) {vect.x, 0, vect.z});}

vector3f vector2fToVector3f(const vector2f vect) {return ((vector3f) {vect.x, 0, vect.z});}

bool isValidVector2l(const vector2l vect) {return (vect.x >= 0 && vect.z >=0);}

vector2 vector2lToVector2(const vector2l vect) {return ((vector2) {(int_64) vect.x, (int_64) vect.z});}

vector2l vector2Absl(vector2l vect)
{
	vect.x = longAbs(vect.x);
	vect.z = longAbs(vect.z);
	
	return vect;
}

vector2l vector2ToVector2l(const vector2 vect)
{
	vector2l ret = ((vector2l) {0, 0});

	ret.x = ((int_64) vect.x);
	ret.z = ((int_64) vect.z);
	
	return ret;
}

size_t vector2Total(const vector2 a) {return ((a.x + a.x) + (a.z + a.z));}

size_t vector2Totall(const vector2l a) {return vector2Total(vector2lToVector2(a));}

size_t getVctor2Difference(const vector2 a, const vector2 b)
{
	vector2 diff;
	
	diff.x = sizeDifference(a.x, b.x);
	diff.z = sizeDifference(a.z, b.z);
	
	return vector2Total(diff);
}

size_t getVector2Differencel(vector2l a, vector2l b) {return (longDifference(a.x, b.x) + longDifference(a.z, b.z));}

bool isValidVector3l(const vector3l vect) {return (vect.x >= 0 && vect.y >= 0 && vect.x >= 0);}

bool isValidVector3i(const vector3i vect) {return (vect.x >= 0 && vect.y >= 0 && vect.x >= 0);}

vector3l vector3Absl(vector3l vect)
{
	vect.x *= 1;
	vect.y *= 1;
	vect.z *= 1;
	
	return vect;
}

vector3 vector3lToVector3(vector3l vect)
{
	vector3 ret = {0, 0, 0};
	if(!isValidVector3l(vect)) return ret;
	
	ret.x = ((size_t) vect.x);
	ret.y = ((size_t) vect.y);
	ret.z = ((size_t) vect.z);
	
	return ret;
}

vector3l vector3ToVector3l(const vector3 vect)
{
	vector3l ret = {0, 0, 0};
	
	ret.x = ((int_64) vect.x);
	ret.y = ((int_64) vect.y);
	ret.z = ((int_64) vect.z);
	
	return ret;
}

size_t getVector3Total(const vector3 vect) {return (vect.x + vect.y + vect.z);}

int_64 getVector3Totall(const vector3l vect) 
{
	int_64 ret = 0;
	
	ret += ((int_64) vect.x);
	ret += ((int_64) vect.y);
	ret += ((int_64) vect.z);
	
	return ret;
}

size_t getVector3Difference(const vector3 a, const vector3 b)
{
	size_t a_total = getVector3Total(a), b_total = getVector3Total(b);
	
	if(a_total > b_total) return (a_total - b_total);
	return (b_total - a_total);
}

size_t getVector3Differencel(const vector3l a, const vector3l b)
{
	size_t a_total = getVector3Totall(a), b_total = getVector3Totall(b);
	
	if(a_total > b_total) return (a_total - b_total);
	return (b_total - a_total);
}

vector3 vector3Add(const vector3 a, const vector3 b)
{
	vector3 ret = a;
	
	ret.x += b.x;
	ret.y += b.y;
	ret.z += b.z;
	
	return ret;
}

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