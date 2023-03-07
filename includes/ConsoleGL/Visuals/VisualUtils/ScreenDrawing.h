#ifndef SCREEN_DRAWING_H
#define SCREEN_DRAWING_H

#ifdef _cplusplus
extern "C"
{
#endif

void addPointToScrnBuf(screen_buffer* buf, const point pt) 
{
	if(buf == null_screen)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to set null screen buffer point %zu-%zu.\n", pt.vect.x, pt.vect.z);
		#endif
		
		return;
	}
	
	for(size_t i = getPointZ(pt); i < (getPointZ(pt) + pt.size.z); i++) for(size_t ii = getPointX(pt); ii < (getPointX(pt) + pt.size.x); ii++) setScreenBufPixel(buf, pt.px, ii, i);
}

/*vector2 getNextClosest2DNode(const vector2 a, const vector2 b)
{
	vector2l ret = vector2ToVector2l(a);
	
    while(vector2Difference(vector2lToVector2(ret), b) != 0) {}
}*/

vector2 getClosestNode2D(const vector2 a, const vector2 b)
{
	bool ignore[] = {(a.x == b.x), (a.z == b.z)}, skip = false;
	vector2l ret = empty_vector2l, lowest = empty_vector2l;
	int_64 prev_diff = getVector2Differencel(vector2ToVector2l(a), vector2ToVector2l(b));
	
	for(size_t i = 0; i < 9; i++)
	{
		int_64 diff = getVector2Differencel(ret, vector2ToVector2l(b));
		
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

vector3 getNextClosestNode(const vector3 a, const vector3 b)
{
	bool ignore[] = {(a.x == b.x), (a.y == b.y), (a.z == b.z)};
	vector3l ret = empty_vector3l, lowest = empty_vector3l;
	int_64 prev_diff = getVector3Differencel(vector3ToVector3l(a), vector3ToVector3l(b));
	uint_8 skip = 0;
	
	for(size_t i = 0; i < 25; i++)
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

void drawLine(screen_buffer* buf, const pixel set_px, const vector3 a, const vector3 b)
{
	vector3 node = a;
	
	for(size_t i = 0; i < getVector3Difference(a, b); i++)
	{
		node = getNextClosestNode(node, b);       if(getVector3Difference(node, b) == 0) break;
		if((node.x > buf->size.x) || (node.z > buf->size.z)) continue;
		
		setScreenBufPixel(buf, set_px, node.x, node.z);
	}
}

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