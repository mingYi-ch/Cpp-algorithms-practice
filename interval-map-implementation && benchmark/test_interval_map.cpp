// test_interval_map.cpp

#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include "interval_map.hpp"

using namespace std;

// helper to dump any map-like container to cerr
template <typename Map>
void print_map(const string &name, const Map &m)
{
    cerr << name << " { ";
    bool first = true;
    for (auto const &p : m)
    {
        if (!first)
            cerr << ", ";
        cerr << "(" << p.first << " → " << p.second << ")";
        first = false;
    }
    cerr << " }\n";
}

template <typename Map>
bool maps_equal(const Map &expected, const Map &actual)
{
    if (expected.size() != actual.size())
    {
        std::cerr << "❌ Map sizes differ: expected "
                  << expected.size() << " vs actual "
                  << actual.size() << "\n";
        print_map("expected", expected);
        print_map("actual", actual);
        return false;
    }

    auto it1 = expected.begin();
    auto it2 = actual.begin();
    size_t idx = 0;
    for (; it1 != expected.end(); ++it1, ++it2, ++idx)
    {
        if (it2 == actual.end())
        {
            std::cerr << "❌ Map iteration went out of sync at index "
                      << idx << "\n";
            print_map("expected", expected);
            print_map("actual", actual);
            return false;
        }
        if (it1->first != it2->first || it1->second != it2->second)
        {
            std::cerr << "❌ Mismatch at element " << idx << ": "
                      << "expected (" << it1->first << " → " << it1->second
                      << "), got (" << it2->first << " → " << it2->second
                      << ")\n";
            print_map("expected", expected);
            print_map("actual", actual);
            return false;
        }
    }

    // all checks passed
    return true;
}

