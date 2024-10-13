#include <utility>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <stack>

#pragma once

template <typename T, size_t N> //перегрузка вывода для std::array
std::ostream& operator<<(std::ostream& out, const std::array <T, N>& a)
{
    out << "[";
    for (size_t i = 0; i < N; i++)
    {
        out << a[i];
        if (i < N - 1)
            out << ", ";
    }
    out << "]";
    return out;
}

template <typename T1, typename T2> //перегрузка вывода для std::pair
std::ostream& operator<<(std::ostream& out, const std::pair <T1, T2>& p)
{
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

template <typename T1, typename T2> //перегрузка вывода для std::map
std::ostream& operator<<(std::ostream& out, const std::map <T1, T2>& mp)
{
    out << "{";

    for(auto [key, value] : mp)
        out << "(" << key << ": " << value << ")";

    out << "}";
    return out;
}

template <typename T> //перегрузка вывода для std::vector
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
    out << "{";
    for (size_t i = 0; i < v.size(); i++)
    {
        out << v[i];
        if (i < v.size() - 1)
            out << ", ";
    }
    out << "}";
    return out;
}


template <typename T> //перегрузка вывода для std::list
std::ostream& operator<<(std::ostream& out, const std::list<T>& l)
{
    int len = l.size();
    int i = 0;

    out << "{";
    for (auto x : l)
    {
        i++;
        out << x;
        if (i != len)
            out << ", ";
    }


    out << "}";
    return out;
}


template <typename T> //перегрузка вывода для std::set
std::ostream& operator<<(std::ostream& out, const std::set<T>& st)
{
    int len = st.size();
    int i = 0;

    out << "{";
    for (auto x : st)
    {
        i++;
        out << x;
        if (i != len)
            out << ", ";
    }


    out << "}";
    return out;
}


template <typename T, typename Comp> //перегрузка вывода для std::set с компаратором
std::ostream& operator<<(std::ostream& out, const std::set<T, Comp>& st)
{
    int len = st.size();
    int i = 0;

    out << "{";
    for (auto x : st)
    {
        i++;
        out << x;
        if (i != len)
            out << ", ";
    }


    out << "}";
    return out;
}



template <typename T> //перегрузка вывода для std::multiset
std::ostream& operator<<(std::ostream& out, const std::multiset<T>& mst)
{
    int len = mst.size();
    int i = 0;

    out << "{";
    for (auto x : mst)
    {
        i++;
        out << x;
        if (i != len)
            out << ", ";
    }


    out << "}";
    return out;
}


template <typename T, typename Comp> //перегрузка вывода для std::multiset с компараторм
std::ostream& operator<<(std::ostream& out, const std::multiset<T, Comp>& mst)
{
    int len = mst.size();
    int i = 0;

    out << "{";
    for (auto x : mst)
    {
        i++;
        out << x;
        if (i != len)
            out << ", ";
    }


    out << "}";
    return out;
}


template<typename T> // перегрузка вывода для std::stack
std::ostream& operator<<(std::ostream& out, const std::stack<T> st)
{
    std::stack<T> stcopy = st;
    int sz = st.size();

    out << "{";

    for (int i = 0; i < sz; i++)
    {
        out << stcopy.top();
        if (i < sz - 1)
            out << " -> ";
        
        stcopy.pop();
    }

    out << "}";

    return out;
}


template <typename T>
void printMatrix(const std::vector<std::vector<T> >& v)
{
    for (std::vector<T> x : v)
    {
        std:: cout << x << std::endl;
    }
    std::cout << std::endl;
}


