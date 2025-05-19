// === interval_map.hpp ===
#ifndef INTERVAL_MAP_HPP
#define INTERVAL_MAP_HPP

#include <map>
#include <type_traits>
#include <utility>

template <typename K, typename V>
class interval_map
{
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val
    template <typename V_forward>
    interval_map(V_forward &&val)
        : m_valBegin(std::forward<V_forward>(val))
    {
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    template <typename V_forward>
    void assign(K const &keyBegin, K const &keyEnd, V_forward &&val)
        requires(std::is_same<std::remove_cvref_t<V_forward>, V>::value)
    {
        // empty interval
        if (!(keyBegin < keyEnd))
            return;

        // empty map
        if (m_map.size() == 0)
        {
            if (val == m_valBegin)
                return;

            m_map.emplace(keyBegin, val);
            m_map.emplace(keyEnd, m_valBegin);
            return;
        }

        // find possible insertion position
        // auto kBegin_lb = m_map.lower_bound(keyBegin);
        auto kEnd_lb = m_map.lower_bound(keyEnd);
        typename std::map<K, V>::iterator it_kEnd;

        // insert keyEnd
        if (kEnd_lb == m_map.begin())
        {
            it_kEnd = m_map.emplace_hint(kEnd_lb, keyEnd, m_valBegin);
        }
        else
        {
            it_kEnd = m_map.emplace_hint(kEnd_lb, keyEnd, std::prev(kEnd_lb)->second);
        }

        // insert  keyBegin/keyEnd in-place
        typename std::map<K, V>::iterator it_search = it_kEnd;
        while (it_search != m_map.begin() &&
               !(it_search->first < keyBegin))
        {
            auto temp = std::prev(it_search);
            if (it_search != it_kEnd)
            {
                m_map.erase(it_search);
            }

            it_search = temp;
        }

        // check boundary case when loop ends, it_search == m_map.begin() and keyBegin is no greater than the first key
        if (it_search == m_map.begin() &&
            !(it_search->first < keyBegin) &&
            it_search != it_kEnd)
        {
            m_map.erase(it_search);
        }

        auto it_kBegin = m_map.emplace_hint(it_kEnd, keyBegin, std::forward<V_forward>(val));
        // canonical check: merge adjacent intervals with the same value
        // ..BCC..
        if (it_kBegin->second == it_kEnd->second)
        {
            m_map.erase(it_kEnd);
        }
        // ..CCB..
        if (it_kBegin != m_map.begin() && std::prev(it_kBegin)->second == it_kBegin->second)
        {
            m_map.erase(it_kBegin);
        }
        // ..AAB..
        while (!m_map.empty() && m_map.begin()->second == m_valBegin)
        {
            m_map.erase(m_map.begin());
        }
    }

    // look-up of the value associated with key
    V const &operator[](K const &key) const
    {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
        {
            return m_valBegin;
        }
        else
        {
            return (--it)->second;
        }
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

#endif // INTERVAL_MAP_HPP