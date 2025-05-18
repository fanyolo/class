class Plane
	{public:
			virtual float area() const =0;
			virtual float girth() const =0;
	}; 
class Body
	{public:
			float volume();
			float surfaceArea();
			void setpb(Plane *p);
			void sethigh();
	private:
			Plane *pbasic;
			float high;
	};
	
class Point
	{public:
			void setpoint();
			float x;
			float y;
	};
class Rectangle: public Plane
	{public:
			void setrec();
			virtual float area()const;
			virtual float girth()const;
	private:
			float a;
			float b;
	};
class Circle: public Plane
	{public:
			void setcir();
			virtual float area()const;
			virtual float girth()const;
	private:
			float a;
	};
class Triangle: public Plane
	{public:
			void settri();
			virtual float area()const;
			virtual float girth()const;
	private:
			Point A;
			Point B;
			Point C;
	};


