#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  Heap(int m=2, PComparator c = PComparator());
  ~Heap();
  void push(const T& item);
  T const & top() const;
  void pop();
  bool empty() const;
  size_t size() const;

private:
  std::vector<T> data_;
  int m_;
  PComparator c_;

  void trickleUp(size_t idx);
  void heapify(size_t idx);
};

// Constructor: store ary-ness and comparator
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m_(m), c_(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

// Move item at idx up while it has priority over its parent
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t idx)
{
  while (idx > 0) {
    size_t parent = (idx - 1) / m_;
    if (c_(data_[idx], data_[parent])) {
      std::swap(data_[idx], data_[parent]);
      idx = parent;
    } else {
      break;
    }
  }
}

template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  if(empty()){
    throw std::underflow_error("Heap::top() called on empty heap");
  }
  return data_[0];
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("Heap::pop() called on empty heap");
  }
  data_[0] = data_.back();
  data_.pop_back();
  if (!empty()) {
    heapify(0);
  }
}

// Move item at idx down while some child has priority over it
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t idx)
{
  while (true) {
    size_t first = m_ * idx + 1;          // first child
    if (first >= data_.size()) break;     // leaf: no children

    // find the highest-priority child among up to m children
    size_t best = first;
    for (int k = 1; k < m_; k++) {
      size_t child = first + k;
      if (child >= data_.size()) break;
      if (c_(data_[child], data_[best])) {
        best = child;
      }
    }

    if (c_(data_[best], data_[idx])) {
      std::swap(data_[idx], data_[best]);
      idx = best;
    } else {
      break;
    }
  }
}

#endif