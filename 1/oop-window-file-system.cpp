class Component
{
	int val;
	public:
		Component(int value): val (value)  {}
		virtual void add(Component*) {}
};

class Primitive: public Component
{
	public:
		Primitive(int val): Component(val) {}
};

class Composite: public Component
{
	vector<Component*> c;
	public:
		Composite(int val): Component(val) {}
		void add(Component* elem){
			c.push_back(elem);
		}

};
