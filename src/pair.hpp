#pragma once
namespace ds{

template <typename T1, typename T2> class pair
{
  public:
    pair() = default;

    pair(T1 item1, T2 item2) : first(item1), second(item2) {}

    T1 first;
    T2 second;
};
template <typename T1, typename T2> class
pair<T1, T2> make_pair(T1 firstItem, T2 secondItem) {
    return pair<T1, T2>(firstItem, secondItem);
}

} // namespace ds