#ifndef SCREEN_DRAWING_H
#define SCREEN_DRAWING_H

#ifdef _cplusplus
extern "C"
{
#endif

/*
	Update screen_buffer 'buf' to include the point 'pt'.
*/
void addPointToScrnBuf(screen_buffer* buf, const point pt) 
{
	if(buf == ((screen_buffer*) NULL))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to set null screen buffer point %zu-%zu.\n", pt.vect.x, pt.vect.z);
		#endif
		
		return;
	}
	
	for(size_t i = getPointZ(pt); i < (getPointZ(pt) + pt.size.z); i++) for(size_t ii = getPointX(pt); ii < (getPointX(pt) + pt.size.x); ii++) setScreenBufPixel(buf, pt.px, ii, i);
}

/*
	Find the neighboring 2D vector coordinates to 'a' which is the closest path to 'b'.
*/
vector2 getClosestNode2D(const vector2 a, const vector2 b)
{
	// An array to ignore positions which have already been checked.
	bool ignore[] = {(a.x == b.x), (a.z == b.z)}, skip = false;
	// Variable used to return the final solution and a placeholder for current closest value to 'b' respectively.
	vector2l ret = empty_vector2l, lowest = empty_vector2l;
	// The previous difference between 'a' and 'b'.
	int_64 prev_diff = getVector2Differencel(vector2ToVector2l(a), vector2ToVector2l(b));
	
	// There are 8 possible positions in a square surrounding 'a'.
	for(size_t i = 0; i < 8; i++)
	{
		// The current difference between the current lowest check and 'b'.
		int_64 diff = getVector2Differencel(ret, vector2ToVector2l(b));
		
		// Check if this check is closer then the last closest.
		if(diff < prev_diff) 
		{
			lowest = ret;
			prev_diff = diff;
		}
		
		
	    if(!ignore[0])
	    {
            if(!skip)
            {
		        if((ret.x == 0) && (a.x < b.x)) {ret.x++;}
		        else ret.x = -1;
		    
		        continue;
    		}
	    }
    	if(!ignore[1])
    	{
    		if((ret.z == 0) && (a.z < b.z)) {ret.z++;}
    		else ret.z = -1;
    	}
	
    	skip = false;
	}
	
	ret = lowest;
	
	return vector2lToVector2(ret);
}

/*
	Find the neighboring 3D vector coordinates to 'a' which is the closest path to 'b'.
*/
vector3 getNextClosestNode(const vector3 a, const vector3 b)
{
	// An array to ignore changing values when we haven't yet finished checking a given row, column or axis.
	bool ignore[] = {(a.x == b.x), (a.y == b.y), (a.z == b.z)};
	// Variables to store the current return and lowest distance values respectively.
	vector3l ret = empty_vector3l, lowest = empty_vector3l;
	// Variable to hold the previous difference between the coordinates of 'a' and 'b'.
	int_64 prev_diff = getVector3Differencel(vector3ToVector3l(a), vector3ToVector3l(b));
	// Variable to determine whether or not to continue checking a row, column or axis.
	uint_8 skip = 0;
	
	// There are 34 possible positions surrounding 'a' in a cube.
	for(size_t i = 0; i < 34; i++)
	{
		vector3l check = vector3Addl(vector3ToVector3l(a), ret);
		int_64 diff = getVector3Differencel(check, vector3ToVector3l(b));
		
		if(diff < prev_diff)
		{
			lowest = check;
			prev_diff = diff;
		}
		
		if(!ignore[0] && (skip < 1))
		{
			if(ret.x == 0) ret.x++;
			else if(ret.x == 1) ret.x = -1;
			else ret.x = 0;
			
			skip++;
			
			continue;
		}
		
		if(!ignore[1] && (skip < 2))
		{
			if(ret.y == 0) ret.y++;
			else if(ret.y == 1) ret.y = -1;
			else
			{
				skip = 0;
				ret.y = 0;
				
				continue;
			}
			
			skip++;
			
			continue;
		}
		
		if(ret.z == 0) ret.z++;
		else if(ret.z == 1) ret.z = -1;
		else
		{
			skip = 0;
			ret.z = 0;
		}
	}
	
	ret = lowest;
	
	return vector3lToVector3(ret);
}

/*
	Draw two points and connect them with a straight line.
*/
void drawLine(screen_buffer* buf, const pixel set_px, const vector3 a, const vector3 b)
{
	vector3 node = a;
	
	// For each position between 'a' and 'b', color the pixel at that location.
	for(size_t i = 0; i < getVector3Difference(a, b); i++)
	{
		// Find the next closest position between 'a' and 'b'.
		node = getNextClosestNode(node, b);
		
		// Check if path has been found, if so exit loop.
		if(getVector3Difference(node, b) == 0) break;

		// Check if current position exceeds 'buf' bounds; if so reiterate.
		if((node.x > buf->size.x) || (node.z > buf->size.z)) continue;
		
		// Set current position pixel to 'set_px'.
		setScreenBufPixel(buf, set_px, node.x, node.z);
	}
}

/*
	Break 'ln' to primitive components and render it to 'buf'.
*/
void addLineToScrnBuf(screen_buffer* buf, const line ln)
{
	addPointToScrnBuf(buf, ln.a);
	addPointToScrnBuf(buf, ln.b);
	
	pixel px;
	initPixel(&px, 'b');
	
	drawLine(buf, px, ln.a.vect, ln.b.vect);
}

#ifdef _cplusplus
}
#endif

#endif