void IntervalMapTest()
{
    // --- Deterministic tests ---
    {
        interval_map<int, char> m('A');
        // empty map: everything should be 'A'
        for (int k = -5; k <= 5; ++k)
        {
            assert(m[k] == 'A');
        }
        map<int, char> expected{};
        assert(maps_equal(expected, m.m_map));
    }

    {
        // head insertion
        {
            interval_map<int, char> m('X');
            m.assign(-10, -5, 'H');
            for (int k = -20; k < -10; ++k)
                assert(m[k] == 'X');
            for (int k = -10; k < -5; ++k)
                assert(m[k] == 'H');
            for (int k = -5; k <= 0; ++k)
                assert(m[k] == 'X');
            map<int, char> expected{{-10, 'H'}, {-5, 'X'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('X');
            m.assign(-10, -5, 'X');
            map<int, char> expected{};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('X');
            m.assign(-10, INT_MAX, 'H');
            map<int, char> expected{{-10, 'H'}, {INT_MAX, 'X'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 10, 'B');
            m.assign(10, 18, 'A');

            m.assign(0, 11, 'A');
            map<int, char> expected{};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, INT_MAX, 'B');
            m.assign(0, 8, 'B');
            map<int, char> expected{{0, 'B'}, {INT_MAX, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, 0, 'D');
            map<int, char> expected{{-5, 'D'}, {0, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, 5, 'A');
            map<int, char> expected{{5, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, 5, 'B');
            map<int, char> expected{{-5, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, 5, 'C');
            map<int, char> expected{{-5, 'C'}, {5, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }
        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, -1, 'A');
            map<int, char> expected{{0, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, -1, 'C');
            map<int, char> expected{{-5, 'C'}, {-1, 'A'}, {0, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, 101, 'C');
            map<int, char> expected{{-5, 'C'}, {101, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(-5, 101, 'B');
            map<int, char> expected{{-5, 'B'}, {101, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(5, 10, 'B');
            map<int, char> expected{{0, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(5, 10, 'C');
            map<int, char> expected{{0, 'B'}, {5, 'C'}, {10, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }

        {
            interval_map<int, char> m('A');
            m.assign(0, 100, 'B');
            m.assign(105, 110, 'A');
            map<int, char> expected{{0, 'B'}, {100, 'A'}};
            assert(maps_equal(expected, m.m_map));
        }
    }

    { // overlapping insertion
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(5, 15, 'C');

        // breakpoints: 0→B, 5→C, 15→A
        map<int, char> expected{
            {0, 'B'},
            {5, 'C'},
            {15, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion2
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(-5, 0, 'C');

        // breakpoints: -5→C, 0→B, 10→A
        map<int, char> expected{
            {-5, 'C'},
            {0, 'B'},
            {10, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 35, 'E');
        map<int, char> expected{
            {0, 'B'},
            {10, 'E'},
            {35, 'D'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 35, 'D');
        map<int, char> expected{
            {0, 'B'},
            {10, 'D'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 35, 'C');
        map<int, char> expected{
            {0, 'B'},
            {10, 'C'},
            {35, 'D'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 40, 'A');
        map<int, char> expected{
            {0, 'B'},
            {10, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 40, 'B');
        map<int, char> expected{
            {0, 'B'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 30, 'D');
        map<int, char> expected{
            {0, 'B'},
            {10, 'D'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 30, 'E');
        map<int, char> expected{
            {0, 'B'},
            {10, 'E'},
            {30, 'D'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    { // overlapping insertion3
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(10, 30, 'C');
        m.assign(30, 40, 'D');

        m.assign(10, 30, 'E');
        map<int, char> expected{
            {0, 'B'},
            {10, 'E'},
            {30, 'D'},
            {40, 'A'}};
        assert(maps_equal(expected, m.m_map));
    }

    {
        interval_map<int, string> m("A");

        m.assign(5, 10, std::string("B")); // [5,10) → std::string("B")
        assert(m[6] == std::string("B"));  // OK

        m.assign(7, 8, std::string("D")); // [7, 8) → 'D'
        //   expected: [5,7) → std::string("B"), [7,8) → 'D', [8,10) → std::string("B")
        // std::cout << "m[6] = '" << m[6] << "'\n"; // prints m[6] = ''  (empty!)
        assert(m[6] == std::string("B"));
    }

    // cases from randomized test
    {
        interval_map<int, char> m('A');
        m.assign(0, 10, 'B');
        m.assign(-6, 13, 'A');

        map<int, char> expected{};
        assert(maps_equal(expected, m.m_map));
    }

    cout << "[OK] Deterministic tests passed\n";

    // --- Randomized stress tests ---
    // 1. check key-value;
    // 2. canonical check: adjacent intervals with different value
    std::mt19937_64 gen(12345);
    std::uniform_int_distribution<int> dist_key(-20, 20);
    std::uniform_int_distribution<int> dist_len(1, 40);
    std::uniform_int_distribution<int> dist_val(0, 3);

    const std::vector<std::string> values = {"A", "B", "C", "D"};

    // insert into single interval
    for (int iter = 0; iter < 10000; ++iter)
    {
        int b = dist_key(gen);
        int len = dist_len(gen);
        int e = b + len;
        const std::string &v = values[dist_val(gen)];

        {
            // Single initial assignment [0,10) -> "B"
            interval_map<int, std::string> m(values[0]);
            m.assign(0, 10, values[1]);
            m.assign(b, e, v);

            // check tail before min(b,0)
            if (!m.m_map.empty())
                assert(m.m_map.begin()->second != values[0]);

            {
                std::uniform_int_distribution<int> sample_before(-5, std::min(b, 0) - 1);
                int k = sample_before(gen);
                assert(m[k] == values[0] && "tail remain 'A'");
            }
            // check head after max(e,10)
            {
                std::uniform_int_distribution<int> sample_after(std::max(e, 10), 80);
                int k = sample_after(gen);
                assert(m[k] == values[0] && "head remain 'A'");
            }
            // inside [b,e) must be v
            {
                if (b < e)
                {
                    std::uniform_int_distribution<int> sample_mid(b, e - 1);
                    int k = sample_mid(gen);
                    if (m[k] != v)
                    {
                        std::cerr << "❌ Expected m[" << k << "]=='" << v << "' but got '" << m[k] << "'\n";
                        assert(false);
                    }
                }
            }
            // left of b, inside [0,10)
            if (b >= 1 && b < 10)
            {
                std::uniform_int_distribution<int> sample_left(0, b - 1);
                int k = sample_left(gen);
                assert(m[k] == values[1]);
            }
            // right of e, inside [0,10)
            if (e >= 0 && e < 10)
            {
                std::uniform_int_distribution<int> sample_right(e, 9);
                int k = sample_right(gen);
                assert(m[k] == values[1]);
            }
            // if e<0 then stays default
            if (e < 0)
            {
                std::uniform_int_distribution<int> sample_neg(e, -1);
                int k = sample_neg(gen);
                assert(m[k] == values[0]);
            }
            // no two adjacent breakpoints share the same value
            {
                auto it = m.m_map.begin();
                if (it != m.m_map.end())
                {
                    for (auto prev = it++; it != m.m_map.end(); ++it, ++prev)
                    {
                        assert(prev->second != it->second);
                    }
                }
            }
        }

        {
            // Two initial intervals [0,10)->"B", [10,20)->"C"
            interval_map<int, std::string> m(values[0]);
            m.assign(0, 10, values[1]);
            m.assign(10, 20, values[2]);
            m.assign(b, e, v);

            // tail before min(b,0)
            if (!m.m_map.empty())
                assert(m.m_map.begin()->second != values[0]);
            {
                std::uniform_int_distribution<int> sample_before(-5, std::min(b, 0) - 1);
                int k = sample_before(gen);
                assert(m[k] == values[0]);
            }
            // head after max(e,20)
            {
                std::uniform_int_distribution<int> sample_after(std::max(e, 20), 80);
                int k = sample_after(gen);
                assert(m[k] == values[0]);
            }
            // inside [b,e) must be v
            if (b < e)
            {
                std::uniform_int_distribution<int> sample_mid(b, e - 1);
                int k = sample_mid(gen);
                if (m[k] != v)
                {
                    std::cerr << "❌ Expected m[" << k << "]=='" << v << "' but got '" << m[k] << "'\n";
                    assert(false);
                }
            }
            // left of b
            if (b >= 1 && b < 10)
            {
                std::uniform_int_distribution<int> sample_left(0, b - 1);
                assert(m[sample_left(gen)] == values[1]);
            }
            else if (b > 10 && b < 20)
            {
                std::uniform_int_distribution<int> sample_left(10, b - 1);
                assert(m[sample_left(gen)] == values[2]);
            }
            else if (b > 20)
            {
                std::uniform_int_distribution<int> sample_left(20, b - 1);
                assert(m[sample_left(gen)] == values[0]);
            }
            // right of e
            if (e > 0 && e < 10)
            {
                std::uniform_int_distribution<int> sample_right(e, 9);
                assert(m[sample_right(gen)] == values[1]);
            }
            else if (e >= 10 && e < 20)
            {
                std::uniform_int_distribution<int> sample_right(e, 19);
                assert(m[sample_right(gen)] == values[2]);
            }
            else if (e < 0)
            {
                std::uniform_int_distribution<int> sample_right(e, -1);
                assert(m[sample_right(gen)] == values[0]);
            }
            // no duplicate adjacent values
            {
                auto it = m.m_map.begin();
                if (it != m.m_map.end())
                {
                    for (auto prev = it++; it != m.m_map.end(); ++it, ++prev)
                    {
                        assert(prev->second != it->second);
                    }
                }
            }
        }

        {
            // Three initial: [0,10)->"B", [10,20)->"A", [20,30)->"D"
            interval_map<int, std::string> m(values[0]);
            m.assign(0, 10, values[1]);
            m.assign(10, 20, values[0]);
            m.assign(20, 30, values[3]);
            m.assign(b, e, v);

            // tail before min(b,0)
            if (!m.m_map.empty())
                assert(m.m_map.begin()->second != values[0]);
            {
                std::uniform_int_distribution<int> sample_before(-10, std::min(b, 0) - 1);
                int k = sample_before(gen);
                assert(m[k] == values[0]);
            }
            // head after max(e,30)
            {
                std::uniform_int_distribution<int> sample_after(std::max(e, 30), 80);
                int k = sample_after(gen);
                assert(m[k] == values[0]);
            }
            // inside [b,e)
            if (b < e)
            {
                std::uniform_int_distribution<int> sample_mid(b, e - 1);
                int k = sample_mid(gen);
                if (m[k] != v)
                {
                    std::cerr << "❌ Expected m[" << k << "]=='" << v << "' but got '" << m[k] << "'\n";
                    assert(false);
                }
            }
            // left of b
            if (b > 0 && b < 10)
            {
                std::uniform_int_distribution<int> sample_left(0, b - 1);
                assert(m[sample_left(gen)] == values[1]);
            }
            else if (b > 10 && b < 20)
            {
                std::uniform_int_distribution<int> sample_left(10, b - 1);
                assert(m[sample_left(gen)] == values[0]);
            }
            else if (b > 20 && b < 30)
            {
                std::uniform_int_distribution<int> sample_left(20, b - 1);
                assert(m[sample_left(gen)] == values[3]);
            }
            // right of e
            if (e > 0 && e < 10)
            {
                std::uniform_int_distribution<int> sample_right(e, 9);
                assert(m[sample_right(gen)] == values[1]);
            }
            else if (e > 10 && e < 20)
            {
                std::uniform_int_distribution<int> sample_right(e, 19);
                assert(m[sample_right(gen)] == values[0]);
            }
            else if (e > 20 && e < 30)
            {
                std::uniform_int_distribution<int> sample_right(e, 29);
                assert(m[sample_right(gen)] == values[3]);
            }
            // no duplicate adjacent values
            {
                auto it = m.m_map.begin();
                if (it != m.m_map.end())
                {
                    for (auto prev = it++; it != m.m_map.end(); ++it, ++prev)
                    {
                        assert(prev->second != it->second);
                    }
                }
            }
        }
    }

    cout << "[OK] Randomized tests passed\n";
}

int main()
{
    IntervalMapTest();
    cout << "All tests passed!\n";
    return 0;
}
