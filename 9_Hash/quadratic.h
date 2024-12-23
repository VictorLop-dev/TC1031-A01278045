

#ifndef MY_HASH
#define MY_HASH
#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~Quadratic();
	bool full() const;
	bool put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
		size = sze;
		keys = new Key[size];
		if (keys == 0){
			//throw OutOfMemory();

      return;
		}
		initialValue = init;
		for (unsigned int i = 0; i < size; i++){
			keys[i] = init;
		}
		values = new Value [size];
		if (values == 0){
      //~Quadratic();
      return;
		}
		for (int i = 0; i < sze; i++){
			values[i] = 0;
		}

		func = f;
		count = 0;

}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	keys = 0;
	delete [ ] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;

}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);

}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start,inc=0;
	start = i = func(k) % size;
  //std::cout<<"Inicio de "<<k<<": "<<start<<std::endl;
	do {
		if (keys[i] == k){
			return i;
		}
    //incremento+=1;
    inc+=1;
		i = ((i+ (inc*inc) ) % size);
    //std::cout<<"Valor candidato del indice: "<<i<<std::endl;
	}
		while (start != i && inc<size);
		return -1;
		//El start es para evitar que iteremos infinitamente.




}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {

	unsigned int i, start;
	long pos;

	if (full()) {
		//throw Overflow();
    return false;
	}

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
    keys[pos] = k;
    //std::cout<<"Reemplazo! \n";
		return true;
	}

	start = i = func(k) % size;
  int inc=0;

	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return true;
		}
    inc+=1;
		i = (i + (inc*inc)) % size;
	} while (start != i && inc<size);
	return false;


}


template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	long pos;
	pos = indexOf(k);
	return (pos != -1);
	//Esta parte del codigo se aprovecha de que la funcion indexOf nos retorna -1
	//en caso de no poder encontrar el valor que buscamos.

}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	unsigned int i, start;
	long pos;
	pos = indexOf(k);
	if (pos != -1){
		return values[pos];
	}
	//throw NoSuchElement();
	//No sé como manejar el caso donde está lleno sin un throw.

}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	std::stringstream aux;
	count = 0;
	for (unsigned int i = 0; i < size; i++){
		keys[i] = initialValue;
	}
}




template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;

	for (unsigned int i = 0; i < size; i++) {
    if(keys[i] != "empty"){
      aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
    }

	}
	return aux.str();
}




#endif
