#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include <boost/optional.hpp>
#include <boost/rational.hpp>

namespace musical {

using boost::optional;
using rational = boost::rational<int>;
using optional_rational = optional<rational>;
using boost::none;

class stream;
class object {
  optional_rational offset_;
  std::map<stream*, rational> streams;
  stream *active_stream;
  std::set<object*> contexts;
public:
  object(): offset_{}, streams{}, active_stream{nullptr}, contexts{} {}
  virtual ~object() {}
  object(object const &) = delete;
  object &operator=(object const &) = delete;
  optional_rational offset() const {
    return active_stream? streams.at(active_stream): offset_;
  }
  rational offset(stream const &s) const { return streams.at(const_cast<stream*>(&s)); }
  virtual rational duration() const { return {}; }
private:
  /*for*/ friend class stream;
  void add(stream *s, rational offset) {
    streams.insert({active_stream=s, offset});
  }
  void add(object *o) { contexts.insert(o); }
  void remove(object *o);
};

class dynamic : public object {};
class rhythmic : public object {};
class rest : public rhythmic {};
class not_rest : public rhythmic {protected: not_rest(): rhythmic{} {} };
class note : public not_rest {};
class chord : public not_rest {};

class stream : public object
{
  std::vector<object*> elements;
public:
  stream(): object{}, elements{} {}
  void insert(rational const &offset, object &obj)
  {
    elements.push_back(&obj);
    obj.add(this, offset);
  }
  rational end_offset() const {
    rational result;
    for (auto element: elements) {
      rational end(element->offset(*this) + element->duration());
      if (end > result) result = end;
    }
    return result;
  }
  void append(object &obj) { insert(end_offset(), obj); }
};

void object::remove(object *o)
{
  streams.erase(dynamic_cast<musical::stream*>(o));
  contexts.erase(o);
}

template<char...> rational operator"" _th();
template<> rational operator"" _th<'8'>() { return rational{1, 8}; }
template<> rational operator"" _th<'1', '6'>() { return rational{1, 16}; }
template<> rational operator"" _th<'3', '2'>() { return rational{1, 32}; }
template<> rational operator"" _th<'6', '4'>() { return rational{1, 64}; }
template<> rational operator"" _th<'1', '2', '8'>() { return rational{1, 128}; }

}
