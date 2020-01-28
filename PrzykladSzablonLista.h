#pragma once
template<class T>
class SzablonLista
{
public:
	typedef T* value_type;
	typedef unsigned int size_type;
	typedef int* iterator;
	typedef T& reference;
    struct TElementStr {
      T *element;
      TElementStr *nastepny;
    };
private:
    TElementStr *glowa = nullptr;
public:
  SzablonLista() {};
  ~SzablonLista() {}; //TODO: destruktor koniecznie do oprogramowania!
  void add(reference element) {
	  if (glowa) {
        glowa->nastepny = new TElementStr;
        glowa = glowa->nastepny;
      } else {
        glowa = new TElementStr;
      }
    glowa->element = &element;
    glowa->nastepny = nullptr;
  };
};
