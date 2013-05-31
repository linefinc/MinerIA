class Point2d
{
public:
	int x;
	int y;
	float distance;
	char dx;
	char dy;

	Point2d()
		:x(0),y(0),distance(-1.0f),dx(0),dy(0)
	{
		
	}

	Point2d(int x, int y)
		:x(x),y(y),distance(-1.0f),dx(0),dy(0)
	{
		
	}



	bool operator == (const Point2d &other) const
	{
		if((x == other.x)&&(y == other.y))
		{
			return true;
		}
		return false;
	}

	void CalcDistance(const Point2d &other)
	{
		float temp = (float)(x - other.x);
		distance = temp * temp;
		temp =(float) (y - other.y);
		distance += temp * temp;
	}
};