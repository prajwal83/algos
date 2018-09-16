#include <iostream>
#include <list>
#include <memory>
#include "../../test_framework/catch.hpp"

class Animal
{
public:
  explicit Animal(const int id) : _id(id) {}
  virtual ~Animal() { }
  const int Id() const { return _id; }
protected:
  int _id;
};

class Dog : public Animal
{
public:
  explicit Dog(const int id) : Animal(id) {}
  ~Dog() {}
};

class Cat : public Animal
{
public:
  explicit Cat(const int id) : Animal(id) {}
  ~Cat() {}
};

class AnimalShelter
{
public:
  void operator=(std::initializer_list<std::shared_ptr<Animal>> l)
  {
    for(auto a : l)
      enqueue(a);
  }

  void enqueue(std::shared_ptr<Animal> a)
  {
    if(typeid(*a.get()) == typeid(Dog))
      _dogs.push_back(std::static_pointer_cast<Dog>(a));
    else
      _cats.push_back(std::static_pointer_cast<Cat>(a));
    _animals.push_back(a);
  }

  bool hasDogs() const { return !_dogs.empty(); }
  bool hasCats() const { return !_cats.empty(); }
  bool hasAnimals() const { return !_animals.empty(); }

  std::shared_ptr<Dog> dequeueDog()
  {
    if(_dogs.empty())
      throw std::string("no dogs in shelter");

    auto dog = *_dogs.begin();
    _dogs.pop_front();

    cleanUp();
    return dog;
  }

  std::shared_ptr<Cat> dequeueCat()
  {
    if(_cats.empty())
      throw std::string("no cats in shelter");

    auto cat = *_cats.begin();
    _cats.pop_front();

    cleanUp();
    return cat;
  }

  std::shared_ptr<Animal> dequeueAny()
  {
    while(!_animals.empty()) 
    {
      auto animal = *_animals.begin();
      _animals.pop_front();
      
      if(typeid(*animal.get()) == typeid(Dog) && !_dogs.empty() && *_dogs.begin() == animal)
      {
        _dogs.pop_front();
        return animal;
      }

      if(typeid(*animal.get()) == typeid(Cat) && !_cats.empty() && *_cats.begin() == animal)
      {
        _cats.pop_front();
        return animal;
      }
    }

    throw std::string("no animals in shelter");
  }

private:
  void cleanUp()
  {
    if(_dogs.empty() && _cats.empty())
      while(!_animals.empty()) _animals.pop_front();
  }

  std::list<std::shared_ptr<Dog>> _dogs;
  std::list<std::shared_ptr<Cat>> _cats;
  std::list<std::shared_ptr<Animal>> _animals;
};

TEST_CASE("animal shelter with single animal", "[ch3.6]")
{
  AnimalShelter s;
  std::shared_ptr<Animal> dog(new Dog(1));
  s.enqueue(dog);
  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueDog() == dog);
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == false);

  s.enqueue(dog);
  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueAny() == dog);
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == false);

  std::shared_ptr<Animal> cat(new Cat(1));
  s.enqueue(cat);
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueAny() == cat);
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == false);

  s.enqueue(cat);
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueCat() == cat);
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == false);
}

TEST_CASE("animal shelter with multiple animal", "[ch3.6]")
{
  AnimalShelter s;
  auto l = { 
    std::shared_ptr<Animal>(new Dog(1)),
    std::shared_ptr<Animal>(new Cat(2)),
    std::shared_ptr<Animal>(new Dog(3)),
    std::shared_ptr<Animal>(new Cat(4)),
    std::shared_ptr<Animal>(new Dog(5)),
    std::shared_ptr<Animal>(new Dog(6)),
    std::shared_ptr<Animal>(new Cat(7)),
  };
  s = l;
  auto it = l.begin();
  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueDog() == *it);
  ++it;

  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueCat() == *it);
  ++it;

  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueAny() == *it);
  ++it;

  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueAny() == *it);
  ++it;

  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueDog() == *it);
  ++it;

  REQUIRE(s.hasDogs() == true);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueDog() == *it);
  ++it;
  
  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == true);
  REQUIRE(s.hasAnimals() == true);
  REQUIRE(s.dequeueAny() == *it);
  ++it;

  REQUIRE(s.hasDogs() == false);
  REQUIRE(s.hasCats() == false);
  REQUIRE(s.hasAnimals() == false);
}
