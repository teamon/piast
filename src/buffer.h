struct BufferItem {
	char character;
	BufferItem* next;
};

class Buffer {
public:
	Buffer();
	void push(char c);
	void pop();
	void clear();
	bool empty();
	char * front();
	int size();
	char read();
	
private:
	int _counter;
	BufferItem *_head, *_tail;
};


