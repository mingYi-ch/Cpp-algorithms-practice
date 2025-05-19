// === interval_map.hpp ===
#ifndef INTERVAL_MAP_ERASE_RANGE_HPP
#define INTERVAL_MAP_ERASE_RANGE_HPP

#include <map>
#include <type_traits>
#include <utility>

namespace interval_map_erase_range
{
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
            if (m_map.empty())
            {
                if (val == m_valBegin)
                    return;

                m_map.emplace(keyBegin, val);
                m_map.emplace(keyEnd, m_valBegin);
                return;
            }

            // find possible insertion position
            auto kBegin_lb = m_map.lower_bound(keyBegin);
            auto kEnd_lb = m_map.lower_bound(keyEnd);

            // store the possible(not for existing keyEnd) value for keyEnd
            V val1 = (kEnd_lb == m_map.begin()) ? m_valBegin : std::prev(kEnd_lb)->second;

            // insert  keyBegin/keyEnd in-place
            typename std::map<K, V>::iterator it_kBegin;
            // replace existing value if  keyBegin exists in the map
            if (kBegin_lb != m_map.end() &&
                !(kBegin_lb->first < keyBegin) &&
                !(keyBegin < kBegin_lb->first))
            {
                it_kBegin = kBegin_lb;
                it_kBegin->second = std::forward<V_forward>(val);
            }
            else
            {
                it_kBegin = m_map.emplace_hint(kBegin_lb, keyBegin, std::forward<V_forward>(val));
            }

            auto it_kEnd = m_map.emplace_hint(kEnd_lb, keyEnd, std::move(val1)); // no insertion of val1 if keyEnd exists in the map

            if (std::next(it_kBegin) != it_kEnd)
                m_map.erase(std::next(it_kBegin), it_kEnd);

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

#endif // INTERVAL_MAP_ERASE_RANGE_HPP
}