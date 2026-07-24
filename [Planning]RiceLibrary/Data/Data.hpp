#pragma once

struct Algorithm
{
    struct vec 
    {
    public:
    int dimention;
    private:
    void method1();
    void method2();
    }
    struct Matrix
    {
    public:

    private:
    void method1();
    void method2();
    }
};

struct IO
{
    void method1();
    void method2();
};

struct Memory {
    void method1();
    void method2();
};

struct exData{
    Algorithm util;
    IO io;
    Memory mem;
};

extern exData data;